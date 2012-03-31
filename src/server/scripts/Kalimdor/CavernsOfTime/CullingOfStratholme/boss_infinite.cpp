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

/*
SQL:
UPDATE creature_template SET spell1=60588, spell2=60590, lootid=32773,  ScriptName="boss_infinite_corruptor" WHERE entry=32273;
delete from creature where guid in (250222, 250116);
INSERT INTO creature VALUES (250222,32273,595,2,1,0,0,2330.420,1393.477,129.142,2.751,300,0,0,175057,0,0,0);
INSERT INTO creature VALUES (250116,32281,595,2,1,0,0,2314.231,1400.733,128.252,5.996,300,0,0,5342,0,0,0);
UPDATE creature SET spawnMask=2 WHERE guid=250222;
UPDATE creature SET spawnMask=2 WHERE guid=250116;
DELETE FROM creature_loot_template WHERE entry = 32773;
REPLACE INTO creature_loot_template (entry, item, ChanceOrQuestChance, mincountOrRef, maxcount) VALUES
(32273, 43951, 100, 1, 1),
(32273, 43228, 16, 4, 4),
(32273, 33470, 5, 1, 27),
(32273, 43852, 3, 1, 1),
(32273, 35947, 1.1, 1, 1),
(32273, 33445, 0.5, 1, 1),
(32273, 33447, 0.3, 1, 1),
(32273, 36430, 0.2, 1, 1),
(32273, 33431, 0.2, 1, 1);
*/

#include "ScriptPCH.h"
#include "culling_of_stratholme.h"

enum Spells
{
    SPELL_CORRUPTING_BLIGHT                     = 60588,
    SPELL_VOID_STRIKE                           = 60590
};

enum NPCs
{
     NPC_TIME_RIFT                               = 28409
};

enum Yells
{
    SAY_AGGRO                                   = -1595045,
    SAY_FAIL                                    = -1595046,
    SAY_DEATH                                   = -1595047
};

const Position TimeRiftLocation = {2337.9, 1278.79, 132.885, 3.62904};

class boss_infinite_corruptor : public CreatureScript
{
public:
    boss_infinite_corruptor() : CreatureScript("boss_infinite_corruptor") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_infinite_corruptorAI(pCreature);
    }

    struct boss_infinite_corruptorAI : public ScriptedAI
    {
     Creature *GuardianOfTime;
     Creature *TimeRift;

        boss_infinite_corruptorAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
        }

        InstanceScript* pInstance;

    void Reset()
    {
          GuardianOfTime = Unit::GetCreature(*me, pInstance->GetData64(DATA_GUARDIAN_OF_TIME));
          TimeRift = me->SummonCreature(NPC_TIME_RIFT, TimeRiftLocation);

          if (pInstance)
                pInstance->SetData(DATA_INFINITE_EVENT, NOT_STARTED);
    }

        void EnterCombat(Unit* /*who*/)
        {
            if (pInstance)
                pInstance->SetData(DATA_INFINITE_EVENT, IN_PROGRESS);
        }

        void AttackStart(Unit* /*who*/) {}
        void MoveInLineOfSight(Unit* /*who*/) {}
        void UpdateAI(const uint32 /*diff*/)
    {
          if (pInstance->GetData(DATA_INFINITE_EVENT) == FAIL)
          {
               DoScriptText(SAY_FAIL, me);
               TimeRift->RemoveFromWorld();
               me->RemoveFromWorld();
               return;
          }

        //Return since we have no target
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

        void JustDied(Unit* /*killer*/)
    {
          DoScriptText(SAY_DEATH, me);
          TimeRift->RemoveFromWorld();

          if (pInstance)
          {
            pInstance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, me->GetEntry());
            pInstance->SetData(DATA_INFINITE_EVENT, DONE);
          }
    };

};
};

void AddSC_boss_infinite_corruptor()
{
    new boss_infinite_corruptor();
}
