<?php

// create email
$full = order::getFullCartInfo();

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
    
    //echo orderSelect::getSelectListAsHumanFields($item['id'], $val, array('display_email' => true));
    echo " ";
    echo order::getCurrencyShort($item['price'], ' ');
    echo " * " . $val['num_items'];

    $sub_total = $val['num_items'] * $item['price'];
    echo " = " . order::getCurrencyShort($sub_total, ' ') . "\n";
    //$total = $sub_total + $total;
    //$weight = $weight + ($item['weight'] * $val['num_items']);
}

echo "\n";

echo lang::translate('order_basket_total_price_items');
echo ' = ';
echo order::getCurrencyShort($full['total'], ' ') . "\n";

echo lang::translate('order_amount_value_added_tax');
echo ' = ';
//echo order::getCurrencySymbol() . ' ';
//$tax = $full['total * config::getModuleIni('order_added_tax');
echo order::getCurrencyShort($full['tax'], ' ') . "\n";

// calculate shipping row
//$order_items = order::getBasketItems();    
$shipping_free_info = orderShippingfree::getShippingFreeInfo(
    $order_items, 
    $full['total']);
    
$shipping_info = orderShipping::getShippingInfo(
    $order_items, 
    $full['total'], 
    $full['weight']);




if (!$shipping_free_info['shipping_is_free']) {
    // no shipping free
    // shipping type has been set
    if (isset($shipping_info['shipping_cost'])) {
        echo $shipping_info['type']['name'];
        echo " = ";
        echo order::getCurrencyShort($shipping_info['shipping_cost'], ' ');
        $full['total']+= $shipping_info['shipping_cost'];
    }       
} else {
    echo $shipping_free_info['shipping_free_str'];
}

echo  "\n";

echo lang::translate('order_amount_total');
echo ' = ';
echo order::getCurrencyShort($full['total'], ' ');
echo "\n\n";
