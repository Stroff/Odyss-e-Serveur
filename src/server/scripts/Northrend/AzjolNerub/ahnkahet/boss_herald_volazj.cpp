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

/*
 * Comment: Missing AI for Twisted Visages
 */

#include "ScriptPCH.h"
#include "ahnkahet.h"

enum Spells
{
    // Herald Volazj
    SPELL_INSANITY                                = 57496, //Dummy
    INSANITY_VISUAL                               = 57561,
    SPELL_INSANITY_TARGET                         = 57508,
    SPELL_MIND_FLAY                               = 57941,
    SPELL_SHADOW_BOLT_VOLLEY                      = 57942,
    SPELL_SHIVER                                  = 57949,
    SPELL_CLONE_PLAYER                            = 57507, //casted on player during insanity
    SPELL_INSANITY_PHASING_1                      = 57508,
    SPELL_INSANITY_PHASING_2                      = 57509,
    SPELL_INSANITY_PHASING_3                      = 57510,
    SPELL_INSANITY_PHASING_4                      = 57511,
    SPELL_INSANITY_PHASING_5                      = 57512,
    // Twisted Visage
    // Paladin
    SPELL_AVENGER_SHIELD                = 57799,
    H_SPELL_AVENGER_SHIELD                = 59999,
    SPELL_CONSECRATION                    = 57798,
    H_SPELL_CONSECRATION                = 59998,
    SPELL_CLEANSE                        = 57767,
    SPELL_FLASH_OF_LIGHT                = 57766,
    H_SPELL_FLASH_OF_LIGHT                = 59997,
    SPELL_SEAL_OF_COMMAND                = 57769,
    SPELL_JUDGEMENT_OF_LIGHT            = 57774,
    // Shaman
    SPELL_BLOODTHIRST                    = 57790,
    H_SPELL_BLOODTHIRST                    = 60017,
    SPELL_EARTH_SHIELD                    = 57802,
    H_SPELL_EARTH_SHIELD                = 60013,
    SPELL_HEALING_WAVE                    = 57785,
    H_SPELL_HEALING_WAVE                = 60012,
    SPELL_EARTH_SHOCK                    = 57783,
    H_SPELL_EARTH_SHOCK                    = 60011,
    SPELL_LIGHTNING_BOLT                = 57781,
    H_SPELL_LIGHTNING_BOLT                = 60099,
    SPELL_STORMSTRIKE                    = 51876,
    SPELL_THUNDERSTORM                    = 57784,
    H_SPELL_THUNDERSTORM                = 60010,
    // Rogue
    SPELL_EVISCERATE                    = 57641,
    H_SPELL_EVISCERATE                    = 60008,
    SPELL_SINISTER_STRIKE                = 57640,
    // Mage
    SPELL_FIREBALL                        = 57628,
    H_SPELL_FIREBALL                    = 59994,
    SPELL_FROST_NOVA                    = 57629,
    H_SPELL_FROST_NOVA                    = 59995,
    // Druid
    SPELL_CAT_FORM                        = 57655,
    SPELL_MANGLE                        = 57657,
    H_SPELL_MANGLE                        = 59988,
    SPELL_RIP                            = 57661,
    H_SPELL_RIP                            = 59989,
    SPELL_LIFEBLOOM                        = 57762,
    H_SPELL_LIFEBLOOM                    = 59990,
    SPELL_NOURISH                        = 57765,
    H_SPELL_NOURISH                        = 59991,
    SPELL_MOONFIRE                        = 57647,
    H_SPELL_MOONFIRE                    = 59987,
    SPELL_WRATH                            = 57648,
    H_SPELL_WRATH                        = 59986,
    // Warlock
    SPELL_CORRUPTION                    = 57645,
    H_SPELL_CORRUPTION                    = 60016,
    SPELL_SHADOW_BOLT                    = 57644,
    H_SPELL_SHADOW_BOLT                    = 60015,
    // Death Knight
    SPELL_DEATH_GRIP                    = 57602,
    SPELL_PLAGUE_STRIKE                    = 57599,
    H_SPELL_PLAGUE_STRIKE                = 59985,
    // Warrior
    SPELL_DEVASTATE                        = 57795,
    H_SPELL_DEVASTATE                    = 60018,
    SPELL_HAMSTRING                        = 9080,
    SPELL_INTERCEPT                        = 61490,
    SPELL_MORTAL_STRIKE                    = 57789,
    SPELL_THUNDER_CLAP                    = 57832,
    H_SPELL_THUNDER_CLAP                = 60019,
    // Hunter
    SPELL_DISENGAGE                        = 57635,
    SPELL_SHOOT                            = 57589,
    H_SPELL_SHOOT                        = 59993,
    // Priest
    SPELL_GREATER_HEAL                    = 57775,
    H_SPELL_GREATER_HEAL                = 60003,
    SPELL_RENEW                            = 57777,
    H_SPELL_RENEW                        = 60004,
    SPELL_SHADOW_WORD_PAIN                = 57778,
    H_SPELL_SHADOW_WORD_PAIN            = 60005,

