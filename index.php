<?php

template::setTitle(lang::translate('order_cart_html_title'));

$display = config::getModuleIni('order_display_main');

if ( !isset($_GET['cat']) || $_GET['cat'] == 0)  {
    orderCategory::displayCatsFull();
}  else {
    orderCategory::displayHTMLMenu();
    orderCategory::displayCatItems();
}

$categories = orderCategory::getAll();
if (empty($categories)) {
    order::displayAllCartItems();
}