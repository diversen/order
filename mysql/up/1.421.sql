ALTER TABLE `order_shipping_cost` ADD COLUMN `parent` int(10);

UPDATE `order_shipping_cost` SET `parent` = 1;

CREATE TABLE `order_shipping_cost_type` (
      `id` int(10) NOT NULL AUTO_INCREMENT,
      `name` varchar(255),
      `description` text,
      PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;

INSERT INTO `order_shipping_cost_type` (`id`, `name`) VALUES (1, 'private'); 