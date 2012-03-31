-- Primi fix a Eye of Eternity
UPDATE instance_template SET script = 'instance_eye_of_eternity' WHERE map = 616;
UPDATE creature_template SET VehicleId=264 WHERE entry = 30248;
UPDATE `gameobject_template` SET `ScriptName` = 'go_malygos_iris' WHERE `entry` IN (193960,193958); 
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
REPLACE INTO conditions (SourceTypeOrReferenceId,SourceEntry,ConditionTypeOrReference,ConditionValue1,ConditionValue2) VALUES
(13, 56505, 18, 1, 22517);
-- Fix ai danni di Malygos e dei suoi add
UPDATE creature_template SET mindmg = 3684, maxdmg = 4329, dmg_multiplier = 7.5, mechanic_immune_mask = 1072918979 WHERE entry = 30245; -- Nexus Lord
UPDATE creature_template SET mindmg = 3684, maxdmg = 4329, dmg_multiplier = 13,  mechanic_immune_mask = 1072918979 WHERE entry = 31750; -- Nexus Lord (1)
UPDATE creature_template SET mechanic_immune_mask = 1072918979 WHERE entry IN (30249, 31751);
UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry IN (31750, 31751);-- Teleport DOWN Orb of Traslocation
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
UPDATE creature_template SET mindmg = 4602, maxdmg = 5502, dmg_multiplier = 13, questItem1 = 44651, mechanic_immune_mask = 617299803 WHERE entry = 50000;
-- Update malygos
UPDATE creature_template SET mindmg = 4602, maxdmg = 5502, dmg_multiplier = 7.5, difficulty_entry_1 = 50000, mechanic_immune_mask = 617299803 WHERE entry = 28859;
UPDATE creature_template SET flags_extra = flags_extra | 1 WHERE entry IN (28859, 50000);
-- Add di malygos e Gameobject
UPDATE creature_template SET ScriptName = 'boss_malygos', unit_flags = unit_flags & ~256 WHERE entry = 28859;
UPDATE creature SET MovementType = 0, spawndist = 0 WHERE id = 28859; -- Malygos, don't move
UPDATE creature_template SET ScriptName = 'mob_nexus_lord' WHERE entry = 30245; -- Nexus Lord
UPDATE creature_template SET ScriptName = 'mob_scion_of_eternity' WHERE entry = 30249; -- Scion of Eternity
UPDATE creature_template SET faction_A = 14, faction_H = 14, ScriptName = 'mob_power_spark' WHERE entry = 30084; -- Power Spark
UPDATE creature_template SET faction_A = 14, faction_H = 14 WHERE entry = 32187; -- Power Spark (1)
UPDATE creature_template SET ScriptName = 'npc_arcane_overload' WHERE entry = 30282; -- Arcane Overload

-- Surge of power (NPC)
DELETE FROM creature WHERE id = 30334;
DELETE FROM creature_addon WHERE guid = 132303;
-- Spawn Focusing iris per summonare malygos
DELETE FROM gameobject WHERE id IN (193958, 193960);
INSERT INTO gameobject VALUES
(NULL, 193958, 616, 1, 1, 754.362, 1301.61, 266.171, 6.23742, 0, 0, 0.022883, -0.999738, 300, 0, 1), 
(NULL, 193960, 616, 2, 1, 754.362, 1301.61, 266.171, 6.23742, 0, 0, 0.022883, -0.999738, 300, 0, 1); 
-- Fix alla chest dei drop
UPDATE gameobject_template SET faction = 35, flags = 0 WHERE entry IN (193967, 193905);-- Aggro Malygos
UPDATE creature_model_info SET combat_reach = '30' WHERE modelid = 26752;
-- Power spark verso Malygos
REPLACE INTO conditions (SourceTypeOrReferenceId,SourceEntry,ConditionTypeOrReference,ConditionValue1,ConditionValue2) VALUES
('13', '56152', '18', '1', '28859');
-- Script GO Focusing Iris
UPDATE `gameobject_template` SET `ScriptName` = 'go_malygos_iris' WHERE `entry` IN (193960,193958); 
-- Gob
UPDATE gameobject_template set data17 = 0 where entry = 193908; -- Exit portal
UPDATE creature_template SET InhabitType = 4, VehicleId = 223 WHERE entry IN (30234, 30248);
UPDATE creature_template SET spell6 = 57092, spell7 = 57403 WHERE entry IN (30161, 31752);
-- Focusing iris (Cambio script)
UPDATE `gameobject_template` SET `ScriptName` = 'go_malygos_iris' WHERE `entry` IN (193960,193958); 
UPDATE creature_template SET  flags_extra =  flags_extra | 0x2 WHERE entry = 31253; -- Alexstrazsa