<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Practica 4: PHP</title>
  </head>
  <body>
    <fieldset>
      <legend>Formulario de subscripción</legend>
      <form action="./procesamiento_formulario.php" method="post">
        <fieldset>
          <legend>Información personal</legend>
          <p>Nombre: <input type="text" name="nombre"/></p>
          <p>Apellidos: <input type="text" name="apellido"/></p>
          <p>Dirección postal: <input type="text" name="direccion_postal"/></p>
          <p>Fecha nacimiento: <input type="date" name="fecha_nacimiento"/></p>
          <p>Teléfono: <input type="text" name="telefono"/></p>
          <p>Email: <input type="text" name="email"/></p>
          <p>Número de CC: <input type="text" name="numero_cc"/></p>
        </fieldset>

        <fieldset>
          <legend>Información sobre la subscripción</legend>

          <p>REVISTA ELEGIDA: <?php echo $_GET['tematica_elegida'];?></p>

          <p>Tipo de subscripción:
            <select name="tipo_subscripcion">
              <option selected>Anual</option>
              <option>Bianual</option>
            </select>
          </p>
          <p>Selecciona método de pago:
            <br>
              <input type="radio" name="modo_pago" value="tarjeta_credito" checked/>Tarjeta de crédito
              <input type="radio" name="modo_pago" value="contrareembolso"/>Contrareembolso
            </br>
              <dl>
                <dt>Información tarjeta de crédito (rellenar si ha elegido pago por tarjeta):</dt>
                  <dd>Tipo tarjeta:
                    <select name="tipo_tarjeta">
                      <option selected>Visa</option>
                      <option>Mastercard</option>
                    </select>
                  </dd>
                  <dd>Número de tarjeta: <input type="text" name="numero_tarjeta"/></dd>
                  <dd>Mes de caducidad:
                    <select name="mes_caducidad">
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
                  </dd>
                  <dd>Año de caducidad: <input type="text" name="anio_caducidad"/></dd>
                  <dd>Código CVC: <input type="text" name="codigo_cvc"/></dd>
              </dl>
          </p>
        </fieldset>

        <fieldset>
          <legend>Otra información</legend>
          <p>Temas de interés:
            <br>
              <input type="checkbox" name="intereses[]" value="divulgacion"/>Divulgación
              <input type="checkbox" name="intereses[]" value="motor"/>Motor
              <input type="checkbox" name="intereses[]" value="viajes"/>Viajes
            </br>
          </p>
          <p>Subscripción a newsletter:
            <input type="checkbox" name="publicidad_email" value="si"/>Avisame de ofertas y nuevas revistas en mi correo
          </p>
        </fieldset>

        <input type="text" value="<?php echo $_GET['tematica_elegida'];?>" name="tematica_elegida" readonly style="visibility:hidden;"/>

        <br>
          <input type="submit" value="Enviar datos"/>
          <input type="reset" value="Limpiar formulario"/>
        </br>
      </form>
    </fieldset>
  </body>
</html>
