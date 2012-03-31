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
SDName: Dustwallow_Marsh
SD%Complete: 95
SDComment: Quest support: 11180, 558, 11126, 11142, 11180. Vendor Nat Pagle
SDCategory: Dustwallow Marsh
EndScriptData */

/* ContentData
mobs_risen_husk_spirit
npc_restless_apparition
npc_deserter_agitator
npc_lady_jaina_proudmoore
npc_nat_pagle
npc_private_hendel
npc_cassa_crimsonwing - handled by npc_taxi
EndContentData */

#include "ScriptPCH.h"
#include "ScriptedEscortAI.h"

/*######
## mobs_risen_husk_spirit
######*/

enum eHuskSpirit
{
    QUEST_WHATS_HAUNTING_WITCH_HILL     = 11180,

    SPELL_SUMMON_RESTLESS_APPARITION    = 42511,
    SPELL_CONSUME_FLESH                 = 37933,               //Risen Husk
    SPELL_INTANGIBLE_PRESENCE           = 43127,               //Risen Spirit

    NPC_RISEN_HUSK                      = 23555,
    NPC_RISEN_SPIRIT                    = 23554,
    NPC_RESTLESS_APPARITION             = 23861
};

class mobs_risen_husk_spirit : public CreatureScript
{
public:
    mobs_risen_husk_spirit() : CreatureScript("mobs_risen_husk_spirit") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mobs_risen_husk_spiritAI (pCreature);
    }

struct mobs_risen_husk_spiritAI : public ScriptedAI
{
    mobs_risen_husk_spiritAI(Creature *c) : ScriptedAI(c) {}

    uint32 m_uiConsumeFlesh_Timer;
    uint32 m_uiIntangiblePresence_Timer;

    void Reset()
    {
        m_uiConsumeFlesh_Timer = 10000;
        m_uiIntangiblePresence_Timer = 5000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;

        if (m_uiConsumeFlesh_Timer <= uiDiff)
        {
            if (me->GetEntry() == NPC_RISEN_HUSK)
                DoCast(me->getVictim(), SPELL_CONSUME_FLESH);

            m_uiConsumeFlesh_Timer = 15000;
        }
        else
            m_uiConsumeFlesh_Timer -= uiDiff;

        if (m_uiIntangiblePresence_Timer <= uiDiff)
        {
            if (me->GetEntry() == NPC_RISEN_SPIRIT)
                DoCast(me->getVictim(), SPELL_INTANGIBLE_PRESENCE);

            m_uiIntangiblePresence_Timer = 20000;
        }
        else
            m_uiIntangiblePresence_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* pKiller)
    {
        if (pKiller->GetTypeId() == TYPEID_PLAYER)
            if (CAST_PLR(pKiller)->GetQuestStatus(QUEST_WHATS_HAUNTING_WITCH_HILL) == QUEST_STATUS_INCOMPLETE)
            {
                DoCast(pKiller, SPELL_SUMMON_RESTLESS_APPARITION, true);
                CAST_PLR(pKiller)->KilledMonsterCredit(NPC_RESTLESS_APPARITION,0);
            }
    }
};

};


/*######
## npc_restless_apparition
######*/

enum eRestlessApparition
{
    SAY_RESTLESS_1      = -1000469,
    SAY_RESTLESS_2      = -1000470,
    SAY_RESTLESS_3      = -1000471
};

class npc_restless_apparition : public CreatureScript
{
public:
    npc_restless_apparition() : CreatureScript("npc_restless_apparition") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_restless_apparitionAI (pCreature);
    }

struct npc_restless_apparitionAI : public ScriptedAI
{
    npc_restless_apparitionAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset()
    {
        DoScriptText(RAND(SAY_RESTLESS_1,SAY_RESTLESS_2,SAY_RESTLESS_3), me);
    }
};

};

/*######
## npc_deserter_agitator
######*/

enum eDeserter
{
    QUEST_TRAITORS_AMONG_US = 11126,
    NPC_THERAMORE_DESERTER                       = 23602,
};

const Position DeserterDisappearPos = {-3609.03f, -4332.91f, 9.39354f, 3.73862f};

#define GOSSIP_ITEM_DESERTER "Your propaganda wont`t work on me. Spout your treasonous filth elsewhere traitor!"

