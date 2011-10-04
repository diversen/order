<?php

$modules = order::getItemModules();

$items = array();
$items[] = html::createLink("/order/products/edit/$vars[id]", lang::translate('order_edit_product_base_info') );

foreach ($modules as $val) {
    $class = moduleLoader::modulePathToClassName($val);
    $str = $class::itemEditMenu($vars['id']);
    $items[] = $str;
}

layout::setModuleMenuExtra($items);
