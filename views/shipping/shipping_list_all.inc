<?php

echo "<table>\n";
echo "<tr>\n";

$weight = lang::translate('order_shipping_weight');

echo "<td>" . $weight  . "</td>";

echo "<td>" . lang::translate('order_shipping_cost') . "</td>";
echo "<td>&nbsp;</td>\n";

echo "</tr>\n";
foreach ($vars as $key => $row) {
    echo "<tr>\n";
    echo "<td>$row[weight]</td>\n";
    echo "<td>$row[cost]</td>\n";
    echo "<td>";
    orderShipping::adminOptions($row['id']);
    echo "</td>\n";
    echo "</tr>\n";
}

echo "</table>\n";