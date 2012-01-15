<?php

http::prg();
template::setTitle(lang::translate('order_payment_html_title'));
$cart = new order();
$cart->displayPayment();