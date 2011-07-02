<?php

/**
 * @ignore
 */
include_once "mySqlForm.php";
include_once "upload.php";

template::setInlineCss(_COS_PATH . '/modules/order/order.css');
template::setJs('/js/jquery.validate.js', 30);
template::setInlineJs(_COS_PATH . '/modules/order/order.js');

include_model('order/shipping');

// {{{ create_item_form
/**
 *
 * @param id    used when we update or delete
 */
function create_item_form($method, $id = null, $values = array()){
    $tf = new mySqlForm('order_items', array('id',  'item_name',   'item_name_alt', 'item_description', 'price', 'stock', 'weight', 'file'), $values);
    $tf->setLabels(array(
        'id' => 'Id is a hidden field',
        'item_name' => lang::translate('order_item_form_title'),
        'item_name_alt' => lang::translate('order_item_form_title_alt'),
        'item_description' => lang::translate('order_item_form_desc'),
        'stock' => lang::translate('order_item_form_stock'),
        'price' => lang::translate('order_item_form_price'),
        'weight' => lang::translate('order_item_form_weight'),
        'file' => lang::translate('order_item_form_upload_image'),
        )
    );

    if ($method == 'update'){
        $tf->setMethod($method, $id);
        $caption = lang::translate('order_item_form_edit_legend');
    } else if ($method== 'insert') {
        $tf->setMethod($method);
        $caption = lang::translate('order_item_form_insert_legend');
    } else {
        $tf->setMethod($method);
        $caption = lang::translate('order_item_form_delete_legend');
    }
    $tf->createForm('', 'post',  'test', '',
                       true,  $caption);
}

