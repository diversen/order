<?php

// for adding top level menu items
// we just add arrays to $_MODULE_MENU array

$_SUB_MODULE_MENU = array (


    array(
        'title' => lang::translate('Add Product'),
        'url' => '/order/admin/index',
        'auth' => 'admin'
    ),

    array(
        'title' => lang::translate('sort_products'),
        'url' => '/order/admin/sort',
        'auth' => 'admin'
    ),
);