/*DELETE FROM creature_template WHERE entry IN (22517, 30090, 30084, 30118, 30248, 30245, 30249, 30282, 30334, 30592, 32295, 28859, 30161);
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction_A`, `faction_H`, `npcflag`, `speed`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `PetSpellDataId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `VehicleId`) VALUES
(22517, 0, 0, 0, 0, 0, 11686, 11686, 11686, 11686, 'i', '', NULL, 0, 80, 80, 16, 16, 0, 1, 1, 0, 0, 0, 0, 252, 7.5, 2000, 0, 1, 33554434, 0, 0, 0, 0, 0, 0, 72, 106, 26, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1.35, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, '', '0'),
(28859, 31734, 0, 0, 0, 0, 26752, 0, 26752, 0, 'Malygos', '', '', 0, 83, 83, 16, 16, 0, 1, 1, 3, 496, 674, 0, 783, 35, 2000, 0, 2, 0, 0, 0, 0, 0, 0, 0, 365, 529, 98, 2, 108, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 7, 500, 50, 0, 44650, 0, 0, 0, 0, 0, 227, 1, 0, 617299803, 1, 'boss_malygos', '0'),
(30084, 32187, 0, 0, 0, 0, 26753, 0, 26753, 0, 'Power Spark', '', '', 0, 80, 80, 16, 16, 0, 1, 1, 0, 0, 0, 0, 0, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 7, 1, 1, 0, 0, 0, 0, 0, 0, 0, 106, 1, 0, 0, 0, 'mob_power_spark', '0'),
(30090, 0, 0, 0, 0, 0, 11686, 11686, 11686, 11686, 'Vortex', '', '', 0, 80, 80, 14, 14, 0, 1, 1, 0, 422, 586, 0, 642, 7.5, 2000, 0, 1, 33554434, 0, 0, 0, 0, 0, 0, 345, 509, 103, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 76, 1, 0, 0, 2, '', '0'),
(30118, 0, 0, 0, 0, 0, 169, 0, 14501, 0, 'Portal (Malygos)', '', '', 0, 80, 80, 114, 114, 0, 1, 1, 0, 422, 586, 0, 642, 7.5, 2000, 0, 1, 33555200, 0, 0, 0, 0, 0, 0, 345, 509, 103, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullAI', 0, 4, 1.35, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', '0'),
(30161, 0, 0, 0, 0, 0, 25835, 0, 25835, 0, 'Wyrmrest Skytalon', '', '', 0, 85, 85, 35, 35, 0, 1, 1, 0, 0, 0, 0, 0, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 7.93651, 1, 0, 0, 0, 0, 0, 0, 0, 231, 1, 0, 0, 0, '', '194'),
(30245, 31750, 0, 0, 0, 0, 24316, 24318, 24317, 24319, 'Nexus Lord', '', '', 0, 80, 80, 16, 16, 0, 1, 1, 1, 5000, 6000, 0, 450, 1, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 30, 25, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', '0'),
(30248, 31749, 0, 0, 0, 0, 26876, 0, 26876, 0, 'Hover Disk', '', 'vehichleCursor', 0, 80, 80, 35, 35, 0, 1, 1, 0, 0, 0, 0, 0, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, '', '224'),
(30249, 31751, 0, 0, 0, 0, 24316, 24318, 24317, 24319, 'Scion of Eternity', '', '', 0, 80, 80, 16, 16, 0, 1, 1, 1, 4000, 5000, 0, 450, 1, 2000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 7, 20, 25, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 'mob_scion_of_eternity', '0'),
(30282, 0, 0, 0, 0, 0, 14501, 14501, 14501, 14501, 'Arcane Overload', '', '', 0, 80, 80, 16, 16, 0, 1, 1, 0, 0, 0, 0, 0, 1, 2000, 0, 1, 33554434, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullAI', 0, 3, 1, 1, 0, 0, 0, 0, 0, 0, 0, 76, 1, 0, 1073741823, 2, '', '0'),
(30334, 0, 0, 0, 0, 0, 169, 0, 11686, 0, 'Surge of Power', '', '', 0, 80, 80, 14, 14, 0, 1, 1, 0, 422, 586, 0, 642, 7.5, 2000, 0, 1, 33554432, 0, 0, 0, 0, 0, 0, 345, 509, 103, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullAI', 0, 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1073741823, 2, '', '0'),
(30592, 0, 0, 0, 0, 0, 11686, 11686, 11686, 11686, 'Static Field', '', '', 0, 80, 80, 16, 16, 0, 1, 1, 0, 0, 0, 0, 0, 1, 2000, 0, 1, 33554438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'NullAI', 0, 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1073741823, 0, '', '0'),
(32295, 0, 0, 0, 0, 0, 27569, 0, 27569, 0, 'Alexstrasza the Life-Binder', 'Queen of the Dragons', '', 0, 83, 83, 35, 35, 0, 1, 1, 3, 0, 0, 0, 0, 1, 2000, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 36, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 4, 10000, 1000, 0, 0, 0, 0, 0, 0, 0, 220, 1, 0, 0, 0, '', '0');
*/
DELETE from creature where id = 30282;
/*
DELETE FROM vehicle_accessory WHERE `accessory_entry` IN (31749, 30248);
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `description`) VALUES ('30249', '30248', 'Malygos Scion');
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `description`) VALUES ('30245', '30248', 'Malygos Lord');
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `description`) VALUES ('31751', '31749', 'Malygos Scion hero');
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `description`) VALUES ('31750', '31749', 'Malygos Lord hero');
UPDATE `vehicle_accessory` SET `seat_id`='1' WHERE `accessory_entry` IN (31749, 30248);
UPDATE creature_template SET VehicleId = 200 WHERE entry IN (31750, 31751, 30249, 30245);
*/

