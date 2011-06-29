<?php

template::setTitle(lang::translate('order_quick_order_title'));
$cart = new order();
if (@isset($_POST['item_update'])){
    $cart->addToBasket(array ('redirect' => '/order/quick_order'));
}
orderView::quickbasket();
