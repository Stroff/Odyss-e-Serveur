
#include "ScriptPCH.h"

enum eEnums
{
// Creatures

NPC_ADORATEUR            = 100063,
NPC_ELEMENTAIRE            = 100064,
NPC_ESPRIT_GLACE        = 100062,
NPC_ESPRIT_PRINTEMPS    = 100061,
NPC_BLIZZARD            = 100065,

// Spells

SPELL_C_BLIZZARD        = 45846,
SPELL_BLIZZARD            = 28547,

SPELL_CANALISATION        = 43320,
SPELL_RAYON                = 49119,
SPELL_EXPLOSION            = 65333,

SPELL_PRISON            = 54894,

SPELL_POINTE            = 50094,
SPELL_HURLEMENT            = 61211,
SPELL_ROCHER            = 54673,

SPELL_BANIR                = 44836,

SPELL_FLEURS            = 55475,

// récompense

GO_CADEAU                = 200110,

// parole

SAY_INTRO1                 = -1900040,        //Vous pensez m'atteindre ?
SAY_INTRO2                 = -1900041,        //Me voici bien placée
SAY_INTRO3                 = -1900042,        //Nous allons nous amuser

SAY_PREMIER                = -1900043,        // Allez-y, adorateurs
SAY_PLAYER_DEAD            = -1900054,
SAY_START_P3             = -1900044,        // Vous avez survécu à mes adorateurs, mais affronter maintenant mes élémentaires de glace !
SAY_START_P4             = -1900045,        // L'Esprit du Printemps mourra ! ESPRITS DE GLACE, TUEZ LE !
SAY_ESPRIT_PRINTEMPS     = -1900046,        // A l'aide ! Tuez ces esprits avant qu'il ne soit trop tard !
SAY_END_P4                = -1900047,     // Merci aventuriers, mais le combat n'est pas fini
SAY_PRE_FIGHT             = -1900048,        // Assez de ces incompétents ! Vous allez découvrir la fureur de l'hiver !
SAY_FIGHT                 = -1900049,        // Je vais vous geler le sang !

SAY_END1                 = -1900050,        // Voici ou votre folie vous à mener, Esprit de l'Hiver.
SAY_END2                 = -1900051,        // Je ne vous détruirai pas. Cependant, je vous bannis de ce monde.
SAY_END3                 = -1900052,        // Si vous essayez de revenir, ces nobles aventuriers se mettront à nouveau en travers de votre route et vous détruirons.
SAY_END4                 = -1900053        // Merci, nobles gens. Grâce à vous, le printemps reviendra et les saisons seront de nouveau en équilibre. Acceptez ce modeste cadeau en signe de grattitude. Que les saisons vous gardent.
};

struct Locations
{
    float x, y, z, o;
};

static Locations PremierPack[]=
{
    {3016.62, -5095.08, 723.54, 6.071088},
    {3033.47, -5111.10, 722.33, 1.645369},
    {3036.16, -5099.07, 722.70, 3.349683},
    {3030.31, -5091.24, 722.75, 4.119373},
    {3030.31, -5091.24, 722.75, 4.119373}
};

static Locations SecondPack[]=
{    
    {3029.62, -5091.59, 722.75, 3.759658},
    {3032.05, -5094.92, 722.70, 3.759658},
    {3033.90, -5097.55, 722.67, 3.759658}
};
    
static Locations Blizzard[]=
{        
    {3013.91, -5093.84, 724.60, 5.309251},
    {3019.32, -5089.86, 723.80, 5.348521},
    {3025.82, -5085.29, 723.95, 5.301397},
    {3023.31, -5080.95, 723.60, 5.301397},
    {3047.72, -5110.00, 722.74, 2.475534}
};
    
static Locations EspritGlaceLoc[]=
{
    {3033.79, -5099.67, 722.51, 1.453731},
    {3028.61, -5090.08, 722.74, 6.028676},
    {3036.36, -5085.41, 722.64, 4.650304},
    {3042.21, -5093.27, 722.29, 2.875304}
};

