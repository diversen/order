<?php

$order_items = $vars['order_items'];

echo "<h3>" . lang::translate("order_details") . "</h3>\n";


$vars['disable_item_edit_buttons'] = true;
templateView::includeModuleView('order', 'display_basket', $vars);

/*
print "<table class=\"order_cart\">\n";
print "<tr>";
print "<td colspan=\"5\">\n";
print "<h3>" . lang::translate("order_details") . "</h3>\n";
print "</td>\n";
print "</tr>\n";

print "<tr>";
print "<td colspan=\"2\">";
print "</td><td>\n";
print lang::translate('order_quantity');
print "</td><td>\n";
print lang::translate('order_sub_total');
print "</td><td>\n";
print lang::translate('order_amount_total');
print "</td>";
print "</tr>\n";

$total = $sub_total = $weight = 0;
foreach ($order_items as $key => $val){
    if ($val == 0) continue;
    $item = order::getItem($val['item_id']);
    if (empty($item)) {
        unset($order_items[$key]);
        continue;
    }

    $options = array ();
    $options['alt'] = $item['item_name_alt'];
    $options['width'] = "75"; 

    print "<tr>\n";
    print "<td>";
    if (!empty($item['file'])){
        print $link = create_image_link(
                "/order/item/$item[id]/"  . 
                rawurlencode($item['item_name']), 
                "/order/download/$item[id]/thumb/$item[md5]", 
                $options
            );
    }


    print "</td>";
    print "<td>";
    print $link = create_link("/order/item/$item[id]/" . rawurlencode ($item['item_name']) , $item['item_name']) . "<br />\n";
    print order::getCurrencySymbol() . '&nbsp;' . $item['price']; // . "<br />";
    print "</td><td>\n";
    print $val;
    print "</td><td>\n";
    print order::getCurrencySymbol() . '&nbsp;';
    $sub_total = $val['add_order'] * $item['price'];
    print $sub_total;
    $total = $sub_total + $total;
    $weight = $weight + ($val['add_order'] * locfloat_to_sysfloat($item['weight']));

    print "</td>\n";
    print "<td>&nbsp;</td>";
    print "</tr>\n";
}
print "<tr>\n";
print "<td colspan=\"3\">";
print lang::translate('order_basket_total_price_items');
print "</td>";
print "<td>&nbsp;</td>\n";
print "<td>";

print order::getCurrencySymbol() . '&nbsp;';
print $total;
print "</td>\n";
print "</tr>\n";

print "<tr>\n";
print "<td colspan=\"4\">\n";
print lang::translate('order_amount_value_added_tax');
print "</td>";
print "<td>";
print order::getCurrencySymbol() . '&nbsp;';
print $total * get_module_ini('order_added_tax');
print "</td>\n";
print "</tr>\n";

print "<tr>\n";
print "<td  colspan=\"4\">\n";
print lang::translate('order_amount_added_shipping_cost') . " ";

$shipping_is_free = false;
$shipping_free = orderShippingFree::getShippingFreePrivate();
if ($total <  $shipping_free) {
    $shipping_free_needed = order::getCurrencySymbol() . '&nbsp;';
    $shipping_free_needed.= $shipping_free - $total;
    print lang::translate('order_amount_before_shipping_free', array($shipping_free_needed)) . ' ';
} else {
    $shipping_is_free = true;
    print lang::translate('order_amount_shipping_is_free') . ' ';
}

print "</td>\n";
print "<td>\n";
print order::getCurrencySymbol() . '&nbsp;';
if ($shipping_is_free) {
    print "0";
    $shipping_cost = 0;
} else {
    print $shipping_cost = orderShipping::getWeightToCost('private', $weight);
}
print "</td>\n";

print "</tr>\n";

print "<tr>\n";
print "<td  colspan=\"4\">\n";
print lang::translate('order_amount_total');
print "</td>\n";
print "<td>\n";
print order::getCurrencySymbol() . '&nbsp;';
print $shipping_cost + $total;
//print orderShipping::getWeightToCost('private', $weight) . ' ';
print "</td>\n";

print "</tr>\n";

print "<table>\n";
 * 
 */