    // Player's spells used for tests
    SPELL_DISPERSION                    = 47585,
    SPELL_BERSERK                        = 50334,
    SPELL_STARFALL                        = 48505,
    SPELL_WILD_GROWTH                    = 48438,
    SPELL_SHOCKWAVE                        = 46968,
    SPELL_BLADE_STORM                    = 46924,
    SPELL_TITAN_GRIP                    = 46917,
    SPELL_BEACON_OF_LIGHT                = 53563,
    SPELL_HAMMER_OF_THE_RIGHTEOUS        = 53595,
    SPELL_DIVINE_STORM                    = 53385,
    SPELL_P_THUNDERSTORM                = 51490,
    SPELL_FERAL_SPIRIT                    = 51533,
    SPELL_RIPTIDE                        = 61295
};

enum Specialisation
{
    SPECIALISATION_OTHER                = 0,
    SPECIALISATION_SHADOW                = 1,
    SPECIALISATION_BALANCE                = 2,
    SPECIALISATION_RESTORATION            = 3,
    SPECIALISATION_FERAL                = 4,
    SPECIALISATION_PROTECTION            = 5,
    SPECIALISATION_FURY                    = 6,
    SPECIALISATION_ARMS                    = 7,
    SPECIALISATION_RETRIBUTION            = 8,
    SPECIALISATION_HOLY                    = 9,
    SPECIALISATION_ELEMENTAL            = 10,
    SPECIALISATION_ENHANCEMENT            = 11
};

#define MOB_TWISTED_VISAGE 30625

#define DATA_CLASS    1
#define DATA_SPECIALISATION    2

//not in db
enum Yells
{
    SAY_AGGRO                                     = -1619030,
    SAY_SLAY_1                                    = -1619031,
    SAY_SLAY_2                                    = -1619032,
    SAY_SLAY_3                                    = -1619033,
    SAY_DEATH_1                                   = -1619034,
    SAY_DEATH_2                                   = -1619035,
    SAY_PHASE                                     = -1619036
};

enum Achievements
{
    ACHIEV_QUICK_DEMISE_START_EVENT               = 20382,
};

class boss_volazj : public CreatureScript
{
public:
    boss_volazj() : CreatureScript("boss_volazj") { }

struct boss_volazjAI : public ScriptedAI
{
    boss_volazjAI(Creature* pCreature) : ScriptedAI(pCreature),Summons(me)
    {
            pInstance = pCreature->GetInstanceScript();
    }

        InstanceScript *pInstance;

    uint32 uiMindFlayTimer;
    uint32 uiShadowBoltVolleyTimer;
    uint32 uiShiverTimer;
    uint32 insanityHandled;
    SummonList Summons;

    // returns the percentage of health after taking the given damage.
    uint32 GetHealthPct(uint32 damage)
    {
        if (damage > me->GetHealth())
            return 0;
        return 100*(me->GetHealth()-damage)/me->GetMaxHealth();
    }

    void DamageTaken(Unit * /*pAttacker*/, uint32 &damage)
    {
        if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
            damage = 0;

        if ((GetHealthPct(0) >= 66 && GetHealthPct(damage) < 66)||
            (GetHealthPct(0) >= 33 && GetHealthPct(damage) < 33))
        {
            me->InterruptNonMeleeSpells(false);
            DoCast(me, SPELL_INSANITY, false);
        }
    }

