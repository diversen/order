<?php



print "<table class = \"order_cart\">\n";
$i = 0;
print "<tr>\n";


foreach ($vars as $key => $val){
    print "<td>";

    $options = array ();
    $options['alt'] = $val['description'];
    $options['title'] = $val['description'];
    $options['width'] = get_module_ini('order_image_size_category');

    print "<h3>$val[name]</h3>";

    if (!empty($val['file'])){
        print create_image_link(
            "/order/cart?cat=$val[id]",
            "/order/download/$val[id]/category", $options
        );
    }
    print "</td>\n";

    $i++;
    $t = $i % 2;
    if (!$t){
        print "</tr><tr>\n";
        $i = 0;
    }

}

if ($i % 2){
    print "<td>&nbsp;</td>";
    print "</tr>\n";
} else {
    print "<td>&nbsp;</td>";
    print "<td>&nbsp;</td>";
    print "</tr>\n";
}
print "</table>\n";
