<?php

include_module('order');

function block_order_cart () {

    $order_items = order::getBasketItems();
    $total_weight = 0;
    $total = $sub_total = $weight = $num_items = 0;

    foreach ($order_items as $key => $val){
        if ($val['add_order'] == 0) continue;
        $item = order::getItem($val['item_id']);
        if (empty($item)) {
            unset($order_items[$key]);
            continue;
        }
        $num_items = $num_items + $val['add_order'];
        $sub_total = $val['add_order'] * $item['price'];
        $total = $sub_total + $total;
        $weight = $weight + ($val['add_order'] * $item['weight']);
    }

    echo "<h3>" . lang::translate('order_basket') . "</h3>\n";
    echo "<table class=\"order_basket\">\n";
    echo "<tr>\n";

    echo "<td>";
    echo lang::translate('order_total_num_items');
    echo "</td>";

    echo "<td>\n";
    echo ' ' . $num_items;
    echo "</td>\n";

    echo "</tr>\n";
    echo "<tr>\n";

    echo "<td>";
    echo lang::translate('order_basket_total_price_items');
    echo "</td>";
    
    echo "<td>";
    echo order::getCurrencySymbol() . '&nbsp;' . format_float_mon($total);
    echo "</td>";

    echo "</tr>\n";
    echo "<tr>\n";

    echo "<td>";
    echo lang::translate('order_amount_value_added_tax');
    echo "</td>";
    
    echo "<td>";
    echo order::getCurrencySymbol() . '&nbsp;';
    $total_with_tax = $total * get_module_ini('order_added_tax');
    echo format_float_mon($total_with_tax);
    
    echo "</td>";

    echo "</tr>\n";

    echo "<tr>\n";
    echo "<td>\n";
    echo lang::translate('order_amount_added_shipping_cost') . " ";
    echo "</td>";

    echo "<td>";
    $shipping_is_free = false;
    $shipping_free = orderShippingFree::getShippingFreePrivate();
    if (count($order_items) == 0) {
        $shipping_is_free = true;
        $shipping_free_str = lang::translate('order_amount_shipping_is_free') . '&nbsp;';
    }
    
    else if ($total <  $shipping_free) {
        $shipping_free_needed = order::getCurrencySymbol() . "&nbsp;";
        $shipping_free_needed.= format_float_mon($shipping_free - $total);
        $shipping_free_str = lang::translate('order_amount_before_shipping_free', array($shipping_free_needed)) . '';
    } else {
        $shipping_is_free = true;
        $shipping_free_str = lang::translate('order_amount_shipping_is_free') . '&nbsp;';
    }

    echo order::getCurrencySymbol() . "&nbsp;";
    if ($shipping_is_free) {
        echo "0";
        $shipping_cost = 0;
    } else {
        $shipping_cost = orderShipping::getWeightToCost('private', $weight);
        echo format_float_mon($shipping_cost);
    }

    echo "</td>";
    echo "</tr>\n";

    echo "<tr>\n";
    echo "<td colspan=\"2\">";

    echo $shipping_free_str;
    echo "</td>";
    echo "</tr>\n";

    echo "<tr>\n";
    echo "<td>\n";

    echo lang::translate('order_amount_total');

    echo "</td>";
    echo "<td>";

    echo order::getCurrencySymbol() . "&nbsp;";
    $total_with_shipping = $shipping_cost + $total;
    echo format_float_mon($total_with_shipping);
    echo "</td>";
    echo "</tr>\n";

    echo "</table>\n";

    echo "<table class=\"order_cart\">\n";
    echo "<tr>\n";

    echo "<td>";
    echo "<form method =\"get\" action=\"/order/basket\">\n";
    echo "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('order_basket') . "\" /> ";
    echo "</form>\n";
    echo "</td>";

    echo "<td>";
    echo "<form method =\"get\" action=\"/order/checkout\">\n";
    echo "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('order_buy') . "\" /> ";
    echo "</form>\n";
    echo "</td>";

    echo "</tr>\n";
    echo "</table>";
    echo "<br />\n";
}