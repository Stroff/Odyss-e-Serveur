/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
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
SDName: Kologarn
SDAuthor: PrinceCreed, Eracus.
SD%Complete: 100%
SD%Comments:
EndScriptData */

#include "ScriptPCH.h"
#include "ulduar.h"
#include "Vehicle.h"

#define SPELL_ARM_DEAD_DAMAGE                   RAID_MODE(63629,63979)
#define SPELL_TWO_ARM_SMASH                     RAID_MODE(63356,64003)
#define SPELL_ONE_ARM_SMASH                     RAID_MODE(63573,64006)
#define SPELL_STONE_SHOUT                       RAID_MODE(63716,64005)
#define SPELL_PETRIFY_BREATH                    RAID_MODE(62030,63980)
#define SPELL_SHOCKWAVE                         RAID_MODE(63783,63982)

#define SPELL_STONE_GRIP                        RAID_MODE(64290,64292)
#define SPELL_STONE_GRIP_STUN                   RAID_MODE(62056,63985)
#define SPELL_ARM_SWEEP                         RAID_MODE(63766,63983)
#define SPELL_FOCUSED_EYEBEAM                   RAID_MODE(63347,63977)
#define SPELL_EYEBEAM_VISUAL_1                  63676
#define SPELL_EYEBEAM_VISUAL_2                  63702
#define SPELL_EYEBEAM_DAMAGE_10                 63346
#define SPELL_EYEBEAM_DAMAGE_25                 63976
#define SPELL_EYEBEAM_IMMUNITY                  64722
#define SPELL_ARM_RESPAWN                       64753
#define SPELL_SHOCKWAVE_VISUAL                  63788
#define ARM_DEAD_DAMAGE                         RAID_MODE(543855,2300925)

enum Events
{
    EVENT_NONE,
    EVENT_SMASH,
	EVENT_GRIP,
    EVENT_SWEEP,
    EVENT_SHOCKWAVE,
    EVENT_EYEBEAM,
    EVENT_STONESHOT,
    EVENT_RIGHT,
    EVENT_LEFT
};

enum Actions
{
    ACTION_RESPAWN_RIGHT,
    ACTION_RESPAWN_LEFT,
	ACTION_GRIP,
	ACTION_LOOKS_KILL_FAIL,
};

enum Npcs
{
    NPC_EYEBEAM_1                               = 33632,
    NPC_EYEBEAM_2                               = 33802,
    NPC_RUBBLE                                  = 33768,
};

enum Yells
{
    SAY_AGGRO                                   = -1603230,
    SAY_SLAY_1                                  = -1603231,
    SAY_SLAY_2                                  = -1603232,
    SAY_LEFT_ARM_GONE                           = -1603233,
    SAY_RIGHT_ARM_GONE                          = -1603234,
    SAY_SHOCKWAVE                               = -1603235,
    SAY_GRAB_PLAYER                             = -1603236,
    SAY_DEATH                                   = -1603237,
    SAY_BERSERK                                 = -1603238
};

#define EMOTE_LEFT                              "Le bras gauche de Kologarn est reapparu !"
#define EMOTE_RIGHT                             "Le bras droit de Kologarn est reapparu !"
#define EMOTE_STONE                             "Kologarn lance Poigne de pierre !"

// Achievements
#define ACHIEVEMENT_LOOKS_COULD_KILL            RAID_MODE(2955, 2956) // TODO
#define ACHIEVEMENT_RUBBLE_AND_ROLL             RAID_MODE(2959, 2960)
#define ACHIEVEMENT_WITH_OPEN_ARMS              RAID_MODE(2951, 2952)
#define ACHIEV_DISARMED_START_EVENT             21687

uint32 GripTargetGUID[3];

const Position RubbleLeft   = {1781.814f, -45.07f, 448.808f, 2.260f};
const Position RubbleRight  = {1781.814f, -3.716f, 448.808f, 4.211f};

enum GameObjects
{
    CACHE_OF_LIVING_STONE_10                    = 195046,
    CACHE_OF_LIVING_STONE_25                    = 195047,
	GO_KOLOGARN_DOOR                            = 194553,
};

