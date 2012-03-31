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
#include "naxxramas.h"

#define SPELL_MORTAL_WOUND      25646
#define SPELL_ENRAGE            RAID_MODE(28371,54427)
#define SPELL_DECIMATE          RAID_MODE(28374,54426)
#define SPELL_BERSERK           26662
#define SPELL_INFECTED_WOUND    29306

#define MOB_ZOMBIE  16360

const Position PosSummon[3] =
{
    {3267.9f, -3172.1f, 297.42f, 0.94f},
    {3253.2f, -3132.3f, 297.42f, 0},
    {3308.3f, -3185.8f, 297.42f, 1.58f},
};

enum Events
{
    EVENT_NONE,
    EVENT_WOUND,
    EVENT_ENRAGE,
    EVENT_DECIMATE,
    EVENT_BERSERK,
    EVENT_SUMMON,
};

#define EMOTE_NEARBY    " spots a nearby zombie to devour!"

class boss_gluth : public CreatureScript
{
public:
    boss_gluth() : CreatureScript("boss_gluth") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_gluthAI (pCreature);
    }

struct boss_gluthAI : public BossAI
{
    boss_gluthAI(Creature *c) : BossAI(c, BOSS_GLUTH)
    {
        // Do not let Gluth be affected by zombies' debuff
        me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_INFECTED_WOUND, true);
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (who->GetEntry() == MOB_ZOMBIE && me->IsWithinDistInMap(who, 7))
        {
            SetGazeOn(who);
            // TODO: use a script text
            me->MonsterTextEmote(EMOTE_NEARBY, 0, true);
        }
        else
            BossAI::MoveInLineOfSight(who);
    }

    void EnterCombat(Unit * /*who*/)
    {
        _EnterCombat();
        events.ScheduleEvent(EVENT_WOUND, 10000);
        events.ScheduleEvent(EVENT_ENRAGE, 15000);
        events.ScheduleEvent(EVENT_DECIMATE, 105000);
        events.ScheduleEvent(EVENT_BERSERK, 8*60000);
        events.ScheduleEvent(EVENT_SUMMON, 15000);
    }

    void JustSummoned(Creature *summon)
    {
        if (summon->GetEntry() == MOB_ZOMBIE)
            summon->AI()->AttackStart(me);
        summons.Summon(summon);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictimWithGaze() || !CheckInRoom())
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_WOUND:
                    DoCast(me->getVictim(), SPELL_MORTAL_WOUND);
                    events.ScheduleEvent(EVENT_WOUND, 10000);
                    break;
                case EVENT_ENRAGE:
                    // TODO : Add missing text
                    DoCast(me, SPELL_ENRAGE);
                    events.ScheduleEvent(EVENT_ENRAGE, 15000);
                    break;
                case EVENT_DECIMATE:
                    {         
                        DoCastAOE(SPELL_DECIMATE);
                        events.ScheduleEvent(EVENT_DECIMATE, 105000);
                        std::list<Creature*> ZombieList;
                        me->GetCreatureListWithEntryInGrid(ZombieList, MOB_ZOMBIE, 100.0f);
                        if (!ZombieList.empty())
                            for (std::list<Creature*>::iterator iter = ZombieList.begin(); iter != ZombieList.end(); iter++)
                            {
                                Creature* zombie = (*iter);
                                if (zombie)
                                    zombie->SetHealth(zombie->GetMaxHealth() * 5 /100);
                            }
                    }
                    break;
                case EVENT_BERSERK:
                    DoCast(me, SPELL_BERSERK);
                    events.ScheduleEvent(EVENT_BERSERK, 5*60000);
                    break;
                case EVENT_SUMMON:
                        for (int32 i = 0; i < RAID_MODE(1, 2); ++i)
                        DoSummon(MOB_ZOMBIE, PosSummon[rand()%3]);
                    events.ScheduleEvent(EVENT_SUMMON, 10000);
                    break;
            }
        }

        if (me->getVictim() && me->getVictim()->GetEntry() == MOB_ZOMBIE)
        {
            if (me->IsWithinMeleeRange(me->getVictim()))
            {
                me->Kill(me->getVictim());
                    me->ModifyHealth(int32(me->CountPctFromMaxHealth(5)));
            }
        }
        else
            DoMeleeAttackIfReady();
    }
};


};

/*
** mob_zombie_chows
*/
class mob_zombie_chows : public CreatureScript
{
public:
    mob_zombie_chows() : CreatureScript("mob_zombie_chows") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_zombie_chowsAI (pCreature);
    }
struct  mob_zombie_chowsAI : public ScriptedAI
{
    mob_zombie_chowsAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
    }

    void Reset()
    {
    }
    void JustDied(Unit* Killer) {}

    void DoMeleeAttackIfReady()
    {
        //If we are within range melee the target
        if (me->IsWithinDistInMap(me->getVictim(), ATTACK_DISTANCE))
        {
            //Make sure our attack is ready and we aren't currently casting
            if (me->isAttackReady() && !me->IsNonMeleeSpellCasted(false))
            {
                DoCast(me->getVictim(), SPELL_INFECTED_WOUND, true);
                me->AttackerStateUpdate(me->getVictim());
                me->resetAttackTimer();
            }
        }
    }

    void SpellHit(Unit* caster, const SpellEntry *spell)
    {
        if(spell->Id == SPELL_DECIMATE)
        {
            me->DeleteThreatList() ;
            me->GetMotionMaster()->MoveChase(caster) ;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};
};

/*
** npc_toxique
*/
class npc_toxique : public CreatureScript
{
public:
    npc_toxique() : CreatureScript("npc_toxique") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_toxiqueAI (pCreature);
    }
struct npc_toxiqueAI : public ScriptedAI
{
    npc_toxiqueAI(Creature *c) : ScriptedAI(c)
    {
    }

    uint32 CheckTimer;

    void Reset()
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE | UNIT_FLAG_PASSIVE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void UpdateAI(const uint32 diff)
    {
        if(CheckTimer)
        {
            Map* pMap = me->GetMap();
            Map::PlayerList const &PlayerList = pMap->GetPlayers();
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                {
                    if (i->getSource()->isAlive())
                    {
                        if(me->IsWithinDist(i->getSource(), 5.0f))
                        {
                            i->getSource()->AddAura(25812, i->getSource());
                        }
                    }
                }
        CheckTimer = 500;
        } else CheckTimer -= diff ;
    }
};
};

void AddSC_boss_gluth()
{
new boss_gluth();
    new mob_zombie_chows();
    new npc_toxique();
}
