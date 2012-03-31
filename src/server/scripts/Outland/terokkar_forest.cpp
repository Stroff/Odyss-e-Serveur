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
SDName: Terokkar_Forest
SD%Complete: 85
SDComment: Quest support: 9889, 10009, 10873, 10896, 10898, 11096, 10052, 10051. Skettis->Ogri'la Flight
SDCategory: Terokkar Forest
EndScriptData */

/* ContentData
mob_unkor_the_ruthless
mob_infested_root_walker
mob_rotting_forest_rager
mob_netherweb_victim
npc_floon
npc_isla_starmane
npc_slim
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"
#include "Group.h"

/*######
## mob_unkor_the_ruthless
######*/

#define SAY_SUBMIT                      -1000194

#define FACTION_HOSTILE                 45
#define FACTION_FRIENDLY                35
#define QUEST_DONTKILLTHEFATONE         9889

#define SPELL_PULVERIZE                 2676
//#define SPELL_QUID9889                32174

class mob_unkor_the_ruthless : public CreatureScript
{
public:
    mob_unkor_the_ruthless() : CreatureScript("mob_unkor_the_ruthless") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_unkor_the_ruthlessAI (pCreature);
    }

struct mob_unkor_the_ruthlessAI : public ScriptedAI
{
    mob_unkor_the_ruthlessAI(Creature* c) : ScriptedAI(c) {}

    bool CanDoQuest;
    uint32 UnkorUnfriendly_Timer;
    uint32 Pulverize_Timer;

    void Reset()
    {
        CanDoQuest = false;
        UnkorUnfriendly_Timer = 0;
        Pulverize_Timer = 3000;
        me->SetStandState(UNIT_STAND_STATE_STAND);
        me->setFaction(FACTION_HOSTILE);
    }

    void EnterCombat(Unit * /*who*/) {}

    void DoNice()
    {
        DoScriptText(SAY_SUBMIT, me);
        me->setFaction(FACTION_FRIENDLY);
        me->SetStandState(UNIT_STAND_STATE_SIT);
        me->RemoveAllAuras();
        me->DeleteThreatList();
        me->CombatStop(true);
        UnkorUnfriendly_Timer = 60000;
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
                if (me->HealthBelowPctDamaged(30, damage))
        {
            if (Group* pGroup = CAST_PLR(done_by)->GetGroup())
            {
                for (GroupReference *itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                {
                    Player *pGroupie = itr->getSource();
                    if (pGroupie &&
                        pGroupie->GetQuestStatus(QUEST_DONTKILLTHEFATONE) == QUEST_STATUS_INCOMPLETE &&
                        pGroupie->GetReqKillOrCastCurrentCount(QUEST_DONTKILLTHEFATONE, 18260) == 10)
                    {
                        pGroupie->AreaExploredOrEventHappens(QUEST_DONTKILLTHEFATONE);
                        if (!CanDoQuest)
                            CanDoQuest = true;
                    }
                }
            } else
            if (CAST_PLR(done_by)->GetQuestStatus(QUEST_DONTKILLTHEFATONE) == QUEST_STATUS_INCOMPLETE &&
                CAST_PLR(done_by)->GetReqKillOrCastCurrentCount(QUEST_DONTKILLTHEFATONE, 18260) == 10)
            {
                CAST_PLR(done_by)->AreaExploredOrEventHappens(QUEST_DONTKILLTHEFATONE);
                CanDoQuest = true;
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (CanDoQuest)
        {
            if (!UnkorUnfriendly_Timer)
            {
                //DoCast(me, SPELL_QUID9889);        //not using spell for now
                DoNice();
            }
            else
            {
                if (UnkorUnfriendly_Timer <= diff)
                {
                    EnterEvadeMode();
                    return;
                } else UnkorUnfriendly_Timer -= diff;
            }
        }

        if (!UpdateVictim())
            return;

        if (Pulverize_Timer <= diff)
        {
            DoCast(me, SPELL_PULVERIZE);
            Pulverize_Timer = 9000;
        } else Pulverize_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

};

/*######
## mob_infested_root_walker
######*/

class mob_infested_root_walker : public CreatureScript
{
public:
    mob_infested_root_walker() : CreatureScript("mob_infested_root_walker") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_infested_root_walkerAI (pCreature);
    }

struct mob_infested_root_walkerAI : public ScriptedAI
{
    mob_infested_root_walkerAI(Creature *c) : ScriptedAI(c) {}

    void Reset() { }
    void EnterCombat(Unit * /*who*/) { }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by && done_by->GetTypeId() == TYPEID_PLAYER)
            if (me->GetHealth() <= damage)
                if (rand()%100 < 75)
                    //Summon Wood Mites
                    DoCast(me, 39130, true);
    }
};

};

/*######
## mob_skywing
######*/
class npc_skywing : public CreatureScript
{
public:
    npc_skywing() : CreatureScript("npc_skywing") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_skywingAI(pCreature);
    }

struct npc_skywingAI : public npc_escortAI
{
public:
    npc_skywingAI(Creature *c) : npc_escortAI(c) {}

