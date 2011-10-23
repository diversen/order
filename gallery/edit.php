<?php

$item_id = URI::getInstance()->fragment(3);
templateView::includeModuleView('order/products', 'admin_menu', array('id' => $item_id));
gallery::viewGallery(3, 4);
//orderGallery::updateGalleryControl(3);