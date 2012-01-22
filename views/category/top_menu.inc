<?php

$id = orderCategory::getCatId();

if (!$id){
    echo html::createLink(
        "/order/cart", lang::translate('order_cat_show_all'),
        array('class' => 'order_cat_menu_active')
    );
} else {
    echo html::createLink(
        "/order/cart",
        lang::translate('order_cat_show_all'),
        array('class' => 'order_cat_menu'));
}

echo "<span class=\"order_cat_menu\">" . MENU_SUB_SEPARATOR_SEC . "</span>";

$i = count($vars);
foreach($vars as $key => $val) {
    //echo "<span id=\"order_cat_menu\">" . MENU_SUB_SEPARATOR . "</span>";
    $url = strings::utf8Slug("/order/cart/$val[id]", $val['name']);
    if ($id) {
        
        echo html::createLink($url, 
            html::specialEncode($val['name']), 

        array('class' => 'order_cat_menu_active'));
    } else {
        echo html::createLink($url, 
            html::specialEncode($val[name]), 
            array('class' => 'order_cat_menu'));
    } 
    $i--;
    if ($i) {
        echo "<span class=\"order_cat_menu\">" . MENU_SUB_SEPARATOR . "</span>";
    }
    
}

echo "<br /><br />\n";