<?php

template::setTitle(lang::translate('order_checkout_html_title'));

$cart = new order();
$options = array ();
$options['redirect'] = '/order/confirm';
order::addToBasket($options);
order::displayConfirm();



