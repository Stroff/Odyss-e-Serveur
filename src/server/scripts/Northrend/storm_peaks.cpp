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
#include "ScriptedEscortAI.h"

/*######
## npc_agnetta_tyrsdottar
######*/

#define SAY_AGGRO                  -1571003
#define GOSSIP_AGNETTA             "Skip the warmup, sister... or are you too scared to face soemeone your own size?"
#define GOSSIP_ITEM_1              "Je suis pr�t(e), sortons d'ici."

enum eAgnetta
{
    QUEST_ITS_THAT_YOUR_GOBLIN      = 12969,
    FACTION_HOSTILE_AT1             = 45
};

class npc_agnetta_tyrsdottar : public CreatureScript
{
public:
    npc_agnetta_tyrsdottar() : CreatureScript("npc_agnetta_tyrsdottar") { }

    struct npc_agnetta_tyrsdottarAI : public ScriptedAI
    {
        npc_agnetta_tyrsdottarAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        void Reset()
        {
            me->RestoreFaction();
        }
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_agnetta_tyrsdottarAI(creature);
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->GetQuestStatus(QUEST_ITS_THAT_YOUR_GOBLIN) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_AGNETTA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        pPlayer->SEND_GOSSIP_MENU(13691, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            DoScriptText(SAY_AGGRO, pCreature);
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->setFaction(FACTION_HOSTILE_AT1);
            pCreature->AI()->AttackStart(pPlayer);
        }

        return true;
    }
};

/*######
## npc_frostborn_scout
######*/

#define GOSSIP_ITEM1    "Are you okay? I've come to take you back to Frosthold if you can stand."
#define GOSSIP_ITEM2    "I'm sorry that I didn't get here sooner. What happened?"
#define GOSSIP_ITEM3    "I'll go get some help. Hang in there."

enum eFrostbornScout
{
    QUEST_MISSING_SCOUTS  =  12864
};

class npc_frostborn_scout : public CreatureScript
{
public:
    npc_frostborn_scout() : CreatureScript("npc_frostborn_scout") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->GetQuestStatus(QUEST_MISSING_SCOUTS) == QUEST_STATUS_INCOMPLETE)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->PlayerTalkClass->SendGossipMenu(13611, pCreature->GetGUID());
        }

        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
            pPlayer->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->PlayerTalkClass->SendGossipMenu(13612, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->PlayerTalkClass->SendGossipMenu(13613, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->PlayerTalkClass->SendGossipMenu(13614, pCreature->GetGUID());
            pPlayer->AreaExploredOrEventHappens(QUEST_MISSING_SCOUTS);
            break;
        }

        return true;
    }
};

/*######
## npc_thorim
######*/

#define GOSSIP_HN "Thorim?"
#define GOSSIP_SN1 "Can you tell me what became of Sif?"
#define GOSSIP_SN2 "He did more than that, Thorim. He controls Ulduar now."
#define GOSSIP_SN3 "It needn't end this way."

enum eThorim
{
    QUEST_SIBLING_RIVALRY = 13064,
    NPC_THORIM = 29445,
    GOSSIP_TEXTID_THORIM1 = 13799,
    GOSSIP_TEXTID_THORIM2 = 13801,
    GOSSIP_TEXTID_THORIM3 = 13802,
    GOSSIP_TEXTID_THORIM4 = 13803
};

