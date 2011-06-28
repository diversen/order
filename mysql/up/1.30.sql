ALTER TABLE `order_items` ADD COLUMN `abstract` varchar(1024) DEFAULT '';

ALTER TABLE `order_items` ADD COLUMN `category` int(10) DEFAULT 0;

DROP TABLE IF EXISTS `order_category`;

CREATE TABLE `order_category` (
      `id` int(10) NOT NULL AUTO_INCREMENT,
      `name` varchar(255) NOT NULL,
      `description` text DEFAULT NULL,
      `file` mediumblob DEFAULT NULL,
      `file_thumb` mediumblob DEFAULT NULL,
      PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;