/*    GO_TRIBUTE_CHEST_10H_25     = 195665,
    GO_TRIBUTE_CHEST_10H_45     = 195666,
    GO_TRIBUTE_CHEST_10H_50     = 195667,
    GO_TRIBUTE_CHEST_10H_99     = 195668,

    GO_TRIBUTE_CHEST_25H_25     = 195669,
    GO_TRIBUTE_CHEST_25H_45     = 195670,
    GO_TRIBUTE_CHEST_25H_50     = 195671,
    GO_TRIBUTE_CHEST_25H_99     = 195672,*/
DELETE FROM gameobject_loot_template WHERE entry BETWEEN '195665' AND '195672';
DELETE FROM reference_loot_template WHERE entry BETWEEN '975566' AND '975574';
DELETE FROM conditions WHERE sourcegroup BETWEEN '975566' AND '975574';
DELETE FROM conditions WHERE sourcegroup BETWEEN '195665' AND '195672';

/* 25 héro */

INSERT INTO `gameobject_loot_template` VALUES ('195672', '49046', '100', '1', '0', '1', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195672', '49044', '100', '1', '0', '1', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195672', '47557', '100', '1', '0', '-975570', '3');
INSERT INTO `gameobject_loot_template` VALUES ('195672', '47545', '100', '1', '0', '-975572', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195672', '47554', '100', '1', '0', '-975573', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195672', '47506', '100', '1', '0', '-975571', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195672', '47528', '100', '1', '0', '-975574', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195671', '47557', '100', '1', '0', '-975570', '3');
INSERT INTO `gameobject_loot_template` VALUES ('195671', '47528', '100', '1', '0', '-975574', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195671', '47506', '100', '1', '0', '-975571', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195670', '47528', '100', '1', '0', '-975574', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195670', '47557', '100', '1', '0', '-975571', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195670', '47506', '100', '1', '0', '-975570', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195669', '47557', '100', '1', '0', '-975570', '2');

-- Réf 25 Héro
INSERT INTO `reference_loot_template` VALUES ('975574', '47528', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975571', '47526', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975574', '47525', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975571', '47524', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975574', '47523', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975571', '47521', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975574', '47520', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975571', '47519', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975574', '47518', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975571', '47517', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975574', '47516', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975571', '47515', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975574', '47513', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975571', '47506', '0', '1', '1', '1', '1');

INSERT INTO `conditions` VALUES (10, 975571, 47526, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975571, 47521, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975571, 47519, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975571, 47517, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975571, 47515, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975571, 47506, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975571, 47524, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975574, 47528, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975574, 47525, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975574, 47523, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975574, 47520, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975574, 47518, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975574, 47516, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975574, 47513, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");

INSERT INTO `reference_loot_template` VALUES ('975573', '47554', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975572', '47553', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975572', '47552', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975573', '47551', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975573', '47550', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975572', '47549', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975573', '47548', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975572', '47547', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975573', '47546', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975572', '47545', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975570', '47559', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975570', '47558', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975570', '47557', '0', '1', '1', '1', '1');

INSERT INTO `conditions` VALUES (10, 975572, 47553, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975572, 47552, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975572, 47549, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975572, 47547, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975572, 47545, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975573, 47554, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975573, 47551, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975573, 47550, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975573, 47548, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975573, 47546, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");

INSERT INTO `conditions` VALUES (4, 195668, 49046, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (4, 195668, 49044, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (4, 195672, 49046, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (4, 195672, 49044, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");

/* 10 Héro */
INSERT INTO `gameobject_loot_template` VALUES ('195668', '49046', '100', '1', '0', '1', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195668', '49044', '100', '1', '0', '1', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195668', '48670', '100', '1', '0', '-975568', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195668', '48675', '100', '1', '0', '-975566', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195668', '48693', '100', '1', '0', '-975569', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195668', '48699', '100', '1', '0', '-975567', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195668', '47556', '100', '1', '0', '1', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195668', '47242', '100', '1', '0', '4', '4');
INSERT INTO `gameobject_loot_template` VALUES ('195667', '47556', '100', '1', '0', '1', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195667', '47242', '100', '1', '0', '4', '4');
INSERT INTO `gameobject_loot_template` VALUES ('195667', '48693', '100', '1', '0', '-975569', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195667', '48699', '100', '1', '0', '-975567', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195666', '47556', '100', '1', '0', '1', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195666', '47242', '100', '1', '0', '2', '2');
INSERT INTO `gameobject_loot_template` VALUES ('195666', '48693', '100', '1', '0', '-975569', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195666', '48699', '100', '1', '0', '-975567', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195665', '47556', '100', '1', '0', '1', '1');
INSERT INTO `gameobject_loot_template` VALUES ('195665', '47242', '100', '1', '0', '2', '2');

-- Ref 10 Héro

INSERT INTO `reference_loot_template` VALUES ('975569', '48714', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975569', '48713', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975569', '48712', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975569', '48711', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975569', '48710', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975569', '48709', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975569', '48708', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975567', '48705', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975567', '48703', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975567', '48701', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975567', '48699', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975567', '48697', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975567', '48695', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975567', '48693', '0', '1', '1', '1', '1');

INSERT INTO `conditions` VALUES (10, 975569, 48714, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975567, 48699, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975569, 48713, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975567, 48701, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975569, 48712, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975567, 48693, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975569, 48711, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975567, 48695, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975569, 48710, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975567, 48697, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975569, 48709, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975567, 48703, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975569, 48708, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975567, 48705, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");

INSERT INTO `reference_loot_template` VALUES ('975566', '48675', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975566', '48674', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975566', '48673', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975566', '48672', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975566', '48671', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975568', '48670', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975568', '48669', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975568', '48668', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975568', '48667', '0', '1', '1', '1', '1');
INSERT INTO `reference_loot_template` VALUES ('975568', '48666', '0', '1', '1', '1', '1');

INSERT INTO `conditions` VALUES (10, 975566, 48675, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975566, 48674, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975566, 48673, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975566, 48672, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975566, 48671, 0, 6, 469, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975568, 48670, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975568, 48669, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975568, 48668, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975568, 48667, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
INSERT INTO `conditions` VALUES (10, 975568, 48666, 0, 6, 67, 0, 0, 0, "Odyssée Loot ToC");
