DELETE FROM `order_item_select`;

DELETE FROM `order_item_select_color`;

DELETE FROM `order_item_select_gallery`;

DROP TABLE `order_item_select_gallery`;

DROP TABLE `order_item_select`;

DROP TABLE  `order_item_select_color`;

ALTER TABLE `order_category` DROP COLUMN `md5`;