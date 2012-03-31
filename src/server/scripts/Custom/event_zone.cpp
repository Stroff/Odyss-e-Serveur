
#include "ScriptPCH.h"
#include "GameObject.h"

enum eEventZMograine
{

    NPC_GARDIEN_ALLIANCE            = 400000,
    NPC_GARDIEN_HORDE                = 400001,
    NPC_TRIGGER_ENTRY_ALLIANCE        = 400002,
    NPC_TRIGGER_ENTRY_HORDE            = 400003,
    SPELL_EVENT_ZONE_PROTECTION        = 1449
    
};

enum eZoneMograine
{
    GO_EVENT_ZONE_1_ALLIANCE         = 500000,
    GO_EVENT_ZONE_1_HORDE            = 500001,
    GO_EVENT_ZONE_2_ALLIANCE         = 500002,
    GO_EVENT_ZONE_2_HORDE            = 500003,
    GO_EVENT_ZONE_3_ALLIANCE         = 500004,
    GO_EVENT_ZONE_3_HORDE            = 500005,
    GO_EVENT_ZONE_4_ALLIANCE         = 500006,
    GO_EVENT_ZONE_4_HORDE            = 500007,
    GO_EVENT_ZONE_5_ALLIANCE         = 500008,
    GO_EVENT_ZONE_5_HORDE            = 500009,
    GO_EVENT_ZONE_6_ALLIANCE         = 500010,
    GO_EVENT_ZONE_6_HORDE            = 500011,
    GO_EVENT_ZONE_7_ALLIANCE         = 500012,
    GO_EVENT_ZONE_7_HORDE            = 500013,
    GO_EVENT_ZONE_8_ALLIANCE         = 500014,
    GO_EVENT_ZONE_8_HORDE            = 500015,
    GO_EVENT_ZONE_9_ALLIANCE         = 500016,
    GO_EVENT_ZONE_9_HORDE            = 500017,
    GO_EVENT_ZONE_10_ALLIANCE         = 500018,
    GO_EVENT_ZONE_10_HORDE            = 500019,
    GO_EVENT_ZONE_11_ALLIANCE         = 500020,
    GO_EVENT_ZONE_11_HORDE            = 500021,
    GO_EVENT_ZONE_12_ALLIANCE         = 500022,
    GO_EVENT_ZONE_12_HORDE            = 500023,
    GO_EVENT_ZONE_13_ALLIANCE         = 500024,
    GO_EVENT_ZONE_13_HORDE            = 500025,
    GO_EVENT_ZONE_14_ALLIANCE         = 500026,
    GO_EVENT_ZONE_14_HORDE            = 500027,
    GO_EVENT_ZONE_15_ALLIANCE         = 500028,
    GO_EVENT_ZONE_15_HORDE            = 500029,
    GO_EVENT_ZONE_16_ALLIANCE         = 500030,
    GO_EVENT_ZONE_16_HORDE            = 500031,
    GO_EVENT_ZONE_17_ALLIANCE         = 500032,
    GO_EVENT_ZONE_17_HORDE            = 500033,
    GO_EVENT_ZONE_18_ALLIANCE         = 500034,
    GO_EVENT_ZONE_18_HORDE            = 500035,
    GO_EVENT_ZONE_19_ALLIANCE         = 500036,
    GO_EVENT_ZONE_19_HORDE            = 500037,
    GO_EVENT_ZONE_FINAL_ALLIANCE    = 500040,
    GO_EVENT_ZONE_FINAL_HORDE        = 500041,
    GO_EVENT_ZONE_1_NEUTRE            = 500050,
    GO_EVENT_ZONE_2_NEUTRE            = 500051,
    GO_EVENT_ZONE_3_NEUTRE            = 500052,
    GO_EVENT_ZONE_4_NEUTRE            = 500053,
    GO_EVENT_ZONE_5_NEUTRE            = 500054,
    GO_EVENT_ZONE_6_NEUTRE            = 500055,
    GO_EVENT_ZONE_7_NEUTRE            = 500056,
    GO_EVENT_ZONE_8_NEUTRE            = 500057,
    GO_EVENT_ZONE_9_NEUTRE            = 500058,
    GO_EVENT_ZONE_10_NEUTRE            = 500059,
    GO_EVENT_ZONE_11_NEUTRE            = 500060,
    GO_EVENT_ZONE_12_NEUTRE            = 500061,
    GO_EVENT_ZONE_13_NEUTRE            = 500062,
    GO_EVENT_ZONE_14_NEUTRE            = 500063,
    GO_EVENT_ZONE_15_NEUTRE            = 500064,
    GO_EVENT_ZONE_16_NEUTRE            = 500065,
    GO_EVENT_ZONE_17_NEUTRE            = 500066,
    GO_EVENT_ZONE_18_NEUTRE            = 500067,
    GO_EVENT_ZONE_19_NEUTRE            = 500068,
    GO_EVENT_ZONE_RESET                = 500070
};

