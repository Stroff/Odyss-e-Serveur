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
SDName: Hellfire_Peninsula
SD%Complete: 100
SDComment: Quest support: 9375, 9410, 9418, 10129, 10146, 10162, 10163, 10340, 10346, 10347, 10382 (Special flight paths), 10250
SDCategory: Hellfire Peninsula
EndScriptData */

/* ContentData
npc_aeranas
npc_ancestral_wolf
go_haaleshi_altar
npc_naladu
npc_tracy_proudwell
npc_trollbane
npc_wounded_blood_elf
npc_urtrak
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

/*######
## npc_aeranas
######*/

enum eAeranas
{
    SAY_SUMMON              = -1000138,
    SAY_FREE                = -1000139,

    FACTION_HOSTILE         = 16,
    FACTION_FRIENDLY        = 35,

    SPELL_ENVELOPING_WINDS  = 15535,
    SPELL_SHOCK             = 12553,

    C_AERANAS               = 17085
};

class npc_aeranas : public CreatureScript
{
public:
    npc_aeranas() : CreatureScript("npc_aeranas") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_aeranasAI (pCreature);
    }

struct npc_aeranasAI : public ScriptedAI
{
    npc_aeranasAI(Creature* c) : ScriptedAI(c) {}

    uint32 Faction_Timer;
    uint32 EnvelopingWinds_Timer;
    uint32 Shock_Timer;

    void Reset()
    {
        Faction_Timer = 8000;
        EnvelopingWinds_Timer = 9000;
        Shock_Timer = 5000;

        me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        me->setFaction(FACTION_FRIENDLY);

        DoScriptText(SAY_SUMMON, me);
    }

    void UpdateAI(const uint32 diff)
    {
        if (Faction_Timer)
        {
            if (Faction_Timer <= diff)
            {
                me->setFaction(FACTION_HOSTILE);
                Faction_Timer = 0;
            } else Faction_Timer -= diff;
        }

        if (!UpdateVictim())
            return;

            if (HealthBelowPct(30))
        {
            me->setFaction(FACTION_FRIENDLY);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop(true);
            DoScriptText(SAY_FREE, me);
            return;
        }

        if (Shock_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_SHOCK);
            Shock_Timer = 10000;
        } else Shock_Timer -= diff;

        if (EnvelopingWinds_Timer <= diff)
        {
            DoCast(me->getVictim(), SPELL_ENVELOPING_WINDS);
            EnvelopingWinds_Timer = 25000;
        } else EnvelopingWinds_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

};

/*######
## npc_ancestral_wolf
######*/

enum eAncestralWolf
{
    EMOTE_WOLF_LIFT_HEAD            = -1000496,
    EMOTE_WOLF_HOWL                 = -1000497,
    SAY_WOLF_WELCOME                = -1000498,

    SPELL_ANCESTRAL_WOLF_BUFF       = 29981,

    NPC_RYGA                        = 17123
};

class npc_ancestral_wolf : public CreatureScript
{
public:
    npc_ancestral_wolf() : CreatureScript("npc_ancestral_wolf") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ancestral_wolfAI(pCreature);
    }

struct npc_ancestral_wolfAI : public npc_escortAI
{
    npc_ancestral_wolfAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        if (pCreature->GetOwner() && pCreature->GetOwner()->GetTypeId() == TYPEID_PLAYER)
            Start(false, false, pCreature->GetOwner()->GetGUID());
        else
            sLog->outError("TRINITY: npc_ancestral_wolf can not obtain owner or owner is not a player.");

        pCreature->SetSpeed(MOVE_WALK, 1.5f);
        Reset();
    }

    Unit* pRyga;

    void Reset()
    {
        pRyga = NULL;
        DoCast(me, SPELL_ANCESTRAL_WOLF_BUFF, true);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (!pRyga && pWho->GetTypeId() == TYPEID_UNIT && pWho->GetEntry() == NPC_RYGA && me->IsWithinDistInMap(pWho, 15.0f))
            pRyga = pWho;

        npc_escortAI::MoveInLineOfSight(pWho);
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 0:
                DoScriptText(EMOTE_WOLF_LIFT_HEAD, me);
                break;
            case 2:
                DoScriptText(EMOTE_WOLF_HOWL, me);
                break;
            case 50:
                if (pRyga && pRyga->isAlive() && !pRyga->isInCombat())
                    DoScriptText(SAY_WOLF_WELCOME, pRyga);
                break;
        }
    }
};

};

/*######
## go_haaleshi_altar
######*/

class go_haaleshi_altar : public GameObjectScript
{
public:
    go_haaleshi_altar() : GameObjectScript("go_haaleshi_altar") { }

