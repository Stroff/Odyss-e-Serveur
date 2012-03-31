CREATE TABLE `log_rename` (
`guid` INT( 11 ) UNSIGNED NOT NULL ,
`accountid` INT( 11 ) UNSIGNED NOT NULL ,
`oldname` VARCHAR( 12 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`newname` VARCHAR( 12 ) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL ,
`date` DATE NOT NULL 
) ENGINE = MYISAM ;

'A executer sur la bdd site