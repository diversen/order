<?php


$_MODULE_MENU = array (


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
    
    array(
        'title' => lang::translate('order_category_admin_main_menu'),
        'url' => '/order/category/index',
        'auth' => 'admin'
    ),
    
    array(
        'title' => lang::translate('order_sales_admin_main_menu'),
        'url' => '/order/sales/index',
        'auth' => 'admin'
    ),
    
    array(
        'title' => lang::system('config'),
        'url' => '/order/config/index',
        'auth' => 'admin'
    ),

);