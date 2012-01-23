<?php

include_module('order/sales');

$cart = new order();


// get buyer info.
load_post('order_form');


// prepare for saving result of transaction
$ary = array();
$ary['full_name'] = $_POST['name'];
$ary['email'] = $_POST['email'];
$ary['full_shipping_info'] = serialize($_POST);
$ary['transaction_details'] = serialize(array ('email' => 'sent'));
$ary['payment_module'] = 'email';
$ary['status'] = 'pending';


$ary['order_details'] = order::displaySystemOrder();

// add to sales table
$sale = new orderSales();
$sale->insert($ary);


$cart->process();
