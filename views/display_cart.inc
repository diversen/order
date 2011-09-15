<?php

print "<table class = \"order_cart\">\n";
$i = 0;
print "<tr>\n";

echo $num_items = count($vars);
$per_row = 2;

//echo $num_items / $per_row;

echo $rest = $num_items % $per_row;

foreach ($vars as $key => $val){
    print "<td>";

    $options = array ();
    $options['alt'] = $val['item_name_alt'];
    $options['width'] = get_module_ini('order_image_size_thumb');

    if (!empty($val['file'])){
        print create_image_link(
            "/order/item/$val[id]/" . rawurlencode($val['item_name']),
            "/order/download/$val[id]", $options
        );
    }
    print "</td>\n";
    print "<td>\n";
    //print "<br />\n";
    print create_link(
            "/order/item/$val[id]/" . rawurlencode($val['item_name']),
            $val['item_name']);
    print "<br />";
    if ($val['stock'] == 0){
        print "<div id=\"form_error\">";
        print lang::translate('order_out_of_stock');
        print "</div>";
    }

    print "<br />";
    print order::getCurrencySymbol() . ' ' .
          $val['price'] . ',-' .
          "<br />\n";

    if (session::isAdmin()){
        $link = create_link(
            "/order/edit/$val[id]",
            lang::translate('order_edit')
        );
        print $link;
        print MENU_SUB_SEPARATOR;
        $link = create_link(
            "/order/delete/$val[id]",
            lang::translate('order_delete')
        );

        print $link;
        
    }
    
    print "</td>\n";
    $i++;
    $t = $i % 2;
    if (!$t){
        print "</tr><tr>\n";
        $i = 0;
    }

}
print "</tr>\n";
print "</table>\n";
