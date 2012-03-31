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

//Razuvious - NO TEXT sound only
//8852 aggro01 - Hah hah, I'm just getting warmed up!
//8853 aggro02 Stand and fight!
//8854 aggro03 Show me what you've got!
//8861 slay1 - You should've stayed home!
//8863 slay2-
//8858 cmmnd3 - You disappoint me, students!
//8855 cmmnd1 - Do as I taught you!
//8856 cmmnd2 - Show them no mercy!
//8859 cmmnd4 - The time for practice is over! Show me what you've learned!
//8861 Sweep the leg! Do you have a problem with that?
//8860 death - An honorable... death...
//8947 - Aggro Mixed? - ?

#define SOUND_AGGRO     RAND(8852,8853,8854)
#define SOUND_SLAY      RAND(8861,8863)
#define SOUND_COMMND    RAND(8855,8856,8858,8859,8861)
#define SOUND_DEATH     8860
#define SOUND_AGGROMIX  8847

#define SPELL_UNBALANCING_STRIKE    26613
#define SPELL_DISRUPTING_SHOUT      RAID_MODE(29107,55543)
#define SPELL_JAGGED_KNIFE          55550
#define SPELL_HOPELESS              29125

#define NPC_DEATH_KNIGHT_UNDERSTUDY 16803

enum Events
{
    EVENT_NONE,
    EVENT_STRIKE,
    EVENT_SHOUT,
    EVENT_KNIFE,
    EVENT_COMMAND,
};

class boss_razuvious : public CreatureScript
{
public:
    boss_razuvious() : CreatureScript("boss_razuvious") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_razuviousAI (pCreature);
    }

struct boss_razuviousAI : public BossAI
{
    boss_razuviousAI(Creature *c) : BossAI(c, BOSS_RAZUVIOUS) {}

    std::list<Creature*> DeathKnight ;

    void KilledUnit(Unit* victim)
    {
        if (!(rand()%3))
            DoPlaySoundToSet(me, SOUND_SLAY);
    }

    void Reset()
    {
        GetCreatureListWithEntryInGrid(DeathKnight, me, NPC_DEATH_KNIGHT_UNDERSTUDY, 50.0) ;
        if(!DeathKnight.empty())
        {
            for(std::list<Creature*>::iterator iter = DeathKnight.begin(); iter != DeathKnight.end(); ++iter)
                if ((*iter)->isDead())
                {
                    (*iter)->RemoveCorpse();
                    (*iter)->Respawn();
                }
        }
    }

    void DamageTaken(Unit* pDone_by, uint32& uiDamage)
    {
        // Damage done by the controlled Death Knight understudies should also count toward damage done by players
        if(pDone_by->GetTypeId() == TYPEID_UNIT && (pDone_by->GetEntry() == 16803 || pDone_by->GetEntry() == 29941))
        {
            me->LowerPlayerDamageReq(uiDamage);
        }
    }

    void JustDied(Unit* /*killer*/)
    {
        _JustDied();
        DoPlaySoundToSet(me, SOUND_DEATH);
        if(!DeathKnight.empty())
        {
            for(std::list<Creature*>::iterator iter = DeathKnight.begin(); iter != DeathKnight.end(); ++iter)
                if (!(*iter)->isDead())
                {
                    me->CastSpell((*iter),SPELL_HOPELESS,true) ;
                }
        }
    }

    void EnterCombat(Unit * /*who*/)
    {
        _EnterCombat();
        if(!DeathKnight.empty())
        {
            for(std::list<Creature*>::iterator iter = DeathKnight.begin(); iter != DeathKnight.end(); ++iter)
                if (!(*iter)->isDead())
                {
                    if(Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                    {
                        (*iter)->SetInCombatWithZone() ;
                        (*iter)->AI()->AttackStart(pTarget) ;
                    }
                }
        }
        DoPlaySoundToSet(me, SOUND_AGGRO);
        events.ScheduleEvent(EVENT_STRIKE, 30000);
        events.ScheduleEvent(EVENT_SHOUT, 25000);
        events.ScheduleEvent(EVENT_COMMAND, 40000);
        events.ScheduleEvent(EVENT_KNIFE, 10000);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_STRIKE:
                    DoCast(me->getVictim(), SPELL_UNBALANCING_STRIKE);
                    events.ScheduleEvent(EVENT_STRIKE, 30000);
                    return;
                case EVENT_SHOUT:
                    DoCastAOE(SPELL_DISRUPTING_SHOUT);
                    events.ScheduleEvent(EVENT_SHOUT, 25000);
                    return;
                case EVENT_KNIFE:
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f))
                        DoCast(pTarget, SPELL_JAGGED_KNIFE);
                    events.ScheduleEvent(EVENT_KNIFE, 10000);
                    return;
                case EVENT_COMMAND:
                    DoPlaySoundToSet(me, SOUND_COMMND);
                    events.ScheduleEvent(EVENT_COMMAND, 40000);
                    return;
            }
        }

        DoMeleeAttackIfReady();
    }
};

};

/*
** npc_death_knight_understudy
*/
enum deathKnightUnderstudySpells
{
    SPELL_BONE_BARRIER        = 29061,
    SPELL_TAUNT                = 61696,
    SPELL_BLOOD_STRIKE        = 29060
};

class npc_death_knight_understudy : public CreatureScript
{
public:
    npc_death_knight_understudy() : CreatureScript("npc_death_knight_understudy") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_death_knight_understudyAI (pCreature);
    }
struct  npc_death_knight_understudyAI : public ScriptedAI
{
    npc_death_knight_understudyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = pCreature->GetInstanceScript();
    }

    InstanceScript* pInstance;

    uint32 boneBarrierTimer ;
    uint32 tauntTimer ;
    uint32 bloodStrikeTimer ;

    void Reset()
    {
        boneBarrierTimer = urand(5000, 8000) ;
        tauntTimer = urand(15000, 18000) ;
        bloodStrikeTimer = urand(9000, 14000) ;
        if(pInstance)
        {
            if(pInstance->GetBossState(BOSS_RAZUVIOUS) == IN_PROGRESS)
            {
                me->SetInCombatWithZone() ;
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if(boneBarrierTimer <= diff)
        {
            DoCast(SPELL_BONE_BARRIER) ;
            boneBarrierTimer = urand(30000, 40000) ;
        } else boneBarrierTimer -= diff ;

        if(tauntTimer <= diff)
        {
            DoCast(SPELL_TAUNT) ;
            tauntTimer = urand(20000, 30000) ;
        } else tauntTimer -= diff ;

        if(bloodStrikeTimer <= diff)
        {
            DoCast(SPELL_BLOOD_STRIKE) ;
            bloodStrikeTimer = urand(9000, 15000) ;
        } else bloodStrikeTimer -= diff ;
    }
};
};

void AddSC_boss_razuvious()
{
    new boss_razuvious();
    new npc_death_knight_understudy();
}