UPDATE creature_template Set VehicleId = 0 WHERE entry IN (30249, 30245, 31751, 31750);

DELETE FROM creature WHERE map=616;
REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES
(53822, 22517, 564, 1, 1, 16925, 0, 703.999, 585.379, 112.711, 1.51844, 3600, 0, 0, 4120, 0, 0, 0),
(53823, 22517, 564, 1, 1, 16925, 0, 600.887, 402.192, 187.173, 4.95674, 3600, 0, 0, 4120, 0, 0, 0),
(53824, 22517, 564, 1, 1, 16925, 0, 945.228, 164.548, 197.158, 1.51844, 3600, 0, 0, 4120, 0, 0, 0),
(53825, 22517, 564, 1, 1, 16925, 0, 753.435, 276.779, 63.8543, 1.58825, 3600, 0, 0, 4120, 0, 0, 0),
(53826, 22517, 564, 1, 1, 16925, 0, 435.294, 741.606, 15.2089, 1.18682, 3600, 0, 0, 4120, 0, 0, 0),
(86196, 22517, 568, 1, 1, 16925, 0, 370.78, 1119.51, 5.78472, 3.87463, 7200, 0, 0, 4120, 0, 0, 0),
(100864, 22517, 578, 3, 1, 16925, 0, 1061, 982.604, 361.154, 3.50811, 3600, 0, 0, 4120, 0, 0, 0),
(126671, 22517, 576, 3, 1, 16925, 0, 733.436, -67.9865, -43.8489, 1.37881, 3600, 0, 0, 4120, 0, 0, 0),
(127213, 22517, 604, 3, 1, 16925, 0, 1942.3, 744.085, 151.475, 5.88176, 3600, 0, 0, 4120, 0, 0, 0),
(137517, 22517, 603, 1, 1, 16925, 0, 2273.02, 287.912, 419.305, 0, 180, 0, 0, 4120, 0, 0, 0),
(503154, 22517, 616, 1, 1, 0, 0, 755.179, 1303.81, 266.171, 4.74717, 25, 0, 0, 4120, 0, 0, 0),
(503155, 22517, 616, 1, 1, 0, 0, 754.421, 1302.09, 266.171, 4.6472, 25, 0, 0, 2500, 0, 0, 0),
(503156, 28859, 616, 3, 1, 0, 0, 821.641, 1220.77, 296.243, 2.32949, 25, 0, 0, 6972500, 212900, 0, 0),
(132304, 30090, 616, 3, 1, 11686, 0, 754.733, 1301.51, 283.379, 5.58505, 3600, 5, 0, 12600, 0, 0, 1),
(132305, 30090, 616, 3, 1, 11686, 0, 754.521, 1301.23, 279.524, 0.680678, 3600, 5, 0, 12600, 0, 0, 1),
(132306, 30090, 616, 3, 1, 11686, 0, 754.356, 1301.48, 285.733, 5.96903, 3600, 5, 0, 12600, 0, 0, 1),
(132307, 30090, 616, 3, 1, 11686, 0, 754.192, 1301.18, 281.851, 5.75959, 3600, 5, 0, 12600, 0, 0, 1),
(132308, 30090, 616, 3, 1, 11686, 0, 754.688, 1301.8, 287.295, 1.25664, 3600, 5, 0, 12600, 0, 0, 1),
(132309, 30118, 616, 3, 1, 14501, 0, 652.417, 1200.52, 295.972, 0.785398, 3600, 0, 0, 7212, 0, 0, 0),
(132310, 30118, 616, 3, 1, 14501, 0, 847.67, 1408.05, 295.972, 3.97935, 3600, 0, 0, 7212, 0, 0, 0),
(132311, 30118, 616, 3, 1, 14501, 0, 647.675, 1403.8, 295.972, 5.53269, 3600, 0, 0, 7212, 0, 0, 0),
(132312, 30118, 616, 3, 1, 14501, 0, 843.182, 1215.42, 295.972, 2.35619, 3600, 0, 0, 7212, 0, 0, 0),
(503157, 30161, 571, 1, 1, 0, 0, 4105.95, 264.407, 50.7187, 0.32889, 25, 0, 0, 75000, 0, 0, 0),
(503158, 30161, 1, 1, 1, 0, 0, 1375.66, -4410.17, 30.2842, 3.25768, 25, 0, 0, 75000, 0, 0, 0),
(503159, 30161, 1, 1, 1, 0, 0, 1255.7, -4373.57, 28.5261, 0.269632, 25, 0, 0, 75000, 0, 0, 0),
(503160, 30161, 13, 1, 1, 0, 0, -0.310414, 0.107129, -144.709, 0.51767, 25, 0, 0, 75000, 0, 0, 0),
(503161, 30282, 616, 1, 1, 0, 0, 784.028, 1326.34, 267.235, 1.9606, 25, 0, 0, 12600, 0, 0, 0),
(503162, 30282, 616, 1, 1, 0, 0, 782.545, 1338.65, 267.235, 3.50627, 25, 0, 0, 12600, 0, 0, 0),
(503163, 30282, 616, 1, 1, 0, 0, 751.664, 1310.78, 266.171, 2.99114, 25, 0, 0, 12600, 0, 0, 0),
(503164, 30282, 616, 1, 1, 0, 0, 751.664, 1310.78, 266.171, 2.99114, 25, 0, 0, 12600, 0, 0, 0),
(132303, 30334, 616, 3, 1, 11686, 0, 754.294, 1301.19, 266.254, 4.24115, 3600, 5, 0, 12600, 0, 0, 1);
/*
DELETE FROM gameobject_template WHERE entry IN (193958, 193908, 193070, 193905, 193967);
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`) VALUES
(193070, 33, 8387, 'Nexus Raid Platform', '', '', '', 0, 0, 1, 0, 0, 0, 0, 0, 0, 100, 0, 0, 0, 8387, 0, 0, 0, 0, 0, 8386, 1, 0, 0, 0, 0, 0, 0, 50, 0, 8, 0, 0, 1, ''),
(193905, 3, 8513, 'Alexstrasza''s Gift', '', '', '', 0, 0, 15, 0, 0, 0, 0, 0, 0, 1818, 193905, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, ''),
(193908, 10, 1327, 'Exit Portal', '', '', '', 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 60474, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, ''),
(193958, 10, 7800, 'The Focusing Iris', '', '', '', 0, 0, 5, 0, 0, 0, 0, 0, 0, 1817, 0, 20711, 196608, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'go_focusing_iris'),
(193967, 3, 8513, 'Alexstrasza''s Gift', '', '', '', 0, 0, 15, 0, 0, 0, 0, 0, 0, 1818, 193967, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, '');

DELETE FROM gameobject WHERE map=616;
REPLACE INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(67449, 193070, 616, 3, 1, 754.346, 1300.87, 256.249, 3.14159, 0, 0, 0, 1, 180, 0, 1),
(67450, 193908, 616, 3, 1, 724.684, 1332.92, 267.234, -0.802851, 0, 0, 0, 1, 180, 0, 1),
(506424, 193958, 616, 3, 1, 759.731, 1306.12, 266.171, 5.01343, 0, 0, 0.593077, -0.805146, 25, 0, 1);
*/
/*delete from gameobject_loot_template where entry in (193905,193967);
-- Malygos - 10-man  emblemy - Conquest
INSERT INTO gameobject_loot_template (`entry`, `item`, `ChanceOrQuestChance`, `groupid`, `mincountOrRef`, `maxcount`, `lootcondition`, `condition_value1`, `condition_value2`) VALUES
(193905,45624,100,0,1,1,0,0,0),
(193905,43953,0.8,2,1,1,0,0,0),
(193905,82000,100,3,-82000,2,0,0,0),
 
-- Malygos - 25-man emblemy - Conquest
(193967,45624,100,0,1,1,0,0,0),
(193967,43952,1.2,1,1,1,0,0,0),
(193967,82001,100,4,-82001,4,0,0,0);
 
delete from reference_loot_template where entry in (82000,82001);
-- Malygos - 10-man
INSERT INTO `reference_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `groupid`, `mincountOrRef`, `maxcount`, `lootcondition`, `condition_value1`, `condition_value2`) VALUES
(82000, 40486, 0, 3, 1, 1, 0, 0, 0),
(82000, 40475, 0, 3, 1, 1, 0, 0, 0),
(82000, 40491, 0, 3, 1, 1, 0, 0, 0),
(82000, 40488, 0, 3, 1, 1, 0, 0, 0),
(82000, 40519, 0, 3, 1, 1, 0, 0, 0),
(82000, 40511, 0, 3, 1, 1, 0, 0, 0),
(82000, 40526, 0, 3, 1, 1, 0, 0, 0),
(82000, 40489, 0, 3, 1, 1, 0, 0, 0),
(82000, 40474, 0, 3, 1, 1, 0, 0, 0),
(82000, 40497, 0, 3, 1, 1, 0, 0, 0),
(82000, 34057, 0, 3, 1, 2, 0, 0, 0),

-- Malygos - 25-man
 
(82001,40566,0,4,1,1,0,0,0),
(82001,40543,0,4,1,1,0,0,0),
(82001,40592,0,4,1,1,0,0,0),
(82001,40590,0,4,1,1,0,0,0),
(82001,40560,0,4,1,1,0,0,0),
(82001,40589,0,4,1,1,0,0,0),
(82001,40555,0,4,1,1,0,0,0),
(82001,40594,0,4,1,1,0,0,0),
(82001,40588,0,4,1,1,0,0,0),
(82001,40194,0,4,1,1,0,0,0),
(82001,40539,0,4,1,1,0,0,0),
(82001,40541,0,4,1,1,0,0,0),
(82001,40562,0,4,1,1,0,0,0),
(82001,40561,0,4,1,1,0,0,0),
(82001,40532,0,4,1,1,0,0,0),
(82001,40531,0,4,1,1,0,0,0),
(82001,40591,0,4,1,1,0,0,0),
(82001,40564,0,4,1,1,0,0,0),
(82001,40558,0,4,1,1,0,0,0),
(82001,40549,0,4,1,1,0,0,0),
(82001,34057,0,4,1,3,0,0,0),
(82001,40526,0,4,1,1,0,0,0),
(82001,40474,0,4,1,1,0,0,0);

REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('56505', '1', '22517');
REPLACE INTO `spell_script_target` (`entry`, `type`, `targetEntry`) VALUES ('56152', '1', '28859');
UPDATE `instance_template` SET `script` = 'instance_eye_of_eternity' WHERE `map` =616;
/*
DELETE FROM creature_template_addon WHERE entry IN (30161, 30248);
INSERT INTO `creature_template_addon` (`entry`, `mount`, `bytes1`, `bytes2`, `emote`, `moveflags`, `vehicle_id`, `passengers`, `auras`) VALUES
(30161, 0, 0, 0, 0, 0, 194, NULL, NULL),
(30248, 0, 0, 0, 0, 0, 224, NULL, NULL);*/

