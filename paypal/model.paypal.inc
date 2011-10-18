<?php


class orderPaypal {
    
    static function displayMethodLink () {
        $text = "Paypal";
        return html::createLink('/order/paypal/index', $text);
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
    
    public static function shippingToPaypalURL () {
        //$shiptoAddress = "&SHIPTONAME=$personName&SHIPTOSTREET=$SHIPTOSTREET&SHIPTOCITY=$SHIPTOCITY&SHIPTOSTATE=$SHIPTOSTATE&SHIPTOCOUNTRYCODE=$SHIPTOCOUNTRYCODE&SHIPTOZIP=$SHIPTOZIP";
         
        
        
        load_post('order_form');
        //print_r($_POST);
            
        $shipto_address = "&SHIPTONAME=$_POST[name]";
        $shipto_address.= "&SHIPTOSTREET=$_POST[adresse]";
        $shipto_address.= "&SHIPTOCITY=$_POST[city]";
        $shipto_address.= "&SHIPTOZIP=$_POST[postal_code]";      
        $shipto_address.= "&SHIPTOCOUNTRYCODE=$_POST[country]";
        
        //if (!empty($_POST['region'])) {
            $shipto_address.= "&SHIPTOSTATE=$_POST[region]";
        //}
        return  $shipto_address;

        //foreach ($shipping_info as $key => $val) {
        //    print $val;
        //}
        //print_r($shipping_info);
        //die;
    }
    
    public static function itemsToPaypalForm () {
        
    }
    
}