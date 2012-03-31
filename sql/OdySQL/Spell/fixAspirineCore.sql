/* Fixed spell damage counting exploit (items with spd) for some classes */


-- Druid
UPDATE `spell_bonus_data` SET `direct_bonus` = 0, `dot_bonus` = 0 WHERE `entry` IN (779,1822,60089);
DELETE FROM `spell_bonus_data` WHERE `entry` IN (1079,9007,22568);
INSERT INTO `spell_bonus_data` VALUES
(1079,0,0,-1,-1,'Druid - Rip'),
(9007,0,0,-1,-1,'Druid - Pounce Bleed'),
(22568,0,0,-1,-1,'Druid - Ferocious Bite');

-- Rogue
UPDATE `spell_bonus_data` SET `direct_bonus` = 0, `dot_bonus` = 0 
WHERE `entry` IN (2818,2819,11353,11354,25349,26968,27187,57969,57970);

-- Deadly Poison fix
DELETE FROM `spell_bonus_data` WHERE `entry` IN ('2818');
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
('2818','0','0','0','0.03','Rogue - Deadly Poison Rank 1($AP*0.12 / number of ticks)');
DELETE FROM `spell_script_names` WHERE `spell_id` IN ('-2818');
INSERT INTO `spell_script_names` (`spell_id`, `ScriptName`) VALUES
('-2818','spell_rog_deadly_poison');

-- Envenom fix
DELETE FROM `spell_bonus_data` WHERE `entry` IN ('32645');
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
('32645','0','0','0','0','Rogue - Envenom');

-- Hunter
UPDATE `spell_bonus_data` SET `direct_bonus` = 0, `dot_bonus` = 0 WHERE `entry` IN (3044,3674,53352,13812,13797,1978,42243);
UPDATE `spell_bonus_data` SET `ap_dot_bonus` = 0.1 WHERE `entry` = 13812;
DELETE FROM `spell_bonus_data` WHERE `entry` IN (24131,53353);
INSERT INTO `spell_bonus_data` VALUES
(24131,0,0,-1,-1,'Hunter - Wyvern Sting (triggered)'),
(53353,0,0,-1,-1,'Hunter - Chimera Shot (Serpent)');
DELETE FROM `spell_ranks` WHERE `first_spell_id` = 24131;
INSERT INTO `spell_ranks` VALUES
(24131,24131,1),
(24131,24134,2),
(24131,24135,3),
(24131,27069,4),
(24131,49009,5),
(24131,49010,6);

-- Fix Explosive shot from spd scaling
DELETE FROM `spell_bonus_data` WHERE `entry`='53352';
INSERT INTO `spell_bonus_data`(`entry`,`direct_bonus`,`dot_bonus`,`ap_bonus`,`ap_dot_bonus`,`comments`) VALUES 
( '53352','0','0','0.14','0','Hunter - Explosive Shot (triggered)');

