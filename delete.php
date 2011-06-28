<?php

/**
 * view file for deleting events
 *
 * @package    event
 */
if (!session::checkAccessControl('allow_edit_cart')){
    return;
}
template::setTitle(lang::translate('Delete Product'));
$id = URI::getInstance()->fragment(2);

$cart = new order();
if (isset($_POST['submit'])){
    $res = $cart->deleteItem($id);
    
}
create_item_form('delete', $id);
