/*
 * Copyright (C) 2008-2011 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: trial_of_the_crusader
SD%Complete: ??%
SDComment: based on /dev/rsa
SDCategory: Crusader Coliseum
EndScriptData */

// Known bugs:
// Some visuals aren't appearing right sometimes

#include "ScriptPCH.h"
#include "trial_of_the_crusader.h"

enum Yells
{
    SAY_INTRO               = -1649030,
    SAY_AGGRO               = -1649031,
    SAY_DEATH               = -1649032,
    EMOTE_INCINERATE        = -1649033,
    SAY_INCINERATE          = -1649034,
    EMOTE_LEGION_FLAME      = -1649035,
    EMOTE_NETHER_PORTAL     = -1649036,
    SAY_NETHER_PORTAL       = -1649037,
    EMOTE_INFERNAL_ERUPTION = -1649038,
    SAY_INFERNAL_ERUPTION   = -1649039,
};

enum Equipment
{
    EQUIP_MAIN           = 47266,
    EQUIP_OFFHAND        = 46996,
    EQUIP_RANGED         = 47267,
    EQUIP_DONE           = EQUIP_NO_CHANGE,
};

enum Summons
{
    NPC_LEGION_FLAME     = 34784,
    NPC_INFERNAL_VOLCANO = 34813,
    NPC_FEL_INFERNAL     = 34815,
    NPC_NETHER_PORTAL    = 34825,
    NPC_MISTRESS_OF_PAIN = 34826,
};

enum BossSpells
{
    /* Jarraxus */
    SPELL_NETHER_POWER          = 66228,
    SPELL_INFERNAL              = 66258,
    SPELL_INFERNAL_ERUPTION     = 66255,
    SPELL_FEL_FIREBALL          = 66532,
    SPELL_FEL_LIGHTING          = 66528,
    SPELL_INCINERATE_FLESH      = 66237,
    SPELL_TOUCH_OF_JARAXXUS     = 66209,
    SPELL_BURNING_INFERNO       = 66242,
    SPELL_NETHER_PORTAL         = 66263,
    SPELL_LEGION_FLAME          = 66197,
    SPELL_LEGION_FLAME_EFFECT   = 66201,

    /* Mistress of pain */
    SPELL_SHIVAN_SLASH          = 67098,
    SPELL_SPINNING_STRIKE       = 66283,
    SPELL_MISTRESS_KISS         = 67077,


    /* Infernal */
    SPELL_FEL_STREAK            = 66494,

    /* Unused ? */
    SPELL_BERSERK               = 64238,
    SPELL_FEL_INFERNO           = 67047,
};

#define COOLDOWN_LEGION_FLAMES       RAID_MODE(8,2,2,2)

/*######
## boss_jaraxxus
######*/

