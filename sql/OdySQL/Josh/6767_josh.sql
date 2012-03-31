/* Borean tundra */
/* crash 
UPDATE creature_template SET ScriptName='npc_seaforium_depth_charge' WHERE (entry='25401'); */
UPDATE creature_template SET ScriptName='' WHERE (entry='25401');
UPDATE creature_template SET ScriptName='mob_oil_stained_wolf' WHERE (entry='25791');
UPDATE creature_template SET ScriptName='npc_dead_caravan_guard' WHERE (entry='25342');
UPDATE gameobject_template SET ScriptName='go_gearmaster_manual' WHERE (entry='190334');
UPDATE creature_template SET ScriptName='npc_raelorasz' WHERE (entry='26117');
UPDATE creature_template SET ScriptName='npc_winterfin_tadpole' WHERE (entry='25201');
UPDATE gameobject_template SET ScriptName='go_winterfin_tadpole_cage' WHERE (entry='187373');
UPDATE creature_template SET ScriptName='mob_varidus_the_flenser' WHERE (entry='25618');

/* Dragonblight */
UPDATE creature_template SET ScriptName='npc_woodlands_walker' WHERE (entry='26421');
UPDATE creature_template SET ScriptName='npc_ravaged_crystalline_ice_giant' WHERE (entry='26809');
UPDATE creature_template SET ScriptName='mob_commander_jordan' WHERE (entry='27237');
UPDATE creature_template SET ScriptName='mob_lead_cannoneer_zierhut' WHERE (entry='27235');
UPDATE creature_template SET ScriptName='mob_blacksmith_goodman' WHERE (entry='27234');
UPDATE creature_template SET ScriptName='mob_stable_master_mercer' WHERE (entry='27236');
UPDATE creature_template SET ScriptName='npc_rokhan' WHERE (entry='26859');
UPDATE creature_template SET ScriptName='mob_dregmar_runebrand' WHERE (entry='27003');
UPDATE creature_template SET ScriptName='npc_warsong_battle_standard' WHERE (entry='26678');
UPDATE creature_template SET ScriptName='npc_hourglass_of_eternity' WHERE entry IN ('27840', '32327');
UPDATE creature_template SET ScriptName='npc_koltira_deathweaver_agmar_hammer' WHERE (entry='26581');
UPDATE creature_template SET ScriptName='mob_arctic_grizzly' WHERE (entry='26482');
UPDATE creature_template SET ScriptName='mob_snowfall_elk' WHERE (entry='26615');
UPDATE creature_template SET ScriptName='mob_fallen_earthen_defender' WHERE (entry='30035');

/* Grizzy */
UPDATE gameobject_template SET ScriptName='go_loken_piedestal' WHERE (entry='188596');
UPDATE creature_template SET ScriptName='npc_image_of_loken' WHERE (entry='27212');
UPDATE creature_template SET ScriptName='mob_highland_mustang' WHERE (entry='26472');
UPDATE creature_template SET ScriptName='npc_depleted_war_golem' WHERE (entry='27017');
UPDATE gameobject_template SET ScriptName='go_seer_of_zeb_halak' WHERE (entry='188458');

/* Howling Fjord */
UPDATE creature_template SET ScriptName='mob_north_fleet_reservist' WHERE (entry='24120');
UPDATE creature_template SET ScriptName='npc_silvermoon_harry' WHERE (entry='24539');
UPDATE creature_template SET ScriptName='mob_proto_drake_egg' WHERE (entry='23777');
UPDATE creature_template SET ScriptName='npc_cleric_of_the_crusade' WHERE (entry='24233');
UPDATE creature_template SET ScriptName='npc_lord_irulon_trueblade' WHERE (entry='24191');
UPDATE creature_template SET ScriptName='npc_captured_valgarde' WHERE entry IN (24086, 24088, 24089, 24090);
UPDATE gameobject_template SET ScriptName='go_dragonflayer_cage' WHERE entry BETWEEN '186566' AND '186575';
UPDATE creature_template SET ScriptName='npc_ancient_male_vrykul' WHERE (entry='24314');
UPDATE creature_template SET ScriptName='npc_alliance_banner' WHERE (entry='24640');
UPDATE creature_template SET ScriptName='npc_lich_king_echo' WHERE entry IN (24248, 29394);
UPDATE creature_template SET ScriptName='mob_reef_bull' WHERE entry IN ('24786');
UPDATE creature_template SET ScriptName='mob_feknut_firecracker_bunny' WHERE entry IN ('24170');
UPDATE creature_template SET ScriptName='mob_proto_drake' WHERE entry IN ('23689');
UPDATE creature_template SET ScriptName='npc_gjalergron_prisoner' WHERE entry IN ('24035');
UPDATE gameobject_template SET ScriptName='go_gjalerbron_cage' WHERE entry IN ('186910');