class npc_thorim : public CreatureScript
{
public:
    npc_thorim() : CreatureScript("npc_thorim") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        if (pPlayer->GetQuestStatus(QUEST_SIBLING_RIVALRY) == QUEST_STATUS_INCOMPLETE) {
            pPlayer->ADD_GOSSIP_ITEM(0, GOSSIP_HN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM1, pCreature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->ADD_GOSSIP_ITEM(0, GOSSIP_SN1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM2, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                pPlayer->ADD_GOSSIP_ITEM(0, GOSSIP_SN2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM3, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                pPlayer->ADD_GOSSIP_ITEM(0, GOSSIP_SN3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_THORIM4, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->CompleteQuest(QUEST_SIBLING_RIVALRY);
                break;
        }
        return true;
    }
};

/*######
## npc_goblin_prisoner
######*/

enum eGoblinPrisoner
{
    GO_RUSTY_CAGE = 191544
};

class npc_goblin_prisoner : public CreatureScript
{
public:
    npc_goblin_prisoner() : CreatureScript("npc_goblin_prisoner") { }

    struct npc_goblin_prisonerAI : public ScriptedAI
    {
        npc_goblin_prisonerAI(Creature* pCreature) : ScriptedAI (pCreature){}

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);

            if (GameObject* pGO = me->FindNearestGameObject(GO_RUSTY_CAGE,5.0f))
            {
                if (pGO->GetGoState() == GO_STATE_ACTIVE)
                    pGO->SetGoState(GO_STATE_READY);
            }
        }

    };

    CreatureAI *GetAI(Creature *creature) const
    { 
        return new npc_goblin_prisonerAI(creature);
    }
};

/*######
## npc_victorious_challenger
######*/

#define GOSSIP_CHALLENGER            "Let's do this, sister."

enum eVictoriousChallenger
{
    QUEST_TAKING_ALL_CHALLENGERS    = 12971,
    QUEST_DEFENDING_YOUR_TITLE      = 13423,

    SPELL_SUNDER_ARMOR              = 11971,
    SPELL_REND_VC                   = 11977
};

class npc_victorious_challenger : public CreatureScript
{
public:
    npc_victorious_challenger() : CreatureScript("npc_victorious_challenger") { }

    struct npc_victorious_challengerAI : public ScriptedAI
    {
        npc_victorious_challengerAI(Creature* pCreature) : ScriptedAI(pCreature) {}

        uint32 SunderArmorTimer;
        uint32 RendTimer;

        void Reset()
        {
            me->RestoreFaction();

            SunderArmorTimer = 10000;
            RendTimer        = 15000;
        }

        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;

            if (RendTimer < diff)
            {
                DoCast(me->getVictim(), SPELL_REND_VC, true);
                RendTimer = 15000;
            }else RendTimer -= diff;

            if (SunderArmorTimer < diff)
            {
                DoCast(me->getVictim(), SPELL_SUNDER_ARMOR, true);
                SunderArmorTimer = 10000;
            }else SunderArmorTimer -= diff;

            DoMeleeAttackIfReady();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            me->RestoreFaction();
        }

    };

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        if (pPlayer->GetQuestStatus(QUEST_TAKING_ALL_CHALLENGERS) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(QUEST_DEFENDING_YOUR_TITLE) == QUEST_STATUS_INCOMPLETE)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_CHALLENGER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
            return true;
        }

        return false;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
            pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->setFaction(14);
            pCreature->AI()->AttackStart(pPlayer);
        }

        return true;
    }

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_victorious_challengerAI(creature);
    }
};

/*######
## npc_loklira_crone
######*/

#define GOSSIP_LOKLIRACRONE     "Tell me about this proposal"
#define GOSSIP_LOKLIRACRONE1    "What happened then?"
#define GOSSIP_LOKLIRACRONE2    "You want me to take part in the Hyldsmeet to end the war?"
#define GOSSIP_LOKLIRACRONE3    "Very well. I'll take part in this competition."

enum eLokliraCrone
{
    QUEST_HYLDSMEET     = 12970,

    GOSSIP_TEXTID_LOK1  = 13778,
    GOSSIP_TEXTID_LOK2  = 13779,
    GOSSIP_TEXTID_LOK3  = 13780
};

class npc_loklira_crone : public CreatureScript
{
public:
    npc_loklira_crone() : CreatureScript("npc_loklira_crone") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        if (pPlayer->GetQuestStatus(QUEST_HYLDSMEET) == QUEST_STATUS_INCOMPLETE)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOKLIRACRONE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
            return true;
        }
        return false;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
            pPlayer->PlayerTalkClass->ClearMenus();
        switch (uiAction)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOKLIRACRONE1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOK1, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOKLIRACRONE2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOK2, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LOKLIRACRONE3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
                pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LOK3, pCreature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                pPlayer->CLOSE_GOSSIP_MENU();
                pPlayer->CompleteQuest(QUEST_HYLDSMEET);
                break;
        }
        return true;
    }
};

