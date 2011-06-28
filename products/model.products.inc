<?php


include_model ("order");

class orderProducts extends order {

    public function displaySortItems(){

        $todos = $this->selectAll('order_items');
        //$otods = $this->select();
        $todos = $this->selectAll('order_items', null, null, null, null, 'weight', true);
        //$todos = $this->get();
        $str = "<div id=\"list\"><div id=\"response\"></div>";
        $str.= "<ul id=\"sort_items\">\n";
        foreach ($todos as $key => $value){
            $str.= "<li id = \"arrayorder_$value[id]\">$value[item_name_alt]";
            //$str.= create_link("/todo/delete/$value[id]", lang::translate('Delete')) . "";
            $str.= "</li><div class=\"clear\"></div>";
        }
        $str.= "</ul></div>\n";
        print $str;
    }
}