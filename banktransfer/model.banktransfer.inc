<?php

class order_banktransfer {
    
    static function displayMethodLink () {
        $text = lang::translate('order_payment_method_bank_transfer'); //"Bankoverførsel (forudbetaling)";
        $options = array ('title' => lang::translate('order_payment_bank_transfer_info'));
        return html::createLink('/order/banktransfer/index', $text, $options);
    } 
    
    public static function displayConfirm (){
        $order_items = order::getBasketItems();
        if (empty($order_items)){
            echo lang::translate('order_no_items_in_basket');
            return;
        }


        load_post('order_form');        
        $vars['order_items'] = $order_items;
        if (empty($vars['order_items'])){
            echo lang::translate('order_no_items_in_basket');
            return;
        }
      
        headline_message(lang::translate('order_payment_select_payment_overview'));
        
        $options = array ('payment_url' => '/order/banktransfer/payment');  
        echo view::get('order', 'confirm_button', $options);
        
        headline_message(lang::translate('order_checkout_overview'));
        echo view::get('order', 'display_basket', $vars);   
        echo view::get('order', 'confirm_form');
        echo view::get('order', 'confirm_button', $options);
    }
}
