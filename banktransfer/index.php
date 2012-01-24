<?php

http::prg();
template::setTitle(lang::translate('order_payment_select_payment_overview'));
//$cart = new order();
$options = array ();
$options['redirect'] = '/order/banktransfer/index';
order::addToBasket($options);
orderBanktransfer::displayConfirm();