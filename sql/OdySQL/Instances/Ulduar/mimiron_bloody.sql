UPDATE `gameobject_template` SET `flags` = 32, `data2` = 3000, `ScriptName` = 'go_call_tram' WHERE `entry` IN (194914, 194912, 194437);
DELETE FROM gameobject WHERE id = '194437';
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
('194437','603','3','1','2306.87','274.237','424.288','1.52255','0','0','0.689847','0.723956','300','0','1');
DELETE FROM gameobject_template WHERE entry = '194438';
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`, `WDBVerified`) VALUES
('194438','1','8504','Activate Tram','','','','0','32','1','0','0','0','0','0','0','0','0','3000','0','0','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','go_call_tram','11159');
DELETE FROM gameobject WHERE id = '194438';
INSERT INTO `gameobject` (`id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(194438, 603, 3,1,2306.99, 2589.35, 424.382, 4.71676, 0, 0, 0.705559, -0.708651, 300, 0, 1);
UPDATE `creature_template` SET `vehicleId` = 336 WHERE `entry` = 33432; -- Leviathan Mk II
DELETE FROM creature WHERE id = 34071;
DELETE FROM vehicle_accessory WHERE entry = 33432;
INSERT INTO vehicle_accessory VALUE (33432, 34071, 7, 1, 'Leviathan Mk II turret', '0');
UPDATE creature_template SET ScriptName = 'boss_mimiron' WHERE entry = 33350;
UPDATE creature_template SET ScriptName = 'boss_leviathan_mk' WHERE entry = 33432;
UPDATE creature_template SET ScriptName = 'boss_leviathan_mk_turret' WHERE entry = 34071;
UPDATE creature_template SET ScriptName = 'mob_proximity_mine' WHERE entry = 34362;
DELETE FROM `creature_model_info` WHERE `modelid`=28831;
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`) VALUES
(28831, 0.5, 7, 2, 0);
DELETE FROM `creature_model_info` WHERE `modelid`=28831;
INSERT INTO `creature_model_info` (`modelid`, `bounding_radius`, `combat_reach`, `gender`, `modelid_other_gender`) VALUES
(28831, 0, 0, 2, 0);
UPDATE `creature_template` SET `flags_extra` = 2 WHERE `entry` IN (33856, 34143, 34050);
UPDATE `creature_template` SET `unit_flags` = 33686018 WHERE `entry` = 34050;
UPDATE `creature` SET `position_x` = 2736.92, `position_y` = 2572.30, `orientation` = 5.723 WHERE `guid` = 137630;
UPDATE `creature_template` SET `ScriptName` = 'boss_vx_001', `unit_flags` = 0, `vehicleid` = 371, `Health_mod` = 375 WHERE `entry` = 33651;
UPDATE `creature_template` SET `ScriptName` = 'boss_aerial_unit', `unit_flags` = 0, `vehicleid` = 388, `Health_mod` = 250 WHERE `entry` = 33670;
UPDATE `creature_template` SET `vehicleid` = 370, `Health_mod` = 156.185 WHERE `entry` = 33432;
UPDATE `creature_template` SET `Health_mod` = 156.185 WHERE `entry` = 34071;

DELETE FROM vehicle_accessory WHERE entry = 33432;
INSERT INTO vehicle_accessory VALUE (33432, 34071, 3, 1, 'Leviathan Mk II turret', '0');
UPDATE `creature_template` SET `modelid1` = 17188, `modelid2` = 0 WHERE `entry` = 25171;
UPDATE `creature_template` SET `speed_walk` = 0.5, `speed_run` = 0.5, `ScriptName` = 'mob_boom_bot' WHERE `entry` IN (33836,34192);

DELETE FROM `creature` WHERE `id`=33651;
INSERT INTO `creature` (`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(33651, 603, 3, 1, 28841, 0, 2744.65, 2569.46, 364.397, 3.14159, 604800, 0, 0, 1742400, 0, 0, 0);
UPDATE `creature_template` SET `unit_flags` = 33686020, `flags_extra` = 2, `ScriptName` = 'rocket_strike' WHERE `entry` = 34047;

DELETE FROM `creature` WHERE `id`=33670;
INSERT INTO `creature` (`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`) VALUES
(33670, 603, 3, 1, 28979, 0, 2744.65, 2569.46, 380.040, 3.14159, 604800, 0, 0, 1742400, 0, 0, 0);

UPDATE `creature_template` SET `unit_flags` = 33686020, `type_flags` = 0, `flags_extra` = 2, `ScriptName` = 'magnetic_core' WHERE `entry` = 34068;
UPDATE `gameobject_template` SET `size` = 1.5 WHERE `entry` = 194956;
DELETE FROM `gameobject` WHERE `id`=194956;
INSERT INTO `gameobject` (`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(194956, 603, 2, 1, 2744.65, 2569.46, 364.397, 3.14159, 0, 0, 0.703237, 0.710955, -604800, 0, 1);
UPDATE `gameobject_template` SET `size` = 1.5 WHERE `entry` = 194789;
DELETE FROM `gameobject` WHERE `id`=194789;
INSERT INTO `gameobject` (`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(194789, 603, 1, 1, 2744.65, 2569.46, 364.397, 3.14159, 0, 0, 0.703237, 0.710955, -604800, 0, 1);

UPDATE `creature_template` SET `mechanic_immune_mask` = 650854235, `flags_extra` = 1 WHERE `entry` IN (33432, 33651, 33670);
UPDATE `creature_template` SET `minlevel` = 80, `maxlevel` = 80, `faction_A` = 35, `faction_H` = 35, `unit_flags` = 33686020 WHERE `entry` = 34211;