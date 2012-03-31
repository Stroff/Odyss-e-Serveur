-- Spawn Zuluhed the whacked
DELETE FROM creature WHERE id = 11980;
INSERT INTO creature VALUE (NULL,11980,530,1,1,0,0,-4155.49,386.408,141.412,4.48379,900,0,0,85560,0,0,0);
-- Argent Tabard teleport
DELETE FROM spell_scripts WHERE id = 66238;
INSERT INTO spell_scripts VALUE (66238, 0, 6, 571, 0, 0, 8490.0429, 1099.1816, 554.392, 0.588);

-- ARGENT SQUIRE/GRUNTLING
-- Gossip flag
UPDATE creature_template SET npcflag = npcflag | 0x81, gossip_menu_id = 50000 WHERE entry = 33238;
UPDATE creature_template SET npcflag = npcflag | 0x81, gossip_menu_id = 50001 WHERE entry = 33239;

DELETE FROM gossip_menu WHERE entry IN (50000, 50001);
INSERT INTO gossip_menu VALUES
(50000, 14324, 0, 0, 0, 0, 0, 0),
(50001, 14372, 0, 0, 0, 0, 0, 0);

DELETE FROM spell_linked_spell WHERE spell_effect = 67401;
INSERT INTO spell_linked_spell VALUES
(-67368, 67401, 0, "Argent Squire - Bank"),
(-67377, 67401, 0, "Argent Squire - Shop"),
(-67376, 67401, 0, "Argent Squire - Mail");

DELETE FROM npc_vendor WHERE entry IN (33238, 33239);
INSERT INTO npc_vendor (`entry`, `item`, `slot`, `maxcount`, `extendedcost`) VALUES
-- Squire
(33238, 3775, 0, 0, 0),
(33238, 5237, 0, 0, 0),
(33238, 5565, 0, 0, 0),
(33238, 16583, 0, 0, 0),
(33238, 17020, 0, 0, 0),
(33238, 17030, 0, 0, 0),
(33238, 17031, 0, 0, 0),
(33238, 17032, 0, 0, 0),
(33238, 17033, 0, 0, 0),
(33238, 21177, 0, 0, 0),
(33238, 37201, 0, 0, 0),
(33238, 41584, 0, 0, 0),
(33238, 41586, 0, 0, 0),
(33238, 43231, 0, 0, 0),
(33238, 43233, 0, 0, 0),
(33238, 43235, 0, 0, 0),
(33238, 43237, 0, 0, 0),
(33238, 44605, 0, 0, 0),
(33238, 44614, 0, 0, 0),
(33238, 44615, 0, 0, 0),

(33238, 33449, 0, 0, 0),
(33238, 33451, 0, 0, 0),
(33238, 33454, 0, 0, 0),
(33238, 33443, 0, 0, 0),
(33238, 35949, 0, 0, 0),
(33238, 35952, 0, 0, 0),
(33238, 35953, 0, 0, 0),
(33238, 35951, 0, 0, 0),
(33238, 35948, 0, 0, 0),
(33238, 35950, 0, 0, 0),

-- Gruntling
(33239, 3775, 0, 0, 0),
(33239, 5237, 0, 0, 0),
(33239, 5565, 0, 0, 0),
(33239, 16583, 0, 0, 0),
(33239, 17020, 0, 0, 0),
(33239, 17030, 0, 0, 0),
(33239, 17031, 0, 0, 0),
(33239, 17032, 0, 0, 0),
(33239, 17033, 0, 0, 0),
(33239, 21177, 0, 0, 0),
(33239, 37201, 0, 0, 0),
(33239, 41584, 0, 0, 0),
(33239, 41586, 0, 0, 0),
(33239, 43231, 0, 0, 0),
(33239, 43233, 0, 0, 0),
(33239, 43235, 0, 0, 0),
(33239, 43237, 0, 0, 0),
(33239, 44605, 0, 0, 0),
(33239, 44614, 0, 0, 0),
(33239, 44615, 0, 0, 0),

(33239, 33449, 0, 0, 0),
(33239, 33451, 0, 0, 0),
(33239, 33454, 0, 0, 0),
(33239, 33443, 0, 0, 0),
(33239, 35949, 0, 0, 0),
(33239, 35952, 0, 0, 0),
(33239, 35953, 0, 0, 0),
(33239, 35951, 0, 0, 0),
(33239, 35948, 0, 0, 0),
(33239, 35950, 0, 0, 0);