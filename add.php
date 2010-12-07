<?php


/**
 * view file for adnministration of events
 *
 * @package    event
 */
if (!session::checkAccessControl('allow_edit_cart')){
    return;
}

template::setTitle(lang::translate('Add Product'));
$cart = new cart ();
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
