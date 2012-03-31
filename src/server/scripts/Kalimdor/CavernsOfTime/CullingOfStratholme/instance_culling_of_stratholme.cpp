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
#include "culling_of_stratholme.h"

#define MAX_ENCOUNTER 5

/* Culling of Stratholme encounters:
0 - Meathook
1 - Salramm the Fleshcrafter
2 - Chrono-Lord Epoch 
3 - Mal'Ganis 
4 - Infinite Corruptor (Heroic only)
*/

/*
A faire:
 - Saut du dialogue entre Arthas et Uther quand le joueur à déjà terminé l'instance auparavant (se baser sur le statut de la quête 13151).
 - Divers dialogues entre PNJs (auberge, caisse pestiférée découverte, avant apparition de Mal'ganis).
*/

struct GroupConfig
{
    uint8 id;
    uint32 entry;
    float x;
    float y;
    float z;
    float o;
    float radius;
    uint8 maxSpawns;
};

const Position ChromieLocation = {1764.7578, 1247.1876, 138.3800, 2.0852};
const Position ArthasLocation = {1766.5721, 1266.2830, 138.5109, 4.8395};
const Position BossWaypointLocation = {2194.110, 1332.00, 130.00, 0};

enum Texts
{
    TEXT_CHROMIE_1                             = -200000,
    TEXT_CHROMIE_2                             = -200001,
};

enum NPCs
{
    NPC_ZOMBIE                                 = 27737,
    NPC_GHOUL                                  = 28249,
    NPC_NECROMANCER                            = 28200,
    NPC_STALKER                                = 28199,
    NPC_FIEND                                  = 27734,
    NPC_GOLEM                                  = 28201,
    NPC_EGHOUL                                 = 27729,
    NPC_CONSTRUCT                              = 27736,
    NPC_ACOLYTE                                = 27731
};