UPDATE creature_template SET `Spell1` = '56091', `Spell2` = '56092', `Spell3` = '57090', `Spell4` = '57143', `Spell5` = '57108', `Spell6` = '57092', `Spell7` = '54422', `VehicleId` = '194' WHERE entry IN (30161, 31752);
UPDATE creature_template SET `Spell1` = '34304', `Spell2` = '0', `Spell3` = '0', `Spell4` = '0', `Spell5` = '0', `Spell6` = '0', `Spell7` = '54422', `VehicleId` = '224' WHERE entry IN (30248, 31769);
UPDATE `creature_template` SET `faction_A`='16', `faction_H`='16' WHERE entry IN (30248, 31769);
/*DELETE FROM vehicle_data WHERE entry IN (194, 224);

INSERT INTO `vehicle_data` (`entry`, `flags`, `Spell1`, `Spell2`, `Spell3`, `Spell4`, `Spell5`, `Spell6`, `Spell7`, `Spell8`, `Spell9`, `Spell10`, `req_aura`) VALUES
(194, 280, 56091, 56092, 57090, 57143, 57108, 57092, 0, 0, 0, 0, 0),
(224, 1802, 34304, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

DELETE FROM vehicle_seat_data WHERE seat IN (2102, 2224);
INSERT INTO `vehicle_seat_data` (`seat`, `flags`) VALUES
(2102, 3),
(2224, 7);*/