class boss_jaraxxus : public CreatureScript
{
public:
    boss_jaraxxus() : CreatureScript("boss_jaraxxus") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_jaraxxusAI(pCreature);
    }

    struct boss_jaraxxusAI : public ScriptedAI
    {
        boss_jaraxxusAI(Creature* pCreature) : ScriptedAI(pCreature), Summons(me)
        {
            m_pInstance = pCreature->GetInstanceScript();
            Reset();
        }

        InstanceScript* m_pInstance;

        SummonList Summons;

        int32 m_uiFelFireballTimer;
        int32 m_uiFelLightningTimer;
        int32 m_uiIncinerateFleshTimer;
        int32 m_uiNetherPowerTimer;
        int32 m_uiLegionFlameTimer;
        int32 m_uiTouchOfJaraxxusTimer;
        int32 m_uiSummonNetherPortalTimer;
        int32 m_uiSummonInfernalEruptionTimer;

        bool isCastingFireball ;

        void Reset()
        {
            if (m_pInstance)
                m_pInstance->SetData(TYPE_JARAXXUS, NOT_STARTED);
            SetEquipmentSlots(false, EQUIP_MAIN, EQUIP_OFFHAND, EQUIP_RANGED);
            m_uiFelFireballTimer = 5*IN_MILLISECONDS;
            m_uiFelLightningTimer = urand(10*IN_MILLISECONDS, 15*IN_MILLISECONDS);
            m_uiIncinerateFleshTimer = urand(20*IN_MILLISECONDS, 25*IN_MILLISECONDS);
            m_uiNetherPowerTimer = 40*IN_MILLISECONDS;
            m_uiLegionFlameTimer = 30*IN_MILLISECONDS;
            m_uiTouchOfJaraxxusTimer = urand(10*IN_MILLISECONDS, 15*IN_MILLISECONDS);
            m_uiSummonNetherPortalTimer = 1*MINUTE*IN_MILLISECONDS;
            m_uiSummonInfernalEruptionTimer = 2*MINUTE*IN_MILLISECONDS;
            Summons.DespawnAll();
        }

        void JustReachedHome()
        {
            if (m_pInstance)
                m_pInstance->SetData(TYPE_JARAXXUS, FAIL);
            DoCast(me, SPELL_JARAXXUS_CHAINS);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_PASSIVE);
        }

        void KilledUnit(Unit *pWho)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                if (m_pInstance)
                    m_pInstance->SetData(DATA_TRIBUTE_TO_IMMORTALITY_ELEGIBLE, 0);
            }
        }

        void JustDied(Unit* /*pKiller*/)
        {
            Summons.DespawnAll();
            DoScriptText(SAY_DEATH, me);
            if (m_pInstance)
                m_pInstance->SetData(TYPE_JARAXXUS, DONE);
        }

        void JustSummoned(Creature* pSummoned)
        {
            Summons.Summon(pSummoned);
        }

        void EnterCombat(Unit* /*pWho*/)
        {
            me->SetInCombatWithZone();
            if (m_pInstance)
                m_pInstance->SetData(TYPE_JARAXXUS, IN_PROGRESS);
            DoScriptText(SAY_AGGRO, me);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (m_uiIncinerateFleshTimer <= uiDiff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 0, true))
                {
                    DoScriptText(EMOTE_INCINERATE, me, pTarget);
                    DoScriptText(SAY_INCINERATE, me);
                    DoCast(pTarget, SPELL_INCINERATE_FLESH);

                    /* incinerate flesh, legion flames, fel lightning and nether power share cooldowns.
                     * incinerate's flesh cooldown is 4s 
                     */
                    static const int32 incinerateCooldown = 4.5*IN_MILLISECONDS;
                    m_uiLegionFlameTimer = std::max(incinerateCooldown, m_uiLegionFlameTimer);
                    m_uiFelLightningTimer = std::max(incinerateCooldown, m_uiFelLightningTimer);
                    m_uiNetherPowerTimer = std::max(incinerateCooldown, m_uiNetherPowerTimer);
                }
                m_uiIncinerateFleshTimer = urand(20*IN_MILLISECONDS, 25*IN_MILLISECONDS);
            } else m_uiIncinerateFleshTimer -= uiDiff;

            if (m_uiLegionFlameTimer <= uiDiff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 0, true))
                {
                    DoScriptText(EMOTE_LEGION_FLAME, me, pTarget);
                    DoCast(pTarget, SPELL_LEGION_FLAME);
                }
                m_uiLegionFlameTimer = 30*IN_MILLISECONDS;

                /* incinerate flesh, legion flames, fel lightning and nether power share cooldowns.
                 * legion flames cooldown is 8s on 10n, and 2s for the 3 other modes. 
                 */
                const int32 legionCooldown = (COOLDOWN_LEGION_FLAMES+0.5)*IN_MILLISECONDS;
                m_uiIncinerateFleshTimer = std::max(legionCooldown, m_uiIncinerateFleshTimer);
                m_uiFelLightningTimer = std::max(legionCooldown, m_uiFelLightningTimer);
                m_uiNetherPowerTimer = std::max(legionCooldown, m_uiNetherPowerTimer);

            } else m_uiLegionFlameTimer -= uiDiff;

            if (m_uiSummonInfernalEruptionTimer <= uiDiff)
            {
                DoScriptText(EMOTE_INFERNAL_ERUPTION, me);
                DoScriptText(SAY_INFERNAL_ERUPTION, me);
                uint8 i = urand(2, 3);
                me->SummonCreature(NPC_INFERNAL_VOLCANO, JaraxxusLoc[i].GetPositionX(), JaraxxusLoc[i].GetPositionY(), JaraxxusLoc[i].GetPositionZ(), TEMPSUMMON_CORPSE_DESPAWN);
                m_uiSummonInfernalEruptionTimer = 2*MINUTE*IN_MILLISECONDS;
            } else m_uiSummonInfernalEruptionTimer -= uiDiff;

            if (m_uiSummonNetherPortalTimer <= uiDiff)
            {
                DoScriptText(EMOTE_NETHER_PORTAL, me);
                DoScriptText(SAY_NETHER_PORTAL, me);
                uint8 i = urand(2, 3);
                me->SummonCreature(NPC_NETHER_PORTAL, JaraxxusLoc[i].GetPositionX(), JaraxxusLoc[i].GetPositionY(), JaraxxusLoc[i].GetPositionZ(), TEMPSUMMON_CORPSE_DESPAWN);
                m_uiSummonNetherPortalTimer = 2*MINUTE*IN_MILLISECONDS;
            } else m_uiSummonNetherPortalTimer -= uiDiff;

            if (m_uiFelLightningTimer <= uiDiff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    DoCast(pTarget, SPELL_FEL_LIGHTING);
                m_uiFelLightningTimer = urand(15*IN_MILLISECONDS, 20*IN_MILLISECONDS);

                /* incinerate flesh, legion flames, fel lightning and nether power share cooldowns.
                 * fel lightning's cooldown is 6s 
                 */
                static const int32 felCooldown = 6.5*IN_MILLISECONDS;
                m_uiIncinerateFleshTimer = std::max(felCooldown, m_uiIncinerateFleshTimer);
                m_uiLegionFlameTimer = std::max(felCooldown, m_uiLegionFlameTimer);
                m_uiNetherPowerTimer = std::max(felCooldown, m_uiNetherPowerTimer);

            } else m_uiFelLightningTimer -= uiDiff;

            if (m_uiNetherPowerTimer <= uiDiff)
            {
                DoCast(me, SPELL_NETHER_POWER);
                
                m_uiNetherPowerTimer = 30*IN_MILLISECONDS;

                /* incinerate flesh, legion flames, fel lightning and nether power share cooldowns.
                 * nether power's cooldown is 6s 
                 */
                static const int32 netherCooldown = 6.5*IN_MILLISECONDS;
                m_uiIncinerateFleshTimer = std::max(netherCooldown, m_uiIncinerateFleshTimer);
                m_uiLegionFlameTimer = std::max(netherCooldown, m_uiLegionFlameTimer);
                m_uiFelLightningTimer = std::max(netherCooldown, m_uiFelLightningTimer);

            } else m_uiNetherPowerTimer -= uiDiff;

            if(!isCastingFireball)
            {
                if (m_uiFelFireballTimer <= uiDiff)
                {
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                    DoCast(SPELL_FEL_FIREBALL);
                    isCastingFireball = true ;
                    m_uiFelFireballTimer = 2600;
                } else m_uiFelFireballTimer -= uiDiff ;
            }
            else
            {
                if (m_uiFelFireballTimer <= uiDiff)
                {
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                    m_uiFelFireballTimer = urand(30000, 35000);
                    isCastingFireball = false ;
                } else m_uiFelFireballTimer -= uiDiff ;
            }

            if (GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC && m_uiTouchOfJaraxxusTimer <= uiDiff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    DoCast(pTarget, SPELL_TOUCH_OF_JARAXXUS);
                m_uiTouchOfJaraxxusTimer = urand(10*IN_MILLISECONDS, 15*IN_MILLISECONDS);
            } else m_uiTouchOfJaraxxusTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };

};

