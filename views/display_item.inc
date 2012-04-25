<?php

echo "<table class=\"order_cart\">";
echo "<tr><td colspan=2>\n";
echo $vars['item_name'] . "<br />";

echo order::getCurrencyShort($vars['price']);

echo "</td></tr>\n";
echo "<tr><td colspan=2>\n";

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
echo "<tr><td class=\"order-align-top\">\n";

$options = array();

$use_gallery = config::getModuleIni('order_use_gallery');
if (isset($use_gallery)) {
    //$gallery_id = URI::getInstance()->fragment(2); 
    gallery::viewGallery(2);
    /*
    $options = array ();
    $options['gallery_id'] = $gallery_id;
    if ($gallery_id) {
        $gallery = new gallery();
        $rows = $gallery->getAllFileInfo($gallery_id);
        $options['no_admin'] = 1;
        $options['default'] = $gallery->getDefaultImage($gallery_id);
        $str = $gallery->getThumbTableHTML($rows, $options);
        echo $str;
    }*/
}

echo "</td><td class=\"order-align-top\">\n";
echo $vars['item_description'];
echo templateView::get('order', 'admin_options_item', $vars);
echo "</td></tr>\n";
echo "</table>\n";
