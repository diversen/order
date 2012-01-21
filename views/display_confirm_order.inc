<?php

$order_items = $vars['order_items'];

echo "<h3>" . lang::translate("order_details") . "</h3>\n";


$vars['disable_item_edit_buttons'] = true;
templateView::includeModuleView('order', 'display_basket', $vars);

/*
echo "<table class=\"order_cart\">\n";
echo "<tr>";
echo "<td colspan=\"5\">\n";
echo "<h3>" . lang::translate("order_details") . "</h3>\n";
echo "</td>\n";
echo "</tr>\n";

echo "<tr>";
echo "<td colspan=\"2\">";
echo "</td><td>\n";
echo lang::translate('order_quantity');
echo "</td><td>\n";
echo lang::translate('order_sub_total');
echo "</td><td>\n";
echo lang::translate('order_amount_total');
echo "</td>";
echo "</tr>\n";

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

    echo "<tr>\n";
    echo "<td>";
    if (!empty($item['file'])){
        echo $link = create_image_link(
                "/order/item/$item[id]/"  . 
                rawurlencode($item['item_name']), 
                "/order/download/$item[id]/thumb/$item[md5]", 
                $options
            );
    }


    echo "</td>";
    echo "<td>";
    echo $link = html::createLink("/order/item/$item[id]/" . rawurlencode ($item['item_name']) , $item['item_name']) . "<br />\n";
    echo order::getCurrencySymbol() . '&nbsp;' . $item['price']; // . "<br />";
    echo "</td><td>\n";
    echo $val;
    echo "</td><td>\n";
    echo order::getCurrencySymbol() . '&nbsp;';
    $sub_total = $val['num_items'] * $item['price'];
    echo $sub_total;
    $total = $sub_total + $total;
    $weight = $weight + ($val['num_items'] * locfloat_to_sysfloat($item['weight']));

    echo "</td>\n";
    echo "<td>&nbsp;</td>";
    echo "</tr>\n";
}
echo "<tr>\n";
echo "<td colspan=\"3\">";
echo lang::translate('order_basket_total_price_items');
echo "</td>";
echo "<td>&nbsp;</td>\n";
echo "<td>";

echo order::getCurrencySymbol() . '&nbsp;';
echo $total;
echo "</td>\n";
echo "</tr>\n";

echo "<tr>\n";
echo "<td colspan=\"4\">\n";
echo lang::translate('order_amount_value_added_tax');
echo "</td>";
echo "<td>";
echo order::getCurrencySymbol() . '&nbsp;';
echo $total * get_module_ini('order_added_tax');
echo "</td>\n";
echo "</tr>\n";

echo "<tr>\n";
echo "<td  colspan=\"4\">\n";
echo lang::translate('order_amount_added_shipping_cost') . " ";

$shipping_is_free = false;
$shipping_free = orderShippingFree::getShippingFreePrivate();
if ($total <  $shipping_free) {
    $shipping_free_needed = order::getCurrencySymbol() . '&nbsp;';
    $shipping_free_needed.= $shipping_free - $total;
    echo lang::translate('order_amount_before_shipping_free', array($shipping_free_needed)) . ' ';
} else {
    $shipping_is_free = true;
    echo lang::translate('order_amount_shipping_is_free') . ' ';
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

echo "</tr>\n";

echo "<table>\n";
 * 
 */