class mob_legion_flame : public CreatureScript
{
public:
    mob_legion_flame() : CreatureScript("mob_legion_flame") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_legion_flameAI(pCreature);
    }

    struct mob_legion_flameAI : public Scripted_NoMovementAI
    {
        mob_legion_flameAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
        {
            Reset();
        }

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->SetInCombatWithZone();
            DoCast(SPELL_LEGION_FLAME_EFFECT);
        }

        void UpdateAI(const uint32 /*uiDiff*/)
        {
            UpdateVictim();
        }
    };

};

class mob_infernal_volcano : public CreatureScript
{
public:
    mob_infernal_volcano() : CreatureScript("mob_infernal_volcano") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_infernal_volcanoAI(pCreature);
    }

    struct mob_infernal_volcanoAI : public Scripted_NoMovementAI
    {
        mob_infernal_volcanoAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature), Summons(me)
        {
            m_pInstance = (InstanceScript*)pCreature->GetInstanceScript();
            Reset();
        }

        InstanceScript* m_pInstance;

        SummonList Summons;

        uint8 m_Count;
        uint8 m_CountMax;
        uint32 m_Timer;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            m_Count = 0;
            if (!IsHeroic())
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                m_CountMax = 3;
                m_Timer = 15*IN_MILLISECONDS;
            }
            else
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                m_CountMax = 0;
                m_Timer = 5*IN_MILLISECONDS;
            }
            Summons.DespawnAll();
        }

        void JustSummoned(Creature* pSummoned)
        {
            Summons.Summon(pSummoned);
            pSummoned->SetCorpseDelay(0);
        }

        void JustDied(Unit* /*pKiller*/)
        {
            me->DespawnOrUnsummon();
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (m_Timer <= uiDiff)
            {
                if (m_CountMax && m_CountMax == m_Count)
                    me->DespawnOrUnsummon();
                else
                {
                    DoCast(SPELL_INFERNAL_ERUPTION);
                    ++m_Count;
                }
                m_Timer = 5*IN_MILLISECONDS;
            } else m_Timer -= uiDiff;

            UpdateVictim();
        }
    };

};

