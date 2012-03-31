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
SDName: Dragonblight
SD%Complete: 100
SDComment:
SDCategory: Dragonblight
EndScriptData */

/* ContentData
npc_alexstrasza_wr_gate
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

enum eEnums
{
    QUEST_RETURN_TO_AG_A    = 12499,
    QUEST_RETURN_TO_AG_H    = 12500,
    MOVIE_ID_GATES          = 14
};

#define GOSSIP_ITEM_WHAT_HAPPENED   "Alexstrasza, can you show me what happened here?"

class npc_alexstrasza_wr_gate : public CreatureScript
{
public:
    npc_alexstrasza_wr_gate() : CreatureScript("npc_alexstrasza_wr_gate") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestRewardStatus(QUEST_RETURN_TO_AG_A) || pPlayer->GetQuestRewardStatus(QUEST_RETURN_TO_AG_H))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WHAT_HAPPENED, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

    bool OnGossipSelect(Player* pPlayer, Creature* /*pCreature*/, uint32 /*uiSender*/, uint32 uiAction)
{
        pPlayer->PlayerTalkClass->ClearMenus();
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->SendMovieStart(MOVIE_ID_GATES);
    }

    return true;
}
};

/*######
## npc_inquisitor_hallard. Quest 12321
######*/

enum eInquisitor
{    
    NPC_GODFREY                 = 27577,
    SPELL_HOLY_FIRE             = 39323,

    QUEST_STRENGTHEN_THE_ANCIENTS_H = 12096,
    QUEST_STRENGTHEN_THE_ANCIENTS_A = 12092,

    NPC_HALLARD                 = 27316,

    SAY_WP_0                    = -1800014,
    SAY_WP_1                    = -1800015,
    SAY_WP_2                    = -1800016,
    SAY_WP_3                    = -1800017,
    SAY_WP_4                    = -1800018,
    SAY_WP_5                    = -1800019,
    SAY_WP_6                    = -1800020,
    SAY_WP_7                    = -1800021,
    SAY_WP_8                    = -1800022,
    SAY_WP_9                    = -1800023,
    SAY_WP_10                   = -1800024,
    SAY_WP_11                   = -1800025,
    SAY_WP_12                   = -1800026,
    SAY_WP_13                   = -1800027,
    SAY_WP_14                   = -1800028,
    SAY_WP_15                   = -1800029,
    SAY_WP_16                   = -1800030,
    SAY_WP_17                   = -1800031,
    SAY_WP_18                   = -1800032,
    SAY_WP_19                   = -1800033,
    SAY_WP_20                   = -1800034,
    SAY_WP_21                   = -1800035,
    SAY_WP_22                   = -1800036,
    SAY_WP_23                   = -1800037,
    SAY_WP_24                   = -1800038,
    SAY_WP_25                   = -1800039,
    SAY_WP_26                   = -1800040,
    SAY_WP_27                   = -1800041
};

#define QUEST_A_RIGHTEOUS_SERMON     12321

class npc_inquisitor_hallard : public CreatureScript
{
public:
    npc_inquisitor_hallard() : CreatureScript("npc_inquisitor_hallard") { }

struct npc_inquisitor_hallardAI : public npc_escortAI
{    
    npc_inquisitor_hallardAI(Creature* pCreature) : npc_escortAI(pCreature) { }

    bool Completed;

