<?php


foreach ($vars->titles as $key => $val) {
    //echo "<td>$val</td>\n";
    echo "$val: $val";
    echo html::hiddenClean($val, $vars->selected[$key]);
    
}




