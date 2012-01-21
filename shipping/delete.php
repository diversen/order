<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

$id = URI::$fragments[3];
$parent = URI::$fragments[4];

if (isset($_POST['submit'])) {
    //orderShipping::sanitize();
    if (!empty(orderShipping::$errors)) {
        view_form_errors(orderShipping::$errors);
    } else {

        $res = orderShipping::delete($id);
        if ($res) {
            session::setActionMessage(
                lang::translate('order_shipping_add_action_message'));
            header("Location: /order/shipping/edit_type_table/$parent");
        } else {
            // should not happen
            $str = 'Could not delete!';
            //view_error($str);
            error_log($str);
        }
    }
}

$row = orderShipping::getOne($id);
orderShipping::showDeleteForm();
