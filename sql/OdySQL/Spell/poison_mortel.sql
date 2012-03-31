DELETE FROM `spell_bonus_data` WHERE `entry`in (2818, 2819, 11353, 11354, 25349, 26968,27187, 57969, 57970);
INSERT INTO `spell_bonus_data` VALUES
(2818,0,0,0,0.03,'Rogue - Deadly Poison All Ranks($AP*0.12 / number of ticks)');

DELETE FROM `spell_script_names` WHERE `ScriptName`='spell_rog_deadly_poison';
INSERT INTO `spell_script_names`(`spell_id`, `ScriptName`) VALUES
(-2818,'spell_rog_deadly_poison');