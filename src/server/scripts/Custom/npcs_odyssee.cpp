/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Npcs_Odyssee
SD%Complete: 100
SDComment: Par léquipe odyssée, npc custom
SDCategory: NPCs Custom
EndScriptData
*/

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "World.h"

#define NPC_FFA_RADIUS      501101

class npc_ffa : public CreatureScript
{
public:
    npc_ffa() : CreatureScript("npc_ffa") { }
	
struct npc_ffaAI : public ScriptedAI
{
    npc_ffaAI(Creature* c) : ScriptedAI(c)
    {
        pMap = c->GetMap();
    }
    Map* pMap;
    Creature* ffa_radius;
    uint8 radius;
    uint16 check_timer;

    void Reset()
    {
        ffa_radius = 0;
        check_timer = 500;
        ffa_radius = me->FindNearestCreature(NPC_FFA_RADIUS, 300);
    }

    void UpdateAI(const uint32 diff)
    {
        if (check_timer <= diff)
        {
            if (!ffa_radius)
                ffa_radius = me->FindNearestCreature(NPC_FFA_RADIUS, 300);

            if (ffa_radius)
            {
                radius = me->GetDistance2d(ffa_radius);

                Map::PlayerList const &PlayerList = pMap->GetPlayers();
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                {
                    if (i->getSource()->isAlive() && !i->getSource()->isGameMaster())
                    {
                        if (me->IsWithinDist(i->getSource(), radius))
                        {
                            if (!i->getSource()->HasByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP))
                                i->getSource()->SetByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
                        }
                        else
                        {
                            if (i->getSource()->HasByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP))
                                i->getSource()->RemoveByteFlag(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_FLAG_FFA_PVP);
                        }
                    }
                }
            }

            check_timer = 500;
        }
        else check_timer -= diff;
    }

};

CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_ffaAI(pCreature);
}
};

#define GOSSIP_ITEM_1 "Participer à l'event"
#define GOSSIP_ITEM_2 "Quitter l'event"
class npc_changephase : public CreatureScript
{
public:
    npc_changephase() : CreatureScript("npc_changephase") { }
	
bool OnGossipHello(Player* pPlayer, Creature* pCreature) 
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_1,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_2,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->SEND_GOSSIP_MENU(68, pCreature->GetGUID());
    return true;
}
bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->SetPhaseMask(16, true);
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->SetPhaseMask(1, 0);
    }
    return true;
}
};
#define GOSSIP_ITEM_ACHERUS_1 "Être téléporté(e) au Hall d'Achérus"
#define GOSSIP_ITEM_ACHERUS_2 "Être téléporté(e) au Cœur d'Achérus"
class npc_portal_acherushack : public CreatureScript
{
public:
    npc_portal_acherushack() : CreatureScript("npc_portal_acherushack") { }
	
bool OnGossipHello(Player* pPlayer, Creature* pCreature) 
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_ACHERUS_1,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_ACHERUS_2,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->SEND_GOSSIP_MENU(100010, pCreature->GetGUID());
    return true;
}
bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->TeleportTo(609, 2399.07, -5635.15, 377.035, 3.70201);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->TeleportTo(609, 2418.67, -5621.41, 420.644, 3.89597);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}
};
#define GOSSIP_ITEM_NAXXANAR_1 "Être téléporté(e) à Naxxanar"
#define GOSSIP_ITEM_NAXXANAR_2 "Être téléporté(e) à la Surface"
class npc_portal_naxxanarhack : public CreatureScript
{
public:
    npc_portal_naxxanarhack() : CreatureScript("npc_portal_naxxanarhack") { }
	
bool OnGossipHello(Player* pPlayer, Creature* pCreature) 
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_NAXXANAR_1,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_NAXXANAR_2,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->SEND_GOSSIP_MENU(100011, pCreature->GetGUID());
    return true;
}
bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->TeleportTo(571, 3738.86, 3566.11, 290.79, 3.76);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->TeleportTo(571, 3799.17, 3580.97, 51.72, 3.76);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}
};
#define GOSSIP_ITEM_JOUG_1 "Être téléporté(e) dans la Forteresse du Joug d'Hiver"
class npc_portal_joughack : public CreatureScript
{
public:
    npc_portal_joughack() : CreatureScript("npc_portal_joughack") { }
	
bool OnGossipHello(Player* pPlayer, Creature* pCreature) 
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_JOUG_1,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF);
    pPlayer->SEND_GOSSIP_MENU(100011, pCreature->GetGUID());
    return true;
}
bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->TeleportTo(571, 5408.328, 2841.659, 418.675, 6.234);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}
};
#define NPC_CUIR      501108
#define NPC_MOUSTACHE 501109
class npc_cuir_moustache : public CreatureScript
{
public:
    npc_cuir_moustache() : CreatureScript("npc_cuir_moustache") { }
	
struct npc_cuir_moustacheAI : public ScriptedAI
{
    npc_cuir_moustacheAI(Creature *c) : ScriptedAI(c) 
    {
       me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
    }

