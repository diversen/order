<?php

$order_items = $vars['order_items'];

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
    $item = order::getItem($key);
    if (empty($item)) {
        unset($order_items[$key]);
        continue;
    }

    $options = array ();
    $options['alt'] = $val['item_name_alt'];
    $options['width'] = get_module_ini('order_image_size_thumb');

    print "<tr>\n";
    print "<td>";
    if (!empty($item['file'])){
        print $link = create_image_link("/order/item/$item[id]/"  . rawurlencode($val['item_name']), "/order/download/$item[id]", $options);
    }


    print "</td>";
    print "<td>";
    print $link = create_link("/order/item/$key/" . rawurlencode ($item['item_name']) , $item['item_name']) . "<br />\n";
    print order::getCurrencySymbol() . $item['price']; // . "<br />";
    print "</td><td>\n";
    print $val;
    print "</td><td>\n";
    print order::getCurrencySymbol() . ' ';
    $sub_total = $val * $item['price'];
    print $sub_total;
    $total = $sub_total + $total;
    $weight = $weight + ($val * $item['weight']);

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

print order::getCurrencySymbol() . ' ';
print $total;
print "</td>\n";
print "</tr>\n";

print "<tr>\n";
print "<td colspan=\"4\">\n";
print lang::translate('order_amount_value_added_tax');
print "</td>";
print "<td>";
print order::getCurrencySymbol() . ' ';
print $total * get_module_ini('order_added_tax');
print "</td>\n";
print "</tr>\n";

print "<tr>\n";
print "<td  colspan=\"4\">\n";
print lang::translate('order_amount_added_shipping_cost');
print "</td>\n";
print "<td>";


print order::getCurrencySymbol() . ' ';
print $shipping_cost = orderShipping::getWeightToCost('private', $weight);


print "</td>\n";
print "</tr>\n";

print "<tr>\n";
print "<td  colspan=\"4\">\n";
print lang::translate('order_amount_total');
print "</td>\n";
print "<td>\n";
print order::getCurrencySymbol();
print $shipping_cost + $total;
//print orderShipping::getWeightToCost('private', $weight) . ' ';
print "</td>\n";

print "</tr>\n";

print "<table>\n";
