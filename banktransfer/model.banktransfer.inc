<?php

class orderBanktransfer {
    
    static function displayMethodLink () {
        $text = "Bankoverførsel (forudbetaling)";
        return html::createLink('/order/banktransfer/index', $text);
    } 
    
    public static function displayConfirm (){
    $order_items = order::getBasketItems();
        if (empty($order_items)){
            echo lang::translate('order_no_items_in_basket');
            return;
        }


        load_post('order_form');        
        
        $vars['order_items'] = $order_items;
        //print_r($vars);
        if (empty($vars['order_items'])){
            echo lang::translate('order_no_items_in_basket');
            return;
        }
      
        
        
        headline_message(lang::translate('order_payment_select_payment_overview'));
        
        $options = array ('payment_url' => '/order/banktransfer/payment');  
        templateView::includeModuleView('order', 'confirm_button', $options);
        
        echo "<h3>Ordre Oversigt</h3>\n";
        templateView::includeModuleView('order', 'display_basket', $vars);   
        
        templateView::includeModuleView('order', 'confirm_form');
          
        templateView::includeModuleView('order', 'confirm_button', $options);
    }
}