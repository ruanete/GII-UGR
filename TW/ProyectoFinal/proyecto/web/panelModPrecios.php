<?php
  require_once('base_web.php');
  if(!isset($_SESSION))
    session_start();

  if(isset($_SESSION["sesion_compras"])){
    if(isset($_GET["modificar_precio"])){
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

    if(isset($_GET["modificar_precio"])){
      require_once('bd.php');
      require_once('htmlforms.php');

      if(isset($_GET['id'])){
        $id = $_GET['id'];
        FORM_editDisco('Introduce el precio nuevo:',$id,'Modificar precio');
      }

      if (isset($_POST['accion'])) {
        if (!is_string($db=DB_conexion())) {
          switch ($_POST['accion']) {
            case 'Modificar precio': // Presentar formulario y pedir confirmación
              $msg = DB_editPrecioDisco($db,$_POST);
              if ($msg===true)
                $info[] = 'El pedido ha sido aceptado correctamente';
              else {
                $info[] = 'No se ha podido aceptar el pedido';
                $info[] = $msg;
              }
              if (isset($info) && msgCount($info)>0){
                msgError($info);
                echo"<form action='./gestionPedidos.php?editar_precios=yes' method='POST'>
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
            <h1>MENU MODIFICAR PRECIOS DE DISCOS</h1>

            <p>La base de datos contiene la siguiente información: </p>";

            require_once('bd.php');
            $bd = DB_conexion();
            $usuarios = getDiscos($bd);
            VIEW_listadoDiscos($bd, 'panelModPrecios.php');

      echo "
            <hr></hr>
            <br/>
          </body>
        </html>";
    }
    if(isset($_GET["modificar_precio"]))
  		echo "</div>";
  }else{
    header('Location: ./identificacion.php');
  }
?>
