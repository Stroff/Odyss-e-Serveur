/* Script de l'event Halloween créé pour le serveur Renaissance Reborn */


#include "ScriptPCH.h"

#include "ScriptedEscortAI.h"

/*######
## npc_halloween
## Escorte
######*/

enum
{
    SAY_START           = -1900011,
    SAY_MORPH            = -1900012,
    SAY_GIVE_BAR        = -1900013,
    SAY_THANKS            = -1900014,
    SAY_GIVE_ADAL        = -1900015,
    SAY_THANKS_ADAL        = -1900016,
    SAY_NO                = -1900017,
    SAY_PITY            = -1900018,
    SAY_BAD                = -1900019,
    SAY_HELP            = -1900020,
    SAY_STEAL            = -1900021,
    
    GIFT_BAR            = 200100,
    GIFT_ADAL            = 200101,
    
    NPC_BRIGITTE        = 50006,
    NPC_ADAL            = 50007,
    NPC_HARIS            = 50008,
    NPC_BAD                = 50009,
    
    DISPLAY_MORPH        = 24213,
    
    QUEST_HALLOWEEN     = 50000
};
class npc_halloween : public CreatureScript
{
public:
    npc_halloween() : CreatureScript("npc_halloween") { }
	
struct npc_halloweenAI : public npc_escortAI
{
    npc_halloweenAI(Creature *c) : npc_escortAI(c) {}

    Creature* Summ4;
    
    void WaypointReached(uint32 i)
    {
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
            return;

        switch(i)
        {
            case 0: DoScriptText(SAY_START, me, pPlayer); break;
            case 4: 
                {
                    DoScriptText(SAY_MORPH, me, pPlayer);
                    me->SetDisplayId(DISPLAY_MORPH);
                    SetRun(true);
                    break;
            case 12:
                {
                    me->SetOrientation(1.209464);
                    Creature* Summ1 = me->SummonCreature(NPC_BRIGITTE, -1929.680054, 5237.740234, -41.817902, 4.345870, TEMPSUMMON_DEAD_DESPAWN, 0);
                    me->SummonGameObject(GIFT_BAR, -1926.529785, 5234.277832, -40.757816, 4.366762, 0, 0, 0, 0, 60000);
                    DoScriptText(SAY_GIVE_BAR, Summ1);
                    break;
                }
            case 13:
                {
                    DoScriptText(SAY_THANKS, me);
                    break;
                }
            case 23:
                {
                    Creature* Summ2 = me->SummonCreature(NPC_ADAL, -1863.680054, 5430.040039, -9.705490, 3.717550, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    me->SummonGameObject(GIFT_ADAL, -1865.812256, 5424.634766, -9.705078, 3.302548, 0, 0, 0, 0, 60000);
                    DoScriptText(SAY_GIVE_ADAL, Summ2);
                    break;
                }
            case 24:
                {
                    DoScriptText(SAY_THANKS_ADAL, me);
                    break;
                }
            case 37:
                {
                    Creature* Summ3= me->SummonCreature(NPC_HARIS, -1739.42, 5149.850098, -37.121601, 4.223700, TEMPSUMMON_TIMED_DESPAWN, 60000);
                    DoScriptText(SAY_NO, Summ3);
                    break;
                }
            case 38:
                {
                    DoScriptText(SAY_PITY, me);
                    break;
                }
            case 44:
                {
                    Summ4 = me->SummonCreature(NPC_BAD, -1839.534546, 5146.425781, -42.459606, 0.298405, TEMPSUMMON_DEAD_DESPAWN, 0);
                    DoScriptText(SAY_BAD, Summ4);
                    break;
                }
            case 45:
                {
                    DoScriptText(SAY_HELP, me);
                    break;
                }
            case 46:
                {
                    Summ4->setDeathState(JUST_DIED);
                    break;
                }
            case 47:
                {
                    DoScriptText(SAY_STEAL, me);
                    break;
                }
            case 48:
                {
                    if (pPlayer)
                        pPlayer->GroupEventHappens(QUEST_HALLOWEEN,me);
                    break;
                }
            }
        }
    }
    void Reset() {}
};

bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* quest)
{
    if (npc_escortAI* pEscortAI = CAST_AI(npc_halloweenAI, pCreature->AI()))
    {
        pEscortAI->Start(true, false, pPlayer->GetGUID());
    }
    return true;
}

CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_halloweenAI(pCreature);
}
};
/*######
## Boss
## Le méchant qui prend les bonbons
######*/

