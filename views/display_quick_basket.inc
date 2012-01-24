<?php


$order_items = order::getBasketItems();
$ary = array ();
foreach ($order_items as $key => $val) {
    if (isset($val['num_items']) && isset($val['item_id'])) {
        $ary[$val['item_id']] = $val['num_items']; 
    }
}

$order_items = $ary;
$all_items = $vars['all_items'];

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
$full = order::getFullCartInfo();

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

    $image_url = gallery::getDefaultImageUrl($item['id'], 'small');
    $link =
        html::createHrefImage(
            strings::utf8Slug("/order/item/$item[id]", $item['item_name']),
            $image_url, $options);
    echo $link;
    echo "</td>";
    echo "<td>";

    $link = html::createLink(
        strings::utf8Slug("/order/item/$item[id]", $item['item_name']),
        $item['item_name']);
    
    echo $link;
    echo "<br />\n";
    echo order::getCurrencyShort($item['price']);
    echo "</td><td>\n";
    echo "<form name=\"checkout\" method =\"post\" action=\"\">";
    echo "<input type=\"hidden\" name = \"item_id\" value =\"$item[id]\" />";
    echo "<input type=\"text\" name=\"num_items\" size =\"2\" maxlength=\"2\" value=\"$val\" />";// . "<br />";
    echo "<input class=\"order_cart\" type =\"submit\" name=\"item_update\" value=\"" . lang::translate('order_item_update') . "\" /> ";
    echo "</form>\n";
    echo "</td><td>\n";
    //echo order::getCurrencySymbol() . '&nbsp;';

    $sub_total = $val * locfloat_to_sysfloat($item['price']);
    echo order::getCurrencyShort($sub_total);
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
echo order::getCurrencySymbol() . '&nbsp;' . format_float_mon($total);
echo "</td>\n";
echo "<td>&nbsp;</td>\n";
echo "</tr>\n";

echo "<tr>\n";
echo "<td colspan=\"4\">";
echo lang::translate('order_amount_value_added_tax');
echo "</td>";
echo "<td>";
echo order::getCurrencySymbol() . '&nbsp;';
echo format_float_mon($total * config::getModuleIni('order_added_tax'));
echo "</td>\n";
echo "<td>&nbsp;</td>\n";
echo "</tr>\n";
// calculate shipping row
$order_items = order::getBasketItems();    
$shipping_free_info = orderShippingfree::getShippingFreeInfo(
    $order_items, 
    $full['total']);
    
$shipping_info = orderShipping::getShippingInfo(
    $order_items, 
    $full['total'], 
    $full['weight']);

echo "<tr>\n";
echo "<td colspan=\"5\">";
echo $shipping_free_info['shipping_free_str'];
    
// no cost type selected
// no cost type selected
if (!isset($shipping_info['shipping_cost'])) {
    if (!$shipping_free_info['shipping_is_free']) {
        echo lang::translate('order_amount_added_shipping_cost_final');
    }
}
    
echo "</td>";
echo "</tr>\n";


if (!$shipping_free_info['shipping_is_free']) {
    // no shipping free
    // shipping type has been set
    if (isset($shipping_info['shipping_cost'])) {
        echo "<tr>\n";
        echo "<td colspan=\"4\">";
        echo $shipping_info['type']['name'];
        echo "</td>";
        echo "<td>";
        echo order::getCurrencyShort($shipping_info['shipping_cost']);
        echo "</td>\n";       
        echo "</tr>\n";
        $full['total']+= $shipping_info['shipping_cost'];
    }       
}

echo "<tr>\n";
echo "<td  colspan=\"4\">\n";
echo lang::translate('order_amount_total');
echo "</td>\n";
echo "<td>\n";
echo order::getCurrencyShort($full['total']);
echo "</td>\n";
echo "</tr>\n";
echo "</table>\n";
