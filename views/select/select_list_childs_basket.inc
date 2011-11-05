<?php

$name = $vars->mainChildSelects['title'];
echo "&nbsp;$name: ";
echo "<select id=\"$name\" name=\"select[$name]\">\n";
echo "<option value=\"\">--</option>\n";
foreach ($vars->parentOptions as $key => $val) {
    $class = $val['value'];
    //echo "$val: ";
    
    foreach ($vars->allChildOptions[$key] as $child) {
        echo "<option value=\"$child[value]\" class=\"$class\">$child[title]</option>\n";
    }
}
echo "</select>\n";
echo "<script>\n"; 
echo "\$(\"#$name\").chained(\"#mark\");";
echo "</script>";