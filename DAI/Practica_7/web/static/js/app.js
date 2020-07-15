//Paginador con AJAX//

function previous(){
	new_page = parseInt($('#current_page').val()) - 1;
	//Si la pagina anterior no es una pagina en si no disminuimos la pagina actual
	if($('.active_page').parent().prev().prev().length==true){
		go_to_page(new_page);
	}
}

function next(){
	new_page = parseInt($('#current_page').val()) + 1;
	//Si la pagina siguiente no es una pagina en si no aumentamos la pagina actual
	if($('.active_page').parent().next().next().length==true){
		go_to_page(new_page);
	}
}

function go_to_page(page_num){
  //Obtengo la pagina que tenga el longdesc con la pagina actual y añado la pagina activa a esta y le quito la pagina activa a la pagina anterior
	//Además activo el color de la pagina actual y desactivo el anterior
	$('#page_navigation .page-item > .page-link').removeClass('active_page');
	$('#page_navigation .page-item').removeClass('active');
	$('.page-link[longdesc=' + page_num +']').addClass('active_page');
	$('.page-link[longdesc=' + page_num +']').parent().addClass('active');

	//Actualizo la pagina actual su numero
	$('#current_page').val(page_num);

	//Actualizo los valores que se visualizan
	$.ajax({
		url: '/web_musical/api/grupos/',
		data: {'numero_pagina' : page_num+1},
		dataType: "json",
		type: 'GET',
		success: function(datos) {
			visualiza_datos(datos);
		},
		failure: function(datos) {
			alert('esto no vá');
		}
	});
}

function create_paginator(number_of_items){
	//Número de paginas a mostrar
	var show_per_page = 3;
	//Calculamos el numero de paginas que vamos a tener
	var number_of_pages = Math.ceil(number_of_items/show_per_page);

	//Variable oculta con la pagina actual la ponemos a 0
	$('#current_page').val(0);
	//Variable oculta con el numero de valores por pagina lo inicializamos a 3
	$('#show_per_page').val(show_per_page);

	//Genero todo el paginador
	var navigation_html = '<nav aria-label="Page navigation example"><ul class="pagination justify-content-center"><li class="page-item"><a class="page-link previous_link" href="javascript:previous();" tabindex="-1">Anterior</a></li>';
	var current_link = 0;
	while(number_of_pages > current_link){
		navigation_html += '<li class="page-item"><a class="page-link" href="javascript:go_to_page(' + current_link +')" longdesc="' + current_link +'">'+ (current_link + 1) +'</a></li>';
	  current_link++;
	}
 	navigation_html += '<li class="page-item"><a class="page-link next_link" href="javascript:next();">Siguiente</a></li></ul>';

	//Imprimo el paginador en la web
	$('#page_navigation').html(navigation_html);

	//Añadimos la clase active_page a la primera página que existe
	$('#page_navigation .page-item:nth-child(2) > .page-link').addClass('active_page');
	$('#page_navigation .page-item:nth-child(2)').addClass('active');
}

function visualiza_datos (datos) {
	$('#content').html("");
  for(var i in datos){
    let pk = datos[i].pk;
    let nombre = datos[i].fields.nombre;
    let fecha_fundacion = datos[i].fields.fecha_fundacion;
    let estilo = datos[i].fields.estilo;

    $('#content').append(`
      <tr>
        <td>${nombre}</td>
        <td>${fecha_fundacion}</td>
        <td>${estilo}</td>
        <td class="float-right">
          {% if not user.is_anonymous %}
            <button onclick="location.href='/web_musical/grupos/edit/${pk}/'" type="button" class="btn btn-info">Editar</button>
            <button onclick="location.href='/web_musical/grupos/delete/${pk}/'" type="button" class="btn btn-danger">Borrar</button>
          {% endif %}
        </td>
      </tr>`)
  }
}

$(document).ready(function(){
	$.ajax({
    url: '/web_musical/api/grupos/count/',
    dataType: "json",
    type: 'GET',
    success: function(datos) {
			$('#total_items').val(datos);
			create_paginator(datos);
    },
    failure: function(datos) {
      alert('esto no vá');
    }
  });

  $.ajax({
    url: '/web_musical/api/grupos/',
    data: {'numero_pagina' : 1},
    dataType: "json",
    type: 'GET',
    success: function(datos) {
      visualiza_datos(datos);
    },
    failure: function(datos) {
      alert('esto no vá');
    }
  });
});

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Paginación sin AJAX//
/*
$(document).ready(function(){
	//Número de paginas a mostrar
	var show_per_page = 3;
	//Se obtienen el número de elementos que hay dentro del div de content
	var number_of_items = $('#content').children().length;
	//Calculamos el numero de paginas que vamos a tener
	var number_of_pages = Math.ceil(number_of_items/show_per_page);

	//Las dos variables ocultas con el valor de la pagina actual y el numero por pagina se inicializan
	$('#current_page').val(0);
	$('#show_per_page').val(show_per_page);

  var navigation_html = '<nav aria-label="Page navigation example"><ul class="pagination justify-content-center"><li class="page-item"><a class="page-link previous_link" href="javascript:previous();" tabindex="-1">Anterior</a></li>';
	var current_link = 0;
	while(number_of_pages > current_link){
    navigation_html += '<li class="page-item"><a class="page-link" href="javascript:go_to_page(' + current_link +')" longdesc="' + current_link +'">'+ (current_link + 1) +'</a></li>';
    current_link++;
	}
  navigation_html += '<li class="page-item"><a class="page-link next_link" href="javascript:next();">Siguiente</a></li></ul>';

	$('#page_navigation').html(navigation_html);

	//Añadimos la clase active_page a la primera página que existe
	$('#page_navigation .page-item:nth-child(2) > .page-link').addClass('active_page');

	//Escondemos los elementos de dentro del div principal
	$('#content').children().css('display', 'none');

	//Luego activamos la visibilidad de aquellos que primeros que hay que paginas
	$('#content').children().slice(0, show_per_page).css('display', 'table-row');

});

function previous(){
	new_page = parseInt($('#current_page').val()) - 1;
	//Si la pagina anterior no es una pagina en si no disminuimos la pagina actual
	if($('.active_page').parent().prev().prev().length==true){
		go_to_page(new_page);
	}
}

function next(){
	new_page = parseInt($('#current_page').val()) + 1;
	//Si la pagina siguiente no es una pagina en si no aumentamos la pagina actual
	if($('.active_page').parent().next().next().length==true){
		go_to_page(new_page);
	}
}
function go_to_page(page_num){
	//Obtenemos el numero de filas que debemos listar por paginas de la variable oculta
	var show_per_page = parseInt($('#show_per_page').val());

	//Obtenemos el elementos desde donde empieza la pagina actual
	start_from = page_num * show_per_page;

	//Obtenemos el elemento final donde acaba la pagina actual
	end_on = start_from + show_per_page;

	//Escondemos todos los elementos contenidos en el div y solo mostramos aquellos que les toque por el numero de pagina
	$('#content').children().css('display', 'none').slice(start_from, end_on).css('display', 'table-row');

	//Obtengo la pagina que tenga el longdesc con la pagina actual y añado la pagina activa a esta y le quito la pagina activa a la pagina anterior
	$('#page_navigation .page-item > .page-link').removeClass('active_page');
	$('.page-link[longdesc=' + page_num +']').addClass('active_page');

	//Actualizo la pagina actual su numero
	$('#current_page').val(page_num);
}
*/