/////////////////////
///npc_injured_goblin
/////////////////////

enum eInjuredGoblin
{
    QUEST_BITTER_DEPARTURE     = 12832,
    SAY_QUEST_ACCEPT           =  -1800042,
    SAY_END_WP_REACHED         =  -1800043
};

class npc_injured_goblin : public CreatureScript
{
public:
    npc_injured_goblin() : CreatureScript("npc_injured_goblin") { }

    struct npc_injured_goblinAI : public npc_escortAI
    {
        npc_injured_goblinAI(Creature* pCreature) : npc_escortAI(pCreature) { }

        void WaypointReached(uint32 i)
        {
            Player* pPlayer = GetPlayerForEscort();
            switch (i)
            {
            case 26:
                DoScriptText(SAY_END_WP_REACHED, me, pPlayer);
                break;
            case 27:
                if (pPlayer)
                    pPlayer->GroupEventHappens(QUEST_BITTER_DEPARTURE, me);
                break;
            }
        }

        void EnterCombat(Unit* /*pWho*/) {}

        void Reset() {}

        void JustDied(Unit* /*pKiller*/)
        {
            Player* pPlayer = GetPlayerForEscort();
            if (HasEscortState(STATE_ESCORT_ESCORTING) && pPlayer)
                pPlayer->FailQuest(QUEST_BITTER_DEPARTURE);
        }

       void UpdateAI(const uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);
            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_injured_goblinAI(creature);
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        if (pPlayer->GetQuestStatus(QUEST_BITTER_DEPARTURE) == QUEST_STATUS_INCOMPLETE)
        {
            pPlayer->ADD_GOSSIP_ITEM(0, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->PlayerTalkClass->SendGossipMenu(9999999, pCreature->GetGUID());
        }
        else
            pPlayer->SEND_GOSSIP_MENU(999999, pCreature->GetGUID());
        return true;
    }

    bool OnQuestAccept(Player* /*pPlayer*/, Creature* pCreature, Quest const *quest)
    {
        if (quest->GetQuestId() == QUEST_BITTER_DEPARTURE)
            DoScriptText(SAY_QUEST_ACCEPT, pCreature);

        return false;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        npc_escortAI* pEscortAI = CAST_AI(npc_injured_goblin::npc_injured_goblinAI, pCreature->AI());

        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            pEscortAI->Start(true, true, pPlayer->GetGUID());
            pCreature->setFaction(113);
        }
        return true;
    }
};
/*########################
## mobs_exhausted_vrykul #
##########################*/

enum eEnums 
{
    FACTION_FRIENDLY       = 35,
    FACTION_HOSTILE        = 14,
    QUEST_DISCIPLINE       = 12906,
    QUEST_MAINTAINING_DISCIPLINE       = 13422,
    ENTRY_EXHAUSTED_VRYKUL = 30146,
    ENTRY_EXHAUSTED_VRYKUL_CREDIT = 29886,
    SPELL_DESPERATE_BLOW   = 57395,
    SPELL_DISCIPLINING_ROD = 56033
};

class mob_exhausted_vrykul : public CreatureScript
{
public:
    mob_exhausted_vrykul() : CreatureScript("mob_exhausted_vrykul") { }

    struct  mob_exhausted_vrykulAI : public ScriptedAI
    {
        mob_exhausted_vrykulAI(Creature *c) : ScriptedAI(c) {}

        bool isDisciplined,isDesperate;

        void Reset() 
        { 
            me->RestoreFaction();
            me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE);
            me->SetStandState(UNIT_STAND_STATE_STAND);
            isDisciplined = false,isDesperate = false;
        }

