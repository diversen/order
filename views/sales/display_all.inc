<?php

foreach ($vars as $key => $val) {
    echo $val['id'] . "<br />\n";
    echo $val['full_name'] . "<br />";
    echo html::createLink("/order/sales/shipping/$val[id]", 
            lang::translate('order_sales_shipping_info'));
    echo MENU_SUB_SEPARATOR;
    
    echo html::createLink("/order/sales/details/$val[id]", 
            lang::translate('order_sales_details_info'));
    
    echo MENU_SUB_SEPARATOR;
    
    echo html::createLink("/order/sales/transaction/$val[id]", 
            lang::translate('order_sales_transaction_info'));
    
}