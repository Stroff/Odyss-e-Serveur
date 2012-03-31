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

/* Script Data Start
SDName: Boss Commander Stoutbeard
SDAuthor: LordVanMartin
SD%Complete:
SDComment:  Only Horde Heroic
SDCategory:
Script Data End */

/*** SQL START ***
update creature_template set scriptname = 'boss_commander_stoutbeard' where entry = '26796';
update creature_template set scriptname = 'npc_alliance_cleric' where entry = '26805';
*** SQL END ***/
#include "ScriptPCH.h"
#include "nexus.h"

enum Spells
{
    SPELL_FROZEN_PRISON                                    =  47543 ,
    //Commander
    SPELL_BATTLE_SHOUT                                  =  31403 ,
    SPELL_CHARGE                                        =  60067 ,
    SPELL_FRIGHTENING_SHOUT                             =  19134 ,
    SPELL_WHIRLWIND_1                                   =  38619 ,
    SPELL_WHIRLWIND_2                                   =  38618 ,
    //Healer
    SPELL_FLASH_HEAL                                    =  17843 ,
    SPELL_FLASH_HEAL_H                                    =  56919 ,
    SPELL_SHIELD                                        =  17139 ,
    SPELL_SHIELD_H                                        =  35944 ,
    SPELL_DEATH                                            =  47697 ,
    SPELL_DEATH_H                                        =  56920
};


#define CREATURE_ALLIANCE_CLERIC                            26805
#define CREATURE_COMMANDER_STOUTBEARD                        26796

//not used
//Yell
#define SAY_AGGRO                                              -1576021
#define SAY_KILL                                               -1576022
#define SAY_DEATH                                              -1576023

class boss_commander_stoutbeard : public CreatureScript
{
public:
    boss_commander_stoutbeard() : CreatureScript("boss_commander_stoutbeard") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_commander_stoutbeardAI (pCreature);
    }

struct boss_commander_stoutbeardAI : public ScriptedAI
{
    boss_commander_stoutbeardAI(Creature *c) : ScriptedAI(c), summons(me)
    {
        pInstance = c->GetInstanceScript();
        Reset();
    }

    SummonList summons;
    uint32 battleShoutTimer ;
    uint32 whirlwindTimer ;
    uint32 frighteningShoutTimer ;
    InstanceScript* pInstance;

    bool frozen;

    void Reset() 
    {
        summons.DespawnAll();
        battleShoutTimer = urand(3000, 5000) ;
        whirlwindTimer = urand(7000, 11000);
        frighteningShoutTimer = urand(14000, 18000) ;
        me->SummonCreature(CREATURE_ALLIANCE_CLERIC, me->GetPositionX()+3, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_DEAD_DESPAWN) ;
        me->SummonCreature(CREATURE_ALLIANCE_CLERIC, me->GetPositionX()-3, me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_DEAD_DESPAWN) ;
        if (pInstance)
            pInstance->SetData(DATA_COMMANDER_EVENT, NOT_STARTED);
        frozen = true;
    }

    void EnterCombat(Unit* who) 
    {
        me->RemoveAurasDueToSpell(SPELL_FROZEN_PRISON) ;
        if(Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 200, true))
            DoCast(target, SPELL_CHARGE) ;
        if (pInstance)
            pInstance->SetData(DATA_COMMANDER_EVENT, IN_PROGRESS);
    }

    void JustSummoned(Creature* summoned)
    {
        if(summoned)
        {
            summons.Summon(summoned);
        }
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            if(frozen)
            {
                DoCast(me, SPELL_FROZEN_PRISON) ;
                frozen = false;
            }

        if(whirlwindTimer<diff)
        {
            DoCast(SPELL_WHIRLWIND_2) ;
            whirlwindTimer = urand(10000, 13000) ;
        } else whirlwindTimer -= diff ;

        if(battleShoutTimer<diff)
        {
            DoCast(SPELL_BATTLE_SHOUT) ;
            battleShoutTimer = urand(130000, 140000) ;
        } else battleShoutTimer -= diff ;

        if(frighteningShoutTimer<diff)
        {
            DoCast(SPELL_FRIGHTENING_SHOUT) ;
            frighteningShoutTimer = urand(15000, 18000) ;
        } else frighteningShoutTimer -= diff ;

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* killer)  
    {
        summons.DespawnAll();
        if (pInstance)
            pInstance->SetData(DATA_COMMANDER_EVENT, DONE);
    }
};

};

class npc_alliance_cleric : public CreatureScript
{
public:
    npc_alliance_cleric() : CreatureScript("npc_alliance_cleric") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_alliance_clericAI (pCreature);
    }

struct npc_alliance_clericAI : public ScriptedAI
{
    npc_alliance_clericAI(Creature *c) : ScriptedAI(c) 
    {
        pInstance = c->GetInstanceScript();
    }

    InstanceScript* pInstance;
    uint32 deathTimer ;
    uint32 shieldTimer ;
    uint32 flashHealTimer ;
    
    bool frozen;

    void Reset() 
    {
        deathTimer = urand(9000, 12000);
        shieldTimer = urand(2000, 4000);
        flashHealTimer = urand(5000, 8000) ;
        frozen = true;
    }
    void EnterCombat(Unit* who) 
    {
        me->RemoveAurasDueToSpell(SPELL_FROZEN_PRISON) ;
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            if(frozen)
            {
                DoCast(me, SPELL_FROZEN_PRISON) ;
                frozen = false;
            }

        if(deathTimer< diff)
        {
            DoCast(me->getVictim(), DUNGEON_MODE(SPELL_DEATH, SPELL_DEATH_H)) ;
            deathTimer = urand(13000, 16000) ;
        } else deathTimer -= diff ;

        if(shieldTimer< diff)
        {
            DoCast(me, DUNGEON_MODE(SPELL_SHIELD, SPELL_SHIELD_H)) ;
            shieldTimer = urand(45000, 48000) ;
        } else shieldTimer -= diff ;

        if(flashHealTimer< diff)
        {
            if(Unit* target = me->FindNearestCreature(CREATURE_COMMANDER_STOUTBEARD, 40, true))
            {
                if(target->GetHealth() < target->GetMaxHealth())
                {
                    DoCast(target, DUNGEON_MODE(SPELL_FLASH_HEAL, SPELL_FLASH_HEAL_H)) ;
                    flashHealTimer = urand(13000, 16000) ;
                }
            }
            else
            {
                DoCast(me, DUNGEON_MODE(SPELL_FLASH_HEAL, SPELL_FLASH_HEAL_H)) ;
                flashHealTimer = urand(16000, 19000) ;
            }
        } else flashHealTimer -= diff ;

        DoMeleeAttackIfReady();
    }
    void JustDied(Unit* killer)  
    {
    }
};

};

void AddSC_boss_commander_stoutbeard()
{
    new boss_commander_stoutbeard();
new npc_alliance_cleric();
}
