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
SDName: Taerar
SD%Complete: 90
SDComment: Mark of Nature & Teleport NYI
SDCategory: Bosses
EndScriptData */

#include "ScriptPCH.h"

enum eEnums
{
    SAY_AGGRO               = -1000399, //signed for 20021
    SAY_SUMMONSHADE         = -1000400, //signed for 20021

//Spells of Taerar
    SPELL_SLEEP             = 24777,
    SPELL_NOXIOUSBREATH     = 24818,
    SPELL_TAILSWEEP         = 15847,
    SPELL_ARCANEBLAST       = 24857,
    SPELL_BELLOWINGROAR     = 22686,

    SPELL_SUMMONSHADE_1     = 24841,
    SPELL_SUMMONSHADE_2     = 24842,
    SPELL_SUMMONSHADE_3     = 24843,

//Spells of Shades of Taerar
    SPELL_POSIONCLOUD       = 24840,
    SPELL_POSIONBREATH      = 20667
};

uint32 m_auiSpellSummonShade[] =
{
    SPELL_SUMMONSHADE_1, SPELL_SUMMONSHADE_2, SPELL_SUMMONSHADE_3
};

class boss_taerar : public CreatureScript
{
public:
    boss_taerar() : CreatureScript("boss_taerar") { }

    CreatureAI *GetAI(Creature *creature) const
    {
        return new boss_taerarAI(creature);
    }

struct boss_taerarAI : public ScriptedAI
{
    boss_taerarAI(Creature *c) : ScriptedAI(c) {}

    uint32 Sleep_Timer;
    uint32 NoxiousBreath_Timer;
    uint32 TailSweep_Timer;
    //uint32 MarkOfNature_Timer;
    uint32 ArcaneBlast_Timer;
    uint32 BellowingRoar_Timer;
    uint32 Shades_Timer;
    uint32 Summon1_Timer;
    uint32 Summon2_Timer;
    uint32 Summon3_Timer;
    int Rand;
    int RandX;
    int RandY;
    Creature* Summoned;
    bool Shades;

    void Reset()
    {
        Sleep_Timer = 15000 + rand()%5000;
        NoxiousBreath_Timer = 38000;
        TailSweep_Timer = 34000;
        //MarkOfNature_Timer = 45000;
        ArcaneBlast_Timer = 32000;
        BellowingRoar_Timer = 45000;
        Summon1_Timer = 0;
        Summon2_Timer = 0;
        Summon3_Timer = 0;
        Shades_Timer = 15000;                               //The time that Taerar is banished
        Shades = false;
    }

    void EnterCombat(Unit* /*pWho*/)
    {
    }

    void SummonShades(Unit* victim)
    {
        if(!victim)
            return;

        Rand = rand()%15;
        switch (rand()%2)
        {
            case 0: RandX = 0 - Rand; break;
            case 1: RandX = 0 + Rand; break;
        }
        Rand = 0;
        Rand = rand()%15;
        switch (rand()%2)
        {
            case 0: RandY = 0 - Rand; break;
            case 1: RandY = 0 + Rand; break;
        }
        Rand = 0;
        Summoned = DoSpawnCreature(15302, RandX, RandY, 0, 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000);
        if(Summoned)
            (Summoned->AI())->AttackStart(victim);
    }

    void UpdateAI(const uint32 diff)
    {
        if (Shades && Shades_Timer < diff)
        {
            //Become unbanished again
            me->setFaction(14);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            //me->m_canMove = true;
            Shades = false;
        } else if (Shades)
        {
            Shades_Timer -= diff;
            //Do nothing while banished
            return;
        }

        //Return since we have no target
        if (!UpdateVictim())
            return;

        //Sleep_Timer
        if (Sleep_Timer < diff)
        {
            Unit* target = NULL;
            target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true);
            if (target) DoCast(target,SPELL_SLEEP);

            Sleep_Timer = 8000 + rand()%7000;
        }else Sleep_Timer -= diff;

        //NoxiousBreath_Timer
        if (NoxiousBreath_Timer < diff)
        {
            DoCast(me->getVictim(),SPELL_NOXIOUSBREATH);
            NoxiousBreath_Timer = 14000 + rand()%6000;
        } else NoxiousBreath_Timer -= diff;

        //Tailsweep every 2 seconds
        if (TailSweep_Timer < diff)
        {
            if( Unit *target = SelectTarget(SELECT_TARGET_RANDOM,0, 0, true) )
                DoCast(target,SPELL_TAILSWEEP);

            TailSweep_Timer = 2000;
        }else TailSweep_Timer -= diff;