        void SpellHit(Unit *caster, const SpellEntry *spell)
        {
            if(caster->GetTypeId() == TYPEID_PLAYER)
            {
                if(!isDisciplined && spell->Id == SPELL_DISCIPLINING_ROD)
                {
                    if(CAST_PLR(caster)->GetQuestStatus(QUEST_DISCIPLINE) == QUEST_STATUS_INCOMPLETE || CAST_PLR(caster)->GetQuestStatus(QUEST_MAINTAINING_DISCIPLINE) == QUEST_STATUS_INCOMPLETE)
                    {
                        switch(rand()%2)
                        {
                        case 0 :
                            me->setFaction(FACTION_FRIENDLY);
                            CAST_PLR(caster)->KilledMonsterCredit(ENTRY_EXHAUSTED_VRYKUL_CREDIT,me->GetGUID());
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            isDisciplined = true;
                            me->ForcedDespawn(15000) ;
                            break ;
                        case 1 :
                            me->setFaction(FACTION_HOSTILE);
                            AttackStart(caster);
                            break ;
                        }
                    }
                }
            }
        }
        void UpdateAI(const uint32 diff)
        {
            if(!UpdateVictim())
                return ;

            if(!isDisciplined && me->GetHealth()*100 < me->GetMaxHealth()*20 && !isDesperate)
            {
                DoCast(SPELL_DESPERATE_BLOW);
                isDesperate = true;
            }

            DoMeleeAttackIfReady();
        }

    };

    CreatureAI* GetAI(Creature* pCreature)
    {
        return new mob_exhausted_vrykulAI (pCreature);
    }
};

/* Memories of Stormhoof */
#define QUEST_MEMORIES_OF_STORMHOOF        13037
#define GOSSIF_MEMORIES                    "Ask Chieftain Swiftspear about his memories"
class npc_chieftain_swiftspear : public CreatureScript
{
public:
    npc_chieftain_swiftspear() : CreatureScript("npc_chieftain_swiftspear") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        if (pPlayer->GetQuestStatus(QUEST_MEMORIES_OF_STORMHOOF) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIF_MEMORIES, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction )
    {
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->KilledMonsterCredit(30381, 0) ;
        }

        return true;
    }
};
enum GoblinChisel
{
    GO_STONE_BLOCK            = 194461,
    GO_SMALL_STONE_BLOCK    = 194463
};

class npc_goblin_chisel : public CreatureScript
{
public:
    npc_goblin_chisel() : CreatureScript("npc_goblin_chisel") { }

    struct npc_goblin_chiselAI : public ScriptedAI
    {
        npc_goblin_chiselAI(Creature* pCreature) : ScriptedAI(pCreature) {}

        uint32 explosionTimer;

        void Reset()
        {
            explosionTimer = 3000 ;
        }

        void UpdateAI(const uint32 diff)
        {
            if (explosionTimer <= diff)
            {
                if (GameObject* stoneBlock = me->FindNearestGameObject(GO_STONE_BLOCK, 5.0f))
                {
                    stoneBlock->SetGoState(GO_STATE_ACTIVE) ;
                    for(uint32 i = 0 ; i<= urand(1, 4) ; i++)
                        me->SummonGameObject(GO_SMALL_STONE_BLOCK, stoneBlock->GetPositionX()+urand(0, 5), stoneBlock->GetPositionY()+urand(0, 5), stoneBlock->GetPositionZ(), 0, 0, 0, 0, 0, 0) ;
                    me->DealDamage(me, me->GetHealth()) ;
                }
            } else explosionTimer -= diff ;
            //Return since we have no target
            if (!UpdateVictim())
                return;
        }
    };

    CreatureAI* GetAI(Creature* pCreature)
    {
        return new npc_goblin_chiselAI (pCreature);
    }
};

/////////////////////
///npc_ranshalla
/////////////////////

enum eRanshalla
{
    DEBUT_BITTER_DEPARTURE        = 4901,
    VALIDE_QUEST_ACCEPT           =  -2000000,
    VALIDE_END_WP_REACHED         =  -2000001
};



class npc_ranshalla : public CreatureScript
{
public:
    npc_ranshalla() : CreatureScript("npc_ranshalla") { }

    struct npc_ranshallaAI : public npc_escortAI
    {
        npc_ranshallaAI(Creature* pCreature) : npc_escortAI(pCreature) { }

