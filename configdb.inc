<?php

$db_config = array (
    array ('name' => 'order_form_accept_text', 
           'description' => lang::translate('order_form_accept_text'),
           'type' => 'textareaSmall', 
           'value' => lang::translate('order_form_accept_text_init_value'),
           'auth' => 'admin',
            // how to display it when getting config. 
           'filters' => array ('markdown')),
);