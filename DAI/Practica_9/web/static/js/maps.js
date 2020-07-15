/*$(document).ready(function(){
  var mymap = L.map('mapid').setView([40.4165001, -3.7025599], 6);

  L.tileLayer('https://api.mapbox.com/styles/v1/{id}/tiles/{z}/{x}/{y}?access_token={accessToken}', {
    attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors, <a href="https://creativecommons.org/licenses/by-sa/2.0/">CC-BY-SA</a>, Imagery © <a href="https://www.mapbox.com/">Mapbox</a>',
    maxZoom: 18,
    id: 'mapbox/streets-v11',
    accessToken: 'pk.eyJ1IjoicnVhbmV0ZSIsImEiOiJjazRyZ2U1aGswcHFnM3VwNGRkNmNwMnEwIn0.FMRnddYnKkYE0Ml4fGdHew'
  }).addTo(mymap);

  window.addNewRestaurante = function(rest){
      let marker = L.marker(rest[1]).addTo(mymap);
      marker.bindPopup(`<b>${rest[0]}</b>`).openPopup();
      mymap.setView(rest[1], 13);
  };

  var marker = L.marker([40.4165001, -3.7025599]).addTo(mymap);
  marker.bindPopup("<b>Hello world!</b><br>I am a popup.").openPopup();
});*/
