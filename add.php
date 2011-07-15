<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

template::setTitle(lang::translate('order_add_product_html_title'));
$cart = new order ();
if (isset($_POST['submit'])){
    $cart->validate();
    $cart->sanitize();
    if (empty($cart->errors)){
        $res = $cart->addItem();
        if ($res) {
            session::setActionMessage(lang::translate('order_confirm_product_inserted'));
            header("Location: /order/products/index");
        } else {
            view_form_errors(order::$errors);
            $message = "Could not add product item in: " . __FILE__;
            cos_error_log($message);
        }
    } else {
        view_form_errors($cart->errors);
    }    
}

order::form('insert');