class npc_deserter_agitator : public CreatureScript
{
public:
    npc_deserter_agitator() : CreatureScript("npc_deserter_agitator") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->GetQuestStatus(QUEST_TRAITORS_AMONG_US) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DESERTER, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INFO);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        if (uiAction == GOSSIP_SENDER_INFO)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            switch (urand(0,1))
            {
                case 0:
                    pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    pCreature->setFaction(14);
                    pCreature->AI()->AttackStart(pPlayer);
                    break;
                case 1:
                    pPlayer->KilledMonsterCredit(NPC_THERAMORE_DESERTER, 0);
                    pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    pCreature->SetSpeed(MOVE_RUN, pCreature->GetSpeedRate(MOVE_RUN), true);
                    pCreature->setFaction(35);
                    pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE | UNIT_FLAG_NON_ATTACKABLE);
                    pCreature->SetReactState(REACT_PASSIVE);
                    pCreature->GetMotionMaster()->MovePoint(1, DeserterDisappearPos);
                    break;
            }
        }

        return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_deserter_agitatorAI(pCreature);
    }

    struct npc_deserter_agitatorAI : public ScriptedAI
    {
        npc_deserter_agitatorAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        void Reset()
        {
            me->RestoreFaction();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE | UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        void MovementInform(uint32 uiType, uint32 uiId)
        {
            if (uiType != POINT_MOTION_TYPE)
                return;

            if (uiId == 1)
                me->DisappearAndDie();
        }
    };
};

/*######
## npc_deserter_agitator
######*/

enum eTheramoreGuard
{
    SAY_QUEST1                                   = -1000641,
    SAY_QUEST2                                   = -1000642,
    SAY_QUEST3                                   = -1000643,
    SAY_QUEST4                                   = -1000644,
    SAY_QUEST5                                   = -1000645,
    SAY_QUEST6                                   = -1000646,
    SAY_QUEST7                                   = -1000647,
    SAY_QUEST8                                   = -1000648,
    SAY_QUEST9                                   = -1000649,

    QUEST_DISCREDITING_THE_DESERTERS             = 11133,

    NPC_THERAMORE_GUARD                          = 4979,

    SPELL_DOCTORED_LEAFLET                       = 42725,
    SPELL_PROPAGANDIZED                          = 42246,
};

#define GOSSIP_ITEM_THERAMORE_GUARD "You look like an intelligent person. Why don't you read one of these leaflets and give it some thought?"

class npc_theramore_guard : public CreatureScript
{
public:
    npc_theramore_guard() : CreatureScript("npc_theramore_guard") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pPlayer->GetQuestStatus(QUEST_DISCREDITING_THE_DESERTERS) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_THERAMORE_GUARD, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INFO);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();

        if (uiAction == GOSSIP_SENDER_INFO)
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->KilledMonsterCredit(NPC_THERAMORE_GUARD, 0);
            DoScriptText(SAY_QUEST1, pCreature);
            pCreature->CastSpell(pCreature, SPELL_DOCTORED_LEAFLET, false);
            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            CAST_AI(npc_theramore_guard::npc_theramore_guardAI, pCreature->AI())->uiYellTimer = 4000;
            CAST_AI(npc_theramore_guard::npc_theramore_guardAI, pCreature->AI())->bYellTimer = true;
        }

        return true;
    }

    CreatureAI *GetAI(Creature *pCreature) const
    {
        return new npc_theramore_guardAI(pCreature);
    }

    struct npc_theramore_guardAI : public ScriptedAI
    {
        npc_theramore_guardAI(Creature *pCreature) : ScriptedAI(pCreature) { }

        uint32 uiYellTimer;
        uint32 uiStep;
        bool bYellTimer;

        void Reset()
        {
            bYellTimer = false;
            uiStep = 0;
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!me->HasAura(SPELL_PROPAGANDIZED))
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

            if (bYellTimer && uiYellTimer <= uiDiff)
            {
                switch(uiStep)
                {
                    case 0:
                        DoScriptText(RAND(SAY_QUEST2, SAY_QUEST3, SAY_QUEST4, SAY_QUEST5, SAY_QUEST6), me);
                        uiYellTimer = 3000;
                        ++uiStep;
                        break;
                    case 1:
                        DoScriptText(RAND(SAY_QUEST7, SAY_QUEST8, SAY_QUEST9), me);
                        me->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
                        uiStep = 0;
                        bYellTimer = false;
                        break;
                }
            }
            else
                uiYellTimer -= uiDiff;
        }
    };
};

