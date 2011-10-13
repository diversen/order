<?php


html::formStart('hello_world');
html::legend(lang::translate('order_item_select_legend'));

$str = "<table>\n";
foreach ($vars->titles as $key => $val) {
    $str.= "<tr>\n";
    $str.= "<td>\n";
    //html::hidden('method', 'item_insert_select');
    
    $str.= "$val: ";
    $str.= "</td>\n";
    $str.= "<td>\n";
    $str.= html::selectClean($val, $vars->options[$key], 'title', 'value', $vars->selected[$key]);
    $str.= "</td>\n";
    //$str.= "<td>\n";
    //$str.= html::createLink("/order/select/reference_add/", 'grr');
    //$str.= "</td>\n";
    
    
    $str.= "<tr>\n";
    $str.= "<td colspan=\"3\">\n";
    $str.= html::createLink("?method=item_delete_select&id=" . $vars->ids[$key], 'Slet');
    $str.= MENU_SUB_SEPARATOR;
    
    $str.= html::createLink("/order/select/edit/". $vars->item_id . "/" . $vars->ids[$key], 'Ret');
    //$str.= MENU_SUB_SEPARATOR;
    //$str.= html::createLink("/order/select/add_reference/". $vars->item_id . "/" . $vars->ids[$key], lang::translate('Opret '));
    
    $str.="</td>\n";
    $str.="</tr>\n";
}
$str.="</table>\n";
html::addHtml($str);

html::formEnd();
echo html::getStr();



