-- instance
UPDATE `instance_template` SET `script`='instance_trial_of_the_crusader' WHERE `map`=649;
DELETE FROM `creature` WHERE `map` = 649 AND `id` IN 
(34797,34796,34799,35144,34780,34460,34463,34461,34471,34475,34472,34453,34455,34458,34454,34451,34456,34497,34496,34467,35465,34468,35610,34473,34474,34441,34449,34448,34450,34606, 34605, 34607);

-- announcers
UPDATE `creature_template` SET `npcflag`=1, `scriptname`='npc_toc_announcer' WHERE `entry`=34816;
DELETE FROM `creature` WHERE `map` = 649 AND `id` = 35766;

UPDATE `creature_template` SET `scriptname`='boss_lich_king_toc' WHERE `entry`=35877;
UPDATE `creature_template` SET  `faction_A`= 1770, `faction_H` = 1770,  `scriptname`='npc_fizzlebang_toc' WHERE `entry`=35458;
UPDATE `creature_template` SET `scriptname`='npc_tirion_toc' WHERE `entry`=34996;
UPDATE `creature_template` SET `scriptname`='npc_garrosh_toc' WHERE `entry`=34995;
UPDATE `creature_template` SET `scriptname`='npc_rinn_toc' WHERE `entry`=34990;

-- Grand crusaders
UPDATE `creature_template` SET `scriptname`='mob_toc_warrior', `AIName` ='' WHERE `entry` IN (34475,34453);
UPDATE `creature_template` SET `scriptname`='mob_toc_mage', `AIName` ='' WHERE `entry` IN (34468,34449);
UPDATE `creature_template` SET `scriptname`='mob_toc_shaman', `AIName` ='' WHERE `entry` IN (34463,34455);
UPDATE `creature_template` SET `scriptname`='mob_toc_enh_shaman', `AIName` ='' WHERE `entry` IN (34470,34444);
UPDATE `creature_template` SET `scriptname`='mob_toc_hunter', `AIName` ='' WHERE `entry` IN (34467,34448);
UPDATE `creature_template` SET `scriptname`='mob_toc_rogue', `AIName` ='' WHERE `entry` IN (34472,34454);
UPDATE `creature_template` SET `scriptname`='mob_toc_priest', `AIName` ='' WHERE `entry` IN (34466,34456);
UPDATE `creature_template` SET `scriptname`='mob_toc_shadow_priest', `AIName` ='' WHERE `entry` IN (34473,34441);
UPDATE `creature_template` SET `scriptname`='mob_toc_dk', `AIName` ='' WHERE `entry` IN (34461,34458);
UPDATE `creature_template` SET `scriptname`='mob_toc_paladin', `AIName` ='' WHERE `entry` IN (34465,34445);
UPDATE `creature_template` SET `scriptname`='mob_toc_retro_paladin', `AIName` ='' WHERE `entry` IN (34471,34456);
UPDATE `creature_template` SET `scriptname`='mob_toc_druid', `AIName` ='' WHERE `entry` IN (34460,34451);
UPDATE `creature_template` SET `scriptname`='mob_toc_boomkin', `AIName` ='' WHERE `entry` IN (34469,34459);
UPDATE `creature_template` SET `scriptname`='mob_toc_warlock' WHERE `entry` IN (34474,34450);

UPDATE `creature_template` SET `scriptname`='mob_toc_pet_warlock', faction_A = '16', faction_H = 16, `AIName` ='' WHERE `entry` IN (35465);
UPDATE `creature_template` SET `scriptname`='mob_toc_pet_hunter', faction_A = '16', faction_H = 16, `AIName` ='' WHERE `entry` IN (35610);

UPDATE `creature_template` SET `lootid`= 0 WHERE  `entry` IN
(34460,34463,34461,34471,34475,34472,34453,34455,34458,34454,34451,34456,34467,35465,34468,35610,34473,34474,34441,34449,34448,34450);
UPDATE `creature_template` SET `lootid`= 0 WHERE  `entry` IN
(12266,12209,12212,12281,12190,12284,12269,12272,12229,12187,12091,12088,12169,12103,12106,12112,12166,12163,12175,12183,12303,12300);
UPDATE `creature_template` SET `lootid`= 0 WHERE  `entry` IN
(12267,12210,12213,12282,12191,12285,12270,12273,12230,12188,12092,12089,12170,12104,12107,12113,12167,12164,12181,12184,12304,12301);
UPDATE `creature_template` SET `lootid`= 0 WHERE  `entry` IN
(12268,12211,12214,12283,12192,12286,12271,12274,12231,12189,12093,12090,12171,12105,12108,12114,12168,12165,12182,12185,12305,12302);

