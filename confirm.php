<?php

template::setTitle(lang::translate('order_checkout_html_title'));

$cart = new order();
order::displayConfirm();



