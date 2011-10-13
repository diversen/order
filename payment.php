<?php

simple_prg();
template::setTitle(lang::translate('order_payment_html_title'));
$cart = new order();

order::displayPayment();