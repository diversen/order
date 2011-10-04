<?php

$all_items = $vars['all_items'];
$order_items = $vars['order_items'];

echo "<table class=\"order_cart\">\n";
echo "<tr>";
echo "<td colspan=\"2\"></td>\n";
echo "<td>";
echo lang::translate('order_quantity');
echo "</td>";
echo "<td>\n";
echo lang::translate('order_sub_total');
echo "</td>";
echo "<td>\n";
echo lang::translate('order_amount_total');
echo "</td>";
echo "<td>&nbsp;</td>";
echo "</tr>\n";
$weight = $total = $sub_total = 0;

foreach ($all_items as $key => $val){

    $item = order::getItem($val['id']);

    if (isset($order_items[$item['id']])){
        $val = $order_items[$item['id']];
    } else {
        $val = 0;
    }
    echo "<tr>\n";
    echo "<td>";

    $options = array ();
    $options['alt'] = $item['item_name_alt'];
    $options['width'] = '75';/*get_module_ini('order_image_size_thumb')*/;

    if (!empty($item['file'])){
        $link =
            create_image_link(
                "/order/item/$item[id]/" . rawurlencode($item['item_name']),
                "/order/download/$item[id]/thumb/$item[md5]", $options);
        echo $link;
    }
    echo "</td>";
    echo "<td>";
    $link = create_link(
        "/order/item/$item[id]/" . rawurlencode ($item['item_name']) ,
        $item['item_name']);
    echo $link;
    echo "<br />\n";
    echo order::getCurrencySymbol() . '&nbsp;' . $item['price'];
    echo "</td><td>\n";
    echo "<form name=\"checkout\" method =\"post\" action=\"\">";
    echo "<input type=\"hidden\" name = \"item_id\" value =\"$item[id]\" />";
    echo "<input type=\"text\" name=\"add_order\" size =\"2\" maxlength=\"2\" value=\"$val\" />";// . "<br />";
    echo "<input class=\"order_cart\" type =\"submit\" name=\"item_update\" value=\"" . lang::translate('order_item_update') . "\" /> ";
    echo "</form>\n";
    echo "</td><td>\n";
    echo order::getCurrencySymbol() . '&nbsp;';
    $sub_total = $val * $item['price'];
    echo $sub_total;
    $total = $sub_total + $total;

    $weight = $weight + ($val * locfloat_to_sysfloat($item['weight']));

    echo "</td>\n";
    echo "<td>&nbsp;</td>";
    echo "<td>&nbsp;</td>\n";
    echo "</tr>\n";

}
echo "<tr>\n";
echo "<td colspan=\"4\">";
echo lang::translate('order_basket_total_price_items');
echo "</td>";
echo "<td>";
echo order::getCurrencySymbol() . '&nbsp;' . $total;
echo "</td>\n";
echo "<td>&nbsp;</td>\n";
echo "</tr>\n";


echo "<tr>\n";
echo "<td colspan=\"4\">";
echo lang::translate('order_amount_value_added_tax');
echo "</td>";
echo "<td>";
echo order::getCurrencySymbol() . '&nbsp;';
echo $total * get_module_ini('order_added_tax');
echo "</td>\n";
echo "<td>&nbsp;</td>\n";
echo "</tr>\n";

echo "<tr>\n";
echo "<td  colspan=\"4\">\n";
echo lang::translate('order_amount_added_shipping_cost') . " ";

$shipping_is_free = false;
$shipping_free = orderShippingFree::getShippingFreePrivate();
if ($total <  $shipping_free) {
    $shipping_free_needed = order::getCurrencySymbol() . '&nbsp;';
    $shipping_free_needed.= $shipping_free - $total;
    echo lang::translate('order_amount_before_shipping_free', array($shipping_free_needed)) . '&nbsp;';
} else {
    $shipping_is_free = true;
    echo lang::translate('order_amount_shipping_is_free') . '&nbsp;';
}

echo "</td>\n";
echo "<td>\n";
echo order::getCurrencySymbol() . '&nbsp;';
if ($shipping_is_free) {
    echo "0";
    $shipping_cost = 0;
} else {
    echo $shipping_cost = orderShipping::getWeightToCost('private', $weight);
}
echo "</td>\n";
echo "<td>&nbsp;</td>\n";
echo "</tr>\n";

echo "<tr>\n";
echo "<td  colspan=\"4\">\n";
echo lang::translate('order_amount_total');
echo "</td>\n";
echo "<td>\n";
echo order::getCurrencySymbol() . '&nbsp;';
echo $shipping_cost + $total;
//echo orderShipping::getWeightToCost('private', $weight) . ' ';
echo "</td>\n";
echo "<td>&nbsp;</td>\n";
echo "</tr>\n";

//echo "<td colspan=\"6\">";
//echo "&nbsp;";
//echo "</td>";

echo "</table>\n";

echo "<table><tr>\n";
echo "<td>";
echo "<form name=\"checkout\" method =\"get\" action=\"/order/checkout\">\n";
echo "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('order_buy') . "\" />";
echo "</form>\n";
echo "</td>\n";
echo "</tr>\n";
echo "</table>\n";
