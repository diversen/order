<?php

template::setTitle(lang::translate('Checkout'));

$cart = new order();
orderView::confirmOrder();
load_post('order_form');

if (@!empty($_COOKIE['order_items'])){
    include_once _COS_PATH . '/modules/order/views/confirm_form.php';
}


