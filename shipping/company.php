<?php

if (isset($_POST['submit'])) {
    orderShipping::sanitize();
    if (!empty(orderShipping::$errors)) {
        view_form_errors(orderShipping::$errors);
    } else {
        $res = orderShipping::add('company');
        if ($res) {
            session::setActionMessage(
                lang::translate('order_shipping_add_action_message'));
            header("Location: /order/shipping/company");
        } else {
            session::setActionMessage(
                lang::translate('order_shipping_add_action_error_message'));
            header("Location: /order/shipping/company");
        }
    }
}


orderShipping::showForm();
orderShipping::displayAll('company');