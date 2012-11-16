<?php

echo "<table class = \"order_cart_category\">\n";
$i = 0;
echo "<tr>\n";

$per_row = config::getModuleIni('order_items_per_row');


foreach ($vars as $val){

    echo "<td class=\"order_align_top\">\n";
    $options = array ();
    $options['alt'] = $val['item_name_alt'];
    $options['width'] = config::getModuleIni('gallery_small_size');
    
    $image_url = gallery::getDefaultImageUrl($val['id'], 'small');
    
    if (!empty($image_url)){
        
        $link =
            html::createHrefImage(
                strings::utf8Slug("/order/item/$val[id]", $val['item_name']),
                $image_url, $options);
        echo $link;
    } else {
        echo "&nbsp;";
    }
    
    if (!empty($val['file'])){
        echo html::createHrefImage(
            "/order/item/$val[id]/" . rawurlencode($val['item_name']),
            "/order/download/$val[id]/thumb/$val[md5]", $options
        );
    }
    
    echo "</td>\n";
    echo "<td class=\"order_align_top\">\n";
    
    $link = html::createLink(
        strings::utf8Slug("/order/item/$val[id]", $val['item_name']),
        $val['item_name']);
    echo $link;
    /*
    echo html::createLink(
            "/order/item/$val[id]/" . rawurlencode($val['item_name']),
            $val['item_name']);*/
    echo "<br />";
    if ($val['stock'] == 0){
        echo "<div id=\"form_error\">";
        echo lang::translate('order_out_of_stock');
        echo "</div>";
    }

    echo order::getCurrencyShort($val['price']) . 
          "<br />\n";

    echo view::get('order', 'admin_options_item', $val);
    echo "</td>\n";
    $i++;
    $t = $i % $per_row;
    if (!$t){
        echo "</tr><tr>\n";
        $i = 0;
    }

}
echo "</tr>\n";
echo "</table>\n";