/* Item */
UPDATE item_template SET ScriptName='item_Interdimensional_Refabricator' WHERE (entry='35479');
UPDATE item_template SET ScriptName='item_DEHTA_trap_smasher' WHERE (entry='35228');
UPDATE item_template SET ScriptName='' WHERE (entry='41507');
UPDATE gameobject_template SET ScriptName = 'go_scourge_enclosure' WHERE (entry='191548');
/* Naxx */
UPDATE creature_template SET ScriptName='mob_zombie_chows' WHERE (entry='16360');

/* Icecrown */
UPDATE creature_template SET ScriptName='npc_sadronite_mine_slave' WHERE (entry='31397');

delete from `script_waypoint` where `entry`=25504;

insert into `script_waypoint` (`entry`,`pointid`,`location_x`, `location_y`, `location_z`,`waittime`,`point_comment`) values
(25504,1,'2882.26','6734.51','32.8864',0,'Mootoo the Younger'),
(25504,2,'2877.37','6731.59','32.8721',0,'Mootoo the Younger'),
(25504,3,'2874.18','6725.85','30.3087',0,'Mootoo the Younger'),
(25504,4,'2866.36','6726.04','26.7277',0,'Mootoo the Younger'),
(25504,5,'2863.97','6731.91','23.8372',0,'Mootoo the Younger'),
(25504,6,'2869.29','6736.92','20.5227',0,'Mootoo the Younger'),
(25504,7,'2874.16','6731.88','18.5042',0,'Mootoo the Younger'),
(25504,8,'2887.05','6736.39','13.997',0,'Mootoo the Younger'),
(25504,9,'2901.68','6741.25','14.0413',0,'Mootoo the Younger'),
(25504,10,'2919.45','6746.28','13.7325',5000,'Mootoo the Younger'),
(25504,11,'2947.18','6738.71','12.7117',0,'Mootoo the Younger'),
(25504,12,'2982.43','6748.59','10.2755',5000,'Mootoo the Younger'),
(25504,13,'2985.05','6776.05','8.33081',0,'Mootoo the Younger'),
(25504,14,'2978.72','6801.48','5.83056',0,'Mootoo the Younger'),
(25504,15,'2957.81','6818.86','4.7594',0,'Mootoo the Younger'),
(25504,16,'2917.03','6820.55','5.87954',5000,'Mootoo the Younger'),
(25504,17,'2890.04','6825.68','4.11676',0,'Mootoo the Younger'),
(25504,18,'2850.31','6812.35','2.09411',0,'Mootoo the Younger'),
(25504,19,'2821.29','6797.99','4.49696',0,'Mootoo the Younger'),
(25504,20,'2798.25','6770.64','5.0632',1000,'Mootoo the Younger'),
(25504,21,'2807.49','6748.29','8.25933',5000,'Mootoo the Younger');

