<?php

// for adding top level menu items
// we just add arrays to $_MODULE_MENU array

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
        'title' => lang::translate('Admin'),
        'url' => '/order/admin/index',
        'auth' => 'admin'
    ),
);