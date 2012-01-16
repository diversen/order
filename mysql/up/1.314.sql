DROP TABLE IF EXISTS `order_item_select`;

CREATE TABLE `order_item_select` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `order_item_id` int(10) NOT NULL,
  `title` varchar (255) DEFAULT '',
  `options` text (255) DEFAULT '',
  FOREIGN KEY (`order_item_id`) REFERENCES `order_items` (id)
    ON DELETE CASCADE ON UPDATE CASCADE,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;

DROP TABLE IF EXISTS `order_item_select_color`;

CREATE TABLE `order_item_select_color` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `order_item_id` int(10) NOT NULL,
  `title` varchar(255) DEFAULT NULL,
  `color` varchar(255) NOT NULL,
  FOREIGN KEY (`order_item_id`) REFERENCES `order_items` (id)
    ON DELETE CASCADE ON UPDATE CASCADE,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;

DROP TABLE IF EXISTS `order_item_select_gallery`;

ALTER TABLE `order_category` ADD COLUMN `md5` varchar(32) NOT NULL;