/*######
## npc_lady_jaina_proudmoore
######*/

enum eLadyJaina
{
    QUEST_JAINAS_AUTOGRAPH = 558,
    SPELL_JAINAS_AUTOGRAPH = 23122
};

#define GOSSIP_ITEM_JAINA "I know this is rather silly but i have a young ward who is a bit shy and would like your autograph."

class npc_lady_jaina_proudmoore : public CreatureScript
{
public:
    npc_lady_jaina_proudmoore() : CreatureScript("npc_lady_jaina_proudmoore") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_SENDER_INFO)
        {
            pPlayer->SEND_GOSSIP_MENU(7012, pCreature->GetGUID());
            pPlayer->CastSpell(pPlayer, SPELL_JAINAS_AUTOGRAPH, false);
        }
        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        if (pPlayer->GetQuestStatus(QUEST_JAINAS_AUTOGRAPH) == QUEST_STATUS_INCOMPLETE)
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_JAINA, GOSSIP_SENDER_MAIN, GOSSIP_SENDER_INFO);

        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

        return true;
    }

};


/*######
## npc_nat_pagle
######*/

enum eNatPagle
{
    QUEST_NATS_MEASURING_TAPE = 8227
};

class npc_nat_pagle : public CreatureScript
{
public:
    npc_nat_pagle() : CreatureScript("npc_nat_pagle") { }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == GOSSIP_ACTION_TRADE)
            pPlayer->SEND_VENDORLIST(pCreature->GetGUID());

        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if (pCreature->isQuestGiver())
            pPlayer->PrepareQuestMenu(pCreature->GetGUID());

        if (pCreature->isVendor() && pPlayer->GetQuestRewardStatus(QUEST_NATS_MEASURING_TAPE))
        {
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
            pPlayer->SEND_GOSSIP_MENU(7640, pCreature->GetGUID());
        }
        else
            pPlayer->SEND_GOSSIP_MENU(7638, pCreature->GetGUID());

        return true;
    }

};


/*######
## npc_private_hendel
######*/

enum eHendel
{
    // looks like all this text ids are wrong.
    SAY_PROGRESS_1_TER          = -1000411, // signed for 3568
    SAY_PROGRESS_2_HEN          = -1000412, // signed for 3568
    SAY_PROGRESS_3_TER          = -1000413,
    SAY_PROGRESS_4_TER          = -1000414,
    EMOTE_SURRENDER             = -1000415,

    QUEST_MISSING_DIPLO_PT16    = 1324,
    FACTION_HOSTILE             = 168,                      //guessed, may be different

    NPC_SENTRY                  = 5184,                     //helps hendel
    NPC_JAINA                   = 4968,                     //appears once hendel gives up
    NPC_TERVOSH                 = 4967
};

//TODO: develop this further, end event not created
class npc_private_hendel : public CreatureScript
{
public:
    npc_private_hendel() : CreatureScript("npc_private_hendel") { }

    bool OnQuestAccept(Player* /*pPlayer*/, Creature* pCreature, const Quest* pQuest)
    {
        if (pQuest->GetQuestId() == QUEST_MISSING_DIPLO_PT16)
            pCreature->setFaction(FACTION_HOSTILE);

        return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_private_hendelAI(pCreature);
    }

struct npc_private_hendelAI : public ScriptedAI
{
    npc_private_hendelAI(Creature* pCreature) : ScriptedAI(pCreature) { }

    void Reset()
    {
        me->RestoreFaction();
    }

    void AttackedBy(Unit* pAttacker)
    {
        if (me->getVictim())
            return;

        if (me->IsFriendlyTo(pAttacker))
            return;

        AttackStart(pAttacker);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
            if (uiDamage > me->GetHealth() || me->HealthBelowPctDamaged(20, uiDamage))
        {
            uiDamage = 0;

            if (Player* pPlayer = pDoneBy->GetCharmerOrOwnerPlayerOrPlayerItself())
                pPlayer->GroupEventHappens(QUEST_MISSING_DIPLO_PT16, me);

            DoScriptText(EMOTE_SURRENDER, me);
            EnterEvadeMode();
        }
    }
};

};



/*######
## npc_zelfrax
######*/

const Position MovePosition = {-2967.030f,-3872.1799f,35.620f, 0.0f};

