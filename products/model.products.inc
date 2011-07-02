<?php

include_model ("order");

class orderProducts extends order {

    public function displaySortItems(){

        //$todos = $this->selectAll('order_items');
        //$otods = $this->select();
        $items = $this->selectAll('order_items', null, null, null, null, 'item_order', true);

        //$todos = $this->get();
        $str = "<div id=\"list\"><div id=\"response\"></div>";
        $str.= "<ul id=\"sort_items\">\n";
        foreach ($items as $key => $val){
            $str.= "<li id = \"arrayorder_$val[id]\">$val[item_name_alt] $val[item_order]";
            $str.= "</li><div class=\"clear\"></div>";
        }
        $str.= "</ul></div>\n";
        print $str;
    }
}