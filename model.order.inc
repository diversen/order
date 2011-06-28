<?php

/**
 * @ignore
 */
include_once "mySqlForm.php";
include_once "upload.php";

template::setInlineCss(_COS_PATH . '/modules/order/order.css');
template::setJs('/js/jquery.validate.js', 30);
template::setInlineJs(_COS_PATH . '/modules/order/order.js');



// {{{ create_item_form
/**
 *
 * @param id    used when we update or delete
 */
function create_item_form($method, $id = null, $values = array()){
    $tf = new mySqlForm('order_items', array('id',  'item_name',   'item_name_alt', 'item_description', 'price', 'stock', 'weight', 'file'), $values);
    $tf->setLabels(array(
        'id' => 'Id is a hidden field',
        'item_name' => lang::translate('Enter title of cart item'),
        'item_name_alt' => lang::translate('item_name_alt'),
        'item_description' => lang::translate('Enter description of cart_item'),
        'stock' => lang::translate('Stock'),
        'price' => lang::translate('Price'),
        'weight' => lang::translate('order_item_weight'),
        'file' => lang::translate('Upload item image'),
        )
    );

    if ($method == 'update'){
        $tf->setMethod($method, $id);
        $caption = lang::translate('Edit Product');
    } else if ($method== 'insert') {
        $tf->setMethod($method);
        $caption = lang::translate('Add Product');
    } else {
        $tf->setMethod($method);
        $caption = lang::translate('Delete Product');
    }
    $tf->createForm('', 'post',  'test', '',
                       true,  $caption);
}

