<?php

$str = lang::translate('order_process_confirm_message') . "<br /><br />";
$str.= lang::translate('order_process_greetings') . " $_SERVER[SERVER_NAME]";

echo $str;

//$_SESSION['order_done'] = 1;
//session::setActionMessage($str);
//header("Location: /order/cart");