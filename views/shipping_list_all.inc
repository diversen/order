<?php

print_r($vars);
echo "<table>\n";
echo "<tr>\n";

$weight = lang::translate('order_shipping_td_weight');

echo "<td>" . $weight  . "</td>";

echo "<td>" . lang::translate('order_shipping_td_cost') . "</td>";

echo "</tr>\n";
foreach ($vars as $key => $row) {
    echo "<tr>\n";
    echo "<td>$row[weight]</td>\n";
    echo "<td>$row[cost]</td>\n";
    echo "</tr>\n";
}

echo "</table>\n";