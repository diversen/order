<?php

// for adding top level menu items
// we just add arrays to $_MODULE_MENU array

$_SUB_MODULE_MENU = array (

    array(
        'title' => lang::translate('order_category_edit_items'),
        'url' => '/order/category/index',
        'auth' => 'admin'
    ),

    array(
        'title' => lang::translate('order_sort_products_menu_item'),
        'url' => '/order/category/sort',
        'auth' => 'admin'
    ),
    
);