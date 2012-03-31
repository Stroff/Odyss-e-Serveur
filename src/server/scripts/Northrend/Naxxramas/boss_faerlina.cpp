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
#include "naxxramas.h"

enum Yells
{
    SAY_GREET       = -1533009,
    SAY_AGGRO_1     = -1533010,
    SAY_AGGRO_2     = -1533011,
    SAY_AGGRO_3     = -1533012,
    SAY_AGGRO_4     = -1533013,
    SAY_SLAY_1      = -1533014,
    SAY_SLAY_2      = -1533015,
    SAY_DEATH       = -1533016
};
enum Creatures
{
    NPC_WORSHIPPER        = 16506,
    NPC_FOLLOWER        = 16505
};
//#define SOUND_RANDOM_AGGRO  8955                            //soundId containing the 4 aggro sounds, we not using this

enum Spells
{
    SPELL_POISON_BOLT_VOLLEY    = 28796,
    H_SPELL_POISON_BOLT_VOLLEY  = 54098,
    SPELL_RAIN_OF_FIRE          = 28794,
    H_SPELL_RAIN_OF_FIRE        = 54099,
    SPELL_FRENZY                = 28798,
    H_SPELL_FRENZY              = 54100,
    SPELL_WIDOWS_EMBRACE        = 28732,
    H_SPELL_WIDOWS_EMBRACE      = 54097,
    SPELL_FIREBALL              = 54095,
    SPELL_FIREBALL_H            = 54096,
    SPELL_SILENCE                = 54093,
    SPELL_BERSERKER_CHARGE        = 56107
};

enum Events
{
    EVENT_NONE,
    EVENT_POISON,
    EVENT_FIRE,
    EVENT_FRENZY
};

enum Achievements
{
    ACHIEVEMENT_MOMMA_SAID_KNOCK_YOU_OUT_10 = 1997,
    ACHIEVEMENT_MOMMA_SAID_KNOCK_YOU_OUT_25 = 2140
};

class boss_faerlina : public CreatureScript
{
public:
    boss_faerlina() : CreatureScript("boss_faerlina") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_faerlinaAI (pCreature);
    }

struct boss_faerlinaAI : public BossAI
{
    boss_faerlinaAI(Creature *c) : BossAI(c, BOSS_FAERLINA), greet(false) 
    {
        pInstance = c->GetInstanceScript();
    }

    InstanceScript *pInstance;
    bool greet;
    bool doDelayFrenzy;
    bool bAchievement;

        void EnterCombat(Unit * /*who*/)
    {
        _EnterCombat();
        DoScriptText(RAND(SAY_AGGRO_1,SAY_AGGRO_2,SAY_AGGRO_3,SAY_AGGRO_4), me);
        events.ScheduleEvent(EVENT_POISON, urand(10000,15000));
        events.ScheduleEvent(EVENT_FIRE, urand(6000,18000));
        events.ScheduleEvent(EVENT_FRENZY, urand(60000,80000));
    }

    void Reset()
    {
        std::list<Creature*> lWorshipperList;
        GetCreatureListWithEntryInGrid(lWorshipperList, me, NPC_WORSHIPPER, 100.0f);
        if (!lWorshipperList.empty())
        {
            for(std::list<Creature*>::iterator iter = lWorshipperList.begin(); iter != lWorshipperList.end(); ++iter)
                if ((*iter)->isDead())
                {
                    (*iter)->RemoveCorpse();
                    (*iter)->Respawn();
                }
        }
        if (GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL)
        {
            std::list<Creature*> lFollowerList;
            GetCreatureListWithEntryInGrid(lFollowerList, me, NPC_FOLLOWER, 100.0f);
            if (!lFollowerList.empty())
            {
                for(std::list<Creature*>::iterator iter = lFollowerList.begin(); iter != lFollowerList.end(); ++iter)
                    if ((*iter)->isDead())
                    {
                        (*iter)->RemoveCorpse();
                        (*iter)->Respawn();
                    }
            }
        }
    doDelayFrenzy = false;
        bAchievement = true;
        _Reset();
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (!greet && who->GetTypeId() == TYPEID_PLAYER)
        {
            DoScriptText(SAY_GREET, me);
            greet = true;
        }
        BossAI::MoveInLineOfSight(who);
    }

