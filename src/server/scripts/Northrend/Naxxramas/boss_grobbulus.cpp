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

/* ScriptData
SDName: Boss_Grobbulus
SDAuthor: ckegg
SD%Complete: 0
SDComment: Place holder
SDCategory: Naxxramas
EndScriptData */

#include "ScriptPCH.h"
#include "naxxramas.h"

#define SPELL_BOMBARD_SLIME         28280

#define SPELL_POISON_CLOUD          28240
#define SPELL_MUTATING_INJECTION    28169
#define SPELL_SLIME_SPRAY           28157
#define H_SPELL_SLIME_SPRAY         54364
#define SPELL_BERSERK               26662
#define SPELL_POISON_CLOUD_ADD_N    28158
#define SPELL_POISON_CLOUD_ADD_H    54362

#define EVENT_BERSERK   1
#define EVENT_CLOUD     2
#define EVENT_INJECT    3
#define EVENT_SPRAY     4

#define MOB_FALLOUT_SLIME   16290
#define MOB_GROBBOLUS_CLOUD    16363

class boss_grobbulus : public CreatureScript
{
public:
    boss_grobbulus() : CreatureScript("boss_grobbulus") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_grobbulusAI (pCreature);
    }

struct boss_grobbulusAI : public BossAI
{
        boss_grobbulusAI(Creature *c) : BossAI(c, BOSS_GROBBULUS)
    {
        me->ApplySpellImmune(0, IMMUNITY_ID, RAID_MODE(SPELL_POISON_CLOUD_ADD_N, SPELL_POISON_CLOUD_ADD_H), true);
        m_pInstance = (InstanceScript*)c->GetInstanceScript();
        Reset();
    }

    InstanceScript* m_pInstance;

    uint32 PoisonCloud_Timer;
    uint32 MutatingInjection_Timer;
    uint32 SlimeSpary_Timer;
    uint32 Enrage_Timer;

    void Reset()
    {
        PoisonCloud_Timer = 15000;
        MutatingInjection_Timer = 20000;
        SlimeSpary_Timer = 15000+rand()%15000;
        Enrage_Timer = 720000;
    }

        void EnterCombat(Unit * /*who*/)
        {
/* Hack odyssee
            _EnterCombat();
            events.ScheduleEvent(EVENT_CLOUD, 15000);
            events.ScheduleEvent(EVENT_INJECT, 20000);
            events.ScheduleEvent(EVENT_SPRAY, 15000+rand()%15000); //not sure
            events.ScheduleEvent(EVENT_BERSERK, 12*60000);
*/
        }

    void SpellHitTarget(Unit *pTarget, const SpellEntry *spell)
    {
        if(spell->Id == SPELL_SLIME_SPRAY || spell->Id == H_SPELL_SLIME_SPRAY)
        {
            if (Creature* pTemp = me->SummonCreature(MOB_FALLOUT_SLIME, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 1000))
                if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0,true))
                {
                    pTemp->AddThreat(pTarget,0.0f);
                    pTemp->AI()->AttackStart(pTarget);
                }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (PoisonCloud_Timer < diff)
        {
            DoCast(me, SPELL_POISON_CLOUD);
            PoisonCloud_Timer = 15000;
        }else PoisonCloud_Timer -= diff;

        if (MutatingInjection_Timer < diff)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0,true))
                DoCast(target, SPELL_MUTATING_INJECTION);

            MutatingInjection_Timer = 20000;
        }else MutatingInjection_Timer -= diff;

        if (SlimeSpary_Timer < diff)
        {
            DoCast(me, RAID_MODE(SPELL_SLIME_SPRAY, H_SPELL_SLIME_SPRAY));
            SlimeSpary_Timer = 15000+rand()%15000;
        }else SlimeSpary_Timer -= diff;

        if (Enrage_Timer < diff)
        {
            DoCast(me, SPELL_BERSERK);
            Enrage_Timer = 300000;
        }else Enrage_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

};

class npc_grobbulus_poison_cloud : public CreatureScript
{
public:
    npc_grobbulus_poison_cloud() : CreatureScript("npc_grobbulus_poison_cloud") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_grobbulus_poison_cloudAI(pCreature);
    }

struct npc_grobbulus_poison_cloudAI : public Scripted_NoMovementAI
{
    npc_grobbulus_poison_cloudAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        Reset();
    }

    uint32 Cloud_Timer;

    void Reset()
    {
        Cloud_Timer = 1000;
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }

    void UpdateAI(const uint32 diff)
    {
            if (Cloud_Timer <= diff)
        {
                DoCast(me, 59116);
            Cloud_Timer = 10000;
        }else Cloud_Timer -= diff;
    }
};

};



void AddSC_boss_grobbulus()
{
    new boss_grobbulus();
    new npc_grobbulus_poison_cloud();
}
