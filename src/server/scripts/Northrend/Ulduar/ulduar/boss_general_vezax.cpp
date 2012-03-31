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
SDName: Boss_General_Vezax
SD%Complete: 90
SDComment: le mp5 n'est pas bloqu� par l'aura de desespoir
SDCategory: Ulduar
*/

#include "ScriptPCH.h"
#include "SpellAuraEffects.h"
#include "ulduar.h"

enum Yells
{
    SAY_AGGRO                                   = -1603290,
    SAY_SLAY_1                                  = -1603291,
    SAY_SLAY_2                                  = -1603292,
    SAY_KITE                                    = -1603293,
    SAY_DEATH                                   = -1603294,
    SAY_BERSERK                                 = -1603295,
    SAY_HARDMODE_ON                             = -1603296,
};

enum Achievments
{
    ACHIEVEMENTS_SMELL_OF_SARONIT_IN_THE_MORNING_10 = 3181,
    ACHIEVEMENTS_SMELL_OF_SARONIT_IN_THE_MORNING_25 = 3188,
    ACHIEVEMENTS_SHADOWDODGER_10                    = 2996,
    ACHIEVEMENTS_SHADOWDODGER_25                    = 2997,
};

enum Spells
{
    // General Vezax
    SPELL_AURA_OF_DESPAIR                       = 62692, // on combat start
    SPELL_AURA_OF_DESPAIR_EFFEKT_DESPAIR        = 64848, // dont know if needet ... need test
    SPELL_CORRUPTED_RAGE                        = 68415,
	SPELL_CORRUPTED_WISDOM                      = 64646, // jugement de sagesse
    SPELL_MARK_OF_THE_FACELESS                  = 63276, // Unknown Aura
    SPELL_MARK_OF_THE_FACELESS_LEECH            = 63278, // Leech Health 1 ... need custom cast
    SPELL_SARONIT_BARRIER                       = 63364, // Script Effekt, Apply while Saronit Animus spawned
    SPELL_SEARING_FLAMES                        = 62661,
    SPELL_SHADOW_CRASH                          = 62660, // Trigger Missile 62659 and 63277
    SPELL_SHADOW_CRASH_DAMAGE                   = 62659, // Explosion Damage
    SPELL_SHADOW_CRASH_AURA                     = 63277, // Triggered Cloud
    SPELL_SURGE_OF_DARKNESS                     = 62662, // every 60 seconds
    SPELL_SUMMON_SARONIT_VARPOR                 = 63081, // every 30 seconds
    SPELL_BERSERK                               = 26662,
    // Saronit Animus - Spawnd after 6th Saronit Varpor
    SPELL_PROFOUND_DARKNESS                     = 63420,
    // Saronit Varpor
    SPELL_SARONIT_VARPOR                        = 63323, // Casted on Death trigger 63322
    SPELL_SARONIT_VARPOR_AURA                   = 63322, // Unknown Aura Dummy needs Scripting ?
    // Player Shaman
    SPELL_SHAMANTIC_RAGE                        = 30823,
	// Player Paladin
	SPELL_JUDGEMENT_OF_THE_WISE                 = 31878,
};

enum NPCs
{
    ENTRY_GENERAL_VEZAX                         = 33271,
    ENTRY_SARONIT_VARPOR                        = 33488,
    ENTRY_SARONIT_ANIMUS                        = 33524
};
#define GO_VEZAX_DOOR                             194750

enum Actions
{
    ACTION_VARPOR_KILLED,
    ACTION_ANIMUS_KILLED
};