    void WaypointReached(uint32 i)
    {
        Player* pPlayer = GetPlayerForEscort();
        if (!pPlayer)
            return;

        switch(i)
        {
            case 8:
                pPlayer->AreaExploredOrEventHappens(10898);
                break;
        }
    }

    void EnterCombat(Unit* /*who*/) {}

    void MoveInLineOfSight(Unit *who)
    {
        if (HasEscortState(STATE_ESCORT_ESCORTING))
            return;

        if (who->GetTypeId() == TYPEID_PLAYER)
        {
            if (CAST_PLR(who)->GetQuestStatus(10898) == QUEST_STATUS_INCOMPLETE)
            {
                    float Radius = 10.0f;
                if (me->IsWithinDistInMap(who, Radius))
                {
                    Start(false, false, who->GetGUID());
                }
            }
        }
    }

    void Reset() {}

    void UpdateAI(const uint32 diff)
    {
        npc_escortAI::UpdateAI(diff);
    }
};

};

/*######
## mob_rotting_forest_rager
######*/

class mob_rotting_forest_rager : public CreatureScript
{
public:
    mob_rotting_forest_rager() : CreatureScript("mob_rotting_forest_rager") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_rotting_forest_ragerAI (pCreature);
    }

struct mob_rotting_forest_ragerAI : public ScriptedAI
{
    mob_rotting_forest_ragerAI(Creature *c) : ScriptedAI(c) {}

    void Reset() { }
    void EnterCombat(Unit * /*who*/) { }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if (done_by->GetTypeId() == TYPEID_PLAYER)
            if (me->GetHealth() <= damage)
                if (rand()%100 < 75)
                    //Summon Lots of Wood Mights
                    DoCast(me, 39134, true);
    }
};

};

/*######
## mob_netherweb_victim
######*/

#define QUEST_TARGET        22459
//#define SPELL_FREE_WEBBED   38950

const uint32 netherwebVictims[6] =
{
    18470, 16805, 21242, 18452, 22482, 21285
};
class mob_netherweb_victim : public CreatureScript
{
public:
    mob_netherweb_victim() : CreatureScript("mob_netherweb_victim") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_netherweb_victimAI (pCreature);
    }

struct mob_netherweb_victimAI : public ScriptedAI
{
    mob_netherweb_victimAI(Creature *c) : ScriptedAI(c) {}

    void Reset() { }
    void EnterCombat(Unit * /*who*/) { }
    void MoveInLineOfSight(Unit * /*who*/) { }

