<?php

// for adding top level menu items
// we just add arrays to $_MODULE_MENU array

$_SUB_MODULE_MENU = array (


    array(
        'title' => lang::translate('order_shipping_main_menu'),
        'url' => '/order/shipping/index',
        'auth' => 'admin'
    ),

    array(
        'title' => lang::translate('order_shipping_private_menu'),
        'url' => '/order/shipping/private',
        'auth' => 'admin'
    ),
    array(
        'title' => lang::translate('order_shipping_company_menu'),
        'url' => '/order/shipping/company',
        'auth' => 'admin'
    ),
    
);