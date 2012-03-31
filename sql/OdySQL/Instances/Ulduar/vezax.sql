-- VEZAX
UPDATE creature_template SET ScriptName = 'boss_general_vezax' WHERE entry IN (33271);
UPDATE creature_template SET faction_A=14,faction_H=14, ScriptName='npc_saronite_animus' WHERE entry IN(33524);
-- vapors
UPDATE creature_template SET faction_A=14,faction_H=14, ScriptName='npc_saronite_vapors' WHERE entry IN(33488);
-- saronite vapors trigger
DELETE FROM conditions WHERE SourceEntry IN(63322) AND SourceTypeOrReferenceId = "13";
INSERT INTO conditions (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`ConditionValue2`) VALUES
(13,63322,18,1,0);
-- elemental respawn
UPDATE creature SET spawntimesecs=1200 WHERE id IN (33838);
DELETE FROM spell_bonus_data WHERE entry = 63338;
INSERT INTO spell_bonus_data VALUES (63338, 0, 0, 0, 0, "Saronite Vapors");

UPDATE `creature_template` SET `ScriptName`='npc_horreur_sans_visage' WHERE (`entry`='33772') LIMIT 1;
UPDATE `creature_template` SET `AIName`='' WHERE (`entry`='33772') LIMIT 1;
UPDATE `creature_template` SET `mechanic_immune_mask` = 617299803, `flags_extra` = 257, `ScriptName` = 'boss_general_vezax' WHERE `entry` = 33271;
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `mechanic_immune_mask` = 650854235, `ScriptName` = 'mob_saronite_vapors' WHERE `entry` = 33488;
UPDATE `creature_template` SET `faction_A` = 14, `faction_H` = 14, `mechanic_immune_mask` = 650854235, `ScriptName` = 'mob_saronite_animus' WHERE `entry` = 33524;
-- Respawn Pure Saronite Deposit
DELETE FROM `gameobject` WHERE `id`=195036;
INSERT INTO `gameobject` (`guid`,`id`,`map`,`spawnMask`,`phaseMask`,`position_x`,`position_y`,`position_z`,`orientation`,`rotation0`,`rotation1`,`rotation2`,`rotation3`,`spawntimesecs`,`animprogress`,`state`) VALUES
(NULL, 195036, 603, 1, 1, 1886.94, 55.3576, 342.37, 0, 0, 0, 0, 1, 604800, 255, 1);
