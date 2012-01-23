<?php

include_module('order/shipping');

class orderShippingFree {

    /**
     * db table for getting free shipping amount
     * @var string $table
     */
    static $table = 'order_shipping_free';
    
    /**
     * var holding errors
     * @var array $errors
     */
    static $errors = array();
    
    /**
     * method for validating shippingFree form
     */
    static function validate () {

        if (!isset($_POST['submit'])) return;

        $_POST['private'] = locfloat_to_sysfloat($_POST['private']);

        if (!isset($_POST['private'])) {
            self::$errors[] = lang::translate('order_shipping_free_float_error');
            return;
        }

        if( (float)$_POST['private'] < 0 ){
            self::$errors[] = lang::translate('order_shipping_free_float_error');
            return;
        }

        if(!is_float_val($_POST['private'], true)){
            self::$errors[] = lang::translate('order_shipping_free_float_error');
            return;
        }
        /*
        $_POST['company'] = locfloat_to_sysfloat($_POST['company']);
        if (!isset($_POST['company'])) {
            self::$errors[] = lang::translate('order_shipping_free_float_error');
            return;
        }

        if( (float)$_POST['company'] < 0 ){
            self::$errors[] = lang::translate('order_shipping_free_float_error');
            return;
        }

        if(!is_float_val($_POST['company'], true)){
            self::$errors[] = lang::translate('order_shipping_free_float_error');
            return;
        }*/
    }

    /**
     * method for getting amount when shipping is free. 
     * @return int $cost the amount were shipping is free. 
     */
    public static function getShippingFree() {
        $db = new db();
        $row = $db->selectOne(self::$table, null, array('type' => 'private'));
        return $row['cost'];
    }
    
    /**
     * method for getting info about shipping free from order_items
     * and total shopping amount in basket. 
     * @param array $order_items
     * @param int $total
     * @return array $ret  
     */
    public static function getShippingFreeInfo ($order_items, $total) {

        $shipping_is_free = 0;
        $shipping_free = self::getShippingFree();
                
        $ret = array ();  
        
        // no items - free shipping
        if (count($order_items) == 0) {
            $shipping_is_free = 1;
            $shipping_free_str = lang::translate('order_amount_shipping_is_free') . '&nbsp;';       
        // no option for shipping free if shipping free is 0        
        } else if ($shipping_free == 0) {
            $shipping_free_str = '';
        // if total amount is less than shipping_free amount 
        // we set a string with amount we need in order to get free shipping
        } else if ( $total <  $shipping_free ) {
            $shipping_free_needed = order::getCurrencySymbol() . "&nbsp;";
            $shipping_free_needed.= format_float_mon($shipping_free - $total);
            $shipping_free_str = lang::translate('order_amount_before_shipping_free', array($shipping_free_needed)) . ' ';
            //$shipping_free_str.= lang::translate('order_amount_added_shipping_cost_final');
        } else {
        // shipping is free
            $shipping_is_free = 1;
            $shipping_free_str = lang::translate('order_amount_shipping_is_free') . '&nbsp;';
        }
             
        $ret['shipping_is_free'] = $shipping_is_free;
        $ret['shipping_free_str'] = $shipping_free_str;
        return $ret;
    }
    

    /**
     * gets shipping free table row
     * @return array $row
     */
    public static function getShippingFreeTable () {
        $db = new db();
        $rows = $db->selectAll(self::$table);
        $row = array();
        foreach ($rows as $key => $val) {
            $row[$val['type']] = $val['cost'];
        }
        return $row;
    }

    /**
     * method for showing form for updating shipping free table 
     * @param type $method 
     */
    public static function showForm ($method = 'update') {
        html::$autoLoadTrigger = 'submit';
        $row = self::getShippingFreeTable();
        html::init($row);
        html::formStart('order_shipping_free_form');
        html::legend(lang::translate('order_shipping_free_legend_edit'));
        html::label('private', lang::translate('order_shipping_free_private_label'));
        html::text('private');
        html::label('submit', '');
        html::submit('submit', lang::translate('order_update'));
        html::formEnd();
        echo html::getStr();
    }

    /**
     * method for updating shipping free table
     * @return boolean $res true on success and false on failure. 
     */
    public static function update () {
        $db = new db();
        db::$dbh->beginTransaction();

        $search = array ('type' => 'private');
        $values = array ('cost' => $_POST['private']);
        $res = $db->update(self::$table, $values, $search);
        if ($res) {
            db::$dbh->commit();
            return 1;
        } else {
            db::$dbh->rollBack();
            return 0;
        }
    }

    /**
     * method for displaying admin page for editing shipping free. 
     */
    public static function index () {
        template::setTitle(lang::translate('order_shopping_free_html_title'));
        echo lang::translate('order_shipping_free_info');

        if (isset($_POST['submit'])) {
            self::validate();
            if (!empty(self::$errors)) {
                view_form_errors(self::$errors);
            } else {
                $res = self::update();
                if ($res) {
                    $message = lang::translate('order_shipping_free_update_confirm');
                    session::setActionMessage($message);
                    header ("Location: /order/shipping/free");
                } else {
                    $message = "Update failed in: " . __FILE__;
                    cos_error_log($message);
                }
                
            }
        }
        orderShippingFree::showForm();
    }  
}