<?php



print "<table class = \"order_cart\">\n";
$i = 0;
print "<tr>\n";

$per_row = get_module_ini('order_items_per_row');

foreach ($vars as $key => $val){
    print "<td>";

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
    print "</td>\n";

    $i++;
    $t = $i % $per_row;
    if (!$t){
        print "</tr><tr>\n";
        $i = 0;
    }

}

/*
if ($i % 2){
    print "<td>&nbsp;</td>";
    print "</tr>\n";
} else {
    print "<td>&nbsp;</td>";
    print "<td>&nbsp;</td>";
    print "</tr>\n";
}*/
print "</tr>\n";
print "</table>\n";