    void WaypointReached(uint32 i)
    {
        Player* pPlayer = GetPlayerForEscort();
        if (!pPlayer)
            return;
        Creature* Godfrey = me->FindNearestCreature(NPC_GODFREY, 50, true);
        if (!Godfrey)
            return;  
        switch (i)
        {
            case 1:                
                DoScriptText(SAY_WP_1, me, Godfrey);
                me->SetUInt64Value(UNIT_FIELD_TARGET, Godfrey->GetGUID());
                me->HandleEmoteCommand(5);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);                
                break;
            case 2:
                Godfrey->HandleEmoteCommand(434);
                DoScriptText(SAY_WP_2, me, Godfrey);
                me->HandleEmoteCommand(15);
                break;
            case 3:                
                DoScriptText(SAY_WP_3, me, Godfrey);
                me->HandleEmoteCommand(1);
                break;
            case 4:
                DoScriptText(SAY_WP_4, Godfrey);
                break;
            case 5:
                DoScriptText(SAY_WP_5, Godfrey);
                break;
            case 6:
                DoScriptText(SAY_WP_6, Godfrey);
                break;
            case 7:
                DoScriptText(SAY_WP_7, me, Godfrey);
                me->HandleEmoteCommand(1);
                break;
            case 8:
                DoScriptText(SAY_WP_8, me, Godfrey);
                me->HandleEmoteCommand(16);
                break;
            case 9:
                DoScriptText(SAY_WP_9, me, Godfrey);                
                me->HandleEmoteCommand(5);
                break;
            case 10:
                DoScriptText(SAY_WP_10, me, Godfrey);
                DoCast(Godfrey, SPELL_HOLY_FIRE);
                break;
            case 11:
                Godfrey->HandleEmoteCommand(434);
                DoScriptText(SAY_WP_11, Godfrey);
                break;
            case 12:
                DoScriptText(SAY_WP_12, me, Godfrey);
                DoCast(Godfrey, SPELL_HOLY_FIRE);
                break;
            case 13:
                DoScriptText(SAY_WP_13, me, Godfrey);
                DoCast(Godfrey, SPELL_HOLY_FIRE);
                break;
            case 14:
                Godfrey->HandleEmoteCommand(434);
                DoScriptText(SAY_WP_14, Godfrey);
                break;
            case 15:
                DoScriptText(SAY_WP_15, me, Godfrey);
                DoCast(Godfrey, SPELL_HOLY_FIRE);
                break;
            case 16:
                DoScriptText(SAY_WP_16, me, Godfrey);
                break;
            case 17:
                DoScriptText(SAY_WP_17, me, Godfrey);
                break;
            case 18:
                DoScriptText(SAY_WP_18, Godfrey);
                break;
            case 19:
                DoScriptText(SAY_WP_19, me, Godfrey);
                break;
            case 20:
                DoScriptText(SAY_WP_20, Godfrey);
                break;
            case 21:
                DoScriptText(SAY_WP_21, Godfrey);
                break;
            case 22:
                DoScriptText(SAY_WP_22, me, Godfrey);
                break;
            case 23:
                DoScriptText(SAY_WP_23, Godfrey);
                break;
            case 24:
                DoScriptText(SAY_WP_24, Godfrey);
                break;
            case 25:
                DoScriptText(SAY_WP_25, me, Godfrey);
                break;
            case 26:
                DoScriptText(SAY_WP_26, me);
                me->SetUInt64Value(UNIT_FIELD_TARGET, pPlayer->GetGUID());
                break;
            case 27:
                DoScriptText(SAY_WP_27, me, Godfrey);
                me->SetUInt64Value(UNIT_FIELD_TARGET, Godfrey->GetGUID());
                Completed = true;                
                if (pPlayer)
                    pPlayer->GroupEventHappens(QUEST_A_RIGHTEOUS_SERMON, me);
                break;                          
        }
    }

    void Reset()
    {  
        Completed = false;
    }    

    void UpdateAI(const uint32 diff)
    {          
        npc_escortAI::UpdateAI(diff);             
    }
};

    bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_A_RIGHTEOUS_SERMON)
    {        
        DoScriptText(SAY_WP_0, pCreature, pPlayer);
            if (npc_escortAI* pEscortAI = CAST_AI(npc_inquisitor_hallard::npc_inquisitor_hallardAI, pCreature->AI()))
        {
            pEscortAI->Start(true, false, pPlayer->GetGUID(), 0, true);
                pCreature->GetMotionMaster()->MovePoint(0, 3801.543f, -679.350f, 213.75f);
        }
    }
    return true;
}

    CreatureAI *GetAI(Creature *creature) const
    {
        return new npc_inquisitor_hallardAI(creature);
    }
};
#define GOSSIP_ITEM_ASK_FOR_BARK    "Ask for a piece of bark."
#define SPELL_TOUGHEN_HIDE            50994

class npc_woodlands_walker : public CreatureScript
{
public:
    npc_woodlands_walker() : CreatureScript("npc_woodlands_walker") { }

struct npc_woodlands_walkerAI : public ScriptedAI
{
    npc_woodlands_walkerAI(Creature *c) : ScriptedAI(c){}

    uint32 toughenHideTimer ;

    void Reset()
    {
        toughenHideTimer = 7000 ;
        if(me->getFaction() == 14)
            me->setFaction(35) ;
    }

