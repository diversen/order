<?php

class orderShipping {

    /**
     *
     * db table with values of a type. 
     * @var string $costTable
     */
    public static $costTable = 'order_shipping_cost';
    
    /**
     * 
     * db table with different cost types (e.g. private and international)
     * @var type $costType
     */
    public static $costType = 'order_shipping_cost_type';

    /**
     * holding errors
     * @var array $errors 
     */
    public static $errors = array();
    
    /**
     * not implemented
     */
    static function validate () {

    }
    
    /**
     * method for getting shipping info as a array 
     * @param array $order_items the order items
     * @param string $total total amount cost
     * @param string $weight total weight of all items
     * @return array $info with shipping info.  
     *               $info['shipping_is_free'] = $shipping_is_free; // boolean
     *               $info['shipping_free_str'] = $shipping_free_str; // e.g. 
     *                you need 10.00 DDK and shipping will be free;
     *               $info['shipping_cost'] = $shipping_cost; // shipping cost
     *               $info['total_cost'] = $shipping_cost + $total; // total cost
     */
    public static function getShippingInfo ($order_items, $total, $weight) {
         

        $types = self::getTypes();
        $shipping_info = order::getShippingCookie();
        $order_shipping_type = null;
        $ret = array();
        if (isset($shipping_info['order_shipping_type'])) {
            $order_shipping_type = $shipping_info['order_shipping_type'];
        }
        
        if (count($types) == 1) {
            $shipping_cost = orderShipping::getWeightToCost(1, $weight);
            $ret['shipping_cost'] = $shipping_cost;
            $ret['type'] = self::getType(1);
            
            
        } else if ($order_shipping_type) {
            $shipping_cost = orderShipping::getWeightToCost($order_shipping_type, $weight);
            $ret['shipping_cost'] = $shipping_cost;
            $ret['type'] = self::getType($order_shipping_type);
            
        } else {
            $shipping_cost = null; 
        }

        $ret['shipping_cost_all_types'] = orderShipping::getWeightToCostAllTypes($weight);
        $ret['shipping_cost'] = $shipping_cost;
        $ret['total_cost'] = $shipping_cost + $total;
        return $ret;       
    }
    
        
    public static function getWeightToCostAllTypes($weight, $newline = "\n") {
        $types =self::getTypes();
        $str = '';      
        $str = lang::translate('order_total_weight') . " " . format_float_mon($weight) . " Kg$newline";
        foreach($types as $key => $val) {
            $cost = self::getWeightToCost($val['id'], $weight);
            $str.= $val['name'] . ' ' . format_float_mon($cost) . ' ' . order::getCurrencySymbol() . $newline;
            
        }
        return rtrim($str);    
    }

    public static function sanitize () {

        if (!isset($_POST['submit'])) {
            return;
        }

        $_POST['cost'] = locfloat_to_sysfloat($_POST['cost']);

        if (empty($_POST['cost']) && $_POST['cost'] != '0') {
            self::$errors[] = lang::translate('order_shipping_form_cost_float_empty');
            return;
        }

        if( (float)$_POST['cost'] < 0 ){            
            self::$errors[] = lang::translate('order_shipping_form_cost_float_less_than_zero');
            return;
        }

        if(!is_float_val($_POST['cost'], true)){
            
            self::$errors[] = lang::translate('order_shipping_form_cost_incorrect_float_value');
            return;
        }

        $_POST['weight'] = locfloat_to_sysfloat($_POST['weight']);
        if (empty($_POST['weight']) && $_POST['weight'] != '0') {
            self::$errors[] = lang::translate('order_shipping_form_weight_float_empty');
            return;
        }

        if( (float)$_POST['weight'] < 0 ){
            self::$errors[] = lang::translate('order_shipping_form_weight_float_less_than_zero');
            return;
        }

        if(!is_float_val($_POST['weight'], true)){
            self::$errors[] = lang::translate('order_shipping_form_weight_incorrect_float_value');
            return;
        }
    }
    
    public static function shippingListTypes () {
        $db = new db();
        $db->selectAll(self::$costTable);
    }

    static function getAll ($type) {
        $db = new db();

        //echo $query = "SELECT * FROM " . self::$table . " ORDER BY CAST(`weight` AS DECIMAL)";
        $query = "Select * from " .  self::$costTable . " ";
        $query.= "WHERE parent = " . db::$dbh->quote($type);
        $query.= "ORDER BY 0+weight ASC";
        $rows = $db->selectQuery($query);
        return $rows;
    }

