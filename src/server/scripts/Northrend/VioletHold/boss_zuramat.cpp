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
#include "violet_hold.h"

enum Spells
{
    SPELL_SHROUD_OF_DARKNESS                    = 54524,
    H_SPELL_SHROUD_OF_DARKNESS                  = 59745,
    SPELL_SUMMON_VOID_SENTRY                    = 54369,
    SPELL_VOID_SHIFT                            = 54361,
    H_SPELL_VOID_SHIFT                          = 59743,
    SPELL_VOID_SHIFTED                               = 54343,

    SPELL_ZURAMAT_ADD_2                         = 54342,
    H_SPELL_ZURAMAT_ADD_2                          = 59747,
    SPELL_SHADOW_BOLT_VOLLEY                       = 54358, // 54342? 54358?
    SPELL_SHADOW_BOLT_VOLLEY_H                       = 59747
};

enum ZuramatCreatures
{
    CREATURE_VOID_SENTRY                        = 29364
};

enum Yells
{
    SAY_AGGRO                                   = -1608037,
    SAY_SLAY_1                                  = -1608038,
    SAY_SLAY_2                                  = -1608039,
    SAY_SLAY_3                                  = -1608040,
    SAY_DEATH                                   = -1608041,
    SAY_SPAWN                                   = -1608042,
    SAY_SHIELD                                  = -1608043,
    SAY_WHISPER                                 = -1608044
};

class boss_zuramat : public CreatureScript
{
public:
    boss_zuramat() : CreatureScript("boss_zuramat") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_zuramatAI (pCreature);
    }

struct boss_zuramatAI : public ScriptedAI
{
    boss_zuramatAI(Creature *c) : ScriptedAI(c), lSummons(me)
    {
        pInstance = c->GetInstanceScript();
    }

    SummonList lSummons;

    InstanceScript* pInstance;

    uint32 SpellVoidShiftTimer;
    uint32 SpellSummonVoidTimer;
    uint32 SpellShroudOfDarknessTimer;

    void Reset()
    {
        lSummons.DespawnAll();
        if (pInstance)
        {
            if (pInstance->GetData(DATA_WAVE_COUNT) == 6)
                pInstance->SetData(DATA_1ST_BOSS_EVENT, NOT_STARTED);
            else if (pInstance->GetData(DATA_WAVE_COUNT) == 12)
                pInstance->SetData(DATA_2ND_BOSS_EVENT, NOT_STARTED);
        }

        SpellShroudOfDarknessTimer = 22000;
        SpellVoidShiftTimer = 15000;
        SpellSummonVoidTimer = 12000;
    }

    void AttackStart(Unit* pWho)
    {
        if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE) || me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        if (me->Attack(pWho, true))
        {
            me->AddThreat(pWho, 0.0f);
            me->SetInCombatWith(pWho);
            pWho->SetInCombatWith(me);
            DoStartMovement(pWho);
        }
    }

    void EnterCombat(Unit* /*who*/)
    {
        DoScriptText(SAY_AGGRO, me);
        if (pInstance)
        {
            if (GameObject *pDoor = pInstance->instance->GetGameObject(pInstance->GetData64(DATA_ZURAMAT_CELL)))
                if (pDoor->GetGoState() == GO_STATE_READY)
                {
                    EnterEvadeMode();
                    return;
                }
            if (pInstance->GetData(DATA_WAVE_COUNT) == 6)
                pInstance->SetData(DATA_1ST_BOSS_EVENT, IN_PROGRESS);
            else if (pInstance->GetData(DATA_WAVE_COUNT) == 12)
                pInstance->SetData(DATA_2ND_BOSS_EVENT, IN_PROGRESS);
        }
    }

    void MoveInLineOfSight(Unit* /*who*/) {}

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        if (SpellSummonVoidTimer <= diff)
        {
            DoCast(me->getVictim(), SPELL_SUMMON_VOID_SENTRY, false);
            SpellSummonVoidTimer = 20000;
        } else SpellSummonVoidTimer -=diff;

        if (SpellVoidShiftTimer <= diff)
        {
             if (Unit* pUnit = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                DoCast(pUnit, DUNGEON_MODE(SPELL_VOID_SHIFT, H_SPELL_VOID_SHIFT));
            SpellVoidShiftTimer = 20000;
        } else SpellVoidShiftTimer -=diff;

        if (SpellShroudOfDarknessTimer <= diff)
        {
            DoCast(me->getVictim(), DUNGEON_MODE(SPELL_SHROUD_OF_DARKNESS, H_SPELL_SHROUD_OF_DARKNESS));
            SpellShroudOfDarknessTimer = 20000;
        } else SpellShroudOfDarknessTimer -=diff;

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/)
    {
        lSummons.DespawnAll();
        DoScriptText(SAY_DEATH, me);

        if (pInstance)
        {
            if (pInstance->GetData(DATA_WAVE_COUNT) == 6)
            {
                pInstance->SetData(DATA_1ST_BOSS_EVENT, DONE);
                pInstance->SetData(DATA_WAVE_COUNT, 7);
            }
            else if (pInstance->GetData(DATA_WAVE_COUNT) == 12)
            {
                pInstance->SetData(DATA_2ND_BOSS_EVENT, DONE);
                pInstance->SetData(DATA_WAVE_COUNT, 13);
            }
        }
    }

    void KilledUnit(Unit * victim)
    {
        if (victim == me)
            return;

        DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2,SAY_SLAY_3), me);
    }

    void JustSummoned(Creature* summon)
    {
        lSummons.Summon(summon);
        //summon->AI()->AttackStart(me->getVictim());
        //summon->AI()->DoCastAOE(HEROIC(SPELL_ZUMARAT_ADD_2, H_SPELL_ZUMARAT_ADD_2));
        //summon->SetPhaseMask(17,true);
    }
};
};

class mob_zuramat_sentry : public CreatureScript
{
public:
    mob_zuramat_sentry() : CreatureScript("mob_zuramat_sentry") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_zuramat_sentryAI (pCreature);
    }

struct  mob_zuramat_sentryAI : public ScriptedAI
{
    mob_zuramat_sentryAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = ((InstanceScript*)pCreature->GetInstanceScript());
        m_bIsRegularMode = !pCreature->GetMap()->IsHeroic();
        SetCombatMovement(false);
    }
    InstanceScript *m_pInstance;
    uint32 checkTimer;
    bool m_bIsRegularMode;

    void EnterCombat(Unit* who)
    {
        checkTimer = 1000;
    }

    void DamageTaken(Unit *done_by, uint32 &damage)
    {
        if(!done_by->HasAura(SPELL_VOID_SHIFTED))
        {
            damage = 0 ;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if(checkTimer)
        {
            if (Creature* pTemp = me->FindNearestCreature(CREATURE_ZURAMAT, 250))
            {
                if(pTemp)
                {
                    if(!pTemp->isAlive())
                    {
                        me->ForcedDespawn();
                    } else {}
                } else { me->ForcedDespawn(); }
            } else { me->ForcedDespawn(); }
        checkTimer = 1000;
        } else checkTimer -=diff;
    }

    void Reset()
    {
        DoCastAOE(DUNGEON_MODE(SPELL_ZURAMAT_ADD_2, H_SPELL_ZURAMAT_ADD_2));
        me->SetPhaseMask(17, true) ;
        DoCast(me, m_bIsRegularMode ? SPELL_SHADOW_BOLT_VOLLEY_H : SPELL_SHADOW_BOLT_VOLLEY);
    }
};
};
void AddSC_boss_zuramat()
{
    new boss_zuramat();
new mob_zuramat_sentry();
}
