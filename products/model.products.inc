<?php

include_model ("order");

class orderProducts extends order {

    public function displaySortItems(){
        
        include_module ('jquerysort');
        $options = array ();
        $options['table'] = self::$table;
        
        $options['field'] = 'item_order';
        $options['title'] = 'item_name';

        jquerysort::setOptions($options);
        jquerysort::setJs();
        echo jquerysort::getHTML();
    }
    
    static function addControl () {
        if (!session::checkAccessControl('order_allow')){
            return;
        }
        
        template::setTitle(lang::translate('order_add_product_html_title'));
        $cart = new order ();
        if (isset($_POST['submit'])){
            $cart->validate();
            $cart->sanitize();
            if (empty($cart->errors)){
                $id = $cart->addItem();
                if ($id) {
                    session::setActionMessage(lang::translate('order_confirm_product_inserted'));
                    header("Location: /order/products/edit/$id");
                } else {
                    view_form_errors($cart->errors);
                    $message = "Could not add product item in: " . __FILE__;
                    cos_error_log($message);
                }
            } else {
                view_form_errors($cart->errors);
            }    
        }

        order::form('insert');
    }
}
