<?php

class orderView {

    // {{{ displayConfirmOrder ()
    public static function detailsEmail (){

        if (!isset($_COOKIE['order_items'])){
            return 0;
        }
        $order_items = order::getBasketItems();
        if (empty($order_items)){
            print lang::translate('order_no_items_in_basket');
            return;
        }

        print lang::translate('order_order_details');
        print "\n\n";

        $total = $sub_total = 0;
        foreach ($order_items as $key => $val){
            if ($val == 0) continue;
            $item = order::getItem($key);
            if (empty($item)) {
                unset($order_items[$key]);
                continue;
            }

            print $item['item_name'] . " ";
            print order::getCurrencySymbol() . ': ' . $item['price'];
            print " * " . $val;

            $sub_total = $val * $item['price'];
            print " = " . order::getCurrencySymbol() . " " . $sub_total . "\n";
            $total = $sub_total + $total;
        }

        print lang::translate('order_amount_total');
        print ' = ';
        print order::getCurrencySymbol() . " " . $total . "\n";

        print lang::translate('order_amount_value_added_tax');
        print ' = ';
        print order::getCurrencySymbol() . ' ';
        print $total * get_module_ini('order_added_tax') . "\n";
        print lang::translate('order_amount_added_shipping_cost') . "\n\n";
    }
    // }}}
    // {{{ displayConfirmOrder ()
    public static function confirmOrder (){
        if (!isset($_COOKIE['order_items'])){
            print lang::translate('order_no_items_in_basket');
            return;
        }
        $order_items = order::getBasketItems();
        if (empty($order_items)){
            print lang::translate('order_no_items_in_basket');
            return;
        }

        print "<table class=\"order_cart\">\n";
        print "<tr>";
        print "<td colspan=\"5\">\n";
        print "<h3>" . lang::translate("order_details") . "</h3>\n";
        print "</td>\n";
        print "</tr>\n";

        print "<tr>";
        print "<td colspan=\"2\">";
        print "</td><td>\n";
        print lang::translate('order_quantity');
        print "</td><td>\n";
        print lang::translate('order_sub_total');
        print "</td><td>\n";
        print lang::translate('order_amount_total');
        print "</td>";
        print "</tr>\n";

        $total = $sub_total = 0;
        foreach ($order_items as $key => $val){
            if ($val == 0) continue;
            $item = order::getItem($key);
            if (empty($item)) {
                unset($order_items[$key]);
                continue;
            }

            $options = array ();
            $options['alt'] = $val['item_name_alt'];
            $options['width'] = get_module_ini('order_image_size_thumb');
            
            print "<tr>\n";
            print "<td>";
            if (!empty($item['file'])){
                print $link = create_image_link("/order/item/$item[id]/"  . rawurlencode($val['item_name']), "/order/download/$item[id]", $options);
            }

            
            print "</td>";
            print "<td>";
            print $link = create_link("/order/item/$key/" . rawurlencode ($item['item_name']) , $item['item_name']) . "<br />\n";
            print order::getCurrencySymbol() . ': ' . $item['price']; // . "<br />";
            print "</td><td>\n";
            print $val;
            print "</td><td>\n";
            print order::getCurrencySymbol() . ' ';
            $sub_total = $val * $item['price'];
            print $sub_total;
            $total = $sub_total + $total;
            print "</td>\n";
            print "<td>&nbsp;</td>";
            print "</tr>\n";
        }
        print "<tr>\n";
        print "<td colspan=\"3\">";
        print lang::translate('order_amount_total');
        print "</td>";
        print "<td>&nbsp;</td>\n";
        print "<td>";

        print order::getCurrencySymbol() . ' ';
        print $total;
        print "</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td colspan=\"4\">";
        print lang::translate('order_amount_value_added_tax');
        print "</td>";
        print "<td>";
        print order::getCurrencySymbol() . ' ';
        print $total * get_module_ini('order_added_tax');
        print "</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td  colspan=5>";
        print lang::translate('order_amount_added_shipping_cost');
        print "</td>\n";
        print "</tr>\n";
        print "<table>\n";
    }
    // }}}
    // {{{ displayBasket ()
    public static function basket (){
        if (!isset($_COOKIE['order_items'])){
            print lang::translate('order_no_items_in_basket');
            return;
        }
        $order_items = order::getBasketItems();
        if (empty($order_items)){
            print lang::translate('order_no_items_in_basket');
            return;
        }

        print "<table class=\"order_cart\">\n";
        print "<tr>";
        print "<td colspan=\"2\"></td>\n";
        print "<td>";
        print lang::translate('order_quantity');
        print "</td>";
        print "<td>\n";
        print lang::translate('order_sub_total');
        print "</td>";
        print "<td>\n";
        print lang::translate('order_amount_total');
        print "</td>";
        print "<td>&nbsp;</td>";
        print "</tr>\n";
        $total = $sub_total = 0;
        foreach ($order_items as $key => $val){
            if ($val == 0) continue;
            $item = order::getItem($key);
            if (empty($item)) {
                unset($order_items[$key]);
                continue;
            }
            print "<tr>\n";
            print "<td>";

            $options = array ();
            $options['alt'] = $val['item_name_alt'];
            $options['width'] = get_module_ini('order_image_size_thumb');

            if (!empty($item['file'])){
                $link = 
                    create_image_link(
                        "/order/item/$key/"  .
                        rawurlencode($item['item_name']),
                        "/order/download/$key", $options);
                print $link;

            } else {
                print "&nbsp;";
            }
            print "</td>";
            print "<td>";
            print $link = create_link("/order/item/$key/" . rawurlencode ($item['item_name']) , $item['item_name']) . "<br />\n";
            print order::getCurrencySymbol();
            print ': ' . $item['price'];
            print "</td><td>\n";
            print "<form name=\"checkout\" method =\"post\" action=\"\">";
            print "<input type=\"hidden\" name = \"item_id\" value =\"$item[id]\" />";
            print "<input type=\"text\" name=\"add_order\" size =\"2\" maxlength=\"2\" value=\"$val\" />";// . "<br />";
            print "<input class=\"order_cart\" type =\"submit\" name=\"item_update\" value=\"" . lang::translate('order_item_update') . "\" /> ";
            print "</form>\n";
            print "</td><td>\n";
            print order::getCurrencySymbol() . '';
            $sub_total = $val * $item['price'];
            $sub_total_weight = $val * $item['weight'];


            print $sub_total;
            $total = $sub_total + $total;
            $total_weight = $sub_total_weight + $total_weight;
            print "</td>\n";
            print "<td>&nbsp;</td>";
            print "<td>&nbsp;</td>\n";
            print "</tr>\n";

        }
        print "<tr>\n";
        print "<td colspan=\"4\">";
        print lang::translate('order_amount_total');
        print "</td>";
        print "<td>";
        print order::getCurrencySymbol() . ' ';
        print $total;
        print "</td>\n";
        print "<td>&nbsp;</td>\n";
        print "</tr>\n";

        /*
        print "<tr>\n";
        print "<td colspan=\"4\">";
        print lang::translate('order_amount_value_added_tax');
        print "</td>";
        print "<td>";
        print order::getCurrencySymbol() . ' ';
        //print $total * get_module_ini('order_added_tax');
        print "total vægt  = $total_weight";
        print "</td>\n";
        print "<td>&nbsp;</td>\n";
        print "</tr>\n";
            */
        print "<tr>\n";
        print "<td colspan=\"4\">";
        print lang::translate('order_amount_value_added_tax');
        print "</td>";
        print "<td>";
        print order::getCurrencySymbol() . ' ';
        print $total * get_module_ini('order_added_tax');
        print "</td>\n";
        print "<td>&nbsp;</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td colspan=\"4\">\n";
        print lang::translate('order_amount_added_shipping_cost');
        print "<br />\n";
        print lang::translate('order_shipping_basket_info');
        print "</td>\n";
        print "<td>\n";
        //print order::getCurrencySymbol() . ' ';
        //print $total * get_module_ini('order_added_tax');
        //print order::getWeightToCost($total_weight);
        
        print "</td>\n";
        print "<td>&nbsp;</td>\n";
        print "</tr>\n";
        print "</tr>\n";


        print "<td colspan=5>";
        print "&nbsp;";
        print "</td>";
        print "<td>";
        print "<form name=\"checkout\" method =\"get\" action=\"/order/checkout\">\n";
        print "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('order_buy') . "\" /> ";
        print "</form>\n";
        print "</td>\n";
        print "</tr>\n";
        print "<table>\n";
    }
    // }}}
    // {{{ displayBasket ()
    public static function quickBasket (){
        
        $order_items = order::getBasketItems();
              
        print "<table class=\"order_cart\">\n";
        print "<tr>";
        print "<td colspan=\"2\"></td>\n";
        print "<td>";
        print lang::translate('order_quantity');
        print "</td>";
        print "<td>\n";
        print lang::translate('order_sub_total');
        print "</td>";
        print "<td>\n";
        print lang::translate('order_amount_total');
        print "</td>";
        print "<td>&nbsp;</td>";
        print "</tr>\n";
        $total = $sub_total = 0;
        $all_items = order::getItemsInBlock();

        foreach ($all_items as $key => $val){

            $item = order::getItem($val['id']);

            if (isset($order_items[$item['id']])){
                $val = $order_items[$item['id']];
            } else {
                $val = 0;
            }
            print "<tr>\n";
            print "<td>";

            $options = array ();
            $options['alt'] = $val['item_name_alt'];
            $options['width'] = get_module_ini('order_image_size_thumb');

            if (!empty($item['file'])){
                $link =
                    create_image_link(
                        "/order/item/$item[id]/" . rawurlencode($item['item_name']),
                        "/order/download/$item[id]", $options);
            }
            print "</td>";
            print "<td>";
            $link = create_link(
                "/order/item/$item[id]/" . rawurlencode ($item['item_name']) ,
                $item['item_name']);
            print $link;
            print "<br />\n";
            print order::getCurrencySymbol() . ': ' . $item['price'];
            print "</td><td>\n";
            print "<form name=\"checkout\" method =\"post\" action=\"\">";
            print "<input type=\"hidden\" name = \"item_id\" value =\"$item[id]\" />";
            print "<input type=\"text\" name=\"add_order\" size =\"2\" maxlength=\"2\" value=\"$val\" />";// . "<br />";
            print "<input class=\"order_cart\" type =\"submit\" name=\"item_update\" value=\"" . lang::translate('order_item_update') . "\" /> ";
            print "</form>\n";
            print "</td><td>\n";
            print order::getCurrencySymbol() . ' ';
            $sub_total = $val * $item['price'];
            print $sub_total;
            $total = $sub_total + $total;
            print "</td>\n";
            print "<td>&nbsp;</td>";
            print "<td>&nbsp;</td>\n";
            print "</tr>\n";

        }
        print "<tr>\n";
        print "<td colspan=\"4\">";
        print lang::translate('order_amount_total');
        print "</td>";
        print "<td>";
        print order::getCurrencySymbol() . ' ';
        print $total;
        print "</td>\n";
        print "<td>&nbsp;</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td colspan=\"4\">";
        print lang::translate('order_amount_value_added_tax');
        print "</td>";
        print "<td>";
        print order::getCurrencySymbol() . ' ';
        print $total * get_module_ini('order_added_tax');
        print "</td>\n";
        print "<td>&nbsp;</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td colspan=\"6\">";
        print lang::translate('order_amount_added_shipping_cost');
        print "</td>\n";
        print "</tr>\n";
        print "<tr>\n";
        print "<td colspan=\"5\">";
        print "&nbsp;</td>";
        print "<td>";
        print "<form name=\"checkout\" method =\"get\" action=\"/order/checkout\">\n";
        print "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('order_buy') . "\" /> ";
        print "</form>\n";
        print "</td>\n";
        print "</tr>\n";
        print "<table>\n";
    }

}