    void SpellHitTarget(Unit *pTarget, const SpellEntry *spell)
    {
        if (spell->Id == SPELL_INSANITY)
        {
            // Not good target or too many players
            if (pTarget->GetTypeId() != TYPEID_PLAYER || insanityHandled > 4)
                return;
            // First target - start channel visual and set self as unnattackable
            if (!insanityHandled)
            {
                // Channel visual
                DoCast(me, INSANITY_VISUAL, true);
                // Unattackable
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetControlled(true, UNIT_STAT_STUNNED);
            }
            // phase mask
            pTarget->CastSpell(pTarget, SPELL_INSANITY_TARGET+insanityHandled, true);
            // summon twisted party members for this target
            Map::PlayerList const &players = me->GetMap()->GetPlayers();
            for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
            {
                Player *plr = i->getSource();
                if (!plr || !plr->isAlive())
                    continue;
                // Summon clone
                if (Unit *summon = me->SummonCreature(MOB_TWISTED_VISAGE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(),TEMPSUMMON_CORPSE_DESPAWN,0))
                {
                    // required for correct visual
                    // Fixme: allow mirror image query to send other guid to get rid of minion status
                    summon->SetUInt64Value(UNIT_FIELD_CREATEDBY, plr->GetGUID());
                    // clone
                    plr->CastSpell(summon, SPELL_CLONE_PLAYER, true);
                    // set phase
                    summon->SetPhaseMask((1<<(4+insanityHandled)),true);
                    // set the class
                    CAST_CRE(summon)->AI()->SetData(DATA_CLASS, plr->getClass());
                    switch(plr->getClass())
                    {
                    case CLASS_PRIEST :
                        if(plr->HasSpell(SPELL_DISPERSION))
                            CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_SHADOW);
                        else
                            CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_OTHER);
                        break ;
                    case CLASS_DRUID :
                        if(plr->HasSpell(SPELL_BERSERK))
                            CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_FERAL);
                        else
                        {
                            if(plr->HasSpell(SPELL_STARFALL))
                                CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_BALANCE);
                            else
                            {
                                if(plr->HasSpell(SPELL_WILD_GROWTH))
                                    CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_RESTORATION);
                                else
                                    CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, RAND(SPECIALISATION_RESTORATION, SPECIALISATION_BALANCE, SPECIALISATION_FERAL));
                            }
                        }
                        break ;
                    case CLASS_WARRIOR :
                        if(plr->HasSpell(SPELL_SHOCKWAVE))
                            CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_PROTECTION);
                        else
                        {
                            if(plr->HasSpell(SPELL_TITAN_GRIP))
                                CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_FURY);
                            else
                            {
                                if(plr->HasSpell(SPELL_BLADE_STORM))
                                    CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_ARMS);
                                else
                                    CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, RAND(SPECIALISATION_FURY, SPECIALISATION_ARMS, SPECIALISATION_PROTECTION));
                            }
                        }
                        break ;
                    case CLASS_PALADIN :
                        if(plr->HasSpell(SPELL_BEACON_OF_LIGHT))
                            CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_HOLY);
                        else
                        {
                            if(plr->HasSpell(SPELL_HAMMER_OF_THE_RIGHTEOUS))
                                CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_PROTECTION);
                            else
                            {
                                if(plr->HasSpell(SPELL_DIVINE_STORM))
                                    CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_RETRIBUTION);
                                else
                                    CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, RAND(SPECIALISATION_RETRIBUTION, SPECIALISATION_HOLY, SPECIALISATION_PROTECTION));
                            }
                        }
                        break ;
                    case CLASS_SHAMAN :
                        if(plr->HasSpell(SPELL_P_THUNDERSTORM))
                            CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_ELEMENTAL);
                        else
                        {
                            if(plr->HasSpell(SPELL_FERAL_SPIRIT))
                                CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_ENHANCEMENT);
                            else
                            {
                                if(plr->HasSpell(SPELL_RIPTIDE))
                                    CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, SPECIALISATION_RESTORATION);
                                else
                                    CAST_CRE(summon)->AI()->SetData(DATA_SPECIALISATION, RAND(SPECIALISATION_RESTORATION, SPECIALISATION_ELEMENTAL, SPECIALISATION_ENHANCEMENT));
                            }
                        }
                        break ;
                    }
                }
            }
            ++insanityHandled;
        }
    }

    void ResetPlayersPhaseMask()
    {
        Map::PlayerList const &players = me->GetMap()->GetPlayers();
        for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
        {
            Player* pPlayer = i->getSource();
            pPlayer->RemoveAurasDueToSpell(GetSpellForPhaseMask(pPlayer->GetPhaseMask()));
        }
    }

    void Reset()
    {
        uiMindFlayTimer = 8*IN_MILLISECONDS;
        uiShadowBoltVolleyTimer = 5*IN_MILLISECONDS;
        uiShiverTimer = 15*IN_MILLISECONDS;

        if (pInstance)
        {
            pInstance->SetData(DATA_HERALD_VOLAZJ, NOT_STARTED);
            pInstance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_QUICK_DEMISE_START_EVENT);
        }

        // Visible for all players in insanity
        me->SetPhaseMask((1|16|32|64|128|256),true);
        // Used for Insanity handling
        insanityHandled = 0;

        ResetPlayersPhaseMask();

        // Cleanup
        Summons.DespawnAll();
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void EnterCombat(Unit* /*who*/)
    {
        DoScriptText(SAY_AGGRO, me);

        if (pInstance)
        {
            pInstance->SetData(DATA_HERALD_VOLAZJ, IN_PROGRESS);
            pInstance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_QUICK_DEMISE_START_EVENT);
        }
    }

    void JustSummoned(Creature *summon)
    {
        Summons.Summon(summon);
    }

    uint32 GetSpellForPhaseMask(uint32 phase)
    {
        uint32 spell = 0;
        switch (phase)
        {
            case 16:
                spell = SPELL_INSANITY_PHASING_1;
                break;
            case 32:
                spell = SPELL_INSANITY_PHASING_2;
                break;
            case 64:
                spell = SPELL_INSANITY_PHASING_3;
                break;
            case 128:
                spell = SPELL_INSANITY_PHASING_4;
                break;
            case 256:
                spell = SPELL_INSANITY_PHASING_5;
                break;
        }
        return spell;
    }

    void SummonedCreatureDespawn(Creature *summon)
    {
        uint32 phase= summon->GetPhaseMask();
        uint32 nextPhase = 0;
        Summons.Despawn(summon);

        // Check if all summons in this phase killed
        for (SummonList::const_iterator iter = Summons.begin(); iter != Summons.end(); ++iter)
        {
            if (Creature *visage = Unit::GetCreature(*me, *iter))
            {
                // Not all are dead
                if (phase == visage->GetPhaseMask())
                    return;
                else
                    nextPhase = visage->GetPhaseMask();
            }
        }

        // Roll Insanity
        uint32 spell = GetSpellForPhaseMask(phase);
        uint32 spell2 = GetSpellForPhaseMask(nextPhase);
        Map* pMap = me->GetMap();
        if (!pMap)
            return;

        Map::PlayerList const &PlayerList = pMap->GetPlayers();
        if (!PlayerList.isEmpty())
        {
            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
            {
                if (Player* pPlayer = i->getSource())
                {
                    if (pPlayer->HasAura(spell))
                    {
                        pPlayer->RemoveAurasDueToSpell(spell);
                        if (spell2) // if there is still some different mask cast spell for it
                            pPlayer->CastSpell(pPlayer, spell2, true);
                    }
                }
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim())
            return;

        if (insanityHandled)
        {
            if (!Summons.empty())
                return;

            insanityHandled = 0;
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetControlled(false, UNIT_STAT_STUNNED);
            me->RemoveAurasDueToSpell(INSANITY_VISUAL);
        }

        if (uiMindFlayTimer <= diff)
        {
            DoCast(me->getVictim(), SPELL_MIND_FLAY);
            uiMindFlayTimer = 20*IN_MILLISECONDS;
        } else uiMindFlayTimer -= diff;

        if (uiShadowBoltVolleyTimer <= diff)
        {
            DoCast(me->getVictim(), SPELL_SHADOW_BOLT_VOLLEY);
            uiShadowBoltVolleyTimer = 5*IN_MILLISECONDS;
        } else uiShadowBoltVolleyTimer -= diff;

        if (uiShiverTimer <= diff)
        {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                DoCast(pTarget, SPELL_SHIVER);
            uiShiverTimer = 15*IN_MILLISECONDS;
        } else uiShiverTimer -= diff;

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/)
    {
        DoScriptText(SAY_DEATH_1, me);

        if (pInstance)
            pInstance->SetData(DATA_HERALD_VOLAZJ, DONE);

        Summons.DespawnAll();
        ResetPlayersPhaseMask();
    }

    void KilledUnit(Unit * /*victim*/)
    {
        DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2,SAY_SLAY_3), me);
    }
};
};

