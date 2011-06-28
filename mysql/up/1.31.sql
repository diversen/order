DROP TABLE IF EXISTS `order_shipping_cost`;

CREATE TABLE `order_shipping_cost` (
      `id` int(10) NOT NULL AUTO_INCREMENT,
      `type` varchar(255) NOT NULL,
      `cost` varchar(255) NOT NULL,
      `weight` varchar(255) NOT NULL,
      PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;