enum eZelfrax
{
    SAY_ZELFRAX     = -1000472,
    SAY_ZELFRAX_2   = -1000473
};

class npc_zelfrax : public CreatureScript
{
public:
    npc_zelfrax() : CreatureScript("npc_zelfrax") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_zelfraxAI(pCreature);
    }

struct npc_zelfraxAI : public ScriptedAI
{
    npc_zelfraxAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        MoveToDock();
    }

    void AttackStart(Unit* pWho)
    {
        if (!pWho)
            return;

        if (me->Attack(pWho, true))
        {
            me->SetInCombatWith(pWho);
            pWho->SetInCombatWith(me);

            if (IsCombatMovementAllowed())
                me->GetMotionMaster()->MoveChase(pWho);
        }
    }

    void MovementInform(uint32 uiType, uint32 /*uiId*/)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        me->SetHomePosition(me->GetPositionX(),me->GetPositionY(),me->GetPositionZ(),me->GetOrientation());
        me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_OOC_NOT_ATTACKABLE);
        SetCombatMovement(true);

        if (me->isInCombat())
            if (Unit* pUnit = me->getVictim())
                me->GetMotionMaster()->MoveChase(pUnit);
    }

    void MoveToDock()
    {
        SetCombatMovement(false);
        me->GetMotionMaster()->MovePoint(0,MovePosition);
        DoScriptText(SAY_ZELFRAX,me);
        DoScriptText(SAY_ZELFRAX_2,me);
    }

    void UpdateAI(uint32 const /*uiDiff*/)
    {
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

};

/*######
## npc_morokk
######*/

enum Morok
{
    SAY_MOR_CHALLENGE               = -1000499,
    SAY_MOR_SCARED                  = -1000500,

    QUEST_CHALLENGE_MOROKK          = 1173,

    FACTION_MOR_HOSTILE             = 168,
    FACTION_MOR_RUNNING             = 35
};

class npc_morokk : public CreatureScript
{
public:
    npc_morokk() : CreatureScript("npc_morokk") { }

bool OnQuestAccept(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_CHALLENGE_MOROKK)
    {
        if (npc_morokkAI* pEscortAI = dynamic_cast<npc_morokkAI*>(pCreature->AI()))
            pEscortAI->Start(true, true, pPlayer->GetGUID(), pQuest);

        return true;
    }

    return false;
}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_morokkAI (pCreature);
    }

struct npc_morokkAI : public npc_escortAI
{
    npc_morokkAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_bIsSuccess = false;
        Reset();
    }

    bool m_bIsSuccess;

    void Reset() {}

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 0:
                SetEscortPaused(true);
                break;
            case 1:
                if (m_bIsSuccess)
                    DoScriptText(SAY_MOR_SCARED, me);
                else
                {
                    me->setDeathState(JUST_DIED);
                    me->Respawn();
                }
                break;
        }
    }

    void AttackedBy(Unit* pAttacker)
    {
        if (me->getVictim())
            return;

        if (me->IsFriendlyTo(pAttacker))
            return;

        AttackStart(pAttacker);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (HasEscortState(STATE_ESCORT_ESCORTING))
        {
            if (HealthBelowPct(30))
            {
                if (Player* pPlayer = GetPlayerForEscort())
                    pPlayer->GroupEventHappens(QUEST_CHALLENGE_MOROKK, me);

                me->setFaction(FACTION_MOR_RUNNING);

                m_bIsSuccess = true;
                EnterEvadeMode();

                uiDamage = 0;
            }
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
        {
            if (HasEscortState(STATE_ESCORT_PAUSED))
            {
                if (Player* pPlayer = GetPlayerForEscort())
                {
                    m_bIsSuccess = false;
                    DoScriptText(SAY_MOR_CHALLENGE, me, pPlayer);
                    me->setFaction(FACTION_MOR_HOSTILE);
                    AttackStart(pPlayer);
                }

                SetEscortPaused(false);
            }

            return;
        }

        DoMeleeAttackIfReady();
    }
};
};

/*######
## npc_ogron
######*/

