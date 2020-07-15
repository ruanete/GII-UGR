<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Practica 4: PHP</title>
  </head>
  <body>
    <?php
      $patron_texto = "/^[a-zA-ZáéíóúÁÉÍÓÚäëïöüÄËÏÖÜàèìòùÀÈÌÒÙ\s]+$/";
      if(!empty($_POST)){
        if(isset($_POST["nombre"],$_POST["producto"]) && !empty($_POST["nombre"]) && !empty($_POST["producto"]) && preg_match($patron_texto, $_POST["nombre"])){
          if (!isset($_COOKIE["nombre"])){
            setcookie("nombre", $_POST["nombre"]);
          }

          if (!isset($_COOKIE["producto"])){
            setcookie("producto", $_POST["producto"]);
          }
    ?>
          <fieldset>
            <legend>Formulario información producto</legend>
            <form action="./validacion_informacion.php" method="post">
              <fieldset>
                <legend>Información producto</legend>
                <p>Talla (30-50): <input type="number" name="talla" min="30" max="50" step="1"></p>
                <p>Elije el color del producto:</p>
                <input type="radio" name="color" value="rojo" checked/>Rojo
                <input type="radio" name="color" value="verde"/>Verde
                <input type="radio" name="color" value="azul"/>Azul
              </fieldset>
              <p></p>
              <input type="submit" value="Siguiente"/>
              <!--<input type="reset" value="Limpiar formulario"/>-->
            </form>
          </fieldset>

    <?php
        }else{
          echo "<fieldset>
            <legend>Formulario compra</legend>
            <form action=\"./formulario_informacion.php\" method=\"post\">
              <fieldset>
                <legend>Información de la compra</legend>";


                  if(empty($_POST["nombre"])){
                    echo "<p>Nombre: <input type=\"text\" name=\"nombre\"/> <h6 style=\"color:#FF0000\";>Debe especificar el nombre.</h6></p>";
                  }else{
                    if(!preg_match($patron_texto, $_POST["nombre"])){
                      echo "<p>Nombre: <input type=\"text\" name=\"nombre\"/> <h6 style=\"color:#FF0000\";>El nombre sólo puede contener letras y espacios.</h6></p>";
                    }
                  }

                echo "<p>Elije el producto que desea comprar:</p>";

                if($_POST["producto"]==="camisa"){
                  echo "<input type=\"radio\" name=\"producto\" value=\"camisa\" checked/>Camisa
                  <input type=\"radio\" name=\"producto\" value=\"pantalon\"/>Pantalón
                  <input type=\"radio\" name=\"producto\" value=\"falda\"/>Falda";
                }else if($_POST["producto"]==="pantalon"){
                  echo "<input type=\"radio\" name=\"producto\" value=\"camisa\"/>Camisa
                  <input type=\"radio\" name=\"producto\" value=\"pantalon\" checked/>Pantalón
                  <input type=\"radio\" name=\"producto\" value=\"falda\"/>Falda";
                }else{
                  echo "<input type=\"radio\" name=\"producto\" value=\"camisa\"/>Camisa
                  <input type=\"radio\" name=\"producto\" value=\"pantalon\"/>Pantalón
                  <input type=\"radio\" name=\"producto\" value=\"falda\" checked/>Falda";
                }

              echo"</fieldset>
              <p></p>
              <input type=\"submit\" value=\"Siguiente\"/>
            </form>
          </fieldset>";
        }
      }else{
        header('Location: ./formulario_producto.html');
      }
    ?>
  </body>
</html>
