INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33842', '63791', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33843', '63792', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33799', '62783', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33791', '63791', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33798', '62787', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33796', '62784', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33793', '62780', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33792', '62785', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33795', '62779', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33794', '62782', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33790', '62781', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33800', '62774', '0', '1', '0', '3');
INSERT INTO `npc_spellclick_spells` (`npc_entry`, `spell_id`, `quest_start`, `quest_start_active`, `quest_end`, `cast_flags`) VALUES ('33870','63663', '0', '1', '0', '3');

-- Delete vieux vehicules
UPDATE `creature_template` SET `vehicleid`=0 WHERE `entry` IN (33800,33844,33845,33842,33843,33799,33791,33798,33796,33793,33792,33795,33794,33790,33796);
UPDATE `creature_template` SET `spell1`=0,`spell2`=0,`spell3`=0,`spell4`=0,`spell5`=0, `spell6`=0 WHERE `entry` IN (33800,33844,33845,33842,33843,33799,33791,33798,33796,33793,33792,33795,33794,33790,33796);

-- Corrects vehicleid and set spells for vehicles 33845 and 33844
UPDATE `creature_template` SET `vehicleid`=349 WHERE `entry` IN (33845,33844,33782);
UPDATE `creature_template` SET `speed`=2,`spell1`=68505,`spell2`=65147,`spell3`=63010,`spell4`=66482,`spell5`=66483 WHERE `entry` IN (33845,33844,33782);


--Other
UPDATE `creature_template` SET `vehicleid`=349 WHERE `entry` IN (33217,33320,33324,33321,33317,33322,33316,33319,33318,33323);
UPDATE `creature_template` SET `speed`=2,`spell1`=62544,`spell2`=62575,`spell3`=62960,`spell4`=62552,`spell5`=64077,`spell6`=62863 WHERE `entry` IN (33217,33320,33324,33321,33317,33322,33316,33319,33318,33323);
