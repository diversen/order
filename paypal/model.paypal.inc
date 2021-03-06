<?php


class order_paypal {
    
    static function displayMethodLink () {
        $text = "Paypal";
        return html::createLink('/order/paypal/index', $text);
    } 
    
    public static function confirmButton () {
        $str = "<form action=\"/order/paypal/ReviewOrder\" method=\"POST\">\n";
	$str.= "<input type=\"hidden\" name=\"paymentType\" value=\"$paymentType\" />\n";        
        $str.= "<input type=\"image\" name=\"submit\" src=\"https://www.paypal.com/en_US/i/btn/btn_xpressCheckout.gif\" />";
        $str.= "</form>";
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
        $options = array ('payment_url' => '/order/paypal/ReviewOrder');
        echo view::get('order', 'confirm_button', $options);
        headline_message(lang::translate('order_display_confirm_details'));
        echo view::get('order', 'display_basket', $vars);          
        echo view::get('order', 'confirm_form');        
        echo view::get('order', 'confirm_button', $options);
    }

    
    public static $totalPrice = 0;
    public static $shippingCost = 0;
    public static $itemsURL = '';
    public static $shippingURL = '';
    public static $shippingInfoURL = '';
    public static $localeURL = '';
    
    
    public static function getTotalPrice () {
        return self::$totalPrice;
    }
    
    public static function getShippingCost () {
        return self::$shippingCost;
    }
    
    public static function getItemsURL () {
        return self::$itemsURL;
    }
    
    public static function getLocaleURL () {
        return self::$localeURL;
    }
    
    public static function getShippingURL () {
        return self::$shippingURL;
    }
    
    public static function getShippingInfoURL () {
        return self::$shippingInfoURL;
    }
    
    public static function init() {
        
        $items = order::getBasketItems();
        $str = '';
        $i = 0; $total_weight = 0; $total_price = 0.00;
        $order_items = 0;
        foreach ($items as $key => $val) {
           $item = order::getItem($val['item_id']);
           $str.= "&L_NAME$i=" . urlencode($item['item_name']);
           $str.= "&L_AMT$i=$item[price]";
           $str.= "&L_QTY$i=$val[num_items]";
           $str.= "&L_NUMBER$i=$item[id]";
           $str.= "&L_DESC$i=" . urlencode($item['item_name_alt']);
           $total_price = $total_price + ($val['num_items'] * $item['price']);
           $total_weight = $total_weight + ($val['num_items'] * $item['weight']);
           $order_items= $order_items + $val['num_items']; 
           $i++;          
        }
        
        echo self::$totalPrice = $total_price;
        self::$itemsURL = $str;
        $shipping_info = orderShipping::getShippingInfo($order_items, $total_price, $total_weight);        
        //print_r($shipping_info); die;
        self::$shippingCost = $shipping_info['shipping_cost'];       
        self::setShippingURL();     
        self::setShippingInfoURL();
        self::setLocaleURL();
    }
    
    public function setLocaleURL () {
        $ary = config::getMainIni('language');
        self::$localeURL = "&LOCALECODE=$ary[1]";
    }
            
    public static function setShippingURL () {
        load_post('order_form');   
        $shipto_address = "&ADDRESSOVERRIDE=1";
        //$shipto_address.= "&ADDROVERRIDE=1";
        $shipto_address = "&SHIPTONAME=$_POST[name]";
        $shipto_address.= "&SHIPTOSTREET=$_POST[adresse]";
        $shipto_address.= "&SHIPTOCITY=$_POST[city]";
        $shipto_address.= "&SHIPTOZIP=$_POST[postal_code]";      
        $shipto_address.= "&SHIPTOCOUNTRYCODE=$_POST[country]";
        $shipto_address.= "&SHIPTOSTATE=$_POST[region]";
        //$shipto_address.= "&NOSHIPPING=1";
        self::$shippingURL =  $shipto_address;
    }
    
    public static function setShippingInfoURL () {
        $shipping_text = lang::translate('order_amount_added_shipping_cost');
        $shipping_cost = self::getShippingCost();
        $str = '';
        $str.= "&L_SHIPPINGOPTIONAMOUNT0=$shipping_cost";
        $str.= "&L_SHIPPINGOPTIONLABEL0=Standard";
        $str.= "&L_SHIPPINGOPTIONNAME0=$shipping_text";
        $str.= "&L_SHIPPINGOPTIONISDEFAULT0=true";
           //$nvpstr.= "&INSURANCEAMT=1.00&INSURANCEOPTIONOFFERED=true";
        $str.= "&CALLBACK=https://www.ppcallback.com/callback.pl";
        $str.= "&SHIPPINGAMT=$shipping_cost";
        self::$shippingInfoURL = $str;
    }
    
    /**
     * 
     * method for processing a payment 
     * @deprecated moved to individual payments modules. 
     * @return void 
     */    
    public static function sendOrderMails (){
        $subject = lang::translate('order_checkout_order_details');

        load_post('order_form');
        
        if (empty($_POST)) return;

        $from = get_main_ini('site_email');
        $order_reply_to = get_main_ini('site_email');
        $order_invoice_to = get_main_ini('site_email');

        ob_start();

        self::displayOrderEmail();
        $message = ob_get_contents();

        ob_end_clean();

        $res_consumer = cosMail::text($_POST['email'], $subject, $message, $from, $order_reply_to);
        if (!$res_consumer) {
            $error = "Could not send order email to $_POST[email]\n";
            error_log($error);
        }
        
        $res_invoice = cosMail::text($order_invoice_to, $subject, $message, $from, $order_reply_to);
        if (!$res_invoice) {
            $error = "Could not send order email to $_POST[email]\n";
            error_log($error);
        }
    }
    
    /** 
     * displays an order email 
     * @return void
     */
    public static function displayOrderEmail (){

        $order_items = order::getBasketItems();
        if (empty($order_items)){
            echo lang::translate('order_no_items_in_basket');
            return;
        }

        $vars['order_items'] = $order_items;
        echo view::get('order', 'display_email', $vars);
        echo view::get ('order', 'confirm_form_email');

        echo "\n\n";

        echo lang::translate('order_paypal_invoice_email_message') . "\n";
        echo lang::translate('order_checkout_greeting') . " http://$_SERVER[SERVER_NAME]";
        return;
    }
}
