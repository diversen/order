<?php

/**
 * view file for editing event
 *
 * @package    event
 */
if (!session::checkAccessControl('order_allow')){
    return;
}

//simple_prg();
order::updateItemControl();

$use_gallery = get_module_ini('order_use_gallery');
if (isset($use_gallery)) {
    include_model('order/gallery');
    orderGallery::updateGalleryControl();
}

$use_select = get_module_ini('order_use_gallery');
if (isset($use_select)) {
    include_model('order/select');
    orderSelect::updateSelectControl();
}

