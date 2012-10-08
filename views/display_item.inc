<?php

/**
 * displays single item
 */
echo "<table class=\"order_cart_item\">";
echo "<tr><td colspan=2>\n";
echo headline_message($vars['item_name']); // . "<br />";

echo order::getCurrencyShort($vars['price']);

echo "</td></tr>\n";
echo "<tr><td colspan=2 class=\"order_align_top\">\n";

if ($vars['stock'] != '0') {

    if (config::getModuleIni('order_use_select')) {
        if (!isset($vars['selected'])) {
            $vars['selected'] = array();
        }
    }
    
    echo "<form name=\"view_item\" method =\"post\">\n";
    echo "<table>\n";    
    echo "<input type=\"hidden\" name=\"item_id\" value=\"$vars[id]\" />\n";

    echo "<tr>";
    echo "<td>\n";
    
    echo lang::translate('order_item_enter_amount');
    echo "</td>";
    echo "<td>";
    echo "<input id=\"order_amount\" maxlength=\"2\" name=\"num_items\" align=\"left\" size=\"2\" value=\"$vars[num_items]\" />\n";    
    echo "</td>\n";
    echo "<td>";
    echo "<input type =\"submit\" name = \"order_submit\" value=\"" .
        lang::translate('order_update_cart_item') .
        "\" /> ";
    echo "</td>";
    echo "</tr>\n";
    echo "</table>";
    echo "</form>\n";
} else {
    echo "<div id=\"form_error\">";
    echo lang::translate('order_out_of_stock');
    echo "</div>";
}
echo "</td></tr>";
echo "<tr><td class=\"order_align_top\">\n";

$options = array();

$use_gallery = config::getModuleIni('order_use_gallery');
if (isset($use_gallery) ) {
    gallery::viewGallery(2, 3, array (
        'no_redirect' => true,
        'no_admin' => true));
}

echo "</td><td class=\"order_align_top\">\n";
echo $vars['item_description'];
echo templateView::get('order', 'admin_options_item', $vars);
echo "</td></tr>\n";
echo "</table>\n";
