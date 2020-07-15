<?php
  require_once('base_web.php');
  cabecera_NOMenu("identificacion");

  if(isset($_SESSION["sesion_admin"])){
    header('Location: ./administracion.php');
  }else if(isset($_SESSION["sesion_compras"])){
    header('Location: ./gestionPedidos.php');
  }else{?>
    <div class="seccion_web">
      <div clas="c_tangana"><h1>C. Tangana</h1></div>
      <form action="./gestion_usuarios.php" method="post">
        <p>Usuario: <input type="text" name="usuario"/></p>
        <p>Contraseña: <input type="password" name="contraseña" id="contraseña"></p>
        <p></p>

        <input type="submit" value="Iniciar sesión"/>

      </form>
      <form action="./index.php" method="post">
        <input type="submit" value="Volver"/>
      </form>
    </div>
<?php  }

pieDePagina()?>
