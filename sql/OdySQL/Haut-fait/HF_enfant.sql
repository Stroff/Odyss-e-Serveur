<<<<<<< HEAD
DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (6641,6642,6643,6644,6651,6652,6653,6654,6655,6656,6657,6659,10391,12398);
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(6641,5,58818,0,''), (6641,16,201,0,''), -- School of Hard Knocks
(6642,5,58818,0,''), (6642,16,201,0,''), -- School of Hard Knocks
(6643,5,58818,0,''), (6643,16,201,0,''), -- School of Hard Knocks
(6644,5,58818,0,''), (6644,16,201,0,''), -- School of Hard Knocks
(6651,5,58818,0,''), (6651,16,201,0,''), -- Bad Example
(6652,5,58818,0,''), (6652,16,201,0,''), -- Bad Example
(6653,5,58818,0,''), (6653,16,201,0,''), -- Bad Example
(6654,5,58818,0,''), (6654,16,201,0,''), -- Bad Example
(6655,5,58818,0,''), (6655,16,201,0,''), -- Bad Example
(6656,5,58818,0,''), (6656,16,201,0,''), -- Bad Example
(6657,5,58818,0,''), (6657,16,201,0,''), -- Bad Example
(6659,5,58818,0,''), (6659,16,201,0,''), -- Hail To The King, Baby
(10391,5,58818,0,''), (10391,16,201,0,''), -- Home Alone
(12398,5,58818,0,''), (12398,16,201,0,''); -- Daily Chores

UPDATE `creature_template` SET `speed_walk`=1,`speed_run`=1.14286,`faction_A`=35,`faction_H`=35,`unit_flags`=`unit_flags`|768,`dynamicflags`=0,`npcflag`=`npcflag`|3,`baseattacktime`=2000,`scale`=1 WHERE `entry` IN (14305,14444,22817,22818,33532,33533);

DELETE FROM `creature_template_addon` WHERE `entry` IN (14305,14444,22817,22818,33532,33533);
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(14305,0,0,0,1,0,'58818'),
(14444,0,0,0,1,0,'58818'),
(22817,0,0,0,1,0,'58818'),
(22818,0,0,0,1,0,'58818'),
(33532,0,0,0,1,0,'58818'),
(33533,0,0,0,1,0,'58818');

DELETE FROM `disables` WHERE `entry` IN (6641,6642,6643,6644,6651,6652,6653,6654,6655,6656,6657,6659,10391,12398) AND `sourceType`=4;
-- derniere partie a faire demain :)
=======
UPDATE `achievement_criteria_data` SET `ScriptName`='achievement_has_orphan_out' WHERE `ScriptName`='achievement_school_of_hard_knocks';
DELETE FROM `achievement_criteria_data` WHERE `criteria_id` IN (6641,6642,6643,6644,6651,6652,6653,6654,6655,6656,6657,6659,10391,12398);
INSERT INTO `achievement_criteria_data` (`criteria_id`,`type`,`value1`,`value2`,`ScriptName`) VALUES
(6641,16,201,0,''), -- School of Hard Knocks
(6642,16,201,0,''), -- School of Hard Knocks
(6643,16,201,0,''), -- School of Hard Knocks
(6644,16,201,0,''), -- School of Hard Knocks
(6651,11,0,0, 'achievement_has_orphan_out'), -- Bad Example
(6651,16,201,0,''), -- Bad Example
(6652,11,0,0, 'achievement_has_orphan_out'), -- Bad Example
(6652,16,201,0,''), -- Bad Example
(6653,11,0,0, 'achievement_has_orphan_out'), -- Bad Example
(6653,16,201,0,''), -- Bad Example
(6654,11,0,0, 'achievement_has_orphan_out'), -- Bad Example
(6654,16,201,0,''), -- Bad Example
(6655,11,0,0, 'achievement_has_orphan_out'), -- Bad Example
(6655,16,201,0,''), -- Bad Example
(6656,11,0,0, 'achievement_has_orphan_out'), -- Bad Example
(6656,16,201,0,''), -- Bad Example
(6657,11,0,0, 'achievement_has_orphan_out'), -- Bad Example
(6657,16,201,0,''), -- Bad Example
(6659,11,0,0, 'achievement_has_orphan_out'), -- Hail To The King, Baby
(6659,16,201,0,''), -- Hail To The King, Baby
(10391,11,0,0, 'achievement_has_orphan_out'), -- Home Alone
(10391,16,201,0,''), -- Home Alone
(12398,11,0,0, 'achievement_has_orphan_out'), -- Daily Chores
(12398,16,201,0,''); -- Daily Chores
/*DELETE FROM `disables` WHERE `entry` IN (6641,6642,6643,6644,6651,6652,6653,6654,6655,6656,6657,6659,10391,12398) AND `sourceType`=4;*/
-- dernière partie a faire demain :)
>>>>>>> parent of d6ae690... merci Trinity x) Refix (en esperant que cette fois il n'y a pas de probleme xD)
