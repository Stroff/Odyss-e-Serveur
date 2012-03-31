-- Pit of saron
UPDATE creature_template SET ScriptName = "npc_jaina_or_sylvannas_pit_of_saron" WHERE entry IN(38189, 38188) ;
REPLACE INTO `areatrigger_scripts` (`entry`, `ScriptName`) VALUES
(5578, 'at_pit_of_saron'),
(5579, 'at_pit_of_saron'),
(5580, 'at_pit_of_saron'),
(5581, 'at_pit_of_saron'),
(5582, 'at_pit_of_saron'),
(5583, 'at_pit_of_saron'),
(5584, 'at_pit_of_saron'),
(5585, 'at_pit_of_saron'),
(5586, 'at_pit_of_saron'),
(5587, 'at_pit_of_saron');
-- Sindragosa Pit Of Saron
UPDATE creature_template SET faction_A = 14, faction_H = 14, ScriptName = "npc_sindragosa_pit_of_saron" WHERE entry = 37755 ;

-- Pit of Saron 
UPDATE `creature_template` SET `mechanic_immune_mask`=`mechanic_immune_mask`|617299803,`flags_extra`=`flags_extra`|1 WHERE `entry` in (36494,3649401); -- Garfrost 
UPDATE `creature_template` SET `mechanic_immune_mask`=`mechanic_immune_mask`|617299803,`flags_extra`=`flags_extra`|1 WHERE `entry` in (36476,3647601); -- Ick 
UPDATE `creature_template` SET `mechanic_immune_mask`=`mechanic_immune_mask`|617299803,`flags_extra`=`flags_extra`|1 WHERE `entry` in (36658,36658); -- Scourgelord Tyrannus 
-- Tyrannus
UPDATE creature_template SET minlevel = 80, maxlevel = 80, ScriptName = "mob_collapsing_icicle" WHERE entry = 36847 ;

-- Exploding orb
UPDATE creature_template SET ScriptName = "mob_exploding_orb" WHERE entry = 36610 ;

UPDATE `creature_template` SET `ScriptName`='npc_tyrannus_intro' WHERE (`entry`='36794') LIMIT 1;
UPDATE `creature_template` SET `InhabitType`='7' WHERE (`entry`='36794') LIMIT 1;