-- Marrowgar

DELETE FROM `script_texts` WHERE `entry` BETWEEN -1631999 AND -1631000;
INSERT INTO `script_texts` (`npc_entry`,`entry`,`content_default`,`content_loc1`,`content_loc2`,`content_loc3`,`content_loc4`,`content_loc5`,`content_loc6`,`content_loc7`,`content_loc8`,`sound`,`type`,`language`,`emote`,`comment`) VALUES
(36612,-1631000,'This is the beginning AND the end, mortals. None may enter the master''s sanctum!',NULL,'Pour vous c\'est le début ET la fin ! Mortels ! Personne ne pénétre dans le sanctuaire du Maître !',NULL,NULL,NULL,NULL,NULL,NULL,16950,1,0,0,'SAY_ENTER_ZONE'),
(36612,-1631001,'The Scourge will wash over this world as a swarm of death and destruction!',NULL,'Le fléau va déferler sur ce monde dans un torrent de mort et de destruction !',NULL,NULL,NULL,NULL,NULL,NULL,16941,1,0,0,'SAY_AGGRO'),
(36612,-1631002,'BONE STORM!',NULL,'TEMPÊTE DANS UN VERRE D\'OS !', NULL,NULL,NULL,NULL,NULL,NULL,16946,1,0,0,'SAY_BONE_STORM'),
(36612,-1631003,'Bound by bone!',NULL,'Liés par les os !',NULL,NULL,NULL,NULL,NULL,NULL,16947,1,0,0, 'SAY_BONESPIKE_1'),
(36612,-1631004,'Stick Around!',NULL,'Ne vous sauvez pas !',NULL,NULL,NULL,NULL,NULL,NULL,16948,1,0,0,'SAY_BONESPIKE_2'),
(36612,-1631005,'The only escape is death!',NULL,'La seule issue est la mort !',NULL,NULL,NULL,NULL,NULL,NULL,16949,1,0,0,'SAY_BONESPIKE_3'),
(36612,-1631006,'More bones for the offering!',NULL,'Toujours plus d\'os pour les offrandes !',NULL,NULL,NULL,NULL,NULL,NULL,16942,1,0,0,'SAY_KILL_1'),
(36612,-1631007,'Languish in damnation!',NULL,'Morfondez-vous dans la damnation !',NULL,NULL,NULL,NULL,NULL,NULL,16943,1,0,0,'SAY_KILL_2'),
(36612,-1631008,'I see... only darkness...',NULL,'Je ne vois... que les ténèbres...',NULL,NULL,NULL,NULL,NULL,NULL,16944,1,0,0,'SAY_DEATH'),
(36612,-1631009,'THE MASTER''S RAGE COURSES THROUGH ME!',NULL,'LA RAGE DU MAÎTRE COULE DANS MES VEINES !',NULL,NULL,NULL,NULL,NULL,NULL,16945,1,0,0,'SAY_BERSERK'),
(36612,-1631010,'Lord Marrowgar creates a whirling storm of bone!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0,'SAY_BONE_STORM_EMOTE');

-- DeathWhisper

DELETE FROM `script_texts` WHERE `entry` BETWEEN -1631028 AND -1631011;
INSERT INTO `script_texts` (`npc_entry`,`entry`,`content_default`,`content_loc1`,`content_loc2`,`content_loc3`,`content_loc4`,`content_loc5`,`content_loc6`,`content_loc7`,`content_loc8`,`sound`,`type`,`language`,`emote`,`comment`) VALUES
(36855,-1631011, 'You have found your way here, because you are among the few gifted with true vision in a world cursed with blindness.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,17272,1,0,0, 'SAY_INTRO_1'),
(36855,-1631012, 'You can see through the fog that hangs over this world like a shroud, and grasp where true power lies.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,17273,1,0,0, 'SAY_INTRO_2'),
(36855,-1631013, 'Fix your eyes upon your crude hands: the sinew, the soft meat, the dark blood coursing within.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,16878,1,0,0, 'SAY_INTRO_3'),
(36855,-1631014, 'It is a weakness; a crippling flaw.... A joke played by the Creators upon their own creations.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,17268,1,0,0, 'SAY_INTRO_4'),
(36855,-1631015, 'The sooner you come to accept your condition as a defect, the sooner you will find yourselves in a position to transcend it.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,17269,1,0,0, 'SAY_INTRO_5'),
(36855,-1631016, 'Through our Master, all things are possible. His power is without limit, and his will unbending.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,17270,1,0,0, 'SAY_INTRO_6'),
(36855,-1631017, 'Those who oppose him will be destroyed utterly, and those who serve -- who serve wholly, unquestioningly, with utter devotion of mind and soul -- elevated to heights beyond your ken.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,17271,1,0,0, 'SAY_INTRO_7'),
(36855,-1631018, 'What is this disturbance?! You dare trespass upon this hallowed ground? This shall be your final resting place.',NULL,'Quelle-est cette perturbation ? Vous osez profaner cette terre sacrée ? Elle deviendra votre sépulture !',NULL,NULL,NULL,NULL,NULL,NULL,16868,1,0,0, 'SAY_AGGRO'),
(36855,-1631019, 'Enough! I see I must take matters into my own hands!',NULL,'Assez ! Je vois qu\'il faut que je prenne la situation en main !',NULL,NULL,NULL,NULL,NULL,NULL,16877,1,0,0, 'SAY_PHASE_2'),
(36855,-1631020, 'Lady Deathwhisper''s Mana Barrier shimmers and fades away!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,0,3,0,0, 'SAY_PHASE_2_EMOTE'),
(36855,-1631021, 'You are weak, powerless to resist my will!',NULL,'Vous êtes faibles, impuissants devant ma volonté !',NULL,NULL,NULL,NULL,NULL,NULL,16876,1,0,0, 'SAY_DOMINATE_MIND'),
(36855,-1631022, 'Take this blessing and show these intruders a taste of our master''s power.',NULL,'Reçois ma bénédiction, et offre à ces intrus un aperçu de la puissance du Maître !',NULL,NULL,NULL,NULL,NULL,NULL,16873,1,0,0, 'SAY_DARK_EMPOWERMENT'),
(36855,-1631023, 'I release you from the curse of flesh!',NULL,'Loyal partisan, je te libère de la malédiction de la chair !',NULL,NULL,NULL,NULL,NULL,NULL,16874,1,0,0, 'SAY_DARK_TRANSFORMATION'),
(36855,-1631024, 'Arise and exult in your pure form!',NULL,'Lève-toi de l\'exultation de cette nouvelle pûreté !',NULL,NULL,NULL,NULL,NULL,NULL,16875,1,0,0, 'SAY_ANIMATE_DEAD'),
(36855,-1631025, 'Do you yet grasp of the futility of your actions?',NULL,'Saisissez-vous maintenant la futilité de vos actes ?',NULL,NULL,NULL,NULL,NULL,NULL,16869,1,0,0, 'SAY_KILL_1'),
(36855,-1631026, 'Embrace the darkness... Darkness eternal!',NULL,'Acceptez les ténèbres eternelles !',NULL,NULL,NULL,NULL,NULL,NULL,16870,1,0,0, 'SAY_KILL_2'),
(36855,-1631027, 'This charade has gone on long enough.',NULL,'Cette supercherie n\'a que trop duré !',NULL,NULL,NULL,NULL,NULL,NULL,16872,1,0,0, 'SAY_BERSERK'),
(36855,-1631028, 'All part of the masters plan! Your end is... inevitable!',NULL,'Le maître avait tout prévu, votre fin est inévitable !',NULL,NULL,NULL,NULL,NULL,NULL,16871,1,0,0, 'SAY_DEATH');
