<?php

function str_replace_ary ($from, $to, $ary){
    foreach ($ary as $key => $val){
        $ary[$key] = str_replace($from, $to, $val);
    }
    return $ary;
}

$_POST = str_replace_ary('&amp;', '&', $_POST);

?>
<?=lang::translate('order_invoice_details')?>:

<?=lang::translate('order_company')?>: <?=@$_POST['company']?>

<?=lang::translate('order_name')?>: <?=@$_POST['name']?>

<?=lang::translate('order_adresse')?>: <?=@$_POST['adresse']?>

<?=lang::translate('order_postal_code')?>: <?=@$_POST['postal_code']?>

<?=lang::translate('order_city')?>: <?=@$_POST['city']?>

<?=lang::translate('order_email')?>: <?=@$_POST['email']?>

<?=lang::translate('order_phone')?>: <?=@$_POST['phone']?>
<?php if (isset($_POST['checkme'])){ ?>


<?=lang::translate('order_diffent_shipping')?>:

<?=lang::translate('order_name')?>: <?=@$_POST['diff_name']?>

<?=lang::translate('order_adresse')?>: <?=@$_POST['diff_adresse']?>

<?=lang::translate('order_postal_code')?>: <?=@$_POST['diff_postal_code']?>

<?=lang::translate('order_city')?>: <?=@$_POST['diff_city']?>
<?php

}