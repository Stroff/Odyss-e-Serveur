/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "oculus.h"

//Types of drake mounts: Ruby(Tank),  Amber(DPS),  Emerald(Healer)
//Two Repeating phases

enum Spells
{
    SPELL_ARCANE_BARRAGE                          = 50804,
    H_SPELL_ARCANE_BARRAGE                        = 59381,
    SPELL_ARCANE_VOLLEY                           = 51153,
    H_SPELL_ARCANE_VOLLEY                         = 59382,
    SPELL_ENRAGED_ASSAULT                         = 51170,
    SPELL_PLANAR_ANOMALIES                        = 57959,
    SPELL_PLANAR_SHIFT                            = 51162,

    SPELL_PLANAR_DISTORSION                       = 59379,
    SPELL_PLANAR_ANOMALIE_AGGRO                   = 57971,
    NPC_PLANAR_ANOMALIE                           = 30879,
    SPELL_PLANAR_BLAST                           = 57976,
    NPC_GREATER_LEY_WHELP                       = 28276
};
/*Ruby Drake ,
(npc 27756) (item 37860)
(summoned by spell Ruby Essence = 37860 ---> Call Amber Drake == 49462 ---> Summon 27756)
*/
enum RubyDrake
{
    NPC_RUBY_DRAKE_VEHICLE                        = 27756,
    SPELL_RIDE_RUBY_DRAKE_QUE                     = 49463,          //Apply Aura: Periodic Trigger, Interval: 3 seconds ---> 49464
    SPELL_RUBY_DRAKE_SADDLE                       = 49464,          //Allows you to ride on the back of an Amber Drake. ---> Dummy
    SPELL_RUBY_SEARING_WRATH                      = 50232,          //(60 yds) - Instant - Breathes a stream of fire at an enemy dragon, dealing 6800 to 9200 Fire damage and then jumping to additional dragons within 30 yards. Each jump increases the damage by 50%. Affects up to 5 total targets
    SPELL_RUBY_EVASIVE_AURA                       = 50248,          //Instant - Allows the Ruby Drake to generate Evasive Charges when hit by hostile attacks and spells.
    SPELL_RUBY_EVASIVE_MANEUVERS                  = 50240,          //Instant - 5 sec. cooldown - Allows your drake to dodge all incoming attacks and spells. Requires Evasive Charges to use. Each attack or spell dodged while this ability is active burns one Evasive Charge. Lasts 30 sec. or until all charges are exhausted.
    //you do not have acces to until you kill Mage-Lord Urom
    SPELL_RUBY_MARTYR                             = 50253          //Instant - 10 sec. cooldown - Redirect all harmful spells cast at friendly drakes to yourself for 10 sec.
};
/*Amber Drake,
(npc 27755)  (item 37859)
(summoned by spell Amber Essence = 37859 ---> Call Amber Drake == 49461 ---> Summon 27755)
*/
enum AmberDrake
{
    NPC_AMBER_DRAKE_VEHICLE                       = 27755,
    SPELL_RIDE_AMBER_DRAKE_QUE                    = 49459,          //Apply Aura: Periodic Trigger, Interval: 3 seconds ---> 49460
    SPELL_AMBER_DRAKE_SADDLE                      = 49460,          //Allows you to ride on the back of an Amber Drake. ---> Dummy
    SPELL_AMBER_SHOCK_LANCE                       = 49840,         //(60 yds) - Instant - Deals 4822 to 5602 Arcane damage and detonates all Shock Charges on an enemy dragon. Damage is increased by 6525 for each detonated.
//  SPELL_AMBER_STOP_TIME                                    //Instant - 1 min cooldown - Halts the passage of time, freezing all enemy dragons in place for 10 sec. This attack applies 5 Shock Charges to each affected target.
    //you do not have access to until you kill the  Mage-Lord Urom.
    SPELL_AMBER_TEMPORAL_RIFT                     = 49592         //(60 yds) - Channeled - Channels a temporal rift on an enemy dragon for 10 sec. While trapped in the rift, all damage done to the target is increased by 100%. In addition, for every 15,000 damage done to a target affected by Temporal Rift, 1 Shock Charge is generated.
};
/*Emerald Drake,
(npc 27692)  (item 37815),
 (summoned by spell Emerald Essence = 37815 ---> Call Emerald Drake == 49345 ---> Summon 27692)
*/
enum EmeraldDrake
{
    NPC_EMERALD_DRAKE_VEHICLE                     = 27692,
    SPELL_RIDE_EMERALD_DRAKE_QUE                  = 49427,         //Apply Aura: Periodic Trigger, Interval: 3 seconds ---> 49346
    SPELL_EMERALD_DRAKE_SADDLE                    = 49346,         //Allows you to ride on the back of an Amber Drake. ---> Dummy
    SPELL_EMERALD_LEECHING_POISON                 = 50328,         //(60 yds) - Instant - Poisons the enemy dragon, leeching 1300 to the caster every 2 sec. for 12 sec. Stacks up to 3 times.
    SPELL_EMERALD_TOUCH_THE_NIGHTMARE             = 50341,         //(60 yds) - Instant - Consumes 30% of the caster's max health to inflict 25,000 nature damage to an enemy dragon and reduce the damage it deals by 25% for 30 sec.
    // you do not have access to until you kill the Mage-Lord Urom
    SPELL_EMERALD_DREAM_FUNNEL                    = 50344         //(60 yds) - Channeled - Transfers 5% of the caster's max health to a friendly drake every second for 10 seconds as long as the caster channels.
};

