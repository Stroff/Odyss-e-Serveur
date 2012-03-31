update creature_template set Health_mod=3.968 where entry in (35644, 36557, 36559, 36558);
update creature_template set spell3=63010 where entry in (35644, 36557, 36559, 36558);

UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33845;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33844;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33217;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33318;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33323;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33322;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33317;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33319;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33316;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33324;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33320;
UPDATE `creature_template` SET `VehicleId`=349, `spell1`=68505, `spell2`=65147, `spell3`=63010, `spell4`=66482, `spell5`=66483,`speed_run`=1.14 WHERE `entry`=33321;

delete from `spell_script_names` where `spell_id` in (62575, 63010, 66481);
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES 
(63010, 'spell_charge_toc5'),
(66481, 'spell_charge_toc5'),
(62575, 'spell_shield_breaker');


update creature_template set AIName='SmartAI' where entry=35311;
delete from smart_scripts where entryorguid=35311;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES
(35311, 0, 0, 0, 25, 0, 100, 0, 0, 0, 0, 0, 11, 67196, 2, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 'Fountain of light - edc5 - AoE heal');