    void UpdateAI(const uint32 diff)
    {
        if(!UpdateVictim())
            return ;

        if(toughenHideTimer <= diff)
        {
            DoCast(me, SPELL_TOUGHEN_HIDE) ;
            toughenHideTimer = 35000 ;
        } else toughenHideTimer -= diff ;

        DoMeleeAttackIfReady() ;
    }
} ;

CreatureAI* GetAI(Creature *pCreature)
{
    return new npc_woodlands_walkerAI(pCreature);
}

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_STRENGTHEN_THE_ANCIENTS_H) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(QUEST_STRENGTHEN_THE_ANCIENTS_A) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ASK_FOR_BARK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        switch(rand()%2)
        {
        case 0 :
            {
                ItemPosCountVec dest;
                uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 36786, 1, false);
                if (msg == EQUIP_ERR_OK)
                {
                    pPlayer->StoreNewItem(dest, 36786, 1, true);
                    pCreature->MonsterTextEmote("Breaking off a piece of its bark, the Woodlands Walker hands it to you before departing.", pPlayer->GetGUID()) ;
                    pPlayer->PlayerTalkClass->ClearMenus();
                }
                break ;
            }
        case 1 :
            {
                pCreature->MonsterTextEmote("is angered by your request and attacks", pPlayer->GetGUID()) ;
                pCreature->setFaction(14) ;
                pCreature->AI()->AttackStart(pPlayer) ;
                break ;
            }
        }
    }
    return true;
}
};

/* Slim Pickings */

#define GOSSIP_ITEM_TAKE_ROCKFLESH    "Take a sample of rockflesh"
#define QUEST_SLIM_PICKINGS                    12075
#define ITEM_SAMPLE_OF_ROCKFLESH            36765

class npc_ravaged_crystalline_ice_giant : public CreatureScript
{
public:
    npc_ravaged_crystalline_ice_giant() : CreatureScript("npc_ravaged_crystalline_ice_giant") { }

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_SLIM_PICKINGS) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TAKE_ROCKFLESH, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        ItemPosCountVec dest;
        uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_SAMPLE_OF_ROCKFLESH, 1, false);
        if (msg == EQUIP_ERR_OK)
        {
            pPlayer->StoreNewItem(dest, ITEM_SAMPLE_OF_ROCKFLESH, 1, true);
            pPlayer->PlayerTalkClass->ClearMenus();
            pCreature->DisappearAndDie() ;
        }
    }
    return true;
}
};

/* The denouncement */
enum Denouncement
{
    SPELL_COMPELLED = 48714,
    KILL_CREDIT_JORDAN = 27426,
    KILL_CREDIT_ZIERHUT = 27427,
    KILL_CREDIT_GOODMAN = 27428,
    KILL_CREDIT_MERCER = 27429,
    SPELL_AVENGING_WRATH = 50837,
    SPELL_CONSECRATION = 32773,
    SPELL_TORCH_TOSS = 50832,
    SPELL_CRUSH_ARMOR = 33661,
    SPELL_SKULL_CRACK = 15621,
    SPELL_SUMMON_WARHORSE = 50829,
};

#define MERCER_YELL "Abbendis is nothing but a harlot, and Grand Admiral Westwind is selling her cheap, just like he sold us out!"

class mob_commander_jordan : public CreatureScript
{
public:
    mob_commander_jordan() : CreatureScript("mob_commander_jordan") { }

struct mob_commander_jordanAI : public ScriptedAI
{
    mob_commander_jordanAI(Creature *c) : ScriptedAI(c) {}

    uint32 avengingWrathTimer ;
    uint32 consecrationTimer ;

    void Reset()
    {
        me->RemoveAllAuras() ;
        avengingWrathTimer = urand(12000, 18000) ;
        consecrationTimer = urand(3000, 6000) ;
    }

    void EnterCombat(Unit* pWho)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if(avengingWrathTimer <= diff)
        {
            DoCast(me, SPELL_AVENGING_WRATH) ;
            avengingWrathTimer = urand(14000, 20000) ;
        } else avengingWrathTimer -= diff ;

        if(consecrationTimer <= diff)
        {
            DoCast(me->getVictim(), SPELL_CONSECRATION) ;
            consecrationTimer = urand(12000, 18000) ;
        } else consecrationTimer -= diff ;

        DoMeleeAttackIfReady() ;
    }

    void JustDied(Unit* pKiller)
    {
        if(me->HasAura(SPELL_COMPELLED))
        {
            if(pKiller->GetTypeId() == TYPEID_PLAYER)
            {
                Player* killer = CAST_PLR(pKiller);
                killer->KilledMonsterCredit(KILL_CREDIT_JORDAN, 0) ;
            }
        }
    }
};

CreatureAI* GetAI(Creature *pCreature)
{
    return new mob_commander_jordanAI(pCreature);
}
};

class mob_lead_cannoneer_zierhut : public CreatureScript
{
public:
    mob_lead_cannoneer_zierhut() : CreatureScript("mob_lead_cannoneer_zierhut") { }

struct mob_lead_cannoneer_zierhutAI : public ScriptedAI
{
    mob_lead_cannoneer_zierhutAI(Creature *c) : ScriptedAI(c) {}

    uint32 torchTossTimer ;

