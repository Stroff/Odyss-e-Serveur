-- Primi fix a Eye of Eternity
UPDATE instance_template SET script = 'instance_eye_of_eternity' WHERE map = 616;
UPDATE creature_template SET VehicleId=264 WHERE entry = 30248;
UPDATE `gameobject_template` SET `ScriptName` = 'go_malygos_iris' WHERE `entry` IN (193960,193958); 
UPDATE gameobject_template SET flags = 4, data0 = 43 WHERE gameobject_template.entry in (193967, 193905);
UPDATE creature_template SET ScriptName = 'boss_malygos' WHERE entry = 28859;
UPDATE creature_template SET ScriptName = 'mob_nexus_lord' WHERE entry = 30245;
UPDATE creature_template SET ScriptName = 'mob_scion_of_eternity' WHERE entry = 30249;
UPDATE creature_template SET ScriptName = 'mob_power_spark' WHERE entry = 30084;
UPDATE creature_template SET ScriptName = 'npc_arcane_overload' WHERE entry = 30282;
-- Fix ai GOB
UPDATE creature_template SET flags_extra = flags_extra | 2, faction_A = 35, faction_H = 35 WHERE entry = 30118; -- Portal (Malygos)
UPDATE `gameobject_template` SET `ScriptName` = 'go_malygos_iris' WHERE `entry` IN (193960,193958); 
-- Fix malygos,reso attaccabile
UPDATE creature_template SET unit_flags = 1 WHERE entry = 28859;
-- Fix al target della spell Surge of power
DELETE FROM spell_script_target WHERE entry = 56505;
INSERT INTO spell_script_target (entry, type, targetEntry) VALUES
(56505, 1, 22517);
-- Fix ai danni di Malygos e dei suoi add
UPDATE creature_template SET mindmg = 3684, maxdmg = 4329, dmg_multiplier = 7.5, mechanic_immune_mask = 1072918979 WHERE entry = 30245; -- Nexus Lord
UPDATE creature_template SET mindmg = 3684, maxdmg = 4329, dmg_multiplier = 13,  mechanic_immune_mask = 1072918979 WHERE entry = 31750; -- Nexus Lord (1)
UPDATE creature_template SET mechanic_immune_mask = 1072918979 WHERE entry IN (30249, 31751);
UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry IN (31750, 31751);
-- Teleport DOWN Orb of Traslocation
UPDATE `gameobject_template` SET `data10` = 26572 WHERE `entry`=180912;
-- Teleport UP Orb of Traslocation
UPDATE `gameobject_template` SET `data10` = 26566 WHERE `entry`=180911;
-- Drake 
UPDATE creature_template SET dynamicflags = 8 WHERE entry = 28859;
-- Realm First!
DELETE FROM achievement_criteria_data WHERE criteria_id = 1400;
INSERT INTO achievement_criteria_data VALUES
(1400, 1, 28859, 0); -- Realm First Magic Seeker
-- Veicoli e hover disk
UPDATE creature_template SET flags_extra = flags_extra | 2 WHERE entry = 30090; -- Vortex  'Arcane Overload', 'Hover Disk');
UPDATE creature_template SET flags_extra = flags_extra | 2, faction_A = 35, faction_H = 35, VehicleId = 165 WHERE entry IN (30234, 30248); -- Hover Disk
-- Bug vari
UPDATE creature_template SET flags_extra = flags_extra | 2, faction_A = 35, faction_H = 35 WHERE entry = 30118; -- Portal (Malygos)
UPDATE creature_template SET flags_extra = flags_extra | 2 WHERE entry = 30282; -- Arcane Overload
UPDATE creature_template SET mindmg = 1, maxdmg = 1, dmg_multiplier = 1 WHERE entry = 30592; -- Static Field
UPDATE creature_template SET modelid1 = 11686, modelid2 = 11686 WHERE entry = 22517; -- Some world trigger
-- Wyrmest Drake Spell & mount
UPDATE creature_template SET spell1 = 56091, spell2 = 56092, spell3 = 57090, spell4 = 57143, spell5 = 57108, spell6 = 57403, VehicleId = 165 WHERE entry IN (30161, 31752);
-- Versione Heroic di Malygos
DELETE FROM creature_template WHERE entry = 50000;
INSERT INTO creature_template (entry, difficulty_entry_1, difficulty_entry_2, difficulty_entry_3, KillCredit1, KillCredit2, modelid1, modelid2, 
modelid3, modelid4, name, subname, IconName, gossip_menu_id, minlevel, maxlevel, exp, faction_A, faction_H, npcflag, speed_walk, speed_run, scale, 
rank, mindmg, maxdmg, dmgschool, attackpower, dmg_multiplier, baseattacktime, rangeattacktime, unit_class, unit_flags, dynamicflags, family, 
trainer_type, trainer_spell, trainer_class, trainer_race, minrangedmg, maxrangedmg, rangedattackpower, type, type_flags, lootid, pickpocketloot, 
skinloot, resistance1, resistance2, resistance3, resistance4, resistance5, resistance6, spell1, spell2, spell3, spell4, spell5, spell6, spell7, 
spell8, PetSpellDataId, VehicleId, mingold, maxgold, AIName, MovementType, InhabitType, Health_mod, Mana_mod, Armor_mod, RacialLeader, questItem1, 
questItem2, questItem3, questItem4, questItem5, questItem6, movementId, RegenHealth, equipment_id, mechanic_immune_mask, flags_extra, ScriptName, WDBVerified) VALUES 
(50000, 0, 0, 0, 0, 0, 26752, 0, 0, 0, 'Malygos', '', '', 0, 83, 83, 2, 16, 16, 0, 1, 1.14286, 1, 3, 496, 674, 0, 783, 35, 2000, 0, 2, 64, 8, 0, 0, 0, 0, 0, 365, 529, 98, 2, 108, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 5, 1500, 50, 1, 0, 44650, 0, 0, 0, 0, 0, 227, 1, 0, 0, 1, 'boss_malygos', 1);
UPDATE creature_template SET mindmg = 4602, maxdmg = 5502, dmg_multiplier = 13, Health_mod = 1400, questItem1 = 44651, mechanic_immune_mask = 617299803 WHERE entry = 50000;
-- Update malygos
UPDATE creature_template SET mindmg = 4602, maxdmg = 5502, dmg_multiplier = 7.5, difficulty_entry_1 = 50000, mechanic_immune_mask = 617299803 WHERE entry = 28859;
UPDATE creature_template SET flags_extra = flags_extra | 1 WHERE entry IN (28859, 50000);
-- Add di malygos e Gameobject
UPDATE gameobject_template SET flags = 4, data0 = 43 WHERE entry in (193967, 193905);
UPDATE creature_template SET ScriptName = 'boss_malygos', unit_flags = unit_flags & ~256 WHERE entry = 28859;
UPDATE creature SET MovementType = 0, spawndist = 0 WHERE id = 28859; -- Malygos, don't move
UPDATE creature_template SET ScriptName = 'mob_nexus_lord' WHERE entry = 30245; -- Nexus Lord
UPDATE creature_template SET ScriptName = 'mob_scion_of_eternity' WHERE entry = 30249; -- Scion of Eternity
UPDATE creature_template SET faction_A = 14, faction_H = 14, ScriptName = 'mob_power_spark' WHERE entry = 30084; -- Power Spark
UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry = 32187; -- Power Spark (1)
UPDATE creature_template SET ScriptName = 'npc_arcane_overload' WHERE entry = 30282; -- Arcane Overload
-- Fix alle rane
UPDATE creature_template SET ScriptName = 'npc_lake_frog' WHERE entry = 33224;

