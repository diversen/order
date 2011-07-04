<?php

class orderShipping {

    static $table = 'order_shipping_cost';

    static $errors = array();
    static function validate () {
        //$db = new db();
        //$db->selectOne(self::$table, 'id', );
    }

    static function sanitize () {

        if (!isset($_POST['submit'])) return;

        $_POST['cost'] = locfloat_to_sysfloat($_POST['cost']);

        if (empty($_POST['cost'])) {
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
        if (empty($_POST['weight'])) {
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

    static function getAll ($type) {
        $db = new db();

        //echo $query = "SELECT * FROM " . self::$table . " ORDER BY CAST(`weight` AS DECIMAL)";
        $query = "Select * from " .  self::$table . " ";
        $query.= "WHERE type = " . db::$dbh->quote($type);
        $query.= "ORDER BY 0+weight ASC";
        $rows = $db->selectQuery($query);
        return $rows;
    }

    static function displayAll ($type) {
        $rows = self::getAll($type);
        echo templateView::includeModuleView('order', 'shipping_list_all', $rows);
        //include_view('order/shipping', '');
    }

    static function add ($type) {
        $db = new db();
        $values = db::prepareToPost();
        $values['type'] = $type;
        $res = $db->insert(self::$table, $values);
        return $res;
    }

    static function update ($id) {
        $db = new db();
        $values = db::prepareToPost();
        //$values['type'] = $type;
        $res = $db->update(self::$table, $values, $id);
        return $res;
    }

    static function delete ($id) {
        $db = new db();
        $values = db::prepareToPost();
        //$values['type'] = $type;
        $res = $db->delete(self::$table, 'id', $id);
        return $res;
    }

    static function getOne ($id) {
        $db = new db ();
        $row = $db->selectOne(self::$table, null, array('id' => $id));
        return $row;
    }

    static function showForm ($method = 'insert', $row = null) {
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
        echo html::$formStr;
    }

    static function showDeleteForm () {
        html::$autoLoadTrigger = 'submit';
        
        html::formStart('order_shipping_form');
        html::legend(lang::translate('order_shipping_legend_form_delete'));
        html::label('submit', '');
        html::submit('submit', lang::translate('order_delete'));
        html::formEnd();
        echo html::$formStr;
    }

    static function adminOptions ($id) {

        $row = self::getOne($id);



        echo html::createLink(
            "/order/shipping/edit/$id/$row[type]",
            lang::translate('order_edit')
        );
        echo MENU_SUB_SEPARATOR;
        echo html::createLink(
            "/order/shipping/delete/$id/$row[type]",
            lang::translate('order_delete')
        );

    }

    
    static function getWeightToCost($type, $weight) {
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

function locfloat_to_sysfloat($value)
{
    $larr = localeconv();
    $search = array(
        $larr['decimal_point'],
    );

    $replace = array('.');
    $res = str_replace($search, $replace, $value);
    return $res;

}

function sysfloat_to_locfloat($value)
{
    $larr = localeconv();
    $replace = array(
        $larr['decimal_point'],
    );

    $search = array('.');
    $res = str_replace($search, $replace, $value);
    return $res;

}

function is_float_val ($val, $accept_zero = false) {
    if ($accept_zero && ($val == 0) ) {
        return true;
    }

    $isFloat=preg_match('/^\s*([0-9]+(\.[0-9]+)?)\s*$/', $val, $myNum);
    if ($myNum[1]) {
        return true;
    } else {
        return false;
    }

}

/*
function ParseFloat($floatString){
    $LocaleInfo = localeconv();
    $floatString = str_replace($LocaleInfo["mon_thousands_sep"] , "", $floatString);
    $floatString = str_replace($LocaleInfo["mon_decimal_point"] , ".", $floatString);
    return floatval($floatString);
}*/