class boss_kologarn : public CreatureScript
{
public:
    boss_kologarn() : CreatureScript("boss_kologarn") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_kologarnAI (pCreature);
    }

    struct boss_kologarnAI : public BossAI
    {
        boss_kologarnAI(Creature *pCreature) : BossAI(pCreature, TYPE_KOLOGARN), vehicle(pCreature->GetVehicleKit()),
            left(false), right(false)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetStandState(UNIT_STAND_STATE_SUBMERGED);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            me->SetFlying(true);
			me->SetReactState(REACT_AGGRESSIVE);
            emerged = false;
        }

        Vehicle *vehicle;

        bool left, right;
		bool Gripped;
        bool emerged;
        uint32 RubbleCount;
		bool LooksKillFail;

        void MoveInLineOfSight(Unit* who)
        {
            // Birth animation
            if (!emerged && me->IsWithinDistInMap(who, 40.0f) && who->GetTypeId() == TYPEID_PLAYER && !who->ToPlayer()->isGameMaster())
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                emerged = true;
            }
        }

        void AttackStart(Unit *who)
        {
            me->Attack(who, true);
        }

        void JustDied(Unit* /*victim*/)
        {                
            DoScriptText(SAY_DEATH, me);
            _JustDied();

            if (instance)
            {
				if (GameObject* KologarnDoor = me->FindNearestGameObject(GO_KOLOGARN_DOOR, 100.0f))
					instance->DoUseDoorOrButton(KologarnDoor->GetGUID());
                // Rubble and Roll
                if (RubbleCount > 4)
                    instance->DoCompleteAchievement(ACHIEVEMENT_RUBBLE_AND_ROLL);
                // With Open Arms
                if (RubbleCount == 0)
                    instance->DoCompleteAchievement(ACHIEVEMENT_WITH_OPEN_ARMS);

				if (!LooksKillFail)
					instance->DoCompleteAchievement(ACHIEVEMENT_LOOKS_COULD_KILL);

                // Remove Stone Grip from players
                Map::PlayerList const &players = instance->instance->GetPlayers();
                for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                {
                    Player* pPlayer = itr->getSource();
 
                    if (!pPlayer)
                        continue;
 
                    if (pPlayer->HasAura(SPELL_STONE_GRIP_STUN))
                    {
                        pPlayer->RemoveAurasDueToSpell(RAID_MODE(64290, 64292));
                        pPlayer->RemoveAurasDueToSpell(SPELL_STONE_GRIP_STUN);
                        pPlayer->GetMotionMaster()->MoveJump(1767.80f, -18.38f, 448.808f, 10, 10);
                    }
                }
            }

            // Hack to disable corpse fall
            me->GetMotionMaster()->MoveTargetedHome();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->setFaction(35);
            // Chest spawn
            me->SummonGameObject(RAID_MODE(CACHE_OF_LIVING_STONE_10, CACHE_OF_LIVING_STONE_25),1836.52f,-36.11f,448.81f,0.56f,0,0,1,1,604800);
        }

        void KilledUnit(Unit* /*who*/)
        {
            if (!(rand()%5))
                DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2), me);
        }

        void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
        {
            if (who->GetTypeId() == TYPEID_UNIT)
            {
                if (who->GetEntry() == NPC_LEFT_ARM)
                    left = apply;
                else if (who->GetEntry() == NPC_RIGHT_ARM)
                    right = apply;
                who->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);
            _EnterCombat();

			if (GameObject* KologarnDoor = me->FindNearestGameObject(GO_KOLOGARN_DOOR, 100.0f))
				instance->DoUseDoorOrButton(KologarnDoor->GetGUID());
        
            RubbleCount = 0;
			LooksKillFail = false;
			Gripped = false;
			for (int32 n = 0; n < RAID_MODE(1, 3); ++n)
                GripTargetGUID[n] = NULL;

            for (int32 n = 0; n < 2; ++n)
            {
                if (vehicle->GetPassenger(n))
                    vehicle->GetPassenger(n)->ToCreature()->AI()->DoZoneInCombat();
            }
            events.ScheduleEvent(EVENT_SMASH, 5000);
            events.ScheduleEvent(EVENT_SWEEP, 8000);
            events.ScheduleEvent(EVENT_EYEBEAM, 10000);
            events.ScheduleEvent(EVENT_SHOCKWAVE, 12000);
			events.ScheduleEvent(EVENT_GRIP, 40000);
        }

        void Reset()
        {
            _Reset();
            
            if (instance)
			{
                instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_DISARMED_START_EVENT);
				if (GameObject* KologarnDoor = me->FindNearestGameObject(GO_KOLOGARN_DOOR, 100.0f))
					if (KologarnDoor->GetGoState() != GO_STATE_ACTIVE)
						instance->DoUseDoorOrButton(KologarnDoor->GetGUID());
			}
        
            if (me->GetVehicleKit())
				me->GetVehicleKit()->Reset();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;
            
            if (events.GetTimer() > 15000 && !me->IsWithinMeleeRange(me->getVictim()))
                DoCastAOE(SPELL_PETRIFY_BREATH, true);
        
            if (!left && !right)
                DoCast(me, SPELL_STONE_SHOUT, true);

            switch(events.GetEvent())
            {
                case EVENT_NONE: break;
                case EVENT_SMASH:
                    if (left && right)
                    {
                        if (me->IsWithinMeleeRange(me->getVictim()))
                            DoCastVictim(SPELL_TWO_ARM_SMASH, true);
                    }
                    else if (left || right)
                    {
                        if (me->IsWithinMeleeRange(me->getVictim()))
                            DoCastVictim(SPELL_ONE_ARM_SMASH, true);
                    }
                    events.RescheduleEvent(EVENT_SMASH, 15000);
                    break;
                case EVENT_SWEEP:
                    if (left)
                        DoCastAOE(SPELL_ARM_SWEEP, true);
                    events.RescheduleEvent(EVENT_SWEEP, 15000);
                    break;
                case EVENT_GRIP:
                    if (right && instance)
                    {
                        if (Unit* RightArm = vehicle->GetPassenger(1))
                        {
                            me->MonsterTextEmote(EMOTE_STONE, 0, true);
                            DoScriptText(SAY_GRAB_PLAYER, me);
                            // Grip up to 3 players
                            for (int32 n = 0; n < RAID_MODE(1, 3); ++n)
                            {
                                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 40, true))
                                    GripTargetGUID[n] = pTarget->GetGUID();
                            }
                            RightArm->ToCreature()->AI()->DoAction(ACTION_GRIP);
                        }
                    }
                    events.RescheduleEvent(EVENT_GRIP, 40000);
                    break;
                case EVENT_SHOCKWAVE:
                    if (left)
                    {
                        DoScriptText(SAY_SHOCKWAVE, me);
                        DoCastAOE(SPELL_SHOCKWAVE, true);
                        DoCastAOE(SPELL_SHOCKWAVE_VISUAL, true);
                    }
                    events.RescheduleEvent(EVENT_SHOCKWAVE, urand(15000, 25000));
                    break;
                case EVENT_EYEBEAM:
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_FARTHEST, 0, 50, true))
                    {
                        if (Creature* EyeBeam = me->SummonCreature(NPC_EYEBEAM_1,pTarget->GetPositionX(),pTarget->GetPositionY()+3,pTarget->GetPositionZ(),0,TEMPSUMMON_TIMED_DESPAWN,10000))
                        {
                            EyeBeam->CastSpell(me, SPELL_EYEBEAM_VISUAL_1, true);
                            EyeBeam->AI()->AttackStart(pTarget);
                        }
                        if (Creature* EyeBeam = me->SummonCreature(NPC_EYEBEAM_2,pTarget->GetPositionX(),pTarget->GetPositionY()-3,pTarget->GetPositionZ(),0,TEMPSUMMON_TIMED_DESPAWN,10000))
                        {
                            EyeBeam->CastSpell(me, SPELL_EYEBEAM_VISUAL_2, true);
                            EyeBeam->AI()->AttackStart(pTarget);
                        }
                    }
                    events.RescheduleEvent(EVENT_EYEBEAM, 20000);
                    break;
                case EVENT_LEFT:
                    if (Unit* LeftArm = me->SummonCreature(NPC_LEFT_ARM, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation()))
                    {
                        LeftArm->_EnterVehicle(vehicle, 0);
                        DoCast(me, SPELL_ARM_RESPAWN, true);
                        me->MonsterTextEmote(EMOTE_LEFT, 0, true);
                        if (instance)
                            instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_DISARMED_START_EVENT);
                    }
                    events.CancelEvent(EVENT_LEFT);
                    break;                
                case EVENT_RIGHT:
                    if (Unit* RightArm = me->SummonCreature(NPC_RIGHT_ARM, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation()))
                    {
                        RightArm->_EnterVehicle(vehicle, 1);
                        DoCast(me, SPELL_ARM_RESPAWN, true);
                        me->MonsterTextEmote(EMOTE_RIGHT, 0, true);
                        if (instance)
                            instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_DISARMED_START_EVENT);
                    }
                    events.CancelEvent(EVENT_RIGHT);
                    break;
            }

            DoMeleeAttackIfReady();
        }

        void DoAction(const int32 action)
        {
            switch (action)
            {
                case ACTION_RESPAWN_LEFT:
                    DoScriptText(SAY_LEFT_ARM_GONE, me);
                    me->DealDamage(me, int32(me->GetMaxHealth() * 15 / 100)); // decreases Kologarn's health by 15%
                    ++RubbleCount;
                    if (instance && right)
                        instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_DISARMED_START_EVENT);
                    events.ScheduleEvent(EVENT_LEFT, 30000);
                    break;
                case ACTION_RESPAWN_RIGHT:
                    DoScriptText(SAY_RIGHT_ARM_GONE, me);
                    me->DealDamage(me, int32(me->GetMaxHealth() * 15 / 100));
                    ++RubbleCount;
                    if (instance && left)
                        instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_DISARMED_START_EVENT);
                    events.ScheduleEvent(EVENT_RIGHT, 30000);
                    break;
				case ACTION_LOOKS_KILL_FAIL:
					LooksKillFail = true;
					break;
            }
        }    
    };
};

