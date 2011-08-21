<?php

/**
 * block file is used for showing content categories
 *
 * @package content
 */

/**
 * function for showing a category block
 *
 * @return string   category block as html
 */
function block_order_images(){
    $smiley = "http://www.findsmiley.dk/da-DK/Searching/TableSearch.htm?searchtype=all&searchstring=jms&vtype=detail&mode=simple&display=table&dato1=&dato2=&SearchExact=false&mapNElng=&mapNElat=&mapSWlng=&mapSWlat=&sort=0&virk=";
    $options['width'] = 125;
    $str = '';
    $str.= create_image("/templates/mandlen/new_eco_dk.jpeg", $options);
    $str.='<br />';

    $options['width'] = 100;
    $str.= create_image("/templates/mandlen/euorganiclogo3.jpg", $options);
    $str.= "<br />";

    $options['width'] = 100;
    $str.= create_image_link($smiley, "/templates/mandlen/kr.gif", $options);
    $str.= "<br /><br />\n";

    $str = "<div class=\"block\"><ul class=\"ul_no_style\"><li>$str</li></ul></div>\n";
    return $str;
}


