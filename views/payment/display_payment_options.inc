<?php


$message = lang::translate('order_payment_select_payment_option');
headline_message($message);
echo "<ul>\n";
foreach ($vars as $key => $val) {
    echo "<li>\n";
    echo $class = moduleLoader::modulePathToClassName($val);
    
    if (class_exists($class)) {
        echo $class::displayMethodLink();
    }
    echo "</li>\n";
}

echo "</ul>\n";
