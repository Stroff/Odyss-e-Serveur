DELETE FROM gameobject_template WHERE entry=300001;
INSERT INTO gameobject_template VALUES
(300001, 9, 3053, 'Prix des Stuff Ar�nes', '', '', '', 0, 6553600, 1, 0, 0, 0, 0, 0, 0, 4000, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', '', 12340);
DELETE FROM page_text WHERE entry = 4000;
INSERT INTO page_text VALUES
(4000, '�===PRIX DU STUFF FATAL===�\r\n\r\nToutes les armes sont au m�me prix.\r\n\r\nIl faut 1150 de c�tes, 50000 points d\'honneurs et 400 points d\'ar�nes.\r\n\r\n(La suite apr�s la mise � jours).', 0, 1);
UPDATE `page_text` SET `text`='�===== ARME R2 =====�\r\n\r\nLes armes Implacables Rang 2 sont disponibles � partir de 2300 de cotes en 2C2.\r\n\r\n \r\n�=== PRIX DU STUFF FATAL ====�\r\n\r\nToutes les armes sont au m�me prix.\r\n\r\nIl faut 1150 de c�tes, 50000 points d\'honneurs et 400 points d\'ar�nes.\r\n\r\n\r\n(La suite apr�s la mise � jours).' 
WHERE `entry`=4000 LIMIT 1;