        //MarkOfNature_Timer
        //if (MarkOfNature_Timer < diff)
        //{
        //    DoCast(me->getVictim(),SPELL_MARKOFNATURE);
        //    MarkOfNature_Timer = 45000;
        //}else MarkOfNature_Timer -= diff;

        //ArcaneBlast_Timer
        if (ArcaneBlast_Timer < diff)
        {
            DoCast(me->getVictim(),SPELL_ARCANEBLAST);
            ArcaneBlast_Timer = 7000 + rand()%5000;
        }else ArcaneBlast_Timer -= diff;

        //BellowingRoar_Timer
        if (BellowingRoar_Timer < diff)
        {
            DoCast(me->getVictim(),SPELL_BELLOWINGROAR);
            BellowingRoar_Timer = 20000 + rand()%10000;
        } else BellowingRoar_Timer -= diff;

        //Summon 3 Shades
        if ( !Shades  && (int) (me->GetHealth()*100 / me->GetMaxHealth() +0.5) == 75)
        {
            if (Summon1_Timer < diff)
            {
                //Inturrupt any spell casting
                me->InterruptNonMeleeSpells(false);
                me->setFaction(35);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                //me->m_canMove = false;

                //Cast
                Unit* target = NULL;
                target = SelectTarget(SELECT_TARGET_RANDOM,0, 0, true);
                SummonShades(target);
                SummonShades(target);
                SummonShades(target);
                Summon1_Timer = 120000;
                Shades = true;
                Shades_Timer = 60000;
            } else Summon1_Timer -= diff;
        }

        //Summon 3 Shades
        if ( !Shades  && (int) (me->GetHealth()*100 / me->GetMaxHealth() +0.5) == 50)
        {
            if (Summon2_Timer < diff)
            {
                //Inturrupt any spell casting
                me->InterruptNonMeleeSpells(false);
                me->setFaction(35);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                //me->m_canMove = false;

                //Cast
                Unit* target = NULL;
                target = SelectTarget(SELECT_TARGET_RANDOM,0, 0, true);
                SummonShades(target);
                SummonShades(target);
                SummonShades(target);
                Summon2_Timer = 120000;
                Shades = true;
                Shades_Timer = 60000;
            } else Summon2_Timer -= diff;
        }

        //Summon 3 Shades
        if ( !Shades  && (int) (me->GetHealth()*100 / me->GetMaxHealth() +0.5) == 25)
        {
            if (Summon3_Timer < diff)
            {
                //Inturrupt any spell casting
                me->InterruptNonMeleeSpells(false);
                me->setFaction(35);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                //me->m_canMove = false;

                //Cast
                Unit* target = NULL;
                target = SelectTarget(SELECT_TARGET_RANDOM,0, 0, true);
                SummonShades(target);
                SummonShades(target);
                SummonShades(target);
                Summon3_Timer = 120000;
                Shades = true;
                Shades_Timer = 60000;
            } else Summon3_Timer -= diff;
        }

        DoMeleeAttackIfReady();
    }
};
};

// Shades of Taerar Script
class boss_shadeoftaerar : public CreatureScript
{
public:
    boss_shadeoftaerar() : CreatureScript("boss_shadeoftaerar") { }

    CreatureAI *GetAI(Creature *creature) const
    {
        return new boss_shadeoftaerarAI(creature);
    }
struct boss_shadeoftaerarAI : public ScriptedAI
{
    boss_shadeoftaerarAI(Creature *c) : ScriptedAI(c) {}

    uint32 PoisonCloud_Timer;
    uint32 PosionBreath_Timer;

    void Reset()
    {
        PoisonCloud_Timer = 8000;
        PosionBreath_Timer = 12000;
    }

    void EnterCombat(Unit *who)
    {
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        //PoisonCloud_Timer
        if (PoisonCloud_Timer < diff)
        {
            DoCast(me->getVictim(),SPELL_POSIONCLOUD);
            PoisonCloud_Timer = 30000;
        }else PoisonCloud_Timer -= diff;

        //PosionBreath_Timer
        if (PosionBreath_Timer < diff)
        {
            DoCast(me->getVictim(),SPELL_POSIONBREATH);
            PosionBreath_Timer = 12000;
        }else PosionBreath_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
};

void AddSC_boss_taerar()
{
    new boss_taerar;
    new boss_shadeoftaerar;
}