    bool OnGossipHello(Player* /*pPlayer*/, GameObject* pGo)
{
        pGo->SummonCreature(C_AERANAS,-1321.79f, 4043.80f, 116.24f, 1.25f, TEMPSUMMON_TIMED_DESPAWN, 180000);
    return false;
}

};

/*######
## npc_naladu
######*/

#define GOSSIP_NALADU_ITEM1 "Why don't you escape?"

enum eNaladu
{
    GOSSIP_TEXTID_NALADU1   = 9788
};

class npc_naladu : public CreatureScript
{
public:
    npc_naladu() : CreatureScript("npc_naladu") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_NALADU1, pCreature->GetGUID());

        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_NALADU_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

};

/*######
## npc_tracy_proudwell
######*/

#define GOSSIP_TEXT_REDEEM_MARKS        "I have marks to redeem!"
#define GOSSIP_TRACY_PROUDWELL_ITEM1    "I heard that your dog Fei Fei took Klatu's prayer beads..."
#define GOSSIP_TRACY_PROUDWELL_ITEM2    "<back>"

enum eTracy
{
    GOSSIP_TEXTID_TRACY_PROUDWELL1       = 10689,
    QUEST_DIGGING_FOR_PRAYER_BEADS       = 10916
};

class npc_tracy_proudwell : public CreatureScript
{
public:
    npc_tracy_proudwell() : CreatureScript("npc_tracy_proudwell") { }

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
        pPlayer->PlayerTalkClass->ClearMenus();
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TRACY_PROUDWELL_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_TRACY_PROUDWELL1, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_TRADE:
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());
            break;
    }

    return true;
}

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pCreature->isVendor())
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_REDEEM_MARKS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    if (pPlayer->GetQuestStatus(QUEST_DIGGING_FOR_PRAYER_BEADS) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TRACY_PROUDWELL_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

};

/*######
## npc_trollbane
######*/

#define GOSSIP_TROLLBANE_ITEM1      "Tell me of the Sons of Lothar."
#define GOSSIP_TROLLBANE_ITEM2      "<more>"
#define GOSSIP_TROLLBANE_ITEM3      "Tell me of your homeland."

enum eTrollbane
{
    GOSSIP_TEXTID_TROLLBANE1        = 9932,
    GOSSIP_TEXTID_TROLLBANE2        = 9933,
    GOSSIP_TEXTID_TROLLBANE3        = 8772
};

class npc_trollbane : public CreatureScript
{
public:
    npc_trollbane() : CreatureScript("npc_trollbane") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
        pPlayer->PlayerTalkClass->ClearMenus();
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TROLLBANE_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_TROLLBANE1, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_TROLLBANE2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_TROLLBANE3, pCreature->GetGUID());
            break;
    }

    return true;
}

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TROLLBANE_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TROLLBANE_ITEM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }

};

/*######
## npc_wounded_blood_elf
######*/

enum eWoundedBloodElf
{
    SAY_ELF_START               = -1000117,
    SAY_ELF_SUMMON1             = -1000118,
    SAY_ELF_RESTING             = -1000119,
    SAY_ELF_SUMMON2             = -1000120,
    SAY_ELF_COMPLETE            = -1000121,
    SAY_ELF_AGGRO               = -1000122,

    QUEST_ROAD_TO_FALCON_WATCH  = 9375
};

class npc_wounded_blood_elf : public CreatureScript
{
public:
    npc_wounded_blood_elf() : CreatureScript("npc_wounded_blood_elf") { }

    bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_ROAD_TO_FALCON_WATCH)
        {
            if (npc_escortAI* pEscortAI = CAST_AI(npc_wounded_blood_elf::npc_wounded_blood_elfAI, pCreature->AI()))
                pEscortAI->Start(true, false, pPlayer->GetGUID());

            // Change faction so mobs attack
            pCreature->setFaction(775);
        }

        return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_wounded_blood_elfAI(pCreature);
    }

struct npc_wounded_blood_elfAI : public npc_escortAI
{
    npc_wounded_blood_elfAI(Creature *c) : npc_escortAI(c) {}

