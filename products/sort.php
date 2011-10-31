<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

$sort = new orderProducts();
$sort->displaySortItems();