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

enum Creatures
{
    NPC_CENTRIFUGE_CORE                = 28183,
    NPC_AZURE_RING_CAPTAIN            = 28236,
    NPC_AZURE_RING_GUARDIAN            = 27638
};

enum Spells
{
    SPELL_ENERGIZE_CORES                          = 50785, //Damage 5938 to 6562, effec2 Triggers 54069, effect3 Triggers 56251
    SPELL_ENERGIZE_CORES_TRIGGER                = 54069,
    SPELL_ENERGIZE_CORES_TRIGGER_H            = 56251,
    SPELL_ENERGIZE_CORES_H                    = 59372, //Damage 9025 to 9975, effect2 Triggers 54069, effect 56251
    SPELL_CALL_AZURE_RING_CAPTAIN                 = 51002, //Effect    Send Event (12229)
    SPELL_CALL_AZURE_RING_CAPTAIN_2               = 51006, //Effect    Send Event (10665)
    SPELL_CALL_AZURE_RING_CAPTAIN_3               = 51007, //Effect    Send Event (18454)
    SPELL_CALL_AZURE_RING_CAPTAIN_4               = 51008, //Effect    Send Event (18455)
    SPELL_CALL_AMPLIFY_MAGIC                      = 51054,
    SPELL_CALL_AMPLIFY_MAGIC_H                = 59371,
    SPELL_ICE_BEAM                              = 49549,
    SPELL_ICE_BEAM_H                          = 59211,
};
//not in db
enum Yells
{
    SAY_AGGRO                                     = -1578022,
    SAY_KILL_1                                    = -1578023,
    SAY_KILL_2                                    = -1578024,
    SAY_DEATH                                     = -1578025,
    SAY_STRIKE_1                                  = -1578026,
    SAY_STRIKE_2                                  = -1578027,
    SAY_STRIKE_3                                  = -1578028,
    SAY_SPAWN                                     = -1578029
};

struct Locations
{
    float x, y, z;
};

static Locations CaptainLoc[4]=
{
    {1316.41, 1129.75, 470.21},
    {1319.71, 1128.13, 470.21},
    {1318.87, 1122.92, 470.21},
    {1315.15, 1127.64, 470.21}
};

class boss_varos : public CreatureScript
{
public:
    boss_varos() : CreatureScript("boss_varos") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_varosAI (pCreature);
    }

struct boss_varosAI : public ScriptedAI
{
    boss_varosAI(Creature *c) : ScriptedAI(c), lSummons(me)
    {
        pInstance = c->GetInstanceScript();
    }

    SummonList lSummons;
    uint32 energizeCoresTimer ;
    uint32 amplifyMagicTimer ;
    uint32 callCaptainTimer ;
    InstanceScript* pInstance;

    void Reset()
    {
        lSummons.DespawnAll();
        energizeCoresTimer = 14000 ;
        amplifyMagicTimer = 30000 ;
        callCaptainTimer = 20000 ;
        if (pInstance)
            pInstance->SetData(DATA_VAROS_EVENT, NOT_STARTED);
    }

    void EnterCombat(Unit* /*who*/)
    {
        DoScriptText(SAY_AGGRO, me);

        if (pInstance)
            pInstance->SetData(DATA_VAROS_EVENT, IN_PROGRESS);
    }

    void SpellHitTarget(Unit* pTarget, const SpellEntry* spell)
    {
        if(!pTarget)
            return ;
        if(spell->Id == SPELL_ENERGIZE_CORES_TRIGGER || spell->Id == SPELL_ENERGIZE_CORES_TRIGGER_H)
        {
            Map::PlayerList const &players = pInstance->instance->GetPlayers();
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
            {
                Player* pPlayer = itr->getSource();

                if (pPlayer && pPlayer->isAlive())
                {
                    if(pPlayer->IsInBetween(me, pTarget, 2.0f))
                    {
                        me->DealDamage(pPlayer, DUNGEON_MODE(5938+rand()%624, 7600+rand()%800), 0, SPELL_DIRECT_DAMAGE, SPELL_SCHOOL_MASK_ARCANE) ;
                    }
                }
            }
            return ;
        }
    }

