<?php

print "<table class=\"order_cart\">";
print "<tr><td colspan=2>\n";
print $vars['item_name'] . " ";
print '(' . lang::translate('order_price') . ' ' .
    order::getCurrencySymbol() . ' ' .
    $vars['price'] . ')';
print "</td></tr>\n";
print "<tr><td colspan=2>\n";

if ($vars['stock'] != '0') {

    print "<form name=\"view_item\" method =\"post\">\n";
    print lang::translate('order_item_enter_amount') . " <input id=\"order_amount\" maxlength=\"2\" name=\"add_order\" align=\"left\" size=\"2\" value=\"$vars[add_order]\" />\n";
    print "<input type=\"hidden\" name=\"item_id\" value=\"$vars[id]\" />\n";
    print "<input type =\"submit\" name = \"order_submit\" value=\"" .
        lang::translate('order_update_cart_item') .
        "\" /> ";

    $total = $vars['price'] * $vars['add_order'];
    print
        lang::translate('order_price') . ': ' .
        $total . ' ' .
        order::getCurrencySymbol();
    print "</form>\n";
} else {
    print "<div id=\"form_error\">";
    print lang::translate('order_out_of_stock');
    print "</div>";
}
print "</td></tr>";
print "<tr><td class=\"order-align-top\">\n";

$options = array();
$options['alt'] = $vars['item_name_alt'];
$options['width'] = get_module_ini('order_image_size');

if (!empty($vars['file'])){
  print $link = create_image_link(
    "/order/item/$vars[id]/" . rawurlencode($vars['item_name']),
    "/order/download/$vars[id]/full/$vars[md5]", $options);
}

$use_gallery = get_module_ini('order_use_gallery');
if (isset($use_gallery)) {
    include_model('order/gallery');
    //orderGallery::updateGalleryControl();
    $item_id = URI::getInstance()->fragment(2);
    $gallery_id = orderGallery::getGalleryIdFromItemId($item_id);
    
    $options = array ();
    $options['gallery_id'] = $gallery_id;
    if ($gallery_id) {
        $gallery = new gallery();
        $rows = $gallery->getAllFileInfo($gallery_id);
        $options['no_admin'] = 1;
        $str = $gallery->getThumbTableHTML($rows, $options);
            //html::addHtml ($str);
        echo $str;
    }
}

print "</td><td class=\"order-align-top\">\n";
print $vars['item_description'];

//print $link = create_link('/order/item', $val['item_name']);
if (session::isAdmin()){
    //print "<br />" .
    print $link = create_link(
        "/order/edit/$vars[id]",
        lang::translate('order_edit')
    );
    print MENU_SUB_SEPARATOR;
    print create_link(
        "/order/delete/$vars[id]",
        lang::translate('order_delete')
    );
}
print "</td></tr>\n";
print "</table>\n";
