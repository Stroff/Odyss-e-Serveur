-- set lootid
UPDATE creature_template SET lootid=35013 WHERE entry=35013;
UPDATE creature_template SET lootid=38433 WHERE entry=38433;
UPDATE creature_template SET lootid=31125 WHERE entry=31125;
UPDATE creature_template SET lootid=33993 WHERE entry=33993;
-- Delete previous loot if exists
DELETE FROM `creature_loot_template` WHERE `entry` IN (33993,31125,35013,38433);
DELETE FROM `reference_loot_template` WHERE `entry`=34097;

DELETE FROM `reference_loot_template` WHERE `entry` IN (1100001,1100002,1100003,1100004,1100005,1100006);
-- Loots on creatures
INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`groupid`,`mincountOrRef`,`maxcount`,`lootcondition`,`condition_value1`,`condition_value2`) VALUES
(33993,44083,1,0,1,1,0,0,0), -- Mammoth (1%)
(33993,43959,1,0,1,1,0,0,0), -- Mammoth (1%)
-- Archavon
(31125,44083,1,0,1,1,0,0,0), -- Mammoth (1%)
(31125,43959,1,0,1,1,0,0,0), -- Mammoth (1%)
-- Koralon
(35013,44083,1,0,1,1,0,0,0), -- Mammoth (1%)
(35013,43959,1,0,1,1,0,0,0), -- Mammoth (1%)
-- Toravon
(38433,44083,1,0,1,1,0,0,0), -- Mammoth (1%)
(38433,43959,1,0,1,1,0,0,0); -- Mammoth (1%)

-- Loots on creatures
INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`groupid`,`mincountOrRef`,`maxcount`,`lootcondition`,`condition_value1`,`condition_value2`) VALUES
(33993,45624,100,0,2,2,0,0,0), -- Emalon dropping 2 Emblems of Triumph
(33993,1,100,0,-1100004,2,0,0,0), -- Emalon dropping 2 from PvE
-- Archavon
(31125,45624,100,0,2,2,0,0,0), -- Archavon dropping 2 Emblems of Triumph
(31125,1,100,0,-1100005,2,0,0,0), -- Archavon dropping 2 from PvE
-- Koralon
(35013,45624,100,0,3,3,0,0,0), -- Koralon dropping 3 Emblems of Triumph
-- Toravon
(38433,45624,100,0,3,3,0,0,0), -- Toravon dropping 3 Emblems of Triumph
(38433,1,100,0,-1100006,2,0,0,0); -- Toravon dropping 2 from PvE

