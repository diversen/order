<?php

class orderGallery {
    
    public static $errors = array();
    public static $table = 'order_item_select_gallery';
    
    public static function getGalleryIdFromItemId ($item_id) {
        
        $row = self::get($item_id);
        if (isset($row['gallery_id'])) {
            $gallery_id = $row['gallery_id']; 
        } else {
            $gallery_id = 0;
        }
        return $gallery_id;
    }
        // }}}
    public static function form($item_id) {
        html::$autoLoadTrigger = 'gallery_submit';
        html::init();
        html::formStart('order_item_form_gallery');
        html::legend(lang::translate('order_item_select_gallery'));
        html::hidden('method', 'item_update_gallery');
        
        $gallery = new galleryAdmin();
        $begin = array (
            'id' => '0', 
            'title' => lang::translate('order_gallery_no_gallery_connected')
        );
        $rows = $gallery->getAllGallery();
        $gallery_id = self::getGalleryIdFromItemId($item_id);        
        html::select('gallery_id', $rows, 'title', 'id', $gallery_id, array(), $begin);
        $str = self::displayGallery($gallery_id);
        html::addHtml($str);
        
        html::label('submit', '');
        html::submit('gallery_submit', lang::translate('order_update'));        
        html::formEnd();
        echo html::getStr();       
    }
    
    //public static function displayGallery () {
        
    //}
    
    public static function validateGallery ($id) {
        if ($id == '0') {
            return 1;
        }
        
        $gallery = self::getGallery($id);
        if (empty($gallery)) {
            self::$errors[] = lang::translate('order_gallery_no_such_gallery');
        }
        return null;
    }
    
    public static function validateItem ($id) {
        $item = order::getItem($id);
        if (empty($item)) {
            self::$errors[] = lang::translate('order_gallery_no_such_item');
        }
    }
    
    public static function getGalleryIdFromRequest() {
        if (isset($_POST['gallery_id'])) {
            return $_POST['gallery_id'];
        }
        return null;
    }
    
    static function itemEditMenu ($id) {
        return html::createLink("/order/gallery/edit/$id", lang::translate('order_gallery_edit'));
    }
    
   
    public static function updateGalleryControl ($frag = 3) {

        $item_id = URI::getInstance()->fragment($frag);
        templateView::includeModuleView('order/products', 'admin_menu', array('id' => $item_id));
        template::setTitle(lang::translate('order_edit_html_title'));
        $gallery_id = self::getGalleryIdFromRequest();
        
        $res = self::validateGallery($gallery_id);
        if ($res === 1) {
            self::delete($item_id);
            session::setActionMessage(
                lang::translate('order_gallery_action_message_gallery_removed'));
                
            header("Location: /order/gallery/edit/$item_id");
                die;
        }
        
        self::validateItem ($item_id);
        if (isset($_POST['method']) && $_POST['method'] == 'item_update_gallery'){          
            if (empty(self::$errors)){
                
                self::delete($item_id);
                $values = array ('gallery_id' => $_POST['gallery_id'],
                    'order_item_id' => $item_id);
                $res = self::update($values);
                session::setActionMessage(
                        lang::translate('order_action_message_gallery_updated'));
                    header("Location: /order/gallery/edit/$item_id");
            } else {
                view_form_errors(self::$errors);
            }
        }
        orderGallery::form($item_id);
    }
    
    public static function displayGallery ($gallery_id) {

        //$item_id = URI::getInstance()->fragment($frag);
        
        if ($gallery_id) {
            $options = array ();
            $options['gallery_id'] = $gallery_id;
            $options['no_admin'] = 1;
            $gallery = new gallery();
            $rows = $gallery->getAllFileInfo($gallery_id);
            $str = $gallery->getThumbTableHTML($rows, $options);
            return $str;
        }
    }
    
    public static function update ($values) {
        $db = new db();
        $db->insert(self::$table, $values);
    }
    
    public static function delete ($item_id) {
        $db = new db();
        return $db->delete(self::$table, 'order_item_id', $item_id);
    }
    
    public static function get ($item_id) {
        $db = new db();
        return $db->selectOne(self::$table, 'order_item_id', $item_id);
    }
    
    public static function getGallery ($id = null) {
        $gallery = galleryAdmin::getGallery($id);
        return $gallery;
    }
}