class boss_general_vezax : public CreatureScript
{
public:
    boss_general_vezax() : CreatureScript("boss_general_vezax") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_general_vezaxAI(pCreature);
    }

    struct boss_general_vezaxAI : public BossAI
    {
        boss_general_vezaxAI(Creature *pCreature) : BossAI(pCreature, TYPE_VEZAX)
        {
            m_pInstance = pCreature->GetInstanceScript();
            VarporList = std::list<uint64>();
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);  // Death Grip
        }

        InstanceScript* m_pInstance;
        std::list<uint64> VarporList;
        uint64 guidSaronitAnimus;

        bool AnimusSummoned;
        bool AnimusKilled;
        bool VarporKilled;
        bool HitByShadowCrash;
        uint32 uiSummonVarpor_Timer;
        uint32 uiSurgeOfDarkness_Timer;
        uint32 uiShadowCrash_Timer;
        uint32 uiSearingFlames_Timer;
        uint32 uiMarkOfTheFaceless;
		uint32 uiBerserk_Timer;

        void Reset()
        {
            _Reset();
            me->ResetLootMode();
            AnimusSummoned = false;
            HitByShadowCrash = false;
            AnimusKilled = false;
            VarporKilled = false;
            DespawnVarpors();
            DespawnAnimus();

            uiSurgeOfDarkness_Timer = 60000;
            uiSummonVarpor_Timer = 30000;
            uiShadowCrash_Timer = 10000;
            uiSearingFlames_Timer = urand(5000,10000);
            uiMarkOfTheFaceless = urand(15000,25000);
			uiBerserk_Timer = 600000;

			if(m_pInstance)
                m_pInstance->SetBossState(TYPE_VEZAX, NOT_STARTED);
        }

        void DespawnVarpors()
        {
            for(std::list<uint64>::iterator itr = VarporList.begin(); itr != VarporList.end(); ++itr)
            {
                if(Creature* varpor = Creature::GetCreature((*me),(*itr)))
                {
                    varpor->DealDamage(varpor,varpor->GetHealth());
                    varpor->RemoveCorpse();
                }
            }

            VarporList.clear();
        }

        void DespawnAnimus()
        {
            if(Creature* animus = Creature::GetCreature((*me),guidSaronitAnimus))
            {
                animus->DealDamage(animus,animus->GetHealth());
                animus->RemoveCorpse();
            }
            guidSaronitAnimus = 0;
        }
			

        void EnterCombat(Unit * /*pWho*/)
        {
            _EnterCombat();

            DoScriptText(SAY_AGGRO,me);
            DoCast(SPELL_AURA_OF_DESPAIR);
			if(m_pInstance)
                m_pInstance->SetBossState(TYPE_VEZAX, IN_PROGRESS);
        }

        void SpellHitTarget(Unit* target, const SpellEntry* spell)
        {
            if(target && target->ToPlayer())
            {
                switch(spell->Id)
                {
                case SPELL_SHADOW_CRASH_DAMAGE:
                    HitByShadowCrash = true;
                    break;
                }
            }
        }

        void JustSummoned(Creature* pSummoned)
        {
            switch(pSummoned->GetEntry())
            {
                case ENTRY_SARONIT_VARPOR:
                    VarporList.push_back(pSummoned->GetGUID());
                    if(!VarporKilled && VarporList.size() > 5)
                    {
                        DespawnVarpors();
                        if(Creature* animus = DoSummon(ENTRY_SARONIT_ANIMUS,me->GetHomePosition(),30000,TEMPSUMMON_MANUAL_DESPAWN))
                            animus->AI()->AttackStart(me->getVictim());
                    }
                    break;
                case ENTRY_SARONIT_ANIMUS:
                    guidSaronitAnimus = pSummoned->GetGUID();
                    AnimusSummoned = true;
                    DoScriptText(SAY_HARDMODE_ON,me);
					me->AddLootMode(LOOT_MODE_HARD_MODE_1);
                    me->InterruptNonMeleeSpells(false);
                    DoCast(SPELL_SARONIT_BARRIER);
                    break;
            }
        }

        void KilledUnit(Unit * /*pWho*/)
        {
            if(urand(0,5) == 0)
                DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2),me);
        }

        void JustDied(Unit * /*pWho*/)
        {
			_JustDied();
            DoScriptText(SAY_DEATH,me);
			if(m_pInstance)
			{
                m_pInstance->SetBossState(TYPE_VEZAX, DONE);
				if (GameObject* Door = me->FindNearestGameObject(GO_VEZAX_DOOR, 500.0f))
					m_pInstance->DoUseDoorOrButton(Door->GetGUID());
			}

            if(!VarporKilled && AnimusSummoned && AnimusKilled)
            {
                if(m_pInstance)
                    m_pInstance->DoCompleteAchievement(RAID_MODE(ACHIEVEMENTS_SMELL_OF_SARONIT_IN_THE_MORNING_10,ACHIEVEMENTS_SMELL_OF_SARONIT_IN_THE_MORNING_25));
            }

            if(!HitByShadowCrash)
            {
                if(m_pInstance)
                    m_pInstance->DoCompleteAchievement(RAID_MODE(ACHIEVEMENTS_SHADOWDODGER_10,ACHIEVEMENTS_SHADOWDODGER_25));
            }
        }

        void DoAction(const int32 action)
        {
            switch(action)
            {
            case ACTION_VARPOR_KILLED:
                VarporKilled = true;
                break;
            case ACTION_ANIMUS_KILLED:
                AnimusKilled = true;
                me->RemoveAurasDueToSpell(SPELL_SARONIT_BARRIER);
                break;
            }
        }

        Unit * CheckPlayersInRange(uint32 uiPlayersMin, float uiRangeMin, float uiRangeMax)
        {
            Map * pMap = me->GetMap();
            if (pMap && pMap->IsDungeon())
            {
                std::list<Player*> PlayerList;
                Map::PlayerList const &Players = pMap->GetPlayers();
                for (Map::PlayerList::const_iterator itr = Players.begin(); itr != Players.end(); ++itr)
                {
                    if (Player * pPlayer = itr->getSource())
                    {
                        float uiDistance = pPlayer->GetDistance(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
                        if (uiRangeMin < uiDistance || uiDistance > uiRangeMax)
                            continue;

                        PlayerList.push_back(pPlayer);
                    }
                }

                if (PlayerList.empty())
                    return NULL;

                size_t size = PlayerList.size();
                if (size < uiPlayersMin)
                    return NULL;

                std::list<Player*>::const_iterator itr = PlayerList.begin();
                std::advance(itr, urand(0, size - 1));
                return *itr;
            }
            else
                return NULL;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() )
                return;

            if(!AnimusSummoned)
                if(uiSummonVarpor_Timer < diff)
                {
                    DoSummon(ENTRY_SARONIT_VARPOR,me,45.0f,30000,TEMPSUMMON_MANUAL_DESPAWN);
                    uiSummonVarpor_Timer = 30000;
                }else uiSummonVarpor_Timer -= diff;

            if(uiSurgeOfDarkness_Timer < diff)
            {
                if(!me->IsNonMeleeSpellCasted(false))
                {
                    DoCast(me,SPELL_SURGE_OF_DARKNESS);
                    DoScriptText(SAY_KITE,me);
                    uiSurgeOfDarkness_Timer = 63000;
                }
            }else uiSurgeOfDarkness_Timer -= diff;

            if(uiShadowCrash_Timer < diff)
            {
                if(!me->IsNonMeleeSpellCasted(false))
                {

                    if(Unit* target = GetPlayerAtMinimumRange(15.0f))
                        DoCast(target,SPELL_SHADOW_CRASH,false);
                    else if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0,100,true))
                        DoCast(target,SPELL_SHADOW_CRASH,false);
                    uiShadowCrash_Timer = 10000;
                }
            }else uiShadowCrash_Timer -= diff;

            if(!AnimusSummoned || AnimusKilled)
                if(uiSearingFlames_Timer < diff)
                {
                    if(!me->IsNonMeleeSpellCasted(false))
                    {
                         DoCast(SPELL_SEARING_FLAMES);
                         uiSearingFlames_Timer = urand(10000,15000);
                    }
                }else uiSearingFlames_Timer -= diff;

            if(uiMarkOfTheFaceless < diff)
            {
                if(!me->IsNonMeleeSpellCasted(false))
                {
                    if(Unit* target = CheckPlayersInRange(RAID_MODE(4,9), 15.0f, 50.f))
                        DoCast(target,SPELL_MARK_OF_THE_FACELESS,false);
                    else if(Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0,100,true))
                        DoCast(target,SPELL_MARK_OF_THE_FACELESS,false);

                        uiMarkOfTheFaceless = urand(15000,25000);
                }
            }else uiMarkOfTheFaceless -= diff;

            if(uiBerserk_Timer < diff)
            {
				DoScriptText(SAY_BERSERK, me);
				DoCast(me, SPELL_BERSERK);
				uiBerserk_Timer = 600000;
            }else uiBerserk_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};
