/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
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
SDName: Boss Ionar
SD%Complete: 90%
SDComment: Timer check
SDCategory: Halls of Lightning
EndScriptData */

#include "ScriptPCH.h"
#include "halls_of_lightning.h"

enum eEnums
{
    SAY_AGGRO                               = -1602011,
    SAY_SLAY_1                              = -1602012,
    SAY_SLAY_2                              = -1602013,
    SAY_SLAY_3                              = -1602014,
    SAY_DEATH                               = -1602015,
    SAY_SPLIT_1                             = -1602016,
    SAY_SPLIT_2                             = -1602017,

    SPELL_BALL_LIGHTNING_N                  = 52780,
    SPELL_BALL_LIGHTNING_H                  = 59800,
    SPELL_STATIC_OVERLOAD_N                 = 52658,
    SPELL_STATIC_OVERLOAD_H                 = 59795,

    SPELL_DISPERSE                          = 52770,
    SPELL_SUMMON_SPARK                      = 52746,
    SPELL_SPARK_DESPAWN                     = 52776,

    //Spark of Ionar
    SPELL_SPARK_VISUAL_TRIGGER_N            = 52667,
    SPELL_SPARK_VISUAL_TRIGGER_H            = 59833,

    NPC_SPARK_OF_IONAR                      = 28926,

    MAX_SPARKS                              = 5,
    MAX_SPARK_DISTANCE                      = 90,       // Distance to boss - prevent runs through the whole instance
    POINT_CALLBACK                          = 0
};

/*######
## Boss Ionar
######*/

class boss_ionar : public CreatureScript
{
public:
    boss_ionar() : CreatureScript("boss_ionar") { }

    bool EffectDummyCreature(Unit* /*pCaster*/, uint32 uiSpellId, uint32 uiEffIndex, Creature* pCreatureTarget)
    {
        //always check spellid and effectindex
        if (uiSpellId == SPELL_DISPERSE && uiEffIndex == 0)
        {
            if (pCreatureTarget->GetEntry() != NPC_IONAR)
                return true;

            for (uint8 i = 0; i < MAX_SPARKS; ++i)
                pCreatureTarget->CastSpell(pCreatureTarget, SPELL_SUMMON_SPARK, true);

            pCreatureTarget->AttackStop();
            pCreatureTarget->SetVisible(false);
            pCreatureTarget->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_DISABLE_MOVE);

            pCreatureTarget->GetMotionMaster()->Clear();
            pCreatureTarget->GetMotionMaster()->MoveIdle();

            //always return true when we are handling this spell and effect
            return true;
        }
        return false;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_ionarAI(pCreature);
    }