delete from `script_texts` where `npc_entry`=25504;
INSERT INTO `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) VALUES 
(25504, -1750040, 'My father''s aura is quite strong, he cannot be far. Could you be a doll and fight off the monsters wandering throught the mist?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'npc_mootoo_the_younger'),
(25504, -1750041, 'Watch out for the monsters!Which way should we go first? Let''s try this way...', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'npc_mootoo_the_younger'),
(25504, -1750042, 'What could this be?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'npc_mootoo_the_younger'),
(25504, -1750043, 'There''s no sign of it ending! Where could my father be?', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'npc_mootoo_the_younger'),
(25504, -1750044, 'Father! You''re safe!', NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, 'npc_mootoo_the_younger');

UPDATE `creature_template` SET `ScriptName`='npc_mootoo_the_younger' WHERE `entry`=25504;

delete from `script_waypoint` where `entry`=25589;
insert into `script_waypoint` (`entry`,`pointid`,`location_x`, `location_y`, `location_z`,`waittime`) values
( 25589, 1,'4462.37','5372.75','-15.2912',0),
( 25589, 2,'4478.7','5377.27','-15.0012',5000),
( 25589, 3,'4482.25','5390.64','-15.2354',0),
( 25589, 4,'4477.09','5405.02','-15.2386',0),
( 25589, 5,'4468.71','5416.9','-15.2602',0),
( 25589, 6,'4457.24','5426.87','-15.6104',0),
( 25589, 7,'4439.7','5433.46','-15.2384',0),
( 25589, 8,'4422.63','5432.32','-14.8822',0),
( 25589, 9,'4404.71','5422.74','-14.4494',0),
( 25589, 10,'4394.68','5406.63','-10.8423',0),
( 25589, 11,'4391.99','5392.88','-6.45477',0),
( 25589, 12,'4390.65','5370.91','0.504708',0),
( 25589, 13,'4393.34','5354.19','3.1859',0),
( 25589, 14,'4401.68','5342.78','5.20245',0),
( 25589, 15,'4417.98','5335.18','8.31299',0),
( 25589, 16,'4431.01','5335.17','11.0135',0),
( 25589, 17,'4446.21','5340.58','14.4585',0),
( 25589, 18,'4462.73','5350.22','16.8783',0),
( 25589, 19,'4475.06','5362.82','19.1229',0),
( 25589, 20,'4480.92','5381.72','22.2479',0),
( 25589, 21,'4481.31','5394.2','26.2008',0),
( 25589, 22,'4476.32','5409.12','29.0811',5000),
( 25589, 23,'4466.33','5420.75','31.8093',0),
( 25589, 24,'4450.66','5430.03','36.2843',0),
( 25589, 25,'4431.24','5433.77','38.2282',0),
( 25589, 26,'4417.65','5437.11','40.2429',0),
( 25589, 27,'4402.5','5440.94','42.7727',0),
( 25589, 28,'4387.11','5450.98','48.6992',0),
( 25589, 29,'4364.52','5468.98','48.8229',0),
( 25589, 30,'4344.02','5483.26','48.0509',0);

UPDATE `creature_template` SET `unit_flags`=33280 WHERE `entry`=25589;
UPDATE `creature_template` SET `ScriptName`='npc_bonker_togglevolt' WHERE `entry`=25589;
UPDATE `creature_template` SET `speed`=1 WHERE `entry`=25589;

delete from `creature` where `id`=25589;

REPLACE INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `DeathState`, `MovementType`) values
('135124','25589','571','1','1','0','0','4409.6','5370.69','-13.196','0.599701','25','0','0','13936','0','0','0');

delete from `script_texts` where `npc_entry`=25589;
insert into `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) values('25589','-1700003','I\'ll make you a deal: If you get me out of here alive, you\'ll get a reward larger than you can imagine!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','0','npc_bonker_togglevolt');
insert into `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) values('25589','-1700002','I AM NOT AN APPETIZER!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','0','npc_bonker_togglevolt');
insert into `script_texts` (`npc_entry`, `entry`, `content_default`, `content_loc1`, `content_loc2`, `content_loc3`, `content_loc4`, `content_loc5`, `content_loc6`, `content_loc7`, `content_loc8`, `sound`, `type`, `language`, `emote`, `comment`) values('25589','-1700001','Right then, no time to waste. Lets get outa here!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','0','0','0','npc_bonker_togglevolt');

/* Sholazar Bassin */
UPDATE gameobject_template SET ScriptName='go_sturdy_wine' WHERE (entry='190622');
UPDATE creature_template SET ScriptName='npc_adventurous_dwarf' WHERE (entry='28604');
UPDATE creature_template SET ScriptName='mob_chicken_escapee' WHERE (entry='28161');

/* Storm Peaks */
UPDATE creature_template SET ScriptName='mob_exhausted_vrykul' WHERE (entry='30146');

/* Zul'Drak */
/* Fais crash 
UPDATE creature_template SET ScriptName='npc_elemental_lord' WHERE (entry='28118'); */
UPDATE creature_template SET ScriptName='' WHERE (entry='28118'); 
UPDATE `creature_template` SET `ScriptName`='' WHERE (`entry`='30022');
/* Fais crash 
UPDATE creature_template SET ScriptName='npc_vladof_the_butcher' WHERE (entry='30022'); */
UPDATE creature_template SET ScriptName='npc_nass' WHERE (entry='28521');
UPDATE creature_template SET ScriptName='npc_stefan_vadu' WHERE (entry='28518');

/* Oculus */
UPDATE creature_template SET ScriptName='npc_unstable_sphere' WHERE (entry='28166');

/* Sartha */
UPDATE creature_template SET ScriptName='' WHERE entry = '30494';

UPDATE creature_template SET ScriptName = "npc_tails_up" WHERE entry IN(33011,33008,29319,33010,33007,29327);
UPDATE creature_template SET ScriptName = 'npc_rescued_crusader' WHERE entry IN(28136, 28142, 28148);

-- Memories of Stormhoof
UPDATE creature_template SET ScriptName = 'npc_chieftain_swiftspear' WHERE entry = 30395;
-- Engineering a disaster
UPDATE creature_template SET ScriptName = 'npc_engineer_helice' WHERE entry = 28787;
-- Engineering a disaster
INSERT IGNORE INTO `script_waypoint` (`entry`, `pointid`, `location_x`, `location_y`, `location_z`, `waittime`, `point_comment`) VALUES
(28787, 0, 5910.56, 5379.95, -98.36, 0, ''),
(28787, 1, 5928.02, 5378.56, -99.04, 0, ''),
(28787, 2, 5917.22, 5383.49, -106.31, 0, ''),
(28787, 3, 5907.29, 5389.99, -106.31, 0, ''),
(28787, 4, 5902.68, 5403.82, -97.13, 0, ''),
(28787, 5, 5892.22, 5405.76, -95.61, 0, ''),
(28787, 6, 5879.53, 5383.24, -93.74, 0, ''),
(28787, 7, 5873.71, 5360.06, -98.49, 0, ''),
(28787, 8, 5852.29, 5351.21, -98.95, 0, ''),
(28787, 9, 5842.24, 5333.76, -100.36, 0, ''),
(28787, 10, 5827.98, 5318.31, -98.06, 0, ''),
(28787, 11, 5815.71, 5309.31, -97.11, 0, '');
-- A Hero's Burden
UPDATE creature_template SET ScriptName = 'npc_zepik_the_gorlok_hunter' WHERE entry = 28668;
UPDATE creature_template SET ScriptName = 'npc_jaloot' WHERE entry = 28667;
UPDATE creature_template SET ScriptName = 'npc_artruis_the_heartless' WHERE entry = 28659;

-- A rough ride
UPDATE creature_template SET ScriptName = 'npc_captive_crocilisk' WHERE entry = 28308;
UPDATE creature_template SET ScriptName = 'npc_chieftain_swiftspear' WHERE entry = 30395;
UPDATE creature_template SET ScriptName = 'npc_dying_berserker' WHERE entry = 31273;
UPDATE creature_template SET ScriptName = 'npc_dying_soldier' WHERE entry = 31304;
UPDATE creature_template SET ScriptName = 'npc_highlord_tirion_fordring_cultist' WHERE entry = 28179;

-- The Thane of Voldrune
UPDATE creature_template SET ScriptName = 'npc_flamebringer' WHERE entry = 27292;

UPDATE gameobject_template SET Scriptname = 'go_frostblade_shrine' WHERE entry = 186649;
UPDATE creature_template SET Scriptname = 'npc_inner_turmoil' WHERE entry = 27959;

UPDATE creature_template SET Scriptname = 'npc_shadowstalker_getry' WHERE entry = 25729;
UPDATE creature_template SET Scriptname = 'npc_windsoul_totem' WHERE entry = 25987;
