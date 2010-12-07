<?php

function str_replace_ary ($from, $to, $ary){
    foreach ($ary as $key => $val){
        $ary[$key] = str_replace($from, $to, $val);
    }
    return $ary;
}

$_POST = str_replace_ary('&amp;', '&', $_POST);

?>
<?=lang::translate('invoice_details')?>: 

<?=lang::translate('company')?>: <?=@$_POST['company']?>

<?=lang::translate('name')?>: <?=@$_POST['name']?>

<?=lang::translate('adresse')?>: <?=@$_POST['adresse']?>

<?=lang::translate('postal_code')?>: <?=@$_POST['postal_code']?>

<?=lang::translate('city')?>: <?=@$_POST['city']?>

<?=lang::translate('email')?>: <?=@$_POST['email']?>

<?=lang::translate('phone')?>: <?=@$_POST['phone']?>
<?php if (isset($_POST['checkme'])){ ?>


<?=lang::translate('diffent_shipping')?>: 

<?=lang::translate('name')?>: <?=@$_POST['diff_name']?>

<?=lang::translate('adresse')?>: <?=@$_POST['diff_adresse']?>

<?=lang::translate('postal_code')?>: <?=@$_POST['diff_postal_code']?>

<?=lang::translate('city')?>: <?=@$_POST['diff_city']?>
<?php

}