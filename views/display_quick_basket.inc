<?php

$all_items = $vars['all_items'];
$order_items = $vars['order_items'];

print "<table class=\"order_cart\">\n";
print "<tr>";
print "<td colspan=\"2\"></td>\n";
print "<td>";
print lang::translate('order_quantity');
print "</td>";
print "<td>\n";
print lang::translate('order_sub_total');
print "</td>";
print "<td>\n";
print lang::translate('order_amount_total');
print "</td>";
print "<td>&nbsp;</td>";
print "</tr>\n";
$weight = $total = $sub_total = 0;

foreach ($all_items as $key => $val){

    $item = order::getItem($val['id']);

    if (isset($order_items[$item['id']])){
        $val = $order_items[$item['id']];
    } else {
        $val = 0;
    }
    print "<tr>\n";
    print "<td>";

    $options = array ();
    $options['alt'] = $val['item_name_alt'];
    $options['width'] = '75px';/*get_module_ini('order_image_size_thumb')*/;

    if (!empty($item['file'])){
        $link =
            create_image_link(
                "/order/item/$item[id]/" . rawurlencode($item['item_name']),
                "/order/download/$item[id]", $options);
        print $link;
    }
    print "</td>";
    print "<td>";
    $link = create_link(
        "/order/item/$item[id]/" . rawurlencode ($item['item_name']) ,
        $item['item_name']);
    print $link;
    print "<br />\n";
    print order::getCurrencySymbol() . '&nbsp;' . $item['price'];
    print "</td><td>\n";
    print "<form name=\"checkout\" method =\"post\" action=\"\">";
    print "<input type=\"hidden\" name = \"item_id\" value =\"$item[id]\" />";
    print "<input type=\"text\" name=\"add_order\" size =\"2\" maxlength=\"2\" value=\"$val\" />";// . "<br />";
    print "<input class=\"order_cart\" type =\"submit\" name=\"item_update\" value=\"" . lang::translate('order_item_update') . "\" /> ";
    print "</form>\n";
    print "</td><td>\n";
    print order::getCurrencySymbol() . '&nbsp;';
    $sub_total = $val * $item['price'];
    print $sub_total;
    $total = $sub_total + $total;

    $weight = $weight + ($val * locfloat_to_sysfloat($item['weight']));

    print "</td>\n";
    print "<td>&nbsp;</td>";
    print "<td>&nbsp;</td>\n";
    print "</tr>\n";

}
print "<tr>\n";
print "<td colspan=\"4\">";
print lang::translate('order_basket_total_price_items');
print "</td>";
print "<td>";
print order::getCurrencySymbol() . '&nbsp;' . $total;
print "</td>\n";
print "<td>&nbsp;</td>\n";
print "</tr>\n";


print "<tr>\n";
print "<td colspan=\"4\">";
print lang::translate('order_amount_value_added_tax');
print "</td>";
print "<td>";
print order::getCurrencySymbol() . '&nbsp;';
print $total * get_module_ini('order_added_tax');
print "</td>\n";
print "<td>&nbsp;</td>\n";
print "</tr>\n";

print "<tr>\n";
print "<td  colspan=\"4\">\n";
print lang::translate('order_amount_added_shipping_cost') . " ";

$shipping_is_free = false;
$shipping_free = orderShippingFree::getShippingFreePrivate();
if ($total <  $shipping_free) {
    $shipping_free_needed = order::getCurrencySymbol() . '&nbsp;';
    $shipping_free_needed.= $shipping_free - $total;
    print lang::translate('order_amount_before_shipping_free', array($shipping_free_needed)) . '&nbsp;';
} else {
    $shipping_is_free = true;
    print lang::translate('order_amount_shipping_is_free') . '&nbsp;';
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
print "<td>&nbsp</td>\n";
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
print "<td>&nbsp</td>\n";
print "</tr>\n";

print "<td colspan=5>";
print "&nbsp;";
print "</td>";

print "</table>\n";

print "<table><tr><td>\n";
//print "<td>";
print "<form name=\"checkout\" method =\"get\" action=\"/order/checkout\">\n";
print "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('order_buy') . "\" /> ";
//print "</form>\n";
print "</td>\n";
print "</tr>\n";
print "</table>\n";