        void WaypointReached(uint32 i)
        {
            Player* pPlayer = GetPlayerForEscort();
            switch (i)
            {
            case 4:
                DoScriptText(VALIDE_END_WP_REACHED, me, pPlayer);
                break;
            case 5:
                if (pPlayer)
                    pPlayer->GroupEventHappens(DEBUT_BITTER_DEPARTURE, me);
                break;
            }
        }

        void EnterCombat(Unit* /*pWho*/) {}

        void Reset() {}

        void JustDied(Unit* /*pKiller*/)
        {
            Player* pPlayer = GetPlayerForEscort();
            if (HasEscortState(STATE_ESCORT_ESCORTING) && pPlayer)
                pPlayer->FailQuest(DEBUT_BITTER_DEPARTURE);
        }

       void UpdateAI(const uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);
            if (!UpdateVictim())
                return;
            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature)
    {
        return new npc_ranshallaAI(pCreature);
    }
};

/*######
## Fix Quest: "Cold Hearted" (12856) http://www.wowhead.com/quest=12856
######*/

enum eCaptiveProtodrake
{
    QUEST_COLD_HEARTED                = 12856,
    ENTRY_FREED_PROTODRAKE            = 29709,
    SPELL_RIDE_FREED_DRAKE            = 55029
};

class npc_captive_protodrake : public CreatureScript
{
public:
    npc_captive_protodrake() : CreatureScript("npc_captive_protodrake") {}

    struct npc_captive_protodrakeAI : public ScriptedAI
    {
        npc_captive_protodrakeAI(Creature* pCreature) : ScriptedAI(pCreature) {}

        void Reset()
        {
            me->SetVisible(true);
        }

        void PassengerBoarded(Unit* pWho, int8 /*seatId*/, bool apply) 
        {
            if (pWho->GetTypeId() != TYPEID_PLAYER)
                return;

            if (pWho && apply)
            {
                if (pWho->ToPlayer()->GetQuestStatus(QUEST_COLD_HEARTED) == QUEST_STATUS_INCOMPLETE)
                {
                    pWho->ExitVehicle();
                    Creature* pFreed = pWho->SummonCreature(ENTRY_FREED_PROTODRAKE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                    if (pFreed && pFreed->IsVehicle())
                    {
                        pWho->RemoveAurasDueToSpell(45472);  //remove parachute
                        pWho->CastSpell(pFreed, SPELL_RIDE_FREED_DRAKE, true);
                        pFreed->SetFlying(true);  //should not be here
                        pFreed->SetSpeed(MOVE_FLIGHT, 3.0f);
                        me->SetVisible(false);
                        me->Kill(me);
                    }
                }
            }
        }

    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_captive_protodrakeAI(creature);
    }
};

enum eFreedProtodrake
{
    ENTRY_LIBERATED_BRUNNHILDAR         = 29734
};

const Position FreedDrakeWaypoints[6] =
{
    {7250.15f, -2327.22f, 869.03f, 0.0f},
    {7118.79f, -2122.05f, 841.32f, 0.0f},
    {7052.86f, -1905.99f, 888.59f, 0.0f},
    {7038.24f, -1822.77f, 857.94f, 0.0f},
    {7044.09f, -1792.25f, 841.69f, 0.0f},
    {7071.20f, -1780.73f, 822.42f, 0.0f}
};

class npc_freed_protodrake : public CreatureScript
{
public:
    npc_freed_protodrake() : CreatureScript("npc_freed_protodrake") { }

    struct npc_freed_protodrakeAI : public ScriptedAI
    {
        npc_freed_protodrakeAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        uint8 count;
        bool wp_reached;
        bool movementStarted;

        void Reset()
        {
            count = 0;
            wp_reached = false;
            movementStarted = false;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE || id != count)
                return;

            if (id < 5)
            {
                ++count;
                wp_reached = true;
            }
            else //reached village, give credits
            {
                Unit* pPlayer = me->GetVehicleKit()->GetPassenger(0); //get player
                if (pPlayer && pPlayer->GetTypeId() == TYPEID_PLAYER)
                {
                    for (uint8 i = 1; i < 4; ++i) //try to get prisoners
                        if (Unit* pPrisoner = me->GetVehicleKit()->GetPassenger(i))
                        { 
                            pPlayer->ToPlayer()->KilledMonsterCredit(ENTRY_LIBERATED_BRUNNHILDAR, 0);
                            pPrisoner->ExitVehicle();
                        }
                    pPlayer->ToPlayer()->KilledMonsterCredit(ENTRY_FREED_PROTODRAKE, 0);
                    pPlayer->ExitVehicle();
                }

                me->SetVisible(false);
                me->ForcedDespawn(1000);
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!me->isCharmed() && !movementStarted)
            {
                movementStarted = true;
                wp_reached = true;
            }