class npc_twisted_visage : public CreatureScript
{
public:
    npc_twisted_visage() : CreatureScript("npc_twisted_visage") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_twisted_visageAI (pCreature);
    }
struct  npc_twisted_visageAI : public ScriptedAI
{
    npc_twisted_visageAI(Creature *c) : ScriptedAI(c){}

    uint32 mClass ;
    uint32 mSpecialisation ;
    uint32 spellTimer1 ;
    uint32 spellTimer2 ;
    uint32 spellTimer3 ;

    void Reset()
    {
        spellTimer1 = urand(3000, 6000);
        spellTimer2 = urand(9000, 12000);
        spellTimer3 = urand(15000, 18000);
    }

    void EnterCombat(Unit* who)
    {
        if((mClass == CLASS_DRUID) && (mSpecialisation == SPECIALISATION_FERAL))
            DoCast(SPELL_CAT_FORM) ;
    }

    void SetData(uint32 id, uint32 data)
    {
        if(id == DATA_CLASS)
            mClass = data ;
        if(id == DATA_SPECIALISATION)
            mSpecialisation = data ;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        switch(mClass)
        {
        case CLASS_WARRIOR:
            switch(mSpecialisation)
            {
            case SPECIALISATION_PROTECTION:
                if(spellTimer1 <= diff)
                {
                    DoCast(me->getVictim(), DUNGEON_MODE(SPELL_DEVASTATE, H_SPELL_DEVASTATE));
                    spellTimer1 = urand(12000, 15000) ;
                } else spellTimer1 -= diff ;
                break ;
            case SPECIALISATION_FURY:
                if(spellTimer1 <= diff)
                {
                    DoCast(me->getVictim(), SPELL_INTERCEPT);
                    spellTimer1 = urand(12000, 15000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    DoCast(me->getVictim(), SPELL_HAMSTRING);
                    spellTimer2 = urand(12000, 15000) ;
                } else spellTimer2 -= diff ;
                break ;
            case SPECIALISATION_ARMS:
                if(spellTimer1 <= diff)
                {
                    DoCast(me->getVictim(), SPELL_MORTAL_STRIKE);
                    spellTimer1 = urand(12000, 15000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    DoCast(me->getVictim(), DUNGEON_MODE(SPELL_THUNDER_CLAP, H_SPELL_THUNDER_CLAP));
                    spellTimer2 = urand(12000, 15000) ;
                } else spellTimer2 -= diff ;
                break ;
            }
            break ;
        case CLASS_PALADIN:
            switch(mSpecialisation)
            {
            case SPECIALISATION_PROTECTION:
                if(spellTimer1 <= diff)
                {
                    DoCast(me->getVictim(), DUNGEON_MODE(SPELL_AVENGER_SHIELD, H_SPELL_AVENGER_SHIELD));
                    spellTimer1 = urand(12000, 15000) ;
                } else spellTimer1 -= diff ;
                break ;
            case SPECIALISATION_RETRIBUTION:
                if(spellTimer1 <= diff)
                {
                    DoCast(me, SPELL_SEAL_OF_COMMAND);
                    spellTimer1 = urand(12000, 15000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    DoCast(me->getVictim(), SPELL_JUDGEMENT_OF_LIGHT);
                    spellTimer2 = urand(12000, 15000) ;
                } else spellTimer2 -= diff ;
                break ;
            case SPECIALISATION_HOLY:
                if(spellTimer1 <= diff)
                {
                    DoCast(me->getVictim(), DUNGEON_MODE(SPELL_CONSECRATION, H_SPELL_CONSECRATION));
                    spellTimer1 = urand(12000, 15000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    bool hasHealed = false ;
                    std::list<Creature*> lTwistedVisageList;
                    GetCreatureListWithEntryInGrid(lTwistedVisageList, me, me->GetEntry(), 100.0f);
                    if (!lTwistedVisageList.empty())
                    {
                        for(std::list<Creature*>::iterator iter = lTwistedVisageList.begin(); iter != lTwistedVisageList.end(); ++iter)
                            if ((*iter)->isAlive())
                            {
                                if ((*iter)->GetPhaseMask() == me->GetPhaseMask())
                                {
                                    if((*iter)->GetHealth()<(*iter)->GetMaxHealth())
                                    {
                                        DoCast((*iter), DUNGEON_MODE(SPELL_FLASH_OF_LIGHT, H_SPELL_FLASH_OF_LIGHT));
                                        spellTimer2 = urand(12000, 15000) ;
                                        hasHealed = true ;
                                        break ;
                                    }
                                }
                            }
                    }
                    if(!hasHealed)
                        if(me->GetHealth()<me->GetMaxHealth())
                        {
                            DoCast(me, DUNGEON_MODE(SPELL_FLASH_OF_LIGHT, H_SPELL_FLASH_OF_LIGHT));
                            spellTimer2 = urand(12000, 15000) ;
                            hasHealed = true ;
                        }
                        else
                            spellTimer2 = urand(3000, 5000) ;
                } else spellTimer2 -= diff ;

                if(spellTimer3 <= diff)
                {
                    bool hasHealed = false ;
                    std::list<Creature*> lTwistedVisageList;
                    GetCreatureListWithEntryInGrid(lTwistedVisageList, me, me->GetEntry(), 100.0f);
                    if (!lTwistedVisageList.empty())
                    {
                        for(std::list<Creature*>::iterator iter = lTwistedVisageList.begin(); iter != lTwistedVisageList.end(); ++iter)
                            if ((*iter)->isAlive())
                            {
                                if ((*iter)->GetPhaseMask() == me->GetPhaseMask())
                                {
                                    if((*iter)->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE))
                                    {
                                        DoCast((*iter), SPELL_CLEANSE);
                                        spellTimer3 = urand(12000, 15000) ;
                                        hasHealed = true ;
                                        break ;
                                    }
                                }
                            }
                    }
                    if(!hasHealed)
                        if(me->HasAuraType(SPELL_AURA_PERIODIC_DAMAGE))
                        {
                            DoCast(me, SPELL_CLEANSE);
                            spellTimer3 = urand(12000, 15000) ;
                            hasHealed = true ;
                        }
                        else
                            spellTimer3 = urand(3000, 5000) ;
                } else spellTimer3 -= diff ;
                break ;
            }
            break ;
        case CLASS_HUNTER:
            if(spellTimer1 <= diff)
            {
                if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    DoCast(pTarget, DUNGEON_MODE(SPELL_SHOOT, H_SPELL_SHOOT));
                spellTimer1 = urand(5000, 8000) ;
            } else spellTimer1 -= diff ;

            if(spellTimer2 <= diff)
            {
                DoCast(me, SPELL_DISENGAGE);
                spellTimer2 = urand(12000, 15000) ;
            } else spellTimer2 -= diff ;
            break ;
        case CLASS_ROGUE:
            if(spellTimer1 <= diff)
            {
                DoCast(me->getVictim(), DUNGEON_MODE(SPELL_EVISCERATE, H_SPELL_EVISCERATE));
                spellTimer1 = urand(12000, 15000) ;
            } else spellTimer1 -= diff ;

            if(spellTimer2 <= diff)
            {
                DoCast(me, SPELL_SINISTER_STRIKE);
                spellTimer2 = urand(12000, 15000) ;
            } else spellTimer2 -= diff ;
            break ;
        case CLASS_PRIEST:
            switch(mSpecialisation)
            {
            case SPECIALISATION_SHADOW:
                if(spellTimer1 <= diff)
                {
                    if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                        DoCast(pTarget, DUNGEON_MODE(SPELL_SHADOW_WORD_PAIN, H_SPELL_SHADOW_WORD_PAIN));
                    spellTimer1 = urand(15000, 18000) ;
                } else spellTimer1 -= diff ;
                break ;
            case SPECIALISATION_OTHER:
                if(spellTimer1 <= diff)
                {
                    bool hasHealed = false ;
                    std::list<Creature*> lTwistedVisageList;
                    GetCreatureListWithEntryInGrid(lTwistedVisageList, me, me->GetEntry(), 100.0f);
                    if (!lTwistedVisageList.empty())
                    {
                        for(std::list<Creature*>::iterator iter = lTwistedVisageList.begin(); iter != lTwistedVisageList.end(); ++iter)
                            if ((*iter)->isAlive())
                            {
                                if ((*iter)->GetPhaseMask() == me->GetPhaseMask())
                                {
                                    if((*iter)->GetHealth()<(*iter)->GetMaxHealth())
                                    {
                                        DoCast((*iter), DUNGEON_MODE(SPELL_RENEW, H_SPELL_RENEW));
                                        spellTimer1 = urand(12000, 15000) ;
                                        hasHealed = true ;
                                        break ;
                                    }
                                }
                            }
                    }
                    if(!hasHealed)
                        if(me->GetHealth()<me->GetMaxHealth())
                        {
                            DoCast(me, DUNGEON_MODE(SPELL_RENEW, H_SPELL_RENEW));
                            spellTimer1 = urand(12000, 15000) ;
                            hasHealed = true ;
                        }
                        else
                            spellTimer1 = urand(3000, 5000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    bool hasHealed ;
                    std::list<Creature*> lTwistedVisageList;
                    GetCreatureListWithEntryInGrid(lTwistedVisageList, me, me->GetEntry(), 100.0f);
                    if (!lTwistedVisageList.empty())
                    {
                        for(std::list<Creature*>::iterator iter = lTwistedVisageList.begin(); iter != lTwistedVisageList.end(); ++iter)
                            if ((*iter)->isAlive())
                            {
                                if ((*iter)->GetPhaseMask() == me->GetPhaseMask())
                                {
                                    if((*iter)->GetHealth()<(*iter)->GetMaxHealth())
                                    {
                                        DoCast((*iter), DUNGEON_MODE(SPELL_GREATER_HEAL, H_SPELL_GREATER_HEAL));
                                        spellTimer2 = urand(12000, 15000) ;
                                        hasHealed = true ;
                                        break ;
                                    }
                                }
                            }
                    }
                    if(!hasHealed)
                        if(me->GetHealth()<me->GetMaxHealth())
                        {
                            DoCast(me, DUNGEON_MODE(SPELL_GREATER_HEAL, H_SPELL_GREATER_HEAL));
                            spellTimer2 = urand(12000, 15000) ;
                            hasHealed = true ;
                        }
                        else
                            spellTimer2 = urand(3000, 5000) ;
                } else spellTimer2 -= diff ;
                break ;
            }
            break ;
        case CLASS_DEATH_KNIGHT:
            if(spellTimer1 <= diff)
            {
                DoCast(me->getVictim(), SPELL_DEATH_GRIP);
                spellTimer1 = urand(12000, 15000) ;
            } else spellTimer1 -= diff ;

            if(spellTimer2 <= diff)
            {
                DoCast(me->getVictim(), DUNGEON_MODE(SPELL_PLAGUE_STRIKE, H_SPELL_PLAGUE_STRIKE));
                spellTimer2 = urand(12000, 15000) ;
            } else spellTimer2 -= diff ;
            break ;
        case CLASS_SHAMAN:
            switch(mSpecialisation)
            {
            case SPECIALISATION_ELEMENTAL:
                if(spellTimer1 <= diff)
                {
                    if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                        DoCast(pTarget, DUNGEON_MODE(SPELL_LIGHTNING_BOLT, H_SPELL_LIGHTNING_BOLT));
                    spellTimer1 = urand(12000, 15000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                        DoCast(pTarget, DUNGEON_MODE(SPELL_EARTH_SHOCK, H_SPELL_EARTH_SHOCK));
                    spellTimer2 = urand(12000, 15000) ;
                } else spellTimer2 -= diff ;

                if(spellTimer3 <= diff)
                {
                    if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                        DoCast(pTarget, DUNGEON_MODE(SPELL_THUNDERSTORM, H_SPELL_THUNDERSTORM));
                    spellTimer3 = urand(12000, 15000) ;
                } else spellTimer3 -= diff ;
                break ;
            case SPECIALISATION_ENHANCEMENT:
                if(spellTimer1 <= diff)
                {
                    DoCast(me->getVictim(), SPELL_STORMSTRIKE);
                    spellTimer1 = urand(12000, 15000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    DoCast(me, DUNGEON_MODE(SPELL_BLOODTHIRST, H_SPELL_BLOODTHIRST));
                    spellTimer2 = urand(60000, 65000) ;
                } else spellTimer2 -= diff ;
                break ;
            case SPECIALISATION_RESTORATION:
                if(spellTimer1 <= diff)
                {
                    bool hasHealed = false ;
                    std::list<Creature*> lTwistedVisageList;
                    GetCreatureListWithEntryInGrid(lTwistedVisageList, me, me->GetEntry(), 100.0f);
                    if (!lTwistedVisageList.empty())
                    {
                        for(std::list<Creature*>::iterator iter = lTwistedVisageList.begin(); iter != lTwistedVisageList.end(); ++iter)
                            if ((*iter)->isAlive())
                            {
                                if ((*iter)->GetPhaseMask() == me->GetPhaseMask())
                                {
                                    if((*iter)->GetHealth()<(*iter)->GetMaxHealth())
                                    {
                                        DoCast((*iter), DUNGEON_MODE(SPELL_EARTH_SHIELD, H_SPELL_EARTH_SHIELD));
                                        spellTimer1 = urand(12000, 15000) ;
                                        hasHealed = true ;
                                        break ;
                                    }
                                }
                            }
                    }
                    if(!hasHealed)
                        if(me->GetHealth()<me->GetMaxHealth())
                        {
                            DoCast(me, DUNGEON_MODE(SPELL_EARTH_SHIELD, H_SPELL_EARTH_SHIELD));
                            spellTimer1 = urand(12000, 15000) ;
                            hasHealed = true ;
                        }
                        else
                            spellTimer1 = urand(3000, 5000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    bool hasHealed = false ;
                    std::list<Creature*> lTwistedVisageList;
                    GetCreatureListWithEntryInGrid(lTwistedVisageList, me, me->GetEntry(), 100.0f);
                    if (!lTwistedVisageList.empty())
                    {
                        for(std::list<Creature*>::iterator iter = lTwistedVisageList.begin(); iter != lTwistedVisageList.end(); ++iter)
                            if ((*iter)->isAlive())
                            {
                                if ((*iter)->GetPhaseMask() == me->GetPhaseMask())
                                {
                                    if((*iter)->GetHealth()<(*iter)->GetMaxHealth())
                                    {
                                        DoCast((*iter), DUNGEON_MODE(SPELL_HEALING_WAVE, H_SPELL_HEALING_WAVE));
                                        spellTimer2 = urand(12000, 15000) ;
                                        hasHealed = true ;
                                        break ;
                                    }
                                }
                            }
                    }
                    if(!hasHealed)
                        if(me->GetHealth()<me->GetMaxHealth())
                        {
                            DoCast(me, DUNGEON_MODE(SPELL_HEALING_WAVE, H_SPELL_HEALING_WAVE));
                            spellTimer2 = urand(12000, 15000) ;
                            hasHealed = true ;
                        }
                        else
                            spellTimer2 = urand(3000, 5000) ;
                } else spellTimer2 -= diff ;
                break ;
            }
            break ;
        case CLASS_MAGE:
            if(spellTimer1 <= diff)
            {
                if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    DoCast(pTarget, DUNGEON_MODE(SPELL_FIREBALL, H_SPELL_FIREBALL));
                spellTimer1 = urand(12000, 15000) ;
            } else spellTimer1 -= diff ;

            if(spellTimer2 <= diff)
            {
                DoCast(me->getVictim(), DUNGEON_MODE(SPELL_FROST_NOVA, H_SPELL_FROST_NOVA));
                spellTimer2 = urand(12000, 15000) ;
            } else spellTimer2 -= diff ;
            break ;
        case CLASS_WARLOCK:
            if(spellTimer1 <= diff)
            {
                if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    DoCast(pTarget, DUNGEON_MODE(SPELL_CORRUPTION, H_SPELL_CORRUPTION));
                spellTimer1 = urand(12000, 15000) ;
            } else spellTimer1 -= diff ;

            if(spellTimer2 <= diff)
            {
                if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                    DoCast(pTarget, DUNGEON_MODE(SPELL_SHADOW_BOLT, H_SPELL_SHADOW_BOLT));
                spellTimer2 = urand(12000, 15000) ;
            } else spellTimer2 -= diff ;
            break ;
        case CLASS_DRUID:
            switch(mSpecialisation)
            {
            case SPECIALISATION_BALANCE:
                if(spellTimer1 <= diff)
                {
                    if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                        DoCast(pTarget, DUNGEON_MODE(SPELL_MOONFIRE, H_SPELL_MOONFIRE));
                    spellTimer1 = urand(12000, 15000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                        DoCast(pTarget, DUNGEON_MODE(SPELL_WRATH, H_SPELL_WRATH));
                    spellTimer2 = urand(12000, 15000) ;
                } else spellTimer2 -= diff ;
                break ;
            case SPECIALISATION_RESTORATION:
                if(spellTimer1 <= diff)
                {
                    bool hasHealed = false ;
                    std::list<Creature*> lTwistedVisageList;
                    GetCreatureListWithEntryInGrid(lTwistedVisageList, me, me->GetEntry(), 100.0f);
                    if (!lTwistedVisageList.empty())
                    {
                        for(std::list<Creature*>::iterator iter = lTwistedVisageList.begin(); iter != lTwistedVisageList.end(); ++iter)
                            if ((*iter)->isAlive())
                            {
                                if ((*iter)->GetPhaseMask() == me->GetPhaseMask())
                                {
                                    if((*iter)->GetHealth()<(*iter)->GetMaxHealth())
                                    {
                                        DoCast((*iter), DUNGEON_MODE(SPELL_LIFEBLOOM, H_SPELL_LIFEBLOOM));
                                        spellTimer1 = urand(12000, 15000) ;
                                        hasHealed = true ;
                                        break ;
                                    }
                                }
                            }
                    }
                    if(!hasHealed)
                        if(me->GetHealth()<me->GetMaxHealth())
                        {
                            DoCast(me, DUNGEON_MODE(SPELL_LIFEBLOOM, H_SPELL_LIFEBLOOM));
                            spellTimer2 = urand(12000, 15000) ;
                            hasHealed = true ;
                        }
                        else
                            spellTimer2 = urand(3000, 5000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    bool hasHealed = false ;
                    std::list<Creature*> lTwistedVisageList;
                    GetCreatureListWithEntryInGrid(lTwistedVisageList, me, me->GetEntry(), 100.0f);
                    if (!lTwistedVisageList.empty())
                    {
                        for(std::list<Creature*>::iterator iter = lTwistedVisageList.begin(); iter != lTwistedVisageList.end(); ++iter)
                            if ((*iter)->isAlive())
                            {
                                if ((*iter)->GetPhaseMask() == me->GetPhaseMask())
                                {
                                    if((*iter)->GetHealth()<(*iter)->GetMaxHealth())
                                    {
                                        DoCast((*iter), DUNGEON_MODE(SPELL_NOURISH, H_SPELL_NOURISH));
                                        spellTimer2 = urand(12000, 15000) ;
                                        hasHealed = true ;
                                        break ;
                                    }
                                }
                            }
                    }
                    if(!hasHealed)
                        if(me->GetHealth()<me->GetMaxHealth())
                        {
                            DoCast(me, DUNGEON_MODE(SPELL_NOURISH, H_SPELL_NOURISH));
                            spellTimer2 = urand(12000, 15000) ;
                            hasHealed = true ;
                        }
                        else
                            spellTimer2 = urand(3000, 5000) ;
                } else spellTimer2 -= diff ;
                break ;
            case SPECIALISATION_FERAL:
                if(spellTimer1 <= diff)
                {
                    DoCast(me->getVictim(), DUNGEON_MODE(SPELL_MANGLE, H_SPELL_MANGLE));
                    spellTimer1 = urand(12000, 15000) ;
                } else spellTimer1 -= diff ;

                if(spellTimer2 <= diff)
                {
                    DoCast(me->getVictim(), DUNGEON_MODE(SPELL_RIP, H_SPELL_RIP));
                    spellTimer2 = urand(12000, 15000) ;
                } else spellTimer2 -= diff ;
                break ;
            }
            break ;
        }

        DoMeleeAttackIfReady();
    }

};
};

void AddSC_boss_volazj()
{
    new boss_volazj;
    new npc_twisted_visage;
}
