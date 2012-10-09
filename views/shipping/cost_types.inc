<?php

echo "<table>";
foreach ($vars as $key => $val) {
    $options = array ('title' => $val['description']);
    echo "<tr>\n";
    echo "<td colspan=2>";
    headline_message(html::createLink("/order/shipping/edit_type/$val[id]", $val['name'], $options));
    echo "</td>";
    echo "</tr>";
    echo "<tr>\n";

    echo "<td>" . html::createLink("/order/shipping/edit_type_table/$val[id]", 
            lang::translate('order_shipping_menu_edit_table')) . MENU_SUB_SEPARATOR .

            "</td>";
    echo "<td>" . html::createLink("/order/shipping/delete_type/$val[id]", 
            lang::translate('order_shipping_menu_delete_type')) . "</td>";
    echo "</tr>\n";
}

echo "</tr></table>\n";