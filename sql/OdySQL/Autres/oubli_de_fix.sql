INSERT INTO `spell_bonus_data` values
(67760, 0, 0, 0, 0, 'Item - Coliseum 25 Heroic Caster Trinket - Pillar of Flame'),
(67714, 0, 0, 0, 0, 'Item - Coliseum 25 Normal Caster Trinket - Pillar of Flame'),
(69729, -1, 0, -1, -1, 'Item - Onyxia 10 Caster Trinket - Searing Flames'),
(69730, -1, 0, -1, -1, 'Item - Onyxia 25 Caster Trinket - Searing Flames'),
(69733, 0, -1, -1, -1, 'Item - Onyxia 10 Caster Trinket - Cauterizing Heal'),
(69734, 0, -1, -1, -1, 'Item - Onyxia 25 Caster Trinket - Cauterizing Heal'),
(64801,0.45,0,0,0,'Druid - T8 Restoration 4P Bonus');

insert into spell_proc_event values
( 67115, 0x00,  15, 0x01400000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,   0,   0,  45), /* Item - Death Knight T9 Melee 2P Bonus */
( 69739, 0x00,   0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,   0,   0,  45), /* Item - Onyxia 25 Caster Trinket */
( 69755, 0x00,   0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,   0,   0,  45), /* Item - Onyxia 10 Caster Trinket */

DELETE FROM `spell_bonus_data` WHERE `entry`=49941;