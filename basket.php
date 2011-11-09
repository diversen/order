<?php

template::setTitle(lang::translate('order_view_basket_html_title'));
$cart = new order();
$cart->addToBasket();
$cart->displayBasket();
