<?php

if (!session::checkAccessControl('allow_edit_cart')){
    return;
}