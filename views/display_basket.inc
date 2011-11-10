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
//echo "<td>&nbsp;</td>";
echo "</tr>\n";
$total = $sub_total = $weight = 0;
foreach ($order_items as $key => $val){

    if ($val['add_order'] == 0) continue;
    $item = order::getItem($val['item_id']);
    if (empty($item)) {
        unset($order_items[$key]);
        continue;
    }
    echo "<tr>\n";
    echo "<td>";

    $options = array ();
    $options['alt'] = $item['item_name_alt'];
    $options['width'] = get_module_ini('gallery_small_size');

    $image_url = gallery::getDefaultImageUrl($item['id'], 'small');
    
    if (!empty($image_url)){
        $link =
            create_image_link(
                "/order/item/$item[id]/"  .
                rawurlencode($item['item_name']),
                $image_url, $options);
        echo $link;
        // USED this to be able to edit exact item rawurlencode($item['item_name']) . "?order_item=$key",

    } else {
        echo "&nbsp;";
    }
    echo "</td>";
    echo "<td>";
    echo $link = create_link("/order/item/$item[id]/" . 
            rawurlencode ($item['item_name']) , $item['item_name']) . "<br />\n";
    echo order::getCurrencySymbol();
    echo ' ' . format_float_mon($item['price']);

    echo orderSelect::getSelectListAsHumanFields($item['id'], $val);

    //echo orderSelect::getSelectChildListAsHumanFields($item['id'], $val);
    echo "</td><td>\n";
    
    if (!isset($vars['disable_item_edit_buttons'])) {
        echo "<form name=\"checkout\" method =\"post\" action=\"\">";
        echo "<input type=\"hidden\" name = \"item_id\" value =\"$item[id]\" />";
        echo "<input type=\"hidden\" name = \"order_item\" value =\"$key\" />";
        echo "<input type=\"text\" name=\"add_order\" size =\"2\" maxlength=\"2\" value=\"$val[add_order]\" />";
    
        echo orderSelect::getSelectListAsHiddenFields($item['id'], $val);
   
        echo "<input class=\"order_cart\" type =\"submit\" name=\"item_update\" value=\"" . lang::translate('order_item_update') . "\" /> ";
    
        echo "</form>\n";
    } else {
        echo $val['add_order'];
    }
    echo "</td><td>\n";
    echo order::getCurrencySymbol() . '&nbsp;';
    $sub_total = $val['add_order'] * $item['price'];
    //$sub_total_weight = $val * $item['weight'];

    echo format_float_mon($sub_total);
    $total = $sub_total + $total;
    $weight = $weight + ($val['add_order'] * $item['weight']);
    echo "</td>\n";
    echo "<td>&nbsp;</td>";
    echo "</tr>\n";

}
echo "<tr>\n";
echo "<td colspan=\"4\">";
echo lang::translate('order_basket_total_price_items');
echo "</td>";
echo "<td>";
echo order::getCurrencySymbol() . '&nbsp;' . format_float_mon($total);
echo "</td>\n";
echo "</tr>\n";


echo "<tr>\n";
echo "<td colspan=\"4\">";
echo lang::translate('order_amount_value_added_tax');
echo "</td>";
echo "<td>";
echo order::getCurrencySymbol() . '&nbsp;';
$tax = $total * get_module_ini('order_added_tax');
echo format_float_mon($tax);
echo "</td>\n";
echo "</tr>\n";

echo "<tr>\n";
echo "<td  colspan=\"4\">\n";
echo lang::translate('order_amount_added_shipping_cost') . " ";

$shipping_info = orderShipping::getShippingInfo($order_items, $total, $weight);

echo "</td>\n";
echo "<td>\n";

echo order::getCurrencySymbol() . "&nbsp;";

echo $shipping_info['shipping_cost']; 

echo "</td>\n";
echo "</tr>\n";

// shipping free string
echo "<tr>\n";
echo "<td  colspan=\"5\">\n";
echo $shipping_info['shipping_free_str'];
echo "</td>\n";
echo "</tr>\n";

echo "<tr>\n";
echo "<td  colspan=\"4\">\n";
echo lang::translate('order_amount_total');
echo "</td>\n";
echo "<td>\n";
echo order::getCurrencySymbol() . "&nbsp;";
$total = $shipping_info['shipping_cost'] + $total;
echo format_float_mon($total);
echo "</td>\n";
echo "</tr>\n";

echo "<td colspan=\"4\">\n";
echo "&nbsp;";
echo "</td>";
echo "</tr>";
echo "</table>";
