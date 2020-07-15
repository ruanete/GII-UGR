<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <title>Practica 4: PHP</title>
  </head>
  <body>
    <fieldset>
      <legend>Inicio de sesión</legend>
      <form action="./gestion_usuarios.php" method="post">
        <p>Usuario: <input type="text" name="usuario"/></p>
        <p>Contraseña: <input type="password" name="contraseña" id="contraseña"></p>
        <p></p>

        <input type="submit" value="Iniciar sesión"/>
      </form>
    </fieldset>
  </body>
</html>
