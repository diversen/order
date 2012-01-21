ALTER TABLE `order_items` ADD COLUMN `file` mediumblob DEFAULT NULL;

ALTER TABLE `order_items` ADD COLUMN `file_thumb` mediumblob DEFAULT NULL;

ALTER TABLE `order_items` ADD COLUMN `content_type` varchar(255) DEFAULT NULL;