    void JustDied(Unit* Killer)
    {
        if (Killer->GetTypeId() == TYPEID_PLAYER)
        {
            if (CAST_PLR(Killer)->GetQuestStatus(10873) == QUEST_STATUS_INCOMPLETE)
            {
                if (rand()%100 < 25)
                {
                    me->SummonCreature(QUEST_TARGET, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                        CAST_PLR(Killer)->KilledMonsterCredit(QUEST_TARGET, 0);
                }
                else
                    me->SummonCreature(netherwebVictims[rand()%6], 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);

                if (rand()%100 < 75)
                    me->SummonCreature(netherwebVictims[rand()%6], 0.0f, 0.0f, 0.0f,0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                me->SummonCreature(netherwebVictims[rand()%6], 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
            }
        }
    }
};

};

/*######
## npc_floon
######*/

#define GOSSIP_FLOON1           "You owe Sim'salabim money. Hand them over or die!"
#define GOSSIP_FLOON2           "Hand over the money or die...again!"

enum eFloon
{
    SAY_FLOON_ATTACK        = -1000195,

    SPELL_SILENCE           = 6726,
    SPELL_FROSTBOLT         = 9672,
    SPELL_FROST_NOVA        = 11831,

    FACTION_HOSTILE_FL      = 1738,
    QUEST_CRACK_SKULLS      = 10009
};

class npc_floon : public CreatureScript
{
public:
    npc_floon() : CreatureScript("npc_floon") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF)
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FLOON2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(9443, pCreature->GetGUID());
        }
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pCreature->setFaction(FACTION_HOSTILE_FL);
            DoScriptText(SAY_FLOON_ATTACK, pCreature, pPlayer);
            pCreature->AI()->AttackStart(pPlayer);
        }
        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->GetQuestStatus(QUEST_CRACK_SKULLS) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_FLOON1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        pPlayer->SEND_GOSSIP_MENU(9442, pCreature->GetGUID());
        return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_floonAI (pCreature);
    }

struct npc_floonAI : public ScriptedAI
{
    npc_floonAI(Creature* c) : ScriptedAI(c)
    {
        m_uiNormFaction = c->getFaction();
    }

    uint32 m_uiNormFaction;
    uint32 Silence_Timer;
    uint32 Frostbolt_Timer;
    uint32 FrostNova_Timer;

    void Reset()
    {
        Silence_Timer = 2000;
        Frostbolt_Timer = 4000;
        FrostNova_Timer = 9000;
        if (me->getFaction() != m_uiNormFaction)
            me->setFaction(m_uiNormFaction);
    }

    void EnterCombat(Unit * /*who*/) {}

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (Silence_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_SILENCE);
            Silence_Timer = 30000;
        } else Silence_Timer -= diff;

        if (FrostNova_Timer <= diff)
        {
            DoCast(me, SPELL_FROST_NOVA);
            FrostNova_Timer = 20000;
        } else FrostNova_Timer -= diff;

        if (Frostbolt_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_FROSTBOLT);
            Frostbolt_Timer = 5000;
        } else Frostbolt_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

};

/*######
## npc_isla_starmane
######*/
enum eIslaStarmaneData
{
    SAY_PROGRESS_1  = -1000571,
    SAY_PROGRESS_2  = -1000572,
    SAY_PROGRESS_3  = -1000573,
    SAY_PROGRESS_4  = -1000574,

    QUEST_EFTW_H    = 10052,
    QUEST_EFTW_A    = 10051,
    GO_CAGE         = 182794,
    SPELL_CAT       = 32447,
};

class npc_isla_starmane : public CreatureScript
{
public:
    npc_isla_starmane() : CreatureScript("npc_isla_starmane") { }

struct npc_isla_starmaneAI : public npc_escortAI
{
    npc_isla_starmaneAI(Creature* c) : npc_escortAI(c) {}

    void WaypointReached(uint32 i)
    {
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
            return;

        switch(i)
        {
        case 0:
            {
            GameObject* Cage = me->FindNearestGameObject(GO_CAGE, 10);
            if (Cage)
                Cage->SetGoState(GO_STATE_ACTIVE);
            }
            break;
        case 2: DoScriptText(SAY_PROGRESS_1, me, pPlayer); break;
        case 5: DoScriptText(SAY_PROGRESS_2, me, pPlayer); break;
        case 6: DoScriptText(SAY_PROGRESS_3, me, pPlayer); break;
        case 29:DoScriptText(SAY_PROGRESS_4, me, pPlayer);
            if (pPlayer)
            {
                if (pPlayer->GetTeam() == ALLIANCE)
                    pPlayer->GroupEventHappens(QUEST_EFTW_A, me);
                else if (pPlayer->GetTeam() == HORDE)
                    pPlayer->GroupEventHappens(QUEST_EFTW_H, me);
            }
            me->SetInFront(pPlayer); break;
        case 30: me->HandleEmoteCommand(EMOTE_ONESHOT_WAVE); break;
        case 31: DoCast(me, SPELL_CAT);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING); break;
        }
    }

    void Reset()
    {
        me->RestoreFaction();
    }

