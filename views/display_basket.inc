<?php

$order_items = $vars['order_items'];

$total_weight = 0;

echo "<table class=\"order_basket_full\">\n";
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
echo "</tr>\n";

$full = order::getFullCartInfo();

foreach ($order_items as $key => $val){

    $item = $full['items'][$val['item_id']];

    echo "<tr>\n";
    echo "<td>";

    $options = array ();
    $options['alt'] = $item['item_name_alt'];
    $options['width'] = config::getModuleIni('gallery_small_size');

    $image_url = gallery::getDefaultImageUrl($item['id'], 'small');
    
    if (!empty($image_url)){
        $link =
            html::createHrefImage(
                strings::utf8Slug("/order/item/$item[id]", $item['item_name']),
                $image_url, $options);
        echo $link;
    } else {
        echo "&nbsp;";
    }
    echo "</td>";
    echo "<td>";
    echo $link = html::createLink(
            strings::utf8Slug("/order/item/$item[id]", $item['item_name']), 
            html::specialEncode($item['item_name']));

    echo "<br />\n";
    echo order::getCurrencyShort($item['price']);
    echo "</td><td>\n";
    
    if (!isset($vars['disable_item_edit_buttons'])) {
        echo "<form name=\"checkout\" method =\"post\" action=\"\">";
        echo "<input type=\"hidden\" name = \"item_id\" value =\"$item[id]\" />";
        echo "<input type=\"hidden\" name = \"order_item\" value =\"$key\" />";
        echo "<input type=\"text\" name=\"num_items\" size =\"2\" maxlength=\"2\" value=\"$val[num_items]\" />";
        echo "<input class=\"order_cart\" type =\"submit\" name=\"item_update\" value=\"" . lang::translate('order_item_update') . "\" /> ";
        echo "</form>\n";
    } else {
        echo $val['num_items'];
    }
    echo "</td><td>\n";
    echo order::getCurrencyShort($item['sub_total']);
    echo "</td>\n";
    echo "<td>&nbsp;</td>";
    echo "</tr>\n";

}
echo "<tr>\n";
echo "<td colspan=\"4\">";
echo lang::translate('order_basket_total_price_items');
echo "</td>";
echo "<td>";

echo order::getCurrencyShort($full['total']);
echo "</td>\n";
echo "</tr>\n";

echo "<tr>\n";
echo "<td colspan=\"4\">";
echo lang::translate('order_amount_value_added_tax');
echo "</td>";
echo "<td>";
echo order::getCurrencyShort($full['tax']);
echo "</td>\n";
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
echo "</table>";
