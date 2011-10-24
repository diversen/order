<?php

include_module('order/shipping');

class orderShippingFree {

    static $table = 'order_shipping_free';
    static $errors = array();
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

    public static function getShippingFreePrivate() {
        $db = new db();
        $row = $db->selectOne(self::$table, null, array('type' => 'private'));
        //echo_r($free);
        return $row['cost'];

    }

    static function getShippingFreeTable () {
        $db = new db();
        $rows = $db->selectAll(self::$table);
        $row = array();
        foreach ($rows as $key => $val) {
            $row[$val['type']] = $val['cost'];
        }
        return $row;
    }

    static function showForm ($method = 'update') {
        html::$autoLoadTrigger = 'submit';
        $row = self::getShippingFreeTable();

        html::init($row);
        html::formStart('order_shipping_free_form');
        html::legend(lang::translate('order_shipping_free_legend_edit'));
        html::label('private', lang::translate('order_shipping_free_private_label'));
        html::text('private');
        //html::label('company', lang::translate('order_shipping_free_company_label'));
        //html::text('company');
        html::label('submit', '');
        html::submit('submit', lang::translate('order_update'));
        html::formEnd();
        echo html::$formStr;
    }

    static function update () {
        $db = new db();
        db::$dbh->beginTransaction();

        $search = array ('type' => 'private');
        $values = array ('cost' => $_POST['private']);
        $res = $db->update(self::$table, $values, $search);

        /*
        $search = array ('type' => 'company');
        $values = array ('cost' => $_POST['company']);
        $res2 = $db->update(self::$table, $values, $search);
        */
        if ($res) {
            db::$dbh->commit();
            return 1;
        } else {
            db::$dbh->rollBack();
            return 0;
        }
    }

    static function index () {
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