    void Reset()
    {
        me->RemoveAllAuras() ;
        torchTossTimer = urand(5000, 9000) ;
    }

    void EnterCombat(Unit* pWho)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if(torchTossTimer <= diff)
        {
            DoCast(me->getVictim(), SPELL_TORCH_TOSS) ;
            torchTossTimer = urand(14000, 20000) ;
        } else torchTossTimer -= diff ;

        DoMeleeAttackIfReady() ;
    }

    void JustDied(Unit* pKiller)
    {
        if(me->HasAura(SPELL_COMPELLED))
        {
            if(pKiller->GetTypeId() == TYPEID_PLAYER)
            {
                Player* killer = CAST_PLR(pKiller);
                killer->KilledMonsterCredit(KILL_CREDIT_ZIERHUT, 0) ;
            }
        }
    }
};

CreatureAI* GetAI(Creature *pCreature)
{
    return new mob_lead_cannoneer_zierhutAI(pCreature);
}
};

class mob_blacksmith_goodman : public CreatureScript
{
public:
    mob_blacksmith_goodman() : CreatureScript("mob_blacksmith_goodman") { }

struct mob_blacksmith_goodmanAI : public ScriptedAI
{
    mob_blacksmith_goodmanAI(Creature *c) : ScriptedAI(c) {}

    uint32 skullCrackTimer ;
    uint32 crushArmorTimer ;

    void Reset()
    {
        me->RemoveAllAuras() ;
        skullCrackTimer = urand(9000, 12000) ;
        crushArmorTimer = urand(3000, 6000) ;
    }

    void EnterCombat(Unit* pWho)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if(skullCrackTimer <= diff)
        {
            DoCast(me->getVictim(), SPELL_SKULL_CRACK) ;
            skullCrackTimer = urand(14000, 20000) ;
        } else skullCrackTimer -= diff ;

        if(crushArmorTimer <= diff)
        {
            DoCast(me->getVictim(), SPELL_CRUSH_ARMOR) ;
            crushArmorTimer = urand(7000, 12000) ;
        } else crushArmorTimer -= diff ;

        DoMeleeAttackIfReady() ;
    }

    void JustDied(Unit* pKiller)
    {
        if(me->HasAura(SPELL_COMPELLED))
        {
            if(pKiller->GetTypeId() == TYPEID_PLAYER)
            {
                Player* killer = CAST_PLR(pKiller);
                killer->KilledMonsterCredit(KILL_CREDIT_GOODMAN, 0) ;
            }
        }
    }
};

CreatureAI* GetAI(Creature *pCreature)
{
    return new mob_blacksmith_goodmanAI(pCreature);
}
};

class mob_stable_master_mercer : public CreatureScript
{
public:
    mob_stable_master_mercer() : CreatureScript("mob_stable_master_mercer") { }

struct mob_stable_master_mercerAI : public ScriptedAI
{
    mob_stable_master_mercerAI(Creature *c) : ScriptedAI(c) {}

    uint32 yellTimer ;

    void Reset()
    {
        me->RemoveAllAuras() ;
        DoCast(SPELL_SUMMON_WARHORSE) ;
        yellTimer = urand(30000, 60000) ;
    }

    void EnterCombat(Unit* pWho)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        if (!me->getVictim())
        {
            if(yellTimer <= diff)
            {
                me->MonsterYell(MERCER_YELL, LANG_UNIVERSAL, 0) ;
                yellTimer = urand(30000, 60000) ;
            } else yellTimer -= diff ;
        }

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady() ;
    }

    void JustDied(Unit* pKiller)
    {
        if(me->HasAura(SPELL_COMPELLED))
        {
            if(pKiller->GetTypeId() == TYPEID_PLAYER)
            {
                Player* killer = CAST_PLR(pKiller);
                killer->KilledMonsterCredit(KILL_CREDIT_MERCER, 0) ;
            }
        }
    }
};

CreatureAI* GetAI(Creature *pCreature)
{
    return new mob_stable_master_mercerAI(pCreature);
}
};

/* Sarathstra, Scourge of the North */
#define QUEST_SARATHSTRA_SCOURGE_OF_THE_NORTH    12097
#define NPC_SARATHSTRA                            26858
#define GOSSIP_ITEM_SARATHSTRA                    "Call for Sarathstra."

class npc_rokhan : public CreatureScript
{
public:
    npc_rokhan() : CreatureScript("npc_rokhan") { }

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_SARATHSTRA_SCOURGE_OF_THE_NORTH) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SARATHSTRA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        Creature* sarathstra = pCreature->SummonCreature(NPC_SARATHSTRA, 4329, 998, 95.3, 0, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 30000) ;
    }
    return true;
}
};

