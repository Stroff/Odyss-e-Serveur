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
#include "ulduar.h"

enum Spells
{
    SPELL_ASCEND                    = 64487,
    SPELL_BERSERK                   = 47008,
    SPELL_BIG_BANG_10               = 64443,
    SPELL_BIG_BANG_25               = 64584,
    SPELL_COSMIC_SMASH_10           = 62301,
    SPELL_COSMIC_SMASH_25           = 64598,
    SPELL_PHASE_PUNCH               = 64412,
    SPELL_PHASE_PUNCH_PHASE         = 64417,
    SPELL_QUANTUM_STRIKE_10         = 64395,
    SPELL_QUANTUM_STRIKE_25         = 64592,
    SPELL_BLACK_HOLE_CREDIT         = 65312,
    SPELL_BLACK_HOLE_EXPLOSION_10   = 64122,
    SPELL_BLACK_HOLE_EXPLOSION_25   = 65108,
    SPELL_BLACK_HOLE_SPAWN_VISUAL   = 62003,
    SPELL_BLACK_HOLE_STATE          = 64135,
    SPELL_BLACK_HOLE_TRIGGER        = 62185,
    SPELL_BLACK_HOLE_PHASE          = 62168,
    SPELL_DESPAWN_BLACK_HOLE        = 64391,
    SPELL_ARCANE_BARAGE_10          = 64599,
    SPELL_ARCANE_BARAGE_25          = 64607,

    SPELL_BOSS_FINISHED             = 65184,
};

enum Creatures
{
    CREATURE_COLLAPSING_STAR        = 32955,
    CREATURE_BLACK_HOLE             = 32953,
    CREATURE_LIVING_CONSTELLATION   = 33052,
    CREATURE_DARK_MATTER            = 33089,
    CREATURE_AZEROTH                = 34246
};

enum Yells
{
    SAY_AGGRO                                   = -1603000,
    SAY_SLAY_1                                  = -1603001,
    SAY_SLAY_2                                  = -1603002,
    SAY_ENGAGED_FOR_FIRST_TIME                  = -1603003,
    SAY_PHASE_2                                 = -1603004,
    SAY_SUMMON_COLLAPSING_STAR                  = -1603005,
    SAY_DEATH_1                                 = -1603006,
    SAY_DEATH_2                                 = -1603007,
    SAY_DEATH_3                                 = -1603008,
    SAY_DEATH_4                                 = -1603009,
    SAY_DEATH_5                                 = -1603010,
    SAY_BERSERK                                 = -1603011,
    SAY_BIG_BANG_1                              = -1603012,
    SAY_BIG_BANG_2                              = -1603013,
    SAY_TIMER_1                                 = -1603014,
    SAY_TIMER_2                                 = -1603015,
    SAY_TIMER_3                                 = -1603016,
    SAY_SUMMON_1                                = -1603017,
    SAY_SUMMON_2                                = -1603018,
    SAY_SUMMON_3                                = -1603019,
};

enum Events
{
    EVENT_NONE,
    EVENT_ASCEND,
    EVENT_BERSERK,
    EVENT_BIGBANG,
    EVENT_COSMICSMASH,
    EVENT_PHASEPUNCH,
    EVENT_QUANTUMSTRIKE,
    EVENT_COLLAPSINGSTAR,
    EVENT_LIVINGCONSTELLATION
};

static Position Locations[]=
{
    {1632.36f, -310.09f, 417.33f, 0.0f},  // room center
    {1632.44f, -301.55f, 417.33f, 0.0f},  // azeroth

    {1649.30f, -295.34f, 458.13f, 0.0f},
    {1612.22f, -294.84f, 458.13f, 0.0f},
    {1629.95f, -327.90f, 458.13f, 0.0f}
};

