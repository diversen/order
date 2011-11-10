<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

orderSelect::updateSelectControl();
