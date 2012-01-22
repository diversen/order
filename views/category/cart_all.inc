<?php

echo "<table class = \"order_cart\">\n";
$i = 0;
echo "<tr>\n";

$per_row = config::getModuleIni('order_items_per_row');

foreach ($vars as $key => $val){
    echo "<td class='order-align-top'>";

    $options = array ();
    $options['alt'] = $val['description'];
    $options['title'] = $val['description'];
    $options['width'] = config::getModuleIni('order_category_image_size');

    headline_message($val['name']);
    
    $image = gallery::getDefaultImage($val['id']);
    $url = strings::utf8Slug("/order/cart/$val[id]", $val['name']);
    
    if (!empty($val['file'])){
        echo create_image_link(
            $url,
            "/order/download/$val[id]/category/$val[md5]", $options
        );
    }
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
