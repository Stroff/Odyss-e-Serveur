
UPDATE `creature_template` SET `AIName`='', `Scriptname`='boss_lich_king_hr' WHERE `entry` IN (37226);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_jaina_and_sylvana_HRextro' WHERE `entry` IN (36955, 37554);

UPDATE `gameobject_template` SET `faction` = '114' WHERE `entry` IN (197341, 201976);
UPDATE `gameobject_template` SET `faction`='1375' WHERE `entry` IN (197341, 202302, 201385, 201596);

UPDATE `creature_template` SET `speed_walk`='1.5', `speed_run`='2.0' WHERE `entry` IN (37226);


UPDATE `creature_template` SET `scale`='0.8', `equipment_id`='1221' WHERE `entry` IN (37221, 36955);
UPDATE `creature_template` SET `equipment_id`='1290' WHERE `entry` IN (37223, 37554);
UPDATE `creature_template` SET `equipment_id`='0' WHERE `entry`=36954;
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_lich_king_hr' WHERE `entry` IN (36954);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_jaina_hor_part1' WHERE `entry` IN (37221);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_sylvanas_hor_part1' WHERE `entry` IN (37223);
UPDATE `creature_template` SET `scale`='1' WHERE `entry` IN (37223);
UPDATE `creature_template` SET `scale`='0.8' WHERE `entry` IN (36658, 37225, 37223, 37226, 37554);
UPDATE `creature_template` SET `unit_flags`='768', `type_flags`='268435564' WHERE `entry` IN (38177, 38176, 38173, 38172, 38567, 38175);
UPDATE `creature_template` SET `AIName`='', `Scriptname`='npc_frostworn_general' WHERE `entry`=36723;

DELETE FROM gameobject WHERE id = 201596 AND map = 668;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES (NULL, 201596, 668, 1, 128, 5275.28, 1694.23, 786.147, 0.981225, 0, 0, 0.471166, 0.882044, 25, 0, 1);
DELETE FROM creature WHERE id IN (36955, 37554);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (1353450, 37554, 668, 3, 1, 0, 0, 5547.27, 2256.95, 733.011, 0.835987, 7200, 0, 0, 252000, 881400, 0, 0);

DELETE from `creature` WHERE `id`=37226;
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (1353440, 37226, 668, 3, 1, 0, 0, 5551.29, 2261.33, 733.012, 4.0452, 604800, 0, 0, 27890000, 0, 0, 0);


