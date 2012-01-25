$(document).ready(function(){
  $("#order_amount").focus();
});

$(document).ready(function(){
    // submission check
    if (!$("#checkme").is(":checked")) {
        $("#extra").css("display","none");
    }

    // Add onclick handler to checkbox w/id checkme
    $("#checkme").click(function(){

    // If checked
    if ($("#checkme").is(":checked")){
        //show the hidden div
        $("#extra").show("fast");
    } else {
        //otherwise, hide it
        $("#extra").hide("fast");
    }
  });
});

/*
$(document).ready(function(){
    $("#order_form").validate();
});*/



$(document).ready(function() {
        var tr = $.tr.translator();
	var validator = $("#order_form").validate({
		rules: {

                        
			name: {
                            required: true,
                            minlength: 3
			},
                        
                        order_shipping_type: {
                            required: true
                        },
                        
                        
                        diff_name: {
                            required: "#checkme:checked",
                            minlength: 3
                        },
                   
                        adresse: {
                            required: true,
                            minlength: 4
			},

                        diff_adresse: {
                            required: "#checkme:checked",
                            minlength: 4
			},

			postal_code: {
                            required: true,
                            minlength: 4    
			},

                        diff_postal_code: {
                            required: "#checkme:checked",
                            minlength: 4

			},
			city: {
                            required: true,
                            minlength: 2
			},

                        diff_city: {
                            required: "#checkme:checked",
                            minlength: 2
			},
                        
			email: {
                            required: true,
                            email: true
			},

                        company: {
                            required: false,
                            minlength: 2
			},

                        phone: {
                            required: false,
                            digits: true,
                            minlength: 6
			}
                        //accept: "required"
			

		},
		messages: {
                        order_shipping_type: tr('order_valid_shipping_type'),
			name: tr('order_valid_name'),
                        diff_name: tr('order_valid_name'),
			adresse: tr('order_valid_adresse'),
                        diff_adresse: tr('order_valid_adresse'),
			postal_code: tr('order_valid_postal_code'),
                        //digits: jQuery.format('Kun tal')
                        //minlength: jQuery.format("Mindst {0} karakterer")	
			
                        diff_postal_code: tr('order_valid_postal_code'),
                            //digits: jQuery.format('Kun tal'),
                            //minlength: jQuery.format("Mindst {0} karakterer")
			//},
                        city: tr('order_valid_city'),

                        diff_city: tr('order_valid_city'),

			email: {
                            required: tr('order_valid_email'),
                            //email: jQuery.format("Skal være email format")
                            email: tr('order_valid_email')
			},
                        phone: tr('order_valid_phone'),
                            //digits: jQuery.format('Kun tal'),
                            //minlength: jQuery.format("Mindst {0} tal")
			//},
                        accept: tr('order_accept_conditions'),
                        //accept: "Acceptere handelsbetingelser",
                        
                        company: tr("order_checkout_company")
		},
		// the errorPlacement has to take the table layout into account
		errorPlacement: function(error, element) {
			if ( element.is(":radio") )
				error.appendTo( element.parent().next().next() );

			else
				error.appendTo( element.parent().next() );
		},
		// specifying a submitHandler prevents the default submit, good for the demo
		//submitHandler: function() {
			//alert("submitted!");
		//},
		// set this class to error-labels to indicate valid fields
		success: function(label) {
			// set &nbsp; as text for IE
			label.html("&nbsp;").addClass("checked");
		}
	});
});
