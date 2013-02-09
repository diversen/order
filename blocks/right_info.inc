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
    $str.='<br />';

    $options['width'] = 100;
    $str.= create_image("/templates/mandlen/euorganiclogo3.jpg", $options);
    $str.= "<br />";

    $options['width'] = 100;
    $str.= html::createHrefImage($smiley, "/templates/mandlen/kr.gif", $options);
    $str.= "<br />\n";

    $info = '<hr />';

$g_plus_one = <<<EOT
<script type="text/javascript" src="http://s7.addthis.com/js/250/addthis_widget.js#pubid=xa-4d9cb75f1ea03ef5"></script>
<!-- AddThis Button END -->
<!-- Place this tag in your head or just before your close body tag -->
<script type="text/javascript" src="https://apis.google.com/js/plusone.js"></script>
<!-- Place this tag where you want the +1 button to render -->
<g:plusone size="small"></g:plusone>
EOT;
    $info.=trim($g_plus_one) ."<br />\n";
    $fb_share = <<<EOT
<a name="fb_share" type="button_count" href="http://www.facebook.com/sharer.php">Del</a><script src="http://static.ak.fbcdn.net/connect.php/js/FB.Share" type="text/javascript"></script>
EOT;

    $info.=$fb_share;

        $fb_link = <<<EOT
<iframe src="http://www.facebook.com/plugins/likebox.php?href=http%3A%2F%2Fwww.facebook.com%2Fmandlen&amp;width=175&amp;colorscheme=light&amp;show_faces=false&amp;border_color&amp;stream=false&amp;header=false&amp;height=62" scrolling="no" frameborder="0" style="border:none; overflow:hidden; width:175px; height:62px;" allowTransparency="true"></iframe>
EOT;

    $info.=$fb_link . "<hr />\n";

    
    /*
    $info.= <<<EOT
<form action="http://www.facebook.com/addfriend.php"><input type="hidden" name="id" value="178272478878935" /><input type="submit" value="Connect with me on Facebook!" /></form>
EOT;
     
     
    $info.= "<br />\n";
*/
    $base_info = <<<EOT
<b>JMS & Co.</b>
Valbygårdsvej 8
2500 Valby
Danmark<hr /><b>Telefon:</b>
31682307
<b>Email:</b> mail@mandlen.dk
<b>CVR:</b>
29 35 56 49<hr />Jarl & Marianne Schacht
EOT;
    $base_info = nl2br($base_info);
    $str.=$info;
    $str.= $base_info;
    return $str;
}


