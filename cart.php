<?php

template::setTitle(lang::translate('order_cart_html_title'));

$display = config::getModuleIni('order_display_main');



orderCategory::redirect();
$id = orderCategory::getCatId();

if ( !$id)  {
    orderCategory::displayCatsFull();
}  else {
    orderCategory::displayHTMLMenu();
    orderCategory::displayCatItems($id);
}

$categories = orderCategory::getAll();
if (empty($categories)) {
    order::displayAllCartItems();
}