DELETE FROM npc_spellclick_spells WHERE spell_id = 60968;
INSERT INTO npc_spellclick_spells (npc_entry, spell_id, quest_start, quest_start_active, quest_end, cast_flags, aura_required, aura_forbidden, user_type) VALUES
(30161, 60968, 0, 0, 0, 1, 0, 0, 0),
(30248, 60968, 0, 0, 0, 1, 0, 0, 0);
 UPDATE creature_template SET AIName = 'NullAI' WHERE entry = 30282;
 
UPDATE creature_template SET InhabitType = '3' WHERE entry = 28859;
UPDATE creature SET spawndist = '0', MovementType = '0' WHERE creature.guid = 132313;

UPDATE `creature_template` SET `speed_walk`='2', `speed_run`='2' WHERE (`entry`='30161') LIMIT 1;
UPDATE `creature_template` SET `RegenHealth`='0' WHERE (`entry`='30161') LIMIT 1;

UPDATE creature_template SET AIName = 'NullAI' WHERE creature_template.entry = 22517;
 
UPDATE creature_template SET AIName = 'NullAI' WHERE creature_template.entry = 30090;
 
UPDATE creature_template SET AIName = 'NullAI' WHERE creature_template.entry = 30118;
 
UPDATE creature_template SET AIName = 'NullAI' WHERE creature_template.entry = 30334;
 
