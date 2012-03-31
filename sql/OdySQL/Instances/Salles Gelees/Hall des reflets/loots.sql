delete from `gameobject_loot_template` where entry in (202336, 201710);
delete from `reference_loot_template` where entry in (202336, 201710);

update `gameobject_template` set data1=202336 where entry in(202336, 202337);

INSERT INTO  `gameobject_loot_template` (
`entry` ,
`item` ,
`ChanceOrQuestChance` ,
`lootmode` ,
`groupid` ,
`mincountOrRef` ,
`maxcount`
)
VALUES (
'202336',  '1',  '100',  '1',  '1',  '-202336',  '2'
);

INSERT INTO  `gameobject_loot_template` (
`entry` ,
`item` ,
`ChanceOrQuestChance` ,
`lootmode` ,
`groupid` ,
`mincountOrRef` ,
`maxcount`
)
VALUES (
'202336',  '43102',  '100',  '1',  '0',  '1',  '1'
);

insert into reference_loot_template values(202336, 50302, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50303, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50304, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50305, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50306, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50308, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50309, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50310, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50311, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50312, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50313, 0, 1, 1, 1, 1);
insert into reference_loot_template values(202336, 50314, 0, 1, 1, 1, 1);

INSERT INTO  `gameobject_loot_template` (
`entry` ,
`item` ,
`ChanceOrQuestChance` ,
`lootmode` ,
`groupid` ,
`mincountOrRef` ,
`maxcount`
)
VALUES (
'201710',  '1',  '100',  '1',  '1',  '-201710',  '2'
);

insert into reference_loot_template values(201710, 49845, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49844, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49840, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49839, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49846, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49848, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49849, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49841, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49851, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49847, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49843, 0, 1, 1, 1, 1);
insert into reference_loot_template values(201710, 49842, 0, 1, 1, 1, 1);
