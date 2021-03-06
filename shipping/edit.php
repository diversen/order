<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

$id = URI::$fragments[3];
$parent = URI::$fragments[4];

if (isset($_POST['submit'])) {
    orderShipping::sanitize();
    if (!empty(orderShipping::$errors)) {
        view_form_errors(orderShipping::$errors);
    } else {
        
        $res = orderShipping::update($id);
        if ($res) {
            session::setActionMessage(
                lang::translate('order_shipping_add_action_message'));
            header("Location: /order/shipping/edit_type_table/$parent");
        } else {
            $str = "Could not edit in " . __FILE__;
            error_log($str);
        }
    }
}

$row = orderShipping::getOne($id);

orderShipping::showForm('update', $row);