UPDATE creature_template SET AIName = 'NullAI' WHERE creature_template.entry = 31253;
 
UPDATE creature_template SET AIName = 'NullAI' WHERE creature_template.entry = 32448;
 
UPDATE creature_template SET modelid1 = 11686, minlevel = 80, maxlevel = 80, AIName = '', flags_extra = '2' WHERE entry = 22517; 

DELETE FROM spell_script_target WHERE entry = 56152 AND targetEntry = 28859;
INSERT INTO spell_script_target (entry, type, targetEntry) VALUES 
('56152', '1', '28859');

UPDATE creature_model_info SET combat_reach = '30' WHERE modelid = 26752;
 
UPDATE creature_template SET InhabitType = '4' WHERE entry IN (30118, 30334, 30592);

UPDATE creature_template SET mechanic_immune_mask = 1073741823 WHERE entry IN (30592, 30282, 30334);
UPDATE `creature_template` SET `Health_mod`='100000' WHERE (`entry`='30161') LIMIT 1;
INSERT INTO gameobject_template (entry, type, displayId, name, IconName, castBarCaption, unk1, faction, flags, size, questItem1, questItem2, questItem3, questItem4, questItem5, questItem6, data0, data1, data2, data3, data4, data5, data6, data7, data8, data9, data10, data11, data12, data13, data14, data15, data16, data17, data18, data19, data20, data21, data22, data23, ScriptName) VALUES
(393070, 0, 8390, 'Nexus Raid Platform - custom destroyed', '', '', '', 35, 36, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '');