-- Paladin
-- Seals of the Pure fix
DELETE FROM spell_bonus_data WHERE entry IN (25742);
INSERT INTO `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) VALUES
('25742','0','0','0','0','Paladin - Seal of Righteousness Dummy Proc');

/* System de proc */


-- Fixed warlock's talent Empowered Imp
UPDATE `spell_proc_event` set `procFlags` = 0x00010004 
WHERE `entry` = 54278;

-- Fixed talent Scent of Blood for death knights
DELETE FROM `spell_proc_event` WHERE `entry` IN (49004,49508,49509);
INSERT INTO `spell_proc_event` (`entry`,`procEx`) VALUES
(49004,0x00000033),
(49508,0x00000033),
(49509,0x00000033);

-- Desolation procs only with BS fix.
DELETE FROM `spell_proc_event` WHERE `entry` IN ('66799','66814','66815','66816','66817');
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
('66799','0','15','4194304','0','0','0','0','0','0','0'), -- Desolation (Rank 1)
('66814','0','15','4194304','0','0','0','0','0','0','0'), -- Desolation (Rank 2)
('66815','0','15','4194304','0','0','0','0','0','0','0'), -- Desolation (Rank 3)
('66816','0','15','4194304','0','0','0','0','0','0','0'), -- Desolation (Rank 4)
('66817','0','15','4194304','0','0','0','0','0','0','0'); -- Desolation (Rank 5)

-- Fix Holy Concentration proc from Empowerd Renew
DELETE FROM `spell_proc_event` WHERE `entry` IN (34753, 34859, 34860);
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
(34753, 0, 6, 6144, 4, 4096, 0, 2, 0, 0, 0), -- rank1
(34859, 0, 6, 6144, 4, 4096, 0, 2, 0, 0, 0), -- rank2
(34860, 0, 6, 6144, 4, 4096, 0, 2, 0, 0, 0); -- rank3

-- Fixed mage's talent Hot Streak
UPDATE `spell_proc_event` SET `SpellFamilyMask1`=`SpellFamilyMask1`|0x00010000 WHERE `entry` IN (44445,44446,44448);

-- Master Poisoner fix
DELETE FROM `spell_dbc` WHERE `Id` IN ('45176');
INSERT INTO `spell_dbc` (`Id`, `Dispel`, `Mechanic`, `Attributes`, `AttributesEx`, `AttributesEx2`, `AttributesEx3`, `AttributesEx4`, `AttributesEx5`, `Stances`, `StancesNot`, `Targets`, `CastingTimeIndex`, `AuraInterruptFlags`, `ProcFlags`, `ProcChance`, `ProcCharges`, `MaxLevel`, `BaseLevel`, `SpellLevel`, `DurationIndex`, `RangeIndex`, `StackAmount`, `EquippedItemClass`, `EquippedItemSubClassMask`, `EquippedItemInventoryTypeMask`, `Effect1`, `Effect2`, `Effect3`, `EffectDieSides1`, `EffectDieSides2`, `EffectDieSides3`, `EffectRealPointsPerLevel1`, `EffectRealPointsPerLevel2`, `EffectRealPointsPerLevel3`, `EffectBasePoints1`, `EffectBasePoints2`, `EffectBasePoints3`, `EffectMechanic1`, `EffectMechanic2`, `EffectMechanic3`, `EffectImplicitTargetA1`, `EffectImplicitTargetA2`, `EffectImplicitTargetA3`, `EffectImplicitTargetB1`, `EffectImplicitTargetB2`, `EffectImplicitTargetB3`, `EffectRadiusIndex1`, `EffectRadiusIndex2`, `EffectRadiusIndex3`, `EffectApplyAuraName1`, `EffectApplyAuraName2`, `EffectApplyAuraName3`, `EffectAmplitude1`, `EffectAmplitude2`, `EffectAmplitude3`, `EffectMultipleValue1`, `EffectMultipleValue2`, `EffectMultipleValue3`, `EffectMiscValue1`, `EffectMiscValue2`, `EffectMiscValue3`, `EffectMiscValueB1`, `EffectMiscValueB2`, `EffectMiscValueB3`, `EffectTriggerSpell1`, `EffectTriggerSpell2`, `EffectTriggerSpell3`, `EffectSpellClassMaskA1`, `EffectSpellClassMaskA2`, `EffectSpellClassMaskA3`, `EffectSpellClassMaskB1`, `EffectSpellClassMaskB2`, `EffectSpellClassMaskB3`, `EffectSpellClassMaskC1`, `EffectSpellClassMaskC2`, `EffectSpellClassMaskC3`, `MaxTargetLevel`, `SpellFamilyName`, `SpellFamilyFlags1`, `SpellFamilyFlags2`, `SpellFamilyFlags3`, `MaxAffectedTargets`, `DmgClass`, `PreventionType`, `DmgMultiplier1`, `DmgMultiplier2`, `DmgMultiplier3`, `AreaGroupId`, `SchoolMask`, `Comment`) VALUES
('45176','0','0','0','0','0','0','0','0','0','0','0','1','0','0','0','0','1','1','1','0','1','0','-1','0','0','3','0','0','0','0','0','0','0','0','0','0','0','0','0','0','6','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','8','0','0','0','0','0','0','0','0','0','0','1','Master Poisoner Trigger (SERVERSIDE)');
DELETE FROM `spell_proc_event` WHERE `entry` IN ('31226', '31227', '58410');
INSERT INTO `spell_proc_event` (`entry`, `SchoolMask`, `SpellFamilyName`, `SpellFamilyMask0`, `SpellFamilyMask1`, `SpellFamilyMask2`, `procFlags`, `procEx`, `ppmRate`, `CustomChance`, `Cooldown`) VALUES
('31226','0','8','0','524288','0','0','0','0','0','0'), -- Master Poisoner (Rank 1)
('31227','0','8','0','524288','0','0','0','0','0','0'), -- Master Poisoner (Rank 2)
('58410','0','8','0','524288','0','0','0','0','0','0'); -- Master Poisoner (Rank 3)

-- Fixed shaman's talent Elemental Focus
UPDATE `spell_proc_event` SET `SpellFamilyMask0` = `SpellFamilyMask0` &~ 192 WHERE `entry` = 16164;

-- Blood reserve proc  (trinket)
469		DELETE FROM `spell_proc_event` WHERE `entry` IN (64568);
470		INSERT INTO `spell_proc_event` VALUES (64568, 0x00, 0x00, 0x00000000, 0x00000000, 0x00000000, 0x001A22A8, 0x00000000, 0, 100, 3);

/* autre */


-- Fixed hunter's talent Lock and Load
DELETE FROM `conditions` WHERE `SourceEntry` = 56453;
INSERT INTO `conditions` (`SourceTypeOrReferenceId`,`SourceEntry`,`ConditionTypeOrReference`,`ConditionValue1`,`Comment`) VALUES
(17,56453,11,67544,'Lock and Load - Lock and Load Marker');

-- Blessing of Sanctuary vs Vigilance
UPDATE `spell_group` SET `spell_id` = 68066 WHERE `id` = 1091 and `spell_id` = 47930;
UPDATE `spell_group` SET `spell_id` = 20912 WHERE `id` = 1092 and `spell_id` = 20911;

-- Fixed spell Anti-Magic Zone
UPDATE `creature_template` SET `modelid1` = 11686, `unit_flags` = 33554432 WHERE `modelid1` = 4590 AND `entry` = 28306;

-- Fix Druid Enrage spell
DELETE FROM `spell_ranks` WHERE `first_spell_id` = 1178;
INSERT INTO `spell_ranks` VALUES (1178,1178,1),(1178,9635,2);

-- Fix a bug when pets chasing target even if it's invisible
DELETE FROM `spell_linked_spell` WHERE `spell_effect` = 54661 AND `spell_trigger` IN (32612,5215,1784);
INSERT INTO `spell_linked_spell` VALUES
(32612,54661,0,'Invisibility Sanctuary Effect'),
(5215,54661,0,'Prowl Sanctuary Effect'),
(1784,54661,0,'Stealth Sanctuary Effect');

