<?php
  require_once('base_web.php');
  if(!isset($_SESSION))
    session_start();

  if(isset($_SESSION["sesion_admin"])){
    if(isset($_GET["nuevo_usuario"]) || isset($_GET["editar_usuario"]) || isset($_GET["borrar_usuario"])){
      cabecera_NOMenu("administracion");
      sidenav();
      echo "<div class=\"main\">";
    }

    if(isset($_GET["nuevo_usuario"])){
      require_once('bd.php');
      require_once('htmlforms.php');

      FORM_newUsuario('Añadir nuevo usuario:','Crear nuevo usuario');
      if (isset($_POST['accion'])) {
        if (!is_string($db=DB_conexion())) {
          switch ($_POST['accion']) {
            case 'Cancelar': // Presentar formulario y pedir confirmación
              header('Location: administracion.php?editar_usuarios=yes');
            break;
            case 'Crear nuevo usuario': // Presentar formulario y pedir confirmación
              $msg = DB_addUsuario($db,$_POST);
              if ($msg===true)
                $info[] = 'El usuario '.$_POST['user_usuario'].' ha sido creado correctamente';
              else {
                $info[] = 'No se ha podido crear el usuario '.$_POST['user_usuario'];
                $info[] = $msg;
              }
              if (isset($info) && msgCount($info)>0){
                msgError($info);
                echo"<form action='./administracion.php?editar_usuarios=yes' method='POST'>
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
    }else if(isset($_GET["editar_usuario"])){
      require_once('bd.php');
      require_once('htmlforms.php');

      if (!is_string($db=DB_conexion())) {
        $accion = $_GET["editar_usuario"];
        $id = $_GET['id'];
        $usuario = DB_getUsuario($db,$id);
        $usuario['id']=$id;
        $url = "panelUsuarios.php?id=$id&editar_usuario=Editar";
        FORM_editUsuario('Edite los datos:',$usuario,'Modificar',$url);
        if (isset($_POST['accion'])) {
          switch ($_POST['accion']) {
            case 'Cancelar': // Presentar formulario y pedir confirmación
              header('Location: administracion.php?editar_usuarios=yes');
            break;
            case 'Modificar':
              $msg = DB_actUsuario($db,$id,['usuario'=>$_POST['user_usuario'], 'nombre'=>$_POST['user_nombre'],'apellidos'=>$_POST['user_apellidos'],'email'=>$_POST['user_email'],'password'=>$_POST['user_contraseña'],'telefono'=>$_POST['user_tlf'],'tipo_usuario'=>$_POST['user_tipo_usuario']]);
              if ($msg===true)
                $info[] = 'El usuario '.$_POST['user_usuario'].' ha sido actualizado';
              else {
                $info[] = 'No se ha podido actualizar '.$_POST['user_usuario'];
                $info[] = $msg;
              }

              if (isset($info) && msgCount($info)>0){
                msgError($info);
                echo"<form action='administracion.php?editar_usuarios=yes' method='POST'>
                  <input type='submit' name='accion' value='Volver al menu del administrador' />
                </form>";
              }
            break;
          }
        }
        DB_desconexion($db);
      }
    }else if(isset($_GET["borrar_usuario"])){
      require_once('bd.php');
      require_once('htmlforms.php');

      if (!is_string($db=DB_conexion())) {
        $accion = $_GET["borrar_usuario"];
        $id = $_GET['id'];
        $usuario = DB_getUsuario($db,$id);
        $usuario['editable']="false";
        $usuario['id']=$id;
        $url = "panelUsuarios.php?id=$id&borrar_usuario=Borrar";
        FORM_editUsuario('Confirme borrado de este usuario:',$usuario,'Confirmar Borrado',$url);
        if (isset($_POST['accion'])) {
          switch ($_POST['accion']) {
            case 'Cancelar': // Presentar formulario y pedir confirmación
              header('Location: administracion.php?editar_usuarios=yes');
            break;
            case 'Confirmar Borrado':
              if (DB_delUsuario($db,$id)){
                $info[] = 'El usuario '.$_POST['user_usuario'].' ha sido borrado';

                if($_POST['user_usuario'] === $_SESSION["sesion_admin"])
                  require('cerrar_sesion.php');
              }else
                $info[] = 'No se ha podido borrar '.$_POST['user_usuario'];

              if (isset($info) && msgCount($info)>0){
                msgError($info);
                echo"<form action='administracion.php?editar_usuarios=yes' method='POST'>
                  <input type='submit' name='accion' value='Volver al menu del administrador' />
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
            <h1>MENU EDICIÓN Y CREACIÓN DE USUARIOS</h1>

            <p>La base de datos contiene la siguiente información: </p>";

            require_once('bd.php');
            $bd = DB_conexion();
            $usuarios = getUsuarios($bd);
            VIEW_listadoUsuarios($bd, 'panelUsuarios.php');

      echo "
            <hr></hr>

            <form action='./panelUsuarios.php' method='GET'>
              <input type='submit' name='nuevo_usuario' value='Crear un nuevo usuario' />
            </form>
            <br/>
          </body>
        </html>";
    }

    if(isset($_GET["nuevo_usuario"]) || isset($_GET["editar_usuario"]) || isset($_GET["borrar_usuario"]))
      echo "</div>";
  }else{
    header('Location: ./identificacion.php');
  }
?>