--
-- Eye of Eternity
--

-- Set instance script
UPDATE instance_template SET script = 'instance_eye_of_eternity' WHERE map = 616;

-- Update flags for NPCs/Vehicles
UPDATE creature_template SET flags_extra = flags_extra | 2 WHERE entry = 30090; -- Vortex  'Arcane Overload', 'Hover Disk');
UPDATE creature_template SET flags_extra = flags_extra | 2, faction_A = 35, faction_H = 35, VehicleId = 224 WHERE entry IN (30234, 30248); -- Hover Disk
UPDATE creature_template SET flags_extra = flags_extra | 2, faction_A = 35, faction_H = 35 WHERE entry = 30118; -- Portal (Malygos)
UPDATE creature_template SET flags_extra = flags_extra | 2 WHERE entry = 30282; -- Arcane Overload
UPDATE creature_template SET mindmg = 1, maxdmg = 1, dmg_multiplier = 1 WHERE entry = 30592; -- Static Field
UPDATE creature_template SET modelid1 = 11686, modelid2 = 11686 WHERE entry = 22517; -- Some world trigger

-- Set scriptnames and some misc data to bosses and GOs
UPDATE gameobject_template SET flags = 4, data0 = 43 WHERE gameobject_template.entry in (193967, 193905);
UPDATE creature_template SET ScriptName = 'boss_malygos', unit_flags = unit_flags & ~256 WHERE entry = 28859;
UPDATE creature SET MovementType = 0, spawndist = 0 WHERE id = 28859; -- Malygos, don't move
UPDATE creature_template SET ScriptName = 'mob_nexus_lord' WHERE entry = 30245; -- Nexus Lord
UPDATE creature_template SET ScriptName = 'mob_scion_of_eternity' WHERE entry = 30249; -- Scion of Eternity
UPDATE creature_template SET faction_A = 14, faction_H = 14, ScriptName = 'mob_power_spark' WHERE entry = 30084; -- Power Spark
UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry = 32187; -- Power Spark (1)
UPDATE creature_template SET ScriptName = 'npc_arcane_overload' WHERE entry = 30282; -- Arcane Overload

-- Fix Wyrmrest drakes creature info
UPDATE creature_template SET spell1 = 56091, spell2 = 56092, spell3 = 57090, spell4 = 57143, spell5 = 57108, spell6 = 57403, VehicleId = 165 WHERE entry IN (30161, 31752);

-- Delete faulty Alextrasza spawn
DELETE FROM creature WHERE guid = 132302;
DELETE FROM creature_addon WHERE guid = 132302;

-- And Surge of Power
DELETE FROM creature WHERE guid = 132303;
DELETE FROM creature_addon WHERE guid = 132303;

-- Fix Loot caches being not selectable
UPDATE gameobject_template SET faction = 35, flags = 0 WHERE entry IN (193967, 193905);

-- Fix Surge of Power targeting
DELETE FROM spell_script_target WHERE entry = 56505;
INSERT INTO spell_script_target (entry, type, targetEntry) VALUES
(56505, 1, 22517);

