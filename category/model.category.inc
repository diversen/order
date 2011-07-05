<?php

class orderCategory {
    static $table = 'order_category';
    static function validate() {
        
    }
    static function showForm ($method = 'insert') {
        html::$autoLoadTrigger = 'submit';
        
        if ($method == 'delete') {
            $button_text = lang::translate('order_delete');
            html::formStart('order_category_form_delete');
            html::legend(lang::translate('order_category_legend_delete'));

            html::label('submit', '');
            html::submit('submit', $button_text);
            html::formEnd();
            echo html::$formStr;
            return;
        }

        if ($method == 'update') {
            html::formStart('order_category_form');

            $id = uri::$fragments[3];
            $row = self::getCategory($id);

            $button_text = lang::translate('order_update');
            $legend_text = lang::translate('order_category_legend_update');
            $submit_label = lang::translate('order_delete_submit_label');
            $submit_label.= $row['name'];
            
            html::init($row);
            html::legend($legend_text);

            html::label('submit', $submit_label);
            html::submit('submit', $button_text);
            html::formEnd();
            echo html::$formStr;
            return;
        }

        $button_text = lang::translate('order_insert');
        $legend_text = lang::translate('order_category_legend_insert');

        html::formStart('order_category_form');
        html::init();
        html::legend($legend_text);
        html::label('name', lang::translate('order_category_name_label'));
        html::text('name');
        html::label('file', lang::translate('order_category_file_label'));
        html::file('file', $extra);
        html::label('submit', '');
        html::submit('submit', $button_text);
        html::formEnd();
        echo html::$formStr;
        return;
    }

    static function getCategory ($id) {
        $db = new db();
        return $db->selectOne(self::$table, 'id', $id);
    }

    static function getAll () {
        $db = new db();
        return $db->selectAll(self::$table);
    }

    static function displayCats () {
        $vars = self::getAll();
        templateView::includeModuleView('order', 'display_cats', $vars);
    }

    static function add () {
        include_once  "upload.php";
        $db = new db();
        $values = db::prepareToPost();
        $db->insert(self::$table, $values);

        //$id = db::$dbh->last_insert_id;
        $id = db::$dbh->lastInsertId();

        
        $res = uploadBlob::scaleImageToBlob(
            'file',
            'order_category', $id, 400);
        return $res;
    }

    static function update() {
        $id = uri::$fragments[3];
        $values = db::prepareToPost($_POST);

        $db = new db();
        $res = $db->update(self::$table, $values, $id);
        return $res;
    }

    static function delete() {
        $id = uri::$fragments[3];
        $db = new db();
        return $db->delete(self::$table, 'id', $id);

    }
}