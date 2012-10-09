<?php

$str = lang::translate('order_paypal_process_confirm_message') . "<br /><br />";
$str.= lang::translate('order_process_greetings') . " $_SERVER[SERVER_NAME]";

echo $str;