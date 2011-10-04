<?php



echo "<table class = \"order_cart\">\n";
$i = 0;
echo "<tr>\n";

$per_row = get_module_ini('order_items_per_row');

foreach ($vars as $key => $val){
    echo "<td>";

    $options = array ();
    $options['alt'] = $val['description'];
    $options['title'] = $val['description'];
    $options['width'] = get_module_ini('order_category_image_size');

    headline_message($val['name']);

    if (!empty($val['file'])){
        echo create_image_link(
            "/order/cart?cat=$val[id]",
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