enum Orgron
{
    SAY_OGR_START                       = -1000452,
    SAY_OGR_SPOT                        = -1000453,
    SAY_OGR_RET_WHAT                    = -1000454,
    SAY_OGR_RET_SWEAR                   = -1000455,
    SAY_OGR_REPLY_RET                   = -1000456,
    SAY_OGR_RET_TAKEN                   = -1000457,
    SAY_OGR_TELL_FIRE                   = -1000458,
    SAY_OGR_RET_NOCLOSER                = -1000459,
    SAY_OGR_RET_NOFIRE                  = -1000460,
    SAY_OGR_RET_HEAR                    = -1000461,
    SAY_OGR_CAL_FOUND                   = -1000462,
    SAY_OGR_CAL_MERCY                   = -1000463,
    SAY_OGR_HALL_GLAD                   = -1000464,
    EMOTE_OGR_RET_ARROW                 = -1000465,
    SAY_OGR_RET_ARROW                   = -1000466,
    SAY_OGR_CAL_CLEANUP                 = -1000467,
    SAY_OGR_NODIE                       = -1000468,
    SAY_OGR_SURVIVE                     = -1000469,
    SAY_OGR_RET_LUCKY                   = -1000470,
    SAY_OGR_THANKS                      = -1000471,

    QUEST_QUESTIONING                   = 1273,

    FACTION_GENERIC_FRIENDLY            = 35,
    FACTION_THER_HOSTILE                = 151,

    NPC_REETHE                          = 4980,
    NPC_CALDWELL                        = 5046,
    NPC_HALLAN                          = 5045,
    NPC_SKIRMISHER                      = 5044,

    SPELL_FAKE_SHOT                     = 7105,

    PHASE_INTRO                         = 0,
    PHASE_GUESTS                        = 1,
    PHASE_FIGHT                         = 2,
    PHASE_COMPLETE                      = 3
};

static float m_afSpawn[] = {-3383.501953f, -3203.383301f, 36.149f};
static float m_afMoveTo[] = {-3371.414795f, -3212.179932f, 34.210f};

class npc_ogron : public CreatureScript
{
public:
    npc_ogron() : CreatureScript("npc_ogron") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ogronAI (pCreature);
    }
