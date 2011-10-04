<?php

template::setTitle(lang::translate('order_cart_html_title'));

$display = get_module_ini('order_display_main');

if ( !isset($_GET['cat']) || $_GET['cat'] == 0)  {
    orderCategory::displayCatsFull();
}  else {
  
//$cart = new order ();
    //$cart->displayCart();
    orderCategory::displayHTMLMenu();
    orderCategory::displayCatItems();
    
}