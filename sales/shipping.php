<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

orderSales::displayShipping();
