-- Anti Personnel Cannon "Strand of the Ancents"
UPDATE `creature_template` SET
`flags_extra`=`flags_extra`|2,
`unit_flags`=`unit_flags`|4,
`unit_flags`=`unit_flags`|32768,
`dynamicflags`=`dynamicflags`|8,
`speed`=NULL,
`spell1`=49872,
`mechanic_immune_mask`=67110928
WHERE `entry` IN (27894,32795);

-- Battleground Demolisher "Strand of the Ancents"
UPDATE `creature_template` SET
`flags_extra`=`flags_extra`|2,
`unit_flags`=`unit_flags`|32768,
`dynamicflags`=`dynamicflags`|8,
`mechanic_immune_mask`=67110928,
`spell1`=52338,
`spell2`=60206
WHERE `entry` IN (28781,32796);

-- Téléporteurs
INSERT spell_linked_spell VALUES ('54643', '54640', 0, 'Teleport Strand of the Ancients' );

INSERT creature VALUES (500600, 23472, 607, 2, 1, 16925, 0, 1042.88, -71.89, 85, 0, 180, 5, 0, 4120, 0, 0, 1);
INSERT creature VALUES (500601, 23472, 607, 2, 1, 16925, 0, 1184.20, 60.92, 56.88, 0, 180, 5, 0, 4120, 0, 0, 1);
INSERT creature VALUES (500602, 23472, 607, 2, 1, 16925, 0, 1235.33, -249.84, 55.38, 0, 180, 5, 0, 4120, 0, 0, 1);
INSERT creature VALUES (500603, 23472, 607, 2, 1, 16925, 0, 1456.89, -249.67, 30.87, 0, 180, 5, 0, 4120, 0, 0, 1);
INSERT creature VALUES (500604, 23472, 607, 2, 1, 16925, 0, 1377.73, 91.64, 30.87, 0, 180, 5, 0, 4120, 0, 0, 1);