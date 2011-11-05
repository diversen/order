<?php

$str ='';

foreach ($vars->titles as $key => $val) {
    if (!isset($vars->displayEmail)) {
        $str.="<br />\n";
    } else {
        $str.= " ";
    }

    $str.=$vars->selectedHuman[$key];
}

if (isset($vars->displayEmail) && !empty($str)) {
    $str = " ($str) ";
}

echo $str;