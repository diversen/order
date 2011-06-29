<?php

// for adding top level menu items
// we just add arrays to $_MODULE_MENU array

$_SUB_MODULE_MENU = array (


    array(
        'title' => lang::translate('order_add_product_menu_item'),
        'url' => '/order/products/index',
        'auth' => 'admin'
    ),

    array(
        'title' => lang::translate('order_sort_products_menu_item'),
        'url' => '/order/products/sort',
        'auth' => 'admin'
    ),
    
);