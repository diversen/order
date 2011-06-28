<?php

template::setTitle(lang::translate('View Basket'));
$cart = new order();
if (@isset($_POST['item_update'])){
    $cart->addToBasket(array ('redirect' => '/order/quick_order'));
}
orderView::quickbasket();
