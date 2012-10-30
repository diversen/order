<?php

//configdb::displayConfig('order');

print_r($_POST);
$f = new html();
$f->formStart();
$f->legend($legend);
$f->label('order_form_accept_text', lang::translate('order_form_accept_text'));
$f->textareaMed('order_form_accept_text');

$payment = config::getModuleIni('order_payment_modules');
//print_r($payment);
foreach ($payment as $val) {
    $f->label($val, $val);
    $f->checkbox($val);
}

$f->submit('order_config_submit', lang::translate('submit'));
$f->formEnd();
echo $f->getStr();
//$f->checkbox($name);


