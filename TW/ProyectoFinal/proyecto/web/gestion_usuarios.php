<?php session_start();?>

<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Practica 4: PHP</title>
  </head>
  <body>
    <?php
    if(!empty($_POST)){
      require_once('bd.php');
      $bd = DB_conexion();
      if(isset($_POST["usuario"],$_POST["contraseña"]) && !empty($_POST["usuario"]) && !empty($_POST["contraseña"]) && compruebaUsuario($bd, $_POST["usuario"], $_POST["contraseña"])){
        $usuario = $_POST["usuario"];
        $contraseña = $_POST["contraseña"];
        if(compruebaAdmin($bd, $usuario, $contraseña)){
          $_SESSION["sesion_admin"] = $usuario;
          DB_addLog($bd, "Ha iniciado sesión el administrador $usuario");
          //echo $_SESSION["sesion_admin"];
          header('Location: ./administracion.php');
        }else{
          $_SESSION["sesion_compras"] = $usuario;
          DB_addLog($bd, "Ha iniciado sesión el gestor de pedidos $usuario");
          header('Location: ./gestionPedidos.php');
        }

        DB_desconexion($bd);
      }else{
        require_once('base_web.php');
        cabecera_NOMenu("identificacion");

        DB_addLog($bd, "Intento fallido de inicio de sesión.");

        echo "<div class=\"seccion_web\">
          <div clas=\"c_tangana\"><h1>C. Tangana</h1></div>
          <form action=\"./gestion_usuarios.php\" method=\"post\">";
            if(empty($_POST["usuario"])){
              echo "<p>Usuario: <input type=\"text\" name=\"usuario\"/> <h6 style=\"color:white\";>Debe especificar el nombre.</h6></p>";
            }else{
              $usuario = $_POST["usuario"];
              echo "<p>Usuario: <input type=\"text\" name=\"usuario\" value=\"$usuario\"/></p>";
            }

            if(empty($_POST["contraseña"])){
              echo "<p>Contraseña: <input type=\"password\" name=\"contraseña\" id=\"contraseña\"> <h6 style=\"color:white\";>Debe especificar la contraseña.</h6></p>";
            }else{
              echo "<p>Contraseña: <input type=\"password\" name=\"contraseña\" id=\"contraseña\"></p>";
            }
            if(!empty($_POST["usuario"]) && !empty($_POST["contraseña"]))
              echo "<p><h6 style=\"color:white\";>Datos no valido, vuelve a intentarlo.</h6></p>";

            echo "<p></p>

            <input type=\"submit\" value=\"Iniciar sesión\"/>

          </form>
          <form action=\"./index.php\" method=\"post\">
            <input type=\"submit\" value=\"Volver\"/>
          </form>
        </div>";

        pieDePagina();
      }
    }
    ?>
  </body>
</html>
