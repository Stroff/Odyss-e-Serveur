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
#include "BattlegroundAB.h"
#include "BattlegroundWS.h"

class achievement_has_orphan_out : public AchievementCriteriaScript
{
    public:
        achievement_has_orphan_out() : AchievementCriteriaScript("achievement_has_orphan_out") { }

        static uint32 const OrphanEntries[6];
        bool OnCheck(Player* source, Unit* /*target*/)
        {
            uint32 currentPet = GUID_ENPART(source->GetCritterGUID());
            for (uint8 i = 0; i < 6; ++i)
                if (currentPet == OrphanEntries[i])
                    return true;

            return false;
        }
};

uint32 const achievement_has_orphan_out::OrphanEntries[6] = {14305, 14444, 22818, 22817, 33533, 33532};

class achievement_storm_glory : public AchievementCriteriaScript
{
    public:
        achievement_storm_glory() : AchievementCriteriaScript("achievement_storm_glory") { }

        bool OnCheck(Player* source, Unit* /*target*/)
        {
            if (source->GetBattlegroundTypeId() != BATTLEGROUND_EY)
                return false;

            Battleground *pEotS = source->GetBattleground();
            if (!pEotS)
                return false;

            return pEotS->IsAllNodesConrolledByTeam(source->GetTeam());
        }
};

class achievement_resilient_victory : public AchievementCriteriaScript
{
    public:
        achievement_resilient_victory() : AchievementCriteriaScript("achievement_resilient_victory") { }

        bool OnCheck(Player* source, Unit* /*target*/)
        {
            Battleground* bg = source->GetBattleground();
            if (!bg)
                return false;

            if (bg->GetTypeID(true) != BATTLEGROUND_AB)
                return false;

            if (!static_cast<BattlegroundAB*>(bg)->IsTeamScores500Disadvantage(source->GetTeam()))
                return false;

            return true;
        }
};

class achievement_bg_control_all_nodes : public AchievementCriteriaScript
{
    public:
        achievement_bg_control_all_nodes() : AchievementCriteriaScript("achievement_bg_control_all_nodes") { }

        bool OnCheck(Player* source, Unit* /*target*/)
        {
            Battleground* bg = source->GetBattleground();
            if (!bg)
                return false;

            if (!bg->IsAllNodesConrolledByTeam(source->GetTeam()))
                return false;

            return true;
        }
};

class achievement_save_the_day : public AchievementCriteriaScript
{
    public:
        achievement_save_the_day() : AchievementCriteriaScript("achievement_save_the_day") { }

        bool OnCheck(Player* source, Unit* target)
        {
            if (!target)
                return false;

            if (Player const* pTarget = target->ToPlayer())
            {
                if (source->GetBattlegroundTypeId() != BATTLEGROUND_WS || !source->GetBattleground())
                    return false;

                BattlegroundWS* pWSG = static_cast<BattlegroundWS*>(source->GetBattleground());
                if (pWSG->GetFlagState(pTarget->GetTeam()) == BG_WS_FLAG_STATE_ON_BASE)
                    return true;
            }
            return false;
        }
};

void AddSC_achievement_scripts()
{
    new achievement_has_orphan_out();
    new achievement_storm_glory();
    new achievement_resilient_victory();
    new achievement_bg_control_all_nodes();
    new achievement_save_the_day();
}
