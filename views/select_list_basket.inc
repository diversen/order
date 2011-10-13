<?php

//print_r($vars);
foreach ($vars->titles as $key => $val) {
    //echo "<td>$val</td>\n";
    //echo $vars->titles[$key];
    echo html::hiddenClean("select[$val]", $vars->selected[$key]);
    
}
