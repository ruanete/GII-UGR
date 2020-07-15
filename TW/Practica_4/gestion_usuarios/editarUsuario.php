<?php
  require_once('bd.php');
  require_once('htmlforms.php');

  if (isset($_POST['accion']) && isset($_POST['id'])) {
    switch ($_POST['accion']) {
      case 'Borrar': // Presentar formulario y pedir confirmación
        $accion = 'Borrar';
        $id = $_POST['id'];
      break;
      case 'Editar': // Presentar formulario y pedir confirmación
        $accion = 'Editar';
        $id = $_POST['id'];
      break;
      case 'Confirmar Borrado': // Borrado confirmado
        $accion = 'BorrarOK';
        $id = $_POST['id'];
      break;
      case 'Modificar': // Modificación confirmada
        $accion = 'Modificar';
        $id = $_POST['id'];
      break;
      case 'Cancelar': break;
    }
  }

  if (isset($id)) {
    if (!is_string($db=DB_conexion())) {
      switch ($accion) {
        case 'Borrar':
          $usuario = DB_getUsuario($db,$id);
          $usuario['editable']="false";
          $usuario['id']=$id;
          FORM_editUsuario('Confirme borrado de esta ciudad:',$usuario,'Confirmar Borrado');
        break;
        case 'BorrarOK':
          if (DB_delUsuario($db,$id))
            $info[] = 'El usuario '.$_POST['user_usuario'].' ha sido borrado';
          else
            $info[] = 'No se ha podido borrar '.$_POST['user_usuario'];

          if (isset($info) && msgCount($info)>0){
            msgError($info);
            echo"<form action='./administracion.php' method='POST'>
              <input type='submit' name='accion' value='Volver al menu del administrador' />
            </form>";
          }
          break;
        case 'Editar':
          $usuario = DB_getUsuario($db,$id);
          $usuario['id']=$id;
          FORM_editUsuario('Edite los datos:',$usuario,'Modificar');
        break;
        case 'Modificar':
          $msg = DB_actUsuario($db,$id,['usuario'=>$_POST['user_usuario'], 'nombre'=>$_POST['user_nombre'],'apellidos'=>$_POST['user_apellidos'],'email'=>$_POST['user_email'],'password'=>$_POST['user_contraseña'],'tipo_usuario'=>$_POST['user_tipo_usuario']]);
          if ($msg===true)
            $info[] = 'El usuario '.$_POST['user_usuario'].' ha sido actualizado';
          else {
            $info[] = 'No se ha podido actualizar '.$_POST['user_usuario'];
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
    }
  } else { // Si los parámetros no son correctos: volver al listado
    header('Location: administracion.php');
  }
?>
