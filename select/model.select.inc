<?php

class orderSelect {
    
    /**
     *
     * @var string  $table the name of the db table we use  
     */
    public static $table = 'order_item_select';
    
    /**
     *
     * @var array $errors array for collecting errors
     */
    public static $errors = array ();
    
    /**
     * controller method usedin pages where we want to display the 
     * standard form and update selects connects to a item
     * @param int $frag part of the url we want to fetch the id of the item 
     */
    public static function updateSelectControl ($frag = 2)  {

        $item_id = URI::getInstance()->fragment($frag);
        if (!isset($item_id)) {
            self::$errors[] = lang::translate('order_select_need_item_id');
        }
        
        if (isset($_POST['method']) && $_POST['method'] == 'item_insert_select') {
            $_POST['options'] = trim(html::specialEncode($_POST['options']));
            if (strlen($_POST['options']) != 0) {
                $values = db::prepareToPost();
                $values['order_item_id'] = $item_id;

                $res = self::add($values);
                if ($res) {
                    session::setActionMessage(lang::translate('order_select_option_added_confirm'));
                    $redirect = "/order/edit/$item_id";
                    header("Location: $redirect");
                }
            }  
        } 
        
        if (@$_GET['method'] == 'item_delete_select') {
            self::delete($_GET['id']);
            session::setActionMessage(lang::translate('order_select_option_delete_confirm'));
            $redirect = "/order/edit/$item_id";
            header("Location: $redirect");
            
        }
        
        self::form($item_id);
    }
    
    /**
     * Not used. Not implemented. Maybe later
     * @return string   html::link 
     */
    public static function getItemMenu () {
        return html::createLink('/order/edit/', 'edit select');
    }
    
    /**
     * draws form for creating select lists / dropdowns for adding options
     * to a shopping cart item
     * 
     * @param int $item_id the item_id of the cart item to which we connect
     *                     the list 
     */
    public static function form($item_id) {
        
        html::$autoLoadTrigger = 'submit';
        html::init();
        html::formStart('order_item_form_select');
        html::legend(lang::translate('order_item_select_legend'));
        html::hidden('method', 'item_insert_select');
        
        html::label('title', lang::translate('order_select_form_title_field'));
        html::text('title');
        
        html::label('options', lang::translate('order_select_form_option_field'));
        html::text('options');
        
        html::label('submit', '');
        html::submit('submit', lang::translate('order_update'));        
        
        html::formEnd();       
        echo html::getStr();   

        $selects = self::getSelectsAsObject($item_id);
        echo templateView::includeModuleView('order', 'select_list_admin', $selects, 1);
        
    }
    
    /**
     * method for getting all select list as drop downs. 
     * see: views/select_list how they are displayed. 
     * 
     * @param type $item_id the cart item in reference
     * @param type $selected 
     */
    public static function getSelectListsAsDropDowns ($item_id, $selected = array()) {
        $obj = self::getSelectsAsObject($item_id, $selected);
        echo templateView::includeModuleView('order', 'select_list', $obj, 1);
    }
    
    /**
     * method for getting all select lists as hidden fields
     * see: views/select_list_hidden
     * @param int $item_id the cart item in reference
     * @param array $selected the values which should be selected 
     */
    public static function getSelectListAsHiddenFields ($item_id, $selected = array()) {
        $obj = self::getSelectsAsObject($item_id, $selected);
        echo templateView::includeModuleView('order', 'select_list_basket', $obj, 1);
    }
    
    /**
     * get selects list as rows from the database table
     * @param int $item_id the cart item in reference
     * @return array all select lists in reference as an array
     */
    public static function getSelects ($item_id) { 
        $db = new db();
        return $db->selectAll(self::$table, null, array('order_item_id' => $item_id));      
    }
    
    /**
     * get select lists as a simple object. 
     * @param int $item_id
     * @param array $selected
     * @return object $object with titles, options, and selected items.  
     */
    public static function getSelectsAsObject ($item_id, $selected = array()) { 
        $ary = array();
        $selects = self::getSelects($item_id);
  
        $obj = new stdClass;
        $obj->titles = $obj->options = $obj->ids = array ();
        $obj->selected = array();
        
        foreach ($selects as $key => $item) {        
            $obj->ids[] = $item['id'];
            $obj->titles[] = $item['title'];
            
            $obj->options[] = unserialize($item['options']);
            
            if (isset($selected[$item['title']])) {
                $val = $selected[$item['title']];
            } else {
                $val = 0;
            }
            $obj->selected[] = $val;
            
        }
        return $obj;       
    }
    
    
    /**
     * add a select list to db.
     * @param array $values
     * @return boolean  value from database operation  
     */
    public static function add ($values) {
        $db = new db();
        $options = explode (",", $values['options']);
        $ary = array();
        foreach ($options as $key => $val) {
            $ary[] = array('id' => $key, 'val' => trim($val));
        }
        $values['options'] = serialize($ary);
        return $db->insert(self::$table, $values);
    }
    
    public static function update() {
        
    }
    
    /**
     * method for delting a select item for database table. 
     * @param type $id
     * @return type 
     */
    public static function delete ($id) {
        $db = new db();
        return $db->delete(self::$table, 'id', $id);
        
    }
}