-- Fix loot for Malygos (Alexstrasza's Gift)
DELETE FROM reference_loot_template WHERE entry = 50008;
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2) VALUES
(50008, 40474, 0, 1, 1, 1, 1, 0, 0, 0), -- Surge Needle Ring
(50008, 40497, 0, 1, 1, 1, 1, 0, 0, 0), -- Black Ice
(50008, 40489, 0, 1, 1, 1, 1, 0, 0, 0), -- Greatstaff of the Nexus
(50008, 40526, 0, 1, 1, 1, 1, 0, 0, 0), -- Gown of the Spell-Weaver
(50008, 40511, 0, 1, 1, 1, 1, 0, 0, 0), -- Focusing Energy Epaulets
(50008, 40475, 0, 1, 1, 1, 1, 0, 0, 0), -- Barricade of Eternity
(50008, 40488, 0, 1, 1, 1, 1, 0, 0, 0), -- Ice Spire Scepter
(50008, 40491, 0, 1, 1, 1, 1, 0, 0, 0), -- Hailstorm
(50008, 40519, 0, 1, 1, 1, 1, 0, 0, 0), -- Footsteps of Malygos
(50008, 40486, 0, 1, 1, 1, 1, 0, 0, 0); -- Necklace of the Glittering Chamber

DELETE FROM reference_loot_template WHERE entry = 50009;
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2) VALUES
(50009, 40592, 0, 1, 1, 1, 1, 0, 0, 0), -- Boots of Healing Energies
(50009, 40566, 0, 1, 1, 1, 1, 0, 0, 0), -- Unravelling Strands of Sanity
(50009, 40194, 0, 1, 1, 1, 1, 0, 0, 0), -- Blanketing Robes of Snow
(50009, 40543, 0, 1, 1, 1, 1, 0, 0, 0), -- Blue Aspect Helm
(50009, 40590, 0, 1, 1, 1, 1, 0, 0, 0), -- Elevated Lair Pauldrons
(50009, 40560, 0, 1, 1, 1, 1, 0, 0, 0), -- Leggings of the Wanton Spellcaster
(50009, 40589, 0, 1, 1, 1, 1, 0, 0, 0), -- Legplates of Sovereignty
(50009, 40555, 0, 1, 1, 1, 1, 0, 0, 0), -- Mantle of Dissemination
(50009, 40591, 0, 1, 1, 1, 1, 0, 0, 0), -- Melancholy Sabatons
(50009, 40594, 0, 1, 1, 1, 1, 0, 0, 0), -- Spaulders of Catatonia
(50009, 40588, 0, 1, 1, 1, 1, 0, 0, 0), -- Tunic of the Artifact Guardian
(50009, 40549, 0, 1, 1, 1, 1, 0, 0, 0), -- Boots of the Renewed Flight
(50009, 40539, 0, 1, 1, 1, 1, 0, 0, 0), -- Chestguard of the Recluse
(50009, 40541, 0, 1, 1, 1, 1, 0, 0, 0), -- Frosted Adroit Handguards
(50009, 40562, 0, 1, 1, 1, 1, 0, 0, 0), -- Hood of Rationality
(50009, 40561, 0, 1, 1, 1, 1, 0, 0, 0), -- Leash of Heedless Magic
(50009, 40532, 0, 1, 1, 1, 1, 0, 0, 0), -- Living Ice Crystals
(50009, 40531, 0, 1, 1, 1, 1, 0, 0, 0), -- Mark of Norgannon
(50009, 40564, 0, 1, 1, 1, 1, 0, 0, 0), -- Winter Spectacle Gloves
(50009, 40558, 0, 1, 1, 1, 1, 0, 0, 0); -- Arcanic Tramplers