    void WaypointReached(uint32 i)
    {
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
            return;

        switch (i)
        {
        case 0:
            DoScriptText(SAY_ELF_START, me, pPlayer);
            break;
        case 9:
            DoScriptText(SAY_ELF_SUMMON1, me, pPlayer);
            // Spawn two Haal'eshi Talonguard
            DoSpawnCreature(16967, -15, -15, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            DoSpawnCreature(16967, -17, -17, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            break;
        case 13:
            DoScriptText(SAY_ELF_RESTING, me, pPlayer);
            break;
        case 14:
            DoScriptText(SAY_ELF_SUMMON2, me, pPlayer);
            // Spawn two Haal'eshi Windwalker
            DoSpawnCreature(16966, -15, -15, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            DoSpawnCreature(16966, -17, -17, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            break;
        case 27:
            DoScriptText(SAY_ELF_COMPLETE, me, pPlayer);
            // Award quest credit
            pPlayer->GroupEventHappens(QUEST_ROAD_TO_FALCON_WATCH,me);
            break;
        }
    }

    void Reset() { }

    void EnterCombat(Unit* /*who*/)
    {
        if (HasEscortState(STATE_ESCORT_ESCORTING))
            DoScriptText(SAY_ELF_AGGRO, me);
    }

    void JustSummoned(Creature* summoned)
    {
        summoned->AI()->AttackStart(me);
    }
};

};

/*######
## npc_fel_guard_hound
######*/

enum eFelGuard
{
    SPELL_SUMMON_POO                              = 37688,

    NPC_DERANGED_HELBOAR                          = 16863
};

class npc_fel_guard_hound : public CreatureScript
{
public:
    npc_fel_guard_hound() : CreatureScript("npc_fel_guard_hound") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_fel_guard_houndAI(pCreature);
    }

struct npc_fel_guard_houndAI : public ScriptedAI
{
    npc_fel_guard_houndAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    uint32 uiCheckTimer;
    uint64 uiHelboarGUID;

    void Reset()
    {
        uiCheckTimer = 5000; //check for creature every 5 sec
        uiHelboarGUID = 0;
    }

    void MovementInform(uint32 uiType, uint32 uiId)
    {
        if (uiType != POINT_MOTION_TYPE || uiId != 1)
            return;

        if (Creature* pHelboar = me->GetCreature(*me,uiHelboarGUID))
        {
            pHelboar->RemoveCorpse();
            DoCast(SPELL_SUMMON_POO);

            if (Player* pOwner = me->GetCharmerOrOwnerPlayerOrPlayerItself())
                me->GetMotionMaster()->MoveFollow(pOwner,0.0f,0.0f);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (uiCheckTimer <= uiDiff)
        {
            if (Creature* pHelboar = me->FindNearestCreature(NPC_DERANGED_HELBOAR, 10.0f, false))
            {
                if (pHelboar->GetGUID() != uiHelboarGUID && me->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE && !me->FindCurrentSpellBySpellId(SPELL_SUMMON_POO))
                {
                    uiHelboarGUID = pHelboar->GetGUID();
                    me->GetMotionMaster()->MovePoint(1,pHelboar->GetPositionX(),pHelboar->GetPositionY(),pHelboar->GetPositionZ());
                }
            }
            uiCheckTimer = 5000;
        }else uiCheckTimer -= uiDiff;

        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

};

/*######
## npc_demoniac_scryer
######*/

#define GOSSIP_ITEM_ATTUNE          "Yes, Scryer. You may possess me."

enum DemoniacScryer
{
    GOSSIP_TEXTID_PROTECT           = 10659,
    GOSSIP_TEXTID_ATTUNED           = 10643,

    QUEST_DEMONIAC                  = 10838,
    NPC_HELLFIRE_WARDLING           = 22259,
    NPC_BUTTRESS                    = 22267,                //the 4x nodes
    NPC_SPAWNER                     = 22260,                //just a dummy, not used

    MAX_BUTTRESS                    = 4,
    TIME_TOTAL                      = MINUTE*10*IN_MILLISECONDS,

    SPELL_SUMMONED_DEMON            = 7741,                 //visual spawn-in for demon
    SPELL_DEMONIAC_VISITATION       = 38708,                //create item

    SPELL_BUTTRESS_APPERANCE        = 38719,                //visual on 4x bunnies + the flying ones
    SPELL_SUCKER_CHANNEL            = 38721,                //channel to the 4x nodes
    SPELL_SUCKER_DESPAWN_MOB        = 38691
};

#define M_PI_F                        3.14159265358979323846

//script is basic support, details like end event are not implemented

class npc_demoniac_scryer : public CreatureScript
{
public:
    npc_demoniac_scryer() : CreatureScript("npc_demoniac_scryer") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_demoniac_scryerAI(pCreature);
    }

struct npc_demoniac_scryerAI : public ScriptedAI
{
    npc_demoniac_scryerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        me->SetReactState(REACT_PASSIVE) ;
        m_bIsComplete = false;
        m_uiSpawnDemonTimer = 15000;
        m_uiSpawnButtressTimer = 20000;
        m_uiButtressCount = 0;
    }

    bool m_bIsComplete;

    uint32 m_uiSpawnDemonTimer;
    uint32 m_uiSpawnButtressTimer;
    uint32 m_uiButtressCount;

    void DoSpawnButtress()
    {
        ++m_uiButtressCount;

        float fAngle;

        switch(m_uiButtressCount)
        {
            case 1: fAngle = 0.0f; break;
            case 2: fAngle = M_PI_F+M_PI_F/2; break;
            case 3: fAngle = M_PI_F/2; break;
            case 4: fAngle = M_PI_F; break;
        }

        float fX, fY;
        me->GetNearPoint2D(fX, fY, 5.0f, fAngle);

        float fZ_Ground = me->GetMap()->GetHeight(fX, fY, MAX_HEIGHT);

        uint32 uiTime = TIME_TOTAL - (m_uiSpawnButtressTimer * m_uiButtressCount);
        me->SummonCreature(NPC_BUTTRESS, fX, fY, fZ_Ground, me->GetAngle(fX, fY), TEMPSUMMON_TIMED_DESPAWN, uiTime);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_HELLFIRE_WARDLING)
        {
            pSummoned->CastSpell(pSummoned, SPELL_SUMMONED_DEMON, false);
            pSummoned->AI()->AttackStart(me);
        }
        else
        {
            if (pSummoned->GetEntry() == NPC_BUTTRESS)
            {
                pSummoned->CastSpell(pSummoned, SPELL_BUTTRESS_APPERANCE, false);
                pSummoned->CastSpell(me, SPELL_SUCKER_CHANNEL, true);
            }
        }
    }

    void SpellHitTarget(Unit* pTarget, const SpellEntry* pSpell)
    {
        if (pTarget->GetEntry() == NPC_HELLFIRE_WARDLING && pSpell->Id == SPELL_SUCKER_DESPAWN_MOB)
            ((Creature*)pTarget)->ForcedDespawn();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bIsComplete)
            return;

        if (m_uiSpawnButtressTimer <= uiDiff)
        {
            if (m_uiButtressCount >= MAX_BUTTRESS)
            {
                me->CastSpell(me, SPELL_SUCKER_DESPAWN_MOB, false);

                if (me->isInCombat())
                {
                    me->DeleteThreatList();
                    me->CombatStop();
                }

                m_bIsComplete = true;
                return;
            }

            m_uiSpawnButtressTimer = 15000;
            DoSpawnButtress();
        }
        else
            m_uiSpawnButtressTimer -= uiDiff;

        if (m_uiSpawnDemonTimer <= uiDiff)
        {
            me->SummonCreature(NPC_HELLFIRE_WARDLING, me->GetPositionX()+urand(-10, 10), me->GetPositionY()+urand(-10, 10), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
            m_uiSpawnDemonTimer = 20000;
        }
        else
            m_uiSpawnDemonTimer -= uiDiff;

        if(!UpdateVictim())
            return ;
    }
};

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (npc_demoniac_scryerAI* pScryerAI = dynamic_cast<npc_demoniac_scryerAI*>(pCreature->AI()))
    {
        if (pScryerAI->m_bIsComplete)
        {
            if (pPlayer->GetQuestStatus(QUEST_DEMONIAC) == QUEST_STATUS_INCOMPLETE)
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ATTUNE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ATTUNED, pCreature->GetGUID());
            return true;
        }
    }

    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_PROTECT, pCreature->GetGUID());
    return true;
}

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        pPlayer->CastSpell(pPlayer, SPELL_DEMONIAC_VISITATION, true);
    }

    return true;
}
};

