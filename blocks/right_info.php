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
function block_right_info(){
    $smiley = "http://www.findsmiley.dk/da-DK/Searching/TableSearch.htm?searchtype=all&searchstring=jms&vtype=detail&mode=simple&display=table&dato1=&dato2=&SearchExact=false&mapNElng=&mapNElat=&mapSWlng=&mapSWlat=&sort=0&virk=";
    $options['width'] = 70;
    $str = '';
    $str.= create_image("/templates/mandlen/oko.png", $options);

    $options['width'] = 100;
    $str.= create_image_link($smiley, "/templates/mandlen/kr.gif", $options);

    $info = '<hr />';
    $fb_share = <<<EOT
<a name="fb_share" type="button_count" href="http://www.facebook.com/sharer.php">Del</a><script src="http://static.ak.fbcdn.net/connect.php/js/FB.Share" type="text/javascript"></script>
EOT;

    $info.=$fb_share ."<hr />";
    /*
    $info.= <<<EOT
<form action="http://www.facebook.com/addfriend.php"><input type="hidden" name="id" value="178272478878935" /><input type="submit" value="Connect with me on Facebook!" /></form>
EOT;
     
     
    $info.= "<br />\n";
*/
    $info.= <<<EOT
<b>JMS & Co.</b>
Valbygårdsvej 8
2500 Valby
Danmark<hr /><b>Telefon:</b>
31682307
<b>Email:</b> mail@mandlen.dk
<b>CVR:</b>
29 35 56 49<hr />Jarl & Marianne Schacht
EOT;
    $info = nl2br($info);

    $str.= $info;
    return $str;
}