        void KilledUnit(Unit* /*victim*/)
    {
        if (!(rand()%3))
            DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2), me);
    }

        void JustDied(Unit* /*Killer*/)
    {
        _JustDied();
        DoScriptText(SAY_DEATH, me);

        if (instance && bAchievement)
            instance->DoCompleteAchievement(RAID_MODE(ACHIEVEMENT_MOMMA_SAID_KNOCK_YOU_OUT_10,ACHIEVEMENT_MOMMA_SAID_KNOCK_YOU_OUT_25));
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (doDelayFrenzy && !me->HasAura(RAID_MODE(SPELL_WIDOWS_EMBRACE, H_SPELL_WIDOWS_EMBRACE)))
        {
            doDelayFrenzy = false;
            DoCast(me, RAID_MODE(SPELL_FRENZY, H_SPELL_FRENZY), true);
        }

        events.Update(diff);

        if (me->HasUnitState(UNIT_STAT_CASTING))
            return;

        while(uint32 eventId = events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_POISON:
                    if (!me->HasAura(RAID_MODE(SPELL_WIDOWS_EMBRACE,H_SPELL_WIDOWS_EMBRACE)))
                        DoCastAOE(RAID_MODE(SPELL_POISON_BOLT_VOLLEY,H_SPELL_POISON_BOLT_VOLLEY));
                    events.ScheduleEvent(EVENT_POISON, urand(8000,15000));
                    break;
                case EVENT_FIRE:
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                        DoCast(pTarget, RAID_MODE(SPELL_RAIN_OF_FIRE, H_SPELL_RAIN_OF_FIRE));
                    events.ScheduleEvent(EVENT_FIRE, urand(6000,18000));
                    break;
                case EVENT_FRENZY:
                    // TODO : Add Text
                    if (!me->HasAura(RAID_MODE(SPELL_WIDOWS_EMBRACE,H_SPELL_WIDOWS_EMBRACE)))
                        DoCast(me, RAID_MODE(SPELL_FRENZY, H_SPELL_FRENZY));
                    else
                        doDelayFrenzy = true;

                    events.ScheduleEvent(EVENT_FRENZY, urand(60000,80000));
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }
    
    void SpellHit(Unit* caster, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_WIDOWS_EMBRACE || spell->Id == H_SPELL_WIDOWS_EMBRACE)
        {
             // TODO : Add Text
             bAchievement = false;
             doDelayFrenzy = true;
             me->Kill(caster);
        }
    }
};

};


class mob_faerlina_add : public CreatureScript
{
public:
    mob_faerlina_add() : CreatureScript("mob_faerlina_add") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_faerlina_addAI (pCreature);
    }

    struct mob_faerlina_addAI : public ScriptedAI
    {
        mob_faerlina_addAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            pInstance = pCreature->GetInstanceScript();
        }

        InstanceScript *pInstance;

        void Reset()
        {
            if (GetDifficulty() == RAID_DIFFICULTY_10MAN_NORMAL) {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, SPELL_EFFECT_BIND, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
            }
        }

        void JustDied(Unit * /*killer*/)
        {
            if (pInstance && GetDifficulty() == RAID_DIFFICULTY_10MAN_NORMAL)
            {
                if (Creature *pFaerlina = pInstance->instance->GetCreature(pInstance->GetData64(DATA_FAERLINA)))
                    DoCast(pFaerlina, SPELL_WIDOWS_EMBRACE);
            }
        }
    };

};

/*
** mob_worshippers
*/
class mob_worshippers : public CreatureScript
{
public:
    mob_worshippers() : CreatureScript("mob_worshippers") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_worshippersAI (pCreature);
    }
struct  mob_worshippersAI : public ScriptedAI
{
    mob_worshippersAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = pCreature->GetInstanceScript();
    }

    InstanceScript *pInstance;
    uint32 m_uiFireball_Timer;

    void Reset()
    {
        //if (GetDifficulty() == RAID_DIFFICULTY_10MAN_NORMAL) {
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, SPELL_EFFECT_BIND, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
        m_uiFireball_Timer = 5000;
        //}
    }

    void JustDied(Unit *killer)
    {
        if (Creature *pFaerlina = pInstance->instance->GetCreature(pInstance->GetData64(DATA_FAERLINA)))
            DoCast(pFaerlina, RAID_MODE(SPELL_WIDOWS_EMBRACE,H_SPELL_WIDOWS_EMBRACE));
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;

        if (m_uiFireball_Timer < uiDiff)
        {
            DoCast(me->getVictim(),  RAID_MODE(SPELL_FIREBALL, SPELL_FIREBALL_H));
            m_uiFireball_Timer = 7000 + rand()%4000;
        }
        else m_uiFireball_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
    
};
};

/*
** mob_followers
*/
class mob_followers : public CreatureScript
{
public:
    mob_followers() : CreatureScript("mob_followers") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_followersAI (pCreature);
    }
struct  mob_followersAI : public ScriptedAI
{
    mob_followersAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = (InstanceScript*)pCreature->GetInstanceScript();
        m_bIsHeroicMode = pCreature->GetMap()->IsHeroic();
        Reset();
    }

    InstanceScript* pInstance;
    bool m_bIsHeroicMode;

    uint32 m_uiSilence_Timer;
    uint32 m_uiBerserkerCharge_Timer;

    void Reset()
    {
        m_uiSilence_Timer = 9000;
        m_uiBerserkerCharge_Timer = 5000;
    }

    void JustDied(Unit *killer)
    {
        if (Creature *pFaerlina = pInstance->instance->GetCreature(pInstance->GetData64(DATA_FAERLINA)))
            DoCast(pFaerlina, H_SPELL_WIDOWS_EMBRACE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;

        if (m_uiBerserkerCharge_Timer < uiDiff)
        {
            if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 40, true))
            {
                DoCast(pTarget, SPELL_BERSERKER_CHARGE);
            }
            m_uiBerserkerCharge_Timer = urand(15000, 19000);
        }
        else m_uiBerserkerCharge_Timer -= uiDiff;

        if (m_uiSilence_Timer < uiDiff)
        {
            DoCastAOE(SPELL_SILENCE);
            m_uiSilence_Timer = urand(15000, 19000);
        }
        else m_uiSilence_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};
};

void AddSC_boss_faerlina()
{
    new boss_faerlina();
    new mob_faerlina_add();
    new mob_worshippers();
    new mob_followers();
}
