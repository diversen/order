<?php


foreach ($vars->titles as $key => $val) {
    //echo "<td>$val</td>\n";
    //echo $vars->titles[$key];
    echo html::hiddenClean($val, $vars->selected[$key]);
    
}