static float WavesLocations[ENCOUNTER_WAVES_NUMBER][ENCOUNTER_WAVES_MAX_SPAWNS][5]=
{
    {
        {NPC_ZOMBIE, 2164.698975, 1255.392944, 135.040878, 0.490202},
        {NPC_ZOMBIE, 2183.501465, 1263.079102, 134.859055, 3.169981},
        {NPC_GHOUL, 2177.512939, 1247.313843, 135.846695, 1.696574},
        {NPC_GHOUL, 2171.991943, 1246.615845, 135.745026, 1.696574},
        {0, 0, 0, 0, 0}
    },
    {
        {NPC_GHOUL, 2254.434326, 1163.427612, 138.055038, 2.077358},
        {NPC_GHOUL, 2254.703613, 1158.867798, 138.212234, 2.345532},
        {NPC_GHOUL, 2257.615723, 1162.310913, 138.091202, 2.077358},
        {NPC_NECROMANCER, 2258.258057, 1157.250732, 138.272873, 2.387766},
        {0, 0, 0, 0, 0}
    },
    {
        {NPC_STALKER, 2348.120117, 1202.302490, 130.491104, 4.698538},
        {NPC_GHOUL, 2352.863525, 1207.819092, 130.424271, 4.949865},
        {NPC_GHOUL, 2343.593750, 1207.915039, 130.781311, 4.321547},
        {NPC_NECROMANCER, 2348.257324, 1212.202515, 130.670135, 4.450352},
        {0, 0, 0, 0, 0}
    },
    {
        {NPC_STALKER, 2139.825195, 1356.277100, 132.199615, 5.820131},
        {NPC_GHOUL, 2137.073486, 1362.464844, 132.271637, 5.820131},
        {NPC_GHOUL, 2134.075684, 1354.148071, 131.885864, 5.820131},
        {NPC_NECROMANCER, 2133.302246, 1358.907837, 132.037689, 5.820131},
        {0, 0, 0, 0, 0}
    },
    {
        {NPC_MEATHOOK, 2232.19, 1331.933, 126.662, 3.15},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
    {
        {NPC_NECROMANCER, 2264.013428, 1174.055908, 138.093094, 2.860481},
        {NPC_GHOUL, 2264.207764, 1170.892700, 138.034973, 2.860481},
        {NPC_GHOUL, 2266.948975, 1176.898926, 137.976929, 2.860481},
        {NPC_STALKER, 2269.215576, 1170.109253, 137.742691, 2.860481},
        {NPC_FIEND, 2273.106689, 1176.101074, 137.880508, 2.860481}
    },
    {
        {NPC_GOLEM, 2349.701660, 1188.436646, 130.428864, 3.908642},
        {NPC_GHOUL, 2349.909180, 1194.582642, 130.417816, 3.577001},
        {NPC_EGHOUL, 2354.662598, 1185.692017, 130.552032, 3.577001},
        {NPC_EGHOUL, 2354.716797, 1191.614380, 130.539810, 3.577001},
        {0, 0, 0, 0, 0}
    },
    {
        {NPC_CONSTRUCT, 2145.212891, 1355.288086, 132.288773, 6.004838},
        {NPC_NECROMANCER, 2137.078613, 1357.612671, 132.173340, 6.004838},
        {NPC_EGHOUL, 2139.402100, 1352.541626, 132.127518, 5.812850},
        {NPC_EGHOUL, 2142.408447, 1360.760620, 132.321564, 5.812850},
        {0, 0, 0, 0, 0}
    },
    {
        {NPC_GHOUL, 2172.686279, 1259.618164, 134.391754, 1.865499},
        {NPC_FIEND, 2177.649170, 1256.061157, 135.096512, 1.849572},
        {NPC_CONSTRUCT, 2170.782959, 1253.594849, 134.973022, 1.849572},
        {NPC_NECROMANCER, 2175.595703, 1249.041992, 135.603531, 1.849572},
        {0, 0, 0, 0, 0}
    },
    {
        {NPC_SALRAMM, 2232.19, 1331.933, 126.662, 3.15},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    },
};

GroupConfig UndeadsGroups[ENCOUNTER_UNDEADS_MAX_GROUPS] =
{
  //|groupID |entry         |x           |y           |z          |o        |radius |maxSpawns |
    {1,       NPC_ZOMBIE,    2226.281250, 1190.027100, 135.714951, 0,        15,     6         },
    {2,       NPC_ZOMBIE,    2331.215820, 1178.376831, 131.654419, 0,        8,      5         },
    //{3,       NPC_ZOMBIE,    2226.146240, 1188.637451, 135.703629, 0,        6,      4         },
    //{3,       NPC_ACOLYTE,   2226.146240, 1188.637451, 135.703629, 0,        6,      4         },
    {4,       NPC_ZOMBIE,    2168.606934, 1271.700317, 133.136124, 0,        10,     6         },
    {4,       NPC_ZOMBIE,    2186.810547, 1327.187866, 129.951279, 0,        12,     12        },
    {6,       NPC_ZOMBIE,    2226.146240, 1188.637451, 135.703629, 0,        6,      4         },
    {6,       NPC_ZOMBIE,    2331.215820, 1178.376831, 131.654419, 0,        8,      5         },
    {7,       NPC_ZOMBIE,    2168.606934, 1271.700317, 133.136124, 0,        10,     6         },
    //{7,       NPC_ZOMBIE,    2186.810547, 1327.187866, 129.951279, 0,        12,     12        },
    {8,       NPC_ZOMBIE,    2226.146240, 1188.637451, 135.703629, 0,        8,      8         },
    {9,       NPC_ZOMBIE,    2168.606934, 1271.700317, 133.136124, 0,        10,     6         },
    {9,       NPC_ZOMBIE,    2186.810547, 1327.187866, 129.951279, 0,        12,     12        },
    {10,      NPC_ZOMBIE,    2331.215820, 1178.376831, 131.654419, 0,        8,      4         },
    {10,      NPC_ZOMBIE,    2226.146240, 1188.637451, 135.703629, 0,        6,      5         },

    {10,      NPC_ZOMBIE,    2566.458740, 1145.727295, 127.523102, 0,        12,     10        },
    {10,      NPC_EGHOUL,    2566.458740, 1145.727295, 127.523102, 0,        5 ,     1         },
    {10,      NPC_ZOMBIE,    2566.278564, 1180.564453, 126.182137, 0,        12,     8         },
    {10,      NPC_ZOMBIE,    2557.144043, 1218.920044, 125.481125, 0,        7,      7         },
    {10,      NPC_CONSTRUCT, 2557.144043, 1218.920044, 125.481125, 4.932457, 1,      1         },
    {10,      NPC_EGHOUL,    2557.144043, 1218.920044, 125.481125, 0,        5,      1         },
    {10,      NPC_FIEND,     2536.077637, 1269.058960, 126.528076, 0,        5,      1         },
    {10,      NPC_ZOMBIE,    2536.077637, 1269.058960, 126.528076, 0,        10,     7         },
    {10,      NPC_ZOMBIE,    2545.483887, 1242.697998, 125.975662, 0,        10,     10        },
    {10,      NPC_EGHOUL,    2545.483887, 1242.697998, 125.975662, 0,        5,      1         },
    {10,      NPC_ZOMBIE,    2519.446533, 1286.734375, 129.678757, 0,        10,     8         },
    {10,      NPC_ZOMBIE,    2494.198975, 1359.625366, 131.444290, 4.932457, 7,      8         },
    {10,      NPC_CONSTRUCT, 2494.198975, 1359.625366, 131.444290, 0,        1,      1         },
    {10,      NPC_FIEND,     2494.198975, 1359.625366, 131.444290, 0,        5,      1         },
    {10,      NPC_EGHOUL,    2494.198975, 1359.625366, 131.444290, 0,        7,      1         },
    {10,      NPC_ZOMBIE,    2485.456055, 1380.183716, 130.124908, 0,        7,      6         },
    {10,      NPC_ACOLYTE,   2485.456055, 1380.183716, 130.124908, 0,        6,      2         },
    {10,      NPC_ZOMBIE,    2473.233643, 1401.531616, 130.503326, 0,        7,      5         },
    {10,      NPC_EGHOUL,    2473.233643, 1401.531616, 130.503326, 0,        7,      1         },
    {10,      NPC_ZOMBIE,    2456.673828, 1424.482788, 130.873215, 0,        7,      7         },
    {10,      NPC_EGHOUL,    2456.673828, 1424.482788, 130.873215, 0,        7,      1         },
    {10,      NPC_ZOMBIE,    2426.650391, 1422.134399, 130.799606, 0,        10,     8         }
};

class instance_culling_of_stratholme : public InstanceMapScript
{
public:
    instance_culling_of_stratholme() : InstanceMapScript("instance_culling_of_stratholme", 595) { }

    InstanceScript* GetInstanceScript(InstanceMap* pMap) const
    {
        return new instance_culling_of_stratholme_InstanceMapScript(pMap);
    }

    struct instance_culling_of_stratholme_InstanceMapScript : public InstanceScript
    {
        instance_culling_of_stratholme_InstanceMapScript(Map* pMap) : InstanceScript(pMap) {Initialize();};
    
    Player* pPlayer;

    uint64 uiArthas;
    uint64 uiMeathook;
    uint64 uiSalramm;
    uint64 uiEpoch;
    uint64 uiMalGanis;
    uint64 uiInfinite;
    uint64 uiGuardianOfTime;
    uint64 uiChromie1;
    uint64 uiChromie2;

    uint32 uiHeroicTimer;
    uint8 uiWave;
    uint64 uiWaveGUID[ENCOUNTER_WAVES_MAX_SPAWNS];

    uint64 uiShkafGate;
    uint64 uiMalGanisGate1;
    uint64 uiMalGanisGate2;
    uint64 uiExitGate;
        uint64 uiMalGanisChest;

    uint32 m_auiArthas;
    uint32 m_auiEncounter[MAX_ENCOUNTER];
    uint32 m_auiPlaguedGrainCrate;

    std::string str_data;

    void Initialize()
    {
        pPlayer = 0;

        uiArthas = 0;
        uiMeathook = 0;
        uiSalramm = 0;
        uiEpoch = 0;
        uiMalGanis = 0;
        uiInfinite = 0;
        uiGuardianOfTime = 0;
        uiChromie1 = 0;
        uiChromie2 = 0;

        uiHeroicTimer = 1500000;
        uiWave = 0;
        memset(&uiWaveGUID, 0, sizeof(uiWaveGUID));

        uiShkafGate = 0;
        uiMalGanisGate1 = 0;
        uiMalGanisGate2 = 0;
        uiExitGate = 0;

        m_auiArthas = 0;
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
        m_auiPlaguedGrainCrate = 0;
    }
    
    bool IsEncounterInProgress() const
    {
        for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            if (m_auiEncounter[i] == IN_PROGRESS) return true;

        return false;
    }
    
        void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
            case NPC_ARTHAS:
                uiArthas = pCreature->GetGUID();
                break;
            case NPC_MEATHOOK:
                uiMeathook = pCreature->GetGUID();
                break;
            case NPC_SALRAMM:
                uiSalramm = pCreature->GetGUID();
                break;
            case NPC_EPOCH:
                uiEpoch = pCreature->GetGUID();
                break;
            case NPC_MAL_GANIS:
                uiMalGanis = pCreature->GetGUID();
                break;
            case NPC_INFINITE:
                uiInfinite = pCreature->GetGUID();
                break;
            case NPC_GUARDIAN_OF_TIME:
                uiGuardianOfTime = pCreature->GetGUID();
                break;
            case NPC_CHROMIE_1:
                uiChromie1 = pCreature->GetGUID();
                break;
            case NPC_CHROMIE_2:
                uiChromie2 = pCreature->GetGUID();
                break;
        }
    }

        void OnGameObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {
            case GO_SHKAF_GATE:
                uiShkafGate = pGo->GetGUID();
                break;
            case GO_MALGANIS_GATE_1:
                uiMalGanisGate1 = pGo->GetGUID();
                break;
            case GO_MALGANIS_GATE_2:
                uiMalGanisGate2 = pGo->GetGUID();
                break;
            case GO_EXIT_GATE:
                uiExitGate = pGo->GetGUID();
                if (m_auiEncounter[3] == DONE)
                    HandleGameObject(uiExitGate,true);
                break;
                case GO_MALGANIS_CHEST_N:
                case GO_MALGANIS_CHEST_H:
                    uiMalGanisChest = pGo->GetGUID();
                    if (m_auiEncounter[3] == DONE)
                        pGo->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                    break;
        }
    }
    
    void SetData(uint32 type, uint32 data)
    {
        switch(type)
        {
            case DATA_ARTHAS_EVENT:
                m_auiArthas = data;
                break;
            case DATA_MEATHOOK_EVENT:
                m_auiEncounter[0] = data;
                break;
            case DATA_SALRAMM_EVENT:
                m_auiEncounter[1] = data;
                break;
            case DATA_EPOCH_EVENT:
                m_auiEncounter[2] = data;
                break;
            case DATA_MAL_GANIS_EVENT:
                m_auiEncounter[3] = data;

                switch(m_auiEncounter[3])
                {
                    case NOT_STARTED:
                        HandleGameObject(uiMalGanisGate2,true);
                        break;
                    case IN_PROGRESS:
                        HandleGameObject(uiMalGanisGate2,false);
                        break;
                    case DONE:
                        HandleGameObject(uiExitGate, true);
                            if (GameObject *pGo = instance->GetGameObject(uiMalGanisChest))
                                pGo->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                        break;
                }
                break;
            case DATA_INFINITE_EVENT:
                m_auiEncounter[4] = data;
                break;
            case DATA_PLAGUED_GRAIN_CRATE:
                m_auiPlaguedGrainCrate = data;
                break;
        }
        
        if (data == DONE && type != DATA_PLAGUED_GRAIN_CRATE)
            SaveToDB();
    }
    
    uint32 GetData(uint32 type)
    {
        switch(type)
        {
            case DATA_ARTHAS_EVENT:               return m_auiArthas;
            case DATA_MEATHOOK_EVENT:             return m_auiEncounter[0];
            case DATA_SALRAMM_EVENT:              return m_auiEncounter[1];
            case DATA_EPOCH_EVENT:                return m_auiEncounter[2];
            case DATA_MAL_GANIS_EVENT:            return m_auiEncounter[3];
            case DATA_INFINITE_EVENT:             return m_auiEncounter[4];
            case DATA_PLAGUED_GRAIN_CRATE:        return m_auiPlaguedGrainCrate;
        }
        return 0;
    }
    
    uint64 GetData64(uint32 identifier)
    {
        switch(identifier)
        {
            case DATA_ARTHAS:                     return uiArthas;
            case DATA_MEATHOOK:                   return uiMeathook;
            case DATA_SALRAMM:                    return uiSalramm;
            case DATA_EPOCH:                      return uiEpoch;
            case DATA_MAL_GANIS:                  return uiMalGanis;
            case DATA_INFINITE:                   return uiInfinite;
            case DATA_GUARDIAN_OF_TIME:           return uiGuardianOfTime;
            case DATA_SHKAF_GATE:                 return uiShkafGate;
            case DATA_MAL_GANIS_GATE_1:           return uiMalGanisGate1;
            case DATA_MAL_GANIS_GATE_2:           return uiMalGanisGate2;
            case DATA_EXIT_GATE:                  return uiExitGate;
                case DATA_MAL_GANIS_CHEST:            return uiMalGanisChest;
        }
        return 0;
    }

    // Retourne le statut des joueurs de la quête "questId"
    QuestStatus GetQuestStatutForPlayersInInstance(uint32 questId)
    {
        const Map::PlayerList &pList = instance->GetPlayers();

        if (pList.getSize() <= 0)
            return QUEST_STATUS_NONE;

        for (Map::PlayerList::const_iterator i = pList.begin(); i != pList.end(); ++i)
            if (i->getSource()->GetQuestStatus(questId) != QUEST_STATUS_COMPLETE)
                return i->getSource()->GetQuestStatus(questId);

        return QUEST_STATUS_COMPLETE;
    }

    // Affecte le statut "status" de la quête "questId"
    void SetQuestStatutForPlayersInInstance(uint32 questId, QuestStatus status)
    {
        const Map::PlayerList &pList = instance->GetPlayers();

        if (pList.getSize() <= 0)
            return;

        for (Map::PlayerList::const_iterator i = pList.begin(); i != pList.end(); ++i)
            i->getSource()->SetQuestStatus(questId, status);
    }

    bool ArrayIsEmpty(uint64 *input, uint32 size)
    {
        for (uint32 i = 0; i < size; ++i)
            if (input[i] != NULL)
                return false;

        return true;
    }

    void SpawnWaveGroup(uint8 waveID)
    {
        for (uint8 i = 0; i < ENCOUNTER_WAVES_MAX_SPAWNS; ++i)
        {
            if ((uint32)WavesLocations[waveID][i][0] == 0)
                break;

            if (Creature* pTemp = pPlayer->SummonCreature((uint32)WavesLocations[waveID][i][0],WavesLocations[waveID][i][1],WavesLocations[waveID][i][2],WavesLocations[waveID][i][3],WavesLocations[waveID][i][4]))
            {
                uiWaveGUID[i] = pTemp->GetGUID();

                if (waveID == 4 || waveID == 9)
                {
                    pTemp->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                    pTemp->GetMotionMaster()->MovePoint(0, BossWaypointLocation);
                }
            }
        }
    }

    void SpawnZombieGroup(uint8 groupID)
    {
        for (uint8 i = 0; i < ENCOUNTER_UNDEADS_MAX_GROUPS; i++)
        {
            if (UndeadsGroups[i].id == groupID)
            {
                for (uint8 j = 0; j < UndeadsGroups[i].maxSpawns; j++)
                {
                    if (Creature *pZombie = pPlayer->SummonCreature(UndeadsGroups[i].entry, UndeadsGroups[i].x, UndeadsGroups[i].y, UndeadsGroups[i].z, UndeadsGroups[i].o))
                    {
                        Position pos;
                        pZombie->GetRandomNearPosition(pos, UndeadsGroups[i].radius);
                        pos.m_positionZ += 2.0f;   // Pour éviter que les mobs transpercent la map
                        pZombie->GetMotionMaster()->MovePoint(0, pos);
                    }
                }
            }
        }
    }

    void UpdateWaveDies()
    {
        for (uint8 i = 0; i < ENCOUNTER_WAVES_MAX_SPAWNS; i++)
            if (uiWaveGUID[i] != NULL)
                if (Creature *pTemp = instance->GetCreature(uiWaveGUID[i]))
                    if (pTemp->isDead())
                        uiWaveGUID[i] = NULL;

    }

    void UpdateWavesSpawns()
    {
        if (GetData(DATA_SALRAMM_EVENT) == DONE)
            uiWave = 10;

        if (uiWave >= 10)
            return;

        if (ArrayIsEmpty(uiWaveGUID, ENCOUNTER_WAVES_MAX_SPAWNS))
        {
            SpawnWaveGroup(uiWave);   // Spawn du groupe ...
            uiWave++;   // Incrémentation de l'Id du groupe
        }

        UpdateWaveDies();
    }

    void UpdateZombieSpawns()
    {
        static uint8 groupID = uiWave;

        if (uiWave == groupID)
        {
            SpawnZombieGroup(groupID);
            groupID++;
        }
    }

    void Update(uint32 diff)
    {
        // Si personne dans l'instance
        if (!instance->HavePlayers())
            return;

        pPlayer = instance->GetPlayers().begin()->getSource();
        Creature *Chromie1 = instance->GetCreature(uiChromie1);
        Creature *Chromie2 = instance->GetCreature(uiChromie2);
        Creature *Arthas = instance->GetCreature(uiArthas);

        if (!Chromie2)
            Chromie2 = pPlayer->SummonCreature(NPC_CHROMIE_2, ChromieLocation);
        if (!Arthas)
            Arthas = pPlayer->SummonCreature(NPC_ARTHAS, ArthasLocation);

        switch (GetQuestStatutForPlayersInInstance(13149))
        {
        case QUEST_STATUS_NONE:
            DoUpdateWorldState(3479, 0);   // Désctivation du WorldState correspondant aux caisses découvertes
            if (Chromie1)
                Chromie1->SetVisible(true);
            if (Chromie2)
                Chromie2->SetVisible(false);
            break;
        case QUEST_STATUS_INCOMPLETE:
            DoUpdateWorldState(3479, 1);   // Activation du WorldState correspondant aux caisses découvertes
            DoUpdateWorldState(3480, m_auiPlaguedGrainCrate);   // Rafraîchissement du nombre de caisses découvertes
            if (m_auiPlaguedGrainCrate >= 5)
                SetQuestStatutForPlayersInInstance(13149, QUEST_STATUS_COMPLETE);
            break;
        case QUEST_STATUS_COMPLETE:
            DoUpdateWorldState(3479, 0);   // Désctivation du WorldState correspondant aux caisses découvertes
            if (Chromie1)
                Chromie1->SetVisible(false);
            if (Chromie2)
                Chromie2->SetVisible(true);
            break;
        }

        switch (GetQuestStatutForPlayersInInstance(13151))
        {
        case QUEST_STATUS_NONE:
            if (Arthas)
                Arthas->SetVisible(false);
            break;
        case QUEST_STATUS_COMPLETE:
        case QUEST_STATUS_INCOMPLETE:
            if (Arthas)
                Arthas->SetVisible(true);
            if (GetData(DATA_MAL_GANIS_EVENT) == DONE)
                SetQuestStatutForPlayersInInstance(13151, QUEST_STATUS_COMPLETE);
            break;
        }

        if (GetData(DATA_ARTHAS_EVENT) == IN_PROGRESS)
        {
            DoUpdateWorldState(3504, uiWave);   // Activation du WorldState correspondant aux vagues

            UpdateWavesSpawns();   // Rafraîchissement des spawn des groupes de mobs
            UpdateZombieSpawns();

            // SI instance héroïque et l'état du Corrupteur Infini égale à ...
            if (instance->IsHeroic() && GetData(DATA_INFINITE_EVENT) != DONE && GetData(DATA_INFINITE_EVENT) != FAIL)
            {
                uint32 Time = (uint32)ceil((float)uiHeroicTimer / (IN_MILLISECONDS * MINUTE));

                DoUpdateWorldState(3932, 1);    // Activation du WorldState correspondant au temps restant
                DoUpdateWorldState(3931, Time);   // Rafraîchissement du temps restant

                if (uiHeroicTimer <= diff)
                    SetData(DATA_INFINITE_EVENT, FAIL);   // Affectation du statut du Corrupteur Infini à Echoué
                else
                    uiHeroicTimer -= diff;
            }
            else
                DoUpdateWorldState(3932, 0);   // Désactivation du WorldState correspondant au temps restant
        }
        else
        {
            DoUpdateWorldState(3504, 0);   // Désactivation du WorldState correspondant aux vagues

            if (instance->IsHeroic())
                DoUpdateWorldState(3932, 0);   // Désactivation du WorldState correspondant au temps restant
        }
    }
    
    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "C S " << m_auiEncounter[0] << " " << m_auiEncounter[1] << " "
            << m_auiEncounter[2] << " " << m_auiEncounter[3] << " " << m_auiEncounter[4] << " " << uiHeroicTimer;

        str_data = saveStream.str();

        OUT_SAVE_INST_DATA_COMPLETE;
        return str_data;
    }

    void Load(const char* in)
    {
        if (!in)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(in);

        char dataHead1, dataHead2;
        uint16 data0, data1, data2, data3, data4;
        uint32 data5;

        std::istringstream loadStream(in);
        loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3 >> data4 >> data5;

        if (dataHead1 == 'C' && dataHead2 == 'S')
        {
            m_auiEncounter[0] = data0;
            m_auiEncounter[1] = data1;
            m_auiEncounter[2] = data2;
            m_auiEncounter[3] = data3;
            m_auiEncounter[4] = data4;
            uiHeroicTimer = data5;

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (m_auiEncounter[i] == IN_PROGRESS)
                    m_auiEncounter[i] = NOT_STARTED;

        } else OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
    }
};

};


void AddSC_instance_culling_of_stratholme()
{
    new instance_culling_of_stratholme();
}
