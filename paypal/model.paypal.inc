<?php


class orderPaypal {
    
    static function displayMethodLink () {
        $text = "Paypal";
        return html::createLink('/order/paypal/ReviewOrder', $text);
        
        //$str = "<form action=\"/order/paypal/ReviewOrder\" method=\"POST\">\n";
	//$str.= "<input type=\"hidden\" name=\"paymentType\" value=\"$paymentType\" />\n";
        
        //$str.= "<input type=\"image\" name=\"submit\" src=\"https://www.paypal.com/en_US/i/btn/btn_xpressCheckout.gif\" />";
        //$str.= "</form>";
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
            $shipto_address.= "&NOSHIPPING=1";
        //}
        return  $shipto_address;

        //foreach ($shipping_info as $key => $val) {
        //    print $val;
        //}
        //print_r($shipping_info);
        //die;
    }
    
    public static $totalPrice = 0;
    public static $shippingCost = 0;
    
    
    public static function getTotalPrice () {
        return locfloat_to_sysfloat(self::$totalPrice);
    }
    
    public static function getShippingCost () {
        return self::$shippingCost;
    }
    
    public static function itemsToPaypalURL () {
        
        $items = order::getBasketItems();
           //print_r($items);  die;
        $str = '';
        $i = 0; $total_weight = 0; $total_price = 0.00;
        foreach ($items as $key => $val) {
           //print_r($val);
           //die;
           $item = order::getItem($val['item_id']);
           $str.= "&L_NAME$i=" . urlencode($item['item_name']);
           $str.= "&L_AMT$i=$item[price]";
           $str.= "&L_QTY$i=$val[add_order]";
           $str.= "&L_NUMBER$i=$item[id]";
           $str.= "&L_DESC$i=" . urlencode($item['item_name_alt']);
           $total_price = $total_price + $val['add_order'] * $item['price'];
           $total_weight = $total_weight + $item['weight'];
           $i++;
           
        }
        self::$totalPrice = $total_price;
        self::$shippingCost = orderShipping::getWeightToCost('private', $total_weight); 
        //print $str; die;
        return $str;
        /*
        $nvpstr.= "&L_NAME0=".$L_NAME0."&L_NAME1=".$L_NAME1;
        $nvpstr.= "&L_AMT0=".$L_AMT0."&L_AMT1=".$L_AMT1;
        $nvpstr.= "&L_QTY0=".$L_QTY0."&L_QTY1=".$L_QTY1;           
        $nvpstr.= "&L_NUMBER0=1000&L_DESC0=Size: 8.8-oz&L_NUMBER1=10001";
        $nvpstr.= "&L_DESC1=Size: Two 24-piece boxes";
         * */
    }
    
}