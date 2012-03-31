/*25n*/
insert into spell_proc_event (entry, procEx, cooldown) values
(67712, 2, 5);
/*25h*/
UPDATE `spell_proc_event` SET `procFlags`=0 WHERE `entry`=67758 LIMIT 1;
UPDATE `spell_proc_event` SET `Cooldown`=5 WHERE `entry`=67758 LIMIT 1;