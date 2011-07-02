<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

//$id = URI::$fragments[3];
$type = URI::$fragments[2];

if (isset($_POST['submit'])) {
    orderShipping::sanitize();
    if (!empty(orderShipping::$errors)) {
        view_form_errors(orderShipping::$errors);
    } else {
        $res = orderShipping::add('private');
        if ($res) {
            session::setActionMessage(
                lang::translate('order_shipping_add_action_message'));
            header("Location: /order/shipping/$type");
        } else {
            $str = "Could not edit in " . __FILE__;
            error_log($str);
        }
    }
}


orderShipping::showForm();
orderShipping::displayAll('private');