<?php

$_INSTALL['VERSION'] = 1.31;

/**
 * We also create a menu item to be added to the main menu placed in database
 */
$_INSTALL['MAIN_MENU_ITEMS'][] = array (
    'title' => 'Shop', // Title of the menu item
    'url' => '/order/cart', // url of the item
    'module_name' => 'order', // beloning to which module
    'parent' => 0, // does it have a parent item
    'weight' => 10, // weight
);

// add any other main menus items
$_INSTALL['MAIN_MENU_ITEMS'][] = array (
    'title' => 'Basket', // Title of the menu item
    'url' => '/order/basket', // url of the item
    'module_name' => 'order', // beloning to which module
    'parent' => 0, // does it have a parent item
    'weight' => 11, // weight
);

// add any other main menus items
$_INSTALL['MAIN_MENU_ITEMS'][] = array (
    'title' => 'quick_order', // Title of the menu item
    'url' => '/order/quick_order', // url of the item
    'module_name' => 'order', // beloning to which module
    'parent' => 0, // does it have a parent item
    'weight' => 12, // weight
);

$_INSTALL['PUBLIC_CLONE_URL'] = 'git://github.com/diversen/order.git';
$_INSTALL['PRIVATE_CLONE_URL'] = 'git@github.com:diversen/order.git';
