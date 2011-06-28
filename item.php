<?php

//$uri = URI::getInstance();
//$id = $uri->fragment(2);

$id = URI::getInstance()->fragment(2);
//$type = $uri->fragment(3);
//print_r($_POST); die;

$cart = new order ();
$cart->displayItem($id);
$cart->addToBasket();
