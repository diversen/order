<?php

foreach ($vars->titles as $key => $val) {
    echo "<tr>\n";
    echo "<td>\n";
    echo "$val: ";
    echo "</td>\n";
    echo "<td>\n";
    echo html::selectClean($val, $vars->options[$key], 'title', 'value', $vars->selected[$key]);
    echo "</td>\n";
    echo "</tr>\n";
}