DROP TABLE IF EXISTS `order_shipping_free`;

CREATE TABLE `order_shipping_free` (
      `id` int(10) NOT NULL AUTO_INCREMENT,
      `type` varchar(255) NOT NULL,
      `cost` varchar(255) NOT NULL,
      PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;

INSERT INTO `order_shipping_free` (`type`, `cost`) VALUES ('private', '0');

INSERT INTO `order_shipping_free` (`type`, `cost`) VALUES ('company', '0');

DROP TABLE IF EXISTS `order_category`;

CREATE TABLE `order_category` (
      `id` int(10) NOT NULL AUTO_INCREMENT,
      `name` varchar(255) NOT NULL,
      `order` int(10) NOT NULL DEFAULT 0,
      `file` mediumblob DEFAULT NULL,
      `content_type` varchar(255) DEFAULT NULL,
      PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;

DROP TABLE IF EXISTS `order_report`;

CREATE TABLE `order_report` (
      `id` int(10) NOT NULL AUTO_INCREMENT,
      `report` mediumtext NOT NULL DEFAULT '',
      PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;