class npc_urtrak : public CreatureScript
{
public:
    npc_urtrak() : CreatureScript("npc_urtrak") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_urtrakAI(pCreature);
    }

struct npc_urtrakAI : public ScriptedAI
{
    npc_urtrakAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if(damage >= me->GetHealth())
        {
            std::list<HostileReference*>::const_iterator i = me->getThreatManager().getThreatList().begin();
            for (i = me->getThreatManager().getThreatList().begin(); i!= me->getThreatManager().getThreatList().end(); ++i)
            {
                if (Unit* pUnit = Unit::GetUnit((*me), (*i)->getUnitGuid()))
                {
                    if (pUnit->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (pUnit->ToPlayer()->GetQuestStatus(10250) == QUEST_STATUS_INCOMPLETE)
                        {
                            pUnit->ToPlayer()->CompleteQuest(10250);
                        }
                    }
                }
            }
        }
    }
};

};

void AddSC_hellfire_peninsula()
{
    new npc_aeranas();
    new npc_ancestral_wolf();
    new go_haaleshi_altar();
    new npc_naladu();
    new npc_tracy_proudwell();
    new npc_trollbane();
    new npc_wounded_blood_elf();
    new npc_fel_guard_hound();
new npc_demoniac_scryer();
new npc_urtrak();
}
