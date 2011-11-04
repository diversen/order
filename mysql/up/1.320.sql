CREATE TABLE `order_sales` (
    `id` int(10) NOT NULL AUTO_INCREMENT,
    `email` varchar(255) NOT NULL,
    `order_details` text NOT NULL,
    `full_name` varchar (255) NOT NULL,
    `full_shipping_info` text NOT NULL,    
    `payment_module` varchar(255) NOT NULL,    
    `transaction_details` text NOT NULL,
    `status` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=UTF8;