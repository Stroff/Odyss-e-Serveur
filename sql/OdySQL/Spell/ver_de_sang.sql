INSERT INTO `creature_template_addon` (`entry`, `auras`) VALUES  
('28017', '50453 0') # Health Leech (Passive) Aura 
ON DUPLICATE KEY UPDATE 
auras = VALUES(auras);
UPDATE `creature_template` 
SET `mindmg` = '80', `maxdmg` = '150', `attackpower` = '25', `minrangedmg` = '70', `maxrangedmg` = '150' 
WHERE `entry` = 28017;