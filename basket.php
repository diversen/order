<?php

/*
if (isset($_GET['start_prg'])){
    simple_prg(true);
} else {
    simple_prg();

}*/


template::setTitle(lang::translate('order_view_basket_html_title'));
$cart = new order();
$cart->addToBasket();
$cart->displayBasket();