static Locations EspritHiver[]=
{
    {3062.16, -5142.60, 745.86, 2.420558},
    {3058.34, -5138.34, 744.55, 2.314531},
    {3024.10, -5104.51, 720.40, 0.746088}
};

static Locations EspritPrintempsLoc[]=
{
    {3035.86, -5092.53, 724.83, 3.967795}
};
    
class boss_noel : public CreatureScript
{
public:
    boss_noel() : CreatureScript("boss_noel") { }	
struct  boss_noelAI : public ScriptedAI
{
    boss_noelAI(Creature *c) : ScriptedAI(c){}

    Creature* blizzard1;
    Creature* blizzard2;
    Creature* blizzard3;
    Creature* blizzard4;
    
    Creature* EspritPrintemps;
    
    Creature* EspritGlace1;
    Creature* EspritGlace2;
    Creature* EspritGlace3;
    Creature* EspritGlace4;
    
    uint32 phase;
    
    uint32 intro_timer;
    uint32 intro;
    
    uint32 phase_2_Timer_1;
    uint32 vagues_1;
    uint32 phase_2_Timer_2;
    
    bool phase3;
    uint32 blizzard_timer;
    uint32 phase3_timer;
    
    bool phase4;
    uint32 domages_timer;
    bool ESPRIT_MORT;
    
    uint32 P5_TIMER;
    uint32 P5_INTRO;
    
    uint32 attaque_1_timer;
    uint32 attaque_2_timer;
    uint32 attaque_3_timer;
    
    bool END;
    uint32 end_timer;
    uint32 end_phase;
    
    void Reset()
    {
        phase = 0;
        
        intro_timer = 0;
        intro = 1;
        
        phase_2_Timer_1 = 1000;
        vagues_1 = 1;
        phase_2_Timer_2 = 30000;
        
        phase3 = false;
        blizzard_timer = 500;
        phase3_timer = 35000;
        
        phase4 = false;
        domages_timer = 3000;
        ESPRIT_MORT = false;
        
        P5_TIMER = 0;
        P5_INTRO = 1;
        
        attaque_1_timer = 5000;
        attaque_2_timer = 9000;
        attaque_3_timer = 13000;
        
        END = false;
        end_timer = 0;
        end_phase = 1;
        
        me->setFaction(14);
        me->SetVisible(true);
    }

    void KilledUnit(Unit *victim)
    {
    }

    void JustDied(Unit *victim)
    {
    }

    void EnterCombat(Unit *who)
    {
        phase = 1;
    }

    void SummonPackOne ()
    {
        for (int i = 0; i < 5; ++i)
            {
                me->SummonCreature(NPC_ADORATEUR, PremierPack[i].x, PremierPack[i].y, PremierPack[i].z, PremierPack[i].o, TEMPSUMMON_DEAD_DESPAWN, 0);
                me->SummonCreature(NPC_ADORATEUR, PremierPack[i].x, PremierPack[i].y, PremierPack[i].z, PremierPack[i].o, TEMPSUMMON_DEAD_DESPAWN, 0);
            }
    }
    
