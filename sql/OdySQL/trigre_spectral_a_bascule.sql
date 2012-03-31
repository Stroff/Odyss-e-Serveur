UPDATE `creature_template` SET `npcflag`=`npcflag`|16777216,`speed_run`=1,`vehicleid`=354 WHERE `entry`=33357; -- "Spectral Tiger"
INSERT INTO `creature_template_addon` (`entry`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES
(33357,0,0,1,0, NULL); -- "Spectral Tiger"
DELETE FROM `npc_spellclick_spells` WHERE `npc_entry`=33357 AND `spell_id`=75648;
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`quest_start`,`quest_start_active`,`quest_end`,`cast_flags`,`aura_required`,`aura_forbidden`,`user_type`) VALUES
(33357,75648,0,0,0,1,0,0,0); -- "Spectral Tiger"