<?php


$_MODULE_MENU = array (
    /*
    array(
        'title' => 'Products',
        'url' => '/order/cart',
    
    ),
    array(
        'title' => 'Basket',
        'url' => '/order/basket',

    ),
    array(
        'title' => 'quick_order',
        'url' => '/order/quick_order',

    ),*/

    array(
        'title' => lang::translate('order_products_admin_main_menu'),
        'url' => '/order/products/index',
        'auth' => 'admin'
    ),
    array(
        'title' => lang::translate('order_shipping_admin_main_menu'),
        'url' => '/order/shipping/index',
        'auth' => 'admin'
    ),
);