    uint32 SummonTimer;
    bool event;
    bool despawn;

    void Reset()
    {
        SummonTimer = 0;
        event = false;
        despawn = false;
    }

    void EnterCombat(Unit * /*who*/) {}


    void DespawnCreatures(uint32 entry, float distance)
    {
        std::list<Creature*> m_pCreatures;
        GetCreatureListWithEntryInGrid(m_pCreatures, me, entry, distance);

        if (m_pCreatures.empty())
            return;

        for(std::list<Creature*>::iterator iter = m_pCreatures.begin(); iter != m_pCreatures.end(); ++iter)
            if(*iter)
                (*iter)->ForcedDespawn();

    }

    void UpdateAI(const uint32 diff)
    {
        if (event)
        {
            if (SummonTimer <= diff)
            {
                switch(urand(0, 3))
                {
                    case 0: 
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX(), me->GetPositionY()+10, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX(), me->GetPositionY()-10, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX()+10, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX()-10, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    break; 
                    case 1: 
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX()+10, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_MOUSTACHE, me->GetPositionX(), me->GetPositionY()+10, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    break;
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX()-10, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_MOUSTACHE, me->GetPositionX(), me->GetPositionY()-10, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    break;
                    case 2: 
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX()+10, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX(), me->GetPositionY()+10, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX()-10, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_MOUSTACHE, me->GetPositionX(), me->GetPositionY()-10, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    break;
                    case 3: 
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX()+10, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_CUIR, me->GetPositionX(), me->GetPositionY()+10, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_MOUSTACHE, me->GetPositionX()-10, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    if (Creature* pTemp = me->SummonCreature(NPC_MOUSTACHE, me->GetPositionX(), me->GetPositionY()-10, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, urand(20000,30000)))
                        if(Unit* pUnit = pTemp->SelectNearestTarget())
                            pTemp->AI()->AttackStart(pUnit);
                    break;
                }
                SummonTimer = 5000;
            } else SummonTimer -= diff;
        }

        if(despawn)
        {
            DespawnCreatures(NPC_CUIR, 50.0f);
            DespawnCreatures(NPC_MOUSTACHE, 50.0f);
            despawn = false;
        }
    }
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_cuir_moustacheAI(pCreature);
}


#define GOSSIP_CUIR_1 "Déclencher l'Event"
#define GOSSIP_CUIR_2 "Arrêter l'Event"
bool OnGossipHello(Player* pPlayer, Creature* pCreature) 
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_CUIR_1,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_CUIR_2,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->SEND_GOSSIP_MENU(100012, pCreature->GetGUID());
    return true;
}
bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        CAST_AI(npc_cuir_moustacheAI, pCreature->AI())->event=true;
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        CAST_AI(npc_cuir_moustacheAI, pCreature->AI())->event=false;
        CAST_AI(npc_cuir_moustacheAI, pCreature->AI())->despawn=true;
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}
};

class npc_cuir : public CreatureScript
{
public:
    npc_cuir() : CreatureScript("npc_cuir") { }
	
struct npc_cuirAI : public ScriptedAI
{
    npc_cuirAI(Creature *c) : ScriptedAI(c) 
    {
    }

    bool Say;

    void Reset()
    {
        Say = true;
    }

    void EnterCombat(Unit * /*who*/) {}

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
             if (Creature* pCM = me->FindNearestCreature(501107, 50.0f))
                if(pCM)
                {
                    CAST_AI(npc_cuir_moustache::npc_cuir_moustacheAI, pCM->AI())->event=false;
                    CAST_AI(npc_cuir_moustache::npc_cuir_moustacheAI, pCM->AI())->despawn=true;
                }
        
        if (Say)
        {
            me->MonsterYell("CUIR !", LANG_UNIVERSAL, 0);
            Say = false;
        }

        if (UpdateVictim())
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_cuirAI(pCreature);
}
};

class npc_moustache : public CreatureScript
{
public:
    npc_moustache() : CreatureScript("npc_moustache") { }
	
struct npc_moustacheAI : public ScriptedAI
{
    npc_moustacheAI(Creature *c) : ScriptedAI(c) 
    {
    }

    bool Say;

    void Reset()
    {
        Say = true;
    }

    void EnterCombat(Unit * /*who*/) {}

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
             if (Creature* pCM = me->FindNearestCreature(501107, 50.0f))
                if(pCM)
                {
                    CAST_AI(npc_cuir_moustache::npc_cuir_moustacheAI, pCM->AI())->event=false;
                    CAST_AI(npc_cuir_moustache::npc_cuir_moustacheAI, pCM->AI())->despawn=true;
                }

        if (Say)
        {
            me->MonsterYell("MOUSTACHE !", LANG_UNIVERSAL, 0);
            Say = false;
        }

