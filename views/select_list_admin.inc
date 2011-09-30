<?php

echo "<table>\n";
foreach ($vars->titles as $key => $val) {
    echo "<tr>\n";
    echo "<td>\n";
    echo "$val: ";
    echo "</td>\n";
    echo "<td>\n";
    echo html::selectClean($val, $vars->options[$key], 'val', 'id', $vars->selected[$key]);
    echo "</td>\n";
    echo "<td>\n";
    echo html::createLink("?method=item_delete_select&id=" . $vars->ids[$key], 'Slet');
    echo "</td>\n";
    echo "</tr>\n";
}
echo "</table>\n";




