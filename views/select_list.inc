<?php

foreach ($vars->titles as $key => $val) {
    //echo "<tr>\n";
    //echo "<td>\n";
    echo "$val: ";
    //echo "</td>\n";
    //echo "<td>\n";
    //echo "<form method=\"post\" action=\"/order/select/set_selects\">\n";
    $extra = array (/*'onchange'=> "this.form.submit()", */"id" => 'mark');
    $init = array ('value' => 0, 'title' => 'Vælg');
    echo html::selectClean("select[$val]", $vars->options[$key], 'title', 'value', $vars->selected[$key], $extra, $init);
    
    
    
    //echo "</form>\n";
    //echo "</td>\n";
    //echo "</tr>\n";
}