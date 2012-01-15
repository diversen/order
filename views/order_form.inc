<?php

if (isset($_POST['checkme'])){
    $checked = 'checked ="yes"';
}

headline_message(lang::translate('order_checkout_legend'))
        
?>
<form action="" method="post" id="order_form">


<table class="checkout">

<tr>
    <td colspan="2"><?=lang::translate('order_legend_company')?></td>
</tr>
<tr>
 
    <td><input type="text" name="company" size="30" value="<?=@$_POST['company']?>" class="required" /></td>
    <td class="status"></td>
</tr>
<tr>
    <td colspan="2">* <?=lang::translate('order_legend_name')?></td>
</tr>
<tr>
    <td><input type="text" name="name" size="30" value="<?=@$_POST['name']?>" class="required" /></td>
    <td colspan="2" class="status"></td>
</tr>

<tr>
<td colspan="2">* <?=lang::translate('order_legend_adresse')?></td>
</tr>
<tr>
<td><input type="text" name="adresse" size="30" value="<?=@$_POST['adresse']?>" /></td>
<td class="status"></td>
</tr>

<tr>
<td colspan="2">* <?=lang::translate('order_legend_postal_code')?></td>
</tr>
<tr>
<td><input type="text" name="postal_code"  size="3" MAXLENGTH="4" value="<?=@$_POST['postal_code']?>" /></td>
<td class="status"></td>
</tr>

<tr>
<td colspan="2">* <?=lang::translate('order_legend_city')?></td>
</tr>
<tr>
<td><input type="text" name="city" size="30" value="<?=@$_POST['city']?>" /></td>
<td class="status"></td>
</tr>
<?php

if (get_module_ini('order_use_country')) { 
    
    $countries = orderHelpers::getCountriesForDropDown();
    $country_dropdown = html::selectClean('country', $countries, 'name', 'id', @$_POST['country'], null, @$_POST['country']);
    //$region_input = html::textClean('region', @$_POST['region']);   
    
    ?>

<tr>
<td colspan="2">* <?=lang::translate('order_legend_country')?></td>
</tr>
<tr>
<td><?=$country_dropdown?></td>
<td class="status"></td>
</tr>

<tr>
    <td colspan="2">* <?=lang::translate('order_legend_region')?></td>
</tr>
<tr>
    <td><input type="text" name="region" size="30" value="<?=@$_POST['region']?>" /></td>
    <td class="status"></td>
</tr>

<? } ?>

<tr>
    <td colspan="2">* <?=lang::translate('order_legend_email')?></td>
</tr>
<tr>
    <td><input type="text" name="email" size="30" value="<?=@$_POST['email']?>" /></td>
    <td class="status"></td>
</tr>

<tr>
<td colspan="2"><?=lang::translate('order_legend_phone')?></td>
</tr>
<tr>
    <td><input type="text" name="phone" size="10" value="<?=@$_POST['phone']?>" /></td>
    <td class="status"></td>
</tr>



<!-- optional start -->

<tr>
    <td colspan="2"><?=lang::translate('order_legend_diffent_shipping')?></td>
</tr>
<tr>
    <td><input id="checkme" type="checkbox" name="checkme" value="1" <?=@$checked?> /></td>
    <td>&nbsp;</td>
</tr>
</table>
    
<table id="extra" class="checkout">
<tr>
    <td colspan="2">* <?=lang::translate('order_legend_name')?></td>
</tr>
<tr>
    <td><input type="text" name="diff_name" size="30" value="<?=@$_POST['diff_name']?>" /></td>
    <td class="status"></td>
</tr>

<tr>
    <td colspan="2">* <?=lang::translate('order_legend_adresse')?></td>
</tr>
<tr>
    <td><input type="text" name="diff_adresse" size="30" value="<?=@$_POST['diff_adresse']?>" /></td>
    <td class="status"></td>
</tr>

<tr>
    <td colspan="2">* <?=lang::translate('order_legend_postal_code')?></td>
</tr>
<tr>
    <td><input type="text" name="diff_postal_code" size="12" MAXLENGTH="4" value="<?=@$_POST['diff_postal_code']?>" /></td>
    <td class="status"></td>
</tr>

<tr>
    <td colspan="2">* <?=lang::translate('order_legend_city')?></td>
</tr>
<tr>
    <td><input type="text" name="diff_city" size="30" value="<?=@$_POST['diff_city']?>" /></td>
    <td class="status"></td>
</tr>

</table>

<table class="checkout">
    <tr>
    <td><input type="submit" name="submit" value="<?=lang::translate('order_legend_add_order_button')?>" /></td>
    </tr>
</table>

</form>
