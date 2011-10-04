<?php

/**
 * Main class in order / shopping cart system
 */
//include_once "mySqlForm.php";
include_once "upload.php";

template::setInlineJs(_COS_PATH . '/modules/order/lang/da_DK/da_DK.js');
template::setJs('/js/jquery.validate.js');
template::setInlineJs(_COS_PATH . '/modules/order/order.js');

include_model('order/shipping');
include_model('order/shipping_free');
include_model('order/category');
include_model('order/select');
include_model('order/gallery');
include_module('gallery/admin');


class order  {
    public static $errors = array();
    static $options = array();
    public static $table = 'order_items';
    public static $moduleName = 'order';

    /**
     *
     * @param id    used when we update or delete
     */
    static function form($method, $frag = 3){

        html::$autoLoadTrigger = 'submitted';
        html::formStart('order_item_form');
        
        if ($method == 'delete') {
            html::legend(lang::translate('order_item_form_delete_legend'));
            $button_text = lang::translate('order_delete');
            html::label('submit', '');
            html::submit('submit', $button_text);
            html::formEnd();
            echo html::getStr();
            return;
        }

        if ($method == 'update') {
            html::legend(lang::translate('order_item_form_edit_legend'));

            $id = uri::$fragments[$frag];
            $row = order::getItem($id);
            
            html::init($row);
            $button_text = lang::translate('order_update');            
            html::hidden('method', 'item_update');           
        }

        if ($method == 'insert') {
            html::init();
            html::legend(lang::translate('order_item_form_insert_legend'));
            $button_text = lang::translate('order_insert');
            html::hidden('method', 'item_insert');
        }

        html::label('item_name', lang::translate('order_item_form_title'));
        html::text('item_name');

        html::label('item_name_alt', lang::translate('order_item_form_title_alt'));
        html::text('item_name_alt');

        html::label('item_description', lang::translate('order_item_form_desc'));
        html::textarea('item_description');

        html::label('category', lang::translate('order_item_form_category'));

        $rows = orderCategory::getAll();     
        html::select('category', $rows, 'name', 'id');

        html::label('stock', lang::translate('order_item_form_stock'));
        html::text('stock');

        html::label('price', lang::translate('order_item_form_price'));
        html::text('price');

        html::label('weight', lang::translate('order_item_form_weight'));
        html::text('weight');

        html::label('file', lang::translate('order_item_form_upload_image'));
        html::file('file');
        
        html::hidden('submitted', 'submitted');

        html::label('submit', '');
        html::submit('submit', $button_text);
        
        html::formEnd();
        echo html::getStr();        
        return;
    }

    public static function updateItemControl ($frag = 3) {

        
        $id = URI::getInstance()->fragment($frag);
        templateView::includeModuleView('order/products', 'admin_menu', $vars = array ('id' => $id));
        template::setTitle(lang::translate('order_edit_html_title'));
        $cart = new order();
        if (isset($_POST['submit']) && $_POST['method'] == 'item_update'){
            $cart->validate();
            $cart->sanitize();
            if (empty($cart->errors)){
                $res = $cart->updateItem($id);
                session::setActionMessage(
                        lang::translate('order_action_message_product_updated'));
                    header("Location: /order/products/edit/$id");
            } else {
                view_form_errors($cart->errors);
            }
        }
        order::form('update');
    }