struct boss_ionarAI : public ScriptedAI
{
    boss_ionarAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceScript();
    }

    InstanceScript* m_pInstance;

    std::list<uint64> m_lSparkGUIDList;

    bool m_bIsSplitPhase;
    uint32 m_uiSplit_Timer;
    uint32 m_uiSparkAtHomeCount;

    uint32 m_uiStaticOverload_Timer;
    uint32 m_uiBallLightning_Timer;

    uint32 m_uiHealthAmountModifier;

    void Reset()
    {
        m_lSparkGUIDList.clear();

        m_bIsSplitPhase = true;
        m_uiSplit_Timer = 25000;
        m_uiSparkAtHomeCount = 0;

        m_uiStaticOverload_Timer = 5000 + rand()%1000;
        m_uiBallLightning_Timer = 10000 + rand()%1000;

        m_uiHealthAmountModifier = 1;

        if (me->IsVisible() == false)
            me->SetVisible(true);
    }

    void AttackedBy(Unit* pAttacker)
    {
        if (me->getVictim())
            return;

        if (me->IsVisible() == false)
            return;

        AttackStart(pAttacker);
    }

    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_AGGRO, me);

        if (m_pInstance)
            m_pInstance->SetData(TYPE_IONAR, IN_PROGRESS);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_IONAR, NOT_STARTED);
    }

    void AttackStart(Unit* pWho)
    {
        if (me->Attack(pWho, true))
        {
            me->AddThreat(pWho, 0.0f);
            me->SetInCombatWith(pWho);
            pWho->SetInCombatWith(me);

            if (me->IsVisible() != false)
                me->GetMotionMaster()->MoveChase(pWho);
        }
    }

        void JustDied(Unit* /*killer*/)
        {
            DoScriptText(SAY_DEATH, me);
		DespawnSpark();

            if (m_pInstance)
                m_pInstance->SetData(TYPE_IONAR, DONE);
        }

        void KilledUnit(Unit * /*victim*/)
    {
        DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2,SAY_SLAY_3), me);
    }

    void DespawnSpark()
    {
        if (m_lSparkGUIDList.empty())
            return;

        for (std::list<uint64>::const_iterator itr = m_lSparkGUIDList.begin(); itr != m_lSparkGUIDList.end(); ++itr)
        {
            if (Creature* pTemp = me->GetMap()->GetCreature(*itr))
            {
                if (pTemp->isAlive())
                    pTemp->ForcedDespawn();
            }
        }
        m_lSparkGUIDList.clear();
    }

    //make sparks come back
    void CallBackSparks()
    {
        //should never be empty here, but check
        if (m_lSparkGUIDList.empty())
            return;

        Position pos;
        me->GetPosition(&pos);

        for (std::list<uint64>::const_iterator itr = m_lSparkGUIDList.begin(); itr != m_lSparkGUIDList.end(); ++itr)
        {
            if (Creature* pSpark = Unit::GetCreature(*me, *itr))
            {
                if (pSpark->isAlive())
                {
                    // Interrupt attack to prevent further attacking player
                    pSpark->AttackStop();

                    if (pSpark->GetMotionMaster()->GetCurrentMovementGeneratorType() == TARGETED_MOTION_TYPE)
                        pSpark->GetMotionMaster()->MovementExpired();

                    //now handle by db
                    //pSpark->SetSpeed(MOVE_RUN, pSpark->GetCreatureInfo()->speed * 2);
                    pSpark->GetMotionMaster()->MovePoint(POINT_CALLBACK, pos);
                    pSpark->SetReactState(REACT_PASSIVE) ;
                }
            }
        }
    }

    void RegisterSparkAtHome()
    {
        ++m_uiSparkAtHomeCount;
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_SPARK_OF_IONAR)
        {
            pSummoned->CastSpell(pSummoned, DUNGEON_MODE(SPELL_SPARK_VISUAL_TRIGGER_N,SPELL_SPARK_VISUAL_TRIGGER_H), true);

            // You can do nothing against these npcs but only run away!
            // They must never get damage at all!
            pSummoned->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_NORMAL, true);
            pSummoned->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);

            Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true);

            if (me->getVictim())
                pSummoned->AI()->AttackStart(pTarget ? pTarget : me->getVictim());

            m_lSparkGUIDList.push_back(pSummoned->GetGUID());
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Splitted
        if (me->IsVisible() == false)
        {
            // Reset if there is no target anymore!
            if (!UpdateVictim())
            {
                DespawnSpark();
                EnterEvadeMode();
            }

            if (m_uiSplit_Timer <= uiDiff)
            {
                m_uiSplit_Timer = 2500;

                // Return sparks to where Ionar splitted
                if (m_bIsSplitPhase)
                {
                    CallBackSparks();
                    m_bIsSplitPhase = false;
                }
                // Lightning effect and restore Ionar
                else if (m_uiSparkAtHomeCount == MAX_SPARKS)
                {
                    me->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_NORMAL, false);
                    me->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, false);
                    me->SetVisible(true);

                    DoCast(me, SPELL_SPARK_DESPAWN, false);

                    DespawnSpark();

                    m_uiSparkAtHomeCount = 0;
                    m_uiSplit_Timer = 25000;
                    m_bIsSplitPhase = true;

                    if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != TARGETED_MOTION_TYPE)
                    {
                        if (me->getVictim())
                            me->GetMotionMaster()->MoveChase(me->getVictim());
                    }
                }
            }
            else
                m_uiSplit_Timer -= uiDiff;

            return;
        }

        //Return since we have no target
        if (!UpdateVictim())
            return;

        if (m_uiStaticOverload_Timer <= uiDiff)
        {
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                DoCast(pTarget, DUNGEON_MODE(SPELL_STATIC_OVERLOAD_N, SPELL_STATIC_OVERLOAD_H));

            m_uiStaticOverload_Timer = 5000 + rand()%1000;
        }
        else
            m_uiStaticOverload_Timer -= uiDiff;

        if (m_uiBallLightning_Timer <= uiDiff)
        {
            DoCast(me->getVictim(), DUNGEON_MODE(SPELL_BALL_LIGHTNING_N, SPELL_BALL_LIGHTNING_H));
            m_uiBallLightning_Timer = 10000 + rand()%1000;
        }
        else
            m_uiBallLightning_Timer -= uiDiff;

        // Health check
        if ((me->GetHealth()*100 / me->GetMaxHealth()) < (100-(20*m_uiHealthAmountModifier)))
        {
            ++m_uiHealthAmountModifier;

            DoScriptText(RAND(SAY_SPLIT_1,SAY_SPLIT_2), me);

            if (me->IsNonMeleeSpellCasted(false))
                me->InterruptNonMeleeSpells(false);

            DoCast(me, SPELL_DISPERSE);
        }

        DoMeleeAttackIfReady();
    }
};