-- Surge of power (NPC)
DELETE FROM creature WHERE id = 30334;
DELETE FROM creature_addon WHERE guid = 132303;
-- Spawn Focusing iris per summonare malygos
DELETE FROM gameobject WHERE id IN (193958, 193960);
INSERT INTO gameobject VALUES
(NULL, 193958, 616, 1, 1, 754.362, 1301.61, 266.171, 6.23742, 0, 0, 0.022883, -0.999738, 300, 0, 1), 
(NULL, 193960, 616, 2, 1, 754.362, 1301.61, 266.171, 6.23742, 0, 0, 0.022883, -0.999738, 300, 0, 1); 
-- Fix alla chest dei drop
UPDATE gameobject_template SET faction = 35, flags = 0 WHERE entry IN (193967, 193905);
-- Fix loot for Malygos (Alexstrasza's Gift)
DELETE FROM reference_loot_template WHERE entry = 50008;
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2) VALUES
(50008, 40474, 0, 1, 1, 1, 1, 0, 0, 0), -- Surge Needle Ring
(50008, 40497, 0, 1, 1, 1, 1, 0, 0, 0), -- Black Ice
(50008, 40489, 0, 1, 1, 1, 1, 0, 0, 0), -- Greatstaff of the Nexus
(50008, 40526, 0, 1, 1, 1, 1, 0, 0, 0), -- Gown of the Spell-Weaver
(50008, 40511, 0, 1, 1, 1, 1, 0, 0, 0), -- Focusing Energy Epaulets
(50008, 40475, 0, 1, 1, 1, 1, 0, 0, 0), -- Barricade of Eternity
(50008, 40488, 0, 1, 1, 1, 1, 0, 0, 0), -- Ice Spire Scepter
(50008, 40491, 0, 1, 1, 1, 1, 0, 0, 0), -- Hailstorm
(50008, 40519, 0, 1, 1, 1, 1, 0, 0, 0), -- Footsteps of Malygos
(50008, 40486, 0, 1, 1, 1, 1, 0, 0, 0); -- Necklace of the Glittering Chamber
-- Fix loot 25 Man
DELETE FROM reference_loot_template WHERE entry = 50009;
INSERT INTO reference_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2) VALUES
(50009, 40592, 0, 1, 1, 1, 1, 0, 0, 0), -- Boots of Healing Energies
(50009, 40566, 0, 1, 1, 1, 1, 0, 0, 0), -- Unravelling Strands of Sanity
(50009, 40194, 0, 1, 1, 1, 1, 0, 0, 0), -- Blanketing Robes of Snow
(50009, 40543, 0, 1, 1, 1, 1, 0, 0, 0), -- Blue Aspect Helm
(50009, 40590, 0, 1, 1, 1, 1, 0, 0, 0), -- Elevated Lair Pauldrons
(50009, 40560, 0, 1, 1, 1, 1, 0, 0, 0), -- Leggings of the Wanton Spellcaster
(50009, 40589, 0, 1, 1, 1, 1, 0, 0, 0), -- Legplates of Sovereignty
(50009, 40555, 0, 1, 1, 1, 1, 0, 0, 0), -- Mantle of Dissemination
(50009, 40591, 0, 1, 1, 1, 1, 0, 0, 0), -- Melancholy Sabatons
(50009, 40594, 0, 1, 1, 1, 1, 0, 0, 0), -- Spaulders of Catatonia
(50009, 40588, 0, 1, 1, 1, 1, 0, 0, 0), -- Tunic of the Artifact Guardian
(50009, 40549, 0, 1, 1, 1, 1, 0, 0, 0), -- Boots of the Renewed Flight
(50009, 40539, 0, 1, 1, 1, 1, 0, 0, 0), -- Chestguard of the Recluse
(50009, 40541, 0, 1, 1, 1, 1, 0, 0, 0), -- Frosted Adroit Handguards
(50009, 40562, 0, 1, 1, 1, 1, 0, 0, 0), -- Hood of Rationality
(50009, 40561, 0, 1, 1, 1, 1, 0, 0, 0), -- Leash of Heedless Magic
(50009, 40532, 0, 1, 1, 1, 1, 0, 0, 0), -- Living Ice Crystals
(50009, 40531, 0, 1, 1, 1, 1, 0, 0, 0), -- Mark of Norgannon
(50009, 40564, 0, 1, 1, 1, 1, 0, 0, 0), -- Winter Spectacle Gloves
(50009, 40558, 0, 1, 1, 1, 1, 0, 0, 0); -- Arcanic Tramplers
-- Emblemi,quest item,Mount
DELETE FROM gameobject_loot_template WHERE entry IN (26094, 26097);
INSERT INTO gameobject_loot_template (entry, item, ChanceOrQuestChance, lootmode, groupid, mincountOrRef, maxcount, lootcondition, condition_value1, condition_value2) VALUES
(26094, 45624, 100, 1, 0, 1, 2, 0, 0, 0), -- Emblem of Heroism x2
(26094, 1, 100, 1, 0, -50008, 2, 0, 0, 0), -- 2 items level 213
(26094, 44650, 100, 1, 0, 1, 1, 9,  13384, 0), -- Quest item, Judgement at the Eye of Eternity
(26094, 43953, 1, 1, 0, 1, 1, 0, 0, 0), -- Reins of the Blue Drake 	
(26097, 1, 100, 1, 0, -50009, 4, 0, 0, 0), -- 4 items ilevel 226
(26097, 44651, 100, 1, 0, 1, 1, 9, 13385, 0), -- Quest item, Heroic Judgement at the Eye of Eternity
(26097, 43952, 1, 1, 0, 1, 1, 0, 0, 0); -- Reins of the Azure Drake