    // {{{ valiedate () method for validating insert and edit of items.
    public function validate(){
        if (isset($_POST['submit'])){
            if (empty($_POST['item_name'])){
                $this->errors[] = lang::translate('order_item_form_error_no_title');
            }
            if (!isset($_POST['price'])){
                $this->errors[] = lang::translate('order_item_form_error_no_valid_price');
            }
        }
        
        if (!is_numeric($_POST['price'])) {
            $this->errors[] = lang::translate('order_item_form_error_not_numeric');
        }
        
        if (!is_numeric($_POST['weight'])) {
            $this->errors[] = lang::translate('order_item_form_error_not_numeric');
        }
        
    }
    // }}}
    // {{{ validateOrderForm() 
    public function validateOrderForm (){
        $_POST = cos_htmlspecialchars($_POST);

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
    // }}}
    // {{{ sanitze()
    public function sanitize(){
        if (isset($_POST['submit'])){
            $_POST = html::specialEncode($_POST);
        }
    } 
    
    static function getItemModules() {
        return get_module_ini('order_item_modules');
    }
    
    /**
     * Adds a item
     * @return type 
     */
    public static function addItem(){
        $db = new db();
        
        db::$dbh->beginTransaction();
        $values = db::prepareToPost();
        $values['item_name'] = cos_sanitize_url($values['item_name']);
        $values['item_name_alt'] = cos_sanitize_url($values['item_name_alt']);
        $values['md5'] = md5(uniqid());
        
        $db->insert(self::$table, $values);
        $id = db::$dbh->lastInsertId();

        $res = self::updateImage($id);
        if (!$res) {
            error_log('error_image_scale');
            db::$dbh->rollBack();
            self::$errors = uploadBlob::$errors;
            return false;
        } else {
            db::$dbh->commit();
            return $id;
        }
    }

    static function updateImage ($id) {

        $order_image_size = get_module_ini('order_image_size');
        $order_image_size_thumb = get_module_ini('order_image_size_thumb');

        $options = array ('quality' => get_module_ini('order_image_quality'));
        if (is_uploaded_file($_FILES['file']['tmp_name'])) {
            $res = uploadBlob::scaleImageToBlob(
                'file', self::$table, 'file', $id, $order_image_size, null, $options);
            if (!$res) {
                self::$errors = uploadBlob::$errors;
                return false;
            }
            $res = uploadBlob::scaleImageToBlob(
                'file', self::$table, 'file_thumb', $id, $order_image_size_thumb, null, $options);
            
            if (!$res) {
                self::$errors = uploadBlob::$errors;
                return false;
            }
        }
        return true;
    }

    public static function getItemsInBlock (){
        $db = new db();
        $all_items = $db->selectAll('order_items', array ('id', 'item_name', 'item_name_alt'), 'stock > 0', null, null, 'item_order', true);
        return $all_items;
    }

    // }}}

    public function displayCheckout(){

        $order_items = order::getBasketItems();
        if (empty($order_items)){
            echo lang::translate('order_checkout_no_items_in_basket');
            return;
        }

        if (isset($_POST['submit'])){
            $this->validateOrderForm();
            if (!empty(order::$errors)){
                view_form_errors(order::$errors);
            } else {
                save_post('order_form');
                unset($_POST['submit']);
                $cookie = serialize($_POST);
                $res = setcookie(
                    'order_form_cookie',
                $cookie, get_module_ini('order_cookie_time') +time(), "/");
                header("Location: /order/confirm");
                die();
            }
        } else {            
            if (!load_post('order_form')) {
                if (isset($_COOKIE['order_form_cookie'])) {
                    $_POST = unserialize($_COOKIE['order_form_cookie']);
                    //$_POST = html::specialEncode($_POST);
                }
            }
        }
        templateView::includeModuleView('order', 'order_form');
    }
    // }}}
    // {{{
    public function process (){
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
        $res_invoice = mail_utf8($order_invoice_to, $subject, $message, $from, $order_reply_to);

        //setcookie ("order_items", "", time() - 3600, "/");
        self::clearBasketItems();
        header("Location: /order/done");
        die;
    }
    // }}}
        
    

    static function getCurrencySymbol () {
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
    static public function displayCart (){
        $db = new db();
        //$template = '';
        $all_items = $db->selectAll('order_items', null, null, null, null, 'item_order', true);
        templateView::includeModuleView('order', 'display_cart', $all_items);
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
            $int_options = array("options" => array("min_range"=>0 ));
            $get_id = filter_var($_GET['order_item'], FILTER_VALIDATE_INT, $int_options);
            
            $val['add_order'] = $items[$get_id]['add_order'];
            $val['selected'] = $items[$get_id];
        } else {
            $val['add_order'] = 1;
        }
        
        $url = "/order/item/$val[id]/";
        $url.= rawurlencode($val['item_name']);

        send_301_headers($url);
        
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
     * adds a item to basket. 
     * 
     * @param array $options array ('redirect' => '/location/to/redirect');
     */
    public function addToBasket ($options = null){        
        if (isset($_POST['add_order'])){
            echo $add_order = filter_var($_POST['add_order'], FILTER_VALIDATE_INT);
            $item_id = filter_var($_POST['item_id'], FILTER_VALIDATE_INT);
            
            
            $order_item = filter_var(@$_REQUEST['order_item'], FILTER_VALIDATE_INT);
            
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
                            if ($val === $_POST) {
                                $match = true;
                                break;
                            } 
                        }
                        
                        if ($match) {                           
                            if ($add_order <= 0) {
                                //unset ($order_items[$key]);
                                unset ($order_items[$order_item]);
                            } else {
                                $_POST['add_order'] = $add_order;
                                $order_items[$key] = $_POST;

                            }
                        } else {
                            if ($add_order <= 0) {
                                unset ($order_items[$order_item]);
                            } else {
                                $_POST['add_order'] = $add_order;
                                $order_items[] = $_POST;
                            }
                            
                            
                        }
                        
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
                }               
            }
        }
    }

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
    
    public static function clearBasketItems () {
        self::setBasketItems(array());       
    }


    public static function getBasketItems (){      
        if (!isset($_COOKIE['order_client_id'])){
            $id = md5(uniqid());
            $order_cookie_time = time() + get_module_ini('order_cookie_time');
            setcookie('order_client_id', $id, $order_cookie_time, '/');
            return array();
        }

        
        $order_items = cache::get('order_basket_items', $_COOKIE['order_client_id'], get_module_ini('order_cookie_time'));
        if (empty($order_items)) {
            $order_items = array();
        }
        return $order_items;
    }

    public static function getItem ($id){
        $db = new db();
        $item = $db->selectOne('order_items', 'id', $id);
        return $item;
    }

    public function updateItem($id){
        $db = new db();
        $values = db::prepareToPost();
        $values['item_name'] = cos_sanitize_url($values['item_name']);

        $values['md5'] = md5(uniqid());
        
        db::$dbh->beginTransaction();
        $db->update(self::$table, $values, $id);

        $res = self::updateImage($id);
        if (!$res) {
            db::$dbh->rollBack();
            return false;
        } else {
            db::$dbh->commit();
            return true;
        }
    }

    public function deleteItem($id){
        $db = new db();
        $res = $db->delete('order_items', 'id', $id);
        if ($res) {
            session::setActionMessage(
                lang::translate('order_product_action_message_product_deleted'));
            header("Location: /order/products/index");
        }
    }

    public static function displayQuickBasket (){

        $order_items = order::getBasketItems();
        $all_items = order::getItemsInBlock();

        $vars['order_items'] = order::getBasketItems();
        $vars['all_items'] = order::getItemsInBlock();

        templateView::includeModuleView('order', 'display_quick_basket', $vars);
        return;

    }


    public static function displayBasket (){
        $vars['order_items'] = order::getBasketItems();
        if (empty($vars['order_items'])){
            echo lang::translate('order_no_items_in_basket');
            return;
        }

        templateView::includeModuleView('order', 'display_basket', $vars);
        templateView::includeModuleView('order', 'display_checkout_submit');

    }

    public static function displayConfirm (){

        $order_items = order::getBasketItems();
        if (empty($order_items)){
            echo lang::translate('order_no_items_in_basket');
            return;
        }

        $vars['order_items'] = $order_items;
        load_post('order_form');

        templateView::includeModuleView('order', 'display_confirm_order', $vars);
        templateView::includeModuleView('order', 'confirm_form');
    }

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
}
