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
function block_order_text(){

    $base_info = <<<EOT
<hr /><b>JMS & Co.</b>
Valbygårdsvej 8
2500 Valby
Danmark
<b>Telefon:</b>
31682307
<b>Email:</b> <a href="mailto:mail@mandlen.dk">mailto:mail@mandlen.dk</a>
<b>CVR:</b>
29 35 56 49
<b>Jarl & Marianne Schacht</b>
EOT;

    $base_info = nl2br($base_info);
    $str = "<div class=\"block\"><ul class=\"ul_no_style\"><li>$base_info</li></ul></div>\n";
    return $str;
}