-- N10
DELETE FROM `creature_loot_template` WHERE `entry` IN 
(34460,34463,34461,34471,34475,34472,34453,34455,34458,34454,34451,34456,34467,35465,34468,35610,34473,34474,34441,34449,34448,34450);
-- H10
DELETE FROM `creature_loot_template` WHERE `entry` IN 
(12266,12209,12212,12281,12190,12284,12269,12272,12229,12187,12091,12088,12169,12103,12106,12112,12166,12163,12175,12183,12303,12300);
-- N25
DELETE FROM `creature_loot_template` WHERE `entry` IN 
(12267,12210,12213,12282,12191,12285,12270,12273,12230,12188,12092,12089,12170,12104,12107,12113,12167,12164,12181,12184,12304,12301);
-- H25
DELETE FROM `creature_loot_template` WHERE `entry` IN 
(12268,12211,12214,12283,12192,12286,12271,12274,12231,12189,12093,12090,12171,12105,12108,12114,12168,12165,12182,12185,12305,12302);

-- Nortrend beasts
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (34796, 34799, 35144, 34797);
UPDATE `creature_template` SET `scriptname`='boss_gormok', `AIName` ='' WHERE `entry`=34796;
UPDATE `creature_template` SET `scriptname`='mob_snobold_vassal', `AIName` ='' WHERE `entry`=34800;

UPDATE `creature_template` SET `scriptname`='boss_dreadscale', `AIName` ='' WHERE `entry`=34799;
UPDATE `creature_template` SET `scriptname`='boss_acidmaw', `AIName` ='' WHERE `entry`=35144;
UPDATE `creature_template` SET `scriptname`='mob_slime_pool', `minlevel` = 80, `maxlevel` = 80, `AIName` ='', `faction_A`= 14, `faction_H` = 14, `modelid1` = 12349, `modelid3` = 12349 WHERE `entry` = 35176;
-- Model id for slime_pool need change!

UPDATE `creature_template` SET `scriptname`='boss_icehowl', `AIName` ='' WHERE `entry`=34797;

UPDATE `creature_template` SET `lootid`= 0 WHERE  `entry` IN (34796,34799,35144);
DELETE FROM `creature_loot_template`  WHERE  `entry` IN (34796,34799,35144);

-- Jaraxxus
UPDATE `creature_template` SET `scriptname`='boss_jaraxxus', `AIName` ='' WHERE `entry`= 34780;
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (34780, 34784, 34813, 34815, 34825, 34826);
UPDATE `creature_template` SET `scriptname`='mob_legion_flame', `minlevel` = 82, `maxlevel` = 82, `modelid1` = 11686, `modelid2` = 11686, `modelid3` = 11686, `modelid4` = 11686, `AIName` ='', `faction_A`= 14, `faction_H` = 14 WHERE `entry` = 34784;
UPDATE `creature_template` SET `scriptname`='mob_infernal_volcano', `AIName` ='' WHERE `entry` = 34813;
UPDATE `creature_template` SET `scriptname`='mob_fel_infernal', `AIName` ='' WHERE `entry` = 34815;
UPDATE `creature_template` SET `scriptname`='mob_nether_portal', `AIName` ='' WHERE `entry` = 34825;
UPDATE `creature_template` SET `scriptname`='mob_mistress_of_pain', `AIName` ='' WHERE `entry` = 34826;

-- Valkiries
UPDATE `creature_template` SET `scriptname` = 'boss_fjola', `AIName` ='' WHERE `entry`=34497;
UPDATE `creature_template` SET `scriptname` = 'boss_eydis', `AIName` ='' WHERE `entry`=34496;
UPDATE `creature_template` SET `InhabitType`='4' WHERE `entry` IN(34497, 34496, 3449701, 3449702, 3449703, 3449601, 3449602, 3449603);
DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (34497, 34496, 34568, 34567);
UPDATE `creature_template` SET `npcflag`=1, `scriptname`='mob_light_essence', `AIName` ='' WHERE entry = 34568;
UPDATE `creature_template` SET `npcflag`=1, `scriptname`='mob_dark_essence', `AIName` ='' WHERE entry = 34567;
UPDATE `creature_template` SET `faction_A` = 14, `minlevel` = 82, `maxlevel` = 82,`faction_H` = 14, `AIName` ='', `scriptname`='mob_unleashed_dark' WHERE entry = 34628;
UPDATE `creature_template` SET `faction_A` = 14, `minlevel` = 82, `maxlevel` = 82,`faction_H` = 14, `AIName` ='', `scriptname`='mob_unleashed_light' WHERE entry = 34630;

-- Anub'arak
UPDATE `creature_template` SET `scriptname`='boss_anubarak_trial', `unit_flags` = 0, `AIName` ='' WHERE `entry`=34564;

