ALTER TABLE `order_item_select` ADD `title_human` varchar(255);

ALTER TABLE `order_item_select` ADD `reference` int(10);

DROP TABLE IF EXISTS `order_item_select_option`;

CREATE TABLE `order_item_select_option` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `select_id` int(10) NOT NULL,
  `title` varchar (255) DEFAULT '',
  `value` int (10),
  FOREIGN KEY (`select_id`) REFERENCES `order_item_select` (id)
    ON DELETE CASCADE ON UPDATE CASCADE,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;
