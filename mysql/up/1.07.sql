DROP TABLE IF EXISTS `cart_items`;

CREATE TABLE `cart_items` (
      `id` int(10) NOT NULL AUTO_INCREMENT,
      `item_name` varchar(255) NOT NULL,
      `item_description` text DEFAULT NULL,
      `stock` int(10) DEFAULT NULL,
      `file` mediumblob DEFAULT NULL,
      `file_thumb` mediumblob DEFAULT NULL,
      `price` int(10) NOT NULL,
      PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;