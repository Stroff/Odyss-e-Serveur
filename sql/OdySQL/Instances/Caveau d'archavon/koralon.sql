DELETE FROM creature WHERE id = '35013';
INSERT INTO `creature` (`id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) VALUES ('35013', '624', '3', '1', '0', '0', '-218.576', '103.862', '91.7463', '4.64565', '604800', '0', '0', '4183500', '0', '0', '0');

UPDATE `creature_template` SET `ScriptName`='boss_koralon' WHERE `entry`='35013';
UPDATE `creature_template` SET `ScriptName`='mob_flame_warder' WHERE `entry`='35143';