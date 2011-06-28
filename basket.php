<?php

/*
if (isset($_GET['start_prg'])){
    simple_prg(true);
} else {
    simple_prg();

}*/


template::setTitle(lang::translate('View Basket'));
$cart = new order();
$cart->addToBasket();
orderView::basket();