class mob_fel_infernal : public CreatureScript
{
public:
    mob_fel_infernal() : CreatureScript("mob_fel_infernal") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_fel_infernalAI(pCreature);
    }

    struct mob_fel_infernalAI : public ScriptedAI
    {
        mob_fel_infernalAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            m_pInstance = (InstanceScript*)pCreature->GetInstanceScript();
            Reset();
        }

        InstanceScript* m_pInstance;
        uint32 m_uiFelStreakTimer;

        void Reset()
        {
            m_uiFelStreakTimer = 30*IN_MILLISECONDS;
            me->SetInCombatWithZone();
        }

        /*void SpellHitTarget(Unit *pTarget, const SpellEntry *pSpell)
        {
            if (pSpell->Id == SPELL_FEL_STREAK)
                DoCastAOE(SPELL_FEL_INFERNO); //66517
        }*/

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (m_pInstance && m_pInstance->GetData(TYPE_JARAXXUS) != IN_PROGRESS)
                me->DespawnOrUnsummon();

            if (m_uiFelStreakTimer <= uiDiff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    DoCast(pTarget, SPELL_FEL_STREAK);
                m_uiFelStreakTimer = 30*IN_MILLISECONDS;
            } else m_uiFelStreakTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };

};

class mob_nether_portal : public CreatureScript
{
public:
    mob_nether_portal() : CreatureScript("mob_nether_portal") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_nether_portalAI(pCreature);
    }

    struct mob_nether_portalAI : public ScriptedAI
    {
        mob_nether_portalAI(Creature* pCreature) : ScriptedAI(pCreature), Summons(me)
        {
            m_pInstance = (InstanceScript*)pCreature->GetInstanceScript();
            Reset();
        }

        InstanceScript* m_pInstance;

        SummonList Summons;

        uint32 m_Timer;
        uint8  m_Count;
        uint8  m_CountMax;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            m_Timer = 10*IN_MILLISECONDS;
            m_Count = 0;
            if (!IsHeroic())
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                m_CountMax = 1;
            }
            else
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                m_CountMax = 0;
            }
            Summons.DespawnAll();
        }

        void JustSummoned(Creature* pSummoned)
        {
            Summons.Summon(pSummoned);
            pSummoned->SetCorpseDelay(0);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (m_Timer <= uiDiff)
            {
                if (m_CountMax && m_CountMax == m_Count)
                    me->DespawnOrUnsummon();
                else
                {
                    DoCast(SPELL_NETHER_PORTAL);
                    ++m_Count;
                }
                m_Timer = 15*IN_MILLISECONDS;
            } else m_Timer -= uiDiff;

            UpdateVictim();
        }
    };

};

