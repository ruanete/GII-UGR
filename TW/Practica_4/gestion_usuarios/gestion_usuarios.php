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
          header('Location: ./administracion.php');
        }else if(compruebaNormalUser($bd, $usuario, $contraseña)){
          echo "<p>HOLA, $usuario HAZ INICIADO SESION COMO USUARIO NORMAL.</p>
          <form action=\"./identificacion.php\" method=\"post\">
            <input type=\"submit\" value=\"Cerrar sesión\"/>
          </form>";
        }

        DB_desconexion($bd);
      }else{
        echo "<fieldset>
          <legend>Inicio de sesión</legend>
          <form action=\"./gestion_usuarios.php\" method=\"post\">";
            if(empty($_POST["usuario"])){
              echo "<p>Usuario: <input type=\"text\" name=\"usuario\"/> <h6 style=\"color:#FF0000\";>Debe especificar el nombre.</h6></p>";
            }else{
              $usuario = $_POST["usuario"];
              echo "<p>Usuario: <input type=\"text\" name=\"usuario\" value=\"$usuario\"/></p>";
            }

            if(empty($_POST["contraseña"])){
              echo "<p>Contraseña: <input type=\"password\" name=\"contraseña\" id=\"contraseña\"> <h6 style=\"color:#FF0000\";>Debe especificar la contraseña.</h6></p>";
            }else{
              echo "<p>Contraseña: <input type=\"password\" name=\"contraseña\" id=\"contraseña\"></p>";
            }

            if(!empty($_POST["usuario"]) && !empty($_POST["contraseña"]))
              echo "<p><h6 style=\"color:#FF0000\";>Datos no valido, vuelve a intentarlo.</h6></p>";
        echo "<p></p>

            <input type=\"submit\" value=\"Iniciar sesión\"/>
          </form>
        </fieldset>";

      }
    }
    ?>
  </body>
</html>
