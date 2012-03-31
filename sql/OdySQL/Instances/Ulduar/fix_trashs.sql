-- Magma Rager
UPDATE `creature_template` SET `spell1` = 64773, `spell2` = 64746, `mingold` = 7100, `maxgold` = 7600, `AIName` = 'SmartAI' WHERE `entry` = 34086;
UPDATE `creature_template` SET `spell1` = 64773, `spell2` = 64746, `mingold` = 14200, `maxgold` = 15600 WHERE `entry` = 34201;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=34086);
INSERT INTO `smart_scripts` VALUES 
(34086, 0, 0, 0, 0, 0, 100, 0, 2000, 4000, 6000, 8000, 11, 64773, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,'Magma Rager - Cast Fire Blast'),
(34086, 0, 1, 0, 0, 0, 100, 0, 8000, 16000, 15000, 25000, 11, 64746, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,'Magma Rager - Cast Superheated winds');
UPDATE `creature_template` SET `unit_flags` = 33718790, modelid1 = 11686, modelid2 = 0, `spell1` = 64724, `AIName` = 'SmartAI' WHERE `entry` = 34194;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=34194);
INSERT INTO `smart_scripts` VALUES 
(34194, 0, 0, 0, 0, 0, 100, 0, 1000, 2000, 10000, 10000, 11, 64724, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0,'Superheated Winds');

-- Boomer XP-500
UPDATE `creature_template` SET `spell1` = 55714, `AIName` = 'SmartAI' WHERE `entry` = 34192;
UPDATE `creature_template` SET `spell1` = 55714 WHERE `entry` = 34216;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=34192);
INSERT INTO `smart_scripts` VALUES 
(34192, 0, 0, 0, 9, 0, 100, 0, 0, 2, 1000, 1000, 11, 55714, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,'Boomer XP-500 - Explode');

-- Twilight Shadowblade
UPDATE `creature_template` SET `spell1` = 63753, `mechanic_immune_mask` = 33554513,  `equipment_id` = 1862, `baseattacktime` = 1000, `mingold` = 7100, `maxgold` = 7600, `AIName` = 'SmartAI' WHERE `entry` = 33824;
UPDATE `creature_template` SET `spell1` = 63753, `mechanic_immune_mask` = 33554513,  `equipment_id` = 1862, `baseattacktime` = 1000, `mingold` = 7100, `maxgold` = 7600 WHERE `entry` = 33831;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=33824);
INSERT INTO `smart_scripts` VALUES 
(33824, 0, 0, 0, 0, 0, 100, 0, 6000, 8000, 12000, 16000, 11, 63753, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,'Twilight Shadowblade - Cast Fan of Knives');

-- Twilight Guardian
UPDATE `creature_template` SET `spell1` = 52719, `spell2` = 62317, `spell3` = 63757, `mechanic_immune_mask` = 33554513, `equipment_id` = 1852, `mingold` = 7100, `maxgold` = 7600, `AIName` = 'SmartAI' WHERE `entry` = 33822;
UPDATE `creature_template` SET `spell1` = 52719, `spell2` = 62317, `spell3` = 63757, `mechanic_immune_mask` = 33554513, `equipment_id` = 1852, `mingold` = 14200, `maxgold` = 15600 WHERE `entry` = 33828;
DELETE FROM `smart_scripts` WHERE (`entryorguid`=33822);
INSERT INTO `smart_scripts` VALUES 
(33822, 0, 0, 0, 0, 0, 100, 0, 6000, 10000, 8000, 10000, 11, 52719, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,'Twilight Guardian - Cast Concussion Blow'),
(33822, 0, 1, 0, 0, 0, 100, 0, 2000, 3000, 3000, 6000, 11, 62317, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,'Twilight Guardian - Cast Devastate'),
(33822, 0, 2, 0, 0, 0, 100, 0, 8000, 10000, 14000, 16000, 11, 63757, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,'Twilight Guardian - Cast Thunderclap');