-- PVP
INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`,`lootcondition`,`condition_value1`,`condition_value2`) VALUES
(33993,41204,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Chain Leggings
(33993,40806,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Dreadplate Gauntlets
(33993,40845,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Dreadplate Legguards
(33993,42016,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Felweave Handguards
(33993,41766,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Leather Gloves
(33993,41142,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Chain Gauntlets
(33993,42004,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Felweave Trousers
(33993,41654,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Leather Legguards
(33993,40804,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Plate Gauntlets
(33993,40844,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Plate Legguards
(33993,41970,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Silk Handguards
(33993,41958,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Silk Trousers
(33993,40880,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Greaves of Triumph
(33993,42114,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Band of Ascendancy
(33993,42115,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Band of Victory
(33993,41835,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Boots of Triumph
(33993,42067,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cloak of Triumph
(33993,41897,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cord of Dominance
(33993,41880,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cord of Salvation
(33993,40974,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Girdle of Salvation
(33993,40879,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Girdle of Triumph
(33993,41902,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Treads of Dominance
(33993,41884,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Treads of Salvation
(33993,41234,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Waistguard of Triumph
(33993,41831,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Belt of Triumph
(33993,40982,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Bracers of Salvation
(33993,40975,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Greaves of Salvation
(33993,42028,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Pendant of Victory
(33993,41229,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Sabatons of Triumph
(33993,41224,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Wristguards of Triumph
(33993,41839,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Armwraps of Triumph
(33993,40888,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Bracers of Triumph
(33993,42068,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cloak of Victory
(33993,41908,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cuffs of Dominance
(33993,41892,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cuffs of Salvation
(33993,41939,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Satin Gloves
(33993,40805,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Scaled Gauntlets
(33993,41873,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Mooncloth Gloves
(33993,41926,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Satin Leggings
(33993,41863,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Mooncloth Leggings 
(33993,40926,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Ornamented Gloves
(33993,40938,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Ornamented Legplates
(33993,40846,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Scaled Legguards
(33993,41198,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Linked Leggings
(33993,41006,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Mail Gauntlets
(33993,41032,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Mail Leggings
(33993,41629,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Belt of Dominance
(33993,41772,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Dragonhide Gloves
(33993,41666,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Dragonhide Legguards
(33993,41286,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Kodohide Gloves
(33993,41136,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Linked Gauntlets
(33993,41000,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Ringmail Gauntlets
(33993,41026,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Ringmail Leggings
(33993,41054,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Sabatons of Salvation
(33993,41069,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Waistguard of Dominance
(33993,41064,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Wristguards of Dominance
(33993,41292,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Wyrmhide Gloves
(33993,41303,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Wyrmhide Legguards
(33993,41639,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Armwraps of Dominance
(33993,41624,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Armwraps of Salvation
(33993,41616,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Belt of Salvation
(33993,41634,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Boots of Dominance
(33993,41620,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Boots of Salvation
(33993,41297,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Kodohide Legguards
(33993,42029,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Pendant of Dominance
(33993,41074,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Sabatons of Dominance
(33993,41048,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Waistguard of Salvation
(33993,41059,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Wristguards of Salvation
(33993,42062,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cloak of Dominance
(33993,42065,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cloak of Salvation
(33993,42030,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Pendant of Ascendancy
(33993,42031,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Pendant of Subjugation
(33993,42033,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Pendant of Salvation 
(33993,42064,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cloak of Ascendancy
(33993,42066,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cloak of Deliverance
(33993,42063,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Cloak of Subjugation
(33993,42032,0,1,1,1,1,0,0,0), -- Deadly Gladiator's Pendant of Deliverance
-- Archavon
(31125,40781,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Dreadplate Chestpiece
(31125,40782,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Scaled Chestpiece
(31125,40783,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Plate Chestpiece
(31125,40801,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Plate Gauntlets
(31125,40802,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Scaled Gauntlets
(31125,40803,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Dreadplate Gauntlets
(31125,40840,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Plate Legguards
(31125,40841,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Dreadplate Legguards
(31125,40842,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Scaled Legguards
(31125,40904,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Ornamented Chestguard
(31125,40925,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Ornamented Gloves
(31125,40937,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Ornamented Legplates
(31125,40988,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Ringmail Armor
(31125,40989,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Mail Armor
(31125,40999,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Ringmail Gauntlets
(31125,41005,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Mail Gauntlets
(31125,41025,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Ringmail Leggings
(31125,41031,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Mail Leggings
(31125,41085,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Chain Armor
(31125,41135,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Linked Gauntlets
(31125,41141,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Chain Gauntlets
(31125,41162,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Linked Leggings
(31125,41203,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Chain Leggings
(31125,41284,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Kodohide Gloves
(31125,41291,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Wyrmhide Gloves
(31125,41296,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Kodohide Legguards
(31125,41302,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Wyrmhide Legguards
(31125,41308,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Kodohide Robes
(31125,41314,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Wyrmhide Robes
(31125,41653,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Leather Legguards
(31125,41659,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Dragonhide Robes
(31125,41665,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Dragonhide Legguards
(31125,41765,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Leather Gloves
(31125,41771,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Dragonhide Gloves
(31125,41857,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Mooncloth Robe
(31125,41862,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Mooncloth Leggings
(31125,41872,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Mooncloth Gloves
(31125,41919,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Satin Robe
(31125,41925,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Satin Leggings
(31125,41938,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Satin Gloves
(31125,41950,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Silk Raiment
(31125,41957,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Silk Trousers
(31125,41969,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Silk Handguards
(31125,42001,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Felweave Raiment
(31125,42003,0,1,1,1,1,0,0,0), -- Hateful Gladiator's Felweave Trousers
(31125,42015,0,1,1,1,1,0,0,0); -- Hateful Gladiator's Felweave Handguards


-- References
INSERT INTO `reference_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`,`lootcondition`,`condition_value1`,`condition_value2`) VALUES
-- Valorous set
(1100004,45419,0,1,1,1,1,0,0,0), -- Valorous Deathbringer Gloves
(1100004,45420,0,1,1,1,1,0,0,0), -- Valorous Deathbringer Leggings
(1100004,46131,0,1,1,1,1,0,0,0), -- Valorous Kirin Tor Gauntlets
(1100004,45367,0,1,1,1,1,0,0,0), -- Valorous Kirin Tor Leggings
(1100004,45360,0,1,1,1,1,0,0,0), -- Valorous Scourgestalker Handguards
(1100004,45362,0,1,1,1,1,0,0,0), -- Valorous Scourgestalker Legguards
(1100004,45397,0,1,1,1,1,0,0,0), -- Valorous Terrorblade Gauntlets
(1100004,45399,0,1,1,1,1,0,0,0), -- Valorous Terrorblade Legplates
(1100004,45337,0,1,1,1,1,0,0,0), -- Valorous Darkruned Handguards
(1100004,45403,0,1,1,1,1,0,0,0), -- Valorous Worldbreaker Legguards
(1100004,45341,0,1,1,1,1,0,0,0), -- Valorous Darkruned Gauntlets
(1100004,45338,0,1,1,1,1,0,0,0), -- Valorous Darkruned Legguards
(1100004,45343,0,1,1,1,1,0,0,0), -- Valorous Darkruned Legplates
(1100004,45387,0,1,1,1,1,0,0,0), -- Valorous Gloves of Sanctification
(1100004,45392,0,1,1,1,1,0,0,0), -- Valorous Handwraps of Sanctification
(1100004,45388,0,1,1,1,1,0,0,0), -- Valorous Leggings of Sanctification
(1100004,45345,0,1,1,1,1,0,0,0), -- Valorous Nightsong Handguards
(1100004,45394,0,1,1,1,1,0,0,0), -- Valorous Pants of Sanctification
(1100004,45430,0,1,1,1,1,0,0,0), -- Valorous Siegebreaker Gauntlets
(1100004,45432,0,1,1,1,1,0,0,0), -- Valorous Siegebreaker Legplates
(1100004,45426,0,1,1,1,1,0,0,0), -- Valorous Siegebreaker Handguards
(1100004,45427,0,1,1,1,1,0,0,0), -- Valorous Siegebreaker Legguards
(1100004,45376,0,1,1,1,1,0,0,0), -- Valorous Aegis Gauntlets
(1100004,45371,0,1,1,1,1,0,0,0), -- Valorous Aegis Greaves
(1100004,45357,0,1,1,1,1,0,0,0), -- Valorous Nightsong Legguards
(1100004,45401,0,1,1,1,1,0,0,0), -- Valorous Worldbreaker Handguards
(1100004,45384,0,1,1,1,1,0,0,0), -- Valorous Aegis Legguards
(1100004,45379,0,1,1,1,1,0,0,0), -- Valorous Aegis Legplates
(1100004,45351,0,1,1,1,1,0,0,0), -- Valorous Nightsong Gloves
(1100004,45409,0,1,1,1,1,0,0,0), -- Valorous Worldbreaker Kilt
(1100004,45416,0,1,1,1,1,0,0,0), -- Valorous Worldbreaker War-Kilt
(1100004,45370,0,1,1,1,1,0,0,0), -- Valorous Aegis Gloves
(1100004,45383,0,1,1,1,1,0,0,0), -- Valorous Aegis Handguards
(1100004,45355,0,1,1,1,1,0,0,0), -- Valorous Nightsong Handgrips
(1100004,45347,0,1,1,1,1,0,0,0), -- Valorous Nightsong Leggings
(1100004,45353,0,1,1,1,1,0,0,0), -- Valorous Nightsong Trousers
(1100004,45406,0,1,1,1,1,0,0,0), -- Valorous Worldbreaker Gloves
(1100004,45414,0,1,1,1,1,0,0,0), -- Valorous Worldbreaker Grips
-- Heroes 
(1100005,39492,0,1,1,1,1,0,0,0), -- Heroes' Frostfire Robe
(1100005,39493,0,1,1,1,1,0,0,0), -- Heroes' Frostfire Leggings
(1100005,39495,0,1,1,1,1,0,0,0), -- Heroes' Frostfire Gloves
(1100005,39497,0,1,1,1,1,0,0,0), -- Heroes' Plagueheart Robe
(1100005,39498,0,1,1,1,1,0,0,0), -- Heroes' Plagueheart Leggings
(1100005,39500,0,1,1,1,1,0,0,0), -- Heroes' Plagueheart Gloves
(1100005,39515,0,1,1,1,1,0,0,0), -- Heroes' Robe of Faith
(1100005,39517,0,1,1,1,1,0,0,0), -- Heroes' Leggings of Faith
(1100005,39519,0,1,1,1,1,0,0,0), -- Heroes' Gloves of Faith
(1100005,39523,0,1,1,1,1,0,0,0), -- Heroes' Raiments of Faith
(1100005,39528,0,1,1,1,1,0,0,0), -- Heroes' Pants of Faith
(1100005,39530,0,1,1,1,1,0,0,0), -- Heroes' Handwraps of Faith
(1100005,39538,0,1,1,1,1,0,0,0), -- Heroes' Dreamwalker Robe
(1100005,39539,0,1,1,1,1,0,0,0), -- Heroes' Dreamwalker Leggings
(1100005,39543,0,1,1,1,1,0,0,0), -- Heroes' Dreamwalker Handguards
(1100005,39544,0,1,1,1,1,0,0,0), -- Heroes' Dreamwalker Gloves
(1100005,39546,0,1,1,1,1,0,0,0), -- Heroes' Dreamwalker Trousers
(1100005,39547,0,1,1,1,1,0,0,0), -- Heroes' Dreamwalker Vestments
(1100005,39554,0,1,1,1,1,0,0,0), -- Heroes' Dreamwalker Raiments
(1100005,39555,0,1,1,1,1,0,0,0), -- Heroes' Dreamwalker Legguards
(1100005,39557,0,1,1,1,1,0,0,0), -- Heroes' Dreamwalker Handgrips
(1100005,39558,0,1,1,1,1,0,0,0), -- Heroes' Bonescythe Breastplate
(1100005,39560,0,1,1,1,1,0,0,0), -- Heroes' Bonescythe Gauntlets
(1100005,39564,0,1,1,1,1,0,0,0), -- Heroes' Bonescythe Legplates
(1100005,39579,0,1,1,1,1,0,0,0), -- Heroes' Cryptstalker Tunic
(1100005,39580,0,1,1,1,1,0,0,0), -- Heroes' Cryptstalker Legguards
(1100005,39582,0,1,1,1,1,0,0,0), -- Heroes' Cryptstalker Handguards
(1100005,39588,0,1,1,1,1,0,0,0), -- Heroes' Earthshatter Tunic
(1100005,39589,0,1,1,1,1,0,0,0), -- Heroes' Earthshatter Legguards
(1100005,39591,0,1,1,1,1,0,0,0), -- Heroes' Earthshatter Handguards
(1100005,39592,0,1,1,1,1,0,0,0), -- Heroes' Earthshatter Hauberk
(1100005,39593,0,1,1,1,1,0,0,0), -- Heroes' Earthshatter Gloves
(1100005,39595,0,1,1,1,1,0,0,0), -- Heroes' Earthshatter Kilt
(1100005,39597,0,1,1,1,1,0,0,0), -- Heroes' Earthshatter Chestguard
(1100005,39606,0,1,1,1,1,0,0,0), -- Heroes' Dreadnaught Battleplate
(1100005,39607,0,1,1,1,1,0,0,0), -- Heroes' Dreadnaught Legplates
(1100005,39609,0,1,1,1,1,0,0,0), -- Heroes' Dreadnaught Gauntlets
(1100005,39611,0,1,1,1,1,0,0,0), -- Heroes' Dreadnaught Breastplate
(1100005,39612,0,1,1,1,1,0,0,0), -- Heroes' Dreadnaught Legguards
(1100005,39617,0,1,1,1,1,0,0,0), -- Heroes' Scourgeborne Battleplate
(1100005,39618,0,1,1,1,1,0,0,0), -- Heroes' Scourgeborne Gauntlets
(1100005,39620,0,1,1,1,1,0,0,0), -- Heroes' Scourgeborne Legplates
(1100005,39622,0,1,1,1,1,0,0,0), -- Heroes' Dreadnaught Handguards
(1100005,39623,0,1,1,1,1,0,0,0), -- Heroes' Scourgeborne Chestguard
(1100005,39624,0,1,1,1,1,0,0,0), -- Heroes' Scourgeborne Handguards
(1100005,39626,0,1,1,1,1,0,0,0), -- Heroes' Scourgeborne Legguards
(1100005,39629,0,1,1,1,1,0,0,0), -- Heroes' Redemption Tunic
(1100005,39630,0,1,1,1,1,0,0,0), -- Heroes' Redemption Greaves
(1100005,39632,0,1,1,1,1,0,0,0), -- Heroes' Redemption Gloves
(1100005,39633,0,1,1,1,1,0,0,0), -- Heroes' Redemption Chestpiece
(1100005,39634,0,1,1,1,1,0,0,0), -- Heroes' Redemption Gauntlets
(1100005,39636,0,1,1,1,1,0,0,0), -- Heroes' Redemption Legplates
(1100005,39638,0,1,1,1,1,0,0,0), -- Heroes' Redemption Breastplate
(1100005,39639,0,1,1,1,1,0,0,0), -- Heroes' Redemption Handguards
(1100005,39641,0,1,1,1,1,0,0,0); -- Heroes' Redemption Legguards

INSERT INTO `reference_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`groupid`,`mincountOrRef`,`maxcount`,`lootcondition`,`condition_value1`,`condition_value2`) VALUES
-- PVE_Toravon
(1100006,50114,0,1,1,1,0,0,0), -- Ahn'Kahar Blood Hunter's Handguards
(1100006,50116,0,1,1,1,0,0,0), -- Ahn'Kahar Blood Hunter's Legguards
(1100006,50275,0,1,1,1,0,0,0), -- Bloodmage Gloves
(1100006,50277,0,1,1,1,0,0,0), -- Bloodmage Leggings
(1100006,50766,0,1,1,1,0,0,0), -- Crimson Acolyte Gloves
(1100006,50391,0,1,1,1,0,0,0), -- Crimson Acolyte Handwraps
(1100006,50769,0,1,1,1,0,0,0), -- Crimson Acolyte Leggings
(1100006,50393,0,1,1,1,0,0,0), -- Crimson Acolyte Pants
(1100006,50240,0,1,1,1,0,0,0), -- Dark Coven Gloves
(1100006,50242,0,1,1,1,0,0,0), -- Dark Coven Leggings
(1100006,50842,0,1,1,1,0,0,0), -- Frost Witch's Gloves
(1100006,50831,0,1,1,1,0,0,0), -- Frost Witch's Grips
(1100006,50836,0,1,1,1,0,0,0), -- Frost Witch's Handguards
(1100006,50844,0,1,1,1,0,0,0), -- Frost Witch's Kilt
(1100006,50838,0,1,1,1,0,0,0), -- Frost Witch's Legguards
(1100006,50833,0,1,1,1,0,0,0), -- Frost Witch's War-Kilt
(1100006,50107,0,1,1,1,0,0,0), -- Lasherweave Gauntlets
(1100006,50822,0,1,1,1,0,0,0), -- Lasherweave Gloves
(1100006,50827,0,1,1,1,0,0,0), -- Lasherweave Handgrips
(1100006,50825,0,1,1,1,0,0,0), -- Lasherweave Legguards
(1100006,50109,0,1,1,1,0,0,0), -- Lasherweave Legplates
(1100006,50820,0,1,1,1,0,0,0), -- Lasherweave Trousers
(1100006,50327,0,1,1,1,0,0,0), -- Lightsworn Gauntlets
(1100006,50868,0,1,1,1,0,0,0), -- Lightsworn Gloves
(1100006,50866,0,1,1,1,0,0,0), -- Lightsworn Greaves
(1100006,50863,0,1,1,1,0,0,0), -- Lightsworn Handguards
(1100006,50861,0,1,1,1,0,0,0), -- Lightsworn Legguards
(1100006,50325,0,1,1,1,0,0,0), -- Lightsworn Legplates
(1100006,50095,0,1,1,1,0,0,0), -- Scourgelord Gauntlets
(1100006,50856,0,1,1,1,0,0,0), -- Scourgelord Handguards
(1100006,50854,0,1,1,1,0,0,0), -- Scourgelord Legguards
(1100006,50097,0,1,1,1,0,0,0), -- Scourgelord Legplates
(1100006,50088,0,1,1,1,0,0,0), -- Shadowblade Gauntlets
(1100006,50090,0,1,1,1,0,0,0), -- Shadowblade Legplates
(1100006,50079,0,1,1,1,0,0,0), -- Ymirjar Lord's Gauntlets
(1100006,50849,0,1,1,1,0,0,0), -- Ymirjar Lord's Handguards
(1100006,50847,0,1,1,1,0,0,0), -- Ymirjar Lord's Legguards
(1100006,50081,0,1,1,1,0,0,0); -- Ymirjar Lord's Legplates

