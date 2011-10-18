<h3><?=lang::translate('order_invoice_details')?></h3>

<table>
    
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
<?php

if (isset($_POST['checkme'])){ 
    
    echo "<h3>" . lang::translate('order_legend_diffent_shipping') . "</h3>\n";
    
    ?>



<table>

<tr>
<td><?=lang::translate('order_name')?></td>
<td><?=$_POST['diff_name']?></td>
</tr>

<tr>
<td><?=lang::translate('order_adresse')?></td>
<td><?=$_POST['diff_adresse']?></td>
</tr>

<tr>
<td><?=lang::translate('order_postal_code')?></td>
<td><?=$_POST['diff_postal_code']?></td>
</tr>

<tr>
<td><?=lang::translate('order_city')?></td>
<td><?=$_POST['diff_city']?></td>
</tr>
</table>
<?php } ?>
