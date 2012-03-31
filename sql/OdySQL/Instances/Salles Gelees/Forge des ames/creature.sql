UPDATE creature_template SET `faction_A` = 31, `faction_H` = 31 WHERE `entry` = 211001;
UPDATE creature_template SET `faction_A` = 190, `faction_H` = 190 WHERE `entry` = 1488101;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3647801;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3649701;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3649901;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3650201;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 0;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3651601;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3652201;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16, flags_extra = 2 WHERE `entry` = 3655101;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3656401;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3662001;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 3666601;
UPDATE creature_template SET `faction_A` = 16, `faction_H` = 16 WHERE `entry` = 0;
UPDATE creature_template SET `faction_A` = 35, `faction_H` = 35 WHERE `entry` = 3709401;
UPDATE creature_template SET `faction_A` = 1770, `faction_H` = 1770 WHERE `entry` = 3758301;
UPDATE creature_template SET `faction_A` = 714, `faction_H` = 714 WHERE `entry` = 3759601;
UPDATE creature_template SET `faction_A` = 1770, `faction_H` = 1770 WHERE `entry` = 3777901;
UPDATE creature_template SET ScriptName = "mob_well_of_souls" WHERE entry = 36536 ;
UPDATE creature_template SET flags_extra = 2 WHERE entry = '36551';
-- Add missing creature_template needed for Devourer of Souls spells Unleashed Souls and Wailing Souls
DELETE FROM `creature_template` WHERE `entry` IN (36503,36504);
INSERT INTO `creature_template` (`entry`,`name`,`modelid1`,`faction_A`,`faction_H`,`unit_class`) VALUES
(36503, 'Devourer of Sorrow',30149,16,16,1),
(36504, 'Devourer of Desire',30150,16,16,1);
-- Add model_info (same radius and reach as Devourer of Souls)
DELETE FROM `creature_model_info` WHERE `modelid` IN(30149,30150);
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`) VALUES
(30149,0.248,6.4,0),
(30150,0.248,6.4,0);

DELETE FROM achievement_criteria_data WHERE criteria_id IN (4522, 4523);
UPDATE `achievement_criteria_data` SET `type`='12', `value1`='1' WHERE (`criteria_id`='4519');
UPDATE `creature_template` SET `speed_walk`='0.6', `scale`='1.5' WHERE `entry` IN (36535, 3653501);
DELETE FROM creature_loot_template WHERE entry IN (36497, 36502) AND item IN (47241, 45624);
UPDATE creature_loot_template SET item = 47241 WHERE item = 45624 and entry IN (3649701, 3650201);