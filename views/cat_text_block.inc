<?php

echo "<div class =\"block\">\n";
echo "<ul id=\"content_tree\">\n";
foreach($vars as $key => $val) {
    //echo "<span id=\"order_cat_menu\">" . MENU_SUB_SEPARATOR . "</span>";
    echo "<li>";
    if (isset($_GET['cat']) && ($_GET['cat'] == $val['id'])) {
        echo html::createLink("/order/cart?cat=$val[id]", 
            "$val[name]", 

        array('class' => 'current'));
    } else {
        echo html::createLink("/order/cart?cat=$val[id]", 
            "$val[name]", 
            array());
    } 
    echo "</li>\n";
    //$i--;
    //if ($i) {
        //echo "<span class=\"order_cat_menu\">" . MENU_SUB_SEPARATOR . "</span>";
    //}
    
}

echo "</ul>\n";
echo "<hr />\n";
echo "</div>\n";
