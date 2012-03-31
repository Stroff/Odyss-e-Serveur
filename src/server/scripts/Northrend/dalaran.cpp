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

/* Script Data Start
SDName: Dalaran
SDAuthor: WarHead, MaXiMiUS
SD%Complete: 99%
SDComment: For what is 63990+63991? Same function but don't work correct...
SDCategory: Dalaran
Script Data End */

#include "ScriptPCH.h"

/*******************************************************
 * npc_mageguard_dalaran
 *******************************************************/

enum Spells
{
    SPELL_TRESPASSER_A = 54028,
    SPELL_TRESPASSER_H = 54029
};

enum NPCs // All outdoor guards are within 35.0f of these NPCs
{
    NPC_APPLEBOUGH_A = 29547,
    NPC_SWEETBERRY_H = 29715,
};

class npc_mageguard_dalaran : public CreatureScript
{
public:
    npc_mageguard_dalaran() : CreatureScript("npc_mageguard_dalaran") { }

struct npc_mageguard_dalaranAI : public Scripted_NoMovementAI
{
    npc_mageguard_dalaranAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pCreature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_NORMAL, true);
        pCreature->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);
    }

    void Reset(){}

    void EnterCombat(Unit* /*pWho*/){}

    void AttackStart(Unit* /*pWho*/){}

    void MoveInLineOfSight(Unit *pWho)
    {
        if (!pWho || !pWho->IsInWorld() || pWho->GetZoneId() != 4395)
            return;

        if (!me->IsWithinDist(pWho, 65.0f, false))
            return;

        Player *pPlayer = pWho->GetCharmerOrOwnerPlayerOrPlayerItself();

        if (!pPlayer || pPlayer->isGameMaster() || pPlayer->IsBeingTeleported() || pPlayer->HasAura(70972) || pPlayer->HasAura(70973))
            return;

        switch (me->GetEntry())
        {
            case 29254:
                if (pPlayer->GetTeam() == HORDE)              // Horde unit found in Alliance area
                    {
                    if (GetClosestCreatureWithEntry(me, NPC_APPLEBOUGH_A, 32.0f))
                    {
                        if (me->isInBackInMap(pWho, 12.0f))   // In my line of sight, "outdoors", and behind me
                            DoCast(pWho, SPELL_TRESPASSER_A); // Teleport the Horde unit out
                    }
                    else                                      // In my line of sight, and "indoors"
                        DoCast(pWho, SPELL_TRESPASSER_A);     // Teleport the Horde unit out
                    }
                break;
            case 29255:
                if (pPlayer->GetTeam() == ALLIANCE)           // Alliance unit found in Horde area
                    {
                    if (GetClosestCreatureWithEntry(me, NPC_SWEETBERRY_H, 32.0f))
                    {
                        if (me->isInBackInMap(pWho, 12.0f))   // In my line of sight, "outdoors", and behind me
                            DoCast(pWho, SPELL_TRESPASSER_H); // Teleport the Alliance unit out
                    }
                    else                                      // In my line of sight, and "indoors"
                        DoCast(pWho, SPELL_TRESPASSER_H);     // Teleport the Alliance unit out
                    }
                break;
        }
        me->SetOrientation(me->GetHomePosition().GetOrientation());
        return;
    }

    void UpdateAI(const uint32 /*diff*/){}
};

    CreatureAI *GetAI(Creature *creature) const
{
        return new npc_mageguard_dalaranAI(creature);
}
};

/*######
## npc_hira_snowdawn
######*/

enum eHiraSnowdawn
{
    SPELL_COLD_WEATHER_FLYING                   = 54197
};

#define GOSSIP_TEXT_TRAIN_HIRA "Je veux apprendre à monter une monture."

class npc_hira_snowdawn : public CreatureScript
{
public:
    npc_hira_snowdawn() : CreatureScript("npc_hira_snowdawn") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (!pCreature->isVendor() || !pCreature->isTrainer())
        return false;

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_TRAIN_HIRA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

    if (pPlayer->getLevel() >= 80 && pPlayer->HasSpell(SPELL_COLD_WEATHER_FLYING))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
        pPlayer->PlayerTalkClass->ClearMenus();
    if (uiAction == GOSSIP_ACTION_TRAIN)
        pPlayer->SEND_TRAINERLIST(pCreature->GetGUID());

    if (uiAction == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetGUID());

    return true;
}
};

/* Vargoth */
#define ITEM_SCHOOLS_OF_ARCANE_MAGIC        43824
#define ITEM_KIRIN_TOR_FAMILIAR                44738
#define SPELL_KIRIN_TOR_FAMILIAR            61472
#define GOSSIP_ITEM_KIRIN_TOR_FAMILIAR_1    "I have a book that might interest you. Would you like to take a look?"
#define GOSSIP_ITEM_KIRIN_TOR_FAMILIAR_2    "Thank you! I will be sure to notify you if I find anything else."

class npc_archmage_vargoth : public CreatureScript
{
public:
    npc_archmage_vargoth() : CreatureScript("npc_archmage_vargoth") { }

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->HasItemCount(ITEM_SCHOOLS_OF_ARCANE_MAGIC, 1, true) && !pPlayer->HasItemCount(ITEM_KIRIN_TOR_FAMILIAR, 1, true) && !pPlayer->HasSpell(SPELL_KIRIN_TOR_FAMILIAR) && pCreature->GetAreaId() == 4637 && pCreature->GetZoneId() == 4395)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KIRIN_TOR_FAMILIAR_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KIRIN_TOR_FAMILIAR_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        if(pPlayer->HasItemCount(ITEM_SCHOOLS_OF_ARCANE_MAGIC, 1, true) && !pPlayer->HasItemCount(ITEM_KIRIN_TOR_FAMILIAR, 1, true) && !pPlayer->HasSpell(SPELL_KIRIN_TOR_FAMILIAR))
        {
            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_KIRIN_TOR_FAMILIAR, 1, false);
            if (msg == EQUIP_ERR_OK)
            {
                pPlayer->StoreNewItem(dest, ITEM_KIRIN_TOR_FAMILIAR, 1, true);
                pPlayer->PlayerTalkClass->ClearMenus();
            }
        }
    }
    return true;
}
};

void AddSC_dalaran()
{
    new npc_mageguard_dalaran;
    new npc_hira_snowdawn;
    new npc_archmage_vargoth();
}