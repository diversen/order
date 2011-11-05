<?php

/**
 * view file for deleting events
 *
 * @package    event
 */
if (!session::checkAccessControl('order_allow')){
    return;
}
template::setTitle(lang::translate('order_delete_html_title'));
$id = URI::getInstance()->fragment(3);

$cart = new orderProducts();
if (isset($_POST['submit'])){
    $res = $cart->deleteItem($id);
    
}
$cart->form('delete');
