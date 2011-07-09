<?php

template::setTitle(lang::translate('order_cart_html_title'));

$display = get_module_ini('order_display_main');


if ($display == 'all') {
    $cart = new order ();
    $cart->displayCart();
    
} else {
    
    order::displayCatCart();

}