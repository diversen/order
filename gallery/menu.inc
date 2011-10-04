<?php

// for adding top level menu items
// we just add arrays to $_MODULE_MENU array

$_SUB_MODULE_MENU = array (
    
    array(
        'title' => lang::translate('order_products_show_all_items'),
        'url' => '/order/products/index',
        'auth' => 'admin'
    ),


    array(
        'title' => lang::translate('order_add_product_menu_item'),
        'url' => '/order/products/add',
        'auth' => 'admin'
    ),

    array(
        'title' => lang::translate('order_sort_products_menu_item'),
        'url' => '/order/products/sort',
        'auth' => 'admin'
    ),
    
);

//include_controller($controller);
include get_module_path('order/products') . "/menu.inc";