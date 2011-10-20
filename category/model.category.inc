<?php

include_model ("order");
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

            $legend_text = lang::translate('order_category_legend_update');

            html::init($row);
            $button_text = lang::translate('order_update');
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

    static function getAll ($fields = null) {
        $db = new db();
        return $db->selectAll(self::$table, $fields, null, null, null, 'order', true);        
    }

    static function displayHTMLMenu () {
        $vars = self::getAll(array('id, name', 'description'));
        templateView::includeModuleView('order', 'cats_menu', $vars);
    }
    
    static function displayBlockMenu () {
        $vars = self::getAll(array('id, name', 'description'));
        templateView::includeModuleView('order', 'cat_text_block', $vars);
    }
   
    static function displayCats () {
        $vars = self::getAll(array('id, name', 'description'));
        templateView::includeModuleView('order', 'display_cats', $vars);
    }

    /*
    static function displayCatsCart () {
        $vars = self::getAll();
        templateView::includeModuleView('order', 'display_cats_full', $vars);
    }*/

    // {{{ displayCart
    static public function displayCatItems (){
        $db = new db();
        $search = array ('category' => $_GET['cat']);
        $template = 'display_cart';
        $all_items = $db->selectAll('order_items', null, $search, null, null, 'item_order', true);
        echo templateView::includeModuleView('order', $template, $all_items, 1);
    }
    // }}}

    static function add () {

        $db = new db();
        db::$dbh->beginTransaction();
      
        $values = db::prepareToPost();
        $values['md5'] = md5(uniqid());
        
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

    public static function updateImage ($id) {
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
        $values['md5'] = md5(uniqid());

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

    static function displayCatsFull () {
        $vars = self::getAll();
        templateView::includeModuleView('order', 'display_cats_full', $vars);
        
    }

    public function displaySortItems(){
        $db = new db();

        //$todos = $this->selectAll('order_items');
        //$otods = $this->select();
        $items = $db->selectAll(self::$table, null, null, null, null, 'order', true);

        //$todos = $this->get();
        $str = "<div id=\"order_category_list\"><div id=\"response\"></div>";
        $str.= "<ul id=\"sort_items\">\n";
        foreach ($items as $key => $val){
            $str.= "<li id = \"arrayorder_$val[id]\">$val[name] $val[order]";
            $str.= "</li><div class=\"clear\"></div>";
        }
        $str.= "</ul></div>\n";
        echo $str;
    }
}