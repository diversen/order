<?php


$id = URI::getInstance()->fragment(2);
//$cart = new order ();
order::displayItem($id);
//$cart->displayItem($id);
//$cart->beforeAddToBasketEvent();
order::addToBasket();
