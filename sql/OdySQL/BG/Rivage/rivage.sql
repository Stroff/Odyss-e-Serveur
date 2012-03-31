/* Démolisseur */
UPDATE creature_template SET vehicleid = 158 WHERE entry = 28781; 

/* Tourelle */
UPDATE creature_template SET vehicleid = 79 WHERE entry = 27894;
UPDATE `creature_template` SET `speed`=NULL WHERE `entry`= 27894;

UPDATE `creature_template` SET `IconName` = 'vehichleCursor', `maxlevel` = 80, `maxhealth` = 65951, `faction_A` = 14, `faction_H` = 14, `maxdmg` = 460, `attackpower` = 1050 WHERE `entry` = 28781;    
UPDATE `creature_template` SET `minlevel` = 70, `maxlevel` = 72, `minhealth` = 9610, `maxhealth` = 9610, `armor` = 7600, `faction_A` = 1891, `faction_H` = 1891, `mindmg` = 166, `maxdmg` = 355, `attackpower` = 941 WHERE `entry` = 32657;    
UPDATE `creature_template` SET `IconName` = 'vehichleCursor', `maxlevel` = 80, `maxhealth` = 45000, `faction_A` = 534, `faction_H` = 534 WHERE `entry` = 27894;    
UPDATE `creature_template` SET `minlevel` = 72, `maxlevel` = 72, `minhealth` = 9610, `maxhealth` = 9610, `armor` = 7600, `faction_A` = 1978, `faction_H` = 1978, `mindmg` = 142, `maxdmg` = 345, `attackpower` = 879 WHERE `entry` = 32659;
UPDATE `creature_template` SET `faction_A` = 1733, `faction_H` = 1733 WHERE `entry` = 27894;
UPDATE `creature_template` SET `minhealth`= 25000, `maxhealth`= 45000, `minlevel`=80, `maxlevel`=80 WHERE `entry`= 27894;
UPDATE `creature_template` SET `minhealth`=50000, `maxhealth`=65951, `minlevel`=80, `maxlevel`=80 WHERE `entry`=28781;
UPDATE `creature_template` SET `npcflag`=1, `minhealth`=6986, `maxhealth`=6986, `minlevel`=70, `maxlevel`= 70 WHERE `entry`=29262;
UPDATE `creature_template` SET `npcflag`=1, `minhealth`=6986, `maxhealth`=6986, `minlevel`=70, `maxlevel`= 70 WHERE `entry`=29260;
-- fix by stryker
-- This change is needed to keep Wintergrasp vehicles on the faction that made them after dismount.
-- Update WG vehicle and accessory factions and add immunity to fear, stun & daze
UPDATE `creature_template` SET `faction_A`=1732,`faction_H`=1735, `mechanic_immune_mask`=`mechanic_immune_mask`|67110928 WHERE `entry` IN 
(27881,28094,28312,32627,28319,32629,28366);
Cannons:
update creature_template set IconName = "Gunner" where entry = 27894;
UPDATE `creature_template` SET `vehicleid`=160 WHERE `entry`=27894;
UPDATE `creature_template` SET `spell1`=49872 WHERE `entry`=27894;
UPDATE `creature_template` set `unit_flags`=`unit_flags`|4 WHERE `entry`=27894;

UPDATE `creature_template` SET `vehicleid`=158 WHERE `entry`=28781;
UPDATE `creature_template` set spell1=49872 where `entry`=32795;
UPDATE `creature_template` set spell1=52338 where `entry`=32796;
UPDATE `creature_template` set spell2`=60206 where `entry`=32796;