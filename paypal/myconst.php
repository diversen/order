<?php

include_once 'constants.php';




//echo "FLAF"; die;
if(defined('API_USERNAME'))
$API_UserName=API_USERNAME;

if(defined('API_PASSWORD'))
$API_Password=API_PASSWORD;

if(defined('API_SIGNATURE'))
$API_Signature=API_SIGNATURE;

if(defined('API_ENDPOINT'))
    $API_Endpoint =API_ENDPOINT;


$version=VERSION;

if(defined('SUBJECT'))
$subject = SUBJECT;
// below three are needed if used permissioning
if(defined('AUTH_TOKEN'))
$AUTH_token= AUTH_TOKEN;

if(defined('AUTH_SIGNATURE'))
$AUTH_signature=AUTH_SIGNATURE;

if(defined('AUTH_TIMESTAMP'))
$AUTH_timestamp=AUTH_TIMESTAMP;
?>