    void UpdateAI(const uint32 diff)
    {
        
        //Phase 1
        switch (phase)
        {
            case 1:                
                if (intro_timer < diff)
                {
                    switch (intro)
                    {
                        case 1:
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->AddUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT + MOVEMENTFLAG_LEVITATING);
                            me->SetSpeed(MOVE_WALK,3.0f,true);
                            DoScriptText(SAY_INTRO1, me);
                            intro_timer = 3000;
                            ++intro;
                        break;
                        
                        case 2:
                            me->GetMotionMaster()->MovePoint(1, EspritHiver[0].x, EspritHiver[0].y, EspritHiver[0].z);
                            intro_timer = 5000;
                            ++intro;
                        break;
                    
                        case 3:
                            me->GetMotionMaster()->MovePoint(1, EspritHiver[1].x, EspritHiver[1].y, EspritHiver[1].z);
                            DoScriptText(SAY_INTRO2, me);
                            intro_timer = 2000;
                            ++intro;
                        break;
                    
                        case 4:
                            DoScriptText(SAY_INTRO3, me);
                            intro_timer = 2000;
                            ++intro;
                        break;
                    
                        case 5:
                            ++phase;
                        break;
                    }
                }
                else intro_timer -= diff;
            break;
                
            case 2:                
                if (phase_2_Timer_1 < diff && vagues_1 < 5)
                {
                    DoScriptText(SAY_PREMIER, me);
                    SummonPackOne();
                    phase_2_Timer_1 = 7000;
                    ++vagues_1;
                }
                else phase_2_Timer_1 -= diff;

                if (phase_2_Timer_2 < diff)
                {
                    ++phase;
                }
                else phase_2_Timer_2 -= diff;

                break;
                
            case 3:
                if (!phase3)
                {
                    DoScriptText(SAY_START_P3, me);
                    blizzard1 = me->SummonCreature(NPC_BLIZZARD, Blizzard[0].x, Blizzard[0].y, Blizzard[0].z, Blizzard[0].o,TEMPSUMMON_TIMED_DESPAWN,30000);
                    blizzard2 = me->SummonCreature(NPC_BLIZZARD, Blizzard[0].x, Blizzard[0].y, Blizzard[0].z, Blizzard[0].o,TEMPSUMMON_TIMED_DESPAWN,30000);
                    blizzard3 = me->SummonCreature(NPC_BLIZZARD, Blizzard[0].x, Blizzard[0].y, Blizzard[0].z, Blizzard[0].o,TEMPSUMMON_TIMED_DESPAWN,30000);
                    blizzard4 = me->SummonCreature(NPC_BLIZZARD, Blizzard[0].x, Blizzard[0].y, Blizzard[0].z, Blizzard[0].o,TEMPSUMMON_TIMED_DESPAWN,30000);
                    
                    blizzard1->SetReactState(REACT_PASSIVE);
                    blizzard2->SetReactState(REACT_PASSIVE);
                    blizzard3->SetReactState(REACT_PASSIVE);
                    blizzard4->SetReactState(REACT_PASSIVE);
                    
                    blizzard1->GetMotionMaster()->MovePoint(1, Blizzard[1].x,Blizzard[1].y, Blizzard[1].z);
                    blizzard2->GetMotionMaster()->MovePoint(1, Blizzard[2].x,Blizzard[2].y, Blizzard[2].z);
                    blizzard3->GetMotionMaster()->MovePoint(1, Blizzard[3].x,Blizzard[3].y, Blizzard[3].z);
                    blizzard4->GetMotionMaster()->MovePoint(1, Blizzard[4].x,Blizzard[4].y, Blizzard[4].z);
                    
                    for (int i = 0; i < 3; ++i)
                    {
                        me->SummonCreature(NPC_ELEMENTAIRE, SecondPack[i].x, SecondPack[i].y, SecondPack[i].z, SecondPack[i].o,TEMPSUMMON_DEAD_DESPAWN,0);
                    }
                    
                    me->CastSpell(me, SPELL_C_BLIZZARD, true);
                    
                    phase3 = true;
                }
                
                if (blizzard_timer < diff)
                {
                    blizzard1->CastSpell(blizzard1, SPELL_BLIZZARD, true);
                    blizzard2->CastSpell(blizzard1, SPELL_BLIZZARD, true);
                    blizzard3->CastSpell(blizzard1, SPELL_BLIZZARD, true);
                    blizzard4->CastSpell(blizzard1, SPELL_BLIZZARD, true);
                    
                    blizzard_timer = 500;
                }
                else blizzard_timer -= diff;
                    
                if (phase3_timer < diff)
                    ++phase;
                else phase3_timer -= diff;
                    
                break;
                
            case 4:
                if (!phase4)
                    {
                    DoScriptText(SAY_START_P4, me);
                    me->RemoveAurasDueToSpell(SPELL_C_BLIZZARD);
                    
                    EspritPrintemps = me->SummonCreature(NPC_ESPRIT_PRINTEMPS, EspritPrintempsLoc[0].x, EspritPrintempsLoc[0].y, EspritPrintempsLoc[0].z, EspritPrintempsLoc[0].o,TEMPSUMMON_DEAD_DESPAWN,0);
                    
                    DoScriptText(SAY_ESPRIT_PRINTEMPS, EspritPrintemps);
                    
                    EspritGlace1  = me->SummonCreature(NPC_ESPRIT_GLACE, EspritGlaceLoc[0].x, EspritGlaceLoc[0].y, EspritGlaceLoc[0].z, EspritGlaceLoc[0].o,TEMPSUMMON_DEAD_DESPAWN,0);
                    EspritGlace2  = me->SummonCreature(NPC_ESPRIT_GLACE, EspritGlaceLoc[1].x, EspritGlaceLoc[1].y, EspritGlaceLoc[1].z, EspritGlaceLoc[1].o,TEMPSUMMON_DEAD_DESPAWN,0);
                    EspritGlace3  = me->SummonCreature(NPC_ESPRIT_GLACE, EspritGlaceLoc[2].x, EspritGlaceLoc[2].y, EspritGlaceLoc[2].z, EspritGlaceLoc[2].o,TEMPSUMMON_DEAD_DESPAWN,0);
                    EspritGlace4  = me->SummonCreature(NPC_ESPRIT_GLACE, EspritGlaceLoc[3].x, EspritGlaceLoc[3].y, EspritGlaceLoc[3].z, EspritGlaceLoc[3].o,TEMPSUMMON_DEAD_DESPAWN,0);
                    
                    EspritPrintemps->CastSpell(EspritPrintemps, SPELL_CANALISATION, true);
                    
                    EspritGlace1->SetReactState(REACT_PASSIVE);
                    EspritGlace2->SetReactState(REACT_PASSIVE);
                    EspritGlace3->SetReactState(REACT_PASSIVE);
                    EspritGlace4->SetReactState(REACT_PASSIVE);
                    
                    EspritGlace1->CastSpell(EspritPrintemps, SPELL_RAYON, true);
                    EspritGlace2->CastSpell(EspritPrintemps, SPELL_RAYON, true);
                    EspritGlace3->CastSpell(EspritPrintemps, SPELL_RAYON, true);
                    EspritGlace4->CastSpell(EspritPrintemps, SPELL_RAYON, true);
                    
                    phase4 = true;
                    }
                    
                if (domages_timer < diff)
                    {
                    if (EspritGlace1->isAlive() || EspritGlace2->isAlive() || EspritGlace3->isAlive() || EspritGlace4->isAlive())
                        {
                        EspritPrintemps->DealDamage(EspritPrintemps, 5000);
                        domages_timer = 1000;
                        }
                    }
                else
                    {domages_timer -= diff;}
                    
                if (!(GetClosestCreatureWithEntry(me, NPC_ESPRIT_PRINTEMPS, 5000.0f)))
                {
                    if(!ESPRIT_MORT)
                    {
                        DoScriptText(SAY_PLAYER_DEAD, me);
                            if (EspritGlace1)
                                EspritGlace1->CastSpell(EspritGlace1, SPELL_EXPLOSION, true);
                            if (EspritGlace2)
                                EspritGlace2->CastSpell(EspritGlace2, SPELL_EXPLOSION, true);
                            if (EspritGlace3)
                                EspritGlace3->CastSpell(EspritGlace3, SPELL_EXPLOSION, true);
                            if (EspritGlace4)
                                EspritGlace4->CastSpell(EspritGlace4, SPELL_EXPLOSION, true);

                            ESPRIT_MORT = true;
                    }
                }
                    
                if (!(GetClosestCreatureWithEntry(EspritPrintemps, NPC_ESPRIT_GLACE, 500.0f)))
                {
                    DoScriptText(SAY_END_P4, EspritPrintemps);
                    ++phase;
                }
                    
                break;
                
            case 5:
                if (P5_TIMER < diff)
                {
                    switch (P5_INTRO)
                    {
                        case 1:
                            EspritPrintemps->CastSpell(EspritPrintemps, SPELL_PRISON, true);
                            DoScriptText(SAY_PRE_FIGHT, me);
                            P5_TIMER = 2000;
                            ++P5_INTRO;
                            break;
                            
                        case 2:
                            me->GetMotionMaster()->MovePoint(1, EspritHiver[2].x, EspritHiver[2].y, EspritHiver[2].z);
                            P5_TIMER = 5000;
                            ++P5_INTRO;
                            break;
                            
                        case 3:
                            DoScriptText(SAY_FIGHT, me);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->SetSpeed(MOVE_WALK,1.0f,true);
                            P5_TIMER = 2000;
                            ++P5_INTRO;
                            break;
                            
                        case 4:
                            ++phase;
                            break;
                    }
                }
                else P5_TIMER -= diff;
                
                break;
                
            case 6:
                
                if (attaque_1_timer < diff)
                {
                    Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true);
                    me->CastSpell(pTarget, SPELL_HURLEMENT, true);
                    attaque_1_timer = 5000;
                }
                else attaque_1_timer -= diff;