    static function displayAll ($type) {
        $rows = self::getAll($type);
        echo templateView::includeModuleView('order', 'shipping/shipping_list_all', $rows);
        //include_view('order/shipping', '');
    }

    public static function add ($type) {
        $db = new db();
        $values = db::prepareToPost();
        $values['parent'] = $type;
        $res = $db->insert(self::$costTable, $values);
        return $res;
    }

    static function update ($id) {
        $db = new db();
        $values = db::prepareToPost();
        //$values['type'] = $type;
        $res = $db->update(self::$costTable, $values, $id);
        return $res;
    }

    static function delete ($id) {
        $db = new db();
        $values = db::prepareToPost();
        //$values['type'] = $type;
        $res = $db->delete(self::$costTable, 'id', $id);
        return $res;
    }
    
    public static function deleteType ($id) {
        $db = new db();
        db::$dbh->beginTransaction();
        try {            
            $db->delete(self::$costTable, 'parent', $id);
            $db->delete(self::$costType, 'id', $id);
            
        } catch (PDOException $e) {            
            db::$dbh->rollBack();
            cos_error_log($e->getTraceAsString());
            return false;
        }
        return db::$dbh->commit();
    }

    static function getOne ($id) {
        $db = new db ();
        $row = $db->selectOne(self::$costTable, null, array('id' => $id));
        return $row;
    }
    

    
    
    public static function showCostTypeForm ($method = 'insert', $row = null) {
        html::$autoLoadTrigger = 'submit';
        if ($method == 'insert') {
            html::init();
        } else {
            html::init($row);
        }
        html::formStart('order_shipping_form');
        if ($method == 'insert') {
            html::legend(lang::translate('order_shipping_legend'));
        } else {
            html::legend(lang::translate('order_shipping_legend_edit'));
        }

        html::label('weight', lang::translate('order_shipping_weight_label'));
        html::text('weight');
        html::label('cost', lang::translate('order_shipping_cost_label'));
        html::text('cost');
        html::label('submit', '');
        
        if ($method == 'insert') {
            html::submit('submit', lang::translate('order_insert'));
        } else {
            html::submit('submit', lang::translate('order_update'));
        }

        html::formEnd();
        echo html::getStr();
    }
    
    /**
     *
     * returns all types of shipping
     * @return array $types
     */
    public static function getTypes () {
        static $types = null;
        if ($types) return $types;   
        $db = new db();
        $types = $db->selectAll(self::$costType);
        return $types;
    }
    
    public static function getCountTypes () {
        $types = self::getTypes();
        return count($types);
        
    }
    
    /**
     *
     * returns all types of shipping
     * @return array $types
     */
    public static function getType ($id) {
        static $types = null;
        if ($types) return $types;   
        $db = new db();
        $types = $db->selectOne(self::$costType, null, array ('id' => $id));
        return $types;
    }
    
    public static function index() {
        $rows = self::getTypes();
        echo templateView::get('order', 'shipping/cost_types', $rows);
    }

    public static function editTypeControl() {
        $db = new db();
        $id = uri::getInstance()->fragment(3);
        $row = $db->selectOne(self::$costType, null, array ('id'=>$id));
        if (isset($_POST['submit'])) {
            $_POST = html::specialEncode($_POST);
            if (empty($_POST['name'])) {
                self::$errors[] = lang::translate('order_shipping_error_no_title');
            }
            if (empty(self::$errors)) {
                self::editType($id);
                session::setActionMessage(lang::translate('order_shipping_action_type_updated'));
                http::locationHeader("/order/shipping/index");
            } else {
                view_form_errors(self::$errors);
            }
        }
        orderShipping::showTypeForm('update', $row);
        //echo templateView::get('order', 'shipping/cost_types', $rows);
    }
    
    public static function editType ($id) {
        $values = db::prepareToPost();
        $db = new db();
        return $db->update(self::$costType, $values, array ('id' => $id));
    }
    