    void JustDied(Unit* /*killer*/)
    {
        if (Player* pPlayer = GetPlayerForEscort())
        {
            if (pPlayer->GetTeam() == ALLIANCE)
                pPlayer->FailQuest(QUEST_EFTW_A);
            else if (pPlayer->GetTeam() == HORDE)
                pPlayer->FailQuest(QUEST_EFTW_H);
        }
    }
};

    bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_EFTW_H || quest->GetQuestId() == QUEST_EFTW_A)
    {
        CAST_AI(npc_escortAI, (pCreature->AI()))->Start(true, false, pPlayer->GetGUID());
        pCreature->setFaction(113);
    }
    return true;
}

    CreatureAI* GetAI(Creature* pCreature) const
{
    return new npc_isla_starmaneAI(pCreature);
}

};

/*######
## go_skull_pile
######*/
#define GOSSIP_S_DARKSCREECHER_AKKARAI         "Summon Darkscreecher Akkarai"
#define GOSSIP_S_KARROG         "Summon Karrog"
#define GOSSIP_S_GEZZARAK_THE_HUNTRESS         "Summon Gezzarak the Huntress"
#define GOSSIP_S_VAKKIZ_THE_WINDRAGER         "Summon Vakkiz the Windrager"

class go_skull_pile : public GameObjectScript
{
public:
    go_skull_pile() : GameObjectScript("go_skull_pile") { }

    bool OnGossipSelect(Player* pPlayer, GameObject* pGo, uint32 uiSender, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        switch(uiSender)
        {
            case GOSSIP_SENDER_MAIN:    SendActionMenu(pPlayer, pGo, uiAction); break;
        }
        return true;
    }

    bool OnGossipHello(Player* pPlayer, GameObject* pGo)
{
    if ((pPlayer->GetQuestStatus(11885) == QUEST_STATUS_INCOMPLETE) || pPlayer->GetQuestRewardStatus(11885))
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_S_DARKSCREECHER_AKKARAI, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_S_KARROG, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_S_GEZZARAK_THE_HUNTRESS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_S_VAKKIZ_THE_WINDRAGER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    }

    pPlayer->SEND_GOSSIP_MENU(pGo->GetGOInfo()->questgiver.gossipID, pGo->GetGUID());
    return true;
}

    void SendActionMenu(Player* pPlayer, GameObject* /*pGo*/, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
              pPlayer->CastSpell(pPlayer,40642,false);
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
              pPlayer->CastSpell(pPlayer,40640,false);
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
              pPlayer->CastSpell(pPlayer,40632,false);
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
              pPlayer->CastSpell(pPlayer,40644,false);
            break;
    }
}
};

/*######
## npc_slim
######*/

enum eSlim
{
    FACTION_CONSORTIUM  = 933
};

class npc_slim : public CreatureScript
{
public:
    npc_slim() : CreatureScript("npc_slim") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_TRADE)
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());

        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isVendor() && pPlayer->GetReputationRank(FACTION_CONSORTIUM) >= REP_FRIENDLY)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
        pPlayer->SEND_GOSSIP_MENU(9896, pCreature->GetGUID());
    }
    else
        pPlayer->SEND_GOSSIP_MENU(9895, pCreature->GetGUID());

    return true;
}

};

/*########
####npc_akuno
#####*/

enum eAkuno
{
    QUEST_ESCAPING_THE_TOMB = 10887,
    NPC_CABAL_SKRIMISHER    = 21661
};

class npc_akuno : public CreatureScript
{
public:
    npc_akuno() : CreatureScript("npc_akuno") { }

    bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_ESCAPING_THE_TOMB)
    {
            if (npc_akunoAI* pEscortAI = CAST_AI(npc_akuno::npc_akunoAI, pCreature->AI()))
            pEscortAI->Start(false, false, pPlayer->GetGUID());

        if (pPlayer->GetTeamId() == TEAM_ALLIANCE)
            pCreature->setFaction(FACTION_ESCORT_A_NEUTRAL_PASSIVE);
        else
            pCreature->setFaction(FACTION_ESCORT_H_NEUTRAL_PASSIVE);
    }
    return true;
}

    CreatureAI* GetAI(Creature* pCreature) const
{
    return new npc_akunoAI(pCreature);
}

    struct npc_akunoAI : public npc_escortAI
    {
        npc_akunoAI(Creature *c) : npc_escortAI(c) {}

        void WaypointReached(uint32 i)
        {
            Player* pPlayer = GetPlayerForEscort();

            if (!pPlayer)
                return;

            switch(i)
            {
                case 3:
                    me->SummonCreature(NPC_CABAL_SKRIMISHER,-2795.99f,5420.33f,-34.53f,0.0f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    me->SummonCreature(NPC_CABAL_SKRIMISHER,-2793.55f,5412.79f,-34.53f,0.0f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 25000);
                    break;
                case 11:
                    if (pPlayer && pPlayer->GetTypeId() == TYPEID_PLAYER)
                        pPlayer->GroupEventHappens(QUEST_ESCAPING_THE_TOMB,me);
                    break;
            }
        }

        void JustSummoned(Creature* summon)
        {
            summon->AI()->AttackStart(me);
        }
    };

};
/*######
## npc_letoll
######*/