                if (attaque_2_timer < diff)
                {
                    Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true);
                    me->CastSpell(pTarget, SPELL_ROCHER, true);
                    attaque_2_timer = 9000;
                }
                else attaque_2_timer -= diff;

                if (attaque_3_timer < diff)
                {
                    Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true);
                    me->CastSpell(pTarget, SPELL_POINTE, true);
                    attaque_3_timer = 13000;
                }
                else attaque_3_timer -= diff;
                
                DoMeleeAttackIfReady();
                
                break;
                
                if (me->GetHealth() <= 20000)
                {
                    me->CastSpell(me, 48788, true);
                    me->setFaction(35);
                    ++phase;
                }
                
            case 7:
                if (!END)
                {
                    EspritPrintemps->RemoveAurasDueToSpell(SPELL_PRISON);
                    me->CastSpell(me, SPELL_BANIR, true);
                    EspritPrintemps->SetUInt64Value(UNIT_FIELD_TARGET, me->GetGUID());
                    me->SetUInt64Value(UNIT_FIELD_TARGET, EspritPrintemps->GetGUID());
                }
                    
                if (end_timer < diff)
                {
                    switch (end_phase)
                    {
                        case 1:
                            DoScriptText(SAY_END1, EspritPrintemps);
                            ++end_phase;
                            end_timer = 2000;
                            break;
                        case 2:
                            DoScriptText(SAY_END2, EspritPrintemps);
                            ++end_phase;
                            end_timer = 3000;
                            break;
                        case 3:
                            DoScriptText(SAY_END3, EspritPrintemps);
                            ++end_phase;
                            end_timer = 4000;
                            break;
                        case 4:
                            me->SetVisible(false);
                            EspritPrintemps->CastSpell(EspritPrintemps, SPELL_FLEURS, true);
                            DoScriptText(SAY_END4, EspritPrintemps);
                            ++end_phase;
                            end_timer = 3000;
                            break;
                        case 5:
                            EspritPrintemps->SetVisible(false);
                            me->SummonGameObject(GO_CADEAU, 3035.86, -5092.53, 724.83, 3.967795, 0, 0, 0, 0, 60000);
                            end_timer = 2000;
                            break;
                        case 6:
                            EspritPrintemps->DealDamage(EspritPrintemps, EspritPrintemps->GetMaxHealth());
                            me->DealDamage(me, me->GetMaxHealth());
                            break;
                    }
                }
                else end_timer -= diff;
            
        }
    }               
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new boss_noelAI (pCreature);
};
};


void AddSC_boss_noel()
{
new boss_noel();
}
