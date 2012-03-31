delete from character_queststatus where status=0 and quest in
(
    select entry from tdbprod.quest_template where tdbprod.quest_template.questFlags & 0x1000
)
