<?php

$ini = get_module_ini('order_menu_items');

$_INSTALL['VERSION'] = 1.316;

if (in_array('order_shop', $ini)) {
    $_INSTALL['MAIN_MENU_ITEMS'][0] = array (
        'title' => 'order_shop', // Title of the menu item
        'url' => '/order/cart', // url of the item
        'module_name' => 'order', // beloning to which module
        'parent' => 0, // does it have a parent item
        'weight' => 10, // weight
    );
    
    if (get_module_ini('order_menu_auth')) {
        $_INSTALL['MAIN_MENU_ITEMS'][0]['auth'] = get_module_ini('order_menu_auth');
    }
}

if (in_array('order_basket', $ini)) {
    $_INSTALL['MAIN_MENU_ITEMS'][1] = array (
        'title' => 'order_basket', // Title of the menu item
        'url' => '/order/basket', // url of the item
        'module_name' => 'order', // beloning to which module
        'parent' => 0, // does it have a parent item
        'weight' => 11, // weight
    );
}

if (in_array('order_quick_order', $ini)) {
    $_INSTALL['MAIN_MENU_ITEMS'][2] = array (
        'title' => 'order_quick_order', // Title of the menu item
        'url' => '/order/quick_order', // url of the item
        'module_name' => 'order', // beloning to which module
        'parent' => 0, // does it have a parent item
        'weight' => 12, // weight
    );
}
    
$_INSTALL['PUBLIC_CLONE_URL'] = 'git://github.com/diversen/order.git';
$_INSTALL['PRIVATE_CLONE_URL'] = 'git@github.com:diversen/order.git';
