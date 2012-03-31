-- POST MARROWGAR

-- set npc to use EventAI
UPDATE `creature_template` SET `AIName`='EventAI', Scriptname = '' WHERE `entry` IN (37011, 36725, 36724, 37007, 37012);

-- delete previous AI scripts
DELETE FROM `creature_ai_scripts` WHERE `creature_id` in (37011, 36725, 36724, 37007, 37012);

-- Ai scripts
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES

(20021001,37012,13,0,100,31,10000,20000,0,0,11,70964,1,0,0,0,0,0,0,0,0,0,'Ancient Skeletal Soldier - Cast Shield Bash When player casts a spell'),
(26021089,37011,0,0,100,31,15000,15000,34000,36000,11,70960,0,1,0,0,0,0,0,0,0,0,'The Damned - Casts Bone Flurry'),
(26021090,37011,6,0,100,30,0,0,0,0,11,70961,0,3,0,0,0,0,0,0,0,0,'The Damned - Cast Shattered Bones On Death'),
(25021040,36725,0,0,100,31,5000,5000,35000,35000,11,70965,0,0,0,0,0,0,0,0,0,0,'Nerubar Broodkeeper - Cast Crypt Scarabs'),
(25021041,36725,14,0,90,30,45000,40,0,0,11,71020,6,1,0,0,0,0,0,0,0,0,'Nerubar Broodkeeper - Casts Dark Mending on Friendlies'),
(25021042,36725,0,0,100,31,10000,10000,21000,22000,11,70980,4,0,0,0,0,0,0,0,0,0,'Nerubar Broodkeeper - Cast Web Wrap'),
(25021073,36724,0,0,100,31,8000,12000,22000,26000,11,71029,4,0,0,0,0,0,0,0,0,0,'Servant of the Throne - Casts Glacial Blast'),
(27021077,37007,0,0,100,31,15000,15000,25000,25000,11,71022,0,0,0,0,0,0,0,0,0,0,'Deathbound Ward - Casts Disrupting Shout'),
(27021078,37007,0,0,100,31,12000,12000,20000,29000,11,71021,1,0,0,0,0,0,0,0,0,0,'Deathbound Ward - Casts Saber Lash');

-- POST MURMEMORT

-- set npc to use EventAI
UPDATE `creature_template` SET `AIName`='EventAI', Scriptname = '' WHERE `entry` IN (36844, 36808, 36805, 36811, 36807, 36829);

-- delete previous AI scripts
DELETE FROM `creature_ai_scripts` WHERE `creature_id` in (36844, 36808, 36805, 36811, 36807, 36829);