class mob_saronit_varpor : public CreatureScript
{
public:
    mob_saronit_varpor() : CreatureScript("mob_saronit_varpor") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_saronit_varporAI (pCreature);
    }

    struct mob_saronit_varporAI : public ScriptedAI
    {
        mob_saronit_varporAI(Creature *pCreature) : ScriptedAI(pCreature)
        {
			m_pInstance = pCreature->GetInstanceScript();
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->MoveRandom(30.0f);
        }
        InstanceScript* m_pInstance;

        void DamageTaken(Unit* who, uint32 &damage)
        {
			if(who->GetGUID() == me->GetGUID())
                return;

            if (damage >= me->GetHealth())
            {
                damage = 0;
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE);
                me->RemoveAllAuras();
                me->SetHealth(me->GetMaxHealth());
                me->ForcedDespawn(30000);
                me->GetMotionMaster()->Initialize();
                me->SetStandState(UNIT_STAND_STATE_DEAD);
				me->setFaction(35);
				me->CastSpell(me, SPELL_SARONIT_VARPOR, true);
                if(Creature* Vezax = Creature::GetCreature((*me),m_pInstance->GetData64(TYPE_VEZAX)))
                    Vezax->ToCreature()->AI()->DoAction(ACTION_VARPOR_KILLED);
            }
        }
    };
    
};

