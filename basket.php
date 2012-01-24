<?php

template::setTitle(lang::translate('order_view_basket_html_title'));
//$cart = new order();
order::addToBasket();
//$cart->addToBasket();

order::displayBasket();
        //;$cart->displayBasket();
