<?php

include_once "selecthelper.inc";
//template::setJs('/js/jquery.chained.js');
class orderSelect {
    
    /**
     *
     * @var string  $table the name of the db table we use  
     */
    public static $table = 'order_item_select';
    public static $option_table = 'order_item_select_option';
    
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
    public static function updateSelectControl ($item_frag = 3, $select_frag = 4 )  {

        $item_id = URI::getInstance()->fragment($item_frag);
        $select_id = URI::getInstance()->fragment($select_frag);
        
        view::includeModuleView('order/products', 'admin_menu', array('id' => $item_id));
        if (!isset($item_id)) {
            self::$errors[] = lang::translate('order_select_need_item_id');
        }
        
        if (isset($_POST['method']) && $_POST['method'] == 'item_insert_select') {
            $_POST['options'] = trim(html::specialEncode($_POST['options']));
            if (strlen($_POST['options']) != 0) {
                $values = db::prepareToPost();
                $values['order_item_id'] = $item_id;

                $res = self::update($values, $select_id);
                if ($res) {
                    session::setActionMessage(lang::translate('order_select_option_added_confirm'));
                    $redirect = "/order/select/index/$item_id";
                    header("Location: $redirect");
                }
            }  
        }
        
            
        self::updateForm($item_id, $select_id);
    }
    
