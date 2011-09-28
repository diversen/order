<?php


$id = URI::getInstance()->fragment(2);
$cart = new order ();
$cart->displayItem($id);
$cart->addToBasket();
