<?php

foreach ($vars as $key => $val) {
    // id
    echo lang::translate('order_sale_order_id') . ' ' .
         MENU_SUB_SEPARATOR_SEC . 
         $val['id'] . "<br />\n";
    
    // status
    echo lang::translate('order_sale_order_status') . ' ' . 
         MENU_SUB_SEPARATOR_SEC .    
         $val['status'] . "<br />";
    
    // name
    echo $val['full_name'] . "<br />";
    
    // shipping
    echo html::createLink("/order/sales/shipping/$val[id]", 
            lang::translate('order_sales_shipping_info'));
    echo MENU_SUB_SEPARATOR;
    
    // order details
    echo html::createLink("/order/sales/details/$val[id]", 
            lang::translate('order_sales_details_info'));
    echo MENU_SUB_SEPARATOR;
    
    // transaction details.
    echo html::createLink("/order/sales/transaction/$val[id]", 
            lang::translate('order_sales_transaction_info'));
    
    echo "<hr />\n";
    
}