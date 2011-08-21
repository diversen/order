<style type="text/css">
#order_category_list ul {
	padding:0px;
	margin: 0px;
        margin-left:0px;
        list-style:none
}
#response {
	margin-bottom:5px;
}
#order_category_list li {
        margin-left:0px;
	margin: 0 0 3px;
	background-color:#aaa;
	color:#fff;
	list-style: none;
}
</style>
<?php

if (!session::checkAccessControl('order_allow')){
    return;
}

$sort = new orderCategory();
$sort->displaySortItems();

?>
