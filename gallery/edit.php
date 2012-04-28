<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

$item_id = URI::getInstance()->fragment(3);
templateView::includeModuleView('order/products', 'admin_menu', array('id' => $item_id));
gallery::viewGallery(3, 4, array ('no_redirect' => true));
//orderGallery::updateGalleryControl(3);