class boss_algalon_the_observer : public CreatureScript
{
public:
    boss_algalon_the_observer() : CreatureScript("boss_algalon_the_observer") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_algalon_the_observerAI(pCreature);
    }

    struct boss_algalon_the_observerAI : public BossAI
    {
        boss_algalon_the_observerAI(Creature* c) : BossAI(c, TYPE_ALGALON)
        {
            summon = false;
        }

        uint8 starCount;
        uint32 phase;
        uint32 stepTimer;
        uint32 step;
        bool summon;

        void Reset()
        {
            _Reset();

            if (summon)
                me->setFaction(7);

            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            phase = 1;
            stepTimer = 0;
            starCount = 0;
        }

        void EnterCombat(Unit* who)
        {
            _EnterCombat();
            me->setFaction(14);

            if (summon)
            {
                me->InterruptSpell(CURRENT_CHANNELED_SPELL);
                DoZoneInCombat();
            }
            else
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                step = 1;
            }

            events.ScheduleEvent(EVENT_BERSERK, 6*MINUTE*IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_BIGBANG, 90*IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_PHASEPUNCH, 15*IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_QUANTUMSTRIKE, urand(4*IN_MILLISECONDS, 14*IN_MILLISECONDS));
            events.ScheduleEvent(EVENT_COSMICSMASH, 25*IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_COLLAPSINGSTAR, 15*IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_LIVINGCONSTELLATION, 50*IN_MILLISECONDS);
        }

        void FinishEncounter()
        {
            if (instance)
                instance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, SPELL_BOSS_FINISHED);
        }

        void KilledUnit(Unit * /*victim*/)
        {
            DoScriptText(RAND(SAY_SLAY_1, SAY_SLAY_2), me);
        }

        void JumpToNextStep(uint32 timer)
        {
            stepTimer = timer;
            ++step;
        }

        void SummonCollapsingStars()
        {
            DoScriptText(SAY_SUMMON_COLLAPSING_STAR, me);
            for (uint8 i = starCount; i < 4; ++i)
            {
                float x, y, angle;
                angle = float(2 * M_PI * rand_norm());
                x = Locations[0].GetPositionX() + 15.0f * cos(angle);
                y = Locations[0].GetPositionY() + 15.0f * sin(angle);

                if (Creature* collapsingStar = me->SummonCreature(CREATURE_COLLAPSING_STAR, x, y, Locations[0].GetPositionZ(), 0,
                    TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3*IN_MILLISECONDS))
                {
                    ++starCount;
                    collapsingStar->SetReactState(REACT_PASSIVE);
                    collapsingStar->GetMotionMaster()->MoveRandom(20.0f);
                    collapsingStar->SetInCombatWithZone();
                }
            }
        }

        void SummonLivingConstallations()
        {
            for (uint8 i = 0; i < 3; ++i)
            {
                if (Creature* livingConstellation = me->SummonCreature(CREATURE_LIVING_CONSTELLATION, Locations[i + 2], TEMPSUMMON_CORPSE_TIMED_DESPAWN,
                    1*IN_MILLISECONDS))
                {
                    livingConstellation->SetInCombatWithZone();
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        livingConstellation->AI()->AttackStart(target);
                }
            }
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
        }

        void SummonedCreatureDies(Creature* summon, Unit* /*killer*/)
        {
            switch (summon->GetEntry())
            {
                case CREATURE_COLLAPSING_STAR:
                    --starCount;
                    me->SummonCreature(CREATURE_BLACK_HOLE, summon->GetPositionX(), summon->GetPositionY(), summon->GetPositionZ());
                    break;
                default:
                    break;
            }
        }

        void SpellHitTarget(Unit* target, const SpellEntry* spell)
        {
            if (spell->Id == SPELL_PHASE_PUNCH)
                if (Aura* phasePunch = target->GetAura(SPELL_PHASE_PUNCH))
                    if (phasePunch->GetStackAmount() > 4)
                    {
                        target->CastSpell(target, SPELL_PHASE_PUNCH_PHASE, true);
                        target->CombatStop();
                        target->getHostileRefManager().deleteReferences();
                    }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (phase == 1 && HealthBelowPct(20))
            {
                phase = 2;
                DoScriptText(SAY_PHASE_2, me);
                summons.DespawnAll();
                events.CancelEvent(EVENT_COLLAPSINGSTAR);
                events.CancelEvent(EVENT_LIVINGCONSTELLATION);
                //SummonUnstableBlackHoles();
            }

            if (HealthBelowPct(2))
            {
                me->SummonGameObject(GO_GIFT_OF_THE_OBSERVER, 1634.258667f, -295.101166f,417.321381f,0,0,0,0,0,0);

                // All of them. or random?
                DoScriptText(SAY_DEATH_1, me);
                DoScriptText(SAY_DEATH_2, me);
                DoScriptText(SAY_DEATH_3, me);
                DoScriptText(SAY_DEATH_4, me);
                DoScriptText(SAY_DEATH_5, me);

                me->DisappearAndDie();
                _JustDied();

                return;
            }

            if (!summon)
            {
                if (stepTimer <= diff)
                {
                    switch (step)
                    {
                        case 1:
                            DoScriptText(SAY_SUMMON_1, me);
                            JumpToNextStep(7500);
                            break;
                        case 2:
                            DoScriptText(SAY_SUMMON_2, me);
                            JumpToNextStep(6000);
                            break;
                        case 3:
                            DoScriptText(SAY_SUMMON_3, me);
                            JumpToNextStep(11000);
                            break;
                        case 4:
                            DoScriptText(SAY_ENGAGED_FOR_FIRST_TIME, me);
                            JumpToNextStep(11000);
                            break;
                        case 5:
                            DoScriptText(SAY_AGGRO, me);
                            JumpToNextStep(7000);
                            break;
                        case 6:
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->SetReactState(REACT_AGGRESSIVE);
                            summon = true;
                            break;
                    }
                } else stepTimer -= diff;
                return;
            }

//            _DoAggroPulse(diff);
            events.Update(diff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BIGBANG:
                        DoScriptText(RAND(SAY_BIG_BANG_1, SAY_BIG_BANG_2), me);
                        DoCast(me->getVictim(), RAID_MODE(SPELL_BIG_BANG_10, SPELL_BIG_BANG_25));
                        events.ScheduleEvent(EVENT_BIGBANG, 90*IN_MILLISECONDS);
                        break;
                    case EVENT_PHASEPUNCH:
                        DoCast(me->getVictim(), SPELL_PHASE_PUNCH, true);
                        events.ScheduleEvent(EVENT_PHASEPUNCH, 15*IN_MILLISECONDS);
                        break;
                    case EVENT_QUANTUMSTRIKE:
                        DoCast(me->getVictim(), RAID_MODE(SPELL_QUANTUM_STRIKE_10, SPELL_QUANTUM_STRIKE_25));
                        events.ScheduleEvent(EVENT_QUANTUMSTRIKE, urand(4*IN_MILLISECONDS, 14*IN_MILLISECONDS));
                        break;
                    case EVENT_COSMICSMASH:
                        DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0), RAID_MODE(SPELL_COSMIC_SMASH_10, SPELL_COSMIC_SMASH_25));
                        events.ScheduleEvent(EVENT_COSMICSMASH, 25*IN_MILLISECONDS);
                        break;
                    case EVENT_COLLAPSINGSTAR:
                        SummonCollapsingStars();
                        events.ScheduleEvent(EVENT_COLLAPSINGSTAR, 45*IN_MILLISECONDS);
                        break;
                    case EVENT_LIVINGCONSTELLATION:
                        SummonLivingConstallations();
                        events.ScheduleEvent(EVENT_LIVINGCONSTELLATION, 50*IN_MILLISECONDS);
                        break;
                    case EVENT_BERSERK:
                        DoScriptText(SAY_BERSERK, me);
                        DoCast(me, SPELL_BERSERK, true);
                        events.ScheduleEvent(EVENT_ASCEND, 3*IN_MILLISECONDS);
                        break;
                    case EVENT_ASCEND:
                        DoCast(me, SPELL_ASCEND);
                        events.ScheduleEvent(EVENT_ASCEND, 10*IN_MILLISECONDS);
                        break;
                    default:
                        break;
                }
            }

            DoMeleeAttackIfReady();
            EnterEvadeIfOutOfCombatArea(diff);
        }
    };
};

