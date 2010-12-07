<?php

if (isset($_POST['checkme'])){
    $checked = 'checked ="yes"';
}

?>
<form action="/order/checkout" method="post" id="order_form">
<table class="checkout">
<tr>
    <td><?=lang::translate('checkout_legend')?></td>
    <td>&nbsp;</td>
</tr>

<tr>
    <td><?=lang::translate('company')?></td>
    <td><input type="text" name="company" size="30" value="<?=@$_POST['company']?>" class="required" /></td>
    <td class="status"></td>
</tr>
<tr>
    <td>* <?=lang::translate('name')?></td>
    <td><input type="text" name="name" size="30" value="<?=@$_POST['name']?>" class="required" /></td>
    <td class="status"></td>
</tr>

<tr>
<td>* <?=lang::translate('adresse')?></td>
<td><input type="text" name="adresse" size="30" value="<?=@$_POST['adresse']?>" /></td>
<td class="status"></td>
</tr>

<tr>
<td>* <?=lang::translate('postal_code')?></td>
<td><input type="text" name="postal_code"  size="3" MAXLENGTH="4" value="<?=@$_POST['postal_code']?>" /></td>
<td class="status"></td>
</tr>

<tr>
<td>* <?=lang::translate('city')?></td>
<td><input type="text" name="city" size="30" value="<?=@$_POST['city']?>" /></td>
<td class="status"></td>
</tr>

<tr>
    <td>* <?=lang::translate('email')?></td>
    <td><input type="text" name="email" size="30" value="<?=@$_POST['email']?>" /></td>
    <td class="status"></td>
</tr>

<tr>
    <td><?=lang::translate('phone')?></td>
    <td><input type="text" name="phone" size="10" value="<?=@$_POST['phone']?>" /></td>
    <td class="status"></td>
</tr>

<!-- optional start -->

<tr>
    <td><?=lang::translate('diffent_shipping')?></td>
    <td><input id="checkme" type="checkbox" name="checkme" value="1" <?=@$checked?> /></td>
    <td>&nbsp;</td>
</tr>
</table>

<table id="extra" class="checkout">
<tr>
    <td>* <?=lang::translate('name')?></td>
    <td><input type="text" name="diff_name" size="30" value="<?=@$_POST['diff_name']?>" /></td>
    <td class="status"></td>
</tr>

<tr>
    <td>* <?=lang::translate('adresse')?></td>
    <td><input type="text" name="diff_adresse" size="30" value="<?=@$_POST['diff_adresse']?>" /></td>
    <td class="status"></td>
</tr>

<tr>
    <td>* <?=lang::translate('postal_code')?></td>
    <td><input type="text" name="diff_postal_code" size="3" MAXLENGTH="4" value="<?=@$_POST['diff_postal_code']?>" /></td>
    <td class="status"></td>
</tr>

<tr>
    <td>* <?=lang::translate('city')?></td>
    <td><input type="text" name="diff_city" size="30" value="<?=@cos_htmlspecialchars($_POST['diff_city'])?>" /></td>
    <td class="status"></td>
</tr>

</table>

<table class="checkout">
    <tr>
    <td>&nbsp;</td>
    <td><input type="submit" name="submit" value="<?=lang::translate('add_order')?>" /></td>
    </tr>
</table>

</form>
