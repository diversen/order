<?php

if (!session::checkAccessControl('order_allow')){
    return;
}


orderShipping::index();
//echo lang::translate('order_shipping_help');
