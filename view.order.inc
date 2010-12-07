<?php

class orderView {


    // {{{ displayConfirmOrder ()
    public static function detailsEmail (){

        if (!isset($_COOKIE['order_items'])){
            //print lang::translate('No Items in basket');
            return 0;
        }
        $order_items = cart::getBasketItems();
        if (empty($order_items)){
            print lang::translate('No Items in basket');
            return;
        }

        print lang::translate("order_details") . "\n\n";

        $total = $sub_total = 0;
        foreach ($order_items as $key => $val){
            if ($val == 0) continue;
            $item = cart::getItem($key);
            if (empty($item)) {
                unset($order_items[$key]);
                continue;
            }

            print $item['item_name'] . " ";
            print lang::translate('locale.amount') . ': ' . $item['price'];
            print " * " . $val;
            //print lang::translate('locale.amount') . ' ';
            $sub_total = $val * $item['price'];
            print " = " . lang::translate('locale.amount') . " " . $sub_total . "\n";
            $total = $sub_total + $total;


        }

        print lang::translate('amount_total');
        print ' = ';
        print lang::translate('locale.amount') . " " . $total . "\n";

        print lang::translate('amount_value_added_tax');
        print ' = ';
        print lang::translate('locale.amount') . ' ';
        print $total * get_module_ini('value_added_tax') . "\n";
        print lang::translate('amount_added_shipping_cost') . "\n\n";
    }
    // }}}
    // {{{ displayConfirmOrder ()
    public static function confirmOrder (){
        if (!isset($_COOKIE['order_items'])){
            print lang::translate('No Items in basket');
            return;
        }
        $order_items = cart::getBasketItems();
        if (empty($order_items)){
            print lang::translate('No Items in basket');
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
        print lang::translate('Quantity');
        print "</td><td>\n";
        print lang::translate('sub_total');
        print "</td><td>\n";
        print lang::translate('amount_total');
        print "</td>";
        print "</tr>\n";

        $total = $sub_total = 0;
        foreach ($order_items as $key => $val){
            if ($val == 0) continue;
            $item = cart::getItem($key);
            if (empty($item)) {
                unset($order_items[$key]);
                continue;
            }

            $options = array ();
            $options['alt'] = $val['item_name_alt'];
            $options['width'] = get_module_ini('cart_image_size_thumb');
            
            print "<tr>\n";
            print "<td>";
            if (!empty($item['file'])){
                print $link = create_image_link("/order/item/$item[id]", "/order/download/$item[id]", $options);
            }

            
            print "</td>";
            print "<td>";
            print $link = create_link("/order/item/$key/" . urlencode ($item['item_name']) , $item['item_name']) . "<br />\n";
            print lang::translate('locale.amount') . ': ' . $item['price']; // . "<br />";
            print "</td><td>\n";
            print $val;
            print "</td><td>\n";
            print lang::translate('locale.amount') . ' ';
            $sub_total = $val * $item['price'];
            print $sub_total;
            $total = $sub_total + $total;
            print "</td>\n";
            print "<td>&nbsp;</td>";
            print "</tr>\n";
        }
        print "<tr>\n";
        print "<td colspan=\"3\">" . lang::translate('amount_total');
        print "</td>";
        print "<td>&nbsp;</td>\n";
        print "<td>";

        print lang::translate('locale.amount') . ' ';
        print $total;
        print "</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td colspan=\"4\">" . lang::translate('amount_value_added_tax');
        print "</td>";
        print "<td>";
        print lang::translate('locale.amount') . ' ';
        print $total * get_module_ini('value_added_tax');
        print "</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td  colspan=5>" . lang::translate('amount_added_shipping_cost') . "</td>\n";
        print "</tr>\n";
        print "<table>\n";
    }
    // }}}
    // {{{ displayBasket ()
    public static function basket (){
        if (!isset($_COOKIE['order_items'])){
            print lang::translate('No Items in basket');
            return;
        }
        $order_items = cart::getBasketItems();
        if (empty($order_items)){
            print lang::translate('No Items in basket');
            return;
        }

        print "<table class=\"order_cart\">\n";
        print "<tr>";
        print "<td colspan=\"2\"></td>\n";
        print "<td>";
        print lang::translate('Quantity');
        print "</td>";
        print "<td>\n";
        print lang::translate('sub_total');
        print "</td>";
        print "<td>\n";
        print lang::translate('amount_total');
        print "</td>";
        print "<td>&nbsp;</td>";
        //print "<td>&nbsp;</td>";
        print "</tr>\n";
        $total = $sub_total = 0;
        foreach ($order_items as $key => $val){
            if ($val == 0) continue;
            $item = cart::getItem($key);
            if (empty($item)) {
                unset($order_items[$key]);
                continue;
            }
            print "<tr>\n";
            print "<td>";

            $options = array ();
            $options['alt'] = $val['item_name_alt'];
            $options['width'] = get_module_ini('cart_image_size_thumb');

            if (!empty($item['file'])){
                print $link = create_image_link("/order/item/$key", "/order/download/$key", $options);
            } else {
                print "&nbsp;";
            }
            print "</td>";
            print "<td>";
            print $link = create_link("/order/item/$key/" . urlencode ($item['item_name']) , $item['item_name']) . "<br />\n";
            print lang::translate('locale.amount') . ': ' . $item['price']; // . "<br />";
            print "</td><td>\n";
            print "<form name=\"checkout\" method =\"post\" action=\"\">";
            print "<input type=\"hidden\" name = \"item_id\" value =\"$item[id]\" />";
            print "<input type=\"text\" name=\"add_order\" size =\"2\" maxlength=\"2\" value=\"$val\" />";// . "<br />";
            print "<input class=\"order_cart\" type =\"submit\" name=\"item_update\" value=\"" . lang::translate('Update') . "\" /> ";
            print "</form>\n";
            print "</td><td>\n";
            print lang::translate('locale.amount') . '';
            $sub_total = $val * $item['price'];
            print $sub_total;
            $total = $sub_total + $total;
            print "</td>\n";
            print "<td>&nbsp;</td>";
            print "<td>&nbsp;</td>\n";
            //print "<td>&nbsp;</td>\n";
            print "</tr>\n";

        }
        print "<tr>\n";
        print "<td colspan=\"4\">" . lang::translate('amount_total');
        print "</td>";
        //print "<td>&nbsp;</td>\n";
        print "<td>";
        print lang::translate('locale.amount') . ' ';
        print $total;
        print "</td>\n";
        print "<td>&nbsp;</td>\n";
        //print "<td>&nbsp;</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td colspan=\"4\">" . lang::translate('amount_value_added_tax');
        print "</td>";
        //print "<td>&nbsp;</td>\n";
        print "<td>";
        print lang::translate('locale.amount') . ' ';
        print $total * get_module_ini('value_added_tax');
        print "</td>\n";
        print "<td>&nbsp;</td>\n";
        //print "<td>&nbsp;</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td colspan=6>" . lang::translate('amount_added_shipping_cost') . "</td>\n";
        //print "<td>&nbsp;</td>";
        print "</tr>\n";
        //print "<td>&nbsp;</td>";
        //print "<td>&nbsp;</td>";
        print "<td colspan=5>";
        print "&nbsp;";
        print "</td>";
        print "<td>";
        print "<form name=\"checkout\" method =\"get\" action=\"/order/checkout\">\n";
        print "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('Buy') . "\" /> ";
        print "</form>\n";
        print "</td>\n";
        //print "<td>&nbsp;</td>";
        //print "<td>&nbsp;</td>";
        print "</tr>\n";
        print "<table>\n";
    }
    // }}}
    // {{{ displayBasket ()
    public static function quickBasket (){
        
        $order_items = cart::getBasketItems();
              
        print "<table class=\"order_cart\">\n";
        print "<tr>";
        print "<td colspan=\"2\"></td>\n";
        print "<td>";
        print lang::translate('Quantity');
        print "</td>";
        print "<td>\n";
        print lang::translate('sub_total');
        print "</td>";
        print "<td>\n";
        print lang::translate('amount_total');
        print "</td>";
        print "<td>&nbsp;</td>";
        //print "<td>&nbsp;</td>";
        print "</tr>\n";
        $total = $sub_total = 0;
        $all_items = cart::getItemsInBlock();

        foreach ($all_items as $key => $val){

            $item = cart::getItem($val['id']);

            if (isset($order_items[$item['id']])){
                $val = $order_items[$item['id']];
            } else {
                $val = 0;
            }
            print "<tr>\n";
            print "<td>";

            $options = array ();
            $options['alt'] = $val['item_name_alt'];
            $options['width'] = get_module_ini('cart_image_size_thumb');

            if (!empty($item['file'])){
                print $link = create_image_link("/order/item/$item[id]", "/order/download/$item[id]", $options);
            }
            print "</td>";
            print "<td>";
            print $link = create_link("/order/item/$item[id]/" . urlencode ($item['item_name']) , $item['item_name']) . "<br />\n";
            print lang::translate('locale.amount') . ': ' . $item['price']; // . "<br />";
            print "</td><td>\n";
            print "<form name=\"checkout\" method =\"post\" action=\"\">";
            print "<input type=\"hidden\" name = \"item_id\" value =\"$item[id]\" />";
            print "<input type=\"text\" name=\"add_order\" size =\"2\" maxlength=\"2\" value=\"$val\" />";// . "<br />";
            print "<input class=\"order_cart\" type =\"submit\" name=\"item_update\" value=\"" . lang::translate('Update') . "\" /> ";
            print "</form>\n";
            print "</td><td>\n";
            print lang::translate('locale.amount') . ' ';
            $sub_total = $val * $item['price'];
            print $sub_total;
            $total = $sub_total + $total;
            print "</td>\n";
            print "<td>&nbsp;</td>";
            print "<td>&nbsp;</td>\n";
            print "</tr>\n";

        }
        print "<tr>\n";
        print "<td colspan=\"4\">" . lang::translate('amount_total');
        print "</td>";
        //print "<td>&nbsp;</td>\n";
        print "<td>";
        print lang::translate('locale.amount') . ' ';
        print $total;
        print "</td>\n";
        print "<td>&nbsp;</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td colspan=\"4\">" . lang::translate('amount_value_added_tax');
        print "</td>";
        print "<td>";
        print lang::translate('locale.amount') . ' ';
        print $total * get_module_ini('value_added_tax');
        print "</td>\n";
        print "<td>&nbsp;</td>\n";
        print "</tr>\n";

        print "<tr>\n";
        print "<td colspan=\"6\">" . lang::translate('amount_added_shipping_cost') . "</td>\n";
        //print "<td>&nbsp;</td>";
        print "</tr>\n";
        print "<tr>\n";
        print "<td colspan=\"5\">";
        print "&nbsp;</td>";
        print "<td>";
        print "<form name=\"checkout\" method =\"get\" action=\"/order/checkout\">\n";
        print "<input class=\"order_cart\" type =\"submit\" name=\"order_submit\" value=\"" . lang::translate('Buy') . "\" /> ";
        print "</form>\n";
        print "</td>\n";
        print "</tr>\n";
        
        print "<table>\n";
    }
    // }}}
}
