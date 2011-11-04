<?php
/**********************************************************
DoExpressCheckoutPayment.php

This functionality is called to complete the payment with
PayPal and display the result to the buyer.

The code constructs and sends the DoExpressCheckoutPayment
request string to the PayPal server.

Called by GetExpressCheckoutDetails.php.

Calls CallerService.php and APIError.php.

**********************************************************/

require_once 'CallerService.php';
include_model ('order/sales');

//session_start();


ini_set('session.bug_compat_42',0);
ini_set('session.bug_compat_warn',0);

/* Gather the information to make the final call to
   finalize the PayPal payment.  The variable nvpstr
   holds the name value pairs
   */
$token =urlencode( $_SESSION['token']);
$paymentAmount =urlencode ($_SESSION['TotalAmount']);
$paymentType = urlencode($_SESSION['paymentType']);
$currCodeType = urlencode($_SESSION['currCodeType']);
$payerID = urlencode($_SESSION['payer_id']);
$serverName = urlencode($_SERVER['SERVER_NAME']);

$nvpstr='&TOKEN='.$token.'&PAYERID='.$payerID.'&PAYMENTACTION='.$paymentType.'&AMT='.$paymentAmount.'&CURRENCYCODE='.$currCodeType.'&IPADDRESS='.$serverName ;



 /* Make the call to PayPal to finalize payment
    If an error occured, show the resulting errors
    */
$resArray=hash_call("DoExpressCheckoutPayment",$nvpstr);

/* Display the API response back to the browser.
   If the response from PayPal was a success, display the response parameters'
   If the response was an error, display the errors received using APIError.php.
   */
$ack = strtoupper($resArray["ACK"]);


if($ack != 'SUCCESS' && $ack != 'SUCCESSWITHWARNING'){
	$_SESSION['reshash']=$resArray;
	$location = "APIError";
	header("Location: $location");
}

// process email sending buyer and shop owner. 
 //$cart = new order();
 //$res = $cart->process();
include_model ('order/sales');

 

// get buyer info.
load_post('order_form');
//print_r($_POST);


$ary = array();
$ary['full_name'] = $_POST['name'];
$ary['email'] = $_POST['email'];
$ary['full_shipping_info'] = serialize($_POST);
$ary['transaction_details'] = serialize($resArray);
$ary['payment_module'] = 'paypal';
$ary['status'] = $resArray['PAYMENTSTATUS'];


//print_r($_POST);



// get sales / order info. 

ob_start();
order::displayOrderEmail();
$message = ob_get_contents();
ob_end_clean();

$ary['order_details'] = $message;

//print $message;

//print_r($resArray);
//require_once 'ShowAllResponse.php';

print_r($ary);

$sale = new orderSales();
$sale->insert($ary);

