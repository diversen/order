<?php
/*
echo "<table>\n";

foreach ($vars as $key => $val) {
    echo "<tr>\n";
    
    echo "<td>\n";
    echo $val['name'];
    echo "</td>\n";

    $url = "/order/category/edit/$val[id]";
    $title = lang::translate('order_edit');

    echo "<td>\n";
    echo html::createLink($url, $title);
    echo "</td>\n";
    //echo MENU_SUB_SEPARATOR;

    $url = "/order/category/delete/$val[id]";
    $title = lang::translate('order_delete');

    echo "<td>\n";
    echo html::createLink($url, $title);
    echo "</td>\n";
    
    //echo "<br />\n";
    echo "</tr>\n";
}

echo "</table>\n";

<?php

echo "<table>\n";

foreach ($vars as $key => $val) {
    echo "<tr>\n";

    echo "<td>\n";
    echo $val['name'];
    echo "</td>\n";

    $url = "/order/category/edit/$val[id]";
    $title = lang::translate('order_edit');

    echo "<td>\n";
    echo html::createLink($url, $title);
    echo "</td>\n";
    //echo MENU_SUB_SEPARATOR;

    $url = "/order/category/delete/$val[id]";
    $title = lang::translate('order_delete');

    echo "<td>\n";
    echo html::createLink($url, $title);
    echo "</td>\n";

    //echo "<br />\n";
    echo "</tr>\n";
}

echo "</table>\n";
*/




print "<table class = \"order_cart\">\n";

foreach ($vars as $key => $val){
    print "<tr>\n";
    print "<td>";

    $options = array ();
    $options['alt'] = $val['name'];
    $options['width'] = get_module_ini('order_image_size_category');

    if (!empty($val['file'])){
        print create_image_link(
            "/order/category/$val[id]/" . rawurlencode($val['name']),
            "/order/download/$val[id]/category", $options
        );
    }
    print "</td>\n";
    print "<td>\n";
    print $val['description'];
    print "</td>\n";

}
print "</tr>\n";
print "<table>\n";