enum
{
    SAY_LE_START                    = -1000511,
    SAY_LE_KEEP_SAFE                = -1000512,
    SAY_LE_NORTH                    = -1000513,
    SAY_LE_ARRIVE                   = -1000514,
    SAY_LE_BURIED                   = -1000515,
    SAY_LE_ALMOST                   = -1000516,
    SAY_LE_DRUM                     = -1000517,
    SAY_LE_DRUM_REPLY               = -1000518,
    SAY_LE_DISCOVERY                = -1000519,
    SAY_LE_DISCOVERY_REPLY          = -1000520,
    SAY_LE_NO_LEAVE                 = -1000521,
    SAY_LE_NO_LEAVE_REPLY1          = -1000522,
    SAY_LE_NO_LEAVE_REPLY2          = -1000523,
    SAY_LE_NO_LEAVE_REPLY3          = -1000524,
    SAY_LE_NO_LEAVE_REPLY4          = -1000525,
    SAY_LE_SHUT                     = -1000526,
    SAY_LE_REPLY_HEAR               = -1000527,
    SAY_LE_IN_YOUR_FACE             = -1000528,
    SAY_LE_HELP_HIM                 = -1000529,
    EMOTE_LE_PICK_UP                = -1000530,
    SAY_LE_THANKS                   = -1000531,

    QUEST_DIGGING_BONES             = 10922,

    NPC_RESEARCHER                  = 22464,
    NPC_BONE_SIFTER                 = 22466,

    MAX_RESEARCHER                  = 4
};

//Some details still missing from here, and will also have issues if followers evade for any reason.
class npc_letoll : public CreatureScript
{
public:
    npc_letoll() : CreatureScript("npc_letoll") { }
struct npc_letollAI : public npc_escortAI
{
    npc_letollAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_uiEventTimer = 5000;
        m_uiEventCount = 0;
    }

    std::list<Creature*> m_lResearchersList;

    uint32 m_uiEventTimer;
    uint32 m_uiEventCount;

    void Reset() {}

    //will make them follow, but will only work until they enter combat with any unit
    void SetFormation()
    {
        uint32 uiCount = 0;

        for(std::list<Creature*>::iterator itr = m_lResearchersList.begin(); itr != m_lResearchersList.end(); ++itr)
        {
            float fAngle = uiCount < MAX_RESEARCHER ? M_PI/MAX_RESEARCHER - (uiCount*2*M_PI/MAX_RESEARCHER) : 0.0f;

            if ((*itr)->isAlive() && !(*itr)->isInCombat())
                (*itr)->GetMotionMaster()->MoveFollow(me, 2.5f, fAngle);

            ++uiCount;
        }
    }

    Creature* GetAvailableResearcher(uint8 uiListNum)
    {
        if (!m_lResearchersList.empty())
        {
            uint8 uiNum = 1;

            for(std::list<Creature*>::iterator itr = m_lResearchersList.begin(); itr != m_lResearchersList.end(); ++itr)
            {
                if (uiListNum && uiListNum != uiNum)
                {
                    ++uiNum;
                    continue;
                }

                if ((*itr)->isAlive() && (*itr)->IsWithinDistInMap(me, 20.0f))
                    return (*itr);
            }
        }

        return NULL;
    }

