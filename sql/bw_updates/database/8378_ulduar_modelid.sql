-- XT-002
UPDATE `creature_model_info` SET `bounding_radius` = 0.465, `combat_reach` = 10 WHERE `modelid` = 28611;
UPDATE `creature_template` SET `dmg_multiplier` = 70 WHERE `entry` = 33293;
-- Assembly of Iron
UPDATE `creature_model_info` SET `bounding_radius` = 0.45, `combat_reach` = 25 WHERE `modelid` = 28313;
UPDATE `creature_model_info` SET `bounding_radius` = 0.45, `combat_reach` = 6 WHERE `modelid` = 28344;
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299547 WHERE `entry` = 32857;
UPDATE `creature_template` SET `dmg_multiplier` = 60 WHERE `entry` = 32867;
UPDATE `creature_template` SET `dmg_multiplier` = 45 WHERE `entry` = 32927;
-- Kologarn
UPDATE `creature_model_info` SET `bounding_radius` = 0.465, `combat_reach` = 15 WHERE `modelid` = 28638;
UPDATE `creature_model_info` SET `bounding_radius` = 0.35, `combat_reach` = 15 WHERE `modelid` = 28821;
UPDATE `creature_model_info` SET `bounding_radius` = 0.35, `combat_reach` = 15 WHERE `modelid` = 28822;
UPDATE `creature_template` SET `baseattacktime` = 1800 WHERE `entry` = 32930;
-- Auriaya
UPDATE `creature_model_info` SET `bounding_radius` = 0.775, `combat_reach` = 5 WHERE `modelid` = 28651;
UPDATE `creature_template` SET `dmg_multiplier` = 60 WHERE `entry` = 33515;
-- Freya
UPDATE `creature_template` SET `baseattacktime` = 1500 WHERE `entry` = 32906;
-- Mimiron
UPDATE `creature_model_info` SET `bounding_radius` = 0.775, `combat_reach` = 7 WHERE `modelid` = 28831;
UPDATE `creature_model_info` SET `bounding_radius` = 0.775, `combat_reach` = 5 WHERE `modelid` = 28841;
UPDATE `creature_model_info` SET `bounding_radius` = 0.775, `combat_reach` = 4 WHERE `modelid` = 28979;
-- Genaral Vezax
UPDATE `creature_template` SET `baseattacktime` = 1800, `dmg_multiplier` = 45 WHERE `entry` = 33271;
UPDATE `creature_model_info` SET `bounding_radius` = 0.62, `combat_reach` = 12 WHERE `modelid` = 28548;
UPDATE `creature` SET `spawntimesecs` = 604800 WHERE `id` = 33838;