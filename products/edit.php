<?php

/**
 * view file for editing event
 *
 * @package    event
 */
if (!session::checkAccessControl('order_allow')){
    return;
}

$product = new orderProducts();
$product->updateItemControl();
