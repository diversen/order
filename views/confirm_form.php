<form action="/order/process" method="post">

<!-- top table -->
<table class="order_cart">
<tr>
<td><h3><?=lang::translate('order_invoice_details')?></h3></td>
<?php
if (isset($_POST['checkme'])){ ?>
<td><h3><?=lang::translate('order_different_shipping')?></h3></td>
<td>&nbsp;</td>
<? } else { ?>
<td>&nbsp;</td>
<? } ?>
</tr>

<tr>

<td>
<!-- first td table -->
<table class ="order_cart">

<tr>
<td><?=lang::translate('order_company')?></td>
<td><?=@$_POST['company']?></td>
</tr>

<tr>
<td><?=lang::translate('order_name')?></td>
<td><?=@$_POST['name']?></td>
</tr>

<tr>
<td><?=lang::translate('order_adresse')?></td>
<td><?=@$_POST['adresse']?></td>
</tr>

<tr>
<td><?=lang::translate('order_postal_code')?></td>
<td><?=@$_POST['postal_code']?></td>
</tr>

<tr>
<td><?=lang::translate('order_city')?></td>
<td><?=@$_POST['city']?></td>
</tr>

<tr>
<td><?=lang::translate('order_email')?></td>
<td><?=@$_POST['email']?></td>
</tr>


<tr>
<td><?=lang::translate('order_phone')?></td>
<td><?=@$_POST['phone']?></td>
</tr>
</table>
<!-- end first table td -->

</td>

<?php

if (isset($_POST['checkme'])){ ?>

<td>

<table class="order_cart">

<tr>
<td><?=lang::translate('order_name')?></td>
<td><?=@cos_htmlspecialchars($_POST['diff_name'])?></td>
</tr>

<tr>
<td><?=lang::translate('order_adresse')?></td>
<td><?=@cos_htmlspecialchars($_POST['diff_adresse'])?></td>
</tr>

<tr>
<td><?=lang::translate('order_postal_code')?></td>
<td><?=@cos_htmlspecialchars($_POST['diff_postal_code'])?></td>
</tr>

<tr>
<td><?=lang::translate('order_city')?></td>
<td><?=@cos_htmlspecialchars($_POST['diff_city'])?></td>
</tr>
</table>

</td>

<?php

}

?>

<td>

<table class="order_cart">
<tr>
    <td><input type="submit" name="submit" value="<?=lang::translate('order_confirm_order')?>" /></td>
</tr>
</table>


</td>
</tr>
</table>
    
</form>