UPDATE `creature_template` SET `modelid1` = 11686, `modelid2` = 11686, `modelid3` = 11686, `modelid4` = 11686 WHERE `entry` IN (37014,37704);
UPDATE `gameobject_template` SET `faction` = '114',`data0` = '0' WHERE `gameobject_template`.`entry` IN (197341,197342,197343);
UPDATE `gameobject` SET `state` = '1' WHERE `id` IN (197342);
UPDATE `gameobject` SET `state` = '0' WHERE `id` IN (197343);
UPDATE `gameobject` SET `state` = '0' WHERE (`id`='201976');
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`, `WDBVerified`) VALUES (197343, 0, 9124, 'Doodad_IceCrown_Door_03', '', '', '', 114, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 12340);
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`, `WDBVerified`) VALUES (197342, 0, 9124, 'Doodad_IceCrown_Door_02', '', '', '', 114, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 12340);
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`, `WDBVerified`) VALUES (197341, 0, 9124, 'Impenetrable Door', '', '', '', 114, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 12340);
REPLACE INTO `gameobject` VALUES ('150294', '197341', '668', '3', '1', '5358.96', '2058.75', '707.724', '0.810935', '0', '0', '-0.370856', '0.928691', '6000', '100', '1');
REPLACE INTO `gameobject` VALUES ('150210', '197342', '668', '3', '1', '5520.77', '2229.04', '733.04', '0.810935', '0', '0', '-0.370856', '0.928691', '6000', '100', '1');
REPLACE INTO `gameobject` VALUES ('150221', '197343', '668', '3', '1', '5582.81', '2230.62', '733.04', '-0.75986', '0', '0', '-0.370856', '0.928691', '6000', '100', '0');
REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '70464', '18', '1', '36881');
REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '69708', '18', '1', '37226');
REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '70194', '18', '1', '37226');
REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '69784', '18', '1', '37014');

REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '69784', '18', '1', '37014');
REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '70224', '18', '1', '37014');
REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '70225', '18', '1', '37014');

REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '69431', '18', '1', '37497');
REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '69431', '18', '1', '37496');
REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '69431', '18', '1', '37496');

REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '69431', '18', '1', '37588');
REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '69431', '18', '1', '37584');
REPLACE INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES ('13', '69431', '18', '1', '37587');

DELETE FROM script_waypoint WHERE entry=36955;
DELETE FROM script_waypoint WHERE entry=37226;
DELETE FROM script_waypoint WHERE entry=37554;

INSERT INTO script_waypoint VALUES
-- Jaina

   (36955, 0, 5587.682,2228.586,733.011, 0, 'WP1'),
   (36955, 1, 5600.715,2209.058,731.618, 0, 'WP2'),
   (36955, 2, 5606.417,2193.029,731.129, 0, 'WP3'),
   (36955, 3, 5598.562,2167.806,730.918, 0, 'WP4 - Summon IceWall 01'), 
   (36955, 4, 5556.436,2099.827,731.827, 0, 'WP5 - Spell Channel'),
   (36955, 5, 5543.498,2071.234,731.702, 0, 'WP6'),
   (36955, 6, 5528.969,2036.121,731.407, 0, 'WP7'),
   (36955, 7, 5512.045,1996.702,735.122, 0, 'WP8'),
   (36955, 8, 5504.490,1988.789,735.886, 0, 'WP9 - Spell Channel'),
   (36955, 9, 5489.645,1966.389,737.653, 0, 'WP10'),
   (36955, 10, 5475.517,1943.176,741.146, 0, 'WP11'),
   (36955, 11, 5466.930,1926.049,743.536, 0, 'WP12'),
   (36955, 12, 5445.157,1894.955,748.757, 0, 'WP13 - Spell Channel'),
   (36955, 13, 5425.907,1869.708,753.237, 0, 'WP14'),
   (36955, 14, 5405.118,1833.937,757.486, 0, 'WP15'),
   (36955, 15, 5370.324,1799.375,761.007, 0, 'WP16'),
   (36955, 16, 5335.422,1766.951,767.635, 0, 'WP17 - Spell Channel'),
   (36955, 17, 5311.438,1739.390,774.165, 0, 'WP18'),
   (36955, 18, 5283.589,1703.755,784.176, 0, 'WP19'),
   (36955, 19, 5260.400,1677.775,784.301, 3000, 'WP20'),
   (36955, 20, 5262.439,1680.410,784.294, 0, 'WP21'),
   (36955, 21, 5260.400,1677.775,784.301, 0, 'WP22'),

-- Sylvana

   (37554, 0, 5587.682,2228.586,733.011, 0, 'WP1'),
   (37554, 1, 5600.715,2209.058,731.618, 0, 'WP2'),
   (37554, 2, 5606.417,2193.029,731.129, 0, 'WP3'),
   (37554, 3, 5598.562,2167.806,730.918, 0, 'WP4 - Summon IceWall 01'), 
   (37554, 4, 5556.436,2099.827,731.827, 0, 'WP5 - Spell Channel'),
   (37554, 5, 5543.498,2071.234,731.702, 0, 'WP6'),
   (37554, 6, 5528.969,2036.121,731.407, 0, 'WP7'),
   (37554, 7, 5512.045,1996.702,735.122, 0, 'WP8'),
   (37554, 8, 5504.490,1988.789,735.886, 0, 'WP9 - Spell Channel'),
   (37554, 9, 5489.645,1966.389,737.653, 0, 'WP10'),
   (37554, 10, 5475.517,1943.176,741.146, 0, 'WP11'),
   (37554, 11, 5466.930,1926.049,743.536, 0, 'WP12'),
   (37554, 12, 5445.157,1894.955,748.757, 0, 'WP13 - Spell Channel'),
   (37554, 13, 5425.907,1869.708,753.237, 0, 'WP14'),
   (37554, 14, 5405.118,1833.937,757.486, 0, 'WP15'),
   (37554, 15, 5370.324,1799.375,761.007, 0, 'WP16'),
   (37554, 16, 5335.422,1766.951,767.635, 0, 'WP17 - Spell Channel'),
   (37554, 17, 5311.438,1739.390,774.165, 0, 'WP18'),
   (37554, 18, 5283.589,1703.755,784.176, 0, 'WP19'),
   (37554, 19, 5260.400,1677.775,784.301, 3000, 'WP20'),
   (37554, 20, 5262.439,1680.410,784.294, 0, 'WP21'),
   (37554, 21, 5260.400,1677.775,784.301, 0, 'WP22'),

-- Lich King

   (37226, 0, 5577.187,2236.003,733.012, 0, 'WP1'),
   (37226, 1, 5587.682,2228.586,733.011, 0, 'WP2'),
   (37226, 2, 5600.715,2209.058,731.618, 0, 'WP3'),
   (37226, 3, 5606.417,2193.029,731.129, 0, 'WP4'),
   (37226, 4, 5598.562,2167.806,730.918, 0, 'WP5'), 
   (37226, 5, 5559.218,2106.802,731.229, 0, 'WP6'),
   (37226, 6, 5543.498,2071.234,731.702, 0, 'WP7'),
   (37226, 7, 5528.969,2036.121,731.407, 0, 'WP8'),
   (37226, 8, 5512.045,1996.702,735.122, 0, 'WP9'),
   (37226, 9, 5504.490,1988.789,735.886, 0, 'WP10'),

   (37226, 10, 5489.645,1966.389,737.653, 0, 'WP10'),
   (37226, 11, 5475.517,1943.176,741.146, 0, 'WP11'),
   (37226, 12, 5466.930,1926.049,743.536, 0, 'WP12'),
   (37226, 13, 5445.157,1894.955,748.757, 0, 'WP13'),
   (37226, 14, 5425.907,1869.708,753.237, 0, 'WP14'),
   (37226, 15, 5405.118,1833.937,757.486, 0, 'WP15'),
   (37226, 16, 5370.324,1799.375,761.007, 0, 'WP16'),
   (37226, 17, 5335.422,1766.951,767.635, 0, 'WP17'),
   (37226, 18, 5311.438,1739.390,774.165, 0, 'WP18'),
   (37226, 19, 5283.589,1703.755,784.176, 0, 'WP19'),
   (37226, 20, 5278.694,1697.912,785.692, 0, 'WP20'),
   (37226, 21, 5283.589,1703.755,784.176, 0, 'WP19');

DELETE FROM creature WHERE guid = '202294';
DELETE FROM creature WHERE guid = '202301';
DELETE FROM creature WHERE id = '37704' AND map = '668';
REPLACE INTO `creature_equip_template` VALUES ('38112', '50249', '49777', '0'); #Falric
UPDATE `creature_template` SET `equipment_id`='38112' WHERE `entry` IN (38112);
REPLACE INTO `creature_equip_template` VALUES ('38113', '50248', '50248', '0'); #Marwyn
UPDATE `creature_template` SET `equipment_id`='38113' WHERE `entry` IN (38113);
UPDATE `gameobject_template` SET `faction` = '114' WHERE `entry` IN (201976);
UPDATE `gameobject_template` SET `faction`='1375' WHERE `entry` IN (202302, 201385, 201596);
UPDATE `gameobject_template` SET `faction`='114', flags = '4' WHERE `entry` IN (201385, 201596);
-- Falric Marwyn
DELETE FROM creature WHERE id IN(38112,38113) and map = '668';
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (NULL, 38112, 668, 3, 1, 0, 0, 5276.81, 2037.45, 709.32, 5.58779, 604800, 0, 0, 377468, 0, 0, 0);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES (NULL, 38113, 668, 3, 1, 0, 0, 5341.72, 1975.74, 709.32, 2.40694, 604800, 0, 0, 539240, 0, 0, 0);
DELETE FROM gameobject WHERE id IN(201596, 202079) and map = '668';
-- Chute Pierre
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES (NULL, 201596, 668, 1, 128, 5275.28, 1694.23, 786.147, 0.981225, 0, 0, 0.471166, 0.882044, 25, 0, 1);
-- Dalaran portal (override)
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(972565, 202079, 668, 3, 65535, 5250.959961, 1639.359985, 784.302, 0, 0, 0, 0, 0, -604800, 100, 1);
UPDATE `creature_template` SET `flags_extra`='2' WHERE (`entry`='37014') ;
UPDATE `creature_template` SET `Health_mod`='100' WHERE (`entry`='37014') LIMIT 1;

DELETE FROM creature WHERE id = 36723;
INSERT INTO `creature` VALUES (NULL, '36723', '668', '3', '1', '0', '0', '5413.94', '2116.69', '707.695', '3.99147', '86400', '0', '0', '315000', '0', '0', '0');

UPDATE `creature_template` SET `faction_A`='16', `faction_H`='16' WHERE `entry` IN (36723);

UPDATE `creature_template` SET `faction_A`='16', `faction_H`='16', Scriptname = 'ghoul_hor' WHERE `entry` IN (36940);
UPDATE `creature_template` SET `faction_A`='16', `faction_H`='16', Scriptname = 'docteur_hor' WHERE `entry` IN (36941);
UPDATE `creature_template` SET `faction_A`='16', `faction_H`='16', Scriptname = 'abon_hor' WHERE `entry` IN (37069);

DELETE FROM gameobject_loot_template WHERE entry IN (201710, 202336);
DELETE FROM reference_loot_template WHERE entry IN (2017100, 2023360);

/* Normal */
UPDATE gameobject_template SET data1 = '201710' WHERE entry IN (202212, 201710);

INSERT INTO `gameobject_loot_template` VALUES ('201710', '1', '100', '1', '0', '-2017100', '2');
INSERT INTO `gameobject_loot_template` VALUES ('201710', '47241', '100', '1', '0', '1', '1');

INSERT INTO `reference_loot_template` VALUES ('2017100', '49849', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49846', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49845', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49844', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49840', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49839', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49851', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49843', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49842', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49841', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49848', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2017100', '49847', '0', '1', '1', '1', '1');

/* Héro */
UPDATE gameobject_template SET data1 = '201710' WHERE entry IN (202336, 202337);

INSERT INTO `gameobject_loot_template` VALUES ('202336', '1', '100', '1', '0', '-2023360', '2');
INSERT INTO `gameobject_loot_template` VALUES ('202336', '47241', '100', '1', '0', '1', '1');
INSERT INTO `gameobject_loot_template` VALUES ('202336', '43102', '100', '1', '0', '1', '1');

INSERT INTO `reference_loot_template` VALUES ('2023360', '50314', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50313', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50312', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50311', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50310', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50309', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50308', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50306', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50305', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50304', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50303', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('2023360', '50302', '0', '1', '1', '1', '1');


-- Captains chest (override)
DELETE FROM `gameobject` WHERE `id` IN (202212,201710,202337,202336) AND map = '668';
UPDATE `gameobject_template` SET `flags` = 0 WHERE `gameobject_template`.`entry` IN (202212,201710,202337,202336);
INSERT INTO `gameobject` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `position_x`, `position_y`, `position_z`, `orientation`, `rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`) VALUES
(972561, 202212, 668, 1, 65535, 5199.29, 1573.8, 819.999, 0.508337, 0, 0, 0, 0, -604800, 100, 1),
(972562, 201710, 668, 1, 65535, 5199.29, 1573.8, 819.999, 0.508337, 0, 0, 0, 0, -604800, 100, 1),
(972563, 202337, 668, 2, 65535, 5199.29, 1573.8, 819.999, 0.508337, 0, 0, 0, 0, -604800, 100, 1),
(972564, 202336, 668, 2, 65535, 5199.29, 1573.8, 819.999, 0.508337, 0, 0, 0, 0, -604800, 100, 1);
-- Dalaran portal (override)
DELETE FROM `gameobject` WHERE `id` = '202079' AND map = '668';

UPDATE `gameobject_template` SET `type`='5' WHERE `entry` IN (201709, 202211);
REPLACE INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (72396, -72395, 1, 'Desespoir Remove les autres desespoir =)');
REPLACE INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (72397, -72396, 1, 'Desespoir Remove les autres desespoir =)');
REPLACE INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (72397, -72395, 1, 'Desespoir Remove les autres desespoir =)');
REPLACE INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (72391, -72390, 1, 'Desespoir Remove les autres desespoir =)');
REPLACE INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (72393, -72391, 1, 'Desespoir Remove les autres desespoir =)');
REPLACE INTO `spell_linked_spell` (`spell_trigger`, `spell_effect`, `type`, `comment`)
VALUES (72393, -72390, 1, 'Desespoir Remove les autres desespoir =)');
REPLACE INTO `creature_equip_template` (`entry`, `equipentry1`, `equipentry2`, `equipentry3`) VALUES ('101011', '1905', '0', '50817');
UPDATE `creature_template` SET `equipment_id`='101011' WHERE `entry` IN(38176, 3817601);
REPLACE INTO `creature_equip_template` (`entry`, `equipentry1`, `equipentry2`, `equipentry3`) VALUES ('101012', '52007', '52008', '0');
UPDATE `creature_template` SET `equipment_id`='101012' WHERE `entry` IN(36723, 3672301);
UPDATE `creature_template` SET `equipment_id`='1218' WHERE `entry` IN(38177, 3817701);
UPDATE `creature_template` SET `equipment_id`='107' WHERE `entry` IN(38173, 3817301);
UPDATE `creature_template` SET `equipment_id`='14' WHERE `entry` IN (38175, 3817501);
UPDATE `creature_template` SET  `AIName`= '', Scriptname = 'npc_reflection', `faction_A`='14', `faction_H`='14', InhabitType = 4 WHERE `entry` IN (37068);
UPDATE creature_template SET InhabitType = '4' WHERE entry IN (3706801);
REPLACE INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
('72390', 'spell_desespoir'),
('72391', 'spell_desespoir'),
('72393', 'spell_desespoir'),
('72395', 'spell_desespoir'),
('72396', 'spell_desespoir'),
('72397', 'spell_desespoir');
REPLACE INTO `spell_rank` (`first_spell_id`, `spell_id`, `rank`) VALUES 
('72390', '72390', '1'),
('72390', '72391', '2'),
('72390', '72393', '3'),
('72395', '72395', '1'),
('72395', '72396', '2'),
('72395', '72397', '3');

UPDATE gameobject_template SET type = '11' WHERE entry IN (201598, 201599);
UPDATE `creature_template` SET `npcflag`='3' WHERE `entry` IN(37223,37221);
UPDATE creature_loot_template SET item = 47241 WHERE item = 45624 and entry IN (38113, 3811301, 38112, 3811201);
UPDATE `quest_template` SET `RewItemId1`='47241' WHERE `RewItemId1`= 45624 AND entry IN (24710, 24712, 24500, 24802);
UPDATE creature_template SET Scriptname = 'npc_reln' WHERE entry IN (37779, 37582);
UPDATE `creature_template` SET `flags_extra`='1' WHERE entry IN (36723,3672301);