-- Aggro Malygos
UPDATE creature_model_info SET combat_reach = '30' WHERE modelid = 26752;
-- Power spark verso Malygos
DELETE FROM spell_script_target WHERE entry = 56152 AND targetEntry = 28859;
INSERT INTO spell_script_target (entry, type, targetEntry) VALUES 
('56152', '1', '28859');
-- Script GO Focusing Iris
UPDATE `gameobject_template` SET `ScriptName` = 'go_malygos_iris' WHERE `entry` IN (193960,193958); 
-- Spawn Water Revenanat by JGC
DELETE FROM creature WHERE id = 30877;
INSERT INTO creature
(`id`,`map`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`, `orientation`,`spawntimesecs`,`spawndist`,`currentwaypoint`,`curhealth`,`curmana`,`DeathState`,`MovementType`)
VALUES
(30877, 571, 1, 1, 27391, 0, 4701.05, 2620.23, 335.868, 3.42586, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 5164.58, 3538.6, 353.628, 0.479253, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 5226.99, 3385.88, 353.644, 0.787289, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4718.32, 3353.8, 336.015, 3.46938, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4852.41, 3513.47, 331.376, 5.56367, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4680.12, 3261.2, 335.64, 5.7209, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 5068.52, 3514.3, 354.219, 5.94507, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4650.11, 3216.19, 336.037, 0.462086, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4704.64, 3453.58, 353.475, 5.79484, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4555.87, 2976.34, 335.639, 0.399384, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 5141.5, 3416.66, 353.632, 5.51932, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4972.7, 3210.85, 346.899, 2.70996, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4781.65, 3148.91, 346.899, 5.31853, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4715.96, 3519.97, 344.724, 0.793317, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4653.8, 2342.48, 334.472, 1.18402, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4576.24, 2360.43, 334.347, 3.19344, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4539.82, 2426.31, 345.484, 1.58316, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4757.16, 2220.46, 335.432, 2.83542, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4788.23, 1975.37, 420.174, 0.598566, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4902.13, 2235, 347.502, 0.766064, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4883.96, 1985.27, 410.708, 3.55263, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4822.82, 2041.69, 404.181, 2.35956, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4903.36, 2049.29, 402.789, 2.98618, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4595.95, 2848.9, 335.764, 0.52775, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4639.69, 2769.04, 335.584, 3.56645, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4612.82, 2909.1, 335.637, 3.27896, 180, 5, 0, 25200, 3994, 0, 1),
(30877, 571, 1, 1, 27391, 0, 4811.98, 2179.59, 334.711, 0.231615, 180, 5, 0, 25200, 3994, 0, 1);
-- Loot Water Revenanat by JGC
UPDATE creature_template SET lootid = 30877 WHERE entry = 30877;
DELETE FROM creature_loot_template WHERE item IN (43322,44808);
INSERT INTO creature_loot_template VALUES
(30877, 43322, -60, 1, 0, 2, 5, 0, 0, 0),
(30877, 44808, -60, 1, 0, 2, 5, 0, 0, 0),
(30846, 43322, -100, 1, 0, 1, 1, 0, 0, 0),
(30846, 44808, -100, 1, 0, 1, 1, 0, 0, 0); 
-- Gob
UPDATE gameobject_template set data17 = 0 where entry = 193908; -- Exit portal
UPDATE creature_template SET InhabitType = 4, VehicleId = 223 WHERE entry IN (30234, 30248);
UPDATE creature_template SET spell6 = 57092, spell7 = 57403 WHERE entry IN (30161, 31752);

-- Focusing iris (Cambio script)
UPDATE `gameobject_template` SET `ScriptName` = 'go_malygos_iris' WHERE `entry` IN (193960,193958); 