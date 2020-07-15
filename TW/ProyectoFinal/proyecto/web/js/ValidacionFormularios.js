function validarFechaMenorActual(date){
      var x=new Date();
      var fecha = date.split("-");
      x.setFullYear(fecha[0],fecha[1]-1,fecha[2]);
      var today = new Date();

      if (x >= today)
        return false;
      else
        return true;
}

function validarConcierto() {
  var fecha, ciudad, lugar;
  fecha = document.getElementById("fecha").value;
  ciudad = document.getElementById("ciudad").value;
  lugar = document.getElementById("lugar").value;

  if(fecha === "" || ciudad === "" || lugar === ""){
    alert("No pueden quedar campos vacíos");
    return false;
  }else if(validarFechaMenorActual(fecha)==true){
    alert("Fecha no valida, anterior a la actual.");
    return false;
  }
}

function validarUsuario() {
  var usuario, nombre, apellidos, email, contraseña, telefono;
  usuario = document.getElementById("usuario").value;
  nombre = document.getElementById("nombre").value;
  apellidos = document.getElementById("apellidos").value;
  email = document.getElementById("email").value;
  contraseña = document.getElementById("contraseña").value;
  telefono = document.getElementById("telefono").value;
  tipo_usuario = document.getElementById("tipo_usuario").value;

  if(usuario === "" || nombre === "" || apellidos === "" || email === "" || contraseña === "" || telefono === "" || tipo_usuario === ""){
    alert("No pueden quedar campos vacíos.");
    return false;
  }else if(!(/^[a-zA-ZáéíóúÁÉÍÓÚäëïöüÄËÏÖÜàèìòùÀÈÌÒÙ\s]+$/.test(nombre))){
    alert("El nombre solo puede contener letras.");
    return false;
  }else if(!(/^[a-zA-ZáéíóúÁÉÍÓÚäëïöüÄËÏÖÜàèìòùÀÈÌÒÙ\s]+$/.test(apellidos))){
    alert("El apellido solo puede contener letras.");
    return false;
  }else if(isNaN(telefono)){
    alert("El telefono no puede contener letras, solo números.");
    return false;
  }else if(!(/^\d{9}$/.test(telefono))){
    alert("No has introducido un número de teléfono válido.");
    return false;
  }else if(!(/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,4})+$/.test(email))){
    alert("El email introducido no es valido.");
    return false;
  }
}

function validarSeccion() {
  var titulo, link, cuerpo;
  titulo = document.getElementById("titulo").value;
  link = document.getElementById("link").value;
  cuerpo = document.getElementById("cuerpo").value;

  if(titulo === "" || link === "" || cuerpo === ""){
    alert("No pueden quedar campos vacíos");
    return false;
  }
}

function validarAceptacionPedido(){
  var mensaje;
  mensaje = document.getElementById("mensaje").value;

  if(mensaje === ""){
    alert("No pueden quedar campos vacíos");
    return false;
  }
}

function validarDenegacionPedido(){
  var mensaje, motivo;
  mensaje = document.getElementById("mensaje").value;
  motivo = document.getElementById("motivo").value;

  if(mensaje === "" || motivo === ""){
    alert("No pueden quedar campos vacíos");
    return false;
  }
}

function validateDecimal(valor) {
    var RE = /^\d*(\.\d{1})?\d{0,1}$/;
    if (RE.test(valor)) {
        return true;
    } else {
        return false;
    }
}

function validarEditarPrecioDisco(){
  var precio;
  precio = document.getElementById("precio").value;

  if(precio === ""){
    alert("No pueden quedar campos vacíos");
    return false;
  }else if(!validateDecimal(precio)){
    alert("Solo puedes introducir números decimales o enteros con dos digitos de precisión.");
    return false;
  }
}

