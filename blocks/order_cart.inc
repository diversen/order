<?php

include_module('order');

function block_order_cart () {

    $cart_info = order::getFullCartInfo();

    echo "<h3>" . lang::translate('order_basket') . "</h3>\n";
    echo "<table class=\"order_basket\">\n";
    echo "<tr>\n";

    echo "<td>";
    echo lang::translate('order_total_num_items');
    echo "</td>";

    echo "<td>\n";
    echo ' ' . $cart_info['num_items'];
    echo "</td>\n";

    echo "</tr>\n";
    echo "<tr>\n";

    echo "<td>";
    echo lang::translate('order_basket_total_price_items');
    echo "</td>";
    
    echo "<td>";
    echo order::getCurrencySymbol() . '&nbsp;' . format_float_mon($cart_info['total']);
    echo "</td>";

    echo "</tr>\n";
    echo "<tr>\n";

    echo "<td>";
    echo lang::translate('order_amount_value_added_tax');
    echo "</td>";
    
    echo "<td>";
    echo order::getCurrencySymbol() . '&nbsp;';

    echo format_float_mon($cart_info['tax']);
    echo "</td>";
    echo "</tr>\n";

    // shipping info
    
    $order_items = order::getBasketItems();    
    $shipping_free_info = orderShippingfree::getShippingFreeInfo(
            $order_items, 
            $cart_info['total']);
    
    $shipping_info = orderShipping::getShippingInfo(
            $order_items, 
            $cart_info['total'], 
            $cart_info['weight']);

    
    
    
    //print_r($shipping_info);

    echo "<tr>\n";
    echo "<td colspan=\"2\">";
    echo $shipping_free_info['shipping_free_str'];
    
    // no cost type selected
    if (!isset($shipping_info['shipping_cost'])) {
        echo lang::translate('order_amount_added_shipping_cost_final');
    }
    
    
    echo "</td>";
    echo "</tr>\n";

    // no shipping free
    if (!$shipping_free_info['shipping_is_free']) {
        
       
        //print_r($shipping_info);
        
        // shipping type has been set
        if (isset($shipping_info['shipping_cost'])) {
            echo "<tr>\n";
            echo "<td>";
            echo $shipping_info['type']['name'];
            echo "</td>";
            echo "<td>";
            echo order::getCurrencySymbol() . ' ' . format_float_mon($shipping_info['shipping_cost']) . ' ';           
            echo "</tr>\n";
            $cart_info['total']+= $shipping_info['shipping_cost'];
        }
        
    }
    
    
    echo "<tr>\n";
    echo "<td>\n";
    echo lang::translate('order_amount_total');
    echo "</td>";
    echo "<td>";

    echo order::getCurrencySymbol() . "&nbsp;";
    echo format_float_mon($cart_info['total']);

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