class npc_focused_eyebeam : public CreatureScript
{
public:
    npc_focused_eyebeam() : CreatureScript("npc_focused_eyebeam") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_focused_eyebeamAI (pCreature);
    }

    struct npc_focused_eyebeamAI : public ScriptedAI
    {
        npc_focused_eyebeamAI(Creature *c) : ScriptedAI(c)
        {
			pInstance = c->GetInstanceScript();
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
            DoCast(me, SPELL_EYEBEAM_IMMUNITY);
            DoCast(me, SPELL_FOCUSED_EYEBEAM);
            me->SetDisplayId(11686);
            checkTimer = 1500;
			Go = false;
			Fail = false;
        }

		InstanceScript* pInstance;
        uint32 checkTimer;
		bool Go;
		bool Fail;

        void SpellHitTarget(Unit* target, const SpellEntry* spell)
        {
            if(target && target->ToPlayer() && !Fail && Go)
            {
                switch(spell->Id)
                {
				case SPELL_EYEBEAM_DAMAGE_10:
                    if (Creature* pKologarn = me->GetCreature(*me, pInstance->GetData64(TYPE_KOLOGARN)))
						pKologarn->AI()->DoAction(ACTION_LOOKS_KILL_FAIL);
					Fail = true;
                    break;
				case SPELL_EYEBEAM_DAMAGE_25:
                    if (Creature* pKologarn = me->GetCreature(*me, pInstance->GetData64(TYPE_KOLOGARN)))
						pKologarn->AI()->DoAction(ACTION_LOOKS_KILL_FAIL);
					Fail = true;
                    break;
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (checkTimer <= diff)
            {
                if (me->getVictim() && me->getVictim()->isAlive())
                    me->GetMotionMaster()->MovePoint(0,me->getVictim()->GetPositionX(),me->getVictim()->GetPositionY(),me->getVictim()->GetPositionZ());
				Go = true;
                checkTimer = 500;
            }
            else checkTimer -= diff;
        }
    };
};

class npc_left_arm : public CreatureScript
{
public:
    npc_left_arm() : CreatureScript("npc_left_arm") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_left_armAI (pCreature);
    }

    struct npc_left_armAI : public ScriptedAI
    {
        npc_left_armAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
            me->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* pInstance;
		
		void EnterCombat(Unit* pWho)
		{
			if (pInstance)
			{
				if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), pInstance->GetData64(DATA_RIGHT_ARM))))
					if (pTemp->isAlive())
						pTemp->SetInCombatWithZone();
				if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), pInstance->GetData64(TYPE_KOLOGARN))))
					if (pTemp->isAlive())
						pTemp->SetInCombatWithZone();
			}
		}

        void JustDied(Unit* /*victim*/)
        {
            for (uint8 i = 0; i < 5; ++i)
                me->SummonCreature(NPC_RUBBLE, RubbleLeft, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 3000);
            
            if (pInstance)
                if (Creature* pKologarn = me->GetCreature(*me, pInstance->GetData64(TYPE_KOLOGARN)))
                    pKologarn->AI()->DoAction(ACTION_RESPAWN_LEFT);
                    
            // Hack to disable corpse fall
            me->GetMotionMaster()->MoveTargetedHome();
        }
    
        void JustSummoned(Creature *summon)
        {
            summon->AI()->DoZoneInCombat();
        }
    };
};

