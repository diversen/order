ALTER TABLE `order_item_select_option` ADD `option_id` int(10) DEFAULT '0';

ALTER TABLE `order_item_select` DROP COLUMN `reference`;

ALTER TABLE `order_item_select` ADD `option_id` int(10) DEFAULT '0';