struct Locations
{
    float x, y, z;
};

static Locations Spawn1[]=
{
    {-254.461105,2279.690186,75.000595},
    {-232.062576,2269.812988,75.000595},
    {-229.897888,2289.188965,74.999435},
    {-247.090851,2296.788818,74.999435},
};

static Locations Spawn2[]=
{
    {-252.464584,2288.688721,84.385147},
    {-238.596069,2283.314697,84.505455}
};

enum
{

    SAY_INTRO                = -1900030,
    
    SAY_CITROUILLES            = -1900031,
    SAY_INTRO_GARGOUILLE    = -1900032,
    SAY_GARGOUILLE            = -1900033,
    SAY_ENTER_FIGHT            = -1900034,
    SAY_DEAD                = -1900035,
    
    NPC_CITROUILLE            = 50021,
    NPC_GARGOUILLE            = 50022,
    
    SPELL_GRAVITY            = 34480,
    SPELL_GRAVITY_AURA        = 39432,
    SPELL_SHADOW_FISURE     = 27810,
    SPELL_IMAGE_MIROIR        = 55342,
    SPELL_CITROUILLE        = 50070,

    
};
class npc_boss_halloween : public CreatureScript
{
public:
    npc_boss_halloween() : CreatureScript("npc_boss_halloween") { }
struct npc_boss_halloweenAI : public ScriptedAI
{
    npc_boss_halloweenAI(Creature *c) : ScriptedAI(c) {}

    uint32 Phase;
    uint32 Vagues1;
    uint32 Vagues2;
    
    uint32 Phase_1_Timer;
    uint32 Phase_2_Timer;
    uint32 Phase_3_Timer;
    
    bool combat;
    bool gravity;
    bool enter_fight;
    bool miroir;
    bool citrouille;
    
    void Reset() 
    {
    gravity = false;
    enter_fight = false;
    miroir = false;
    citrouille = false;
    
    combat = 0;
    Phase = 0;
    Vagues1 = 0;
    Vagues2 = 0;
    
    Phase_1_Timer = 7000;
    Phase_2_Timer = 7000;
    Phase_3_Timer = 20000;
    }
    
