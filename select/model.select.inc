<?php

class orderSelect {
    
    public static $table = 'order_item_select';
    public static $errors = array ();
    
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
        self::form($item_id);
    }
    
    
    public static function getItemMenu () {
        return html::createLink('/order/edit/', 'edit select');
    }
    

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
        
        $selects = self::getSelects($item_id);
        
        echo html::getStr();   
        
        $rows = self::getSelects($item_id);
        echo templateView::includeModuleView('order', 'select_list', $rows, 1);
        
    }
    
    public static function getSelects ($item_id) { 
        $db = new db();
        return $db->selectAll(self::$table, null, array('order_item_id' => $item_id));      
    }
    

    public static function add ($values) {
        $db = new db();
        return $db->insert(self::$table, $values);
    }
    
    public static function update() {
        
    }
    
    public static function delete () {
        
    }
}