class boss_eregos : public CreatureScript
{
public:
    boss_eregos() : CreatureScript("boss_eregos") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_eregosAI (pCreature);
    }

struct boss_eregosAI : public ScriptedAI
{
    boss_eregosAI(Creature *c) : ScriptedAI(c), lSummons(me)
    {
        pInstance = c->GetInstanceScript();
    }

    InstanceScript* pInstance;
    bool barrage ;
    bool isSummoning ;
    uint16 phase ;
    uint16 whelpsNumber ;
    uint32 enragedAssaultTimer ;
    uint32 phaseTimer ;
    uint32 whelpSummonTimer ;
    uint32 castTimer ;
    std::list<Creature*> anomalieList ;
    SummonList lSummons;

    void Reset()
    {
        castTimer = 2000 ;
        enragedAssaultTimer = 40000 ;
        whelpSummonTimer = 90000 ;
        isSummoning = false ;
        whelpsNumber = 0 ;
        phase = 0 ;
        lSummons.DespawnAll();
        anomalieList.clear() ;
        barrage = false ;
        me->SetFlying(true);
        if (pInstance)
            pInstance->SetData(DATA_EREGOS_EVENT, NOT_STARTED);
    }

        void EnterCombat(Unit* /*who*/)
    {
        if (pInstance)
            pInstance->SetData(DATA_EREGOS_EVENT, IN_PROGRESS);
    }