        if (UpdateVictim())
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_moustacheAI(pCreature);
}
};


#define GOSSIP_QUEST_13220 "Valider la quête 13220"
class npc_quest13220 : public CreatureScript
{
public:
    npc_quest13220() : CreatureScript("npc_quest13220") { }
	
bool OnGossipHello(Player* pPlayer, Creature* pCreature) 
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_QUEST_13220,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF); //ajout GOSSIP_QUEST_13220
    pPlayer->SEND_GOSSIP_MENU(100013, pCreature->GetGUID()); //ajout npc_text débug quête odyssée
    return true;
}
bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF) //si le joueur est ok avec GOSSIP_QUEST_13220
    {
        pPlayer->CompleteQuest(13220); //on complète la quête
        pPlayer->CLOSE_GOSSIP_MENU(); //on ferme le menu de parlote au npc
    }
    return true;
}
};
#define GOSSIP_QUEST_9164   "Valider l'objectif 1 de la quête 9164"
#define GOSSIP_QUEST_9164_2 "Valider l'objectif 2 de la quête 9164"
#define GOSSIP_QUEST_9164_3 "Valider l'objectif 3 de la quête 9164"
class npc_quest9164 : public CreatureScript
{
public:
    npc_quest9164() : CreatureScript("npc_quest9164") { }
	
bool OnGossipHello(Player* pPlayer, Creature* pCreature) 
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_QUEST_9164,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_QUEST_9164_2,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_QUEST_9164_3,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+2);
    pPlayer->SEND_GOSSIP_MENU(100013, pCreature->GetGUID()); //ajout npc_text débug quête odyssée
    return true;
}
bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        CAST_PLR(pPlayer)->KilledMonsterCredit(16208,0);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        CAST_PLR(pPlayer)->KilledMonsterCredit(16209,0);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
    {
        CAST_PLR(pPlayer)->KilledMonsterCredit(16206,0);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}
};
// Quete Escorte
class npc_questescorte : public CreatureScript
{
public:
    npc_questescorte() : CreatureScript("npc_questescorte") { }
	
struct npc_questescorteAI : public ScriptedAI
{
    npc_questescorteAI(Creature* c) : ScriptedAI(c)
    {
    }
    
    uint32 check_timer;
    uint8 phase;

    void Reset()
    {
    }

    void UpdateAI(const uint32 diff)
    {
        if (check_timer <= diff)
        {
            if (phase == 1)
            {
                me->SetHealth(11111); //hack
            }
        }
        else check_timer -= diff;
    }

};

#define GOSSIP_QUEST_EN_COURS "C'est parti !"
#define GOSSIP_QUEST_FINI   "Merci de m'avoir aider !"

enum eEnumDivers
{
    POS_X              = 1, //pos x à atteindre
    POS_Y              = 1, //pos y à atteindre
    POS_Z              = 1, //pos z à atteindre
    TEMPS_MIS          = 1, //temps mis pour atteindre
    KILL_CREDIT        = 1, //objectif
    QUEST_REQUIS       = 1, //quete requise
    QUEST_COMPLETE     = 1  //quete à compléter
};

bool OnGossipHello(Player* pPlayer, Creature* pCreature) 
{
    if (pPlayer->GetQuestStatus(QUEST_REQUIS))
        if (pCreature->GetHealth() != 11111) //hack
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_QUEST_EN_COURS,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF);

    if (pPlayer->GetQuestStatus(QUEST_REQUIS))
        if (pCreature->GetHealth() == 11111) //hack
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_QUEST_FINI,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(100013, pCreature->GetGUID()); //ajout npc_text débug quête odyssée
    return true;
}
bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        if(Creature* pTemp = pCreature->SummonCreature(pCreature->GetEntry(), pCreature->GetPositionX(), pCreature->GetPositionY(), pCreature->GetPositionZ()+1, 0, TEMPSUMMON_MANUAL_DESPAWN, 0))
        {
            pTemp->GetMotionMaster()->MovePoint(0, POS_X, POS_Y, POS_Z); // Move to x, y, z
            CAST_AI(npc_questescorteAI, pTemp->AI())->phase=1;
            CAST_AI(npc_questescorteAI, pTemp->AI())->check_timer=TEMPS_MIS; //temps qu'il met
        }
        pPlayer->CLOSE_GOSSIP_MENU();
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->KilledMonsterCredit(KILL_CREDIT,0); // 1: Creature à tuer pour valider objectif look quest_template
        pPlayer->CompleteQuest(QUEST_COMPLETE);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_questescorteAI(pCreature);
}
};

void AddSC_npcs_odyssee()
{
 new npc_ffa();
new npc_changephase();
new npc_portal_acherushack();
new npc_portal_naxxanarhack();
new npc_portal_joughack();
new npc_cuir_moustache();
new npc_cuir();
new npc_moustache();
new npc_quest13220();
new npc_quest9164();
new npc_questescorte();
}