class npc_right_arm : public CreatureScript
{
public:
    npc_right_arm() : CreatureScript("npc_right_arm") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_right_armAI (pCreature);
    }

    struct npc_right_armAI : public ScriptedAI
    {
        npc_right_armAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 64708, true);
            me->SetReactState(REACT_PASSIVE);
        }

        InstanceScript* pInstance;

        bool Gripped;
        int32 ArmDamage;
        uint32 SqueezeTimer;

        void Reset()
        {
            Gripped = false;
            ArmDamage = 0;
            SqueezeTimer = 0;
        }

		void EnterCombat(Unit* pWho)
		{
			if (pInstance)
			{
				if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), pInstance->GetData64(DATA_RIGHT_ARM))))
					if (pTemp->isAlive())
						pTemp->SetInCombatWithZone();
				if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), pInstance->GetData64(TYPE_KOLOGARN))))
					if (pTemp->isAlive())
						pTemp->SetInCombatWithZone();
			}
		}

        void JustDied(Unit* /*victim*/)
        {
            for (uint8 i = 0; i < 5; ++i)
                me->SummonCreature(NPC_RUBBLE, RubbleRight, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 3000);
            
            if (pInstance)
                if (Creature* pKologarn = me->GetCreature(*me, pInstance->GetData64(TYPE_KOLOGARN)))
                    pKologarn->AI()->DoAction(ACTION_RESPAWN_RIGHT);
                    
            // Hack to disable corpse fall
            me->GetMotionMaster()->MoveTargetedHome();
        }
    
        void JustSummoned(Creature *summon)
        {
            summon->AI()->DoZoneInCombat();
        }

        void KilledUnit(Unit* Victim)
        {
            if (Victim)
            {
                Victim->ExitVehicle();
                Victim->GetMotionMaster()->MoveJump(1767.80f, -18.38f, 448.808f, 10, 10);
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (Gripped)
            {
                if (SqueezeTimer <= diff)
                {
                    for (uint8 n = 0; n < RAID_MODE(1, 3); ++n)
                    {
                        if (me->GetVehicleKit()->GetPassenger(n) && me->GetVehicleKit()->GetPassenger(n)->isAlive())
                            me->Kill(me->GetVehicleKit()->GetPassenger(n), true);
                    }
                    Gripped = false;
                }
                else SqueezeTimer -= diff;
            }
        }

        void DoAction(const int32 action)
        {
            switch (action)
            {
                case ACTION_GRIP:
                    for (uint8 n = 0; n < RAID_MODE(1, 3); ++n)
                    {
                        if (Unit* GripTarget = Unit::GetUnit(*me, GripTargetGUID[n]))
                        {
                            if (GripTarget && GripTarget->isAlive())
                            {
                                GripTarget->_EnterVehicle(me->GetVehicleKit(), n);
                                me->AddAura(SPELL_STONE_GRIP, GripTarget);
                                me->AddAura(SPELL_STONE_GRIP_STUN, GripTarget);
                                GripTargetGUID[n] = NULL;
                            }
                        }
                    }
                    ArmDamage = 0;
                    SqueezeTimer = 16000;
                    Gripped = true;
                    break;
            }
        }
    
        void DamageTaken(Unit* pKiller, uint32 &damage)
        {
            if (Gripped)
            {
                ArmDamage += damage;
                int32 dmg = RAID_MODE(100000, 480000);
            
                if (ArmDamage >= dmg || damage >= me->GetHealth())
                {
                    for (uint8 n = 0; n < RAID_MODE(1, 3); ++n)
                    {
                        Unit* pGripTarget = me->GetVehicleKit()->GetPassenger(n);
                        if (pGripTarget && pGripTarget->isAlive())
                        {
                            pGripTarget->RemoveAurasDueToSpell(SPELL_STONE_GRIP);
                            pGripTarget->RemoveAurasDueToSpell(SPELL_STONE_GRIP_STUN);
                            pGripTarget->ExitVehicle();
                            pGripTarget->GetMotionMaster()->MoveJump(1767.80f, -18.38f, 448.808f, 10, 10);
                        }
                    }
                    Gripped = false;
                }
            }
        }
    };

};

void AddSC_boss_kologarn()
{
    new boss_kologarn();
    new npc_focused_eyebeam();
    new npc_left_arm();
    new npc_right_arm();
}