var myDictionary = {
    da_DK : {
        'order_valid_shipping_type' : 'Vælg fragt',
        'order_valid_name' : 'Indtast navn',
        'order_valid_email' : 'Skal gyldig email',
        'order_valid_adresse' : 'Indtast adresse',
        'order_valid_postal_code' : 'Indtast postnummer',
        'order_valid_city' : 'Indtast by',
        'order_valid_phone' : 'Indtast nummer',
        'order_accept_conditions' : 'accepter betingelser',
        'order_valid_company' : 'Indtast firma'        
    }
}

$.tr.dictionary(myDictionary);

// 2. Language selection.
$.tr.language('da_DK', true);