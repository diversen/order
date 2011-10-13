<?php


$message = "Vælg betalingsform";
headline_message($message);
echo "<ul>\n";
foreach ($vars as $key => $val) {
    echo "<li>\n";
    $class = moduleLoader::modulePathToClassName($val);
    
    if (class_exists($class)) {
        echo $class::displayMethodLink();
    }
    echo "</li>\n";
}

echo "</ul>\n";