struct npc_ogronAI : public npc_escortAI
{
    npc_ogronAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        lCreatureList.clear();
        m_uiPhase = 0;
        m_uiPhaseCounter = 0;
        Reset();
    }

    std::list<Creature*> lCreatureList;

    uint32 m_uiPhase;
    uint32 m_uiPhaseCounter;
    uint32 m_uiGlobalTimer;

    void Reset()
    {
        m_uiGlobalTimer = 5000;

        if (HasEscortState(STATE_ESCORT_PAUSED) && m_uiPhase == PHASE_FIGHT)
            m_uiPhase = PHASE_COMPLETE;

        if (!HasEscortState(STATE_ESCORT_ESCORTING))
        {
            lCreatureList.clear();
            m_uiPhase = 0;
            m_uiPhaseCounter = 0;
        }
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (HasEscortState(STATE_ESCORT_ESCORTING) && pWho->GetEntry() == NPC_REETHE && lCreatureList.empty())
            lCreatureList.push_back((Creature*)pWho);

        npc_escortAI::MoveInLineOfSight(pWho);
    }

    Creature* GetCreature(uint32 uiCreatureEntry)
    {
        if (!lCreatureList.empty())
        {
            for(std::list<Creature*>::iterator itr = lCreatureList.begin(); itr != lCreatureList.end(); ++itr)
            {
                if ((*itr)->GetEntry() == uiCreatureEntry && (*itr)->isAlive())
                    return (*itr);
            }
        }

        return NULL;
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 9:
                DoScriptText(SAY_OGR_SPOT, me);
                break;
            case 10:
                if (Creature* pReethe = GetCreature(NPC_REETHE))
                    DoScriptText(SAY_OGR_RET_WHAT, pReethe);
                break;
            case 11:
                SetEscortPaused(true);
                break;
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        lCreatureList.push_back(pSummoned);

        pSummoned->setFaction(FACTION_GENERIC_FRIENDLY);

        if (pSummoned->GetEntry() == NPC_CALDWELL)
            pSummoned->GetMotionMaster()->MovePoint(0, m_afMoveTo[0], m_afMoveTo[1], m_afMoveTo[2]);
        else
        {
            if (Creature* pCaldwell = GetCreature(NPC_CALDWELL))
            {
                //will this conversion work without compile warning/error?
                size_t iSize = lCreatureList.size();
                pSummoned->GetMotionMaster()->MoveFollow(pCaldwell, 0.5f, (M_PI/2)*(int)iSize);
            }
        }
    }

    void DoStartAttackMe()
    {
        if (!lCreatureList.empty())
        {
            for(std::list<Creature*>::iterator itr = lCreatureList.begin(); itr != lCreatureList.end(); ++itr)
            {
                if ((*itr)->GetEntry() == NPC_REETHE)
                    continue;

                if ((*itr)->isAlive())
                {
                    (*itr)->setFaction(FACTION_THER_HOSTILE);
                    (*itr)->AI()->AttackStart(me);
                }
            }
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
        {
            if (HasEscortState(STATE_ESCORT_PAUSED))
            {
                if (m_uiGlobalTimer < uiDiff)
                {
                    if (m_uiPhase == PHASE_FIGHT)
                        m_uiPhase = PHASE_COMPLETE;

                    m_uiGlobalTimer = 5000;

                    switch(m_uiPhase)
                    {
                        case PHASE_INTRO:
                        {
                            switch(m_uiPhaseCounter)
                            {
                                case 0:
                                    if (Creature* pReethe = GetCreature(NPC_REETHE))
                                        DoScriptText(SAY_OGR_RET_SWEAR, pReethe);
                                    break;
                                case 1:
                                    DoScriptText(SAY_OGR_REPLY_RET, me);
                                    break;
                                case 2:
                                    if (Creature* pReethe = GetCreature(NPC_REETHE))
                                        DoScriptText(SAY_OGR_RET_TAKEN, pReethe);
                                    break;
                                case 3:
                                    DoScriptText(SAY_OGR_TELL_FIRE, me);
                                    if (Creature* pReethe = GetCreature(NPC_REETHE))
                                        DoScriptText(SAY_OGR_RET_NOCLOSER, pReethe);
                                    break;
                                case 4:
                                    if (Creature* pReethe = GetCreature(NPC_REETHE))
                                        DoScriptText(SAY_OGR_RET_NOFIRE, pReethe);
                                    break;
                                case 5:
                                    if (Creature* pReethe = GetCreature(NPC_REETHE))
                                        DoScriptText(SAY_OGR_RET_HEAR, pReethe);

                                    me->SummonCreature(NPC_CALDWELL, m_afSpawn[0], m_afSpawn[1], m_afSpawn[2], 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                                    me->SummonCreature(NPC_HALLAN, m_afSpawn[0], m_afSpawn[1], m_afSpawn[2], 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                                    me->SummonCreature(NPC_SKIRMISHER, m_afSpawn[0], m_afSpawn[1], m_afSpawn[2], 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);
                                    me->SummonCreature(NPC_SKIRMISHER, m_afSpawn[0], m_afSpawn[1], m_afSpawn[2], 0.0f, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 300000);

                                    m_uiPhase = PHASE_GUESTS;
                                    break;
                            }
                            break;
                        }
                        case PHASE_GUESTS:
                        {
                            switch(m_uiPhaseCounter)
                            {
                                case 6:
                                    if (Creature* pCaldwell = GetCreature(NPC_CALDWELL))
                                        DoScriptText(SAY_OGR_CAL_FOUND, pCaldwell);
                                    break;
                                case 7:
                                    if (Creature* pCaldwell = GetCreature(NPC_CALDWELL))
                                        DoScriptText(SAY_OGR_CAL_MERCY, pCaldwell);
                                    break;
                                case 8:
                                    if (Creature* pHallan = GetCreature(NPC_HALLAN))
                                    {
                                        DoScriptText(SAY_OGR_HALL_GLAD, pHallan);

                                        if (Creature* pReethe = GetCreature(NPC_REETHE))
                                            pHallan->CastSpell(pReethe, SPELL_FAKE_SHOT, false);
                                    }
                                    break;
                                case 9:
                                    if (Creature* pReethe = GetCreature(NPC_REETHE))
                                    {
                                        DoScriptText(EMOTE_OGR_RET_ARROW, pReethe);
                                        DoScriptText(SAY_OGR_RET_ARROW, pReethe);
                                    }
                                    break;
                                case 10:
                                    if (Creature* pCaldwell = GetCreature(NPC_CALDWELL))
                                        DoScriptText(SAY_OGR_CAL_CLEANUP, pCaldwell);

                                    DoScriptText(SAY_OGR_NODIE, me);
                                    break;
                                case 11:
                                    DoStartAttackMe();
                                    m_uiPhase = PHASE_FIGHT;
                                    break;
                            }
                            break;
                        }
                        case PHASE_COMPLETE:
                        {
                            switch(m_uiPhaseCounter)
                            {
                                case 12:
                                    if (Player* pPlayer = GetPlayerForEscort())
                                        pPlayer->GroupEventHappens(QUEST_QUESTIONING, me);

                                    DoScriptText(SAY_OGR_SURVIVE, me);
                                    break;
                                case 13:
                                    if (Creature* pReethe = GetCreature(NPC_REETHE))
                                        DoScriptText(SAY_OGR_RET_LUCKY, pReethe);
                                    break;
                                case 14:
                                    DoScriptText(SAY_OGR_THANKS, me);
                                    SetRun();
                                    SetEscortPaused(false);
                                    break;
                            }
                            break;
                        }
                    }

                    if (m_uiPhase != PHASE_FIGHT)
                        ++m_uiPhaseCounter;
                }
                else
                    m_uiGlobalTimer -= uiDiff;
            }

            return;
        }

        DoMeleeAttackIfReady();
    }
};

bool OnQuestAccept(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_QUESTIONING)
    {
        if (npc_ogronAI* pEscortAI = dynamic_cast<npc_ogronAI*>(pCreature->AI()))
        {
            pEscortAI->Start(false, false, pPlayer->GetGUID(), pQuest, true);
            pCreature->setFaction(FACTION_ESCORT_N_FRIEND_PASSIVE);
            DoScriptText(SAY_OGR_START, pCreature, pPlayer);
        }
    }

    return true;
}
};
/////////////////////
/// npc_stinky
/////////////////////

