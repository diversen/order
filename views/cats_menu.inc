<?php


if (!isset($_GET['cat']) || ($_GET['cat'] == '0') ) {
    echo html::createLink(
        "/order/cart?cat=0", lang::translate('order_cat_show_all'),
        array('id' => 'order_cat_menu_active')
    );
} else {
    echo html::createLink(
        "/order/cart?cat=0",
        lang::translate('order_cat_show_all'),
        array('id' => 'order_cat_menu'));
}

echo "<span id=\"order_cat_menu\">" . MENU_SUB_SEPARATOR_SEC . "</span>";

$i = count($vars);
foreach($vars as $key => $val) {
    //echo "<span id=\"order_cat_menu\">" . MENU_SUB_SEPARATOR . "</span>";
    if (isset($_GET['cat']) && ($_GET['cat'] == $val['id'])) {
        echo html::createLink("/order/cart?cat=$val[id]", 
            "$val[name]", 

        array('id' => 'order_cat_menu_active'));
    } else {
        echo html::createLink("/order/cart?cat=$val[id]", 
            "$val[name]", 
            array('id' => 'order_cat_menu'));
    } 
    $i--;
    if ($i) {
        echo "<span id=\"order_cat_menu\">" . MENU_SUB_SEPARATOR . "</span>";
    }
    
}

echo "<br /><br />\n";