// }}}
class order extends db {
    public static $errors = array();
    static $options = array();
    // {{{ valiedate () method for validating insert and edit of items.
    public function validate(){
        if (isset($_POST['submit'])){
            if (empty($_POST['item_name'])){
                $this->errors[] = lang::translate('No Item');
            }
            if (!isset($_POST['price'])){
                $this->errors[] = lang::translate('No valid Price');
            }
        }
    }
    // }}}
    // {{{ validateOrderForm() 
    public function validateOrderForm (){
        $_POST = cos_htmlspecialchars($_POST);

        if (strlen($_POST['name']) < 3){
            self::$errors['name'] = lang::translate('error_name');
        }

        if (strlen($_POST['adresse']) < 3){
            self::$errors['adresse'] = lang::translate('error_adresse');
        }
        if (strlen($_POST['city']) < 1){
            self::$errors['city'] = lang::translate('error_city');
        }

        if(!preg_match("#^[0-9]{4}$#", $_POST['postal_code'])) {
            self::$errors['zip_code'] = lang::translate('error_zip_code');
        }

        if (!filter_var($_POST['email'], FILTER_VALIDATE_EMAIL)){
            self::$errors['email'] = lang::translate('error_email');
        }

        if (isset($_POST['checkme'])){
            if (strlen($_POST['diff_name']) < 3){
                self::$errors['diff_name'] = lang::translate('error_diff_name');
            }

            if (strlen($_POST['diff_adresse']) < 3){
                self::$errors['diff_adresse'] = lang::translate('error_diff_adresse');
            }
            if (strlen($_POST['diff_city']) < 1){
                self::$errors['diff_city'] = lang::translate('diff_error_city');
            }

            if(!preg_match("#^[0-9]{4}$#", $_POST['diff_postal_code'])) {
                self::$errors['diff_zip_code'] = lang::translate('error_diff_zip_code');
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

            $cart_image_size = get_module_ini('cart_image_size');
            $this->scaleImage($_FILES['file']['tmp_name'], $_FILES['file']['tmp_name'], $cart_image_size);

            $values['file'] = uploadBlob::getFP($options);
            $values['content_type'] = $_FILES['file']['type'];
            $bind = array('file' => PDO::PARAM_LOB);
            $res = $this->insert('order_items', $values, $bind);

            $last_insert_id = self::$dbh->lastInsertId();

            $cart_image_size_thumb = get_module_ini('cart_image_size_thumb');
            $this->scaleImage($_FILES['file']['tmp_name'], $_FILES['file']['tmp_name'], $cart_image_size_thumb);

            $values = array();
            $values['file_thumb'] = uploadBlob::getFP($options);
            $bind = array('file_thumb' => PDO::PARAM_LOB);
            $res = $this->update('order_items', $values, $last_insert_id, $bind);

        } else {
            $res = $this->insert('order_items', $values);
        }
        if ($res) {
            session::setActionMessage(lang::translate('Product Inserted'));
            header("Location: /order/cart");
        }
    }

    public static function getItemsInBlock (){
        $db = new db();
        if (session::isAdmin()){
            $all_items = $db->selectAll('order_items', array ('id', 'item_name', 'item_name_alt'), null, null, null, 'weight', true);
            //$all_items = $db->selectAll('order_items', array ('id', 'item_name', 'item_name_alt'));
        } else {
            $all_items = $db->selectAll('order_items', array ('id', 'item_name', 'item_name_alt'), 'stock > 0', null, null, 'weight', true);
            //$all_items = $db->selectAll('order_items', array ('id', 'item_name', 'item_name_alt'), 'stock > 0');
        }
        return $all_items;
    }

    // }}}

    public function checkout(){
        if (!isset($_COOKIE['order_items'])){
            print lang::translate('No Items in basket');
            return;
        }
        $order_items = order::getBasketItems();
        if (empty($order_items)){
            print lang::translate('No Items in basket');
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
            print lang::translate('No Items in basket');
            return;
        }

        $subject = lang::translate("order_details");

        // load $_POST values
        load_post('order_form');

        // from
        $from = get_main_ini('site_email');

        // reply-to and invoice email
        $reply_to = get_module_ini('reply_to');
        $invoice_to = get_module_ini('invoice_to');

        // create email message
        ob_start();

        // print order details
        orderView::detailsEmail();

        // print email
        include _COS_PATH . "/modules/order/views/confirm_form_email.php";

        echo "\n\n";
        echo lang::translate('invoice_email_message');

        echo lang::translate('cheers') . " $_SERVER[SERVER_NAME]";
        // flush message
        $message = ob_get_contents();

        ob_end_clean();

        $res_consumer = mail_utf8($_POST['email'], $subject, $message, $from, $reply_to);
        $res_invoice = mail_utf8($invoice_to, $subject, $message, $from, $reply_to);

        if (get_module_ini('debug') == 0){
            setcookie ("order_items", "", time() - 3600, "/");
        }
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

    function getCurrencySymbol () {
        static $local = null;
        if (!isset($localeconv)){
            $local = localeconv();
        }
        return $currency = $local['int_curr_symbol'];
    }

    // {{{ displayCart
    public function displayCart (){

        $local = localeconv();
            /*print_r($local); */
                $currency = $local['int_curr_symbol'];
        //$this->select('order_items', null, array('stock'))
        //$this->displayItemsInBlock();
        if (session::isAdmin()){
            $all_items = $this->selectAll('order_items', null, null, null, null, 'weight', true);
            //$all_items = $this->selectAll('order_items');
        } else {
            //$all_items = $this->selectAll('order_items', null, 'stock > 0');
            $all_items = $this->selectAll('order_items', null, 'stock > 0', null, null, 'weight', true);
        }
        //$all_items = $this->selectAll('order_items');
        print "<table class = \"order_cart\">\n";
        $i = 0;
        print "<tr>\n";

        
        foreach ($all_items as $key => $val){            
            print "<td>";

            $options = array ();
            $options['alt'] = $val['item_name_alt'];
            $options['width'] = get_module_ini('cart_image_size_thumb');
            
            if (!empty($val['file'])){
                print create_image_link("/order/item/$val[id]/" . rawurlencode($val['item_name']), "/order/download/$val[id]", $options);
            }
            print "</td>\n";
            print "<td>\n";
            //print "<br />\n";
            print create_link("/order/item/$val[id]/" . rawurlencode($val['item_name']), $val['item_name'])  . "<br />";
            //print substr2($val['item_description'], 50);
            print "<br />";
            print
                //lang::translate('Price') . ' ' .
                //lang::translate('price_per_unit') . ' ' .
                
                $this->getCurrencySymbol() . ' ' .
                $val['price'] . ',-' .
                "<br />\n";

            
            if (session::isAdmin()){
                print $link = create_link("/order/edit/$val[id]", lang::translate('Edit'));
                print " | " . $link = create_link("/order/delete/$val[id]", lang::translate('Delete'));
                if ($val['stock'] == 0){
                    print "<div id=\"form_error\">". lang::translate('out_of_stock') . "</div>";
                }
            }
            print "</td>\n";
            $i++;
            $t = $i % 2;
            if (!$t){
                print "</tr><tr>\n";
                $i = 0;
            }

        }
        print "</tr>\n";
        print "<table>\n";
    }

    // }}}


    // {{{ displayItem ($id)
    public function displayItem ($id){
        if (isset($_POST['add_order'])){
            $add_order = filter_var($_POST['add_order'], FILTER_VALIDATE_INT);
        } else if (isset($_COOKIE['order_items'][$id])){
            $order_items = unserialize($_COOKIE['order_items']);
            if(isset($order_items[$id]) && $order_items[$id] != 0) {
                $add_order = $order_items[$id];
            } else {
                $add_order = 1;
            }
        } else {
            $add_order = 1;
        }

       
        $val = $this->getItem($id);

        if (empty($val)){
            header ("HTTP/1.1 301 Moved Permanently");
            header ("Location: /order/cart");
        }

        $url = "/order/item/$val[id]/" . rawurlencode($val['item_name']);
        if ($_SERVER['REQUEST_URI'] != $url) {
            header("HTTP/1.1 301 Moved Permanently");
            //$url = contentArticle::getArticleUrl($article_row['id'], rawurlencode($article_row['title']));
            //$url = html::getUrl($url);
            $url = "/order/item/$val[id]/" . rawurlencode($val['item_name']);
            header("Location: $url");
        }
        
        $title = lang::translate('View Product') . " :: " . $val['item_name'];
        template::setTitle(html::specialEncode($title));

        $meta_desc = cos_remove_extra_ws(html::specialEncode(substr2($val['item_description'], 155, 3, false)));
        template::setMeta(array('description' => $meta_desc));


        //include_once 'modules/filters_default/simple.php';

        $val['item_description'] = get_filtered_content('simple', $val['item_description']);


        //print "<hr id=\"thick_hr\" />";
        print "<table class=\"order_cart\">";
        print "<tr><td colspan=2>\n";
        print $val['item_name'] . " ";
        print '(' . 
            lang::translate('Price') . ' ' .         
            lang::translate('locale.amount') . ' ' .
            $val['price'] . ')';
        print "</td></tr>\n";
        print "<tr><td colspan=2>\n";
        print "<form name=\"view_item\" method =\"post\">\n";
        print lang::translate('enter_amount') . " <input id=\"order_amount\" maxlength=\"2\" name=\"add_order\" align=\"left\" size=\"2\" value=\"$add_order\" />\n";
        print "<input type=\"hidden\" name=\"item_id\" value=\"$id\" />\n";
        print "<input type =\"submit\" name = \"order_submit\" value=\"" . lang::translate('Update Cart') . "\" /> ";

        $total = $val['price'] * $add_order;
        print
            lang::translate('Price') . ': ' .
            $total . ' ' .
            lang::translate('locale.amount');
        print "</form>\n";
        print "</td></tr>";
        print "<tr><td>\n";

        $options = array();
        $options['alt'] = $val['item_name_alt'];
        $options['width'] = get_module_ini('cart_image_size');

        if (!empty($val['file'])){
          print $link = create_image_link("/order/item/$val[id]/" . rawurlencode($val['item_name']), "/order/download/$val[id]/full", $options);
        }
        
        print "</td><td>\n";
        print $val['item_description'];

        //print $link = create_link('/order/item', $val['item_name']);
        if (isset($_SESSION['admin'])){
            print "<br />" . $link = create_link("/order/edit/$val[id]", lang::translate('Edit'));
            print MENU_SUB_SEPARATOR . $link = create_link("/order/delete/$val[id]", lang::translate('Delete'));
        }
        print "</td></tr>\n";
        print "</table>\n";
    }
    // }}}
    // {{{ setBasketCookie ($order_items = array())
    public static function setBasketCookie ($order_items = array()) {
        $order_items = serialize($order_items);
        $cookie_time = time() + get_module_ini('cookie_time');
        setcookie('order_items', $order_items, $cookie_time, '/');
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
            if ($val == 0 || $val == '') unset($order_items[$key]);
            if ($key == 0 || $key == '') unset($order_items[$key]);
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
            
            $cart_image_size = get_module_ini('cart_image_size');
            $this->scaleImage($_FILES['file']['tmp_name'], $_FILES['file']['tmp_name'], $cart_image_size);

            $values['file'] = uploadBlob::getFP($options);
            $values['content_type'] = $_FILES['file']['type'];

            $bind = array('file' => PDO::PARAM_LOB);
            $res = $this->update('order_items', $values, $id, $bind);
            
            $cart_image_size_thumb = get_module_ini('cart_image_size_thumb');
            $this->scaleImage($_FILES['file']['tmp_name'], $_FILES['file']['tmp_name'], $cart_image_size_thumb);

            //$values = array();
            $values =   array('file_thumb' => uploadBlob::getFP($options));
            $bind =     array('file_thumb' => PDO::PARAM_LOB);
            $res = $this->update('order_items', $values, $id, $bind);
        } else {
            $res = $this->update('order_items', $values, $id);
        }
        if ($res) {
            session::setActionMessage(lang::translate('Product Updated'));
            header("Location: /order/cart");
        }
    }
    // }}}
    // {{{ deleteItem($id)
    public function deleteItem($id){
        $res = $this->delete('order_items', 'id', $id);
        if ($res) {
            session::setActionMessage(lang::translate('Product Deleted'));
            header("Location: /order/cart");
        }
    }
    // }}}
    // {{{ viewConfirm()
    public function viewConfirm (){
        $file = _COS_PATH . "/modules/order/views/view_confirm.php";
        print simple_template($file);        
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
}
