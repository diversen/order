<?php

echo "<table>\n";

foreach ($vars as $key => $val) {
    echo "<tr>\n";
    
    echo "<td>\n";
    echo $val['name'];
    echo "</td>\n";

    $url = "/order/category/edit/$val[id]";
    $title = lang::translate('order_edit');

    echo "<td>\n";
    echo html::createLink($url, $title);
    echo "</td>\n";
    //echo MENU_SUB_SEPARATOR;

    $url = "/order/category/delete/$val[id]";
    $title = lang::translate('order_delete');

    echo "<td>\n";
    echo html::createLink($url, $title);
    echo "</td>\n";
    
    //echo "<br />\n";
    echo "</tr>\n";
}

echo "</table>\n";