    void JustStartedEscort()
    {
        m_uiEventTimer = 5000;
        m_uiEventCount = 0;

        m_lResearchersList.clear();

        GetCreatureListWithEntryInGrid(m_lResearchersList, me, NPC_RESEARCHER, 25.0f);

        if (!m_lResearchersList.empty())
            SetFormation();
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 0:
                if (Player* pPlayer = GetPlayerForEscort())
                    DoScriptText(SAY_LE_KEEP_SAFE, me, pPlayer);
                break;
            case 1:
                DoScriptText(SAY_LE_NORTH, me);
                break;
            case 10:
                DoScriptText(SAY_LE_ARRIVE, me);
                break;
            case 12:
                DoScriptText(SAY_LE_BURIED, me);
                SetEscortPaused(true);
                break;
            case 13:
                SetRun();
                break;
        }
    }

    void EnterCombat(Unit* pWho)
    {
        if (pWho->isInCombat() && pWho->GetTypeId() == TYPEID_UNIT && pWho->GetEntry() == NPC_BONE_SIFTER)
            DoScriptText(SAY_LE_HELP_HIM, me);
    }

    void JustSummoned(Creature* pSummoned)
    {
        Player* pPlayer = GetPlayerForEscort();

        if (pPlayer && pPlayer->isAlive())
            pSummoned->AI()->AttackStart(pPlayer);
        else
            pSummoned->AI()->AttackStart(me);
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
        {
            if (HasEscortState(STATE_ESCORT_PAUSED))
            {
                if (m_uiEventTimer < uiDiff)
                {
                    m_uiEventTimer = 7000;

                    switch(m_uiEventCount)
                    {
                        case 0:
                            DoScriptText(SAY_LE_ALMOST, me);
                            break;
                        case 1:
                            DoScriptText(SAY_LE_DRUM, me);
                            break;
                        case 2:
                            if (Creature* pResearcher = GetAvailableResearcher(0))
                                DoScriptText(SAY_LE_DRUM_REPLY, pResearcher);
                            break;
                        case 3:
                            DoScriptText(SAY_LE_DISCOVERY, me);
                            break;
                        case 4:
                            if (Creature* pResearcher = GetAvailableResearcher(0))
                                DoScriptText(SAY_LE_DISCOVERY_REPLY, pResearcher);
                            break;
                        case 5:
                            DoScriptText(SAY_LE_NO_LEAVE, me);
                            break;
                        case 6:
                            if (Creature* pResearcher = GetAvailableResearcher(1))
                                DoScriptText(SAY_LE_NO_LEAVE_REPLY1, pResearcher);
                            break;
                        case 7:
                            if (Creature* pResearcher = GetAvailableResearcher(2))
                                DoScriptText(SAY_LE_NO_LEAVE_REPLY2, pResearcher);
                            break;
                        case 8:
                            if (Creature* pResearcher = GetAvailableResearcher(3))
                                DoScriptText(SAY_LE_NO_LEAVE_REPLY3, pResearcher);
                            break;
                        case 9:
                            if (Creature* pResearcher = GetAvailableResearcher(4))
                                DoScriptText(SAY_LE_NO_LEAVE_REPLY4, pResearcher);
                            break;
                        case 10:
                            DoScriptText(SAY_LE_SHUT, me);
                            break;
                        case 11:
                            if (Creature* pResearcher = GetAvailableResearcher(0))
                                DoScriptText(SAY_LE_REPLY_HEAR, pResearcher);
                            break;
                        case 12:
                            DoScriptText(SAY_LE_IN_YOUR_FACE, me);
                            me->SummonCreature(NPC_BONE_SIFTER, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                            break;
                        case 13:
                            DoScriptText(EMOTE_LE_PICK_UP, me);

                            if (Player* pPlayer = GetPlayerForEscort())
                            {
                                DoScriptText(SAY_LE_THANKS, me, pPlayer);
                                pPlayer->GroupEventHappens(QUEST_DIGGING_BONES, me);
                            }

                            SetEscortPaused(false);
                            break;
                    }

                    ++m_uiEventCount;
                }
                else
                    m_uiEventTimer -= uiDiff;
            }

            return;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_letollAI(pCreature);
}

bool OnQuestAccept(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_DIGGING_BONES)
    {
        if (npc_escortAI* pEscortAI = CAST_AI(npc_letollAI, pCreature->AI()))
        {
            DoScriptText(SAY_LE_START, pCreature);
            pCreature->setFaction(FACTION_ESCORT_N_NEUTRAL_PASSIVE);

            pEscortAI->Start(false, false, pPlayer->GetGUID(), pQuest, true);
        }
    }

    return true;
}
};
/*######
## npc_mana_bomb_exp_trigger
######*/

