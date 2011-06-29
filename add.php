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
        // redirect to event list
    } else {
        view_form_errors($cart->errors);
        //create_item_form('insert');
    }
//} else {
    
}

create_item_form('insert', null, array());
