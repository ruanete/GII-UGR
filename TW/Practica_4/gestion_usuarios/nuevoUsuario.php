<?php
  require_once('bd.php');
  require_once('htmlforms.php');

  if (isset($_POST['accion'])) {
    if (!is_string($db=DB_conexion())) {
      switch ($_POST['accion']) {
        case 'Crear un nuevo usuario': // Presentar formulario y pedir confirmación
          FORM_newUsuario('Añadir nuevo usuario:','Crear nuevo usuario');
        break;
        case 'Cancelar': // Presentar formulario y pedir confirmación
          header('Location: administracion.php');
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
            echo"<form action='./administracion.php' method='POST'>
              <input type='submit' name='accion' value='Volver al menu del administrador' />
            </form>";
          }
        break;
      }
      DB_desconexion($db);
    }else{
      header('Location: administracion.php');
    }
  }
?>
