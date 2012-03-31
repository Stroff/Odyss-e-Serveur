/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: Felwood
SD%Complete: 95
SDComment: Quest support: 4101, 4102
SDCategory: Felwood
EndScriptData */

/* ContentData
npcs_riverbreeze_and_silversky
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedFollowerAI.h"

/*######
## npcs_riverbreeze_and_silversky
######*/

#define GOSSIP_ITEM_BEACON  "Please make me a Cenarion Beacon"

class npcs_riverbreeze_and_silversky : public CreatureScript
{
public:
    npcs_riverbreeze_and_silversky() : CreatureScript("npcs_riverbreeze_and_silversky") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->CastSpell(pPlayer, 15120, false);
        }
        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    uint32 eCreature = pCreature->GetEntry();

    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (eCreature == 9528)
    {
        if (pPlayer->GetQuestRewardStatus(4101))
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BEACON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(2848, pCreature->GetGUID());
        } else if (pPlayer->GetTeam() == HORDE)
        pPlayer->SEND_GOSSIP_MENU(2845, pCreature->GetGUID());
        else
            pPlayer->SEND_GOSSIP_MENU(2844, pCreature->GetGUID());
    }

    if (eCreature == 9529)
    {
        if (pPlayer->GetQuestRewardStatus(4102))
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BEACON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(2849, pCreature->GetGUID());
        } else if (pPlayer->GetTeam() == ALLIANCE)
        pPlayer->SEND_GOSSIP_MENU(2843, pCreature->GetGUID());
        else
            pPlayer->SEND_GOSSIP_MENU(2842, pCreature->GetGUID());
    }

    return true;
}
};
/*####
# npc_kitten
####*/

enum Kitten
{
    EMOTE_SAB_JUMP              = -1000541,
    EMOTE_SAB_FOLLOW            = -1000542,

    SPELL_CORRUPT_SABER_VISUAL  = 16510,

    QUEST_CORRUPT_SABER         = 4506,
    NPC_WINNA                   = 9996,
    NPC_CORRUPT_SABER           = 10042
};

#define GOSSIP_ITEM_RELEASE     "I want to release the corrupted saber to Winna."

class npc_kitten : public CreatureScript
{
public:
    npc_kitten() : CreatureScript("npc_kitten") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_kittenAI (pCreature);
    }
    struct npc_kittenAI : public FollowerAI
    {
        npc_kittenAI(Creature* pCreature) : FollowerAI(pCreature)
        {
            if (pCreature->GetOwner() && pCreature->GetOwner()->GetTypeId() == TYPEID_PLAYER)
            {
                StartFollow((Player*)pCreature->GetOwner());
                SetFollowPaused(true);
                DoScriptText(EMOTE_SAB_JUMP, me);

                pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                //find a decent way to move to center of moonwell
            }

            m_uiMoonwellCooldown = 7500;
        }

        uint32 m_uiMoonwellCooldown;

        void Reset() { }

        void MoveInLineOfSight(Unit* pWho)
        {
            //should not have npcflag by default, so set when expected
            if (!me->getVictim() && !me->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP) && HasFollowState(STATE_FOLLOW_INPROGRESS) && pWho->GetEntry() == NPC_WINNA)
            {
                if (me->IsWithinDistInMap(pWho, INTERACTION_DISTANCE))
                    me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            }
        }

        void UpdateFollowerAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
            {
                if (HasFollowState(STATE_FOLLOW_PAUSED))
                {
                    if (m_uiMoonwellCooldown < uiDiff)
                    {
                        me->CastSpell(me, SPELL_CORRUPT_SABER_VISUAL, false);
                        SetFollowPaused(false);
                    }
                    else
                        m_uiMoonwellCooldown -= uiDiff;
                }

                return;
            }

            DoMeleeAttackIfReady();
        }
    };

    bool EffectDummyCreature(Unit *caster, uint32 uiSpellId, uint32 uiEffIndex, Creature *pCreatureTarget)
    {
        //always check spellid and effectindex
        if (uiSpellId == SPELL_CORRUPT_SABER_VISUAL && uiEffIndex == 0)
        {
            // Not nice way, however using UpdateEntry will not be correct.
            if (const CreatureInfo* pTemp = ObjectMgr::GetCreatureTemplate(NPC_CORRUPT_SABER))
            {
                pCreatureTarget->SetEntry(pTemp->Entry);
                pCreatureTarget->SetDisplayId(pTemp->Modelid1);
                pCreatureTarget->SetName(pTemp->Name);
                pCreatureTarget->SetFloatValue(OBJECT_FIELD_SCALE_X, pTemp->scale);
            }

            if (Unit* pOwner = pCreatureTarget->GetOwner())
                DoScriptText(EMOTE_SAB_FOLLOW, pCreatureTarget, pOwner);

            //always return true when we are handling this spell and effect
            return true;
        }
        return false;
    }
};

