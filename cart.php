<?php

template::setTitle(lang::translate('Products'));
$cart = new cart ();
$cart->displayCart();