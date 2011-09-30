<?php

// diplay checkout submit button as a table

echo "<table>\n";
echo "<tr>\n";
echo "<td>\n";
echo "<form name=\"checkout\" method =\"get\" action=\"/order/checkout\">\n";
echo "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('order_buy') . "\" /> ";
echo "</form>\n";
echo "</td>\n";
echo "</tr>\n";
echo "</table>\n";