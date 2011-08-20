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
function block_order_share(){
    $info = '';
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

    $info.= $fb_link;
    
    return $info;
}