// }}}
class order  {
    public static $errors = array();
    static $options = array();
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
            //$_POST = cos_htmlentities($_POST);
        }
    } 
    // }}}
    // {{{ addItem
    public function addItem(){
        $options = array();

        $values = self::prepareToPost();
        $values['item_name'] = cos_sanitize_url($values['item_name']);
        $values['item_name_alt'] = cos_sanitize_url($values['item_name_alt']);
        if (!empty($_FILES['file']['tmp_name'])){


            $options['filename'] = 'file';
            $options['maxsize'] = 4000000;
            // scale tmp image to tmp image

            $order_image_size = get_module_ini('order_image_size');
            $this->scaleImage($_FILES['file']['tmp_name'], $_FILES['file']['tmp_name'], $order_image_size);

            $values['file'] = uploadBlob::getFP($options);
            $values['content_type'] = $_FILES['file']['type'];
            $bind = array('file' => PDO::PARAM_LOB);
            $res = $this->insert('order_items', $values, $bind);

            $last_insert_id = self::$dbh->lastInsertId();

            $order_image_size_thumb = get_module_ini('order_image_size_thumb');
            $this->scaleImage($_FILES['file']['tmp_name'], $_FILES['file']['tmp_name'], $order_image_size_thumb);

            $values = array();
            $values['file_thumb'] = uploadBlob::getFP($options);
            $bind = array('file_thumb' => PDO::PARAM_LOB);
            $res = $this->update('order_items', $values, $last_insert_id, $bind);

        } else {
            $res = $this->insert('order_items', $values);
        }
        if ($res) {
            session::setActionMessage(lang::translate('order_confirm_product_inserted'));
            header("Location: /order/cart");
        }
    }

    public static function getItemsInBlock (){
        $db = new db();
        //if (session::isAdmin()){
        //    $all_items = $db->selectAll('order_items', array ('id', 'item_name', 'item_name_alt'), null, null, null, 'item_order', true);
            //$all_items = $db->selectAll('order_items', array ('id', 'item_name', 'item_name_alt'));
        //} else {
            $all_items = $db->selectAll('order_items', array ('id', 'item_name', 'item_name_alt'), 'stock > 0', null, null, 'item_order', true);
            //$all_items = $db->selectAll('order_items', array ('id', 'item_name', 'item_name_alt'), 'stock > 0');
        //}
        return $all_items;
    }

    // }}}

    public function displayCheckout(){
        if (!isset($_COOKIE['order_items'])){
            print lang::translate('order_checkout_no_items_in_basket');
            return;
        }
        $order_items = order::getBasketItems();
        if (empty($order_items)){
            print lang::translate('order_checkout_no_items_in_basket');
            return;
        }

        if (isset($_POST['submit'])){
            $this->validateOrderForm();
            if (!empty(order::$errors)){
                view_form_errors(order::$errors);
            } else {
                save_post('order_form');
                header("Location: /order/confirm");
            die();

            }
        } else {
            load_post('order_form');
        }
        include_once _COS_PATH . '/modules/order/views/order_form.php';
    }
    // }}}
    // {{{
    public function process (){
        if (!isset($_COOKIE['order_items'])){
            print lang::translate('order_checkout_no_items_in_basket');
            return;
        }

        $subject = lang::translate('order_checkout_order_details');
        load_post('order_form');

        $from = get_main_ini('site_email');
        $order_reply_to = get_module_ini('order_reply_to');
        $order_invoice_to = get_module_ini('order_invoice_to');


        ob_start();

        order::displayOrderEmail();

        
        $message = ob_get_contents();

        ob_end_clean();

        $res_consumer = mail_utf8($_POST['email'], $subject, $message, $from, $order_reply_to);
        $res_invoice = mail_utf8($order_invoice_to, $subject, $message, $from, $order_reply_to);

        //if (get_module_ini('order_debug') == 0){
            setcookie ("order_items", "", time() - 3600, "/");
        //}
        header("Location: /order/done");
        die;
        // add to db
        //if ()){
            //db::$dbh->commit();
        //    return 1;
        //} else {
            //db::$dbh->rollBack();
        //    return 0;
        //}


    }
    // }}}

    static function getCurrencySymbol () {
        static $local = null;
        if (!isset($localeconv)){
            $local = localeconv();
        }
        return $currency = $local['int_curr_symbol'];
    }

    static function getWeightToCost($type, $weight) {
        $db = new db();

        

    }

    // {{{ displayCart
    public function displayCart (){
        $db = new db();
        $all_items = $db->selectAll('order_items', null, null, null, null, 'item_order', true);
        templateView::includeModuleView('order', 'display_cart', $all_items);
    }
    // }}}
    // {{{ displayItem ($id)
    public function displayItem ($id){
        if (isset($_POST['add_order'])){
            $add_order = filter_var($_POST['add_order'], FILTER_VALIDATE_INT);
        } else if (isset($_COOKIE['order_items'][$id])){
            $order_items = unserialize($_COOKIE['order_items']);
            if(isset($order_items[$id]) && $order_items[$id] != '0') {
                $add_order = $order_items[$id];
            } else {
                $add_order = 1;
            }
        } else {
            $add_order = 1;
        }
      
        $val = $this->getItem($id);
        $val['add_order'] = $add_order;

        if (empty($val)){
            header ("HTTP/1.1 301 Moved Permanently");
            header ("Location: /order/cart");
        }

        $url = "/order/item/$val[id]/";
        $url.= rawurlencode($val['item_name']);

        if ($_SERVER['REQUEST_URI'] != $url) {
            header("HTTP/1.1 301 Moved Permanently");
            $url = "/order/item/$val[id]/";
            $url.= rawurlencode($val['item_name']);
            header("Location: $url");
        }
        
        $title = lang::translate('order_view_single_product');
        $title.= MENU_SUB_SEPARATOR_SEC;
        $title.= $val['item_name'];
        template::setTitle(html::specialEncode($title));

        $meta_desc =
        cos_remove_extra_ws(html::specialEncode(substr2($val['item_description'], 155, 3, false)));
        template::setMeta(array('description' => $meta_desc));

        $val['item_description'] = get_filtered_content('simple', $val['item_description']);

        print templateView::includeModuleView('order', 'display_item', $val);
    }
    // }}}
    // {{{ setBasketCookie ($order_items = array())
    public static function setBasketCookie ($order_items = array()) {
        $order_items = serialize($order_items);
        $order_cookie_time = time() + get_module_ini('order_cookie_time');
        setcookie('order_items', $order_items, $order_cookie_time, '/');
    }
    // }}}
    // {{{ addToBasket()
    public function addToBasket ($options = null){
        //$item_id = URI::getInstance()->fragment(2);
        
        if (isset($_POST['add_order'])){
            $add_order = filter_var($_POST['add_order'], FILTER_VALIDATE_INT);
            $item_id = $_POST['item_id'];
            $item_id = filter_var($item_id, FILTER_VALIDATE_INT);

            // update cart
            if (is_int($add_order) && is_int($item_id)){
                // update cookie
                if (@!empty($_COOKIE['order_items'])){
                    $order_items = unserialize($_COOKIE['order_items']);
                    $order_items[$item_id] = $add_order;
                    self::setBasketCookie($order_items);
                } else {
                    $order_items = array ();
                    $order_items[$item_id] = $add_order;
                    self::setBasketCookie($order_items);
                }
                if (isset($options['redirect'])){
                    $header = "Location: $options[redirect]";
                    header ($header);
                } else {
                    header ("Location: /order/basket");
                }               
            }
        }
    }
    // }}} 
    // {{{ getBasketItems ()
    public static function getBasketItems (){
        if (!isset($_COOKIE['order_items'])){
            return array();
        }
        $order_items = unserialize($_COOKIE['order_items']);
        if (!is_array($order_items)) self::setBasketCookie ();

        foreach ($order_items as $key => $val){
            if ($val == '0' || $val == '') unset($order_items[$key]);
            if ($key == '0' || $key == '') unset($order_items[$key]);
        }

        if (empty($order_items)){
            return array();
        }
        return $order_items;
    }
    // }}}
    
    // {{{ getItem($id)
    public function getItem ($id){
        $db = new db();
        $item = $db->selectOne('order_items', 'id', $id);
        return $item;
    }
    // }}}
    // {{{ updateItem($id)
    public function updateItem($id){
        $values = self::prepareToPost();
        $values['item_name'] = cos_sanitize_url($values['item_name']);
        $values['item_name_alt'] = cos_sanitize_url($values['item_name_alt']);
        if (!empty($_FILES['file']['tmp_name'])){
            $options['filename'] = 'file';
            $options['maxsize'] = 4000000;
            
            $order_image_size = get_module_ini('order_image_size');
            $this->scaleImage($_FILES['file']['tmp_name'], $_FILES['file']['tmp_name'], $order_image_size);

            $values['file'] = uploadBlob::getFP($options);
            $values['content_type'] = $_FILES['file']['type'];

            $bind = array('file' => PDO::PARAM_LOB);
            $res = $this->update('order_items', $values, $id, $bind);
            
            $order_image_size_thumb = get_module_ini('order_image_size_thumb');
            $this->scaleImage($_FILES['file']['tmp_name'], $_FILES['file']['tmp_name'], $order_image_size_thumb);

            //$values = array();
            $values =   array('file_thumb' => uploadBlob::getFP($options));
            $bind =     array('file_thumb' => PDO::PARAM_LOB);
            $res = $this->update('order_items', $values, $id, $bind);
        } else {
            $res = $this->update('order_items', $values, $id);
        }
        if ($res) {
            session::setActionMessage(
                lang::translate('order_action_message_product_updated'));
            header("Location: /order/cart");
        }
    }
    // }}}
    // {{{ deleteItem($id)
    public function deleteItem($id){
        $res = $this->delete('order_items', 'id', $id);
        if ($res) {
            session::setActionMessage(
                lang::translate('order_product_action_message_product_deleted'));
            header("Location: /order/cart");
        }
    }
    // }}}
    // {{{ scaleImage 
    private function scaleImage ($image, $thumb, $length){
        require_once 'Image/Transform.php';

        //create transform driver object
        $it = Image_Transform::factory('GD');
        if (PEAR::isError($it)) {
            die($it->getMessage());
        }

        //load the original file
        $ret = $it->load($image);
        if (PEAR::isError($ret)) {
            die($ret->getMessage());
        }

        //scale
        $ret = $it->scaleByLength($length);
        if (PEAR::isError($ret)) {
            die($ret->getMessage());
        }

        //save it into a different file
        $ret = $it->save($thumb);
        if (PEAR::isError($ret)) {
            die($ret->getMessage());
        }
    }
    // }}}
        // {{{ displayBasket ()
    public static function displayQuickBasket (){

        $order_items = order::getBasketItems();
        $all_items = order::getItemsInBlock();

        $vars['order_items'] = order::getBasketItems();
        $vars['all_items'] = order::getItemsInBlock();

        templateView::includeModuleView('order', 'display_quick_basket', $vars);
        return;

    }

        // {{{ displayBasket ()
    public static function displayBasket (){
        if (empty($_COOKIE['order_items'])){
            print lang::translate('order_no_items_in_basket');
            return;
        }

        $vars['order_items'] = order::getBasketItems();
        if (empty($vars['order_items'])){
            print lang::translate('order_no_items_in_basket');
            return;
        }

        templateView::includeModuleView('order', 'display_basket', $vars);

    }
    // }}}
        // {{{ displayConfirmOrder ()
    public static function displayConfirm (){
        if (!isset($_COOKIE['order_items'])){
            print lang::translate('order_no_items_in_basket');
            return;
        }
        $order_items = order::getBasketItems();
        if (empty($order_items)){
            print lang::translate('order_no_items_in_basket');
            return;
        }

        $vars['order_items'] = $order_items;

        templateView::includeModuleView('order', 'display_confirm_order', $vars);

    }
    // }}}
        // {{{ displayConfirmOrder ()
    public static function displayOrderEmail (){

        if (!isset($_COOKIE['order_items'])){
            return 0;
        }
        $order_items = order::getBasketItems();

        if (empty($order_items)){
            print lang::translate('order_no_items_in_basket');
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
