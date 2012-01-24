<?php

template::setTitle(lang::translate('order_quick_order_title'));
order::addToBasket(array ('redirect' => '/order/quick_order'));
order::displayQuickBasket();