-- Set money
UPDATE `creature_template` SET `lootid`=`entry`,`mingold` = '325609',`maxgold` = '325609' WHERE `entry`=31722;
-- Archavon loot:
DELETE FROM `creature_loot_template` WHERE `entry` = 31722;
INSERT INTO `creature_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`groupid`,`mincountOrRef`,`maxcount`,`lootcondition`,`condition_value1`,`condition_value2`) VALUES
(31722,45624,100,0,2,2,0,0,0), -- emblems
(31722,43959,1,0,1,1,0,0,0), -- mount Alliance
(31722,44083,1,0,1,1,0,0,0), -- mount Horde
(31722,1,100,0,-1100007,3,0,0,0); -- dropping 3 from PvE
-- Reference
DELETE FROM `reference_loot_template` WHERE `entry` = '1100007';
INSERT INTO `reference_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`groupid`,`mincountOrRef`,`maxcount`) VALUES
(1100007,40415,0,1,1,1), -- Valorous Frostfire Gloves
(1100007,40417,0,1,1,1), -- Valorous Frostfire Leggings
(1100007,40418,0,1,1,1), -- Valorous Frostfire Robe
(1100007,40422,0,1,1,1), -- Valorous Plagueheart Leggings
(1100007,40423,0,1,1,1), -- Valorous Plagueheart Robe
(1100007,40445,0,1,1,1), -- Valorous Gloves of Faith
(1100007,40448,0,1,1,1), -- Valorous Leggings of Faith
(1100007,40449,0,1,1,1), -- Valorous Robe of Faith
(1100007,40454,0,1,1,1), -- Valorous Handwraps of Faith
(1100007,40457,0,1,1,1), -- Valorous Pants of Faith
(1100007,40458,0,1,1,1), -- Valorous Raiments of Faith
(1100007,40460,0,1,1,1), -- Valorous Dreamwalker Handguards
(1100007,40462,0,1,1,1), -- Valorous Dreamwalker Leggings
(1100007,40463,0,1,1,1), -- Valorous Dreamwalker Robe
(1100007,40466,0,1,1,1), -- Valorous Dreamwalker Gloves
(1100007,40468,0,1,1,1), -- Valorous Dreamwalker Trousers
(1100007,40469,0,1,1,1), -- Valorous Dreamwalker Vestments
(1100007,40471,0,1,1,1), -- Valorous Dreamwalker Raiments
(1100007,40472,0,1,1,1), -- Valorous Dreamwalker Handgrips
(1100007,40493,0,1,1,1), -- Valorous Dreamwalker Legguards
(1100007,40495,0,1,1,1), -- Valorous Bonescythe Breastplate
(1100007,40496,0,1,1,1), -- Valorous Bonescythe Gauntlets
(1100007,40500,0,1,1,1), -- Valorous Bonescythe Legplates
(1100007,40503,0,1,1,1), -- Valorous Cryptstalker Tunic
(1100007,40504,0,1,1,1), -- Valorous Cryptstalker Handguards
(1100007,40506,0,1,1,1), -- Valorous Cryptstalker Legguards
(1100007,40508,0,1,1,1), -- Valorous Earthshatter Tunic
(1100007,40509,0,1,1,1), -- Valorous Earthshatter Handguards
(1100007,40512,0,1,1,1), -- Valorous Earthshatter Legguards
(1100007,40514,0,1,1,1), -- Valorous Earthshatter Hauberk
(1100007,40515,0,1,1,1), -- Valorous Earthshatter Gloves
(1100007,40517,0,1,1,1), -- Valorous Earthshatter Kilt
(1100007,40520,0,1,1,1), -- Valorous Earthshatter Grips
(1100007,40522,0,1,1,1), -- Valorous Earthshatter War-Kilt
(1100007,40523,0,1,1,1), -- Valorous Earthshatter Chestguard
(1100007,40525,0,1,1,1), -- Valorous Dreadnaught Battleplate
(1100007,40527,0,1,1,1), -- Valorous Dreadnaught Gauntlets
(1100007,40529,0,1,1,1), -- Valorous Dreadnaught Legplates
(1100007,40544,0,1,1,1), -- Valorous Dreadnaught Breastplate
(1100007,40545,0,1,1,1), -- Valorous Dreadnaught Handguards
(1100007,40547,0,1,1,1), -- Valorous Dreadnaught Legguards
(1100007,40550,0,1,1,1), -- Valorous Scourgeborne Battleplate
(1100007,40552,0,1,1,1), -- Valorous Scourgeborne Gauntlets
(1100007,40556,0,1,1,1), -- Valorous Scourgeborne Legplates
(1100007,40559,0,1,1,1), -- Valorous Scourgeborne Chestguard
(1100007,40563,0,1,1,1), -- Valorous Scourgeborne Handguards
(1100007,40567,0,1,1,1), -- Valorous Scourgeborne Legguards
(1100007,40569,0,1,1,1), -- Valorous Redemption Tunic
(1100007,40570,0,1,1,1), -- Valorous Redemption Gloves
(1100007,40572,0,1,1,1), -- Valorous Redemption Greaves
(1100007,40574,0,1,1,1), -- Valorous Redemption Chestpiece
(1100007,40575,0,1,1,1), -- Valorous Redemption Gauntlets
(1100007,40577,0,1,1,1), -- Valorous Redemption Legplates
(1100007,40579,0,1,1,1), -- Valorous Redemption Breastplate
(1100007,40580,0,1,1,1), -- Valorous Redemption Handguards
(1100007,40583,0,1,1,1), -- Valorous Redemption Legguards
(1100007,40784,0,1,1,1), -- Deadly Gladiator's Dreadplate Chestpiece
(1100007,40785,0,1,1,1), -- Deadly Gladiator's Scaled Chestpiece
(1100007,40786,0,1,1,1), -- Deadly Gladiator's Plate Chestpiece
(1100007,40804,0,1,1,1), -- Deadly Gladiator's Plate Gauntlets
(1100007,40805,0,1,1,1), -- Deadly Gladiator's Scaled Gauntlets
(1100007,40806,0,1,1,1), -- Deadly Gladiator's Dreadplate Gauntlets
(1100007,40844,0,1,1,1), -- Deadly Gladiator's Plate Legguards
(1100007,40845,0,1,1,1), -- Deadly Gladiator's Dreadplate Legguards
(1100007,40846,0,1,1,1), -- Deadly Gladiator's Scaled Legguards
(1100007,40905,0,1,1,1), -- Deadly Gladiator's Ornamented Chestguard
(1100007,40926,0,1,1,1), -- Deadly Gladiator's Ornamented Gloves
(1100007,40938,0,1,1,1), -- Deadly Gladiator's Ornamented Legplates
(1100007,40990,0,1,1,1), -- Deadly Gladiator's Ringmail Armor
(1100007,40991,0,1,1,1), -- Deadly Gladiator's Mail Armor
(1100007,41000,0,1,1,1), -- Deadly Gladiator's Ringmail Gauntlets
(1100007,41006,0,1,1,1), -- Deadly Gladiator's Mail Gauntlets
(1100007,41026,0,1,1,1), -- Deadly Gladiator's Ringmail Leggings
(1100007,41032,0,1,1,1), -- Deadly Gladiator's Mail Leggings
(1100007,41080,0,1,1,1), -- Deadly Gladiator's Linked Armor
(1100007,41086,0,1,1,1), -- Deadly Gladiator's Chain Armor
(1100007,41136,0,1,1,1), -- Deadly Gladiator's Linked Gauntlets
(1100007,41142,0,1,1,1), -- Deadly Gladiator's Chain Gauntlets
(1100007,41198,0,1,1,1), -- Deadly Gladiator's Linked Leggings
(1100007,41204,0,1,1,1), -- Deadly Gladiator's Chain Leggings
(1100007,41286,0,1,1,1), -- Deadly Gladiator's Kodohide Gloves
(1100007,41292,0,1,1,1), -- Deadly Gladiator's Wyrmhide Gloves
(1100007,41297,0,1,1,1), -- Deadly Gladiator's Kodohide Legguards
(1100007,41303,0,1,1,1), -- Deadly Gladiator's Wyrmhide Legguards
(1100007,41309,0,1,1,1), -- Deadly Gladiator's Kodohide Robes
(1100007,41315,0,1,1,1), -- Deadly Gladiator's Wyrmhide Robes
(1100007,41649,0,1,1,1), -- Deadly Gladiator's Leather Tunic
(1100007,41654,0,1,1,1), -- Deadly Gladiator's Leather Legguards
(1100007,41660,0,1,1,1), -- Deadly Gladiator's Dragonhide Robes
(1100007,41666,0,1,1,1), -- Deadly Gladiator's Dragonhide Legguards
(1100007,41766,0,1,1,1), -- Deadly Gladiator's Leather Gloves
(1100007,41772,0,1,1,1), -- Deadly Gladiator's Dragonhide Gloves
(1100007,41858,0,1,1,1), -- Deadly Gladiator's Mooncloth Robe
(1100007,41863,0,1,1,1), -- Deadly Gladiator's Mooncloth Leggings
(1100007,41873,0,1,1,1), -- Deadly Gladiator's Mooncloth Gloves
(1100007,41920,0,1,1,1), -- Deadly Gladiator's Satin Robe
(1100007,41926,0,1,1,1), -- Deadly Gladiator's Satin Leggings
(1100007,41939,0,1,1,1), -- Deadly Gladiator's Satin Gloves
(1100007,41951,0,1,1,1), -- Deadly Gladiator's Silk Raiment
(1100007,41958,0,1,1,1), -- Deadly Gladiator's Silk Trousers
(1100007,41970,0,1,1,1), -- Deadly Gladiator's Silk Handguards
(1100007,41997,0,1,1,1), -- Deadly Gladiator's Felweave Raiment
(1100007,42004,0,1,1,1), -- Deadly Gladiator's Felweave Trousers
(1100007,42016,0,1,1,1); -- Deadly Gladiator's Felweave Handguards