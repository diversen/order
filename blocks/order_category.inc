<?php

include_module('order/category');

function block_order_category() {
    orderCategory::displayBlockMenu();
}