/* INSTANCE */
UPDATE `characters`, `character_homebind` SET `characters`.`position_x`=`character_homebind`.`position_x`, `characters`.`position_y`=`character_homebind`.`position_y`, `characters`.`position_z`=`character_homebind`.`position_z`, `characters`.`map`=`character_homebind`.`map` WHERE `characters`.`guid`=`character_homebind`.`guid`;
UPDATE `characters` SET `instance_id`=0;
TRUNCATE `character_instance`;
TRUNCATE `group_instance`;
TRUNCATE `group_member`;
TRUNCATE `groups`;
TRUNCATE `instance`;
TRUNCATE `corpse`;
TRUNCATE `instance_reset`;