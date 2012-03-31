-- Mission: Eternal Flame
UPDATE quest_template SET ReqSpellCast1 = 42564, ReqSpellCast2 = 42564, ReqSpellCast3 = 42564, ReqSpellCast4 = 42564 WHERE entry = 11202;
-- Abandoned mule pack
UPDATE creature_template SET faction_A = 16, faction_H = 16 WHERE entry = 23977;
-- Trust
UPDATE quest_template SET ReqSourceId4 = 0, ReqCreatureOrGOId1 = 24752, ReqSpellCast1 = 44363 WHERE entry = 11460;
UPDATE item_template SET spellid_1 = 44363 WHERE entry = 34102; 
DELETE FROM gameobject_loot_template WHERE entry = 186938;
INSERT INTO gameobject_loot_template VALUE
(186938, 34102, -100, 1, 0, 1, 1, 0, 0, 0);
-- The Delicate Sound of Thunder & Lightning Infused Relics
UPDATE quest_template SET ReqCreatureOrGOId1 = 0 , ReqCreatureOrGOCount1 = 0, SpecialFlags = 0, QuestFlags = 138, Method = 0 WHERE entry IN( 11495, 11494);
