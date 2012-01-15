<?php

/**
 * File containing orderProducts class
 * @package order
 */
include_model ("order");


/**
 * orderProducts class. Used for insertingdelting and updating products. 
 * @package order
 */
class orderProducts extends order {
    
    /**
     *
     * @param type $method insert, update or delete
     * @param type $frag fragment id of url to fetch item id from.
     * @return type 
     */
    public static function form($method, $frag = 3){

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
        html::textareaMed('item_description');

        html::label('category', lang::translate('order_item_form_category'));

        $rows = orderCategory::getAll();     
        html::select('category', $rows, 'name', 'id');

        html::label('stock', lang::translate('order_item_form_stock'));
        html::text('stock');

        html::label('price', lang::translate('order_item_form_price'));
        html::text('price');

        html::label('weight', lang::translate('order_item_form_weight'));
        html::text('weight');
        
        html::hidden('submitted', 'submitted');

        html::label('submit', '');
        html::submit('submit', $button_text);
        
        html::formEnd();
        echo html::getStr();        
        return;
    }

    /**
     * method for displaying update item form
     * @param type $frag the URL fragement to fetch item from
     */
    public function updateItemControl ($frag = 3) {
       
        $id = URI::getInstance()->fragment($frag);
        templateView::includeModuleView('order/products', 'admin_menu', $vars = array ('id' => $id));
        template::setTitle(lang::translate('order_edit_html_title'));

        if (isset($_POST['submit']) && $_POST['method'] == 'item_update'){
            $this->validate();
            $this->sanitize();
            if (empty($this->errors)){
                $res = $this->updateItem($id);
                if ($res) {
                    session::setActionMessage(
                            lang::translate('order_action_message_product_updated'));
                        header("Location: /order/products/edit/$id");
                } else {
                    view_form_errors($thyis->errors);
                }
            } else {
                view_form_errors($this->errors);
            }
        }
        $this->form('update');
    }


    /**
     * method for validating on insert or update. 
     */
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

    /**
     * method for displaying a sorting table of all items. 
     */
    public function displaySortItems(){
        
        include_module ('jquerysort');
        $options = array ();
        $options['table'] = self::$table;
        
        $options['field'] = 'item_order';
        $options['title'] = 'item_name';

        jquerysort::setOptions($options);
        jquerysort::setJs();
        echo jquerysort::getHTML();
    }
    
    /**
     * methodf for displaying a form for adding an item. 
     * @return type 
     */
    public function addControl () {
        if (!session::checkAccessControl('order_allow')){
            return;
        }
        
        template::setTitle(lang::translate('order_add_product_html_title'));
        //$cart = new order ();
        if (isset($_POST['submit'])){
            $this->validate();
            $this->sanitize();
            if (empty($this->errors)){
                $id = $this->addItem();
                if ($id) {
                    session::setActionMessage(lang::translate('order_confirm_product_inserted'));
                    header("Location: /order/products/edit/$id");
                } else {
                    view_form_errors($cart->errors);
                    $message = "Could not add product item in: " . __FILE__;
                    cos_error_log($message);
                }
            } else {
                view_form_errors($cart->errors);
            }    
        }

        $this->form('insert');
    }
    
    /**
     * method for updating an item
     * @param int $id id of the item to update. 
     * @return boolean $res boolean true on success and false on failure- 
     */
    public function updateItem($id){
        $db = new db();
        $values = db::prepareToPost();
        $values['item_name'] = strings::sanitizeUrlSimple($values['item_name']);

        $values['md5'] = md5(uniqid());
        db::$dbh->beginTransaction();
        $db->update(self::$table, $values, $id);
        db::$dbh->commit();
        return true;
    }

    /**
     * method for delting an item. 
     * @param type $id 
     */
    public function deleteItem($id){
        $db = new db();
        $res = $db->delete('order_items', 'id', $id);
        if ($res) {
            session::setActionMessage(
                lang::translate('order_product_action_message_product_deleted'));
            header("Location: /order/products/index");
        }
    }
    
        
    /**
     * Adds a product item. 
     * item_name and item_name_alt are sanitized  for safe display in html. 
     * @return int $id id of the inserted item. 
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
        db::$dbh->commit();
        return $id;
    }
}
