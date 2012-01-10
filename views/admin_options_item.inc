<?php

// admin_options_item.inc
// base admin options (edit | delete ) for item

$str = '';
if (session::isAdmin()){
    $str.= html::createLink(
        "/order/products/edit/$vars[id]",
        lang::translate('order_edit')
    );
    $str.= MENU_SUB_SEPARATOR;
    $str.= html::createLink(
        "/order/products/delete/$vars[id]",
        lang::translate('order_delete')
    );
    echo $str;
}