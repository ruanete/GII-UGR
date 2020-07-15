<?php
  require_once('base_web.php');
  if(!isset($_SESSION))
    session_start();

  if(isset($_SESSION["sesion_admin"])){
    if(isset($_GET["nuevo_concierto"]) || isset($_GET["editar_concierto"]) || isset($_GET["borrar_concierto"])){
      cabecera_NOMenu("administracion");
      sidenav();
      echo "<div class=\"main\">";
    }

    if(isset($_GET["nuevo_concierto"])){
      require_once('bd.php');
      require_once('htmlforms.php');

      FORM_newConcierto('Añadir nuevo concierto:','Crear nuevo concierto');
      if (isset($_POST['accion'])) {
        if (!is_string($db=DB_conexion())) {
          switch ($_POST['accion']) {
            case 'Cancelar': // Presentar formulario y pedir confirmación
              header('Location: administracion.php?editar_conciertos=yes');
            break;
            case 'Crear nuevo concierto': // Presentar formulario y pedir confirmación
              $msg = DB_addConcierto($db,$_POST);
              if ($msg===true)
                $info[] = 'El concierto ha sido creado correctamente';
              else {
                $info[] = 'No se ha podido crear el concierto';
                $info[] = $msg;
              }
              if (isset($info) && msgCount($info)>0){
                msgError($info);
                echo"<form action='./administracion.php?editar_conciertos=yes' method='POST'>
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
    }else if(isset($_GET["editar_concierto"])){
      require_once('bd.php');
      require_once('htmlforms.php');

      if (!is_string($db=DB_conexion())) {
        $accion = $_GET["editar_concierto"];
        $id = $_GET['id'];
        $usuario = DB_getConcierto($db,$id);
        $usuario['id']=$id;
        $url = "panelConciertos.php?id=$id&editar_concierto=Editar";
        FORM_editConcierto('Edite los datos:',$usuario,'Modificar',$url);
        if (isset($_POST['accion'])) {
          switch ($_POST['accion']) {
            case 'Cancelar': // Presentar formulario y pedir confirmación
              header('Location: administracion.php?editar_conciertos=yes');
            break;
            case 'Modificar':
              $msg = DB_actConcierto($db,$id,['fecha'=>$_POST['conc_fecha'], 'ciudad'=>$_POST['conc_ciudad'],'lugar'=>$_POST['conc_lugar']]);
              if ($msg===true)
                $info[] = 'El concierto ha sido actualizado';
              else {
                $info[] = 'No se ha podido actualizar el concierto';
                $info[] = $msg;
              }

              if (isset($info) && msgCount($info)>0){
                msgError($info);
                echo"<form action='administracion.php?editar_conciertos=yes' method='POST'>
                  <input type='submit' name='accion' value='Volver' />
                </form>";
              }
            break;
          }
        }
        DB_desconexion($db);
      }
    }else if(isset($_GET["borrar_concierto"])){
      require_once('bd.php');
      require_once('htmlforms.php');

      if (!is_string($db=DB_conexion())) {
        $accion = $_GET["borrar_concierto"];
        $id = $_GET['id'];
        $usuario = DB_getConcierto($db,$id);
        $usuario['editable']="false";
        $usuario['id']=$id;
        $url = "panelConciertos.php?id=$id&borrar_concierto=Borrar";
        FORM_editConcierto('Confirme borrado de este concierto:',$usuario,'Confirmar Borrado',$url);
        if (isset($_POST['accion'])) {
          switch ($_POST['accion']) {
            case 'Cancelar': // Presentar formulario y pedir confirmación
              header('Location: administracion.php?editar_conciertos=yes');
            break;
            case 'Confirmar Borrado':
              if (DB_delConcierto($db,$id))
                $info[] = 'El concierto ha sido borrado';
              else
                $info[] = 'No se ha podido borrar el concierto';

              if (isset($info) && msgCount($info)>0){
                msgError($info);
                echo"<form action='administracion.php?editar_conciertos=yes' method='POST'>
                  <input type='submit' name='accion' value='Volver' />
                </form>";
              }
            break;
          }
        }
        DB_desconexion($db);
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
            <h1>MENU EDICIÓN Y CREACIÓN DE CONCIERTOS</h1>

            <p>La base de datos contiene la siguiente información: </p>";

            require_once('bd.php');
            $bd = DB_conexion();
            $usuarios = getUsuarios($bd);
            VIEW_listadoConciertos($bd, 'panelConciertos.php');

      echo "
            <hr></hr>

            <form action='./panelConciertos.php' method='GET'>
              <input type='submit' name='nuevo_concierto' value='Crear un nuevo concierto' />
            </form>
            <br/>
          </body>
        </html>";
    }

    if(isset($_GET["nuevo_concierto"]) || isset($_GET["editar_concierto"]) || isset($_GET["borrar_concierto"]))
      echo "</div>";
  }else{
    header('Location: ./identificacion.php');
  }
?>
