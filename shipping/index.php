<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

echo lang::translate('order_shipping_help');
