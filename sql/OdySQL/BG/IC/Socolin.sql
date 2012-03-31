-- Canon de la canonnière de l'Alliance
-- http://fr.wowhead.com/npc=34929
UPDATE `creature_template` SET `spell1` = '69495',`VehicleId` = '452' WHERE `entry` =34929;
UPDATE `creature_template` SET `VehicleId` = '452' WHERE `entry` =34929;

-- Canon de la canonnière de la Horde
-- http://fr.wowhead.com/npc=34935
UPDATE `creature_template` SET `spell1` = '68825',`VehicleId` = '453' WHERE `entry` =34935;
UPDATE `creature_template` SET `VehicleId` = '453' WHERE `entry` =34935;

-- Canon du donjon
-- http://fr.wowhead.com/npc=34944
UPDATE `creature_template` SET `spell1` = '67452',`spell2` = '68169' WHERE `entry` =34944;
UPDATE `creature_template` SET `VehicleId` = '160' WHERE `entry` =34944;

-- Catapulte
-- http://fr.wowhead.com/npc=34793
UPDATE `creature_template` SET `spell1` = '66218',`spell2` = '66296' WHERE `entry` =34793;
UPDATE `creature_template` SET `VehicleId` = '438' WHERE `entry` =34793;

-- Démolisseur
-- http://fr.wowhead.com/npc=34775

UPDATE `creature_template` SET `spell1` = '67442',`spell2` = '68068' WHERE `entry` =34775;
UPDATE `creature_template` SET `VehicleId` = '509' WHERE `entry` =34775;

-- Engin de siège
-- http://fr.wowhead.com/npc=34776

UPDATE `creature_template` SET `spell1` = '67816',`spell2` = '69502' WHERE `entry` =34776;
UPDATE `creature_template` SET `VehicleId` = '447' WHERE `entry` =34776;

-- Engin de siège
-- http://fr.wowhead.com/npc=35069

UPDATE `creature_template` SET `spell1` = '67816',`spell2` = '69502' WHERE `entry` =35069;
UPDATE `creature_template` SET `VehicleId` = '436' WHERE `entry` =35069;

-- Lanceur de glaive
-- http://fr.wowhead.com/npc=34802

UPDATE `creature_template` SET `spell1` = '68827',`spell2` = '69515' WHERE `entry` =34802;
UPDATE `creature_template` SET `VehicleId` = '447' WHERE `entry` =34802;

-- Lanceur de glaive
-- http://fr.wowhead.com/npc=35273

UPDATE `creature_template` SET `spell1` = '68827', `spell2` = '69515' WHERE `entry` =35273;
UPDATE `creature_template` SET `VehicleId` = '447' WHERE `entry` =35273;

-- Tourelle de flammes
-- http://fr.wowhead.com/npc=34778

UPDATE `creature_template` SET `spell1` = '68832' WHERE `entry` =34778;
-- Tourelle de flammes
-- http://fr.wowhead.com/npc=36356

UPDATE `creature_template` SET `spell1` = '68832' WHERE `entry` =36356;

-- Tourelle de siège
-- http://fr.wowhead.com/npc=34777

UPDATE `creature_template` SET `spell1` = '67462',
`spell2` = '69505' WHERE `entry` =34777;

-- Warbear Matriarch
UPDATE creature_template SET spell5 = 54458, spell4 = 54459, spell6 = 54460 WHERE entry = 29918;

-- Isle of conquest boss
UPDATE creature_template SET ScriptName = "boss_isle_of_conquest" WHERE entry IN(34922, 34924);

-- Tourelle de siège
-- http://fr.wowhead.com/npc=36355

UPDATE `creature_template` SET `spell1` = '67462',
`spell2` = '69505' WHERE `entry` =36355;

-- Vitesse des catapulte
UPDATE creature_template SET speed_run = 2.428571 WHERE entry = 34793;
UPDATE creature_template SET speed_walk = 2.8 WHERE entry = 34793;