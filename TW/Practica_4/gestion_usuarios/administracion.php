<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Practica 4: PHP</title>
  </head>
  <body>
    <h1>MENU DEL ADMINISTRADOR</h1>

    <p>La base de datos contiene la siguiente información: </p>
    <?php
      require_once('bd.php');
      $bd = DB_conexion();
      $usuarios = getUsuarios($bd);
      VIEW_listadoUsuarios($bd, 'editarUsuario.php');
    ?>

    <hr></hr>

    <form action='./nuevoUsuario.php' method='POST'>
      <input type='submit' name='accion' value='Crear un nuevo usuario' />
    </form>
    <br/>
    <form action="./identificacion.php" method="post">
      <input type="submit" value="Cerrar sesión"/>
    </form>
  </body>
</html>