class mob_collapsing_star : public CreatureScript
{
public:
    mob_collapsing_star() : CreatureScript("mob_collapsing_star") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_collapsing_starAI(pCreature);
    }

    struct mob_collapsing_starAI : public ScriptedAI
    {
        mob_collapsing_starAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        uint32 loseHealthTimer;

        void Reset()
        {
            loseHealthTimer = 1*IN_MILLISECONDS;
        }

        void JustDied(Unit * /*killer*/)
        {
            DoCast(SPELL_BLACK_HOLE_CREDIT);
            DoCast(me, RAID_MODE(SPELL_BLACK_HOLE_EXPLOSION_10, SPELL_BLACK_HOLE_EXPLOSION_25), true);
        }

        void UpdateAI(const uint32 diff)
        {
            if (loseHealthTimer <= diff)
            {
                me->DealDamage(me, me->CountPctFromMaxHealth(1)); 
                loseHealthTimer = 1*IN_MILLISECONDS;
            } else loseHealthTimer -= diff;
        }
    };
};

class mob_living_constellation : public CreatureScript
{
public:
    mob_living_constellation() : CreatureScript("mob_living_constellation") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_living_constellationAI(pCreature);
    }

    struct mob_living_constellationAI : public ScriptedAI
    {
        mob_living_constellationAI(Creature* pCreature) : ScriptedAI(pCreature) { }

        uint32 arcaneBarrageTimer;

        void Reset()
        {
            me->SetFlying(true);
            me->SetSpeed(MOVE_FLIGHT, 0.6f);
            arcaneBarrageTimer = urand(5*IN_MILLISECONDS, 10*IN_MILLISECONDS);
        }

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetTypeId() != TYPEID_UNIT)
                return;

            if (who->GetEntry() == CREATURE_BLACK_HOLE && who->GetDistance(me) < 5.0f)
            {
                who->ToCreature()->CastSpell(who, SPELL_DESPAWN_BLACK_HOLE, true);
                who->ToCreature()->ForcedDespawn(1*IN_MILLISECONDS);
                me->DealDamage(me, me->GetHealth());
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (arcaneBarrageTimer <= diff)
            {
                DoCast(RAID_MODE(SPELL_ARCANE_BARAGE_10, SPELL_ARCANE_BARAGE_25));
                arcaneBarrageTimer = 5*IN_MILLISECONDS;
            } else arcaneBarrageTimer -= diff;
        }
    };
};

