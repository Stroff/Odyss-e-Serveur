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
#include "pit_of_saron.h"

enum EventsIds
{
    EVENT_INTRO_1                               = 1,
    EVENT_INTRO_2                               = 2,
    EVENT_INTRO_3                               = 3,
    EVENT_INTRO_4                               = 4,
    EVENT_INTRO_5                               = 5,
    EVENT_INTRO_6                               = 6,
    EVENT_INTRO_7                               = 7,
    EVENT_INTRO_8                               = 8,
    EVENT_INTRO_9                               = 9,
    EVENT_INTRO_10                              = 10,
    EVENT_INTRO_11                              = 11,
    EVENT_INTRO_12                              = 12,
    EVENT_INTRO_13                              = 13,
    EVENT_INTRO_14                              = 14,
    EVENT_ICEFALL                               = 15
};

enum Yells
{
    SAY_TYRANNUS_OPENNING_01                    = -1658071,
    SAY_TYRANNUS_OPENNING_02                    = -1658072,
    SAY_TYRANNUS_OPENNING_03                    = -1658073,
    SAY_TYRANNUS_OPENNING_04                    = -1658074,
    SAY_TYRANNUS_OPENNING_05                    = -1658075,

    SAY_SYLVANAS_OPENNING_01                    = -1658076,
    SAY_SYLVANAS_OPENNING_02                    = -1658077,
    SAY_SYLVANAS_OPENNING_03                    = -1658078,
    SAY_SYLVANAS_OPENNING_04                    = -1658079,

    SAY_JAINA_OPENNING_01                       = -1658080,
    SAY_JAINA_OPENNING_02                       = -1658081,
    SAY_JAINA_OPENNING_03                       = -1658082,
    SAY_JAINA_OPENNING_04                       = -1658083,
    SAY_JAINA_OPENNING_05                       = -1658084
};

enum Spells
{
    SPELL_MIGHTY_KICK                           = 69021, //ick's spell
    SPELL_SHADOW_BOLT                           = 69028, //krick's spell
    SPELL_TOXIC_WASTE                           = 69024, //krick's spell
    SPELL_EXPLOSIVE_BARRAGE_KRICK               = 69012, //special spell 1
    SPELL_EXPLOSIVE_BARRAGE_ICK                 = 69263, //special spell 1
    SPELL_POISON_NOVA                           = 68989, //special spell 2
    SPELL_PURSUIT                               = 68987, //special spell 3

    SPELL_EXPLOSIVE_BARRAGE_SUMMON              = 69015,
    SPELL_EXPLODING_ORB                         = 69017, //visual on exploding orb
    SPELL_AUTO_GROW                             = 69020, //grow effect on exploding orb
    SPELL_HASTY_GROW                            = 44851, //need to check growing stacks
    SPELL_EXPLOSIVE_BARRAGE_DAMAGE              = 69019, //damage done by orb while exploding

    SPELL_STRANGULATING                         = 69413, //krick's selfcast in intro
    SPELL_SUICIDE                               = 7,
    SPELL_KRICK_KILL_CREDIT                     = 71308,
    SPELL_NECROMANTIC_POWER                     = 69753,
    SPELL_RAISE_DEAD                            = 69350,
    SPELL_EMPOWERED_BLIZZARD                    = 32192,
    SPELL_BLIZZARD                              = 41482,
    SPELL_SHRIEK_HIGHBORNE                      = 70512,

    SPELL_ICEFALL                               = 69424,
    SPELL_ICEFALL_DAMAGES                       = 69426
};

static const Position blizzardPos[] =
{
    {471.52f, 237.29f, 528.69f, 0.0f},
    {472.44f, 204.61f, 528.70f, 0.0f},
    {457.39f, 223.46f, 528.70f, 0.0f},
    {455.70f, 211.16f, 528.70f, 0.0f}
};

static const Position Tyrannus_move_after_intro = {736.39f, 279.29f, 543.87f, 0.0f};

class instance_pit_of_saron : public InstanceMapScript
{
    public:
        instance_pit_of_saron() : InstanceMapScript(PoSScriptName, 658) { }

