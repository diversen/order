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
    

	// validate signup form on keyup and submit
	var validator = $("#order_form").validate({
		rules: {

                        
			name: "required",
                        diff_name: {

                        required: "#checkme:checked",
                        minlength:4
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
                                digits: true,
				minlength: 4
                                
			},

                        diff_postal_code: {
				required: "#checkme:checked",
                                digits: true,
				minlength: 4

			},
			city: {
				required: true,
				minlength: 1
			},

                        diff_city: {
				required: "#checkme:checked",
				minlength: 1
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

		},
		messages: {
			name: "Indtast navn",
                        diff_name: "Indtast navn",
			
			adresse: {
				required: "Indtast adresse",
				minlength: jQuery.format("Mindst {0} karakterer")
			},
                        diff_adresse: {
				required: "Indtast adresse",
				minlength: jQuery.format("Mindst {0} karakterer")
			},
			postal_code: {
				required: "Indtast postkode",
                                digits: jQuery.format('Kun tal'),
				minlength: jQuery.format("Mindst {0} karakterer")
				
			},
                        diff_postal_code: {
				required: "Indtast postkode",
                                digits: jQuery.format('Kun tal'),
				minlength: jQuery.format("Mindst {0} karakterer")

			},
                        city: {
				required: "Indtast by",
				minlength: jQuery.format("Mindst {0} karakterer")

			},
                        diff_city: {
				required: "Indtast by",
				minlength: jQuery.format("Mindst {0} karakterer")

			},
			email: {
				required: "Indtast en gyldig email",
                                email: jQuery.format("Skal være email format")
			},
                        phone: {
				required: "Indtast et gyldigt nummer",
                                digits: jQuery.format('Kun tal'),
                                minlength: jQuery.format("Mindst {0} tal")
			},
                        company: "Indtast firma"


		},
		// the errorPlacement has to take the table layout into account
		errorPlacement: function(error, element) {
			if ( element.is(":radio") )
				error.appendTo( element.parent().next().next() );
			else if ( element.is(":checkbox") )
				error.appendTo ( element.next() );
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

/*
http://papermashup.com/drag-drop-with-php-jquery/
*/

$(document).ready(function(){
    function slideout(){
        setTimeout(function(){
            $("#response").slideUp("fast", function () {
            });
        }, 2000);
    }
    $("#response").hide();
        $(function() {
            $("#list ul").sortable({
                opacity: 0.8, cursor: 'move', update: function() {
                    var order = $(this).sortable("serialize") + '&update=update';
                    $.post("/order/products/update", order, function(theResponse){
                        $("#response").html(theResponse);
                        $("#response").slideDown('fast');
			slideout();

                    });
                }
            });
        });
    });

$(document).ready(function(){
    function slideout(){
        setTimeout(function(){
            $("#response").slideUp("fast", function () {
            });
        }, 2000);
    }
    $("#response").hide();
        $(function() {
            $("#order_category_list ul").sortable({
                opacity: 0.8, cursor: 'move', update: function() {
                    var order = $(this).sortable("serialize") + '&update=update';
                    $.post("/order/category/update", order, function(theResponse){
                        $("#response").html(theResponse);
                        $("#response").slideDown('fast');
			slideout();

                    });
                }
            });
        });
    });