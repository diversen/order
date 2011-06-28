<?php

/**
 * block file is used for showing content categories
 *
 * @package content
 */

/**
 * function for showing a category block
 *
 * @return string   category block as html
 */
include_model ('order');

function block_item_info(){
    $cart = new order ();
    //$str = '<div id ="block_menu">';
    $str = '';
    $str.="<h3>" . lang::translate ('Varer') . "</h3>\n";
    $str.="<ul>\n";
    $items = $cart->getItemsInBlock();
    foreach ($items as $key => $val){
        $str.= "<li>". create_link("/order/item/$val[id]/" . rawurlencode($val['item_name']), $val['item_name_alt']) . "</li>";
    }
    $str.="</ul>\n";
    return $str;
}


