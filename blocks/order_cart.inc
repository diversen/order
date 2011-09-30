<?php

include_module('order');

function block_order_cart () {

    $order_items = order::getBasketItems();
    print_r($order_items);
    $total_weight = 0;
    $total = $sub_total = $weight = $num_items = 0;

    foreach ($order_items as $key => $val){
        if ($val['add_order'] == 0) continue;
        $item = order::getItem($key);
        if (empty($item)) {
            unset($order_items[$key]);
            continue;
        }
        $num_items = $num_items + $val['add_order'];
        $sub_total = $val['add_order'] * $item['price'];
        $total = $sub_total + $total;
        $weight = $weight + ($val['add_order'] * locfloat_to_sysfloat($item['weight']));
    }

    print "<h3>" . lang::translate('order_basket') . "</h3>\n";
    print "<table class=\"order_basket\">\n";
    print "<tr>\n";

    print "<td>";
    print lang::translate('order_total_num_items');
    print "</td>";

    print "<td>\n";
    print ' ' . $num_items;
    print "</td>\n";

    print "</tr>\n";
    print "<tr>\n";

    print "<td>";
    print lang::translate('order_basket_total_price_items');
    print "</td>";
    
    print "<td>";
    print order::getCurrencySymbol() . '&nbsp;' . $total;
    print "</td>";

    print "</tr>\n";
    print "<tr>\n";

    print "<td>";
    print lang::translate('order_amount_value_added_tax');
    print "</td>";
    
    print "<td>";
    print order::getCurrencySymbol() . '&nbsp;';
    print $total * get_module_ini('order_added_tax');
    print "</td>";

    print "</tr>\n";

    print "<tr>\n";
    print "<td>\n";
    print lang::translate('order_amount_added_shipping_cost') . " ";
    print "</td>";

    print "<td>";
    $shipping_is_free = false;
    $shipping_free = orderShippingFree::getShippingFreePrivate();
    if ($total <  $shipping_free) {
        $shipping_free_needed = order::getCurrencySymbol() . "&nbsp;";
        $shipping_free_needed.= $shipping_free - $total;
        $shipping_free_str = lang::translate('order_amount_before_shipping_free', array($shipping_free_needed)) . '';
    } else {
        $shipping_is_free = true;
        $shipping_free_str = lang::translate('order_amount_shipping_is_free') . '&nbsp;';
    }

    print order::getCurrencySymbol() . "&nbsp;";
    if ($shipping_is_free) {
        print "0";
        $shipping_cost = 0;
    } else {
        print $shipping_cost = orderShipping::getWeightToCost('private', $weight);
    }

    print "</td>";
    print "</tr>\n";

    print "<tr>\n";
    print "<td colspan=\"2\">";

    print $shipping_free_str;
    print "</td>";
    print "</tr>\n";

    print "<tr>\n";
    print "<td>\n";

    print lang::translate('order_amount_total');

    print "</td>";
    print "<td>";

    print order::getCurrencySymbol() . "&nbsp;";
    print $shipping_cost + $total;
    print "</td>";
    print "</tr>\n";

    print "</table>\n";

    print "<table class=\"order_cart\">\n";
    print "<tr>\n";

    print "<td>";
    print "<form name=\"checkout\" method =\"get\" action=\"/order/basket\">\n";
    print "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('order_basket') . "\" /> ";
    print "</form>\n";
    print "</td>";

    print "<td>";
    print "<form name=\"checkout\" method =\"get\" action=\"/order/checkout\">\n";
    print "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('order_buy') . "\" /> ";
    print "</form>\n";
    print "</td>";

    print "</tr>\n";
    print "</table>";
    print "<br />\n";
}