        void AttackStart(Unit* /*who*/) {}
        void MoveInLineOfSight(Unit* /*who*/) {}
    void JustSummoned(Creature* summon)
    {
        lSummons.Summon(summon);
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();

        if(phase == 0 || phase == 2)
        {
            if(enragedAssaultTimer < diff)
            {
                DoCast(me, SPELL_ENRAGED_ASSAULT, true);
                enragedAssaultTimer = 40000;
            } else enragedAssaultTimer -= diff;

            if(isSummoning)
            {
                if(whelpsNumber<4)
                {
                    if (Creature* whelp = me->SummonCreature(NPC_GREATER_LEY_WHELP, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
                    {
                        whelp->SetFlying(true);
                        whelp->SetInCombatWithZone();
                        whelp->AI()->AttackStart(me->getVictim());
                    }
                    whelpsNumber++ ;
                }
                else
                {
                    whelpsNumber = 0 ;
                    isSummoning = false ;
                }
            }
            else
            {
                if(whelpSummonTimer<diff)
                {
                    isSummoning = true ;
                    whelpSummonTimer = 90000 ;
                    whelpsNumber = 0 ;
                } else whelpSummonTimer -= diff ;
            }

            if((phase == 0 && (me->GetHealth()*100 / me->GetMaxHealth() <= 60)) || (phase == 2 && (me->GetHealth()*100 / me->GetMaxHealth()) <= 20))
            {
                DoCast(me, SPELL_PLANAR_SHIFT, true);
                DoCast(me, SPELL_PLANAR_ANOMALIES,true);
                Map* pMap = me->GetMap();
                if (pMap && pMap->IsDungeon())
                {
                    Map::PlayerList const &players = pMap->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                    {
                        if(itr->getSource()->isAlive())
                        {
                            if(Creature* anomalie = me->SummonCreature(NPC_PLANAR_ANOMALIE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
                            {
                                anomalie->GetMotionMaster()->MoveFollow(itr->getSource(), 0, 0) ;
                                anomalieList.push_back(anomalie) ;
                            }
                        }
                    }
                }
                phaseTimer = 18000;
                ++phase;
            }

            if(castTimer<=diff)
            {
                if(barrage)
                {
                    DoCast(DUNGEON_MODE(SPELL_ARCANE_BARRAGE,H_SPELL_ARCANE_BARRAGE));
                    barrage = !barrage;
                }
                else
                {
                    DoCast(DUNGEON_MODE(SPELL_ARCANE_VOLLEY,H_SPELL_ARCANE_VOLLEY));
                    barrage = !barrage;
                }
                castTimer = 2000 ;
            } castTimer -= diff ;
        }
        else
        {
            if(phaseTimer < diff)
            {
                if(!anomalieList.empty())
                {
                    for(std::list<Creature*>::const_iterator itrA = anomalieList.begin() ; itrA != anomalieList.end() ; itrA++)
                    {
                        if((*itrA))
                            (*itrA)->DisappearAndDie();
                    }
                }
                anomalieList.clear() ;
                ++phase;
                Unit* target = SelectTarget(SELECT_TARGET_RANDOM) ;
                if(target)
                {
                    me->getThreatManager().clearReferences() ;
                    me->GetMotionMaster()->Clear() ;
                    me->AddThreat(target, 0.0f) ;
                    me->AI()->AttackStart(target) ;
                }
            } else phaseTimer -= diff;
        }
    }

        void JustDied(Unit* /*killer*/)
    {
        lSummons.DespawnAll();
        anomalieList.clear() ;
        if (pInstance)
            pInstance->SetData(DATA_EREGOS_EVENT, DONE);
    }
};

};

class npc_planar_anomalie : public CreatureScript
{
public:
    npc_planar_anomalie() : CreatureScript("npc_planar_anomalie") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_planar_anomalieAI (pCreature);
    }
struct  npc_planar_anomalieAI : public ScriptedAI
{
    npc_planar_anomalieAI(Creature *c) : ScriptedAI(c)
    {
    }

    uint32 checkTimer ;

    void Reset()
    {
        me->SetFlying(true);
        me->SetReactState(REACT_PASSIVE) ;
        DoCast(me, SPELL_PLANAR_DISTORSION, true) ;
        DoCast(me, SPELL_PLANAR_ANOMALIE_AGGRO, true) ;
        checkTimer = 1000 ;
    }

    void UpdateAI(const uint32 diff)
    {
        if(checkTimer <= diff)
        {
            Map* pMap = me->GetMap();
            if (pMap && pMap->IsDungeon())
            {
                Map::PlayerList const &players = pMap->GetPlayers();
                for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                {
                    if(itr->getSource() && itr->getSource()->isAlive())
                    {
                        if(me->IsWithinDist(itr->getSource(), 3))
                        {
                            DoCast(itr->getSource(),SPELL_PLANAR_BLAST, true) ;
                            me->DisappearAndDie();
                        }
                    }
                }
            }
            checkTimer = 1000 ;
        } else checkTimer -= diff ;
    }
};
};

void AddSC_boss_eregos()
{
    new boss_eregos();
    new npc_planar_anomalie();
}