class mob_saronit_animus : public CreatureScript
{
public:
    mob_saronit_animus() : CreatureScript("mob_saronit_animus") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_saronit_animusAI (pCreature);
    }

    struct mob_saronit_animusAI : public ScriptedAI
    {
        mob_saronit_animusAI(Creature *c) : ScriptedAI(c)
        {
            m_pInstance = c->GetInstanceScript();
        }

        InstanceScript* m_pInstance;
        uint32 uiProfoundDarkness_Timer;

        void Reset()
        {
            uiProfoundDarkness_Timer = 1000;
        }

        void JustDied(Unit* killer)
        {
            if(killer->GetGUID() == me->GetGUID())
                return;

            if(m_pInstance)
                if(Creature* vezax = Creature::GetCreature((*me),m_pInstance->GetData64(TYPE_VEZAX)))
                {
                    vezax->AI()->DoAction(ACTION_ANIMUS_KILLED);
                }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() )
                return;

            if(uiProfoundDarkness_Timer < diff)
            {
                if(!me->IsNonMeleeSpellCasted(false))
                {
                    DoCast(SPELL_PROFOUND_DARKNESS);
                    uiProfoundDarkness_Timer = 10000;
                }
            }else uiProfoundDarkness_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };
};

class spell_general_vezax_aura_of_despair_aura : public SpellScriptLoader
{
public:
    spell_general_vezax_aura_of_despair_aura() : SpellScriptLoader("spell_general_vezax_aura_of_despair_aura") { }

    class spell_general_vezax_aura_of_despair_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_general_vezax_aura_of_despair_AuraScript);

        bool Validate(SpellEntry const* /*spellInfo*/)
        {
            if (!sSpellStore.LookupEntry(SPELL_AURA_OF_DESPAIR_EFFEKT_DESPAIR))
                return false;
            if (!sSpellStore.LookupEntry(SPELL_CORRUPTED_RAGE))
                return false;
			if (!sSpellStore.LookupEntry(SPELL_CORRUPTED_WISDOM))
                return false;
            return true;
        }

        void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTarget()->GetTypeId() != TYPEID_PLAYER)
                return;

            Player* pTarget = GetTarget()->ToPlayer();

            if(pTarget->getClass() == CLASS_SHAMAN && pTarget->HasSpell(SPELL_SHAMANTIC_RAGE))
                pTarget->CastSpell(pTarget,SPELL_CORRUPTED_RAGE,true);
			if(pTarget->getClass() == CLASS_PALADIN && pTarget->HasSpell(SPELL_JUDGEMENT_OF_THE_WISE))
                pTarget->CastSpell(pTarget,SPELL_CORRUPTED_WISDOM,true);

            pTarget->CastSpell(pTarget,SPELL_AURA_OF_DESPAIR_EFFEKT_DESPAIR,true);

        }

        void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (GetTarget()->GetTypeId() != TYPEID_PLAYER)
                return;

            Player* pTarget = GetTarget()->ToPlayer();

            pTarget->RemoveAurasDueToSpell(SPELL_CORRUPTED_RAGE);
			pTarget->RemoveAurasDueToSpell(SPELL_CORRUPTED_WISDOM);
            pTarget->RemoveAurasDueToSpell(SPELL_AURA_OF_DESPAIR_EFFEKT_DESPAIR);
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_general_vezax_aura_of_despair_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PREVENT_REGENERATE_POWER, AURA_EFFECT_HANDLE_REAL);
            OnEffectRemove += AuraEffectRemoveFn(spell_general_vezax_aura_of_despair_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PREVENT_REGENERATE_POWER, AURA_EFFECT_HANDLE_REAL);
        }

    };

    AuraScript* GetAuraScript() const
    {
        return new spell_general_vezax_aura_of_despair_AuraScript();
    }
};

void AddSC_boss_general_vezax()
{
    new boss_general_vezax();
    new mob_saronit_varpor();
    new mob_saronit_animus();
    new spell_general_vezax_aura_of_despair_aura();
}
