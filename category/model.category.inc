<?php

include_once  "upload.php";

class orderCategory {
    static $table = 'order_category';
    static $errors = array();
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

            html::init($row);
            $button_text = lang::translate('order_update');
            html::label('name', lang::translate('order_category_name_label'));
            html::text('name');
            html::label('description', lang::translate('order_category_description_label'));
            html::textarea('description');
            html::label('file', lang::translate('order_category_file_label'));
            html::file('file');

            html::label('submit', '');
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
        html::label('description', lang::translate('order_category_description_label'));
        html::textarea('description');
        html::label('file', lang::translate('order_category_file_label'));
        html::file('file');
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

        $db = new db();
        db::$dbh->beginTransaction();
      
        $values = db::prepareToPost();
        $db->insert(self::$table, $values);
        $id = db::$dbh->lastInsertId();

        $res = self::updateImage($id);
        if (!$res) {
            db::$dbh->rollBack();
            return false;
        } else {
            db::$dbh->commit();
            return true;
        }
    }

    static function updateImage ($id) {
        // scale image into blob

        $length = get_module_ini('order_category_image_size');
        if (is_uploaded_file($_FILES['file']['tmp_name'])) {
            $res = uploadBlob::scaleImageToBlob(
                'file', self::$table, 'file', $id, $length);
            if (!$res) {
                self::$errors = uploadBlob::$errors;
                return false;

            } else {
                return true;
            }
        }
        return true;
    }

    static function update() {
        $id = uri::$fragments[3];
        $values = db::prepareToPost($_POST);

        $db = new db();
        db::$dbh->beginTransaction();
        $db->update(self::$table, $values, $id);
        
        $res = self::updateImage($id);
        if (!$res) {
            db::$dbh->rollBack();
            return false;
        } else {
            db::$dbh->commit();
            return true;
        }
        //return self::updateImage($id);
    }

    static function delete() {
        $id = uri::$fragments[3];
        $db = new db();
        return $db->delete(self::$table, 'id', $id);
    }
}