bool OnEffectDummyCreature(Unit* pCaster, uint32 uiSpellId, uint32 uiEffIndex, Creature* pCreatureTarget)
{
    //always check spellid and effectindex
    if (uiSpellId == SPELL_DISPERSE && uiEffIndex == 0)
    {
        if (pCreatureTarget->GetEntry() != NPC_IONAR)
            return true;

        for (uint8 i = 0; i < MAX_SPARKS; ++i)
            pCreatureTarget->CastSpell(pCreatureTarget, SPELL_SUMMON_SPARK, true);

        pCreatureTarget->AttackStop();
        pCreatureTarget->SetVisible(false);

        // he never must get damage (e.g. through aoe) if he isn't there
        pCreatureTarget->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_NORMAL, true);
        pCreatureTarget->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);

        if (pCreatureTarget->GetMotionMaster()->GetCurrentMovementGeneratorType() == TARGETED_MOTION_TYPE)
            pCreatureTarget->GetMotionMaster()->MovementExpired();

        //always return true when we are handling this spell and effect
        return true;
    }
    return false;
}
};
/*######
## mob_spark_of_ionar
######*/

class mob_spark_of_ionar : public CreatureScript
{
public:
    mob_spark_of_ionar() : CreatureScript("mob_spark_of_ionar") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_spark_of_ionarAI(pCreature);
    }

struct mob_spark_of_ionarAI : public ScriptedAI
{
    mob_spark_of_ionarAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceScript();
    }

    InstanceScript* m_pInstance;

    uint32 uiCheckTimer;

    void Reset()
    {
        uiCheckTimer = 2000;
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE || !m_pInstance)
            return;

        if (uiPointId == POINT_CALLBACK)
        {
            if (Creature* pIonar = m_pInstance->instance->GetCreature(m_pInstance->GetData64(DATA_IONAR)))
            {
                if (!pIonar->isAlive())
                {
                    if (me->isAlive())
                        me->ForcedDespawn();

                    return;
                }

                if (boss_ionar::boss_ionarAI* pIonarAI = dynamic_cast<boss_ionar::boss_ionarAI*>(pIonar->AI()))
                    pIonarAI->RegisterSparkAtHome();
            }
            else
                if (me->isAlive())
                    me->ForcedDespawn();
        }
    }

    void EnterCombat(Unit* who)
    {   // Prevent to get aggro / start attack if we move home
        if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
            return;

        ScriptedAI::EnterCombat(who);
    }

    void AttackStart(Unit* pWho)
    {   // Prevent to get aggro / start attack if we move home
        if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == POINT_MOTION_TYPE)
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Despawn since we have no target and the encounter is not running
        if (!UpdateVictim() && m_pInstance && m_pInstance->GetData(TYPE_IONAR) != IN_PROGRESS)
        {
            if (me->isAlive())
                me->ForcedDespawn();

            return;
        }

        // Prevent them to follow players through the whole instance
        if (uiCheckTimer <= uiDiff)
        {
            if (m_pInstance)
            {
                Creature* pIonar = m_pInstance->instance->GetCreature(m_pInstance->GetData64(DATA_IONAR));
                if (pIonar && pIonar->isAlive())
                {
                    if (me->GetDistance(pIonar) > MAX_SPARK_DISTANCE)
                    {
                        Position pos;
                        pIonar->GetPosition(&pos);

                        // Interrupt attack to prevent further attacking player
                        me->AttackStop();

                        if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == TARGETED_MOTION_TYPE)
                            me->GetMotionMaster()->MovementExpired();

                        //now handle by db
                        //me->SetSpeed(MOVE_RUN, me->GetCreatureInfo()->speed * 2);
                        me->GetMotionMaster()->MovePoint(POINT_CALLBACK, pos);
                    }
                }
                else
                    if (me->isAlive())
                        me->ForcedDespawn();
            }
                uiCheckTimer = 2*IN_MILLISECONDS;
        }
        else
            uiCheckTimer -= uiDiff;

        // No melee attack at all!
    }
};

};


void AddSC_boss_ionar()
{
    new boss_ionar();
    new mob_spark_of_ionar();
}