    public static function addTypeControl() {        
        if (isset($_POST['submit'])) {
            $_POST = html::specialEncode($_POST);
            if (empty($_POST['name'])) {
                self::$errors[] = lang::translate('order_shipping_error_no_title');
            }
            if (empty(self::$errors)) {
                $id = self::addType();              
                session::setActionMessage(lang::translate('order_shipping_action_type_added'));
                http::locationHeader("/order/shipping/edit_type_table/$id");
            } else {
                view_form_errors(self::$errors);
            }
        }
        orderShipping::showTypeForm('insert');
        //echo templateView::get('order', 'shipping/cost_types', $rows);
    }
    
    public static function addType () {
        $db = new db();
        $values = db::prepareToPost();
        $res = $db->insert(self::$costType, $values);
        if ($res) {
            $id = db::$dbh->lastInsertId();
            return $id;
        }
        return false;
    }
    
    public static function showTypeForm ($method = 'insert', $row = null) {
        html::$autoLoadTrigger = 'submit';
        if ($method == 'insert') {
            html::init();
        } else {
            html::init($row);
        }
        html::formStart('order_shipping_type_form');
        if ($method == 'insert') {
            html::legend(lang::translate('order_shipping_type_legend'));
        } else {
            html::legend(lang::translate('order_shipping_type_legend_edit'));
        }

        html::label('name', lang::system('system_form_label_title'));
        html::text('name');
        html::label('description', lang::system('system_form_label_abstract'));
        html::textareaSmall('description');
        html::label('submit', '');
        
        if ($method == 'insert') {
            html::submit('submit', lang::translate('order_insert'));
        } else {
            html::submit('submit', lang::translate('order_update'));
        }

        html::formEnd();
        echo html::getStr();
    }

    public static function showForm ($method = 'insert', $row = null) {
        
        html::$autoLoadTrigger = 'submit';
        if ($method == 'insert') {
            html::init();
        } else {
            $row['weight'] = intl::formatDecimal(
                    config::getMainIni('locale'), $row['weight']);
            $row['cost'] = intl::formatDecimal(
                    config::getMainIni('locale'), $row['cost']);
            html::init($row);
        }
        html::formStart('order_shipping_form');
        if ($method == 'insert') {
            html::legend(lang::translate('order_shipping_legend'));
        } else {
            html::legend(lang::translate('order_shipping_legend_edit'));
        }

        $weight_example = intl::formatDecimal(
                                    config::getMainIni('locale'), 10.50);
        html::label(
                'weight', 
                    lang::translate(
                            'order_shipping_weight_label', 
                            array ($weight_example))
                );
        html::text('weight');
        
        
        $cost_example = intl::formatDecimal(
                                    config::getMainIni('locale'), 100.50);
        html::label('cost', lang::translate(
                'order_shipping_cost_label', 
                    array ($cost_example))
                );
        html::text('cost');
        html::label('submit', '');
        
        if ($method == 'insert') {
            html::submit('submit', lang::translate('order_insert'));
        } else {
            html::submit('submit', lang::translate('order_update'));
        }

        html::formEnd();
        echo html::getStr();
    }

    public static function showDeleteForm () {
        html::$autoLoadTrigger = 'submit';
        
        html::formStart('order_shipping_form');
        html::legend(lang::translate('order_shipping_legend_form_delete'));
        html::label('submit', '');
        html::submit('submit', lang::translate('order_delete'));
        html::formEnd();
        echo html::getStr();
    }
    
    public static function showDeleteTypeForm () {
        html::$autoLoadTrigger = 'submit';
        
        html::formStart('order_shipping_form');
        html::legend(lang::translate('order_shipping_legend_form_delete_type'));
        html::label('submit', '');
        html::submit('submit', lang::translate('order_delete'));
        html::formEnd();
        echo html::getStr();
    }

    static function adminOptions ($id) {

        $row = self::getOne($id);
        echo html::createLink(
            "/order/shipping/edit/$id/$row[parent]",
            lang::translate('order_edit')
        );
        echo MENU_SUB_SEPARATOR;
        echo html::createLink(
            "/order/shipping/delete/$id/$row[parent]",
            lang::translate('order_delete')
        );

    }

    
    public static function getWeightToCost($type, $weight) {
        $rows = self::getAll($type);
        $i = count($rows);
        $res = 0;
        foreach ($rows as $key => $val) {
            if ($weight > $val['weight']) {
                continue;
            } else {
                return $res = $val['cost'];
            }
        }

        if ($res == '0'){
            $row = array_pop($rows);
            return $row['cost'];
        }
        return $res;
    }

}
