<?php

template::setTitle(lang::translate('order_checkout_html_title'));

$cart = new order();
order::displayConfirm();
load_post('order_form');

if (@!empty($_COOKIE['order_items'])){
    templateView::includeModuleView('order', 'confirm_form');
}