        struct instance_pit_of_saron_InstanceScript : public InstanceScript
        {
            instance_pit_of_saron_InstanceScript(Map* map) : InstanceScript(map)
            {
                SetBossNumber(MAX_ENCOUNTER);
                _garfrostGUID = 0;
                _krickGUID = 0;
                _ickGUID = 0;
                _tyrannusGUID = 0;
                _rimefangGUID = 0;
                _jainaOrSylvanas1GUID = 0;
                _jainaOrSylvanas2GUID = 0;
                _leftNecroGUID = 0;
                _rightNecroGUID = 0;
                _teamInInstance = 0;
                _events.ScheduleEvent(EVENT_INTRO_1, 12000);
                _tunnelStarted = false;
            }

            void OnPlayerEnter(Player* player)
            {
                if (!_teamInInstance)
                    _teamInInstance = player->GetTeam();

            }

            void Update(uint32 diff) {

                _events.Update(diff);

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_INTRO_1:
                            if (Creature* tyrannusEvent = ObjectAccessor::GetObjectInMap(_tyrannusEventGUID, instance, (Creature*)NULL))
                                DoScriptText(SAY_TYRANNUS_OPENNING_01, tyrannusEvent);

                             _events.ScheduleEvent(EVENT_INTRO_2, 5000);
                            break;
                        case EVENT_INTRO_2:
                            if (Creature* tyrannusEvent = ObjectAccessor::GetObjectInMap(_tyrannusEventGUID, instance, (Creature*)NULL))
                                DoScriptText(SAY_TYRANNUS_OPENNING_02, tyrannusEvent);

                            _events.ScheduleEvent(EVENT_INTRO_3, 13000);
                            break;
                        case EVENT_INTRO_3:

                            if (Creature* jainaOrSylvanas = ObjectAccessor::GetObjectInMap(_jainaOrSylvanas1GUID, instance, (Creature*)NULL))
                                if (_teamInInstance == ALLIANCE)
                                    DoScriptText(SAY_JAINA_OPENNING_01, jainaOrSylvanas);
                                else
                                    DoScriptText(SAY_SYLVANAS_OPENNING_01, jainaOrSylvanas);

                            _events.ScheduleEvent(EVENT_INTRO_4, 1600);
                            for(std::list<Creature*>::const_iterator it = _championsAttackingLeftNecro.begin();
                            it != _championsAttackingLeftNecro.end(); ++it)
                                if (Creature* leftNecro = ObjectAccessor::GetObjectInMap(_leftNecroGUID, instance, (Creature*)NULL))
                                    (*it)->GetAI()->AttackStart(leftNecro);

                            for(std::list<Creature*>::const_iterator it = _championsAttackingRightNecro.begin();
                            it != _championsAttackingRightNecro.end(); ++it)
                                if (Creature* rightNecro = ObjectAccessor::GetObjectInMap(_rightNecroGUID, instance, (Creature*)NULL))
                                    (*it)->GetAI()->AttackStart(rightNecro);


                            break;

                        case EVENT_INTRO_4:
                            _events.ScheduleEvent(EVENT_INTRO_5, 3600);
                            if (Creature* tyrannusEvent = ObjectAccessor::GetObjectInMap(_tyrannusEventGUID, instance, (Creature*)NULL))
                                DoScriptText(SAY_TYRANNUS_OPENNING_03, tyrannusEvent);
                            break;

                        case EVENT_INTRO_5:
                            _events.ScheduleEvent(EVENT_INTRO_6, 400);

                            for(std::list<Creature*>::const_iterator it = _championsAttackingLeftNecro.begin();
                            it != _championsAttackingLeftNecro.end(); ++it) {
                                (*it)->CastSpell((*it), SPELL_STRANGULATING, false);
                            }

                            for(std::list<Creature*>::const_iterator it = _championsAttackingRightNecro.begin();
                            it != _championsAttackingRightNecro.end(); ++it) {
                                (*it)->CastSpell((*it), SPELL_STRANGULATING, false);
                            }
                            break;

                        case EVENT_INTRO_6:
                            _events.ScheduleEvent(EVENT_INTRO_7, 5500);
                            if (Creature* tyrannusEvent = ObjectAccessor::GetObjectInMap(_tyrannusEventGUID, instance, (Creature*)NULL))
                                DoScriptText(SAY_TYRANNUS_OPENNING_04, tyrannusEvent);
                            break;

                        case EVENT_INTRO_7:
                            if (Creature* tyrannusEvent = ObjectAccessor::GetObjectInMap(_tyrannusEventGUID, instance, (Creature*)NULL))
                                if(!_championsAttackingLeftNecro.empty())
                                    tyrannusEvent->CastSpell((*_championsAttackingLeftNecro.begin()), SPELL_NECROMANTIC_POWER, true);

                            _events.ScheduleEvent(EVENT_INTRO_8, 3500);

                            for(std::list<Creature*>::const_iterator it = _championsAttackingLeftNecro.begin();
                            it != _championsAttackingLeftNecro.end(); ++it) {
                                if (Creature* tyrannusEvent = ObjectAccessor::GetObjectInMap(_tyrannusEventGUID, instance, (Creature*)NULL))
                                    tyrannusEvent->Kill(*it);

                                (*it)->RemoveAurasDueToSpell(SPELL_STRANGULATING);
                            }

                            for(std::list<Creature*>::const_iterator it = _championsAttackingRightNecro.begin();
                            it != _championsAttackingRightNecro.end(); ++it) {
                                if (Creature* tyrannusEvent = ObjectAccessor::GetObjectInMap(_tyrannusEventGUID, instance, (Creature*)NULL))
                                    tyrannusEvent->Kill(*it);

                                (*it)->RemoveAurasDueToSpell(SPELL_STRANGULATING);
                            }

                            if (Creature* jainaOrSylvanas = ObjectAccessor::GetObjectInMap(_jainaOrSylvanas1GUID, instance, (Creature*)NULL))
                                if (_teamInInstance == ALLIANCE)
                                    DoScriptText(SAY_JAINA_OPENNING_02, jainaOrSylvanas);
                                else
                                    DoScriptText(SAY_SYLVANAS_OPENNING_02, jainaOrSylvanas);
                            break;
                        case EVENT_INTRO_8:
                            _events.ScheduleEvent(EVENT_INTRO_9, 1800);
                            for(std::list<Creature*>::const_iterator it = _championsAttackingLeftNecro.begin();
                            it != _championsAttackingLeftNecro.end(); ++it) {
                                (*it)->CastSpell((*it), SPELL_RAISE_DEAD, false);
                            }

                            for(std::list<Creature*>::const_iterator it = _championsAttackingRightNecro.begin();
                            it != _championsAttackingRightNecro.end(); ++it) {
                                (*it)->CastSpell((*it), SPELL_RAISE_DEAD, false);
                            }

                            if (Creature* tyrannusEvent = ObjectAccessor::GetObjectInMap(_tyrannusEventGUID, instance, (Creature*)NULL))
                                DoScriptText(SAY_TYRANNUS_OPENNING_05, tyrannusEvent);

                            break;
                        case EVENT_INTRO_9:
                            _events.ScheduleEvent(EVENT_INTRO_10, 1000);
                            for(std::list<Creature*>::const_iterator it = _championsAttackingLeftNecro.begin();
                            it != _championsAttackingLeftNecro.end(); ++it) {
                                (*it)->UpdateEntry(NPC_SKELETAL_SLAVE);
                                (*it)->SetMaxHealth(4000);
                                (*it)->SetHealth((*it)->GetMaxHealth());
                                (*it)->setDeathState(ALIVE);
                                (*it)->SetReactState(REACT_AGGRESSIVE);
                            }

                            for(std::list<Creature*>::const_iterator it = _championsAttackingRightNecro.begin();
                            it != _championsAttackingRightNecro.end(); ++it) {
                                (*it)->UpdateEntry(NPC_SKELETAL_SLAVE);
                                (*it)->SetHealth(4000);
                                (*it)->setDeathState(ALIVE);
                                (*it)->SetReactState(REACT_AGGRESSIVE);
                            }

                            if (Creature* leftNecro = ObjectAccessor::GetObjectInMap(_leftNecroGUID, instance, (Creature*)NULL))
                                leftNecro->SetReactState(REACT_AGGRESSIVE);

                            if (Creature* rightNecro = ObjectAccessor::GetObjectInMap(_rightNecroGUID, instance, (Creature*)NULL))
                                rightNecro->SetReactState(REACT_AGGRESSIVE);

                            if (Creature* tyrannusEvent = ObjectAccessor::GetObjectInMap(_tyrannusEventGUID, instance, (Creature*)NULL)) {
                                tyrannusEvent->SetSpeed(MOVE_FLIGHT, 3.5f, true);
                                tyrannusEvent->GetMotionMaster()->MovePoint(0, Tyrannus_move_after_intro);
                            }
                            break;
                        case EVENT_INTRO_10:
                            _events.ScheduleEvent(EVENT_INTRO_11, 100);
                            if (Creature* jainaOrSylvanas = ObjectAccessor::GetObjectInMap(_jainaOrSylvanas1GUID, instance, (Creature*)NULL)) {
                                for(std::list<Creature*>::const_iterator it = _championsAttackingLeftNecro.begin();
                                it != _championsAttackingLeftNecro.end(); ++it) {
                                    (*it)->GetAI()->AttackStart(jainaOrSylvanas);
                                }

                                for(std::list<Creature*>::const_iterator it = _championsAttackingRightNecro.begin();
                                it != _championsAttackingRightNecro.end(); ++it) {
                                    (*it)->GetAI()->AttackStart(jainaOrSylvanas);
                                }
                            }
                            break;

                        case EVENT_INTRO_11:
                            _events.ScheduleEvent(EVENT_INTRO_12, 2500);

                            if (Creature* jainaOrSylvanas = ObjectAccessor::GetObjectInMap(_jainaOrSylvanas1GUID, instance, (Creature*)NULL)) {
                                if (_teamInInstance == ALLIANCE) {
                                    for(int i = 0; i < 4; i++) {
                                        Creature* dummy = jainaOrSylvanas->SummonCreature(23837, blizzardPos[i],  TEMPSUMMON_TIMED_DESPAWN, 20000);
                                        if(dummy)
                                            jainaOrSylvanas->CastSpell(dummy, SPELL_BLIZZARD, false);
                                    }

                                    DoScriptText(SAY_JAINA_OPENNING_03, jainaOrSylvanas);
                                }
                                else {
                                    jainaOrSylvanas->CastSpell(jainaOrSylvanas, SPELL_SHRIEK_HIGHBORNE, false);
                                }
                            }
                            break;

                        case EVENT_INTRO_12:
                            _events.ScheduleEvent(EVENT_INTRO_13, 2500);

                            if (Creature* jainaOrSylvanas = ObjectAccessor::GetObjectInMap(_jainaOrSylvanas1GUID, instance, (Creature*)NULL)) {
                                for(std::list<Creature*>::const_iterator it = _championsAttackingLeftNecro.begin();
                                it != _championsAttackingLeftNecro.end(); ++it) {
                                    jainaOrSylvanas->Kill(*it);
                                }

                                for(std::list<Creature*>::const_iterator it = _championsAttackingRightNecro.begin();
                                it != _championsAttackingRightNecro.end(); ++it) {
                                    jainaOrSylvanas->Kill(*it);
                                }
                            }

                            break;
                        case EVENT_INTRO_13:
                            _events.ScheduleEvent(EVENT_INTRO_14, 6000);
                            if (Creature* jainaOrSylvanas = ObjectAccessor::GetObjectInMap(_jainaOrSylvanas1GUID, instance, (Creature*)NULL))
                                if (_teamInInstance == ALLIANCE)
                                    DoScriptText(SAY_JAINA_OPENNING_04, jainaOrSylvanas);
                                else
                                    DoScriptText(SAY_SYLVANAS_OPENNING_03, jainaOrSylvanas);

                            break;
                        case EVENT_INTRO_14:
                            if (Creature* jainaOrSylvanas = ObjectAccessor::GetObjectInMap(_jainaOrSylvanas1GUID, instance, (Creature*)NULL))
                                if (_teamInInstance == ALLIANCE)
                                    DoScriptText(SAY_JAINA_OPENNING_05, jainaOrSylvanas);
                                else
                                    DoScriptText(SAY_SYLVANAS_OPENNING_04, jainaOrSylvanas);
                            break;
                        case EVENT_ICEFALL:
                        {
                            if(_tunnelStarted)
                                _events.ScheduleEvent(EVENT_ICEFALL, 400);
                            std::list<uint64>::iterator itr = _icefallStalkers.begin();
                            advance(itr, urand(0, _icefallStalkers.size()-1));
                            if(Creature * stalker = ObjectAccessor::GetObjectInMap(*itr, instance, (Creature*)NULL))
                                stalker->CastSpell(stalker, 69424, false);
                            break;
                        }
                    }
                }

            }

            void OnCreatureCreate(Creature* creature)
            {
                if (!_teamInInstance)
                {
                    Map::PlayerList const &players = instance->GetPlayers();
                    if (!players.isEmpty())
                        if (Player* player = players.begin()->getSource())
                            _teamInInstance = player->GetTeam();
                }

                switch (creature->GetEntry())
                {
                    case NPC_GARFROST:
                        _garfrostGUID = creature->GetGUID();
                        break;
                    case NPC_KRICK:
                        _krickGUID = creature->GetGUID();
                        break;
                    case NPC_ICK:
                        _ickGUID = creature->GetGUID();
                        break;
                    case NPC_TYRANNUS:
                        _tyrannusGUID = creature->GetGUID();
                        break;
                    case NPC_RIMEFANG:
                        _rimefangGUID = creature->GetGUID();
                        break;
                    case NPC_TYRANNUS_EVENTS:
                        _tyrannusEventGUID = creature->GetGUID();
                        creature->SetFlying(true);
                        break;
                    case NPC_SYLVANAS_PART1:
                        if (_teamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_JAINA_PART1, ALLIANCE);

                        _jainaOrSylvanas1GUID = creature->GetGUID();
                        creature->SetReactState(REACT_PASSIVE);
                        
                        break;
                    case NPC_SYLVANAS_PART2:
                        if (_teamInInstance == ALLIANCE)
                            creature->UpdateEntry(NPC_JAINA_PART2, ALLIANCE);
                        _jainaOrSylvanas2GUID = creature->GetGUID();
                        break;
                    case NPC_KALIRA:
                        if (_teamInInstance == ALLIANCE)
                           creature->UpdateEntry(NPC_ELANDRA, ALLIANCE);
                        break;
                    case NPC_KORALEN:
                        if (_teamInInstance == ALLIANCE)
                           creature->UpdateEntry(NPC_KORLAEN, ALLIANCE);
                        break;
                    case NPC_CHAMPION_1_HORDE:
                        if (_teamInInstance == ALLIANCE)
                           creature->UpdateEntry(NPC_CHAMPION_1_ALLIANCE, ALLIANCE);
                        if(creature->GetPositionY() >= 216)
                            _championsAttackingLeftNecro.push_back(creature);
                        else
                            _championsAttackingRightNecro.push_back(creature);
                    
                        break;
                    case NPC_CHAMPION_2_HORDE:
                        if (_teamInInstance == ALLIANCE)
                           creature->UpdateEntry(NPC_CHAMPION_2_ALLIANCE, ALLIANCE);
                        if(creature->GetPositionY() >= 216)
                            _championsAttackingLeftNecro.push_back(creature);
                        else
                            _championsAttackingRightNecro.push_back(creature);
                        break;
                    case NPC_CHAMPION_3_HORDE: // No 3rd set for Alliance?
                        if (_teamInInstance == ALLIANCE)
                           creature->UpdateEntry(NPC_CHAMPION_2_ALLIANCE, ALLIANCE);
                        if(creature->GetPositionY() >= 216)
                            _championsAttackingLeftNecro.push_back(creature);
                        else
                            _championsAttackingRightNecro.push_back(creature);
                        break;
                    case NPC_HORDE_SLAVE_1:
                        if (_teamInInstance == ALLIANCE)
                           creature->UpdateEntry(NPC_ALLIANCE_SLAVE_1, ALLIANCE);
                        break;
                    case NPC_HORDE_SLAVE_2:
                        if (_teamInInstance == ALLIANCE)
                           creature->UpdateEntry(NPC_ALLIANCE_SLAVE_2, ALLIANCE);
                        break;
                    case NPC_HORDE_SLAVE_3:
                        if (_teamInInstance == ALLIANCE)
                           creature->UpdateEntry(NPC_ALLIANCE_SLAVE_3, ALLIANCE);
                        break;
                    case NPC_HORDE_SLAVE_4:
                        if (_teamInInstance == ALLIANCE)
                           creature->UpdateEntry(NPC_ALLIANCE_SLAVE_4, ALLIANCE);
                        break;
                    case NPC_DEATHWHISPER_NECROLYTE:
                        if(creature->GetPositionX() <= 508) {
                            if(creature->GetPositionY() >= 216)
                                _leftNecroGUID = creature->GetGUID();
                            else
                                _rightNecroGUID = creature->GetGUID();

                            creature->SetReactState(REACT_PASSIVE); // so that they don't move to the champions attacking them
                        }
                        break;
                    case NPC_INVISIBLE_STALKER:
                        _icefallStalkers.push_back(creature->GetGUID());
                        break;
                    default:
                        break;
                }
            }

            uint32 GetData(uint32 type)
            {
                switch (type)
                {
                    case DATA_TEAM_IN_INSTANCE:
                        return _teamInInstance;
                    default:
                        break;
                }

                return 0;
            }

            uint64 GetData64(uint32 type)
            {
                switch (type)
                {
                    case DATA_GARFROST:
                        return _garfrostGUID;
                    case DATA_KRICK:
                        return _krickGUID;
                    case DATA_ICK:
                        return _ickGUID;
                    case DATA_TYRANNUS:
                        return _tyrannusGUID;
                    case DATA_RIMEFANG:
                        return _rimefangGUID;
                    case DATA_TYRANNUS_EVENT:
                        return _tyrannusEventGUID;
                    case DATA_JAINA_SYLVANAS_1:
                        return _jainaOrSylvanas1GUID;
                    case DATA_JAINA_SYLVANAS_2:
                        return _jainaOrSylvanas2GUID;
                    default:
                        break;
                }

                return 0;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "P S " << GetBossSaveData();

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
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

                std::istringstream loadStream(in);
                loadStream >> dataHead1 >> dataHead2;

                if (dataHead1 == 'P' && dataHead2 == 'S')
                {
                    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;

                        SetBossState(i, EncounterState(tmpState));
                    }
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }

            void SetData(uint32 type, uint32 data)
            {
                if(type == 1 ) {
                    if(data == 1 && !_tunnelStarted) {
                        _tunnelStarted = true;
                        _events.ScheduleEvent(EVENT_ICEFALL, 250);
                    }
                    else if(data == 0) {
                        _tunnelStarted = false;
                    }
                }
            }

        private:
            uint64 _garfrostGUID;
            uint64 _krickGUID;
            uint64 _ickGUID;
            uint64 _tyrannusGUID;
            uint64 _rimefangGUID;

            uint64 _tyrannusEventGUID;
            uint64 _jainaOrSylvanas1GUID;
            uint64 _jainaOrSylvanas2GUID;

            uint64 _leftNecroGUID;
            uint64 _rightNecroGUID;

            bool _tunnelStarted;

            std::list<Creature*> _championsAttackingLeftNecro;
            std::list<Creature*> _championsAttackingRightNecro;
            std::list<uint64>    _icefallStalkers;

            EventMap _events;

            uint32 _teamInInstance;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_pit_of_saron_InstanceScript(map);
        }
};

void AddSC_instance_pit_of_saron()
{
    new instance_pit_of_saron();
}
