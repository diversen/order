<?php

/**
 * Main class in order / shopping cart system
 */

/**
 * @ignore
 */
include_once "helpers.inc";
include_once "upload.php";

template::setJs('/js/jquery.validate.js');
template::setInlineJs(get_module_path('order') . '/lang/da_DK/da_DK.js');


template::setInlineJs(get_module_path('order') . '/assets/order.js');
template::setInlineCss(get_module_path('order') . '/assets/order.css');

include_model('order/shipping');
include_model('order/shippingfree');
include_model('order/category');
include_model('order/select');
include_model('order/gallery');

/**
 * order class if the class for adding items to cart etc. 
 * updating cart, checkout, etc. 
 */
class order  {
    
    /**
     *
     * @var array $errors array holding errors
     */
    public static $errors = array();
    
    /**
     *
     * @var string  $table name of the order items table 
     */
    public static $table = 'order_items';
    
    /**
     * @var string  $mdouleName name of the module
     */
    public static $moduleName = 'order';


    /**
     * method for validating shipping form
     */
    public function validateShippingForm (){
        $_POST = html::specialEncode($_POST);

        if (strlen($_POST['name']) < 3){
            self::$errors['name'] = lang::translate('order_order_form_error_name');
        }

        if (strlen($_POST['adresse']) < 3){
            self::$errors['adresse'] = lang::translate('order_order_form_error_adresse');
        }
        if (strlen($_POST['city']) < 1){
            self::$errors['city'] = lang::translate('order_order_form_error_city');
        }

        if(!preg_match("#^[0-9]{4}$#", $_POST['postal_code'])) {
            self::$errors['zip_code'] = lang::translate('order_order_form_error_zip_code');
        }

        if (!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
            self::$errors['email'] = lang::translate('order_order_form_error_email');
        }

        if (isset($_POST['checkme'])){
            if (strlen($_POST['diff_name']) < 3){
                self::$errors['diff_name'] = lang::translate('order_order_form_error_diff_name');
            }

            if (strlen($_POST['diff_adresse']) < 3){
                self::$errors['diff_adresse'] = lang::translate('order_order_form_error_diff_adresse');
            }
            if (strlen($_POST['diff_city']) < 1){
                self::$errors['diff_city'] = lang::translate('order_order_form_diff_error_city');
            }

            if(!preg_match("#^[0-9]{4}$#", $_POST['diff_postal_code'])) {
                self::$errors['diff_zip_code'] = lang::translate('order_order_form_error_diff_zip_code');
            }
        }
    }
    /**
     * method for sanitizing a submission. 
     */
    public function sanitize(){
        if (isset($_POST['submit'])){
            $_POST = html::specialEncode($_POST);
        }
    } 
    
    /**
     *
     * @return array $modules all modules set in order.ini order_item_modules 
     */
    static function getItemModules() {
        return get_module_ini('order_item_modules');
    }


    /**
     * method for displaying checkout. 
     * @return void
     * 
     */
    public function displayCheckout(){

        $order_items = order::getBasketItems();
        if (empty($order_items)){
            echo lang::translate('order_checkout_no_items_in_basket');
            return;
        }
        
        if (isset($_POST['submit'])){
            $this->validateShippingForm();
            if (!empty(order::$errors)){
                view_form_errors(order::$errors);
            } else {
                save_post('order_form');
                unset($_POST['submit']);
                self::setShippingCookie($_POST);
                header("Location: /order/payment");
                die();
            }
        } else {            
            if (!load_post('order_form')) {
                $shipping_info = self::getShippingCookie();
                if (!empty($shipping_info)) {
                    // no need to special encode. Cookies are auto encoded. 
                    $_POST = $shipping_info;
                }
            }
        }          
        echo templateView::get('order', 'order_form');
    }
    