/* Reclusive runemaster */
#define SPELL_RUNE_SHIELD            48325
#define QUEST_RECLUSIVE_RUNEMASTER    12150
class mob_dregmar_runebrand : public CreatureScript
{
public:
    mob_dregmar_runebrand() : CreatureScript("mob_dregmar_runebrand") { }

struct mob_dregmar_runebrandAI : public ScriptedAI
{
    mob_dregmar_runebrandAI(Creature *c) : ScriptedAI(c) {}

    bool isMovingHome ;
    bool isSpeaking ;
    bool halfLifeSpeak ;

    void Reset()
    {
        isSpeaking = false ;
        halfLifeSpeak = false ;
        isMovingHome = false ;
    }

    void EnterCombat(Unit* pWho)
    {
        me->MonsterYell("Je sais pourquoi vous êtes là : l'un de ces idiots de magnataures des plaines s'est mélé de ce qui ne le regardait pas et a réussi à faire intervenir les dragons. Cela vous plait, de leur obéir comme un gentil petit chien ?", LANG_UNIVERSAL, 0) ;
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if(damage > me->GetHealth())
            damage = 0 ;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if(!isSpeaking)
        {
            if(me->GetHealth() * 5 < me->GetMaxHealth())
            {
                isSpeaking = true ;
                DoCast(me, SPELL_RUNE_SHIELD) ;
            }
        }

        if(!halfLifeSpeak)
        {
            if(me->GetHealth() * 2 < me->GetMaxHealth())
            {
                me->MonsterYell("Vous recherchez leur chef... Petites créatures, vous déclarez la guerre aux clans de Grom'thar le Portefoudre en personne. Ne soyez pas si impatients de foncer vers la mort.", LANG_UNIVERSAL, 0) ;
                halfLifeSpeak = true ;
            }
        }

        if(isSpeaking)
        {
            if(!isMovingHome)
            {
                me->MonsterYell("Ha ! Vous l'aurez voulu. Faites sonner le cor d'un chef magnataure dans le cercle de torches au sud du sanctuaire draconique bleu. Et priez pour le pardon de vos dieux... Grom'thar viendra.", LANG_UNIVERSAL, 0) ;
                Unit *pTarget = NULL;
                std::list<HostileReference *> t_list = me->getThreatManager().getThreatList();
                for (std::list<HostileReference *>::const_iterator itr = t_list.begin(); itr!= t_list.end(); ++itr)
                {
                    pTarget = Unit::GetUnit(*me, (*itr)->getUnitGuid());
                    if (!pTarget)
                        continue;

                    if (pTarget->GetTypeId() == TYPEID_PLAYER)
                    {
                        CAST_PLR(pTarget)->GroupEventHappens(QUEST_RECLUSIVE_RUNEMASTER, me);
                        break ;
                    }
                }
                me->RemoveAllAuras();
                me->DeleteThreatList();
                me->CombatStop();
                me->GetMotionMaster()->MoveTargetedHome();
                isMovingHome = true ;
            }
        }

        DoMeleeAttackIfReady() ;
    }

    void JustDied(Unit* pKiller)
    {
    }
};

CreatureAI* GetAI(Creature *pCreature)
{
    return new mob_dregmar_runebrandAI(pCreature);
}
};

/* The might of the horde */
#define NPC_ANUBAR_INVADER                    26676
#define QUEST_THE_MIGHT_OF_THE_HORDE        12053
class npc_warsong_battle_standard : public CreatureScript
{
public:
    npc_warsong_battle_standard() : CreatureScript("npc_warsong_battle_standard") { }

struct npc_warsong_battle_standardAI : public ScriptedAI
{
    npc_warsong_battle_standardAI(Creature *c) : ScriptedAI(c), lSummons(me)
    {
        summonNumber = 0 ;
        summonTimer = 2000 ;
    }

    uint32 summonTimer ;
    uint8 summonNumber ;
    SummonList lSummons;

    void Reset()
    {
        me->SetReactState(REACT_PASSIVE) ;
    }

    void JustSummoned(Creature* summon)
    {
        lSummons.Summon(summon);
    }

    void JustDied(Unit *who)
    {
        lSummons.DespawnAll();
    }

    void EnterCombat(Unit *who) {}

