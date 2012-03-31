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

#define SAY_AGGRO           RAND(-1533109,-1533110,-1533111)
#define SAY_SLAY            -1533112
#define SAY_TAUNT           RAND(-1533113,-1533114,-1533115,-1533116,-1533117)
#define SAY_DEATH           -1533118

#define SPELL_SPELL_DISRUPTION  29310
#define SPELL_DECREPIT_FEVER    RAID_MODE(29998,55011)
#define SPELL_PLAGUE_CLOUD      29350
#define ACHIEV_SAFETY_DANCE     RAID_MODE(1996,2139)

enum Events
{
    EVENT_NONE,
    EVENT_DISRUPT,
    EVENT_FEVER,
    EVENT_ERUPT,
    EVENT_PHASE,
};

enum Phases
{
    PHASE_FIGHT = 1,
    PHASE_DANCE,
};

// Anti-cheaters position check
#define CHECK_X             2821.88
#define CHECK_Y            -3684.89
#define CHECK_Z             273.62

class boss_heigan : public CreatureScript
{
public:
    boss_heigan() : CreatureScript("boss_heigan") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_heiganAI (pCreature);
    }

struct boss_heiganAI : public BossAI
{
    boss_heiganAI(Creature *c) : BossAI(c, BOSS_HEIGAN) {}

    uint32 eruptSection;
    bool eruptDirection;
    Phases phase;

        void KilledUnit(Unit* /*Victim*/)
    {
        if (!(rand()%5))
            DoScriptText(SAY_SLAY, me);
    }

        void JustDied(Unit* /*Killer*/)
    {
        _JustDied();
        DoScriptText(SAY_DEATH, me);

        // TODO: in caso di ress i player morti non devono essere contati vivi alla fine
        if (instance)
        {
            const Map::PlayerList &Players = instance->instance->GetPlayers();
            if (!Players.isEmpty())
            {
                Player *pPlayer;
                for (Map::PlayerList::const_iterator i = Players.begin(); i != Players.end(); ++i)
                    if ((pPlayer = i->getSource()) && !pPlayer->isAlive())
                        return;
                instance->DoCompleteAchievement(ACHIEV_SAFETY_DANCE);
            }
        }
    }

        void EnterCombat(Unit * /*who*/)
    {
        _EnterCombat();
        DoScriptText(SAY_AGGRO, me);
        EnterPhase(PHASE_FIGHT);
    }

    void EnterPhase(Phases newPhase)
    {
        phase = newPhase;
        events.Reset();
        eruptSection = 3;
        if (phase == PHASE_FIGHT)
        {
            me->SetReactState(REACT_AGGRESSIVE);
            events.ScheduleEvent(EVENT_DISRUPT, urand(10000, 25000));
            events.ScheduleEvent(EVENT_FEVER, urand(15000, 20000));
            events.ScheduleEvent(EVENT_PHASE, 90000);
            events.ScheduleEvent(EVENT_ERUPT, 15000);
        }
        else
        {
            float x, y, z, o;            
            me->SetReactState(REACT_PASSIVE);
            me->GetHomePosition(x, y, z, o);
            me->NearTeleportTo(x, y, z, o);
            DoCastAOE(SPELL_PLAGUE_CLOUD);
            events.ScheduleEvent(EVENT_PHASE, 45000);
            events.ScheduleEvent(EVENT_ERUPT, 7500);
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim() || !CheckInRoom())
            return;

        events.Update(diff);

        // Distance check
        if(me->GetDistance(CHECK_X, CHECK_Y, CHECK_Z) <= 4)
        {
            std::list<HostileReference*> &m_threatlist = me->getThreatManager().getThreatList();
            for (std::list<HostileReference*>::iterator itr = m_threatlist.begin(); itr != m_threatlist.end(); ++itr)
                if((*itr)->getTarget()->GetTypeId() == TYPEID_PLAYER)
                    (*itr)->getTarget()->NearTeleportTo(2793.86, -3707.38, 276.627, 0);
        }

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_DISRUPT:
                    DoCastAOE(SPELL_SPELL_DISRUPTION);
                    events.ScheduleEvent(EVENT_DISRUPT, urand(5000, 10000));
                    break;
                case EVENT_FEVER:
                    DoCastAOE(SPELL_DECREPIT_FEVER);
                    events.ScheduleEvent(EVENT_FEVER, urand(20000, 25000));
                    break;
                case EVENT_PHASE:
                    // TODO : Add missing texts for both phase switches
                    EnterPhase(phase == PHASE_FIGHT ? PHASE_DANCE : PHASE_FIGHT);
                    break;
                case EVENT_ERUPT:
                    instance->SetData(DATA_HEIGAN_ERUPT, eruptSection);
                    TeleportCheaters();

                    if (eruptSection == 0)
                        eruptDirection = true;
                    else if (eruptSection == 3)
                        eruptDirection = false;

                    eruptDirection ? ++eruptSection : --eruptSection;

                    events.ScheduleEvent(EVENT_ERUPT, phase == PHASE_FIGHT ? 10000 : 3350);
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }
};

};


void AddSC_boss_heigan()
{
    new boss_heigan();
}
