<?php

template::setTitle(lang::translate('order_cart_html_title'));
$cart = new order ();
$cart->displayCart();