    public static function setShippingCookie ($values = array ()) {
        if (isset($_COOKIE['order_client_id'])){
            $id = $_COOKIE['order_client_id'];
        } else {
            $id = md5(uniqid());
            $order_cookie_time = time() + get_module_ini('order_cookie_time');
            setcookie('order_client_id', $id, $order_cookie_time, '/');
        }
        cache::set('order_shipping_info', $id, $values);    
    }
    
    /**
     * gets shipping info from system cache.
     * @return array $shipping_info array with shipping info. empty array
     *               if shipping info has not been set.   
     */
    public static function getShippingCookie (){      
        if (!isset($_COOKIE['order_client_id'])){
            $id = md5(uniqid());
            $order_cookie_time = time() + get_module_ini('order_cookie_time');
            setcookie('order_client_id', $id, $order_cookie_time, '/');
            return array();
        }

                
        $shipping_info = cache::get('order_shipping_info', $_COOKIE['order_client_id'], get_module_ini('order_cookie_time'));
        if (!isset($shipping_info)) {
            $shipping_info = array ();
        }
        return $shipping_info;
    }
    
    /**
     * method for displaying payment options. 
     */
    public function displayPayment () {
        if (isset($_POST['submit'])){
            $this->validateShippingForm();
            if (!empty(order::$errors)){
                view_form_errors(order::$errors);
            } else {
                save_post('order_form');
                unset($_POST['submit']);
                $cookie = serialize($_POST);
                $res = setcookie(
                    'order_form_cookie',
                $cookie, get_module_ini('order_cookie_time') +time(), "/");
                header("Location: /order/payment");
                die();
            }
        } else {            
            if (!load_post('order_form')) {
                if (isset($_COOKIE['order_form_cookie'])) {
                    $_POST = unserialize($_COOKIE['order_form_cookie']);
                }
            }
        }
                
        $payment_modules = get_module_ini('order_payment_modules');
        moduleLoader::includeModules($payment_modules);
        
        echo templateView::includeModuleView(
            'order', 'payment/display_payment_options', $payment_modules, 1
        );
        
    }
    
    /**
     * 
     * method for processing a payment 
     * @deprecated moved to individual payments modules. 
     * @return void 
     */    
    public static function process (){
        $subject = lang::translate('order_checkout_order_details');

        load_post('order_form');
        
        if (empty($_POST)) return;

        $from = get_main_ini('site_email');
        $order_reply_to = get_main_ini('site_email');
        $order_invoice_to = get_main_ini('site_email');

        ob_start();

        order::displayOrderEmail();
        $message = ob_get_contents();

        ob_end_clean();

        $res_consumer = mail_utf8($_POST['email'], $subject, $message, $from, $order_reply_to);
        if (!$res_consumer) {
            $error = "Could not send order email to $_POST[email]\n";
            error_log($error);
        }
        
        $res_invoice = mail_utf8($order_invoice_to, $subject, $message, $from, $order_reply_to);
        if (!$res_invoice) {
            $error = "Could not send order email to $_POST[email]\n";
            error_log($error);
        }
        
        //setcookie ("order_items", "", time() - 3600, "/");
        self::clearBasketItems();
        header("Location: /order/done");
        die;
    }
    // }}}
        
    
    /**
     *
     * Get currency symbol. If set in module ini (order_currency), then this 
     * will be used. Otherwise base it on locales. 
     * 
     * @return string   international currency symbol (e.g. USD, DKK) 
     */
    public static function getCurrencySymbol () {
        $currency = get_module_ini('order_currency');
        if ($currency) {
            return $currency;
        }
        static $local = null;
        if (!isset($local)){
            $local = localeconv();
        }
        return $currency = trim($local['int_curr_symbol']);
    }



    // {{{ displayCart
    /**
     * display all items in shop
     */
    public static function displayAllCartItems (){
        $db = new db();
        $all_items = $db->selectAll('order_items', null, null, null, null, 'item_order', true);
        templateView::includeModuleView('order', 'category/cart_category', $all_items);
    }
    // }}}
    
