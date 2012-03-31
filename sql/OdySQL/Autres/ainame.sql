UPDATE creature_template SET AIName = 'EventAI' WHERE entry IN (33695, 34127);

INSERT INTO `creature_ai_scripts` VALUES ('1013', '34127', '4', '0', '50', '0', '0', '0', '0', '0', '11', '65147', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Boneguard Commander - Cast Shield-Breaker on Aggro (chance 50%)');
INSERT INTO `creature_ai_scripts` VALUES ('1014', '34127', '4', '0', '50', '0', '0', '0', '0', '0', '11', '63010', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Boneguard Commander - Cast Charge on Aggro (chance 50%)');
INSERT INTO `creature_ai_scripts` VALUES ('1015', '34127', '1', '0', '100', '1', '1000', '1000', '0', '0', '11', '60023', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Boneguard Commander - Scourge Banner Aura on Spawn');
INSERT INTO `creature_ai_scripts` VALUES ('1100', '33695', '0', '0', '100', '0', '20000', '20000', '0', '0', '11', '65130', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Cultist Bombardier - Cast Time Bomb after 20 sec');
INSERT INTO `creature_ai_scripts` VALUES ('1101', '33695', '0', '0', '100', '1', '4000', '6000', '7000', '10000', '11', '65128', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'Cultist Bombardier - Cast Throw Dynamite');