class mob_mistress_of_pain : public CreatureScript
{
public:
    mob_mistress_of_pain() : CreatureScript("mob_mistress_of_pain") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_mistress_of_painAI(pCreature);
    }

    struct mob_mistress_of_painAI : public ScriptedAI
    {
        mob_mistress_of_painAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            m_pInstance = (InstanceScript*)pCreature->GetInstanceScript();
            if (m_pInstance)
                m_pInstance->SetData(DATA_MISTRESS_OF_PAIN_COUNT, INCREASE);
            Reset();
        }

        InstanceScript* m_pInstance;
        uint32 m_uiShivanSlashTimer;
        uint32 m_uiSpinningStrikeTimer;
        uint32 m_uiMistressKissTimer;

        void Reset()
        {
            m_uiShivanSlashTimer = 30*IN_MILLISECONDS;
            m_uiSpinningStrikeTimer = 30*IN_MILLISECONDS;
            m_uiMistressKissTimer = 15*IN_MILLISECONDS;
            me->SetInCombatWithZone();
        }

        void JustDied(Unit* /*pKiller*/)
        {
            if (m_pInstance)
                m_pInstance->SetData(DATA_MISTRESS_OF_PAIN_COUNT, DECREASE);
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (m_pInstance && m_pInstance->GetData(TYPE_JARAXXUS) != IN_PROGRESS)
                me->DespawnOrUnsummon();

            if (m_uiShivanSlashTimer <= uiDiff)
            {
                DoCastVictim(SPELL_SHIVAN_SLASH);
                m_uiShivanSlashTimer = 30*IN_MILLISECONDS;
            } else m_uiShivanSlashTimer -= uiDiff;

            if (m_uiSpinningStrikeTimer <= uiDiff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    DoCast(pTarget, SPELL_SPINNING_STRIKE);
                m_uiSpinningStrikeTimer = 30*IN_MILLISECONDS;
            } else m_uiSpinningStrikeTimer -= uiDiff;

            if (IsHeroic() && m_uiMistressKissTimer <= uiDiff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    DoCast(pTarget, SPELL_MISTRESS_KISS);
                m_uiMistressKissTimer = 30*IN_MILLISECONDS;
            } else m_uiMistressKissTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };

};

class spell_nether_power : public SpellScriptLoader
{
    public:
        spell_nether_power() : SpellScriptLoader("spell_nether_power") { }

        class spell_nether_powerAuraScript : public AuraScript
        {
            PrepareAuraScript(spell_nether_powerAuraScript)

            bool Validate(SpellEntry const * /*spellEntry*/)
            {
                return true;
            }

            void HandleEffectApply(AuraEffect const * aurEff, AuraEffectHandleModes /*mode*/)
            {
                switch(GetSpellProto()->Id) {
                    case 66228:
                    case 67107:
                        SetStackAmount(5);
                        break;
                    case 67106:
                    case 67108: 
                        SetStackAmount(10);
                        break;
                }
            }

            // function registering
            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_nether_powerAuraScript::HandleEffectApply, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        // function which creates AuraScript
        AuraScript *GetAuraScript() const
        {
            return new spell_nether_powerAuraScript();
        }
};

void AddSC_boss_jaraxxus()
{
    new boss_jaraxxus();
    new mob_legion_flame();
    new mob_infernal_volcano();
    new mob_fel_infernal();
    new mob_nether_portal();
    new mob_mistress_of_pain();
    new spell_nether_power();
}
