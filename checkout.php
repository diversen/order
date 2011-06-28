<?php

//simple_prg();

template::setTitle(lang::translate('Checkout'));

$cart = new order();
$cart->checkout();
