function genera_grafica(datos){
  var valores = []

  for(var i in datos){
    valores.push(datos[i])
  }

  $(function() {
  var chartOptions = {
  	chart: {
      renderTo: 'chart',
    	type: 'bar'
    },
    title: {
    	text: 'Cantidad de datos en la base de datos'
    },
    xAxis: {
    	categories: ['Grupos', 'Albums', 'Músicos']
    },
    yAxis: {
    	title: 'Value',
      tickInterval: 1,
      min: 0
    },
    series: [{
        name: 'Número de datos en la BD',
        data: valores,
        color: '#00897b'
    }]
  }

  var chart = new Highcharts.Chart(chartOptions);
  });
}


$(document).ready(function(){
  $.ajax({
    url: '/web_musical/api/database/count/',
    dataType: "json",
    type: 'GET',
    success: function(datos) {
      genera_grafica(datos);
    },
    failure: function(datos) {
      alert('esto no vá');
    }
  });
});
