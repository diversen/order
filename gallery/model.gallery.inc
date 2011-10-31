<?php

class orderGallery {
    
    public static $errors = array();
    
    static function itemEditMenu ($id) {
        return html::createLink("/order/gallery/edit/$id", lang::translate('order_gallery_edit'));
    }
    

}