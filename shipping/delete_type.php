<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

$id = URI::$fragments[3];

if (isset($_POST['submit'])) {
    orderShipping::deleteType($id);
    session::setActionMessage(lang::translate('order_shipping_type_action_deleted'));
    http::locationHeader('/order/shipping/index');
}

orderShipping::showDeleteTypeForm();
