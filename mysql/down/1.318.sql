ALTER TABLE `order_item_select_option` DROP COLUMN `option_id`;

ALTER TABLE `order_item_select` DROP COLUMN `option_id`;

ALTER TABLE `order_item_select` ADD `reference` int(10) DEFAULT 0;