enum eStinky
{
    QUEST_STINKYS_ESCAPE_H                       = 1270,
    QUEST_STINKYS_ESCAPE_A                       = 1222,
    SAY_QUEST_ACCEPTED                           = -1000507,
    SAY_STAY_1                                   = -1000508,
    SAY_STAY_2                                   = -1000509,
    SAY_STAY_3                                   = -1000510,
    SAY_STAY_4                                   = -1000511,
    SAY_STAY_5                                   = -1000512,
    SAY_STAY_6                                   = -1000513,
    SAY_QUEST_COMPLETE                           = -1000514,
    SAY_ATTACKED_1                               = -1000515,
    EMOTE_DISAPPEAR                              = -1000516
};

class npc_stinky : public CreatureScript
{
public:
   npc_stinky() : CreatureScript("npc_stinky") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_stinkyAI(pCreature);
    }

    bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const *quest)
    {
         if (quest->GetQuestId() == QUEST_STINKYS_ESCAPE_H || QUEST_STINKYS_ESCAPE_A)
         {
             if (npc_stinkyAI* pEscortAI = CAST_AI(npc_stinky::npc_stinkyAI, pCreature->AI()))
             {
                 pCreature->setFaction(FACTION_ESCORT_N_NEUTRAL_ACTIVE);
                 pCreature->SetStandState(UNIT_STAND_STATE_STAND);
                 DoScriptText(SAY_QUEST_ACCEPTED, pCreature);
                 pEscortAI->Start(false, false, pPlayer->GetGUID());
             }
         }
         return true;
    }

    struct npc_stinkyAI : public npc_escortAI
    {
       npc_stinkyAI(Creature* pCreature) : npc_escortAI(pCreature) { }


        void WaypointReached(uint32 i)
        {
            Player* pPlayer = GetPlayerForEscort();
            if (!pPlayer)
                return;

            switch (i)
            {
            case 7:
                DoScriptText(SAY_STAY_1, me, pPlayer);
                break;
            case 11:
                DoScriptText(SAY_STAY_2, me, pPlayer);
                break;
            case 25:
                DoScriptText(SAY_STAY_3, me, pPlayer);
                break;
            case 26:
                DoScriptText(SAY_STAY_4, me, pPlayer);
                break;
            case 27:
                DoScriptText(SAY_STAY_5, me, pPlayer);
                break;
            case 28:
                DoScriptText(SAY_STAY_6, me, pPlayer);
                me->SetStandState(UNIT_STAND_STATE_KNEEL);
                break;
            case 29:
                me->SetStandState(UNIT_STAND_STATE_STAND);
                break;
            case 37:
                DoScriptText(SAY_QUEST_COMPLETE, me, pPlayer);
                me->SetSpeed(MOVE_RUN, 1.2f, true);
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                if (pPlayer && pPlayer->GetQuestStatus(QUEST_STINKYS_ESCAPE_H))
                    pPlayer->GroupEventHappens(QUEST_STINKYS_ESCAPE_H, me);
                if (pPlayer && pPlayer->GetQuestStatus(QUEST_STINKYS_ESCAPE_A))
                    pPlayer->GroupEventHappens(QUEST_STINKYS_ESCAPE_A, me);
                break;
            case 39:
                DoScriptText(EMOTE_DISAPPEAR, me);
                break;

            }
        }

        void EnterCombat(Unit* pWho)
        {
            DoScriptText(SAY_ATTACKED_1, me, pWho);
        }

        void Reset() {}

        void JustDied(Unit* /*pKiller*/)
        {
            Player* pPlayer = GetPlayerForEscort();
            if (HasEscortState(STATE_ESCORT_ESCORTING) && pPlayer)
            {
                if (pPlayer->GetQuestStatus(QUEST_STINKYS_ESCAPE_H))
                    pPlayer->FailQuest(QUEST_STINKYS_ESCAPE_H);
                if (pPlayer->GetQuestStatus(QUEST_STINKYS_ESCAPE_A))
                    pPlayer->FailQuest(QUEST_STINKYS_ESCAPE_A);
            }
        }

       void UpdateAI(const uint32 uiDiff)
        {
            npc_escortAI::UpdateAI(uiDiff);

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

/**
*** npc_captured_totem
**/
enum eCapturedTotem
{
    NPC_DRYWALLOW_CROCILISK        = 4341,
    NPC_CAPTURED_TOTEM_CREDIT    = 23811
};

class npc_captured_totem : public CreatureScript
{
public:
    npc_captured_totem() : CreatureScript("npc_captured_totem") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_captured_totemAI (pCreature);
    }
struct npc_captured_totemAI : public ScriptedAI
{
    npc_captured_totemAI(Creature* c) : ScriptedAI(c){}

    uint32 checkTimer ;

    void Reset()
    {
        checkTimer = 3000 ;
    }

    void EnterCombat(Unit* who){}

    void UpdateAI(const uint32 diff)
    {
        if(checkTimer<= diff)
        {
            if(Creature* crocilisk = me->FindNearestCreature(NPC_DRYWALLOW_CROCILISK, 10.0f, false))
            {
                if (me->isSummon())
                {
                    if (Unit* owner = me->GetOwner())
                    {
                        if(owner->GetTypeId() == TYPEID_PLAYER)
                        {
                            if(Player* player = CAST_PLR(owner))
                                player->KilledMonsterCredit(NPC_CAPTURED_TOTEM_CREDIT, 0) ;
                        }
                    }
                }
                crocilisk->DisappearAndDie() ;
            }
            checkTimer = 3000 ;
        } else checkTimer -= diff ;

        if (!UpdateVictim())
            return;
    }
};
};

#define GOSSIP_RESCUE_ITHANIA        "Je viens vous sauver."

class npc_ithania : public CreatureScript
{
public:
    npc_ithania() : CreatureScript("npc_ithania") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ithaniaAI (pCreature);
    }

struct npc_ithaniaAI : public ScriptedAI
{

npc_ithaniaAI(Creature* pCreature) : ScriptedAI(pCreature) {}

bool OnGossipHello(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(9437) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_RESCUE_ITHANIA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    }
    return true;
}

bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiAction)
    {
    case GOSSIP_ACTION_INFO_DEF + 1:
        pPlayer->TalkedToCreature(pCreature->GetEntry(), pCreature->GetGUID());
        pCreature->GetMotionMaster()->MovePoint(0, -2861.49, -3424.64, 39);
        pCreature->ForcedDespawn(5000);
        break;
    }

    return true;
}
};
};

void AddSC_dustwallow_marsh()
{
    new mobs_risen_husk_spirit();
    new npc_restless_apparition();
    new npc_deserter_agitator();
    new npc_lady_jaina_proudmoore();
    new npc_nat_pagle();
    new npc_private_hendel();
    new npc_zelfrax();
    new npc_morokk();
    new npc_ogron();
    new npc_stinky();
    new npc_captured_totem();
    new npc_ithania();
    new npc_theramore_guard();
}
