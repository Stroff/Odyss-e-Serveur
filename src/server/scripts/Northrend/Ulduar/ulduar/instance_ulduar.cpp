/*
 * Copyright (C) 2008-2010 TrinityCore <http://www.trinitycore.org/>
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
#include "ulduar.h"

class instance_ulduar : public InstanceMapScript
{
public:
    instance_ulduar() : InstanceMapScript("instance_ulduar", 603) { }

    InstanceScript* GetInstanceScript(InstanceMap* pMap) const
    {
        return new instance_ulduar_InstanceMapScript(pMap);
    }

    struct instance_ulduar_InstanceMapScript : public InstanceScript
    {
		instance_ulduar_InstanceMapScript(Map* pMap) : InstanceScript(pMap) {}

        uint32 uiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;
		// 1ere aile
        uint64 uiLeviathanGUID;
        uint64 LeviathanGateGUID;
		uint64 ShieldDoorGUID;
		uint64 LightningDoorGUID;

        uint64 uiIgnisGUID;

        uint64 uiRazorscaleGUID;
        uint64 uiExpCommanderGUID;

        uint64 uiXT002GUID;
		// 2nd aile
        uint64 uiAssemblyGUIDs[3];
		uint64 IronCouncilDoorGUID;
		uint64 ArchivumDoorGUID;
		uint32 data_brundir_stunned; // Achievement cant if stunned

        uint64 uiKologarnGUID;
        uint64 uiRightArmGUID;
        uint64 uiLeftArmGUID;
        uint64 KologarnBridgeGUID;

        uint64 uiAuriayaGUID;
        uint64 uiSentryGUID1;
        uint64 uiSentryGUID2;
        uint64 uiSentryGUID3;
        uint64 uiSentryGUID4;
        uint64 uiFeralDefenderGUID;

        uint64 uiMimironGUID;
		uint64 uiLeviathanMKIIGUID;
        uint64 uiVX001GUID;
        uint64 uiAerialUnitGUID;
        uint64 uiMagneticCoreGUID;
		uint64 MimironTramGUID;
		uint64 MimironElevatorGUID;
		uint64 MimironDoorGUIDs[2];

        uint64 uiAlgalonGUID;
		uint64 uiAlgalonBridgeGUID;
        uint64 uiAlgalonBridgeVisualGUID;
        uint64 uiAlgalonBridgeDoorGUID;
        uint64 uiAlgalonGlobeGUID;
        uint64 uiAlgalonDoor1GUID;
        uint64 uiAlgalonDoor2GUID;
        uint64 uiAlgalonAccessGUID;
		uint32 uiPlayerDeathFlag;
		uint32 uiAlgalonKillCount;
        uint32 uiCountdownTimer;
        uint32 uiAlgalonCountdown;
        // 62 - not ready to engage
        // 61 - ready to engage, not engaged yet
        // < 61 - engaged, timer running
        // 0 - failed

		// 3eme aile
        uint64 uiHodirGUID;

        uint64 uiThorimGUID;
		uint64 ThorimLeverGUID;
		uint64 uiRunicColossusGUID;
        uint64 uiRuneGiantGUID;
		uint64 StoneDoorGUID;
		uint64 RunicDoorGUID;

        uint64 uiFreyaGUID;
		uint64 uiBrightleafGUID;
        uint64 uiIronbranchGUID;
        uint64 uiStonebarkGUID;
		// LUNBERJACKED Achievement
		uint32 uiLunberjackedTimer;
		uint32 uiFreyaAddCount;
		uint32 uiLunberjackedData;
		bool AchievFail;
		// 4eme aile
        uint64 uiVezaxGUID;
		uint64 KeepersGateGUID; // before Vezax

        uint64 uiYoggSaronGUID;
		uint64 uiSaraGUID;
        uint64 uiYoggSaronDoorGUID;
        uint64 uiYoggSaronBrainDoor1GUID;
        uint64 uiYoggSaronBrainDoor2GUID;
        uint64 uiYoggSaronBrainDoor3GUID;
		uint64 uiFreyaImageGUID;
        uint64 uiThorimImageGUID;
        uint64 uiMimironImageGUID;
        uint64 uiHodirImageGUID;

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTER);
			uiLeviathanGUID           = 0;
            LeviathanGateGUID         = 0;
			ShieldDoorGUID            = 0;
			LightningDoorGUID         = 0;
            uiIgnisGUID               = 0;
            uiRazorscaleGUID          = 0;
            uiExpCommanderGUID        = 0;
            uiXT002GUID               = 0;
			IronCouncilDoorGUID       = 0;
			ArchivumDoorGUID          = 0;
            uiKologarnGUID            = 0;
            uiRightArmGUID            = 0;
            uiLeftArmGUID             = 0;
            KologarnBridgeGUID        = 0;
            uiAuriayaGUID             = 0;
            uiFeralDefenderGUID       = 0;
            uiSentryGUID1             = 0;
            uiSentryGUID2             = 0;
            uiSentryGUID3             = 0;
            uiSentryGUID4             = 0;
            uiMimironGUID             = 0;
			uiLeviathanMKIIGUID       = 0;
            uiVX001GUID               = 0;
            uiAerialUnitGUID          = 0;
            uiMagneticCoreGUID        = 0;
			MimironTramGUID           = 0;
			MimironElevatorGUID       = 0;
            uiHodirGUID               = 0;
            uiThorimGUID              = 0;
			ThorimLeverGUID           = 0;
			StoneDoorGUID             = 0;
			RunicDoorGUID             = 0;
		    uiRunicColossusGUID       = 0;
            uiRuneGiantGUID           = 0;
            uiFreyaGUID               = 0;
			uiBrightleafGUID          = 0;
            uiIronbranchGUID          = 0;
            uiStonebarkGUID           = 0;
            uiVezaxGUID               = 0;
			KeepersGateGUID           = 0;
            uiYoggSaronGUID           = 0;
			uiSaraGUID                = 0;
            uiYoggSaronDoorGUID       = 0;
            uiYoggSaronBrainDoor1GUID = 0;
            uiYoggSaronBrainDoor2GUID = 0;
            uiYoggSaronBrainDoor3GUID = 0;
			uiFreyaImageGUID          = 0;
            uiThorimImageGUID         = 0;
            uiMimironImageGUID        = 0;
            uiHodirImageGUID          = 0;
            uiAlgalonGUID             = 0;
			uiAlgalonBridgeGUID       = 0;
            uiAlgalonBridgeVisualGUID = 0;
            uiAlgalonBridgeDoorGUID   = 0;
            uiAlgalonGlobeGUID        = 0;
            uiAlgalonDoor1GUID        = 0;
            uiAlgalonDoor2GUID        = 0;
            uiAlgalonAccessGUID       = 0;
			uiPlayerDeathFlag         = 0;
            uiAlgalonKillCount        = 0;
            uiAlgalonCountdown        = 62;
            uiCountdownTimer          = 1*MINUTE*IN_MILLISECONDS;
			// Achievement LunberJacked
			uiLunberjackedTimer       = 15*IN_MILLISECONDS;
			uiFreyaAddCount           = 0;
			AchievFail                = false;
			uiLunberjackedData        = 0;
			// Achievement cant if stunned
			data_brundir_stunned      = 0;

            memset(uiEncounter, 0, sizeof(uiEncounter));
            memset(uiAssemblyGUIDs, 0, sizeof(uiAssemblyGUIDs));
			memset(MimironDoorGUIDs, 0, sizeof(MimironDoorGUIDs));
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                if (uiEncounter[i] == IN_PROGRESS)
                    return true;
            }

            return false;
        }

        void OnCreatureCreate(Creature* creature)
        {
			Map::PlayerList const &players = instance->GetPlayers();
            uint32 TeamInInstance = 0;

            if (!players.isEmpty())
                if (Player* pPlayer = players.begin()->getSource())
                    TeamInInstance = pPlayer->GetTeam();

            switch(creature->GetEntry())
            {
                case NPC_LEVIATHAN:
                    uiLeviathanGUID = creature->GetGUID();
                    break;
                case NPC_IGNIS:
                    uiIgnisGUID = creature->GetGUID();
                    break;
                case NPC_RAZORSCALE:
                    uiRazorscaleGUID = creature->GetGUID();
                    break;
                case NPC_EXPEDITION_COMMANDER:
                    uiExpCommanderGUID = creature->GetGUID();
                    break;
                case NPC_XT002:
                    uiXT002GUID = creature->GetGUID();
                    break;
                // Assembly of Iron
                case NPC_STEELBREAKER:
                    uiAssemblyGUIDs[0] = creature->GetGUID();
                    break;
                case NPC_MOLGEIM:
                    uiAssemblyGUIDs[1] = creature->GetGUID();
                    break;
                case NPC_BRUNDIR:
                    uiAssemblyGUIDs[2] = creature->GetGUID();
                    break;
                case NPC_KOLOGARN:
                    uiKologarnGUID = creature->GetGUID();
                    break;
                case NPC_RIGHT_ARM:
                    uiRightArmGUID = creature->GetGUID();
                    break;
                case NPC_LEFT_ARM:
                    uiLeftArmGUID = creature->GetGUID();
                    break;
                case NPC_AURIAYA:
                    uiAuriayaGUID = creature->GetGUID();
                    break;
                case NPC_SANCTUM_SENTRY:
                    if (uiSentryGUID1 == 0)
                        uiSentryGUID1 = creature->GetGUID();
                    else if (uiSentryGUID2 == 0)
                        uiSentryGUID2 = creature->GetGUID();
                    else if (uiSentryGUID3 == 0)
                        uiSentryGUID3 = creature->GetGUID();
                    else if (uiSentryGUID4 == 0)
                        uiSentryGUID4 = creature->GetGUID();
                    break;
                case NPC_FERAL_DEFENDER:
                    uiFeralDefenderGUID = creature->GetGUID();
                    break;
                case NPC_MIMIRON:
                    uiMimironGUID = creature->GetGUID();
                    break;
				case NPC_MKII:
					uiLeviathanMKIIGUID = creature->GetGUID();
					break;
				case NPC_VX001:
					uiVX001GUID = creature->GetGUID();
					break;
				case NPC_AERIAL:
					uiAerialUnitGUID = creature->GetGUID();
					break;
				case MAGNETIC_CORE:
					uiMagneticCoreGUID = creature->GetGUID();
					break;
                case NPC_HODIR:
                    uiHodirGUID = creature->GetGUID();
                    break;
                case NPC_THORIM:
					uiThorimGUID = creature->GetGUID();
					break;
				case NPC_RUNIC_COLOSSUS:
					uiRunicColossusGUID = creature->GetGUID();
					break;
                case NPC_RUNE_GIANT:
					uiRuneGiantGUID = creature->GetGUID();
					break;
				case NPC_BRIGHTLEAF:
					uiBrightleafGUID = creature->GetGUID();
					break;
                case NPC_IRONBRANCH:
					uiIronbranchGUID = creature->GetGUID();
					break;
                case NPC_STONEBARK:
					uiStonebarkGUID = creature->GetGUID();
					break;
                case NPC_FREYA:
                    uiFreyaGUID = creature->GetGUID();
                    break;
                case NPC_VEZAX:
                    uiVezaxGUID = creature->GetGUID();
                    break;
                case NPC_YOGGSARON:
                    uiYoggSaronGUID = creature->GetGUID();
                    break;
                case NPC_SARA:
                    uiSaraGUID = creature->GetGUID();
                    break;
                case NPC_ALGALON:
                    uiAlgalonGUID = creature->GetGUID();
					if (uiAlgalonCountdown < 62)
                        creature->setFaction(7);
                    break;
				// Keeper's Images
               case NPC_FREYA_IMAGE:
				   uiFreyaImageGUID = creature->GetGUID();
                   creature->SetVisible(false);
				   break;
               case NPC_THORIM_IMAGE:
				   uiThorimImageGUID = creature->GetGUID();
                   creature->SetVisible(false);
				   break;
			   case NPC_MIMIRON_IMAGE:
				   uiMimironImageGUID = creature->GetGUID();
                   creature->SetVisible(false);
				   break;
               case NPC_HODIR_IMAGE:
				   uiHodirImageGUID = creature->GetGUID();
                   creature->SetVisible(false);
				   break;
            }

        // Hodir: Alliance npcs are spawned by default
        if (TeamInInstance == HORDE)
            switch(creature->GetEntry())
            {
                case 33325: creature->UpdateEntry(32941, HORDE); return;
                case 32901: creature->UpdateEntry(33333, HORDE); return;
                case 33328: creature->UpdateEntry(33332, HORDE); return;
                case 32900: creature->UpdateEntry(32950, HORDE); return;
                case 32893: creature->UpdateEntry(33331, HORDE); return;
                case 33327: creature->UpdateEntry(32946, HORDE); return;
                case 32897: creature->UpdateEntry(32948, HORDE); return;
                case 33326: creature->UpdateEntry(33330, HORDE); return;
                case 32907: creature->UpdateEntry(32908, HORDE); return;
                case 32885: creature->UpdateEntry(32883, HORDE); return;
            }
         }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
            case GO_LEVIATHAN_GATE:
				LeviathanGateGUID = go->GetGUID();
				if (GetBossState(TYPE_LEVIATHAN) == DONE)
					go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
				break;
			case GO_SHIELD_DOOR:
				ShieldDoorGUID = go->GetGUID();
				break;
			case GO_LIGHTNING_DOOR:
				LightningDoorGUID = go->GetGUID();
				break;
			case GO_IRON_COUNCIL_DOOR:
				IronCouncilDoorGUID = go->GetGUID();
				break;
			case GO_ARCHIVUM_DOOR:
				ArchivumDoorGUID = go->GetGUID();
				break;
            case GO_KOLOGARN_BRIDGE:
				KologarnBridgeGUID = go->GetGUID();
				if (GetBossState(TYPE_KOLOGARN) == DONE)
					HandleGameObject(0, false, go);
				break;
			case GO_RUNIC_DOOR:
				RunicDoorGUID = go->GetGUID();
				break;
            case GO_STONE_DOOR:
				StoneDoorGUID = go->GetGUID();
				break;
            case GO_THORIM_LEVER:
				ThorimLeverGUID = go->GetGUID();
				break;
			case GO_MIMIRON_DOOR_1:
				MimironDoorGUIDs[0] = go->GetGUID();
				break;
			case GO_MIMIRON_DOOR_2:
				MimironDoorGUIDs[1] = go->GetGUID();
				break;
			case GO_MIMIRON_DOOR_3:
				MimironDoorGUIDs[2] = go->GetGUID();
				break;
			 case GO_MIMIRON_TRAM:
				 MimironTramGUID = go->GetGUID();
				 break;
			 case GO_MIMIRON_ELEVATOR:
				 MimironElevatorGUID = go->GetGUID();
				 break;
             case GO_KEEPERS_DOOR:
				 KeepersGateGUID = go->GetGUID();
				 go->SetFlag(GAMEOBJECT_FLAGS,GO_FLAG_LOCKED);
				 break;
             case GO_YOGGSARON_DOOR:
				 uiYoggSaronDoorGUID = go->GetGUID();
				 HandleGameObject(NULL, true, go);
				 break;
             case GO_YOGGBRAIN_DOOR_1:
				 uiYoggSaronBrainDoor1GUID = go->GetGUID();
				 HandleGameObject(NULL, false, go);
				 break;
             case GO_YOGGBRAIN_DOOR_2:
				 uiYoggSaronBrainDoor2GUID = go->GetGUID();
				 HandleGameObject(NULL, false, go);
				 break;
             case GO_YOGGBRAIN_DOOR_3:
				 uiYoggSaronBrainDoor3GUID = go->GetGUID();
				 HandleGameObject(NULL, false, go);
				 break;
		     case GO_ALGALON_PLATFORM:
				 HandleGameObject(NULL, false, go);
				 break;
		     case GO_ALGALON_BRIDGE:
				 uiAlgalonBridgeGUID = go->GetGUID();
				 HandleGameObject(NULL, false, go);
				 break;
		     case GO_ALGALON_B_VISUAL:
				 uiAlgalonBridgeVisualGUID = go->GetGUID();
				 HandleGameObject(NULL, false, go);
				 break;
		     case GO_ALGALON_B_DOOR:
				 uiAlgalonBridgeDoorGUID = go->GetGUID();
				 HandleGameObject(NULL, true, go);
				 break;
		     case GO_ALGALON_GLOBE:
				 uiAlgalonGlobeGUID = go->GetGUID();
				 HandleGameObject(NULL, false, go);
				 break;
		     case GO_ALGALON_DOOR_1:
				 uiAlgalonDoor1GUID = go->GetGUID();
				 HandleGameObject(NULL, uiAlgalonCountdown < 62 ? true : false, go);
				 break;
		     case GO_ALGALON_DOOR_2:
				 uiAlgalonDoor2GUID = go->GetGUID();
				 HandleGameObject(NULL, uiAlgalonCountdown < 62 ? true : false, go);
				 break;
		     case GO_ALGALON_ACCESS:
				 uiAlgalonAccessGUID = go->GetGUID();
				 if (uiAlgalonCountdown < 62)
				 {
					 go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                     go->SetGoState(GO_STATE_ACTIVE);
				 }
				 break;

                default: break;
            }
        }

        void OnGameObjectRemove(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_LEVIATHAN_DOOR:
                    AddDoor(go, false);
                    break;
                default:
                    break;
            }
        }

        void ProcessEvent(GameObject* /*go*/, uint32 uiEventId)
        {
            // Flame Leviathan's Tower Event triggers
           Creature* pFlameLeviathan = instance->GetCreature(uiLeviathanGUID);

            if (pFlameLeviathan && pFlameLeviathan->isAlive()) //No leviathan, no event triggering ;)
                switch(uiEventId)
                {
                    case EVENT_TOWER_OF_STORM_DESTROYED:
                        pFlameLeviathan->AI()->DoAction(1);
                        break;
                    case EVENT_TOWER_OF_FROST_DESTROYED:
                        pFlameLeviathan->AI()->DoAction(2);
                        break;
                    case EVENT_TOWER_OF_FLAMES_DESTROYED:
                        pFlameLeviathan->AI()->DoAction(3);
                        break;
                    case EVENT_TOWER_OF_LIFE_DESTROYED:
                        pFlameLeviathan->AI()->DoAction(4);
                        break;
                }
        }

        bool SetBossState(uint32 type, EncounterState state)
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
            case TYPE_LEVIATHAN:
				if (state == IN_PROGRESS)
				{
					HandleGameObject(ShieldDoorGUID, false);
					HandleGameObject(LightningDoorGUID, false);
				}
				else
				{
					HandleGameObject(ShieldDoorGUID, true);
					HandleGameObject(LightningDoorGUID, true);
				}
				break;
            case TYPE_XT002:
            case TYPE_IGNIS:
            case TYPE_RAZORSCALE:
            case TYPE_AURIAYA:
				break;
            case TYPE_ASSEMBLY:
				if (state == IN_PROGRESS)
					HandleGameObject(IronCouncilDoorGUID, false);
				else
				{
					HandleGameObject(IronCouncilDoorGUID, true);
					if (state == DONE)
						HandleGameObject(ArchivumDoorGUID, true);
				}
				break;
            case TYPE_KOLOGARN:
				if (state == DONE)
					HandleGameObject(KologarnBridgeGUID, false);
                break;
            case TYPE_THORIM:
				if (state == IN_PROGRESS)
					if (GameObject* pThorimLever = instance->GetGameObject(ThorimLeverGUID))
						pThorimLever->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_UNK1);
				if (state == DONE)
					CheckKeepersState();
                break;
            case TYPE_HODIR:
            case TYPE_FREYA:
				if (state == DONE)
					CheckKeepersState();
				break;
            case TYPE_MIMIRON:
				if (state == IN_PROGRESS)
				{
					HandleGameObject(MimironDoorGUIDs[0], false);
					HandleGameObject(MimironDoorGUIDs[1], false);
					HandleGameObject(MimironDoorGUIDs[2], false);
				}
				else
				{
					HandleGameObject(MimironDoorGUIDs[0], true);
					HandleGameObject(MimironDoorGUIDs[1], true);
					HandleGameObject(MimironDoorGUIDs[2], true);
					if (state == DONE)
						CheckKeepersState();
				}
				break;
            case TYPE_VEZAX:
				if (state == DONE)
				{
					// Keeper's Images
                    if (Creature* pFreya = instance->GetCreature(uiFreyaImageGUID))
                        pFreya->SetVisible(true);
                    if (Creature* pThorim = instance->GetCreature(uiThorimImageGUID))
                        pThorim->SetVisible(true);
                    if (Creature* pMimiron = instance->GetCreature(uiMimironImageGUID))
                        pMimiron->SetVisible(true);
                    if (Creature* pHodir = instance->GetCreature(uiHodirImageGUID))
                        pHodir->SetVisible(true);
				}
				break;
			case TYPE_YOGGSARON:
				if(state == IN_PROGRESS)
                    HandleGameObject(uiYoggSaronDoorGUID,false);
                else
                    HandleGameObject(uiYoggSaronDoorGUID,true);
                break;
			case TYPE_ALGALON:
				switch (state)
				{
				case SPECIAL:
					if (Creature* algalon = instance->GetCreature(uiAlgalonGUID))
						algalon->setFaction(7);
					HandleGameObject(uiAlgalonDoor1GUID, true);
					HandleGameObject(uiAlgalonDoor2GUID, true);
					uiAlgalonCountdown = 61;
					SaveToDB();
					break;
				case NOT_STARTED:
					HandleGameObject(uiAlgalonGlobeGUID, false);
					HandleGameObject(uiAlgalonBridgeGUID, false);
					HandleGameObject(uiAlgalonBridgeVisualGUID, false);
					HandleGameObject(uiAlgalonBridgeDoorGUID, true);
					break;
				case IN_PROGRESS:
					if (uiAlgalonCountdown > 60)
					{
						uiAlgalonCountdown = 60;
						DoUpdateWorldState(WORLDSTATE_ALGALON_SHOW, 1);
						DoUpdateWorldState(WORLDSTATE_ALGALON_TIME, uiAlgalonCountdown);
						SaveToDB();
					}
					HandleGameObject(uiAlgalonGlobeGUID, true);
					HandleGameObject(uiAlgalonBridgeGUID, true);
					HandleGameObject(uiAlgalonBridgeVisualGUID, true);
					HandleGameObject(uiAlgalonBridgeDoorGUID, false);
					break;
				case DONE:
					// uiAlgalonCountdown = 1;
					// uiCountdownTimer = 0;
					HandleGameObject(uiAlgalonGlobeGUID, false);
					HandleGameObject(uiAlgalonBridgeGUID, false);
					HandleGameObject(uiAlgalonBridgeVisualGUID, false);
					HandleGameObject(uiAlgalonBridgeDoorGUID, true);
					break;
				}
				break;
             }

             return true;
        }

		void CheckKeepersState()
        {
            if (GameObject* pGo = instance->GetGameObject(KeepersGateGUID))
            {
                InstanceScript* pInstance = pGo->GetInstanceScript();
                if (pInstance)
                {
					if (pInstance->GetBossState(TYPE_MIMIRON) == DONE)
						if (pInstance->GetBossState(TYPE_FREYA) == DONE)
							if (pInstance->GetBossState(TYPE_THORIM) == DONE)
								if (pInstance->GetBossState(TYPE_HODIR) == DONE)
									if (instance->GetDifficulty() == RAID_DIFFICULTY_10MAN_NORMAL) // keep lock for raid mode 25
										pGo->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_LOCKED);
                }
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            switch(type)
            {
				case DATA_RUNIC_DOOR:
                    if (RunicDoorGUID)
						if (GameObject* RunicDoor = instance->GetGameObject(RunicDoorGUID))
							RunicDoor->SetGoState(GOState(data));
                break;
                case DATA_STONE_DOOR:
                    if (StoneDoorGUID)
                        if (GameObject* StoneDoor = instance->GetGameObject(StoneDoorGUID))
							StoneDoor->SetGoState(GOState(data));
                break;
				case DATA_CALL_TRAM:
                    if (MimironTramGUID && instance)
                    {
                        // Load Mimiron Tram (unfortunally only server side)
                        instance->LoadGrid(2307.0f, 284.632f);

                        if (data == 0)
                            if (GameObject* MimironTram = instance->GetGameObject(MimironTramGUID))
								MimironTram->SetGoState(GO_STATE_READY);
                        if (data == 1)
							if (GameObject* MimironTram1 = instance->GetGameObject(MimironTramGUID))
								MimironTram1->SetGoState(GO_STATE_ACTIVE);

                        // Send movement update to players
						if (GameObject* MimironTram2 = instance->GetGameObject(MimironTramGUID))
                        if (Map* pMap = MimironTram2->GetMap())
                            if (pMap->IsDungeon())
                            {
                                Map::PlayerList const &PlayerList = pMap->GetPlayers();

                                if (!PlayerList.isEmpty())
                                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                        if (i->getSource())
                                        {
                                            UpdateData data;
                                            WorldPacket pkt;
                                            MimironTram2->BuildValuesUpdateBlockForPlayer(&data, i->getSource());
                                            data.BuildPacket(&pkt);
                                            i->getSource()->GetSession()->SendPacket(&pkt);
                                        }
                            }
                    }
                    break;
                case DATA_MIMIRON_ELEVATOR:
                    if (MimironElevatorGUID)
						if (GameObject* MimironElevator = instance->GetGameObject(MimironElevatorGUID))
							MimironElevator->SetGoState(GOState(data));
                    break;
                case TYPE_COLOSSUS:
                    uiEncounter[TYPE_COLOSSUS] = data;
                    if (data == 2)
                    {
                        if (Creature* pBoss = instance->GetCreature(uiLeviathanGUID))
                            pBoss->AI()->DoAction(10);
                        if (GameObject* pGate = instance->GetGameObject(LeviathanGateGUID))
                            pGate->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                        SaveToDB();
                    }
                    break;
				case EVENT_LUNBERJACKED:
					if (data == DONE)
					{
						if (instance->GetDifficulty() == RAID_DIFFICULTY_10MAN_NORMAL)
							DoCompleteAchievement(ACHIEVEMENT_LUNBERJACKED_10);
						if (instance->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL)
							DoCompleteAchievement(ACHIEVEMENT_LUNBERJACKED_25);
					}
					uiLunberjackedData = data;
					break;
				case FREYA_ADD_COUNT_DEATH:
					if (data == 1)
						SetData(EVENT_LUNBERJACKED, IN_PROGRESS);
					uiFreyaAddCount = data;
					break;
				case EVENT_BRUNDIR_STUNNED:
					data_brundir_stunned = data;
					break;

                default:
                    break;
            }
        }

        uint64 GetData64(uint32 data)
        {
            switch(data)
            {
                case TYPE_LEVIATHAN:            return uiLeviathanGUID;
                case TYPE_IGNIS:                return uiIgnisGUID;
                case TYPE_RAZORSCALE:           return uiRazorscaleGUID;
				case DATA_EXP_COMMANDER:        return uiExpCommanderGUID;
                case TYPE_XT002:                return uiXT002GUID;
                case TYPE_KOLOGARN:             return uiKologarnGUID;
                case DATA_LEFT_ARM:             return uiLeftArmGUID;
                case DATA_RIGHT_ARM:            return uiRightArmGUID;
                case TYPE_AURIAYA:              return uiAuriayaGUID;
                case DATA_SENTRY_1:             return uiSentryGUID1;
                case DATA_SENTRY_2:             return uiSentryGUID2;
                case DATA_SENTRY_3:             return uiSentryGUID3;
                case DATA_SENTRY_4:             return uiSentryGUID4;
                case DATA_FERAL_DEFENDER:       return uiFeralDefenderGUID;
                case TYPE_MIMIRON:              return uiMimironGUID;
				case DATA_LEVIATHAN_MK_II:      return uiLeviathanMKIIGUID;
                case DATA_VX_001:               return uiVX001GUID;
                case DATA_AERIAL_UNIT:          return uiAerialUnitGUID;
                case DATA_MAGNETIC_CORE:        return uiMagneticCoreGUID;
                case TYPE_HODIR:                return uiHodirGUID;
                case TYPE_THORIM:               return uiThorimGUID;
				case DATA_RUNIC_COLOSSUS:       return uiRunicColossusGUID;
                case DATA_RUNE_GIANT:           return uiRuneGiantGUID;
				case DATA_BRIGHTLEAF:           return uiBrightleafGUID;
                case DATA_IRONBRANCH:           return uiIronbranchGUID;
                case DATA_STONEBARK:            return uiStonebarkGUID;
                case TYPE_FREYA:                return uiFreyaGUID;
                case TYPE_VEZAX:                return uiVezaxGUID;
                case TYPE_YOGGSARON:            return uiYoggSaronGUID;
                case TYPE_ALGALON:              return uiAlgalonGUID;
                case DATA_SARA:                 return uiSaraGUID;
                case DATA_BRAIN_DOOR_1:         return uiYoggSaronBrainDoor1GUID;
                case DATA_BRAIN_DOOR_2:         return uiYoggSaronBrainDoor2GUID;
                case DATA_BRAIN_DOOR_3:         return uiYoggSaronBrainDoor3GUID;

                // Assembly of Iron
                case DATA_STEELBREAKER:         return uiAssemblyGUIDs[0];
                case DATA_MOLGEIM:              return uiAssemblyGUIDs[1];
                case DATA_BRUNDIR:              return uiAssemblyGUIDs[2];
            }

            return 0;
        }

        uint32 GetData(uint32 type)
        {
            switch(type)
            {
                case TYPE_COLOSSUS:
                    return uiEncounter[type];
				case EVENT_LUNBERJACKED:
					return uiLunberjackedData;
				case FREYA_ADD_COUNT_DEATH:
					return uiFreyaAddCount;
				case EVENT_BRUNDIR_STUNNED:
					return data_brundir_stunned;
            }

            return 0;
        }

		bool CheckAchievementCriteriaMeet(uint32 criteria_id, Player const* /*source*/, Unit const* /*target = NULL*/, uint32 /*miscvalue1 = 0*/)
        {
            // Yogg-Saron
            switch(criteria_id)
            {
            case ACHIEVEMENT_CRITERIA_THE_ASSASSINATION_OF_KING_LLANE_10:
            case ACHIEVEMENT_CRITERIA_THE_ASSASSINATION_OF_KING_LLANE_25:
                {
                    if(GetBossState(TYPE_YOGGSARON) != IN_PROGRESS)
                        return false;

                    if(Creature* Sara = instance->GetCreature(uiSaraGUID))
                        return (Sara->AI()->GetData(DATA_PORTAL_PHASE) == 0);

                    return false;
                }
            case ACHIEVEMENT_CRITERIA_THE_TORTURED_CHAMPION_10:
            case ACHIEVEMENT_CRITERIA_THE_TORTURED_CHAMPION_25:
                {
                    if(GetBossState(TYPE_YOGGSARON) != IN_PROGRESS)
                        return false;

                    if(Creature* Sara = instance->GetCreature(uiSaraGUID))
                        return (Sara->AI()->GetData(DATA_PORTAL_PHASE) == 2);

                    return false;
                }
            case ACHIEVEMENT_CRITERIA_FORGING_OF_THE_DEMON_SOUL_10:
            case ACHIEVEMENT_CRITERIA_FORGING_OF_THE_DEMON_SOUL_25:
                {
                    if(GetBossState(TYPE_YOGGSARON) != IN_PROGRESS)
                        return false;

                    if(Creature* Sara = instance->GetCreature(uiSaraGUID))
                        return (Sara->AI()->GetData(DATA_PORTAL_PHASE) == 1);

                    return false;
                }
            }
            return false;
        }

		void Update(uint32 diff)
		{
			if (GetData(EVENT_LUNBERJACKED) !=FAIL && GetData(EVENT_LUNBERJACKED) == IN_PROGRESS)
			{
				if (uiLunberjackedTimer <= diff)
				{
					SetData(EVENT_LUNBERJACKED, FAIL);
					AchievFail = true;
				} else uiLunberjackedTimer -= diff;

				if (uiFreyaAddCount >= 3 && !AchievFail)
					SetData(EVENT_LUNBERJACKED, DONE);
			}

			if (uiAlgalonCountdown && uiAlgalonCountdown < 61)
            {
                if (uiCountdownTimer < diff)
                {
                    uiAlgalonCountdown--;

                    if (uiAlgalonCountdown)
                    {
                        DoUpdateWorldState(WORLDSTATE_ALGALON_SHOW, 1);
                        DoUpdateWorldState(WORLDSTATE_ALGALON_TIME, uiAlgalonCountdown);
                    }
                    else
                    {
                        DoUpdateWorldState(WORLDSTATE_ALGALON_SHOW, 0);
                    }
                    SaveToDB();
                    uiCountdownTimer += 1*MINUTE*IN_MILLISECONDS;
                }
                uiCountdownTimer -= diff;
            }
		}

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "U U " << GetBossSaveData() << GetData(TYPE_COLOSSUS);

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char* strIn)
        {
            if (!strIn)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(strIn);

            char dataHead1, dataHead2;

            std::istringstream loadStream(strIn);
            loadStream >> dataHead1 >> dataHead2;

            if (dataHead1 == 'U' && dataHead2 == 'U')
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;

                    if (i == TYPE_COLOSSUS)
                        SetData(i, tmpState);
                    else
                        SetBossState(i, EncounterState(tmpState));
                }
            }

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

// Mimiron Tram
class go_call_tram : public GameObjectScript
{
public:
    go_call_tram() : GameObjectScript("go_call_tram") { }

    bool OnGossipHello(Player* pPlayer, GameObject* go)
    {
        InstanceScript* pInstance = go->GetInstanceScript();

        if (!pInstance)
            return false;

        switch(go->GetEntry())
        {
            case 194914:
            case 194438:
                pInstance->SetData(DATA_CALL_TRAM, 0);
                break;
            case 194912:
            case 194437:
                pInstance->SetData(DATA_CALL_TRAM, 1);
                break;
        }
        return true;
    }
};

void AddSC_instance_ulduar()
{
    new instance_ulduar();
	new go_call_tram();
}
