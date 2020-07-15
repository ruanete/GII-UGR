<?php
  require_once('base_web.php');
  if(!isset($_SESSION))
    session_start();

  if(isset($_SESSION["sesion_compras"])){
    if(isset($_GET["aceptar_pedido"]) || isset($_GET["denegar_pedido"])){
  		cabecera_NOMenu("administracion");
  		echo "<div class=\"sidenav\">
        <a href=\"gestionPedidos.php?pedidos_pendientes=yes\">Pedidos pendientes</a>
        <a href=\"gestionPedidos.php?historico_pedidos=yes\">Historico pedidos</a>
        <a href=\"gestionPedidos.php?editar_precios=yes\">Editar precios</a>
        <a href=\"./index.php\" id=\"volver\">Volver a la web</a>
        <a href=\"./cerrar_sesion.php\" id=\"cerrar\">Cerrar sesión</a>
      </div>";

  		echo "<div class=\"main\">";
  	}

    if(isset($_GET["aceptar_pedido"])){
      require_once('bd.php');
      require_once('htmlforms.php');

      if(isset($_GET['id'])){
        $id = $_GET['id'];
        FORM_aceptaPedido('Escriba el mensaje de correo que desea enviar:',$id,'Aceptar pedido');
      }

      if (isset($_POST['accion'])) {
        if (!is_string($db=DB_conexion())) {
          switch ($_POST['accion']) {
            case 'Aceptar pedido': // Presentar formulario y pedir confirmación
              $msg = DB_editPedidoAceptar($db,$_POST,$_SESSION["sesion_compras"]);
              if ($msg===true)
                $info[] = 'El pedido ha sido aceptado correctamente';
              else {
                $info[] = 'No se ha podido aceptar el pedido';
                $info[] = $msg;
              }
              if (isset($info) && msgCount($info)>0){
                msgError($info);
                echo"<form action='./administracion.php?pedidos_pendientes=yes' method='POST'>
                  <input type='submit' name='accion' value='Volver' />
                </form>";
              }
            break;
          }
          DB_desconexion($db);
        }else{
          header('Location: administracion.php');
        }
      }
    }else if(isset($_GET["denegar_pedido"])){
      require_once('bd.php');
      require_once('htmlforms.php');

      if(isset($_GET['id'])){
        $id = $_GET['id'];
        FORM_deniegaPedido('Escriba el mensaje de correo que desea enviar:','Escriba el motivo de la denegación:',$id,'Denegar pedido');
      }

      if (isset($_POST['accion'])) {
        if (!is_string($db=DB_conexion())) {
          switch ($_POST['accion']) {
            case 'Denegar pedido': // Presentar formulario y pedir confirmación
              $msg = DB_editPedidoDenegar($db,$_POST,$_SESSION["sesion_compras"]);
              if ($msg===true)
                $info[] = 'El pedido ha sido denegado correctamente';
              else {
                $info[] = 'No se ha podido denegar el pedido';
                $info[] = $msg;
              }
              if (isset($info) && msgCount($info)>0){
                msgError($info);
                echo"<form action='./administracion.php?pedidos_pendientes=yes' method='POST'>
                  <input type='submit' name='accion' value='Volver' />
                </form>";
              }
            break;
          }
          DB_desconexion($db);
        }else{
          header('Location: administracion.php');
        }
      }
    }else{
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
            VIEW_listadoPedidosPendientes($bd, 'panelGestor.php');

      echo "
            <hr></hr>
            <br/>
          </body>
        </html>";
    }
    if(isset($_GET["aceptar_pedido"]) || isset($_GET["denegar_pedido"]))
  		echo "</div>";
  }else{
    header('Location: ./identificacion.php');
  }
?>
