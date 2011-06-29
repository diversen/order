<?php

/**
 * view file for editing event
 *
 * @package    event
 */
if (!session::checkAccessControl('order_allow')){
    return;
}

$id = URI::getInstance()->fragment(2);

template::setTitle(lang::translate('order_edit_html_title'));
$cart = new order();
if (isset($_POST['submit'])){
    $cart->validate();
    $cart->sanitize();
    if (empty($cart->errors)){
        $cart->updateItem($id);
    } else {
        view_form_errors($cart->errors);
    }
}
create_item_form('update', $id);
