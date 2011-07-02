<?php

class orderView {

    // {{{ displayConfirmOrder ()
    public static function detailsEmail (){

        if (!isset($_COOKIE['order_items'])){
            return 0;
        }
        $order_items = order::getBasketItems();
        if (empty($order_items)){
            print lang::translate('order_no_items_in_basket');
            return;
        }

        print lang::translate('order_order_details');
        print "\n\n";

        $total = $sub_total = 0;
        foreach ($order_items as $key => $val){
            if ($val == 0) continue;
            $item = order::getItem($key);
            if (empty($item)) {
                unset($order_items[$key]);
                continue;
            }

            print $item['item_name'] . " ";
            print order::getCurrencySymbol() . ': ' . $item['price'];
            print " * " . $val;

            $sub_total = $val * $item['price'];
            print " = " . order::getCurrencySymbol() . " " . $sub_total . "\n";
            $total = $sub_total + $total;
        }

        print lang::translate('order_amount_total');
        print ' = ';
        print order::getCurrencySymbol() . " " . $total . "\n";

        print lang::translate('order_amount_value_added_tax');
        print ' = ';
        print order::getCurrencySymbol() . ' ';
        print $total * get_module_ini('order_added_tax') . "\n";
        print lang::translate('order_amount_added_shipping_cost') . "\n\n";
    }
    // }}}




}