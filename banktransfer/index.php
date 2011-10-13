<?php

simple_prg();

$cart = new order();
$options = array ();
$options['redirect'] = '/order/banktransfer/index';
$cart->addToBasket($options);
orderBanktransfer::displayConfirm();