class go_event_banner : public GameObjectScript
{
public:
    go_event_banner() : GameObjectScript("go_event_banner") { }
	
bool GOHello(Player *pPlayer, GameObject *pGO)
{
    uint32 GardienEntry = 0;

    bool ZONE_1_ALLIANCE = false;
    bool ZONE_1_HORDE = false;
    bool ZONE_2_ALLIANCE = false;
    bool ZONE_2_HORDE = false;
    bool ZONE_3_ALLIANCE = false;
    bool ZONE_3_HORDE = false;
    bool ZONE_4_ALLIANCE = false;
    bool ZONE_4_HORDE = false;
    bool ZONE_5_ALLIANCE = false;
    bool ZONE_5_HORDE = false;
    bool ZONE_6_ALLIANCE = false;
    bool ZONE_6_HORDE = false;
    bool ZONE_7_ALLIANCE = false;
    bool ZONE_7_HORDE = false;
    bool ZONE_8_ALLIANCE = false;
    bool ZONE_8_HORDE = false;
    bool ZONE_9_ALLIANCE = false;
    bool ZONE_9_HORDE = false;
    bool ZONE_10_ALLIANCE = false;
    bool ZONE_10_HORDE = false;
    bool ZONE_11_ALLIANCE = false;
    bool ZONE_11_HORDE = false;
    bool ZONE_12_ALLIANCE = false;
    bool ZONE_12_HORDE = false;
    bool ZONE_13_ALLIANCE = false;
    bool ZONE_13_HORDE = false;
    bool ZONE_14_ALLIANCE = false;
    bool ZONE_14_HORDE = false;
    bool ZONE_15_ALLIANCE = false;
    bool ZONE_15_HORDE = false;
    bool ZONE_16_ALLIANCE = false;
    bool ZONE_16_HORDE = false;
    bool ZONE_17_ALLIANCE = false;
    bool ZONE_17_HORDE = false;
    bool ZONE_18_ALLIANCE = false;
    bool ZONE_18_HORDE = false;
    bool ZONE_19_ALLIANCE = false;
    bool ZONE_19_HORDE = false;
    bool ZONE_FINAL_ALLIANCE = false;
    bool ZONE_FINAL_HORDE = false;
    bool ZONE_END = false;
    
    
    float fX1, fY1, fZ1;
    fX1 = pGO->GetPositionX();
    fY1 = pGO->GetPositionY();
    fZ1 = pGO->GetPositionZ();
    
    float fX2, fY2, fZ2;
    pGO->GetClosePoint(fX2, fY2, fZ2, pGO->GetObjectSize(), INTERACTION_DISTANCE);
    
    switch(pGO->GetEntry())
    {
        case GO_EVENT_ZONE_1_ALLIANCE:
            if (ZONE_2_HORDE || ZONE_3_HORDE || ZONE_4_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_1_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_1_HORDE = true;
            ZONE_1_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_1_HORDE:
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_1_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_1_HORDE = false;
            ZONE_1_ALLIANCE = true;
            pGO->Delete();
            break;
        case GO_EVENT_ZONE_2_ALLIANCE:
            if (ZONE_1_HORDE || ZONE_4_HORDE || ZONE_5_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_2_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_2_HORDE = true;
            ZONE_2_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_2_HORDE:
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_2_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_2_HORDE = false;
            ZONE_2_ALLIANCE = true;
            pGO->Delete();
            break;
        case GO_EVENT_ZONE_3_ALLIANCE:
            if (ZONE_1_HORDE || ZONE_4_HORDE || ZONE_6_HORDE || ZONE_7_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_3_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_3_HORDE = true;
            ZONE_3_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_3_HORDE:
            if (ZONE_1_ALLIANCE || ZONE_4_ALLIANCE || ZONE_6_ALLIANCE || ZONE_7_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_3_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_3_HORDE = false;
            ZONE_3_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_4_ALLIANCE:
            if (ZONE_1_HORDE || ZONE_2_HORDE || ZONE_3_HORDE || ZONE_5_HORDE || ZONE_7_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_4_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_4_HORDE = true;
            ZONE_4_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_4_HORDE:
            if (ZONE_1_ALLIANCE || ZONE_2_ALLIANCE || ZONE_3_ALLIANCE || ZONE_5_ALLIANCE || ZONE_7_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_4_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_4_HORDE = false;
            ZONE_4_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_5_ALLIANCE:
            if (ZONE_2_HORDE || ZONE_4_HORDE || ZONE_7_HORDE || ZONE_8_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_5_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_5_HORDE = true;
            ZONE_5_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_5_HORDE:
            if (ZONE_2_ALLIANCE || ZONE_4_ALLIANCE || ZONE_7_ALLIANCE || ZONE_8_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_5_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_5_HORDE = false;
            ZONE_5_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_6_ALLIANCE:
            if (ZONE_3_HORDE || ZONE_7_HORDE || ZONE_9_HORDE || ZONE_10_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_6_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_6_HORDE = true;
            ZONE_6_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_6_HORDE:
            if (ZONE_3_ALLIANCE || ZONE_7_ALLIANCE || ZONE_9_ALLIANCE || ZONE_10_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_6_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_6_HORDE = false;
            ZONE_6_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_7_ALLIANCE:
            if (ZONE_3_HORDE || ZONE_4_HORDE || ZONE_5_HORDE || ZONE_6_HORDE || ZONE_8_HORDE || ZONE_10_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_7_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_7_HORDE = true;
            ZONE_7_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_7_HORDE:
            if (ZONE_3_ALLIANCE || ZONE_4_ALLIANCE || ZONE_5_ALLIANCE || ZONE_6_ALLIANCE || ZONE_8_ALLIANCE || ZONE_10_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_7_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_7_HORDE = false;
            ZONE_7_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_8_ALLIANCE:
            if (ZONE_5_HORDE || ZONE_7_HORDE || ZONE_10_HORDE || ZONE_11_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_8_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_8_HORDE = true;
            ZONE_8_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_8_HORDE:
            if (ZONE_5_ALLIANCE || ZONE_7_ALLIANCE || ZONE_10_ALLIANCE || ZONE_11_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_8_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_8_HORDE = false;
            ZONE_8_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_9_ALLIANCE:
            if (ZONE_6_HORDE || ZONE_10_HORDE || ZONE_14_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_9_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_9_HORDE = true;
            ZONE_9_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_9_HORDE:
            if (ZONE_6_ALLIANCE || ZONE_10_ALLIANCE || ZONE_14_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_9_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_9_HORDE = false;
            ZONE_9_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_10_ALLIANCE:
            if (ZONE_6_HORDE || ZONE_7_HORDE || ZONE_8_HORDE || ZONE_9_HORDE || ZONE_11_HORDE || ZONE_12_HORDE || ZONE_13_HORDE || ZONE_14_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_10_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_10_HORDE = true;
            ZONE_10_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_10_HORDE:
            if (ZONE_6_ALLIANCE || ZONE_7_ALLIANCE || ZONE_8_ALLIANCE || ZONE_9_ALLIANCE || ZONE_11_ALLIANCE || ZONE_12_ALLIANCE || ZONE_13_ALLIANCE || ZONE_14_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_10_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_10_HORDE = false;
            ZONE_10_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_11_ALLIANCE:
            if (ZONE_8_HORDE || ZONE_10_HORDE || ZONE_12_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_11_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_11_HORDE = true;
            ZONE_11_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_11_HORDE:
            if (ZONE_8_ALLIANCE || ZONE_10_ALLIANCE || ZONE_12_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_11_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_11_HORDE = false;
            ZONE_11_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_12_ALLIANCE:
            if (ZONE_10_HORDE || ZONE_11_HORDE || ZONE_13_HORDE || ZONE_17_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_12_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_12_HORDE = true;
            ZONE_12_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_12_HORDE:
            if (ZONE_10_ALLIANCE || ZONE_11_ALLIANCE || ZONE_13_ALLIANCE || ZONE_17_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_12_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_12_HORDE = false;
            ZONE_12_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_13_ALLIANCE:
            if (ZONE_10_HORDE || ZONE_12_HORDE || ZONE_14_HORDE || ZONE_15_HORDE || ZONE_16_HORDE || ZONE_17_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_13_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_13_HORDE = true;
            ZONE_13_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_13_HORDE:
            if (ZONE_10_ALLIANCE || ZONE_12_ALLIANCE || ZONE_14_ALLIANCE || ZONE_15_ALLIANCE || ZONE_16_ALLIANCE || ZONE_17_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_13_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_13_HORDE = false;
            ZONE_13_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_14_ALLIANCE:
            if (ZONE_9_HORDE || ZONE_10_HORDE || ZONE_13_HORDE || ZONE_15_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_14_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_14_HORDE = true;
            ZONE_14_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_14_HORDE:
            if (ZONE_9_ALLIANCE || ZONE_10_ALLIANCE || ZONE_13_ALLIANCE || ZONE_15_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_14_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_14_HORDE = false;
            ZONE_14_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_15_ALLIANCE:
            if (ZONE_13_HORDE || ZONE_14_HORDE || ZONE_16_HORDE || ZONE_19_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_15_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_15_HORDE = true;
            ZONE_15_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_15_HORDE:
            if (ZONE_13_ALLIANCE || ZONE_14_ALLIANCE || ZONE_16_ALLIANCE || ZONE_19_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_15_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_15_HORDE = false;
            ZONE_15_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_16_ALLIANCE:
            if (ZONE_13_HORDE || ZONE_15_HORDE || ZONE_17_HORDE || ZONE_18_HORDE || ZONE_19_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_16_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_16_HORDE = true;
            ZONE_16_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_16_HORDE:
            if (ZONE_13_ALLIANCE || ZONE_15_ALLIANCE || ZONE_17_ALLIANCE || ZONE_18_ALLIANCE || ZONE_19_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_16_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_16_HORDE = false;
            ZONE_16_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_17_ALLIANCE:
            if (ZONE_12_HORDE || ZONE_13_HORDE || ZONE_16_HORDE || ZONE_18_HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_17_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_17_HORDE = true;
            ZONE_17_ALLIANCE = false;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_17_HORDE:
            if (ZONE_12_ALLIANCE || ZONE_13_ALLIANCE || ZONE_16_ALLIANCE || ZONE_18_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_17_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_17_HORDE = false;
            ZONE_17_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_18_ALLIANCE:
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_18_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_18_HORDE = true;
            ZONE_18_ALLIANCE = false;
            pGO->Delete();
            break;
        case GO_EVENT_ZONE_18_HORDE:
            if (ZONE_16_ALLIANCE || ZONE_17_ALLIANCE || ZONE_19_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_18_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_18_HORDE = false;
            ZONE_18_ALLIANCE = true;
            pGO->Delete();}
            break;
        case GO_EVENT_ZONE_19_ALLIANCE:
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_19_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_19_HORDE = true;
            ZONE_19_ALLIANCE = false;
            pGO->Delete();
            break;
        case GO_EVENT_ZONE_19_HORDE:
            if (ZONE_15_ALLIANCE || ZONE_16_ALLIANCE || ZONE_18_ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_19_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_19_HORDE = false;
            ZONE_19_ALLIANCE = true;
            pGO->Delete();}
            break;
            
        case GO_EVENT_ZONE_FINAL_ALLIANCE:
            if (pPlayer->GetTeam() ==  HORDE)
            {
                if (ZONE_1_HORDE || ZONE_2_HORDE)
                {
                GardienEntry = NPC_GARDIEN_HORDE;
                pPlayer->SummonGameObject(GO_EVENT_ZONE_FINAL_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
                ZONE_FINAL_HORDE = true;
                ZONE_END = true;
                pGO->Delete();
                }
            }
            break;
        case GO_EVENT_ZONE_FINAL_HORDE:
            if (pPlayer->GetTeam() ==  ALLIANCE)
            {
                if (ZONE_18_ALLIANCE || ZONE_19_ALLIANCE)
                {
                GardienEntry = NPC_GARDIEN_ALLIANCE;
                pPlayer->SummonGameObject(GO_EVENT_ZONE_FINAL_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
                ZONE_FINAL_ALLIANCE = true;
                ZONE_END = true;
                pGO->Delete();
                }
            }
            break;
            
            
            
        case GO_EVENT_ZONE_1_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_2_HORDE || ZONE_3_HORDE || ZONE_4_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_1_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_1_HORDE = true;
            pGO->Delete();
            }
            if (pPlayer->GetTeam() ==  ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_1_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_1_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_2_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_1_HORDE || ZONE_4_HORDE || ZONE_5_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_2_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_2_HORDE = true;
            pGO->Delete();
            }
            if (pPlayer->GetTeam() ==  ALLIANCE)
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_2_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_2_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_3_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_1_HORDE || ZONE_4_HORDE || ZONE_6_HORDE || ZONE_7_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_3_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_3_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_1_ALLIANCE || ZONE_4_ALLIANCE || ZONE_6_ALLIANCE || ZONE_7_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_3_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_3_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_4_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_1_HORDE || ZONE_2_HORDE || ZONE_3_HORDE || ZONE_5_HORDE || ZONE_7_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_4_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_4_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_1_ALLIANCE || ZONE_2_ALLIANCE || ZONE_3_ALLIANCE || ZONE_5_ALLIANCE || ZONE_7_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_4_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_4_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_5_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_2_HORDE || ZONE_4_HORDE || ZONE_7_HORDE || ZONE_8_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_5_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_5_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_2_ALLIANCE || ZONE_4_ALLIANCE || ZONE_7_ALLIANCE || ZONE_8_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_5_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_5_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_6_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_3_HORDE || ZONE_7_HORDE || ZONE_9_HORDE || ZONE_10_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_6_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_6_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_3_ALLIANCE || ZONE_7_ALLIANCE || ZONE_9_ALLIANCE || ZONE_10_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_6_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_6_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_7_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_3_HORDE || ZONE_4_HORDE || ZONE_5_HORDE || ZONE_6_HORDE || ZONE_8_HORDE || ZONE_10_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_7_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_7_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_3_ALLIANCE || ZONE_4_ALLIANCE || ZONE_5_ALLIANCE || ZONE_6_ALLIANCE || ZONE_8_ALLIANCE || ZONE_10_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_7_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_7_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_8_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_5_HORDE || ZONE_7_HORDE || ZONE_10_HORDE || ZONE_11_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_8_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_8_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_5_ALLIANCE || ZONE_7_ALLIANCE || ZONE_10_ALLIANCE || ZONE_11_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_8_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_8_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_9_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_6_HORDE || ZONE_10_HORDE || ZONE_14_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_9_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_9_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_6_ALLIANCE || ZONE_10_ALLIANCE || ZONE_14_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_9_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_9_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_10_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_6_HORDE || ZONE_7_HORDE || ZONE_8_HORDE || ZONE_9_HORDE || ZONE_11_HORDE || ZONE_12_HORDE || ZONE_13_HORDE || ZONE_14_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_10_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_10_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_6_ALLIANCE || ZONE_7_ALLIANCE || ZONE_8_ALLIANCE || ZONE_9_ALLIANCE || ZONE_11_ALLIANCE || ZONE_12_ALLIANCE || ZONE_13_ALLIANCE || ZONE_14_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_10_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_10_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_11_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_8_HORDE || ZONE_10_HORDE || ZONE_12_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_11_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_11_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_8_ALLIANCE || ZONE_10_ALLIANCE || ZONE_12_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_11_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_11_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_12_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_10_HORDE || ZONE_11_HORDE || ZONE_13_HORDE || ZONE_17_HORDE))
            { 
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_12_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_12_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_10_ALLIANCE || ZONE_11_ALLIANCE || ZONE_13_ALLIANCE || ZONE_17_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_12_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_12_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_13_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_10_HORDE || ZONE_12_HORDE || ZONE_14_HORDE || ZONE_15_HORDE || ZONE_16_HORDE || ZONE_17_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_13_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_13_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_10_ALLIANCE || ZONE_12_ALLIANCE || ZONE_14_ALLIANCE || ZONE_15_ALLIANCE || ZONE_16_ALLIANCE || ZONE_17_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_13_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_13_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_14_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_9_HORDE || ZONE_10_HORDE || ZONE_13_HORDE || ZONE_15_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_14_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_14_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_9_ALLIANCE || ZONE_10_ALLIANCE || ZONE_13_ALLIANCE || ZONE_15_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_14_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_14_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_15_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_13_HORDE || ZONE_14_HORDE || ZONE_16_HORDE || ZONE_19_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_15_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_15_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_13_ALLIANCE || ZONE_14_ALLIANCE || ZONE_16_ALLIANCE || ZONE_19_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_15_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_15_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_16_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_13_HORDE || ZONE_15_HORDE || ZONE_17_HORDE || ZONE_18_HORDE || ZONE_19_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_16_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_16_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_13_ALLIANCE || ZONE_15_ALLIANCE || ZONE_17_ALLIANCE || ZONE_18_ALLIANCE || ZONE_19_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_16_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_16_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_17_NEUTRE:
            if ((pPlayer->GetTeam() ==  HORDE) && (ZONE_12_HORDE || ZONE_13_HORDE || ZONE_16_HORDE || ZONE_18_HORDE))
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_17_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_17_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_12_ALLIANCE || ZONE_13_ALLIANCE || ZONE_16_ALLIANCE || ZONE_18_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_17_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_17_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_18_NEUTRE:
            if (pPlayer->GetTeam() ==  HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_18_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_18_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_16_ALLIANCE || ZONE_17_ALLIANCE || ZONE_19_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_18_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_18_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
        case GO_EVENT_ZONE_19_NEUTRE:
            if (pPlayer->GetTeam() ==  HORDE)
            {
            GardienEntry = NPC_GARDIEN_HORDE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_19_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_19_HORDE = true;
            pGO->Delete();
            }
            if ((pPlayer->GetTeam() ==  ALLIANCE) && (ZONE_15_ALLIANCE || ZONE_16_ALLIANCE || ZONE_18_ALLIANCE))
            {
            GardienEntry = NPC_GARDIEN_ALLIANCE;
            pPlayer->SummonGameObject(GO_EVENT_ZONE_19_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN, 0);
            ZONE_19_ALLIANCE = true;
            pGO->Delete();
            }
            break;
            
            
            
            
        case GO_EVENT_ZONE_RESET:
            if (pPlayer->GetSession()->GetSecurity() == 3)
                {
                    ZONE_1_ALLIANCE = false;
                    ZONE_1_HORDE = false;
                    ZONE_2_ALLIANCE = false;
                    ZONE_2_HORDE = false;
                    ZONE_3_ALLIANCE = false;
                    ZONE_3_HORDE = false;
                    ZONE_4_ALLIANCE = false;
                    ZONE_4_HORDE = false;
                    ZONE_5_ALLIANCE = false;
                    ZONE_5_HORDE = false;
                    ZONE_6_ALLIANCE = false;
                    ZONE_6_HORDE = false;
                    ZONE_7_ALLIANCE = false;
                    ZONE_7_HORDE = false;
                    ZONE_8_ALLIANCE = false;
                    ZONE_8_HORDE = false;
                    ZONE_9_ALLIANCE = false;
                    ZONE_9_HORDE = false;
                    ZONE_10_ALLIANCE = false;
                    ZONE_10_HORDE = false;
                    ZONE_11_ALLIANCE = false;
                    ZONE_11_HORDE = false;
                    ZONE_12_ALLIANCE = false;
                    ZONE_12_HORDE = false;
                    ZONE_13_ALLIANCE = false;
                    ZONE_13_HORDE = false;
                    ZONE_14_ALLIANCE = false;
                    ZONE_14_HORDE = false;
                    ZONE_15_ALLIANCE = false;
                    ZONE_15_HORDE = false;
                    ZONE_16_ALLIANCE = false;
                    ZONE_16_HORDE = false;
                    ZONE_17_ALLIANCE = false;
                    ZONE_17_HORDE = false;
                    ZONE_18_ALLIANCE = false;
                    ZONE_18_HORDE = false;
                    ZONE_19_ALLIANCE = false;
                    ZONE_19_HORDE = false;
                    ZONE_FINAL_ALLIANCE = false;
                    ZONE_FINAL_HORDE = false;
                    ZONE_END = false;
                }
            break;
    }

    if (GardienEntry)
        pPlayer->SummonCreature(GardienEntry, fX2, fY2, fZ2, pGO->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0);
    switch (GardienEntry)
    {
    case NPC_GARDIEN_ALLIANCE:
            pPlayer->SummonCreature(NPC_TRIGGER_ENTRY_ALLIANCE, fX1, fY1, fZ1, pGO->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0);
            break;
        
    case NPC_GARDIEN_HORDE:
            pPlayer->SummonCreature(NPC_TRIGGER_ENTRY_HORDE, fX1, fY1, fZ1, pGO->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0);
            break;
    }
    
    return false;

}
};

class mob_zone_gardian : public CreatureScript
{
public:
    mob_zone_gardian() : CreatureScript("mob_zone_gardian") { }
struct  mob_zone_gardianAI : public ScriptedAI
{
    mob_zone_gardianAI(Creature *c) : ScriptedAI(c){}

    uint32 event_zone_protection_timer;
    Creature* cTrigger;
    
    bool IsSpawn;
    
    void Reset()
    {
        IsSpawn = false;
        event_zone_protection_timer = 6000;
        cTrigger = NULL;
    }
    
    void UpdateAI(const uint32 diff)
    {
        if (!IsSpawn)
        {
            if (NPC_GARDIEN_ALLIANCE == me->GetEntry())
                cTrigger = me->FindNearestCreature(NPC_TRIGGER_ENTRY_ALLIANCE, 20);
            if (NPC_GARDIEN_HORDE == me->GetEntry())
                cTrigger = me->FindNearestCreature(NPC_TRIGGER_ENTRY_HORDE, 20);

            if (cTrigger)
            {
                cTrigger->SetReactState(REACT_PASSIVE);
                cTrigger->SetVisible(false);
                IsSpawn = true;
            }
        }
            
        if (event_zone_protection_timer < diff)
        {
            event_zone_protection_timer = 6000;
                if (me->isAlive())
                    if (cTrigger)
                        cTrigger->CastSpell(cTrigger, SPELL_EVENT_ZONE_PROTECTION, true);
        }
        else event_zone_protection_timer -= diff;
        
        DoMeleeAttackIfReady();
    }
    
    void JustDied(Unit* Killer)
    {
        cTrigger->ForcedDespawn();
    }
};

CreatureAI* GetAI(Creature* pCreature)
{
    return new mob_zone_gardianAI (pCreature);
};
};

void AddSC_scripts_zone_event()
{
    new go_event_banner();
new mob_zone_gardian();
}
