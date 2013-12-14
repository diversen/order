<?php

/**
 * Main class in order / shopping cart system
 */

/**
 * @ignore
 */
//include_once "coslib/helpers.inc";
include_once "coslib/upload.php";
include_once "coslib/cache.php";
include_once "coslib/intl.php";
include_once config::getModulePath('order') . "/helpers.inc";

order::loadAssets();

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
     * loads assets
     */
    public static function loadAssets () {
        template::setJs('/js/jquery.validate.js');
        
        $lang = config::getMainIni('language');
        template::setInlineJs(get_module_path('order') . "/lang/$lang/$lang.js");
        template::setInlineJs(get_module_path('order') . '/assets/order.js');

        include_model('order/shipping');
        include_model('order/shippingfree');
        include_model('order/category');
        include_model('order/select');
        include_model('order/gallery');
    }

    /**
     * method for validating shipping form
     */
    public function validateShippingForm (){
        
        $_POST = html::specialEncode($_POST);

        $num_types = orderShipping::getCountTypes();
        if ($num_types == 0 || $num_types == 1 ) return true;
        
        if (!empty($_POST['order_shipping_type'])) {
            $shipping_types = orderShipping::getTypes();
            
            $ret = false;
            foreach ($shipping_types as $key => $val) {
                if ($val['id'] == $_POST['order_shipping_type']) {
                    $ret = true;
                    break;
                } else {
                    $ret = false;
                }
            }
            
            if (!$ret) {
                self::$errors[] = lang::translate('order_order_form_error_shipping_type');
            }          
        } else {
            self::$errors[] = lang::translate('order_order_form_error_shipping_type');
        }
        
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
        return config::getModuleIni('order_item_modules');
    }

    /**
     * method for displaying checkout. 
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
                http::locationHeader("/order/payment");
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
        echo view::get('order', 'order_form');
    }
    
    /**
     * method for setting a cookie with shipping info. 
     * This is entered in displayCheckout
     * @param type $values 
     */
    public static function setShippingCookie ($values = array ()) {
        if (isset($_COOKIE['order_client_id'])){
            $id = $_COOKIE['order_client_id'];
        } else {
            $id = md5(uniqid());
            $order_cookie_time = time() + config::getModuleIni('order_cookie_time');
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
            $order_cookie_time = time() + config::getModuleIni('order_cookie_time');
            setcookie('order_client_id', $id, $order_cookie_time, '/');
            return array();
        }
                
        $shipping_info = 
            cache::get(
                'order_shipping_info', 
                $_COOKIE['order_client_id'], 
                config::getModuleIni('order_cookie_time')
            );
        if (!isset($shipping_info)) {
            $shipping_info = array ();
        }
        return $shipping_info;
    }
    
    /**
     * method for displaying payment options. 
     * will load different options from order.ini setting: order_payment_modules
     * e.g. 
     * 
     * order_payment_modules[] = 'paypal'
     * order_payment_modules[] = 'email'
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
                setcookie(
                    'order_form_cookie',
                    $cookie, config::getModuleIni('order_cookie_time') +time(), 
                     "/");
                http::locationHeader("/order/payment");
            }
        } else {            
            if (!load_post('order_form')) {
                if (isset($_COOKIE['order_form_cookie'])) {
                    $_POST = unserialize($_COOKIE['order_form_cookie']);
                }
            }
        }
                
        $payment_modules = config::getModuleIni('order_payment_modules');
        
        moduleloader::includeModules($payment_modules);
        
        echo view::get(
            'order', 'payment/display_payment_options', $payment_modules
        );
        
        //die;
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

        self::clearBasketItems();
        http::locationHeader("/order/done");
    }
        
    /**
     *
     * @param float $value e.g. 20.00
     * @return string $formatted e.g. DKK 20,00. 
     */
    public static function getCurrencyShort ($value, $sep = "&nbsp;") {
        return intl::formatCurrency(config::getMainIni('locale'), $value);
    }
    
    /**
     *
     * Get currency symbol. If not set in module ini (order_currency), then this 
     * will be used. Based on current setting of locales. 
     * @return string $str international currency symbol (e.g. USD, DKK) 
     */
    public static function getCurrencySymbol () {
        $currency = config::getModuleIni('order_currency');
        if ($currency) {
            return $currency;
        }
        static $local = null;
        if (!isset($local)){
            $local = localeconv();
        }
        return $currency = trim($local['int_curr_symbol']);
    }
    
    /**
     * get all info of all items used for getting
     * @return array assoc array with info about all items
     *              // full info about all items
     *              $full_info['items'] = array ();
     *               
     *              $full_info['num_items'] = $num_items;
     *              $full_info['weight'] = $weight;
     *              $full_info['total'] = $total;
     *              $full_info['tax'] = $tax;
     */
    public static function getFullCartInfo () {
        $order_items = order::getBasketItems();
        $total = $sub_total = $weight = $num_items = 0;

        $full_info = array ();
        $full_info['items'] = array();

        foreach ($order_items as $key => $val){

            $item = self::getItem($val['item_id']);
            $full_info['items'][$item['id']] = $item;
            $num_items = $num_items + $val['num_items'];
            
            $full_info['items'][$item['id']]['num_items'] = $val['num_items'];
                      
            $sub_total = $val['num_items'] * $item['price'];
            $full_info['items'][$item['id']]['sub_total'] = $sub_total;
            
            $total = $sub_total + $total;
            
            $sub_weight = $val['num_items'] * $item['weight'];
            $full_info['items'][$item['id']]['sub_weight'] = $sub_weight;
            
            $weight = $weight + $sub_weight;
        }
        $full_info['num_items'] = $num_items;
        $full_info['weight'] = $weight;
        $full_info['total'] = $total;
        
        $tax = $total * config::getModuleIni('order_added_tax');
        $full_info['tax'] = $tax;
                 
        return $full_info;
    }
    
    /**
     * 
     * display all items in a shopping cart
     */
    public static function displayAllCartItems (){
        $all_items = db_q::setSelect('order_items')->order('item_order')->fetch();
        echo view::get('order', 'category/cart_category', $all_items);
    }
    
    /**
     * method for getting number of items in basket from an id
     * @param int $id
     * @return int $id number of items in basket 
     */
    public static function getNumItemsInBasket ($id) {
        $items = self::getBasketItems();
        foreach ($items as $key => $val){
            if ($val['item_id'] == $id) {
                return $val['num_items'];
            }
        }
        return 0;
        
    }

    /**
     * method for displaying a single shop item
     * @param int $id the id of the shopping item 
     */
    public static function displayItem ($id){
     
        $val = self::getItem($id);
        $num_items = self::getNumItemsInBasket($id);
        
        // initial value of item is 1
        if ($num_items == 0) {
            $num_items = 1;
        }
        
        if (empty($val)){
            header ("HTTP/1.1 301 Moved Permanently");
            header ("Location: /order/cart");
        }
        
        $url = strings::utf8Slug("/order/item/$val[id]", $val['item_name']);
        http::permMovedHeader($url);
        
        $title = lang::translate('order_view_single_product');
        $title.= MENU_SUB_SEPARATOR_SEC;
        $title.= $val['item_name'];
        template::setTitle($title);

        $meta_desc = html::specialEncode($val['item_name_alt']);
        template::setMeta(array('description' => $meta_desc));

        $filters = config::getModuleIni('order_filters');
        $val['item_description'] = get_filtered_content($filters, $val['item_description']);
        $val['num_items'] = $num_items;
        
        echo view::get('order', 'display_item', $val);
    }

    /**
     * adds a item to basket. an addtion to the basket always comes from an POST
     * operation. 
     * 
     * @param array $options array ('redirect' => '/location/to/redirect');
     */
    public static function addToBasket ($options = null){       
      
        if (isset($_POST['num_items'])){

          (int)$num_items = filter_var($_POST['num_items'], FILTER_VALIDATE_INT);
          (int)$item_id = filter_var($_POST['item_id'], FILTER_VALIDATE_INT);

            if (is_int($num_items) && is_int($item_id)){
                self::updateBasket($item_id, $num_items);

                if (isset($options['redirect'])){
                    http::locationHeader($options['redirect']);
                } else {
                    session::setActionMessage(lang::translate('order_item_added_to_basket'));
                    $redirect = config::getModuleIni('order_redirect_update_item');
                    if (!isset($redirect)) {
                        $redirect = "/order/cart";
                    }                    
                    http::locationHeader ($redirect);
                }               
            }
        }    
    } 
    
    /**
     * method for updating the basket
     * @param int $item_id the id of the item
     * @param int $num_items number of the item 
     */
    public static function updateBasket( $item_id, $num_items) {
        
        $order_items = self::getBasketItems();
        $match = false;
        foreach ($order_items as $key => $val) {
    
            if ($val['item_id'] == $item_id) {
                if ($num_items > 0) {
                    $order_items[$key]['num_items'] = $num_items;
                } else {
                    $match = true;
                    unset($order_items[$key]);                            
                }
                $match = true;                       
            }
        }
                
        if (!$match) {
            $order_items[] = array ('item_id' => $item_id, 'num_items' => $num_items); 
        }
                            
        self::setBasketItems($order_items);
    
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
            
            $order_cookie_time = time() + config::getModuleIni('order_cookie_time');
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
    public static function getBasketItems (){    
        // first item
        if (!isset($_COOKIE['order_client_id'])){
            $id = md5(uniqid());
            $order_cookie_time = time() + config::getModuleIni('order_cookie_time');
            setcookie('order_client_id', $id, $order_cookie_time, '/');
            $_COOKIE['order_client_id'] = $id;
            return array();
        }
               
        $order_items = cache::get('order_basket_items', $_COOKIE['order_client_id'], config::getModuleIni('order_cookie_time'));
        if (empty($order_items)) {
            $order_items = array ();
            return $order_items;
        }
        
        // check if any item has been deleted
        foreach ($order_items as $key => $val) {
            $item = order::getItem($val['item_id']);
            if (empty($item)) {
                unset($order_items[$key]);
                
                //continue;
            }
        }
        
        self::setBasketItems($order_items);

        return $order_items;
    }

    /**
     * method for getting a single item
     * @param int $id the id of the item
     * @return array $row the full item. 
     */
    public static function getItem ($id){
        
        static $items;
        if (isset($items[$id])) return $items[$id];
        
        $db = new db();
        $item = $db->selectOne('order_items', 'id', $id);
        $items[$id] = $item;
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

        view::includeModuleView('order', 'display_quick_basket', $vars);
        view::includeModuleView('order', 'display_checkout_submit');
        return;
    }


    /**
     * displays basket. 
     */
    public static function displayBasket (){
        $vars['order_items'] = order::getBasketItems();

        if (empty($vars['order_items'])){
            echo lang::translate('order_no_items_in_basket');
            http::locationHeader('/order/cart');
        }

        view::includeModuleView('order', 'display_basket', $vars);
        view::includeModuleView('order', 'display_checkout_submit');

    }

    /**
     * displays basket and confirm form. 
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

        view::includeModuleView('order', 'display_basket', $vars);       
        view::includeModuleView('order', 'confirm_form');
    }

    /** 
     * displays an order email 
     */
    public static function displayOrderEmail (){

        $order_items = order::getBasketItems();
        if (empty($order_items)){
            echo lang::translate('order_no_items_in_basket');
            return;
        }

        $vars['order_items'] = $order_items;
        view::includeModuleView('order', 'display_email', $vars);
        view::includeModuleView ('order', 'confirm_form_email');

        echo "\n\n";

        echo lang::translate('order_checkout_invoice_email_message');
        echo lang::translate('order_checkout_greeting') . " $_SERVER[SERVER_NAME]";
        return;
    }
    
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
        return view::get('order', 'sales/system_order', $vars);
    }
}
