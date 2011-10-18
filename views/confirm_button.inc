<?php

if (isset($vars['payment_url'])) {
    $payment_url = $vars['payment_url'];
} else {
    $payment_url = '/order/process';
}

?>
<form action="<?=$payment_url?>" method="post" id="order_form">
<table class="checkout">

<!--
<tr>
    <td colspan="2">
        <?=lang::translate('order_legend_accept_terms')?> 
        <a id="various1" href="#inline1"><?=lang::translate('order_accept_terms_link_text')?></a>
    </td>
</tr>
-->
<!--
<tr>
    <td><input id="accept" type="checkbox" name="accept" value="<?=@$_POST['accept']?>" /></td>
    <td class="status"></td>
</tr>
-->
<tr>
    <td colspan="2">
        <input type="submit" name="submit" value="<?=lang::translate('order_confirm_order')?>" />
    </td>
</tr>
</table>
</form>

<!--
<div style="display: none;">
		<div id="inline1" style="width:400px;height:400px;overflow:auto;">
<?php       

$text = get_module_ini('order_form_accept_text');
$filters = get_module_ini('order_filters');
echo get_filtered_content($filters, $text); 

?>
		</div>
    
</div>-->