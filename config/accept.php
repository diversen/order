<?php

$text = get_module_ini('order_form_accept_text');
$filters = get_module_ini('order_filters');
echo get_filtered_content($filters, $text);