    // {{{ displayItem ($id)
    public function displayItem ($id){
     
        $val = $this->getItem($id);
        $items = self::getBasketItems();

        if (empty($val)){
            header ("HTTP/1.1 301 Moved Permanently");
            header ("Location: /order/cart");
        }
        
        if (isset($_GET['order_item'])) {
            $int_options = array("options" => array("min_range" => 0 ));
            $get_id = filter_var($_GET['order_item'], FILTER_VALIDATE_INT, $int_options);
            
            $val['add_order'] = $items[$get_id]['add_order'];
            $val['selected'] = $items[$get_id];
        } else {
            // finder  
            $val['add_order'] = 1;
        }
        
        $url = 
        strings::utf8Slug("/order/item/$val[id]", $val['item_name']);

        if (isset($_GET['order_item'])) {
            $url.="?order_item=" . $_GET['order_item'];
        }
        
        http::permMovedHeader($url);
        
        $title = lang::translate('order_view_single_product');
        $title.= MENU_SUB_SEPARATOR_SEC;
        $title.= $val['item_name'];
        template::setTitle(html::specialEncode($title));

        $meta_desc = html::specialEncode($val['item_name_alt']);
        template::setMeta(array('description' => $meta_desc));

        $filters = get_module_ini('order_filters');
        $val['item_description'] = get_filtered_content($filters, $val['item_description']);
  
        echo templateView::includeModuleView('order', 'display_item', $val, 1);
    }

    /**
     * adds a item to basket. an addtion to the basket always comes ffrom an POST
     * operation. 
     * 
     * @param array $options array ('redirect' => '/location/to/redirect');
     */
    public function addToBasket ($options = null){        
        $db = new db();        
        if (isset($_POST['add_order'])){
            $add_order = filter_var($_POST['add_order'], FILTER_VALIDATE_INT);
            $item_id = filter_var($_POST['item_id'], FILTER_VALIDATE_INT);           
            $order_item = filter_var($_POST['order_item'], FILTER_VALIDATE_INT);
                     
            if (is_int($add_order) && is_int($item_id)){
                $order_items = self::getBasketItems();

                unset($_POST['order_submit']);
                unset($_POST['add_order']);
                unset($_POST['item_update']);
                unset($_POST['order_item']);
                    
                $match = false;
                    
                if (!empty($order_items)) {                    
                        
                        
                    foreach ($order_items as $key => $val) {
                        unset($val['add_order']);
                            
                        // check for exact match between item in basket
                        // and item being submitted. This means we can
                        // operate on anything on the $_POST array. 
                        if ($val == $_POST) {
                            $match = true;
                            break;
                        } 
                    }
                        
                    // match we update the $order_items[$key] array
                    // with new value. 
                    if ($match) {                           
                        if ($add_order <= 0) {
                            unset ($order_items[$order_item]);
                        } else {
                            $_POST['add_order'] = $add_order;
                            $order_items[$key] = $_POST;

                        }
                    // no match but if there is an add_order we add 
                    // the item to the $order_items array
                    } else {
                        if ($add_order <= 0) {
                            unset ($order_items[$order_item]);
                        } else {
                            $_POST['add_order'] = $add_order;
                            $order_items[] = $_POST;
                        }                            
                    }
                // first item into basket. 
                } else {
                    $_POST['add_order'] = $add_order;
                    $order_items[] = $_POST; 
                } 
                self::setBasketItems($order_items);

                if (isset($options['redirect'])){
                    $header = "Location: $options[redirect]";
                    header ($header);
                } else {
                    session::setActionMessage(lang::translate('order_item_added_to_basket'));
                    $redirect = get_module_ini('order_redirect_update_item');
                    if (!isset($redirect)) {
                        $redirect = "/order/cart";
                    }                    
                    header ("Location: $redirect");
                    exit;
                }               
            }
        }    
    } 

