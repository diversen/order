<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

if (isset($_POST['submit'])) {
    orderCategory::validate();
    if (empty(orderCategory::$errors)) {
        $res = orderCategory::update();
        if ($res) {
            $message = lang::translate('order_category_confirm_category_updated');
            session::setActionMessage($message);
            header("Location: /order/category/index");
        } else {
            view_form_errors(orderCategory::$errors);
            $message = "Could not update category in: " . __FILE__;
            cos_error_log($message);
        }
    }
}

orderCategory::showForm('update');
