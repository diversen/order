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
        
        $res = $cart->updateItem($id);
        session::setActionMessage(
                lang::translate('order_action_message_product_updated'));
            header("Location: /order/products/index");
    } else {
        view_form_errors($cart->errors);
    }
}
order::form('update');
