<?php

class orderSales {
    
    public static $table = 'order_sales';
    
    /**
     * status symbols for a payment
     * From the paypal API
     * @var type 
     */
    /*
    public static $statusSymbol = array (
        1 => 'NONE',
        2 => 'CANCELED_REVERSAL',
        3 => 'DENIED',
        4 => 'EXPIRED',
        5 => 'FAILED',
        6 => 'IN_PROGRESS',
        7 => 'PARTIALLY_REFUNDED',
        8 => 'PENDING',
        9 => 'REVERSED',
        10 => 'PROCESSED',
        11 => 'VOIDED'
    );*/
    
    /*
      None – No status
      Canceled-Reversal– A reversal has been canceled, for example, when you win a dispute and the funds for the reversal have been returned to you.
      Completed – The payment has been completed, and the funds have been added successfully to your account balance.
      Denied – You denied the payment. This happens only if the payment was previously pending because of possible reasons described for the PendingReason element.
      Expired – The authorization period for this payment has been reached.
      Failed – The payment has failed. This happens only if the payment was made from your buyer’s bank account.
      In-Progress – The transaction has not terminated, for example, an authorization may be awaiting completion.
      Partially-Refunded – The payment has been partially refunded
      Pending – The payment is pending. See the PendingReason field for more information.
      Refunded – You refunded the payment.
      Reversed – A payment was reversed due to a chargeback or other type of reversal. The funds have been removed from your account balance and returned to the buyer. The reason for the reversal is specified in the ReasonCode element.
      Processed – A payment has been accepted.
      Voided – An authorization for this transaction has been voided.
      
     * 
    */
    
    public static function insert ($values) {
        $db = new db();
        $res = $db->insert(self::$table, $values);
        return $res;
    }
    
    public static function update () {
        
    }
    
    public static function delete () {
        
    }
    
    public static function getAll($from = 0, $limit = 10) {

        $db = new dbQ();
        $db->setSelect(self::$table);
        $db->limit(0,1);
        $rows = $db->fetch();
               
        /*
        $db->setUpdate(self::$table);
        $values = array ('email' => 'test2', 'full_name' => 'argh');
        $db->setValues($values);
        $db->filter('id =', 1);
        $db->condition('AND');
        $db->filter('email =', 'test2');
        echo $res = $db->exec();
        
        $db->setInsert(self::$table);
        $values = array ('email' => 'flfie', 'full_name' => 'duda');
        $db->setValues($values);
        
        echo $res = $db->exec();
        
        $db->setDelete(self::$table);
        $db->filter('email =', 'test2');
        echo $res = $db->exec();
        */
        
        
        return $rows;
    }
    
    public static function displayAll () {
        $rows = self::getAll();
        print_r($rows);
        
    }
    
}
