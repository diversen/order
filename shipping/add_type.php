<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

orderShipping::addTypeControl();