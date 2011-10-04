<?php

include_model ("order");

class orderProducts extends order {

    public function displaySortItems(){
        $db = new db();

        //$todos = $this->selectAll('order_items');
        //$otods = $this->select();
        $items = $db->selectAll('order_items', null, null, null, null, 'item_order', true);

        //$todos = $this->get();
        $str = "<div id=\"list\"><div id=\"response\"></div>";
        $str.= "<ul id=\"sort_items\">\n";
        foreach ($items as $key => $val){
            $str.= "<li id = \"arrayorder_$val[id]\">$val[item_name] $val[item_order]";
            $str.= "</li><div class=\"clear\"></div>";
        }
        $str.= "</ul></div>\n";
        echo $str;
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
                    view_form_errors(order::$errors);
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