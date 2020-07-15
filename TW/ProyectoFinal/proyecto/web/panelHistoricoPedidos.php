<?php
  require_once('base_web.php');
  if(!isset($_SESSION))
    session_start();

  if(isset($_SESSION["sesion_compras"])){
    echo "
      <!DOCTYPE html>
      <html>
        <head>
          <meta charset=\"utf-8\">
          <title>Practica 4: PHP</title>
        </head>
        <body>
          <h1>MENU GESTIÓN DE PEDIDOS</h1>

          <p>La base de datos contiene la siguiente información: </p>";

          require_once('bd.php');
          $bd = DB_conexion();
          $usuarios = getPedidos($bd);
          VIEW_listadoPedidos($bd, 'panelGestor.php');

    echo "
          <hr></hr>
          <br/>
        </body>
      </html>";

  }else{
    header('Location: ./identificacion.php');
  }
?>
