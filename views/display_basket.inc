<?php

$order_items = $vars['order_items'];
$total_weight = 0;

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
$total = $sub_total = $weight = 0;
foreach ($order_items as $key => $val){
    if ($val == 0) continue;
    $item = order::getItem($key);
    if (empty($item)) {
        unset($order_items[$key]);
        continue;
    }
    print "<tr>\n";
    print "<td>";

    $options = array ();
    $options['alt'] = $val['item_name_alt'];
    $options['width'] = get_module_ini('order_image_size_thumb');

    if (!empty($item['file'])){
        $link =
            create_image_link(
                "/order/item/$key/"  .
                rawurlencode($item['item_name']),
                "/order/download/$key", $options);
        print $link;

    } else {
        print "&nbsp;";
    }
    print "</td>";
    print "<td>";
    print $link = create_link("/order/item/$key/" . rawurlencode ($item['item_name']) , $item['item_name']) . "<br />\n";
    print order::getCurrencySymbol();
    print ' ' . $item['price'];
    print "</td><td>\n";
    print "<form name=\"checkout\" method =\"post\" action=\"\">";
    print "<input type=\"hidden\" name = \"item_id\" value =\"$item[id]\" />";
    print "<input type=\"text\" name=\"add_order\" size =\"2\" maxlength=\"2\" value=\"$val\" />";// . "<br />";
    print "<input class=\"order_cart\" type =\"submit\" name=\"item_update\" value=\"" . lang::translate('order_item_update') . "\" /> ";
    print "</form>\n";
    print "</td><td>\n";
    print order::getCurrencySymbol() . '';
    $sub_total = $val * $item['price'];
    //$sub_total_weight = $val * $item['weight'];

    print $sub_total;
    $total = $sub_total + $total;
    $weight = $weight + ($val * $item['weight']);
    print "</td>\n";
    print "<td>&nbsp;</td>";
    print "<td>&nbsp;</td>\n";
    print "</tr>\n";

}
print "<tr>\n";
print "<td colspan=\"4\">";
print lang::translate('order_amount_total');
print "</td>";
print "<td>";
print order::getCurrencySymbol() . ' ';
print $total;
print "</td>\n";
print "<td>&nbsp;</td>\n";
print "</tr>\n";

/*
print "<tr>\n";
print "<td colspan=\"4\">";
print lang::translate('order_amount_value_added_tax');
print "</td>";
print "<td>";
print order::getCurrencySymbol() . ' ';
//print $total * get_module_ini('order_added_tax');
print "total vægt  = $total_weight";
print "</td>\n";
print "<td>&nbsp;</td>\n";
print "</tr>\n";
    */
print "<tr>\n";
print "<td colspan=\"4\">";
print lang::translate('order_amount_value_added_tax');
print "</td>";
print "<td>";
print order::getCurrencySymbol() . ' ';
print $total * get_module_ini('order_added_tax');
print "</td>\n";
print "<td>&nbsp;</td>\n";
print "</tr>\n";

print "<tr>\n";
print "<td  colspan=\"4\">\n";
print lang::translate('order_amount_added_shipping_cost');

print "<br />";
print lang::translate('order_private') . ' ';
print orderShipping::getWeightToCost('private', $weight) . ' ';
print order::getCurrencySymbol();

/*

print "<br />";
print lang::translate('order_company') . ' ';
print orderShipping::getWeightToCost('company', $weight) . ' ';
print order::getCurrencySymbol();
*/

print "</td>\n";
print "<td>&nbsp</td>\n";
print "<td>";

/*
$_POST['company'] = trim ($_POST['company']);
if (isset($_POST['company']) && !empty($_POST['company'])) {
    print orderShipping::getWeightToCost('company', $weight);
} else {
    print orderShipping::getWeightToCost('private', $weight);
}
*/
//print "vægt " . $weight;
print "</td>\n";
print "</tr>\n";


print "<td colspan=5>";
print "&nbsp;";
print "</td>";
print "<td>";
print "<form name=\"checkout\" method =\"get\" action=\"/order/checkout\">\n";
print "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('order_buy') . "\" /> ";
print "</form>\n";
print "</td>\n";
print "</tr>\n";
print "<table>\n";
