<?php

$order_items = $vars['order_items'];

print lang::translate('order_order_details');
print "\n\n";

$weight = $total = $sub_total = 0;
foreach ($order_items as $key => $val){
    if ($val == 0) continue;
    $item = order::getItem($key);
    if (empty($item)) {
        unset($order_items[$key]);
        continue;
    }

    print $item['item_name'] . " ";
    print order::getCurrencySymbol() . $item['price'];
    print " * " . $val;

    $sub_total = $val * $item['price'];
    print " = " . order::getCurrencySymbol() . " " . $sub_total . "\n";
    $total = $sub_total + $total;
    $weight = $weight + (locfloat_to_sysfloat($item['weight']) * $val);
}

print "\n";

print lang::translate('order_basket_total_price_items');
print ' = ';
print order::getCurrencySymbol() . $total . "\n";

print lang::translate('order_amount_value_added_tax');
print ' = ';
print order::getCurrencySymbol() ;    
print $total * get_module_ini('order_added_tax') . "\n";

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

print lang::translate('order_amount_added_shipping_cost');
print ' = ';
print order::getCurrencySymbol();
print $shipping_cost;
print "\n";

print lang::translate('order_amount_total');
print ' = ';
$total = $total + $shipping_cost;
print order::getCurrencySymbol() . $total . "\n\n";



        


