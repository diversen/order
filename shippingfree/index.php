<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

orderShippingFree::index();