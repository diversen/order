<?php

template::setTitle(lang::translate('Products'));
$cart = new order ();
$cart->displayCart();