class mob_black_hole : public CreatureScript
{
public:
    mob_black_hole() : CreatureScript("mob_black_hole") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_black_holeAI(pCreature);
    }

    struct mob_black_holeAI : public Scripted_NoMovementAI
    {
        mob_black_holeAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
        {
            DoCast(me, SPELL_BLACK_HOLE_SPAWN_VISUAL, true);
            DoCast(me, SPELL_BLACK_HOLE_STATE, true);
            DoCast(me, SPELL_BLACK_HOLE_TRIGGER, true);
            me->setFaction(14);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_PASSIVE);
            me->SetInCombatWithZone();
        }

        void SpellHitTarget(Unit* target, const SpellEntry* spell)
        {
            if (spell->Id == SPELL_BLACK_HOLE_PHASE)
            {
                target->CombatStop();
                target->getHostileRefManager().deleteReferences();
            }
        }
    };
};

class go_planetarium_access : public GameObjectScript
{
public:
    go_planetarium_access() : GameObjectScript("go_planetarium_access") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        InstanceScript* pInstance = go->GetInstanceScript();
		
		if (pInstance->GetBossState(TYPE_YOGGSARON) == DONE)
			if (player->HasItemCount(45796, 1) || player->HasItemCount(45798, 1))
			{
				pInstance->SetBossState(TYPE_ALGALON, SPECIAL);
				go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
				go->SetGoState(GO_STATE_ACTIVE);
			}
			return true;
    }
};

void AddSC_boss_algalon()
{
    new boss_algalon_the_observer();
    new mob_collapsing_star();
    new mob_living_constellation();
    new mob_black_hole();
//    new go_planetarium_access(); // the boss don't start right now.
}
