<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

echo "<h3>" . lang::translate('order_sales_transaction_info') . "</h3>";
orderSales::displayTransaction();