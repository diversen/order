<?php

include_model ("order");
include_once "upload.php";
include_once "imagescale.php";

class orderCategory {
    public static $table = 'order_category';
    public static $errors = array();
    public static $maxsize = 2000000;
    public static $allowMime = 
        array ('image/gif', 'image/jpeg', 'image/pjpeg', 'image/png');
    public static function validate() {
        
    }
    
    /**
     * 
     * @param type $method (delete, update or insert)
     */
    public static function showForm ($method = 'insert') {
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
            html::textareaSmall('description');
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
        html::textareaSmall('description');
        html::label('file', lang::translate('order_category_file_label'));
        html::file('file');
        html::label('submit', '');
        html::submit('submit', $button_text);
        html::formEnd();
        echo html::$formStr;
        return;
    }

    /**
     * get a category from id. 
     * @param int $id the category id
     * @return array $category
     */
    public static function getCategory ($id) {
        $db = new db();
        return $db->selectOne(self::$table, 'id', $id);
    }

    /**
     * get all categories. 
     * @param  string $fields to get
     * @return array $categories 
     */
    public static function getAll ($fields = null) {
        $db = new db();
        return $db->selectAll(self::$table, $fields, null, null, null, 'order', true);        
    }
    
    /**
     * display all categoies as a HTML menu on top of pages. 
     */
    public static function displayHTMLMenu () {
        $vars = self::getAll(array('id, name', 'description'));
        templateView::includeModuleView('order', 'category/top_menu', $vars);
    }
    
    /**
     * display all categories as HTML block. 
     */
    public static function displayBlockMenu () {
        $vars = self::getAll(array('id, name', 'description'));
        templateView::includeModuleView('order', 'category/block', $vars);
    }
   
    /**
     * display categories as admin list. 
     */
    public static function displayCats () {
        $vars = self::getAll(array('id, name', 'description'));
        templateView::includeModuleView('order', 'category/admin_list', $vars);
    }

    /**
     * displays a full user cart category
     */
    public static function displayCatItems (){
        $db = new db();
        $search = array ('category' => $_GET['cat']);
        $template = 'category/cart_category';
        $all_items = $db->selectAll('order_items', null, $search, null, null, 'item_order', true);
        echo templateView::includeModuleView('order', $template, $all_items, 1);
    }

    /**
     * add a category
     * @return boolean true on success and false on failure.  
     */
    public static function add () {

        $db = new db();
        db::$dbh->beginTransaction();
      
        $values = db::prepareToPost();
        $values['md5'] = md5(uniqid());
        
        $db->insert(self::$table, $values);
        $id = db::$dbh->lastInsertId();

        if (!empty($_FILES['file']['name']) ){
            $res = self::updateImage($id);
            if (!$res) {
                db::$dbh->rollBack();
                return false;
            }
        }
        //} else {
        $res = db::$dbh->commit();
        return $res;
        //}
    }

    /**
     * updates a image on update category
     * @param type $id the id of the category to update
     * @return boolean true on success and false on failure. 
     */
    public static function updateImage ($id) {
       
        if (empty($_FILES['file']['name'])) {
            return true;
        }
        $width = get_module_ini('order_category_image_size');
        
        //$options['filename'] = 'file';
        $options['maxsize'] = self::$maxsize;
        $options['allow_mime'] = self::$allowMime;
                
        $fp = uploadBlob::getFP('file', $options);
        if (!$fp) {
            self::$errors = uploadBlob::$errors;
            return false;
        } 
        
        $values['file'] = $fp;
        
        // we got a valid file pointer where we checked for errors
        // now we use the tmp name for the file when scaling. 
        $res = imagescale::byX(
            $_FILES['file']['tmp_name'], 
            $_FILES['file']['tmp_name'], 
            $width);
        
        //$values['id'] = $id;
        $values['content_type'] = $_FILES['file']['type'];        
        $bind = array('file' => PDO::PARAM_LOB);
        
        $db = new db();
        $res = $db->update(self::$table, $values, $id, $bind);
        return $res;
    }

    /**
     * updates a category
     * @return boolean true on success and false on failure
     */
    public static function update() {
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
    }

    /**
     * deletes a category
     * @return boolean true on success and false on failure
     */
    public static function delete() {
        $id = uri::$fragments[3];
        $db = new db();
        return $db->delete(self::$table, 'id', $id);
    }
    
    /**
     * display all categories. 
     */
    public static function displayCatsFull () {
        $vars = self::getAll();
        templateView::includeModuleView('order', 'category/cart_all', $vars);       
    }

    /**
     * display jquery sorting of categories. 
     */
    public function displaySortItems(){
        include_module ('jquerysort');
        $options = array ();
        $options['table'] = self::$table;
        
        $options['field'] = 'order';
        $options['title'] = 'name';
        //jquerysort::setTable(self::$table);
        jquerysort::setOptions($options);
        jquerysort::setJs();
        echo jquerysort::getHTML();
    }
}