        void AttackStart(Unit* /*who*/) {}
        void MoveInLineOfSight(Unit* /*who*/) {}
    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        if(energizeCoresTimer <= diff)
        {
            DoCast(DUNGEON_MODE(SPELL_ENERGIZE_CORES, SPELL_ENERGIZE_CORES_H));
            energizeCoresTimer = 30000 ;
        } else energizeCoresTimer -= diff ;

        if(amplifyMagicTimer <= diff)
        {
            if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                DoCast(target, DUNGEON_MODE(SPELL_CALL_AMPLIFY_MAGIC, SPELL_CALL_AMPLIFY_MAGIC_H));
            amplifyMagicTimer = 30000 ;
        } else amplifyMagicTimer ;

        if(callCaptainTimer <= diff)
        {
            int pos = rand()%4 ;
            if(Creature* captain = me->SummonCreature(NPC_AZURE_RING_CAPTAIN, CaptainLoc[pos].x, CaptainLoc[pos].y, CaptainLoc[pos].z, 0))
            {
                captain->SetReactState(REACT_PASSIVE) ;
                if(Creature* guardian = captain->FindNearestCreature(NPC_AZURE_RING_GUARDIAN, 40.0f))
                {
                    guardian->GetMotionMaster()->MovePoint(0,  CaptainLoc[pos].x, CaptainLoc[pos].y, CaptainLoc[pos].z) ;
                }
            }
            callCaptainTimer = 30000 ;
        } else callCaptainTimer -= diff ;

        DoMeleeAttackIfReady();
    }
    void JustDied(Unit* /*killer*/)
    {
        lSummons.DespawnAll();
        DoScriptText(SAY_DEATH, me);

        if (pInstance)
            pInstance->SetData(DATA_VAROS_EVENT, DONE);
    }
    void KilledUnit(Unit * victim)
    {
        if (victim == me)
            return;
        DoScriptText(RAND(SAY_KILL_1,SAY_KILL_2), me);
    }
    void JustSummoned(Creature *summon)
    {
        lSummons.Summon(summon);
    }
};

};

class npc_azure_ring_captain : public CreatureScript
{
public:
    npc_azure_ring_captain() : CreatureScript("npc_azure_ring_captain") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_azure_ring_captainAI (pCreature);
    }
struct npc_azure_ring_captainAI : public ScriptedAI
{
    npc_azure_ring_captainAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = c->GetInstanceScript();
    }

    InstanceScript* pInstance;
    uint32 iceBeamTimer ;

    void Reset()
    {
        iceBeamTimer = 5000 ;
    }

    void UpdateAI(const uint32 diff)
    {
        if(!me->IsMounted())
        {
            if(Creature* guardian = me->FindNearestCreature(NPC_AZURE_RING_GUARDIAN, 5.0f))
            {
                me->GetMotionMaster()->MoveJump(guardian->GetPositionX(), guardian->GetPositionY(), guardian->GetPositionZ(), 5.0f, 10.0f);
                me->Mount(NPC_AZURE_RING_GUARDIAN) ;
                guardian->ForcedDespawn(0) ;
                me->GetMotionMaster()->MoveRandom() ;
                me->SetFlying(true) ;
                me->SetReactState(REACT_PASSIVE) ;
            }
        }

        if(pInstance && pInstance->GetData(DATA_VAROS_EVENT) == IN_PROGRESS && me->IsMounted())
        {
            if(iceBeamTimer <= diff)
            {
                if(Creature* varos = Unit::GetCreature(*me, pInstance->GetData64(DATA_VAROS)))
                {
                    if(Unit* target = varos->AI()->SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    {
                        DoCast(target, DUNGEON_MODE(SPELL_ICE_BEAM, SPELL_ICE_BEAM_H)) ;
                    }
                }
                iceBeamTimer = 20000 ;
            } else iceBeamTimer -= diff ;
        }

        //Return since we have no target
        if (!UpdateVictim() && !me->IsNonMeleeSpellCasted(false))
            return;
    }
};

};

void AddSC_boss_varos()
{
    new boss_varos();
    new npc_azure_ring_captain();
}
