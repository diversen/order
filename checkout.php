<?php

simple_prg();
template::setTitle(lang::translate('order_checkout_html_title'));
$cart = new order();
$cart->displayCheckout();