-- Ai scripts
INSERT INTO `creature_ai_scripts` (`id`,`creature_id`,`event_type`,`event_inverse_phase_mask`,`event_chance`,`event_flags`,`event_param1`,`event_param2`,`event_param3`,`event_param4`,`action1_type`,`action1_param1`,`action1_param2`,`action1_param3`,`action2_type`,`action2_param1`,`action2_param2`,`action2_param3`,`action3_type`,`action3_param1`,`action3_param2`,`action3_param3`,`comment`) VALUES
(16021069,36844,0,0,100,6,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Risen Deathspeaker Servant - Stop Movement on Aggro'),
(16021070,36844,4,0,100,6,0,0,0,0,11,69576,1,0,22,6,0,0,0,0,0,0,'Deathspeaker Servant - Cast Chaos Bolt and Set Phase 1 on Aggro'),
(16021071,36844,3,0,100,6,15,0,0,0,21,1,0,0,22,5,0,0,0,0,0,0,'Deathspeaker Servant - Start Movement and Set Phase 2 when Mana is at 15%'),
(16021072,36844,0,6,100,7,0,0,1500,3000,11,69576,1,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Cast Chaos Bolt above 15% Mana (Phase 1)'),
(16021073,36844,3,5,100,6,100,28,0,0,21,0,0,0,22,6,0,0,0,0,0,0,'Deathspeaker Servant - Set Ranged Movement and Set Phase 1 when Mana is above 28% (Phase 2)'),
(16021074,36844,9,0,100,7,30,50,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Start Movement Beyond 30 Yards'),
(16021075,36844,7,0,100,6,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - On Evade set Phase to 0'),
(16021076,36844,0,0,100,24,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Stop Movement on Aggro'),
(16021077,36844,4,0,100,24,0,0,0,0,11,71108,1,0,22,6,0,0,0,0,0,0,'Deathspeaker Servant - Cast Chaos Bolt and Set Phase 1 on Aggro'),
(16021078,36844,3,0,100,24,15,0,0,0,21,1,0,0,22,5,0,0,0,0,0,0,'Deathspeaker Servant - Start Movement and Set Phase 2 when Mana is at 15%'),
(16021079,36844,0,6,100,25,0,0,1500,3000,11,71108,1,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Cast Chaos Bolt above 15% Mana (Phase 1)'),
(16021080,36844,3,5,100,24,100,28,0,0,21,0,0,0,22,6,0,0,0,0,0,0,'Deathspeaker Servant - Set Ranged Movement and Set Phase 1 when Mana is above 28% (Phase 2)'),
(16021081,36844,9,0,100,25,30,50,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Start Movement Beyond 30 Yards'),
(15021082,36844,7,0,100,24,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - On Evade set Phase to 0'),
(25021066,36844,0,0,100,7,5000,7000,15000,19000,11,69404,4,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Casts Curse of Agony'),
(25021067,36844,0,0,100,25,5000,7000,15000,19000,11,71112,4,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Casts Curse of Agony'),
(25021068,36844,0,0,100,31,12000,14000,30000,32000,11,69405,4,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Casts Consuming Shadows'),
(22021068,36808,0,0,100,31,11000,11000,22000,25000,11,69492,1,0,0,0,0,0,0,0,0,0,'Deathspeaker Zealot  - Casts Shadow Cleave'),
(22021069,36805,0,0,100,6,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Stop Movement on Aggro'),
(22021070,36805,4,0,100,6,0,0,0,0,11,69576,1,0,22,6,0,0,0,0,0,0,'Deathspeaker Servant - Cast Chaos Bolt and Set Phase 1 on Aggro'),
(22021071,36805,3,0,100,6,15,0,0,0,21,1,0,0,22,5,0,0,0,0,0,0,'Deathspeaker Servant - Start Movement and Set Phase 2 when Mana is at 15%'),
(22021072,36805,0,6,100,7,0,0,1500,3000,11,69576,1,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Cast Chaos Bolt above 15% Mana (Phase 1)'),
(22021073,36805,3,5,100,6,100,28,0,0,21,0,0,0,22,6,0,0,0,0,0,0,'Deathspeaker Servant - Set Ranged Movement and Set Phase 1 when Mana is above 28% (Phase 2)'),
(22021074,36805,9,0,100,7,30,50,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Start Movement Beyond 30 Yards'),
(22021075,36805,7,0,100,6,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - On Evade set Phase to 0'),
(22021076,36805,0,0,100,24,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Stop Movement on Aggro'),
(22021077,36805,4,0,100,24,0,0,0,0,11,71108,1,0,22,6,0,0,0,0,0,0,'Deathspeaker Servant - Cast Chaos Bolt and Set Phase 1 on Aggro'),
(22021078,36805,3,0,100,24,15,0,0,0,21,1,0,0,22,5,0,0,0,0,0,0,'Deathspeaker Servant - Start Movement and Set Phase 2 when Mana is at 15%'),
(22021079,36805,0,6,100,25,0,0,1500,3000,11,71108,1,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Cast Chaos Bolt above 15% Mana (Phase 1)'),
(22021080,36805,3,5,100,24,100,28,0,0,21,0,0,0,22,6,0,0,0,0,0,0,'Deathspeaker Servant - Set Ranged Movement and Set Phase 1 when Mana is above 28% (Phase 2)'),
(22021081,36805,9,0,100,25,30,50,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Start Movement Beyond 30 Yards'),
(22021082,36805,7,0,100,24,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - On Evade set Phase to 0'),
(27021066,36805,0,0,100,7,5000,7000,15000,19000,11,69404,4,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Casts Curse of Agony'),
(27021067,36805,0,0,100,25,5000,7000,15000,19000,11,71112,4,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Casts Curse of Agony'),
(27021068,36805,0,0,100,31,12000,14000,30000,32000,11,69405,4,0,0,0,0,0,0,0,0,0,'Deathspeaker Servant - Casts Consuming Shadows'),
(27021069,36829,0,0,100,31,12000,14000,22000,22000,11,69483,4,0,0,0,0,0,0,0,0,0,'Deathspeaker High Priest  - Casts Dark Reckoning'),
(27021070,36829,1,0,100,31,1000,1000,1800000,1800000,11,69491,0,0,0,0,0,0,0,0,0,0,'Deathspeaker High Priest - Casts Aura of Darkness on Spawn'),
(22021089,36811,0,0,100,7,12000,15000,25000,25000,11,69355,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Attendant  - Casts Shadow Nova'),
(22021090,36811,0,0,100,25,12000,15000,25000,25000,11,71106,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Attendant  - Casts Shadow Nova'),
(22021091,36811,0,0,100,30,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Attendant  - Stop Movement on Aggro'),
(22021092,36811,4,0,100,30,0,0,0,0,11,69387,1,0,22,6,0,0,0,0,0,0,'Deathspeaker Attendant  - Cast Shadow Bolt and Set Phase 1 on Aggro'),
(22021093,36811,3,0,100,30,15,0,0,0,21,1,0,0,22,5,0,0,0,0,0,0,'Deathspeaker Attendant  - Start Movement and Set Phase 2 when Mana is at 15%'),
(22021094,36811,0,6,100,31,0,0,1500,3000,11,69387,1,0,0,0,0,0,0,0,0,0,'Deathspeaker Attendant  - Cast Shadow Bolt above 15% Mana (Phase 1)'),
(22021095,36811,3,5,100,30,100,28,0,0,21,0,0,0,22,6,0,0,0,0,0,0,'Deathspeaker Attendant  - Set Ranged Movement and Set Phase 1 when Mana is above 28% (Phase 2)'),
(22021096,36811,9,0,100,31,30,50,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Attendant  - Start Movement Beyond 30 Yards'),
(22021097,36811,7,0,100,30,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Attendant  - On Evade set Phase to 0'),
(27021079,36807,14,0,90,6,320,40,0,0,11,69389,6,1,0,0,0,0,0,0,0,0,'Deathspeaker Disciple - Casts Shadow Mend on Friendlies'),
(27021080,36807,14,0,90,24,320,40,0,0,11,71107,6,1,0,0,0,0,0,0,0,0,'Deathspeaker Disciple - Casts Shadow Mend on Friendlies'),
(27021081,36807,0,0,100,30,0,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Disciple - Stop Movement on Aggro'),
(27021082,36807,4,0,100,30,0,0,0,0,11,69387,1,0,22,6,0,0,0,0,0,0,'Deathspeaker Disciple - Cast Shadow Bolt and Set Phase 1 on Aggro'),
(27021083,36807,3,0,100,30,15,0,0,0,21,1,0,0,22,5,0,0,0,0,0,0,'Deathspeaker Disciple - Start Movement and Set Phase 2 when Mana is at 15%'),
(27021084,36807,0,6,100,31,0,0,1500,3000,11,69387,1,0,0,0,0,0,0,0,0,0,'Deathspeaker Disciple - Cast Shadow Bolt above 15% Mana (Phase 1)'),
(27021085,36807,3,5,100,30,100,28,0,0,21,0,0,0,22,6,0,0,0,0,0,0,'Deathspeaker Disciple - Set Ranged Movement and Set Phase 1 when Mana is above 28% (Phase 2)'),
(22021086,36807,9,0,100,31,30,50,0,0,22,1,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Disciple - Start Movement Beyond 30 Yards'),
(22021087,36807,7,0,100,30,0,0,0,0,22,0,0,0,0,0,0,0,0,0,0,0,'Deathspeaker Disciple - On Evade set Phase to 0'),
(22021088,36807,0,0,100,31,9000,9000,25000,28000,11,69391,0,1,0,0,0,0,0,0,0,0,'Deathspeaker Disciple - Casts Dark Blessing');