DELETE FROM gameobject_loot_template WHERE entry IN (26094, 26097);
INSERT INTO gameobject_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2) VALUES
(26094, 40752, 100, 1, 0, 2, 2, 0, 0, 0), -- Emblem of Heroism x2
(26094, 	1, 100, 1, 0, -50008, 2, 0, 0, 0), -- 2 items ilevel 213
(26094, 44650, 100, 1, 0, 1, 1, 9,  13384, 0), -- Quest item, Judgement at the Eye of Eternity
(26094, 43953, 1, 1, 0, 1, 1, 0, 0, 0), -- Reins of the Blue Drake 	
-- End of 10m Malygos loot

(26097, 40753, 100, 1, 0, 2, 2, 0, 0, 0), -- Emblem of Valor x2
(26097, 	1, 100, 1, 0, -50009, 4, 0, 0, 0), -- 4 items ilevel 226
(26097, 44651, 100, 1, 0, 1, 1, 9, 13385, 0), -- Quest item, Heroic Judgement at the Eye of Eternity
(26097, 43952, 1, 1, 0, 1, 1, 0, 0, 0); -- Reins of the Azure Drake
-- End of 25m Malygos loot

-- Fix Malygos and his adds' damage
UPDATE creature_template SET mindmg = 3684, maxdmg = 4329, dmg_multiplier = 7.5, mechanic_immune_mask = 1072918979 WHERE entry = 30245; -- Nexus Lord
UPDATE creature_template SET mindmg = 3684, maxdmg = 4329, dmg_multiplier = 13,  mechanic_immune_mask = 1072918979 WHERE entry = 31750; -- Nexus Lord (1)
UPDATE creature_template SET mechanic_immune_mask = 1072918979 WHERE entry IN (30249, 31751);
UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry IN (31750, 31751);

-- Create entry for Heroic Malygos
DELETE FROM creature_template WHERE entry = 50000;
INSERT INTO creature_template (entry, difficulty_entry_1, difficulty_entry_2, difficulty_entry_3, KillCredit1, KillCredit2, modelid1, modelid2, 
modelid3, modelid4, name, subname, IconName, gossip_menu_id, minlevel, maxlevel, exp, faction_A, faction_H, npcflag, speed_walk, speed_run, scale, 
rank, mindmg, maxdmg, dmgschool, attackpower, dmg_multiplier, baseattacktime, rangeattacktime, unit_class, unit_flags, dynamicflags, family, 
trainer_type, trainer_spell, trainer_class, trainer_race, minrangedmg, maxrangedmg, rangedattackpower, type, type_flags, lootid, pickpocketloot, 
skinloot, resistance1, resistance2, resistance3, resistance4, resistance5, resistance6, spell1, spell2, spell3, spell4, spell5, spell6, spell7, 
spell8, PetSpellDataId, VehicleId, mingold, maxgold, AIName, MovementType, InhabitType, Health_mod, Mana_mod, Armor_mod, RacialLeader, questItem1, 
questItem2, questItem3, questItem4, questItem5, questItem6, movementId, RegenHealth, equipment_id, mechanic_immune_mask, flags_extra, ScriptName, WDBVerified) VALUES 
(50000, 0, 0, 0, 0, 0, 26752, 0, 0, 0, 'Malygos', '', '', 0, 83, 83, 2, 16, 16, 0, 1, 1.14286, 1, 3, 496, 674, 0, 783, 35, 2000, 0, 2, 64, 8, 0, 0, 0, 0, 0, 365, 529, 98, 2, 108, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 500, 50, 1, 0, 44650, 0, 0, 0, 0, 0, 227, 1, 0, 0, 1, 'boss_malygos', 1);

UPDATE creature_template SET Health_mod = 1400, questItem1 = 44651, mechanic_immune_mask = 617299803, ScriptName = '', WDBVerified = 1 WHERE entry = 50000;

UPDATE creature_template SET mindmg = 4602, maxdmg = 5502, dmg_multiplier = 7.5, difficulty_entry_1 = 50000, mechanic_immune_mask = 617299803 WHERE entry = 28859;
UPDATE creature_template SET mindmg = 4602, maxdmg = 5502, dmg_multiplier = 13 WHERE entry = 50000;

UPDATE creature_template SET flags_extra = flags_extra | 1 WHERE entry IN (28859, 50000);