class npc_corrupt_saber : public CreatureScript
{
public:
    npc_corrupt_saber() : CreatureScript("npc_corrupt_saber") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_corrupt_saberAI (pCreature);
    }

struct npc_corrupt_saberAI : public ScriptedAI
{
npc_corrupt_saberAI( Creature *c) : ScriptedAI(c){}

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_CORRUPT_SABER) == QUEST_STATUS_INCOMPLETE)
    {
        if (GetClosestCreatureWithEntry(pCreature, NPC_WINNA, INTERACTION_DISTANCE))
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RELEASE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        if (npc_kitten::npc_kittenAI* pKittenAI = dynamic_cast<npc_kitten::npc_kittenAI*>(pCreature->AI()))
            pKittenAI->SetFollowComplete();

        pPlayer->AreaExploredOrEventHappens(QUEST_CORRUPT_SABER);
    }

    return true;
}
};
};

/*######
## npc_niby_the_almighty (summons el pollo grande)
######*/
enum nibyTheAlmighty
{
    QUEST_KROSHIUS     = 7603,

    NPC_IMPSY          = 14470,

    SPELL_SUMMON_POLLO = 23056,

    SAY_NIBY_1         = -1000566,
    SAY_NIBY_2         = -1000567,
    EMOTE_IMPSY_1      = -1000568,
    SAY_IMPSY_1        = -1000569,
    SAY_NIBY_3         = -1000570
};

class npc_niby_the_almighty : public CreatureScript
{
public:
    npc_niby_the_almighty() : CreatureScript("npc_niby_the_almighty") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_niby_the_almightyAI (pCreature);
    }

struct npc_niby_the_almightyAI : public ScriptedAI
{
    npc_niby_the_almightyAI(Creature* pCreature) : ScriptedAI(pCreature){}

    uint32 m_uiSummonTimer;
    uint8  m_uiSpeech;

    bool m_bEventStarted;

    void Reset()
    {
        m_uiSummonTimer = 500;
        m_uiSpeech = 0;

        m_bEventStarted = false;
    }

    void StartEvent()
    {
        Reset();
        m_bEventStarted = true;
        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bEventStarted)
        {
            if (m_uiSummonTimer <= uiDiff)
            {
                switch (m_uiSpeech)
                {
                    case 1:
                        me->GetMotionMaster()->Clear();
                        me->GetMotionMaster()->MovePoint(0, 5407.19f, -753.00f, 350.82f);
                        m_uiSummonTimer = 6200;
                        break;
                    case 2:
                        me->SetOrientation(1.2f);
                        DoScriptText(SAY_NIBY_1, me);
                        m_uiSummonTimer = 3000;
                        break;
                    case 3:
                        DoScriptText(SAY_NIBY_2, me);
                        DoCast(me, SPELL_SUMMON_POLLO);
                        m_uiSummonTimer = 2000;
                        break;
                    case 4:
                        if (Creature* pImpsy = GetClosestCreatureWithEntry(me, NPC_IMPSY, 20.0))
                        {
                            DoScriptText(EMOTE_IMPSY_1, pImpsy);
                            DoScriptText(SAY_IMPSY_1, pImpsy);
                            m_uiSummonTimer = 2500;
                        }
                        else
                        {
                            //Skip Speech 5
                            m_uiSummonTimer = 40000;
                            ++m_uiSpeech;
                        }
                        break;
                    case 5:
                        DoScriptText(SAY_NIBY_3, me);
                        m_uiSummonTimer = 40000;
                        break;
                    case 6:
                        me->GetMotionMaster()->MoveTargetedHome();
                        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        m_bEventStarted = false;
                }
                ++m_uiSpeech;
            }
            else
                m_uiSummonTimer -= uiDiff;
        }
        else
            if(!UpdateVictim())
                return ;
    }
};

bool ChooseReward(Player* pPlayer, Creature* pCreature, const Quest* pQuest, uint32 slot)
{
    if (pQuest->GetQuestId() == QUEST_KROSHIUS)
    {
        if (npc_niby_the_almightyAI* pNibyAI = CAST_AI(npc_niby_the_almightyAI, pCreature->AI()))
        {
            pNibyAI->StartEvent();
        }
    }
    return true;
}
};

void AddSC_felwood()
{
    new npcs_riverbreeze_and_silversky();
    new npc_kitten();
    new npc_corrupt_saber();
    new npc_niby_the_almighty();
}
