<?php

/**
 * controller file for doing downloads
 *
 * @package     module_system
 */

// send cache headers


include_module('order');
$cart = new cart();

$uri = URI::getInstance();
$id = $uri->fragment(2);
$type = $uri->fragment(3);

$item = $cart->getItem($id);

if (empty($item['file'])) return;

send_cache_headers();
header("Content-Type: $item[content_type]");

if ($type == 'full'){
    echo $item['file'];
} else {
    echo $item['file_thumb'];
}
die;