<?php


include_module ('order');
// this file check which selects has been set. 

// get parent selects connected to item_id
$selects = orderSelect::getSelects($_REQUEST['item_id']);


print_r($_REQUEST);
//print_r($selects);

$selects_submitted = array();
foreach ($_REQUEST['select'] as $key => $value) {
    if ($value != '0') {
        $selects_submitted[] = $key;                    
    }
}
            
// find out which selects has been submitted
// out of those hold in selects array

foreach ($selects as $key => $val) {
    //print_r($val);
    if (in_array($val['title'], $selects_submitted))  {                    
        $selects[$key]['selected'] = $_REQUEST['select'][$val['title']];
    }
}

//print_r($selects);

foreach($selects as $key => $val) {

    $childs = orderSelect::getSelectChilds($val['id']);
    if (empty($childs->allChildOptions)) {
        echo "no child options";
    } else {
        //print_r($childs);
        $title = $childs->mainChildSelects['title'];
        if (isset($selects[$key]['selected'])) {
            $selected = $selects[$key]['selected'];
        } else {
            $selected = 0; 
        }
        $select_child_options = $childs->allChildOptions[$selected];
        //print_r($select_child_options);
        echo html::selectClean("select[$title]", $select_child_options, 'title', 'value', '0', '');
        //find out which array to get child selects from                   
    }         
}
die;

//$_SESSION['order_selects_command']
