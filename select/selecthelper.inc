<?php

class selecthelper {
    
    public static function getSelectChilds ($item_id, $selected = array()) { 
        $db = new db();
        
        $row = $db->selectOne(self::$table, null, array('order_item_id' => $item_id));
        $q = new QBuilder();
        $q->setSelect(self::$table);
        $q->filter('option_id = ', $row['id']);
        $q->condition('AND');
        $q->filter('title !=', '');
        $row = $q->fetchSingle();
        

        $obj = new stdClass();
        $obj->mainChildSelects = $row;
        //if (isset( $selected )) {
        //    $obj->mainChildSelects['selected'] = 
        //}
               
        $parent_options = array ();
        
        $rows = $db->selectAll(self::$option_table, null, array( 'select_id' => $row['option_id']));                   
        
        $i= 1;
        foreach ($rows as $krey => $val) {
            $parent_options[$i] = $val;
            $i++;
        }
        
        $obj->parentOptions = $parent_options;        
        $obj->allChildOptions = array();
        
        $i = 1;
        foreach ($obj->parentOptions as $key => $val) {
            $obj->allChildOptions[$i] = $db->selectAll(self::$option_table, null, array( 'option_id' => $val['id']));            
            
            $i++;
        }        
        return $obj;
    }
    
    /**
     *
     * @var string  $table the name of the db table we use  
     */
    public static $table = 'order_item_select';
    public static $option_table = 'order_item_select_option';
    
    /**
     * get selects list as rows from the database table
     * @param int $item_id the cart item in reference
     * @return array all select lists in reference as an array
     */
    public static function getSelects ($item_id) { 
        $db = new db();        
        return $db->selectAll(self::$table, null, array('order_item_id' => $item_id, 'option_id' => '0'));      
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
        $obj->item_id = $item_id;
        $obj->titles = $obj->options = $obj->ids = array ();
        $obj->selected = $obj->selectedHuman = array();

        $id = 1;
        foreach ($selects as $item) {        
            $obj->ids[$id] = $item['id'];
            $obj->titles[$id] = $item['title'];
            $options = db::init()->select(self::$option_table, null, array ('select_id' => $item['id']));
            $obj->options[$id] = $options; 
            
            if (isset($selected['select'][$item['title']])) {
                $val = $selected['select'][$item['title']];                
            } else {
                $val = 0;
            }
            
            $obj->selected[$id] = $val;
            $row = db::init()->selectOne(
                    self::$option_table, null, $search = array(
                        'select_id' => $item['id'], 'value' => $val));

            $obj->selectedHuman[$id] = $row['title'];
            $id++;
        }
        //print_r($obj); die;
        return $obj;       
    }
    
    
    function getSingleParentSelect ($item_id) {
        $db = new db();
        return $db->selectOne(self::$table, null, array(
            'order_item_id' => $item_id,
            'option_id' => 0));
    }
    
    function getSingleChildSelect ($parent) {
        $q = new QBuilder();
        $q->setSelect(self::$table);
        $q->filter('option_id = ', $parent);
        $q->condition('AND');
        $q->filter('title !=', '');
        return $row = $q->fetchSingle();
    } 
    
    function getAllParentOptions () {
        $rows = $db->selectAll(self::$option_table, null, array( 'select_id' => $row['option_id']));                   
        
    }
    
    function getAllChildSelect () {
        
    }
    
    
}