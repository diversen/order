<?php

// create email

$order_items = $vars['order_items'];

//echo "\n\n";

$weight = $total = $sub_total = 0;
foreach ($order_items as $key => $val){
    if ($val == 0) continue;
    $item = order::getItem($val['item_id']);
    if (empty($item)) {
        unset($order_items[$key]);
        continue;
    }

    echo $item['item_name'];
    
    echo orderSelect::getSelectListAsHumanFields($item['id'], $val, array('display_email' => true));
    echo " ";
    echo order::getCurrencySymbol() . ' ' . format_float_mon($item['price']);
    echo " * " . $val['add_order'];

    $sub_total = $val['add_order'] * $item['price'];
    echo " = " . order::getCurrencySymbol() . " " . format_float_mon($sub_total) . "<br />";
    $total = $sub_total + $total;
    $weight = $weight + ($item['weight'] * $val['add_order']);
}

echo "<br />";

echo lang::translate('order_basket_total_price_items');
echo ' = ';
echo order::getCurrencySymbol() . ' ' . format_float_mon($total) . "<br />";

echo lang::translate('order_amount_value_added_tax');
echo ' = ';
echo order::getCurrencySymbol() . ' ';
$tax = $total * get_module_ini('order_added_tax');
echo format_float_mon($tax) . "<br />";

$shipping_info = orderShipping::getShippingInfo($order_items, $total, $weight);

echo lang::translate('order_amount_added_shipping_cost');
echo ' = ';
echo order::getCurrencySymbol() . ' ';
echo $shipping_info['shipping_cost'];
echo "<br />";

echo lang::translate('order_amount_total');
echo ' = ';

echo order::getCurrencySymbol() . ' ' . $shipping_info['total_cost'];