    void UpdateAI(const uint32 diff)
    {
        if(summonTimer <= diff)
        {
            if(summonNumber >= 5)
            {
                if(Unit* owner = me->GetOwner())
                {
                    if(owner->GetTypeId() == TYPEID_PLAYER)
                    {
                        Player* player = CAST_PLR(owner);
                        player->GroupEventHappens(QUEST_THE_MIGHT_OF_THE_HORDE, me) ;
                    }
                }
                me->DisappearAndDie() ;
            }
            uint8 summons ;
            if(summonNumber<= 2)
                summons = 1 ;
            else if(summonNumber<= 4)
                summons = 2 ;
            else summons = 3 ;
            for(int i = 0 ; i<summons ; i++)
            {
                Creature* defender = me->SummonCreature(NPC_ANUBAR_INVADER, me->GetPositionX()+20, me->GetPositionY()+20, me->GetPositionZ()) ;
                if(defender)
                {
                    defender->AI()->AttackStart(me) ;
                }
            }
            summonNumber ++ ;
            summonTimer = 16000 ;
        } else summonTimer -= diff ; 

        if (!UpdateVictim())
            return;
    }
};


CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_warsong_battle_standardAI (pCreature);
}
};

/* Mystery of the Infinite */
#define NPC_HOURGLASS_OF_ETERNITY_72        27840
#define NPC_HOURGLASS_OF_ETERNITY_80        32327
#define QUEST_MYSTERY_OF_INFINITE_REDUX        13343
#define QUEST_MYSTERY_OF_INFINITE            12470
#define NPC_FUTURE_YOU                        27899
#define NPC_PAST_YOU                        32331
enum OtherYouSayings
{
    SAY_FUTURE_1 =    -6000000,
    SAY_FUTURE_2 =    -6000001,
    SAY_FUTURE_3 =    -6000002,
    SAY_FUTURE_4 =    -6000003,
    SAY_FUTURE_5 =    -6000004,
    SAY_FUTURE_6 =    -6000005,
    SAY_FUTURE_7 =    -6000006,
    SAY_FUTURE_8 =    -6000007,
    SAY_PAST_1 =    -6000008,
    SAY_PAST_2 =    -6000009,
    SAY_PAST_3 =    -6000010,
    SAY_PAST_4 =    -6000011,
    SAY_PAST_5 =    -6000012,
    SAY_PAST_6 =    -6000013,
    SAY_PAST_7 =    -6000014,
    SAY_PAST_8 =    -6000015
};
enum HourglassMobs
{
    NPC_INFINITE_ASSAILANT                    = 27896,
    NPC_INFINITE_CHRONOMAGUS                = 27898,
    NPC_INFINITE_DESTROYER                    = 27897,
    NPC_INFINITE_TIMERENDER                    = 27900,
    NPC_NOZDORMU                            = 27925
};
class npc_hourglass_of_eternity : public CreatureScript
{
public:
    npc_hourglass_of_eternity() : CreatureScript("npc_hourglass_of_eternity") { }

struct npc_hourglass_of_eternityAI : public ScriptedAI
{
    npc_hourglass_of_eternityAI(Creature *c) : ScriptedAI(c), lSummons(me)
    {
        ownerGUID = 0 ;
        summonNumber = 0 ;
        summonTimer = 3000 ;
        if(me->GetEntry() == NPC_HOURGLASS_OF_ETERNITY_72)
        {
            otherYou = me->SummonCreature(NPC_FUTURE_YOU, me->GetPositionX()+5, me->GetPositionY()+5, me->GetPositionZ()) ;
            otherYou->MonsterWhisper("Hey there, don't be alarmed. It's me... you... from the future. I''m here to help.", ownerGUID) ;
        }
        else
        {
            otherYou = me->SummonCreature(NPC_PAST_YOU, me->GetPositionX()+5, me->GetPositionY()+5, me->GetPositionZ()) ;
            otherYou->MonsterWhisper("Whoa! You're me, but from the future! Hey, my equipment got an upgrade. Cool!", ownerGUID) ;
        }
        if (me->isSummon())
        {
            if (owner = CAST_SUM(me)->GetSummoner())
            {
                otherYou->SetMaxHealth(owner->GetMaxHealth()) ;
                otherYou->SetHealth(otherYou->GetMaxHealth()) ;
                otherYou->SetArmor(owner->GetArmor()) ;
                ownerGUID = owner->GetGUID() ;
            }
        }
        me->SetReactState(REACT_PASSIVE) ;
    }

    uint32 summonTimer ;
    uint8 summonNumber ;
    Creature* otherYou ;
    SummonList lSummons;
    Unit* owner ;
    uint64 ownerGUID ;

    void Reset()
    {
    }

    void JustSummoned(Creature* summon)
    {
        if(summon && (summon->GetEntry()!= NPC_NOZDORMU))
            lSummons.Summon(summon);
    }

    void JustDied(Unit *who)
    {
        lSummons.DespawnAll();
    }

    void EnterCombat(Unit *who) {}