    void SummonCitrouilles ()
    {
        me->SummonCreature(NPC_CITROUILLE, Spawn1[0].x, Spawn1[0].y, Spawn1[0].z, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
        me->SummonCreature(NPC_CITROUILLE, Spawn1[1].x, Spawn1[1].y, Spawn1[1].z, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
        me->SummonCreature(NPC_CITROUILLE, Spawn1[2].x, Spawn1[2].y, Spawn1[2].z, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
        me->SummonCreature(NPC_CITROUILLE, Spawn1[3].x, Spawn1[3].y, Spawn1[3].z, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
    }
    
    void SummonGargouilles ()
    {
        me->SummonCreature(NPC_GARGOUILLE, Spawn2[0].x, Spawn2[0].y, Spawn2[0].z, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
        me->SummonCreature(NPC_GARGOUILLE, Spawn2[1].x, Spawn2[1].y, Spawn2[1].z, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
    }
    
    void EnterCombat(Unit* who) 
    {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->AddUnitMovementFlag(MOVEMENTFLAG_ONTRANSPORT + MOVEMENTFLAG_LEVITATING);
        me->GetMotionMaster()->MovePoint(1, -245.234787, 2285.565895, 86.331779);
        DoScriptText(SAY_INTRO, me);
        Phase = 1;
    }

    
    void JustDied(Unit *victim)
    {
        DoScriptText(SAY_DEAD, me);
    }
    
    
    void UpdateAI(const uint32 diff)
    {
        
        //Phase 1
        switch (Phase)
        {
            case 1:
            {
                if (Phase_1_Timer < diff)
                {
                    ++Vagues1;
                    // Lance la prochaine vague dans 10 secondes
                    Phase_1_Timer = 10000;
                    
                    if (Vagues1 <= 3)
                    {
                        DoScriptText(SAY_CITROUILLES, me);
                        SummonCitrouilles();
                    }
                    
                    if (Vagues1 == 4)
                        ++Phase;
                }
                else
                    Phase_1_Timer -= diff;
                break;
            }
            // phase 2
            case 2:
            {
                if (gravity == false)
                {
                    Map* pMap = me->GetMap();
                    Map::PlayerList const &PlayerList = pMap->GetPlayers();
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        Unit* pUnit = i->getSource();
                        if (pUnit && (pUnit->GetTypeId() == TYPEID_PLAYER))
                        {
                            if (pUnit->isAlive())
                            {
                                if(me->IsWithinDist(pUnit, 30.0f, false))
                                {
                                    DoTeleportPlayer(pUnit, Spawn2[0].x, Spawn2[0].y, Spawn2[0].z, pUnit->GetOrientation());
                                    
                                    pUnit->CastSpell(pUnit, SPELL_GRAVITY, true, 0, 0, me->GetGUID());
                                    pUnit->CastSpell(pUnit, SPELL_GRAVITY_AURA, true, 0, 0, me->GetGUID());
                                }
                            }
                        }
                    }
                    gravity = true;
                }
                if (Phase_2_Timer < diff)
                {
                    ++Vagues2;
                    // Lance la prochaine vague dans 10 secondes
                    Phase_2_Timer = 10000;
                    if (Vagues2 <= 2)
                    {
                        DoScriptText(SAY_GARGOUILLE, me);
                        SummonGargouilles();
                    }
                    
                    if (Vagues2 == 3)
                        ++Phase;
                }
                else
                    Phase_2_Timer -= diff;
                break;
            }
            // phase 3
            case 3:
            {
                if (enter_fight == false)
                {
                    DoScriptText(SAY_ENTER_FIGHT, me);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    enter_fight = true;
                }
                    
                if (Phase_3_Timer < diff)
                {
                    // Prochain inversement de gravité dans 50 secondes
                    Phase_3_Timer = 50000;
                    
                    // Inversement de gravité
                    Map* pMap = me->GetMap();
                    Map::PlayerList const &PlayerList = pMap->GetPlayers();
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        Unit* pUnit = i->getSource();
                        if (pUnit && (pUnit->GetTypeId() == TYPEID_PLAYER))
                        {
                            if (i->getSource()->isAlive())
                            {
                                if(me->IsWithinDist(i->getSource(), 30.0f, false))
                                {
                                    DoTeleportPlayer(pUnit, Spawn2[0].x, Spawn2[0].y, Spawn2[0].z, pUnit->GetOrientation());
                                    pUnit->CastSpell(pUnit, SPELL_GRAVITY, false, 0, 0, me->GetGUID());
                                    pUnit->CastSpell(pUnit, SPELL_GRAVITY_AURA, true, 0, 0, me->GetGUID());
                                }
                            }
                        }
                    // fin Inversement de gravité
                    }
                    
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0, 0, true))
                    DoCast(target, SPELL_SHADOW_FISURE);
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0, 0, true))
                    DoCast(target, SPELL_SHADOW_FISURE);
                }
                else
                    Phase_3_Timer -= diff;
                
                if (!miroir && (me->GetHealth()*100)/me->GetMaxHealth() <= 50)
                {
                    DoCast(me, SPELL_IMAGE_MIROIR, true);
                    miroir = true;
                }
                if (!citrouille && (me->GetHealth()*100)/me->GetMaxHealth() <= 20)
                {
                    DoCast(me, SPELL_CITROUILLE, true);
                    citrouille = true;
                }
                
            DoMeleeAttackIfReady();
            }            
        }
    }               
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new npc_boss_halloweenAI(pCreature);
}
};

void AddSC_event_halloween()
{
new npc_halloween();
new npc_boss_halloween();
}