enum manaBomb
{
    SAY_COUNT_1                 = -1000472,
    SAY_COUNT_2                 = -1000473,
    SAY_COUNT_3                 = -1000474,
    SAY_COUNT_4                 = -1000475,
    SAY_COUNT_5                 = -1000476,

    SPELL_MANA_BOMB_LIGHTNING   = 37843,
    SPELL_MANA_BOMB_EXPL        = 35513,

    NPC_MANA_BOMB_EXPL_TRIGGER  = 20767,
    NPC_MANA_BOMB_KILL_TRIGGER  = 21039
};

class npc_mana_bomb_exp_trigger : public CreatureScript
{
public:
    npc_mana_bomb_exp_trigger() : CreatureScript("npc_mana_bomb_exp_trigger") { }

struct npc_mana_bomb_exp_triggerAI : public ScriptedAI
{
    npc_mana_bomb_exp_triggerAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    GameObject* pManaBomb;

    bool m_bIsActivated;
    uint32 m_uiEventTimer;
    uint32 m_uiEventCounter;

    void Reset()
    {
        pManaBomb = NULL;
        m_bIsActivated = false;
        m_uiEventTimer = 1000;
        m_uiEventCounter = 0;
    }

    void DoTrigger(Player* pPlayer, GameObject* pGo)
    {
        if (m_bIsActivated)
            return;

        m_bIsActivated = true;

        pPlayer->KilledMonsterCredit(NPC_MANA_BOMB_KILL_TRIGGER, 0);

        pManaBomb = pGo;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_bIsActivated)
            return;

        if (m_uiEventTimer < uiDiff)
        {
            m_uiEventTimer = 1000;

            if (m_uiEventCounter < 10)
                me->CastSpell(me, SPELL_MANA_BOMB_LIGHTNING, false);

            switch(m_uiEventCounter)
            {
                case 5:
                    if (pManaBomb)
                        pManaBomb->SetGoState(GO_STATE_ACTIVE);

                    DoScriptText(SAY_COUNT_1, me);
                    break;
                case 6:
                    DoScriptText(SAY_COUNT_2, me);
                    break;
                case 7:
                    DoScriptText(SAY_COUNT_3, me);
                    break;
                case 8:
                    DoScriptText(SAY_COUNT_4, me);
                    break;
                case 9:
                    DoScriptText(SAY_COUNT_5, me);
                    break;
                case 10:
                    me->CastSpell(me, SPELL_MANA_BOMB_EXPL, false);
                    break;
                case 30:
                    if (pManaBomb)
                        pManaBomb->SetGoState(GO_STATE_READY);

                    Reset();
                    break;
            }

            ++m_uiEventCounter;
        }
        else
            m_uiEventTimer -= uiDiff;
    }
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_mana_bomb_exp_triggerAI(pCreature);
}
};

/*######
## go_mana_bomb
######*/
class go_mana_bomb : public GameObjectScript
{
public:
    go_mana_bomb() : GameObjectScript("go_mana_bomb") { }
bool GOHello(Player* pPlayer, GameObject* pGo)
{
    if (Creature* pCreature = GetClosestCreatureWithEntry(pGo, NPC_MANA_BOMB_EXPL_TRIGGER, INTERACTION_DISTANCE))
    {
        if (npc_mana_bomb_exp_trigger::npc_mana_bomb_exp_triggerAI* pBombAI = CAST_AI(npc_mana_bomb_exp_trigger::npc_mana_bomb_exp_triggerAI, pCreature->AI()))
            pBombAI->DoTrigger(pPlayer, pGo);
    }

    return true;
}
};

void AddSC_terokkar_forest()
{
    new mob_unkor_the_ruthless();
    new mob_infested_root_walker();
    new mob_rotting_forest_rager();
    new mob_netherweb_victim();
    new npc_floon();
    new npc_isla_starmane();
    new go_skull_pile();
    new npc_skywing();
    new npc_slim();
    new npc_akuno();
new npc_letoll();
new npc_mana_bomb_exp_trigger();
new go_mana_bomb();
}
