<?php

/**
 * controller file for doing downloads
 *
 * @package     module_system
 */

// send cache headers



include_module('order/category');



$uri = URI::getInstance();
$id = $uri->fragment(2);
$type = $uri->fragment(3);

//http://mandlen/order/download/9
//http://mandlen/order/download/9/full

$item = array();
if (!$type || $type == 'full') {
    include_module('order');
    $item = order::getItem($id);
} else if ( $type == 'category') {
    include_module('order/category');
    $item = orderCategory::getCategory($id);
}

if (empty($item['file'])) return;

send_cache_headers();
header("Content-Type: $item[content_type]");

if ($type == 'full' || $type == 'category'){
    echo $item['file'];
} else {
    echo $item['file_thumb'];
}
die;