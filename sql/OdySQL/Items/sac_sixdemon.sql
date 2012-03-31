UPDATE creature_template SET AIName = 'EventAI' WHERE entry = '10656';
DELETE FROM `creature_ai_scripts` WHERE (`creature_id`=10656);
INSERT INTO `creature_ai_scripts` VALUES 
(50000000, 10656, 0, 0, 100, 0, 45000, 45000, 45000, 45000, 37, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 'Felhunter die in 45 sec'),
(50000001, 10656, 1, 0, 100, 0, 45000, 45000, 45000, 45000, 37, 0, 0, 0, 0, 0, 0, 0, 
0, 0, 0, 0, 'Felhunter die in 45 sec OOC');