DELETE FROM `creature_ai_scripts` WHERE `creature_id` IN (34606, 34605, 34607, 34564, 34660);
UPDATE `creature_template` SET `modelid1` = 25144, `modelid2` = 0, `modelid3` = 25144, `modelid4` = 0, `faction_A` = 14, `faction_H` = 14, `AIName` = '', `ScriptName` = 'mob_frost_sphere' WHERE `entry` = 34606;
UPDATE `creature_template` SET `scriptname`='mob_swarm_scarab', `AIName` ='' WHERE `entry`=34605;
UPDATE `creature_template` SET `scriptname`='mob_nerubian_borrower', `AIName` ='' WHERE `entry`=34607;
UPDATE `creature_template` SET `scriptname`='mob_anubarak_spike', `faction_A` = 14, `minlevel` = 80, `maxlevel` = 80,`faction_H` = 14, `AIName` ='' WHERE `entry`=34660;
UPDATE `creature_template` SET `speed_walk`='0.8', `speed_run`='0.8' WHERE (`entry`='34660') LIMIT 1;
UPDATE creature_template SET `VehicleId` = '442' WHERE `entry` = '34796'; /* Gormok */
DELETE FROM `vehicle_accessory` where entry = '34796';
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`) VALUES ('34796', '34800', '0', '0', 'Gormok Frogh');
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`) VALUES ('34796', '34800', '1', '0', 'Gormok Frogh');
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`) VALUES ('34796', '34800', '2', '0', 'Gormok Frogh');
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`) VALUES ('34796', '34800', '3', '0', 'Gormok Frogh');
INSERT INTO `vehicle_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `hack_doublon`) VALUES ('34796', '34800', '0', '0', 'Gormok Frogh', '1');
UPDATE `creature_template` SET `unit_flags`='0' WHERE (`entry`='34800') LIMIT 1;
UPDATE `creature_template` SET `unit_flags`='0' WHERE (`entry`='3480001') LIMIT 1;
UPDATE `creature_template` SET `unit_flags`='0' WHERE (`entry`='3480002') LIMIT 1;
UPDATE `creature_template` SET `unit_flags`='0' WHERE (`entry`='3480003') LIMIT 1;
/*
446 34826
*/
UPDATE `creature_template` SET `flags_extra`='2' WHERE `entry` IN (35820, 35821, 17965);

UPDATE creature_template SET faction_A = '1801', faction_H = '1801' WHERE entry IN (34453, 34455, 34458, 34454, 34451, 34456, 34441, 34449, 34448, 34450);

UPDATE creature_template SET faction_A = '1802', faction_H = '1802' WHERE entry IN (34460, 34463, 34461, 34471, 34475, 34472, 34467, 34468, 34473, 34474);

UPDATE creature_template SET Scriptname = "mob_poussiere_scarab" where entry = '34862';
UPDATE `creature_template` SET `InhabitType`='3' WHERE entry IN (3460601, 3460602, 3460603, 34606);
REPLACE INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `ScriptName`, `WDBVerified`) VALUES ('195647', '0', '9044', 'Main Gate', '', '', '', '1375', '32', '1.48375', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '11723');
REPLACE INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `faction_A`, `faction_H`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `Health_mod`, `Mana_mod`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES ('3460604', '0', '0', '0', '0', '0', '1126', '25144', '0', '0', 'Frost Sphere', '', '', '0', '79', '80', '2', '14', '14', '0', '1', '1.14286', '1', '0', '422', '586', '0', '642', '1', '0', '0', '1', '32768', '8', '0', '0', '0', '0', '0', '345', '509', '103', '8', '64', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '0.238095', '1', '1', '0', '0', '0', '0', '0', '0', '0', '721', '1', '0', '0', '0', 'mob_frost_sphere_die', '1');

DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (12350,12358,12359,11779,11802,11780,11801);
UPDATE `gameobject_template` SET `type`='11' WHERE `entry` IN(201598, 201599);
UPDATE `gameobject_template` SET `type`='5' WHERE (`entry`='201709') LIMIT 1

DELETE FROM `custom_texts` WHERE `entry` IN (-2760029,-2760030,-2760031,-2760032,-2760033,-2760034,-2760035,-2760036);
INSERT INTO `custom_texts` (entry, content_default, sound, type, language, emote, comment) VALUES
(-2760029, "Lavette !", 16017, 1, 0, 0, "Faction Champions - killing an alliance player1"),
(-2760030, "Pitoyable !", 16018, 1, 0, 0, "Faction Champions - killing an alliance player2"),
(-2760031, "Surpassé.", 16019, 1, 0, 0, "Faction Champions - killing an alliance player3"),
(-2760032, "Lok'tar !", 16020, 1, 0, 0, "Faction Champions - killing an alliance player4"),
(-2760033, "HAH !", 16060, 1, 0, 0, "Faction Champions - killing an horde player1"),
(-2760034, "Aucun défi !", 16061, 1, 0, 0, "Faction Champions - killing an horde player2"),
(-2760035, "Incapable vermine.", 16062, 1, 0, 0, "Faction Champions - killing an horde player3"),
(-2760036, "C'est ça la crème de la Horde ?", 16063, 1, 0, 0, "Faction Champions - killing an horde player4");

DELETE from gameobject WHERE id IN (195631, 195632, 195633, 195635);