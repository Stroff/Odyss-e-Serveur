-- The cluthes of evil (Fixata)
UPDATE quest_template SET NextQuestId = 0 WHERE entry = 11501;
-- Iron Rune Constructs and You (3 quest)
UPDATE quest_template SET Method = 0, QuestFlags = 138, SpecialFlags = 0, ReqCreatureOrGOId1 = 0, ReqCreatureOrGOCount1 = 0 WHERE entry IN (11485, 11489, 11491);
-- Rep Timbermaw hold (Quest piume)
UPDATE quest_template SET RewRepValueId1 = 0, RewRepValue1 = 300 WHERE entry IN (8469, 8467);

