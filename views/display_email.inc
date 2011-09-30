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
    echo order::getCurrencySymbol() . ' ' . $item['price'];
    echo " * " . $val['add_order'];

    $sub_total = $val['add_order'] * $item['price'];
    echo " = " . order::getCurrencySymbol() . " " . $sub_total . "\n";
    $total = $sub_total + $total;
    $weight = $weight + (locfloat_to_sysfloat($item['weight']) * $val['add_order']);
}

echo "\n";

echo lang::translate('order_basket_total_price_items');
echo ' = ';
echo order::getCurrencySymbol() . ' ' . $total . "\n";

echo lang::translate('order_amount_value_added_tax');
echo ' = ';
echo order::getCurrencySymbol() . ' ';
echo $total * get_module_ini('order_added_tax') . "\n";

$shipping_is_free = false;
$shipping_free = orderShippingFree::getShippingFreePrivate();
if ($total <  $shipping_free) {
    //
} else {
    $shipping_is_free = true;
}

if ($shipping_is_free) {
    $shipping_cost = 0;
} else {
    $shipping_cost = orderShipping::getWeightToCost('private', $weight);
}

echo lang::translate('order_amount_added_shipping_cost');
echo ' = ';
echo order::getCurrencySymbol() . ' ';
echo $shipping_cost;
echo "\n";

echo lang::translate('order_amount_total');
echo ' = ';
$total = $total + $shipping_cost;
echo order::getCurrencySymbol() . ' ' . $total . "\n\n";