    /**
     * controller method usedin pages where we want to display the 
     * standard form and update selects connects to a item
     * @param int $frag part of the url we want to fetch the id of the item 
     */
    public static function indexSelectControl ($frag = 3)  {

        $item_id = URI::getInstance()->fragment($frag);
        view::includeModuleView('order/products', 'admin_menu', array('id' => $item_id));
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
                    $redirect = "/order/select/index/$item_id";
                    header("Location: $redirect");
                }
            }  
        }
        
        if (@$_GET['method'] == 'item_delete_select') {
            self::delete($_GET['id']);
            session::setActionMessage(lang::translate('order_select_option_delete_confirm'));
            $redirect = "/order/select/index/$item_id";
            header("Location: $redirect");
            
        }       
        self::form($item_id);
    }
    
    static function itemEditMenu ($id) {
        return html::createLink(
                "/order/select/index/$id", 
                lang::translate('order_select_edit_menu'));
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
        self::mainFormBaseFields();
        echo html::getStr();   

        $selects = self::getSelectsAsObject($item_id);
        echo view::includeModuleView('order', 'select/select_list_admin', $selects, 1);
        
    }
    
    static function mainFormBaseFields () {
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
    }
    
    /*
    static function formReference ($item_id, $select_id) {
        
        templateView::includeModuleView('order/products', 'admin_menu', array('id' => $item_id));
        $base = self::getSelectBase($select_id);
        html::formStart('order_select_add_reference');
        html::legend("opret underfelt til: " . $base['title']);
        html::label('title', 'Enter title');
        html::text('title');
         
        $options = self::getSelectListAsHiddenFields($select_id);
        //print_r($options);
        $rows = self::getSelectOptions($select_id);
        //print_r($rows);
        foreach ($rows as $key => $val) {
            html::label($val['id'], "Options for: $val[title]");
            html::text($val['id']);
        }
        html::submit('submit', 'submit');
        html::formEnd();
        echo html::getStr();
    }*/
   
    /*
    static function addReferenceControl () {
        $select_id = URI::$fragments[4];
        $item_id = URI::$fragments[3];
               
        if (isset($_POST['submit'])) {
            self::validateAddReference();
            if (empty (self::$erros)) {
                $res = self::addReferences($item_id, $select_id);
                if ($res) {
                    session::setActionMessage('Reference added');
                    header ($_SERVER['REQUEST_URI']);
                } else {
                    die ('argh');
                }
            }            
        }
        self::formReference ($item_id, $select_id);
       
    }*/
    /*
    
    function addReferences ($order_item_id, $option_id) {
        $db = new db();
        $values = db::prepareToPost();
        $title = $values['title']; unset($values['title']);

        foreach ($values as $key => $val) {
            $ary = array ();
            $ary['options'] = $val;
            $ary['order_item_id'] = $order_item_id;
            $ary['option_id'] = $option_id;
            $ary['title'] = $title;
            self::add($ary, $key, array('mulitple' => true));
        }
        return 1;
    }*/
    
    /*
    static function validateAddReference () {
        
    }*/
    
    public static function getSelectOptions ($select_id) { 
        return db::init()->selectAll(self::$option_table, null, array ('select_id' => $select_id));
    }
    
    static function getSelectAsString ($values) {

        $str = '';
        $x = count($values);
        foreach($values as $key => $val) {
            $str.= $val['title'];
            $x--; if ($x) $str.= ", ";
        }
        return $str;
    }
    
    static function getSelectBase($select_id) {
        return db::init()->selectOne(self::$table, 'id', $select_id);
    }
    
    static function updateForm ($item_id, $select_id) {
        
        $row = self::getSelectBase ($select_id);
        $rows = self::getSelectSingle($select_id);
        $values['title'] = $row['title'];
        $values['options'] = self::getSelectAsString($rows);

        html::$autoLoadTrigger = 'submit';
        html::init($values);
        
        self::mainFormBaseFields();
        echo html::getStr();  
    }
    
    /**
     * add a select list to db.
     * @param array $values
     * @return boolean  value from database operation  
     */
    public static function add ($values, $option_id = null, $options = array()) {
        
        static $check = null;
        static $i = 1;
        $db = new db();
        $options = explode (",", $values['options']);
        $ary = array();
        
        db::$dbh->beginTransaction();
        unset($values['options']);
        if (isset($check)) {
            $values['title'] ='';
        } else {
            $check = 1;
        }
        
        $db->insert(self::$table, $values);
            $last_insert_id = db::$dbh->lastInsertId();
            $check = 1;


        foreach ($options as $key => $val) {
            $ary = array();
            if (isset($option_id)) {
                $ary['option_id'] = $option_id;
            }
            $ary['value'] = $i;
            $ary['select_id'] = $last_insert_id;
            $ary['title'] = trim($val);
            $db->insert(self::$option_table, $ary);
            $i++;
        }
        
        return db::$dbh->commit();        
    }
    
    public static function update($values, $select_id) {
        $db = new db();
        
        db::$dbh->beginTransaction();
        $options = explode (",", $values['options']);

        $db->update(self::$table, array('title' => $values['title']), $select_id); 
        
        $rows = $db->selectAll(self::$option_table, null, array ('select_id' => $select_id));
        
        /*
        print_r($rows);
        print_r($_POST);
        die; */
        //die;
        $db->delete(self::$option_table, 'select_id', $select_id);
        
        $ary = array();
        $i = 1;
        foreach ($options as $key => $val) {
            $ary = array(
                'title' => trim($val), 'value' => $i, 'select_id' => $select_id);
            $db->insert(self::$option_table, $ary);
            $i++;
        }
        //$values['options'] = serialize($ary);
        //$db->update(self::$table, $values, $id);
        return db::$dbh->commit();
    }
    
    /**
     * method for delting a select item for database table. 
     * @param type $id
     * @return type 
     */
    public static function delete ($id) {

        $db = new db();
        
        // find childs if any. 
        $rows = $db->selectAll(self::$table, null, array ('id' => $id));

        //print_r($rows); die;
        $db->delete(self::$table, 'id', $id);
        foreach ($rows as $key => $val) {
            $db->delete(self::$table, 'id', $val['id']);
        }
        
    }
    /**
     * method for getting all select list as drop downs. 
     * see: views/select/select_list how they are displayed. 
     * 
     * @param type $item_id the cart item in reference
     * @param type $selected 
     */
    public static function getSelectListsAsDropDowns ($item_id, $selected = array()) {
        $obj = self::getSelectsAsObject($item_id, $selected);
        echo view::includeModuleView('order', 'select/select_list', $obj, 1);
        /*
        $childs = orderSelect::getSelectChilds($item_id, $selected);
        if (!empty($childs->allChildOptions)) {
            echo templateView::includeModuleView('order', 'select/select_list_childs', $childs, 1);
        }*/
    }
    
    /**
     * method for getting all select lists as hidden fields
     * see: views/select/select_list_hidden
     * @param int $item_id the cart item in reference
     * @param array $selected the values which should be selected 
     */
    public static function getSelectListAsHiddenFields ($item_id, $selected = array()) {
        $obj = self::getSelectsAsObject($item_id, $selected);
        echo view::includeModuleView('order', 'select/select_list_basket', $obj, 1);
        //$childs = orderSelect::getSelectChilds($item_id, $selected);
        //print_r($childs); die;
        /*
        if (!empty($childs->allChildOptions)) {
            //print_r($childs); die;
            if (isset($childs->selectedHuman)) {
                $title = $childs->title;
                $value = $childs->selected;
            
                echo "<input type=\"hidden\" name = \"select[$title]\" value=\"$value\" />";  
            }
            //echo templateView::includeModuleView('order', 'select/select_list_childs_basket', $childs, 1);
        }*/
        
    }
    
    /**
     * method for getting all select lists as human names
     * @see   files views/select/select_list_human
     * @param int $item_id the cart item in reference
     * @param array $selected the values which should be selected 
     */
    public static function getSelectListAsHumanFields ($item_id, $selected = array(), $options = array()) {
        $obj = self::getSelectsAsObject($item_id, $selected);
        if (isset($options['display_email'])) {
            $obj->displayEmail = true;
        }
        //print_r($obj);
        
        return view::get('order', 'select/select_list_human', $obj);
        
        /*
        $childs = orderSelect::getSelectChilds($item_id, $selected, $options);
        
        if (!empty($childs->allChildOptions)) {
            
            if (isset($childs->selectedHuman)) {
                $title = $childs->title;
                $value = $childs->selectedHuman;
                
                
                echo "<br />" ;
                echo $value;  
            }
            //echo templateView::includeModuleView('order', 'select/select_list_childs_basket', $childs, 1);
        }*/
    }
    /*
    public static function getSelectChildListAsHumanFields ($item_id, $selected = array(), $options = array()) {
        //print_r($selected);
        $obj = self::getSelectChilds($item_id, $selected);
        if (isset($options['display_email'])) {
            $obj->displayEmail = true;
        }
        
        echo templateView::includeModuleView('order', 'select/select_list_child_human', $obj, 1);
    }*/
    
    
    public static function getSelectByName () {
        $db = new db();
        $rows = $db->selectOne(self::$table,  null, array(
            'order_item_id' => $order_item_id, 'title' => $title));
        return $rows;
        
    }
    
    /**
     * get selects list as rows from the database table
     * @param int $item_id the cart item in reference
     * @return array all select lists in reference as an array
     */
    public static function getSelects ($item_id) { 
        $db = new db();        
        return $db->selectAll(self::$table, null, array('order_item_id' => $item_id, 'option_id' => '0'));      
    }
    
    /*
    public static function getSelectChilds ($item_id, $selected = array(), $options = array()) { 
        $db = new db();
        
        $row = $db->selectOne(self::$table, null, array('order_item_id' => $item_id));
              
        $q = new QBuilder();
        $q->setSelect(self::$table);
        $q->filter('option_id = ', $row['id']);
        $q->condition('AND');
        $q->filter('title !=', '');
        $row = $q->fetchSingle();
        
        $obj = new stdClass();
        //print "sdog";
        //print_r($selected);
        $title = $row['title'];
        if (!empty($selected)) {
            foreach ($selected['select'] as $key => $val) {
                if ($key == $title) {
                    $obj->selected = $val;
                    $obj->title = $title;
                }
            }
        }
        

        
        $obj->mainChildSelects = $row;
        //if (isset( $selected )) {
        //    $obj->mainChildSelects['selected'] = 
        //}
        //$obj->selected = $selected;  
        //print_r($selected);
        
        $parent_options = array ();
        
        $rows = $db->selectAll(self::$option_table, null, array( 'select_id' => $row['option_id']));                   
        
        //print_r($rows) ; die;
        $i= 1;
        foreach ($rows as $krey => $val) {
            $parent_options[$i] = $val;
            $i++;
        }
        
        $obj->parentOptions = $parent_options;        
        $obj->allChildOptions = array();
        
        $i = 1;
        //print_r($selected); print "GRRRR";
        foreach ($obj->parentOptions as $key => $val) {
            $obj->allChildOptions[$i] = $db->selectAll(self::$option_table, null, array( 'option_id' => $val['id']));           
            foreach ($obj->allChildOptions[$i] as $k => $v) {

                if (isset($obj->selected)) {
                
                    if ($v['value'] == $obj->selected) {
                        $obj->selectedHuman = $v['title'];
                    }
                }
            }
            $i++;
        }        
        return $obj;
    }*/
    
    public static function getSelectSingle ($select_id) {
        $db = new db();
        $rows = $db->selectAll(self::$option_table, null, array('select_id' => $select_id));
        return $rows;
    }
    
    /**
     * get select lists as a simple object. 
     * @param int $item_id
     * @param array $selected
     * @return object $object with titles, options, and selected items.  
     */
    public static function getSelectsAsObject ($item_id, $selected = array()) { 
        //print_r($selected);
        $ary = array();
        $selects = self::getSelects($item_id);
        //print_r($selects);
        $obj = new stdClass;
        $obj->item_id = $item_id;
        $obj->titles = $obj->options = $obj->ids = array ();
        $obj->selected = $obj->selectedHuman = array();

        $id = 1;
        foreach ($selects as $item) {    
            //print_r($item);
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
            if (!empty($row)) {
                $obj->selectedHuman[$id] = $row['title'];
            }
            $id++;
        }
        return $obj;       
    }

}