    void UpdateAI(const uint32 diff)
    {
        if(summonTimer <= diff)
        {
            switch(summonNumber)
            {
            case 0 :
            case 1 :
                if(me->GetEntry() == NPC_HOURGLASS_OF_ETERNITY_72)
                {
                    otherYou->MonsterWhisper("Heads up... here they come. I'll help as much as I can. Let's just keep them off the hourglass!", ownerGUID) ;
                }
                else
                {
                    otherYou->MonsterWhisper("Here come the Infinites! I've got to keep the hourglass safe. Can you help?", ownerGUID) ;
                }
                for(int i = 0 ; i<2 ; i++)
                {
                    Creature* infinite = me->SummonCreature(RAND(NPC_INFINITE_ASSAILANT, NPC_INFINITE_CHRONOMAGUS,NPC_INFINITE_DESTROYER) , me->GetPositionX()+20, me->GetPositionY()+20, me->GetPositionZ()) ;
                    if(infinite)
                    {
                        infinite->AI()->AttackStart(me) ;
                    }
                }
                summonTimer = 20000 ;
                break ;
            case 2 :
                if(me->GetEntry() == NPC_HOURGLASS_OF_ETERNITY_72)
                {
                    otherYou->MonsterWhisper("I can''t believe that I used to wear that.", ownerGUID) ;                
                }
                else
                {
                    otherYou->MonsterWhisper("Wait a minute! If you're here, then that means that in the not-so-distant future I'm going to be you helping me? Are we stuck in a time loop?", ownerGUID) ;
                }
                for(int i = 0 ; i<3 ; i++)
                {
                    if(Creature* infinite = me->SummonCreature(RAND(NPC_INFINITE_ASSAILANT, NPC_INFINITE_CHRONOMAGUS,NPC_INFINITE_DESTROYER) , me->GetPositionX()+20, me->GetPositionY()+20, me->GetPositionZ()))
                    {
                        infinite->AI()->AttackStart(me) ;
                    }
                }
                summonTimer = 20000 ;
                break ;
            case 3 :
                if(me->GetEntry() == NPC_HOURGLASS_OF_ETERNITY_72)
                {
                    otherYou->MonsterWhisper("Listen. I''m not supposed to tell you this, but there's going to be this party that you're invited to. Whatever you do, DO NOT DRINK THE PUNCH!", ownerGUID) ;
                }
                else
                {
                    otherYou->MonsterWhisper("This equipment looks cool and all, but couldn't we have done a little better? Are you even raiding?", ownerGUID) ;
                }
                if(Creature* infinite = me->SummonCreature(NPC_INFINITE_TIMERENDER, me->GetPositionX()+20, me->GetPositionY()+20, me->GetPositionZ()))
                {
                    infinite->AI()->AttackStart(me) ;
                }
                summonTimer = 40000 ;
                break ;
            case 4 :
                if(me->GetEntry() == NPC_HOURGLASS_OF_ETERNITY_72)
                {
                    otherYou->MonsterWhisper("Look, the hourglass has revealed Nozdormu !", ownerGUID) ;
                }
                else
                {
                    otherYou->MonsterWhisper("What the heck? Nozdormu is up there !", ownerGUID) ;
                }
                if(owner)
                {
                    if(owner->GetTypeId() == TYPEID_PLAYER)
                    {
                        Player* player = CAST_PLR(owner);
                        if(me->GetEntry() == NPC_HOURGLASS_OF_ETERNITY_72)
                            player->GroupEventHappens(QUEST_MYSTERY_OF_INFINITE, me) ;
                        else
                            player->GroupEventHappens(QUEST_MYSTERY_OF_INFINITE_REDUX, me) ;
                    }
                }
                me->SummonCreature(NPC_NOZDORMU, me->GetPositionX()+20, me->GetPositionY()+20, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 60000) ;
                summonTimer = 12000 ;
                break ;
            case 5 :
                if(me->GetEntry() == NPC_HOURGLASS_OF_ETERNITY_72)
                {
                    me->MonsterWhisper("Farewell. Keep us alive and get some better equipment !", ownerGUID) ;
                }
                else
                {
                    me->MonsterWhisper("I feel like I''m being pulled through time. Thanks for the help ...", ownerGUID) ;
                }
                me->DisappearAndDie() ;
                otherYou->DisappearAndDie() ;
                break ;
            }
            summonNumber ++ ;
            summonTimer = 16000 ;
        } else summonTimer -= diff ; 

        if (!UpdateVictim())
            return;
    }
};


CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_hourglass_of_eternityAI(pCreature);
}
};

/* The power to destroy */
#define GOSSIP_ITEM_WORLD_OF_SHADOWS "I want to go in the world of shadows."
enum ThePowerToDestroy
{
    SPELL_WORLD_OF_SHADOWS            =    47740,
    QUEST_THE_POWER_TO_DESTROY        =    12132,
};

