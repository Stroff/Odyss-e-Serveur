UPDATE  `creature_template` SET  `ScriptName` =  'npc_DeathspeakerServant' WHERE  `creature_template`.`entry` =36805;

/* coffre de loot de deathbringer en trop */
delete from `gameobject` where `id`=202239 and `spawnMask`=3;
