<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Practica 4: PHP</title>
  </head>
  <body>
    <?php
      if(!empty($_POST)){
        if(isset($_POST["talla"],$_POST["color"]) && !empty($_POST["talla"]) && !empty($_POST["color"])){
          if (!isset($_COOKIE["talla"])){
            setcookie("talla", $_POST["talla"]);
            $_COOKIE["talla"]=$_POST["talla"];
          }

          if (!isset($_COOKIE["color"])){
            setcookie("color", $_POST["color"]);
            $_COOKIE["color"]=$_POST["color"];
          }
          //IMPRIMO VALORES
          echo "<h1>INFORMACIÓN RECIBIDA: </h1>";
          echo "Nombre: ", $_COOKIE["nombre"], PHP_EOL;
          echo "Producto: ", $_COOKIE["producto"], PHP_EOL;
          echo "Talla: ", $_COOKIE["talla"], PHP_EOL;
          echo "Color: ", $_COOKIE["color"], PHP_EOL;
        }
      }else{
        header('Location: ./formulario_producto.html');
      }
    ?>
    <form action="./eliminaCookies.php" method='POST'>
      <input type='submit' value='Finalizar compra' name='finalizar_compra'>
    </form>
  </body>
</html>
