<?php

$str = '';
if (session::isAdmin()){
    $str.= create_link(
        "/order/products/edit/$vars[id]",
        lang::translate('order_edit')
    );
    $str.= MENU_SUB_SEPARATOR;
    $str.= create_link(
        "/order/products/delete/$vars[id]",
        lang::translate('order_delete')
    );
    echo $str;
}