<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

if (isset($_POST['submit'])) {
    orderCategory::validate();
    if (empty(orderCategory::$errors)) {
        $res = orderCategory::delete();
        if ($res) {
            $message = lang::translate('order_category_confirm_category_deleted');
            session::setActionMessage($message);
            header("Location: /order/category/index");
        } else {
            $message = "Could not delete category in: " . __FILE__;
            cos_error_log($message);
        }
    }
}

orderCategory::showForm('delete');