class npc_koltira_deathweaver_agmar_hammer : public CreatureScript
{
public:
    npc_koltira_deathweaver_agmar_hammer() : CreatureScript("npc_koltira_deathweaver_agmar_hammer") { }

bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    if(pQuest->GetQuestId() == QUEST_THE_POWER_TO_DESTROY)
    {
        pPlayer->CastSpell(pPlayer, SPELL_WORLD_OF_SHADOWS, true) ;
    }
    return false;
}

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_THE_POWER_TO_DESTROY) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_WORLD_OF_SHADOWS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, SPELL_WORLD_OF_SHADOWS, true);
    }

    return true;
}
};

/* Where the wild things roam */
enum WhereTheWildThingsRoam
{
    SPELL_RECENTLY_INNOCULATED        = 47675,
    SPELL_PUNCTURE                    = 15976
};

class mob_arctic_grizzly : public CreatureScript
{
public:
    mob_arctic_grizzly() : CreatureScript("mob_arctic_grizzly") { }

struct mob_arctic_grizzlyAI : public ScriptedAI
{
    mob_arctic_grizzlyAI(Creature *c) : ScriptedAI(c) 
    {
    }

    void Reset()
    {
    }

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        if (spell->Id == 47627 && !me->HasAura(SPELL_RECENTLY_INNOCULATED))
        {
            if(caster->GetTypeId() == TYPEID_PLAYER)
            {
                Player* player = CAST_PLR(caster);
                player->KilledMonsterCredit(26882, 0) ;
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady() ;
    }
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new mob_arctic_grizzlyAI (pCreature);
}
};

class mob_snowfall_elk : public CreatureScript
{
public:
    mob_snowfall_elk() : CreatureScript("mob_snowfall_elk") { }

struct mob_snowfall_elkAI : public ScriptedAI
{
    mob_snowfall_elkAI(Creature *c) : ScriptedAI(c) 
    {
    }

    uint32 punctureTimer ;

    void Reset()
    {
        punctureTimer = urand(5000, 8000) ;
    }

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        if (spell->Id == 47627 && !me->HasAura(SPELL_RECENTLY_INNOCULATED))
        {
            if(caster->GetTypeId() == TYPEID_PLAYER)
            {
                Player* player = CAST_PLR(caster);
                player->KilledMonsterCredit(26895, 0) ;
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        if(punctureTimer<diff)
        {
            DoCast(me->getVictim(), SPELL_PUNCTURE);
            punctureTimer = urand(9000, 14000) ;
        } else punctureTimer -= diff ;

        DoMeleeAttackIfReady() ;
    }
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new mob_snowfall_elkAI (pCreature);
}
};

class mob_fallen_earthen_defender : public CreatureScript
{
public:
    mob_fallen_earthen_defender() : CreatureScript("mob_fallen_earthen_defender") { }

struct mob_fallen_earthen_defenderAI : public ScriptedAI
{
    mob_fallen_earthen_defenderAI(Creature *c) : ScriptedAI(c) 
    {
        despawnTimer = 30000 ;
    }

    bool isFollowing ;
    uint32 despawnTimer ;

    void Reset()
    {
        isFollowing = false ;
    }

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        if (spell->Id == 55804 && !isFollowing)
        {
            if(caster->GetTypeId() == TYPEID_PLAYER)
            {
                Player* player = CAST_PLR(caster);
                player->KilledMonsterCredit(me->GetEntry(), 0) ;
                me->SetStandState(UNIT_STAND_STATE_STAND) ;
                isFollowing = true ;
                me->GetMotionMaster()->MoveFollow(player, 3.0f, 0) ;
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if(isFollowing)
        {
            if(despawnTimer <= diff)
            {
                me->DisappearAndDie() ;
            } else despawnTimer -= diff ;
        }

        //Return since we have no target
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady() ;
    }
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new mob_fallen_earthen_defenderAI (pCreature);
}
};

void AddSC_dragonblight()
{
    new npc_alexstrasza_wr_gate();
    new npc_inquisitor_hallard();
new npc_woodlands_walker();
new npc_ravaged_crystalline_ice_giant();
new mob_commander_jordan();
new mob_lead_cannoneer_zierhut();
new mob_blacksmith_goodman();
new mob_stable_master_mercer();
new npc_rokhan();
new mob_dregmar_runebrand();
new npc_warsong_battle_standard();
new npc_hourglass_of_eternity();
new npc_koltira_deathweaver_agmar_hammer();
new mob_arctic_grizzly();
new mob_snowfall_elk();
new mob_fallen_earthen_defender();
}
