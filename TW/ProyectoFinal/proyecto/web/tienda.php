<?php
  require_once('base_web.php');
  require_once('bd.php');
  cabecera("tienda");

  if(isset($_GET["id"], $_GET["precio"])){
    $bd = DB_conexion();
    $result = mysqli_query($bd, "SELECT titulo FROM discos WHERE id=$_GET[id]");
    $titulo = mysqli_fetch_row($result);
    $precio = $_GET["precio"];
    echo "
    <div class=\"seccion_web\">
      <article>
        <section>
          <fieldset>
            <legend>Formulario de compra</legend>
            <form action=\"./procesar.php\" method=\"post\" onsubmit=\"return validarPedido();\">
              <fieldset>
                <legend>Producto a comprar</legend>
                <p>Producto:";
                echo "<input type=\"hidden\" name=\"id\" value=\"$_GET[id]\"/>";
                echo $titulo[0];
                echo "</p>
                <p>";
                echo "Precio: $precio";
                echo "</p>
              </fieldset>

              <fieldset>
                <legend>Datos personales</legend>
                <p>Nombre: <input type=\"text\" name=\"nombre\" id=\"nombre\"/></p>
                <p>Apellidos: <input type=\"text\" name=\"apellidos\" id=\"apellidos\"/></p>
                <p>Teléfono: <input type=\"text\" name=\"telefono\" id=\"telefono\"/></p>
                <p>Correo electronico: <input type=\"text\" name=\"correo\" id=\"correo\"/></p>
              </fieldset>

              <fieldset>
                <legend>Datos de pago</legend>
                  <p>Método de pago:
                    <select name=\"metodo_pago\" id=\"metodo_pago\">
                      <option selected>Contrareembolso</option>
                      <option>Tarjeta</option>
                    </select>
                  </p>
                  <p>Número de tarjeta: <input type=\"text\" name=\"numero_tarjeta\" id=\"numero_tarjeta\"/></p>
                  <p>Mes de caducidad:
                    <select name=\"mes_caducidad\" id=\"mes_caducidad\">
                      <option selected>01</option>
                      <option>02</option>
                      <option>03</option>
                      <option>04</option>
                      <option>05</option>
                      <option>06</option>
                      <option>07</option>
                      <option>08</option>
                      <option>09</option>
                      <option>10</option>
                      <option>11</option>
                      <option>12</option>
                    </select>
                  </p>
                  <p>Año de caducidad: <input type=\"text\" name=\"anio_caducidad\" id=\"anio_caducidad\"/></p>
                  <p>Código CVC: <input type=\"text\" name=\"codigo_cvc\" id=\"codigo_cvc\"/><p>
              </fieldset>

              <fieldset>
                <legend>Dirección de envío</legend>
                  <p>Provincia: <input type=\"text\" name=\"provincia\" id=\"provincia\"/></p>
                  <p>Población: <input type=\"text\" name=\"poblacion\" id=\"poblacion\"/></p>
                  <p>Código postal: <input type=\"text\" name=\"codigo_postal\" id=\"codigo_postal\"/></p>
                  <p>Calle: <input type=\"text\" name=\"calle\" id=\"calle\"/></p>
              </fieldset>

                <input type=\"submit\" value=\"Enviar datos\"/>
                <input type=\"reset\" value=\"Limpiar formulario\"/>
           </form>
         </fieldset>
        </section>
      </article>
    </div>";
    DB_desconexion($bd);
    pieDePagina();
  }else{
    header('Location: index.php');
  }
?>