function validarPedido(){
  var nombre, apellidos, telefono, correo, metodo_pago, numero_tarjeta, mes_caducidad, anio_caducidad, codigo_cvc, provincia, poblacion, codigo_postal, calle;
  nombre = document.getElementById("nombre").value;
  apellidos = document.getElementById("apellidos").value;
  telefono = document.getElementById("telefono").value;
  correo = document.getElementById("correo").value;
  metodo_pago = document.getElementById("metodo_pago").value;
  numero_tarjeta = document.getElementById("numero_tarjeta").value;
  mes_caducidad = document.getElementById("mes_caducidad").value;
  anio_caducidad = document.getElementById("anio_caducidad").value;
  codigo_cvc = document.getElementById("codigo_cvc").value;
  provincia = document.getElementById("provincia").value;
  poblacion = document.getElementById("poblacion").value;
  codigo_postal = document.getElementById("codigo_postal").value;
  calle = document.getElementById("calle").value;

  if(nombre==="" || apellidos==="" || telefono==="" || correo==="" || metodo_pago==="" || provincia==="" || poblacion==="" || codigo_postal==="" || calle===""){
    alert("No pueden quedar campos vacíos");
    return false;
  }else if(!(/^[a-zA-ZáéíóúÁÉÍÓÚäëïöüÄËÏÖÜàèìòùÀÈÌÒÙ\s]+$/.test(nombre))){
    alert("El nombre no puede contener números.");
    return false;
  }else if(!(/^[a-zA-ZáéíóúÁÉÍÓÚäëïöüÄËÏÖÜàèìòùÀÈÌÒÙ\s]+$/.test(apellidos))){
    alert("El apellido no puede contener números.");
    return false;
  }else if(isNaN(telefono)){
    alert("El teléfono no puede contener letras, solo números.");
    return false;
  }else if(!(/^[9|6|7][0-9]{8}$/.test(telefono))){
    alert("No has introducido número de teléfono válido.");
    return false;
  }else if(!(/^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$/.test(correo))){
    alert("No has introducido un email válido.");
    return false;
  }else if(!(/^[a-zA-ZáéíóúÁÉÍÓÚäëïöüÄËÏÖÜàèìòùÀÈÌÒÙ\s]+$/.test(provincia))){
    alert("La provincia no puede contener números.");
    return false;
  }else if(!(/^[a-zA-ZáéíóúÁÉÍÓÚäëïöüÄËÏÖÜàèìòùÀÈÌÒÙ\s]+$/.test(poblacion))){
    alert("La población no puede contener números.");
    return false;
  }else if(!(/^(?:0[1-9]\d{3}|[1-4]\d{4}|5[0-2]\d{3})$/.test(codigo_postal))){
    alert("No has introducido un código postal válido.");
    return false;
  }else if(!(/[a-zA-Z1-9À-ÖØ-öø-ÿ]+\.?(( |\-)[a-zA-Z1-9À-ÖØ-öø-ÿ]+\.?)*/.test(calle))){
    alert("No has introducido una calle válida.");
    return false;
  }

  var f = new Date();

  if(metodo_pago=="Tarjeta"){
    if(numero_tarjeta==="" || mes_caducidad==="" || anio_caducidad==="" || codigo_cvc===""){
      alert("Has elegido metodo de pago por tarjeta, debes rellenar los datos de esta.");
      return false;
    }else if(!(/^5[1-5]\d{2}-?\d{4}-?\d{4}-?\d{4}$/.test(numero_tarjeta)) || !(/^5[1-5]\d{2}-?\d{4}-?\d{4}-?\d{4}$/.test(numero_tarjeta))){
      alert("No has introducido un número de tarjeta válido."+numero_tarjeta);
      return false;
    }else if(!(/[0-9]{4}/.test(anio_caducidad))){
      alert("El año de caducidad solo puede contener 4 digitos y ninguna letra.");
      return false;
    }else if(anio < f.getFullYear() || anio!=f.getFullYear() && mes_caducidad < g.getMonth()){
      alert("Has introducido una tarjeta cumplida.");
      return false;
    }else if(!(/^[0-9]{3}$/.test(codigo_cvc))){
      alert("No has introducido un código CVC válido.");
      return false;
    }
  }
}
