<?php

// create email

$order_items = $vars['order_items'];
echo lang::translate('order_order_details');
echo "\n\n";

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
    echo " = " . order::getCurrencySymbol() . " " . format_float_mon($sub_total) . "\n";
    $total = $sub_total + $total;
    $weight = $weight + ($item['weight'] * $val['add_order']);
}

echo "\n";

echo lang::translate('order_basket_total_price_items');
echo ' = ';
echo order::getCurrencySymbol() . ' ' . format_float_mon($total) . "\n";

echo lang::translate('order_amount_value_added_tax');
echo ' = ';
echo order::getCurrencySymbol() . ' ';
$total_with_tax = $total * get_module_ini('order_added_tax');
echo format_float_mon($total_with_tax) . "\n";

$shipping_is_free = false;
$shipping_free = orderShippingFree::getShippingFreePrivate();
if (count($order_items) == 0) {
    $shipping_is_free = true;
    $shipping_free_str = lang::translate('order_amount_shipping_is_free') . '&nbsp;';
} else if ($shipping_free == 0) {
    $shipping_free_str = '';
    $shipping_is_free = false;
} else if ( $total <  $shipping_free ) {
    $shipping_free_needed = order::getCurrencySymbol() . "&nbsp;";
    $shipping_free_needed.= format_float_mon($shipping_free - $total);
    $shipping_free_str = lang::translate('order_amount_before_shipping_free', array($shipping_free_needed)) . '';
} else {
    $shipping_is_free = true;
    $shipping_free_str = lang::translate('order_amount_shipping_is_free') . '&nbsp;';
}

if ($shipping_is_free) {
    $shipping_cost = 0;
} else {
    $shipping_cost = orderShipping::getWeightToCost('private', $weight);
}

echo lang::translate('order_amount_added_shipping_cost');
echo ' = ';
echo order::getCurrencySymbol() . ' ';
echo format_float_mon($shipping_cost);
echo "\n";

echo lang::translate('order_amount_total');
echo ' = ';
$total = $total + $shipping_cost;
echo order::getCurrencySymbol() . ' ' . format_float_mon($total) . "\n\n";
