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
    $smiley = "http://www.findsmiley.dk/da-DK/Searching/TableSearch.htm?searchtype=all&amp;searchstring=jms&amp;vtype=detail&amp;mode=simple&amp;display=table&amp;dato1=&amp;dato2=&amp;SearchExact=false&amp;mapNElng=&amp;mapNElat=&amp;mapSWlng=&amp;mapSWlat=&amp;sort=0&amp;virk=";
    $options['width'] = 125;
    $options['alt'] = 'Dansk økologi mærke';
    $str = '';
    $str.= create_image("/templates/mandlen/new_eco_dk.jpeg", $options);
    $str.='<br />';

    $options['alt'] = 'EU økologi mærke';
    $options['width'] = 100;
    $str.= create_image("/templates/mandlen/euorganiclogo3.jpg", $options);
    $str.= "<br />";

    $options['alt'] = 'Se kontrol raport';
    $options['width'] = 100;
    $str.= html::createHrefImage($smiley, "/templates/mandlen/kr.gif", $options);
    $str.= "<br /><br />\n";

    $str = "<div class=\"block\"><ul class=\"ul_no_style\"><li>$str</li></ul></div>\n";
    return $str;
}