            if (wp_reached)
            {
                wp_reached = false;
                me->GetMotionMaster()->MovePoint(count, FreedDrakeWaypoints[count]);
            }
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_freed_protodrakeAI(pCreature);
    }
};

enum eBrunnhildarPrisoner
{
    SPELL_ICE_BLOCK                   = 45776,   //wrong id
    SPELL_ICE_SHARD                   = 55046,
    SPELL_ICE_SHARD_IMPACT            = 55047
};

class npc_brunnhildar_prisoner : public CreatureScript
{
public:
    npc_brunnhildar_prisoner() : CreatureScript("npc_brunnhildar_prisoner") {}

    struct npc_brunnhildar_prisonerAI : public ScriptedAI
    {
        npc_brunnhildar_prisonerAI(Creature* pCreature) : ScriptedAI(pCreature) {}

        uint32 uiCheckTimer;

        void Reset()
        {
            uiCheckTimer = 10000;
            me->CastSpell(me, SPELL_ICE_BLOCK, true);
        }

        void SpellHit(Unit *pCaster, const SpellEntry *spell) 
        {
            if (spell->Id == SPELL_ICE_SHARD)
            {
                me->CastSpell(me, SPELL_ICE_SHARD_IMPACT, true);

                if (pCaster->IsVehicle())
                {
                    me->RemoveAurasDueToSpell(SPELL_ICE_BLOCK);
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (uiCheckTimer < diff)
            {
                if (!me->HasUnitState(UNIT_STAT_ONVEHICLE))
                {
                    //return home if not passenger
                    if (me->GetDistance(me->GetHomePosition()) > 20.0f)
                    {
                        me->Kill(me);
                        me->Respawn();
                    }
                }
                else
                {
                    if (me->GetPositionY() > -2595.0f)
                    {
                        //remove charm from drake (find better way to remove control?)
                        if (Unit* pBase = me->GetVehicleBase())
                            if (pBase->isCharmed())
                                pBase->RemoveCharmedBy(pBase->GetCharmer());
                    }
                }
                uiCheckTimer = 10000;
            }else uiCheckTimer -= diff;
        }
    };

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_brunnhildar_prisonerAI(creature);
    }
};

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(DEBUT_BITTER_DEPARTURE) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(0, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->PlayerTalkClass->SendGossipMenu(9999999, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(999999, pCreature->GetGUID());
    return true;
}

bool OnQuestAccept(Player* /*pPlayer*/, Creature* pCreature, Quest const *quest)
{
    if (quest->GetQuestId() == DEBUT_BITTER_DEPARTURE)
        DoScriptText(SAY_QUEST_ACCEPT, pCreature);

    return false;
}

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    npc_escortAI* pEscortAI = CAST_AI(npc_ranshalla::npc_ranshallaAI, pCreature->AI());

    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pEscortAI->Start(true, true, pPlayer->GetGUID());
        pCreature->setFaction(113);
    }
    return true;
}

void AddSC_storm_peaks()
{
    new npc_agnetta_tyrsdottar();
    new npc_frostborn_scout();
    new npc_thorim();
    new npc_goblin_prisoner();
    new npc_victorious_challenger();
    new npc_loklira_crone();
    new npc_injured_goblin();
    /*** quete Brisons la glace.cpp ***/
    new npc_captive_protodrake();
    new npc_freed_protodrake();
    new npc_brunnhildar_prisoner();

// OdyMERGE � int�grer ?    new npc_roxi_ramrocket();
new mob_exhausted_vrykul();
new npc_chieftain_swiftspear();
new npc_goblin_chisel();
new npc_ranshalla();
}