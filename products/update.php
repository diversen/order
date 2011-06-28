<?php

/**
 * view file for editing event
 *
 * @package    event
 */
if (!session::checkAccessControl('allow_edit_cart')){
    return;
}

$array	= $_POST['arrayorder'];

if ($_POST['update'] == "update"){
    $db = new db();
    $count = 1;
    foreach ($array as $key => $val) {
        $values = array('weight' => $key);
        $db->update('order_items', $values, $val);
        $count++;
    }
    echo lang::translate('Order saved');
}

die;