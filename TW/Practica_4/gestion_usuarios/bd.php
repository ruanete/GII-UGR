<?php
require_once('dbcredenciales.php');

// Conexión a la BBDD
// Devuelve:
// Si conexión ok  resource asociado a la BBDD
// Si error de conexión  un string con mensaje de error
function DB_conexion() {
  $db = mysqli_connect(DB_HOST,DB_USER,DB_PASSWD,DB_DATABASE);
  if (!$db)
    return "Error de conexión a la base de datos (".mysqli_connect_errno().") : ".mysqli_connect_error();
  // Establecer la codificación de los datos almacenados ("collation")
  mysqli_set_charset($db,"utf8");
  return $db;
}
// Desconexión de la BBDD
function DB_desconexion($db) {
  mysqli_close($db);
}

function getUsuarios($db) {
  $res = mysqli_query($db, "SELECT * from usuarios");

  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $tabla = mysqli_fetch_all($res,MYSQLI_ASSOC);
    } else { // No hay resultados para la consulta
      $tabla = [];
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
    } else { // Error en la consulta
      $tabla = false;
    }
    return $tabla;
}

function compruebaAdmin($db, $usuario, $contraseña) {
  $res = mysqli_query($db, "SELECT password FROM usuarios WHERE usuario='$usuario' and tipo_usuario='Administrador'");
  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $codificado = mysqli_fetch_array($res,MYSQLI_ASSOC);
      $contraseña_codificada = $codificado['password'];

      if(password_verify($contraseña, $contraseña_codificada))
        return true;
      else
        return false;
    }else{
      return false;
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
  } else { // Error en la consulta
      return false;
  }
}

function compruebaNormalUser($db, $usuario, $contraseña) {
  $res = mysqli_query($db, "SELECT password FROM usuarios WHERE usuario='$usuario' and tipo_usuario='Normal'");
  echo $contraseña;
  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $codificado = mysqli_fetch_array($res,MYSQLI_ASSOC);
      $contraseña_codificada = $codificado['password'];

      if(password_verify($contraseña, $contraseña_codificada))
        return true;
      else
        return false;
    }else{
      return false;
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
  } else { // Error en la consulta
      return false;
  }
}

function compruebaUsuario($db, $usuario, $contraseña){
  $res = mysqli_query($db, "SELECT password FROM usuarios WHERE usuario='$usuario'");
  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0 ) { // Si hay alguna tupla de respuesta
      $codificado = mysqli_fetch_array($res,MYSQLI_ASSOC);
      $contraseña_codificada = $codificado['password'];

      if(password_verify($contraseña, $contraseña_codificada))
        return true;
      else
        return false;
    }else{
      return false;
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
  } else { // Error en la consulta
      return false;
  }
}

function VIEW_listadoUsuarios($bd, $accion) {
  $result = mysqli_query($bd, "SELECT * FROM usuarios");
  //se despliega el resultado
  echo "<table>";
  echo "<tr>";
  echo "<th>Usuario</th>";
  echo "<th>Nombre</th>";
  echo "<th>Apellidos</th>";
  echo "<th>Email</th>";
  echo "<th>Contraseña</th>";
  echo "<th>Tipo de usuario</th>";
  echo "<th>Acción</th>";
  echo "</tr>";
  while ($row = mysqli_fetch_row($result)){
  	echo "<tr>";
      echo "<td>".$row[0]."</td>";
      echo "<td>".$row[1]."</td>";
      echo "<td>".$row[2]."</td>";
      echo "<td>".$row[3]."</td>";
      echo "<td>".$row[4]."</td>";
      echo "<td>".$row[5]."</td>";
      echo "<td class='user_botones'><form action='$accion' method='POST'>
            <input type='hidden' name='id' value='{$row['0']}' />
            <input type='submit' name='accion' value='Editar' />
            <input type='submit' name='accion' value='Borrar' />
            </form></td>";
    	echo "</tr>";
  }
  echo "</table>";
}

function DB_delUsuario($db,$id) {
  mysqli_query($db, "DELETE FROM usuarios WHERE usuario='$id'");
  if (mysqli_affected_rows($db)==1)
    return true;
  else
    return false;
}

function DB_actUsuario($db,$id,$datos) {
  $res = mysqli_query($db,"SELECT usuario FROM usuarios WHERE usuario='{$datos['usuario']}'");
  $usuario = mysqli_fetch_assoc($res);
  mysqli_free_result($res);

  if ($usuario['usuario']==$datos['usuario'] && $usuario['usuario']!=$id){
    $info[] = 'Ya hay otra cuenta con el mismo usuario.';
  }else {
    if(array_key_exists('password', $datos)){
      $password = password_hash($datos["password"], PASSWORD_DEFAULT);
    }else{
      $password = $datos['password'];
    }

    $res = mysqli_query($db, "UPDATE usuarios SET usuario='{$datos['usuario']}',nombre='{$datos['nombre']}', apellidos='{$datos['apellidos']}',
      email='{$datos['email']}', password='$password', tipo_usuario='{$datos['tipo_usuario']}' WHERE usuario='$id'");
    if (!$res) {
      $info[] = 'Error al actualizar';
      $info[] = mysqli_error($db);
    }
  }

  if (isset($info))
    return $info;
  else
    return true; // OK
}

function DB_addUsuario($db,$datos){
  $res = mysqli_query($db,"SELECT usuario FROM usuarios WHERE usuario='{$datos['user_usuario']}'");
  $usuario = mysqli_fetch_assoc($res);
  mysqli_free_result($res);

  if ($usuario['usuario']==$datos['user_usuario']){
    $info[] = 'Ya hay otra cuenta con el mismo usuario.';
  }else {
    $password = password_hash($datos["user_contraseña"], PASSWORD_DEFAULT);
    $res = mysqli_query($db,"INSERT INTO usuarios VALUES('{$datos['user_usuario']}','{$datos['user_nombre']}','{$datos['user_apellidos']}','{$datos['user_email']}','$password','{$datos['user_tipo_usuario']}')");

    if (!$res) {
      $info[] = 'Error al añadir nuevo usuario';
      $info[] = mysqli_error($db);
    }
  }

  if (isset($info))
    return $info;
  else
    return true; // OK
}

function DB_getUsuario($db, $id) {
  $res = mysqli_query($db, "SELECT * from usuarios WHERE usuario='$id'");

  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $tabla = mysqli_fetch_all($res,MYSQLI_ASSOC);
    } else { // No hay resultados para la consulta
      $tabla = [];
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
    } else { // Error en la consulta
      $tabla = false;
    }
    return $tabla;
}

?>
