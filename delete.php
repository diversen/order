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
$id = URI::getInstance()->fragment(2);

$cart = new order();
if (isset($_POST['submit'])){
    $res = $cart->deleteItem($id);
    
}
order::form('delete');