    /**
     * sets the basket items into the cache.
     * @param array $values the values of the basket 
     */
    public static function setBasketItems ($values = array()) {
        if (isset($_COOKIE['order_client_id'])){
            $id = $_COOKIE['order_client_id'];
        } else {
            $id = md5(uniqid());
            $order_cookie_time = time() + get_module_ini('order_cookie_time');
            setcookie('order_client_id', $id, $order_cookie_time, '/');
        }
        cache::set('order_basket_items', $id, $values);    
    }
    
    /**
     * delete all basket items from cache. 
     * Should be called after successfull checkput 
     */
    public static function clearBasketItems () {
        self::setBasketItems(array());       
    }


    /**
     * gets basket item from system cache.
     * @return array $basket items return the items in basket.  
     */
    public function getBasketItems (){      
        if (!isset($_COOKIE['order_client_id'])){
            $id = md5(uniqid());
            $order_cookie_time = time() + get_module_ini('order_cookie_time');
            setcookie('order_client_id', $id, $order_cookie_time, '/');
            return array();
        }

                
        $order_items = cache::get('order_basket_items', $_COOKIE['order_client_id'], get_module_ini('order_cookie_time'));
        if (!isset($order_items)) {
            $order_items = array ();
        }
        
        foreach ($order_items as $key => $val) {
            $row = self::getItem($val['item_id']);
            if (empty($row)) {
                unset($order_items[$key]);
                self::setBasketItems($order_items);
            }
        }
        
        if (empty($order_items)) {
            $order_items = array();
        }
        return $order_items;
    }

    /**
     * method for getting a single item
     * @param int $id the id of the item
     * @return array $row the full item. 
     */
    public static function getItem ($id){
        $db = new db();
        $item = $db->selectOne('order_items', 'id', $id);
        return $item;
    }


    /**
     * gets all items which are not out of sale. 
     * @return array $all_items
     */
    public static function getItemsInBlock (){
        $db = new db();
        $all_items = $db->selectAll('order_items', array ('id', 'item_name', 'item_name_alt'), 'stock > 0', null, null, 'item_order', true);
        return $all_items;
    }

    /**
     * display a basket with all items and option for adding all items. 
     * @return type 
     */
    public static function displayQuickBasket (){

        $order_items = order::getBasketItems();
        $all_items = order::getItemsInBlock();

        $vars['order_items'] = order::getBasketItems();
        $vars['all_items'] = order::getItemsInBlock();

        templateView::includeModuleView('order', 'display_quick_basket', $vars);
        return;
    }


    /**
     * displays basket. 
     * @return void
     */
    public static function displayBasket (){
        $vars['order_items'] = order::getBasketItems();
        if (empty($vars['order_items'])){
            echo lang::translate('order_no_items_in_basket');
            return;
        }

        templateView::includeModuleView('order', 'display_basket', $vars);
        templateView::includeModuleView('order', 'display_checkout_submit');

    }

    /**
     * displays basket and confirm form. 
     * @return type 
     */
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

        templateView::includeModuleView('order', 'display_basket', $vars);       
        templateView::includeModuleView('order', 'confirm_form');
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
        templateView::includeModuleView('order', 'display_email', $vars);
        templateView::includeModuleView ('order', 'confirm_form_email');

        echo "\n\n";

        echo lang::translate('order_checkout_invoice_email_message');
        echo lang::translate('order_checkout_greeting') . " $_SERVER[SERVER_NAME]";
        return;
    }
    // }}}
    // {{{
    /** 
     * displays an order email 
     * @return void
     */
    public static function displaySystemOrder (){

        $order_items = order::getBasketItems();
        if (empty($order_items)){
            echo lang::translate('order_no_items_in_basket');
            return;
        }

        $vars['order_items'] = $order_items;
        return templateView::get('order', 'sales/system_order', $vars);
    }
    // }}}
}
