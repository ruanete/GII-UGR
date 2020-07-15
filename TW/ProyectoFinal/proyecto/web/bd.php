<?php
require_once('dbcredenciales.php');
require_once('seccionbio.php');
require_once('disco.php');

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
  $usuario_clean = mysqli_real_escape_string($db,$usuario);
  $res = mysqli_query($db, "SELECT password FROM usuarios WHERE usuario='$usuario_clean' and tipo_usuario='Administrador'");
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
  $usuario_clean = mysqli_real_escape_string($db,$usuario);
  $res = mysqli_query($db, "SELECT password FROM usuarios WHERE usuario='$usuario_clean' and tipo_usuario='Normal'");
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
  $usuario_clean = mysqli_real_escape_string($db,$usuario);
  $res = mysqli_query($db, "SELECT password FROM usuarios WHERE usuario='$usuario_clean'");
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
  echo "<th>Telefono</th>";
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
      echo "<td>".$row[6]."</td>";
      echo "<td class='user_botones'><form action='$accion' method='GET'>
            <input type='hidden' name='id' value='{$row['0']}' />
            <input type='submit' name='editar_usuario' value='Editar' />
            <input type='submit' name='borrar_usuario' value='Borrar' />
            </form></td>";
    	echo "</tr>";
  }
  echo "</table>";
}

function DB_delUsuario($db,$id) {
  //$id_clean = filter_var($id, FILTER_SANITIZE_NUMBER_INT);
  mysqli_query($db, "DELETE FROM usuarios WHERE usuario='$id'");
  if (mysqli_affected_rows($db)==1){
    DB_addLog($db, "Se ha borrado el usuario $id");
    return true;
  }else
    return false;
}

function DB_actUsuario($db,$id,$datos) {
  $usuario_clean = mysqli_real_escape_string($db,$datos['usuario']);
  $nombre_clean = mysqli_real_escape_string($db,$datos['nombre']);
  $apellidos_clean = mysqli_real_escape_string($db,$datos['apellidos']);
  $email_clean = mysqli_real_escape_string($db,$datos['email']);
  $telefono_clean = mysqli_real_escape_string($db,$datos['telefono']);
  $tipo_usuario_clean = mysqli_real_escape_string($db,$datos['tipo_usuario']);

  $res = mysqli_query($db,"SELECT usuario FROM usuarios WHERE usuario='$usuario_clean'");
  $id_clean = filter_var($id, FILTER_SANITIZE_NUMBER_INT);
  $res2 = mysqli_query($db,"SELECT password FROM usuarios WHERE usuario='$id_clean'");
  $contraseña_bd = mysqli_fetch_assoc($res2);
  $usuario = mysqli_fetch_assoc($res);
  mysqli_free_result($res);
  mysqli_free_result($res2);

  if ($usuario['usuario']==$datos['usuario'] && $usuario['usuario']!=$id){
    $info[] = 'Ya hay otra cuenta con el mismo usuario.';
  }else {
    if(strcmp ($contraseña_bd["password"] , $datos["password"] ) == 0){
      $res = mysqli_query($db, "UPDATE usuarios SET usuario='$usuario_clean',nombre='$nombre_clean', apellidos='$apellidos_clean',
        email='$email_clean', telefono='$telefono_clean', tipo_usuario='$tipo_usuario_clean' WHERE usuario='$id'");
    }else{
      $password = password_hash($datos["password"], PASSWORD_DEFAULT);
      $res = mysqli_query($db, "UPDATE usuarios SET usuario='$usuario_clean',nombre='$nombre_clean', apellidos='$apellidos_clean',
        email='$email_clean', password='$password', telefono='$telefono_clean', tipo_usuario='$tipo_usuario_clean' WHERE usuario='$id'");
    }

    if (!$res) {
      $info[] = 'Error al actualizar';
      $info[] = mysqli_error($db);
    }
  }

  if (isset($info))
    return $info;
  else{
    if($_SESSION["sesion_admin"] != $datos['usuario']){
      $_SESSION["sesion_admin"]= $datos['usuario'];
    }
    DB_addLog($db, "Se ha modificado el usuario {$datos['usuario']}");
    return true; // OK
  }
}

function DB_addUsuario($db,$datos){
  $user_usuario_clean = mysqli_real_escape_string($db,$datos['user_usuario']);
  $user_nombre_clean = mysqli_real_escape_string($db,$datos['user_nombre']);
  $user_apellidos_clean = mysqli_real_escape_string($db,$datos['user_apellidos']);
  $user_email_clean = mysqli_real_escape_string($db,$datos['user_email']);
  $user_telefono_clean = mysqli_real_escape_string($db,$datos['user_tlf']);
  $user_tipo_usuario_clean = mysqli_real_escape_string($db,$datos['user_tipo_usuario']);

  $res = mysqli_query($db,"SELECT usuario FROM usuarios WHERE usuario='$user_usuario_clean'");
  $usuario = mysqli_fetch_assoc($res);
  mysqli_free_result($res);

  if ($usuario['usuario']==$datos['user_usuario']){
    $info[] = 'Ya hay otra cuenta con el mismo usuario.';
  }else {
    $password = password_hash($datos["user_contraseña"], PASSWORD_DEFAULT);
    $res = mysqli_query($db,"INSERT INTO usuarios VALUES('$user_usuario_clean','$user_nombre_clean','$user_apellidos_clean','$user_email_clean','$password','$user_telefono_clean','$user_tipo_usuario_clean')");

    if (!$res) {
      $info[] = 'Error al añadir nuevo usuario';
      $info[] = mysqli_error($db);
    }
  }

  if (isset($info))
    return $info;
  else{
    DB_addLog($db, "Se ha creado un nuevo usuario llamado {$datos['user_usuario']}");
    return true; // OK
  }
}

function DB_getUsuario($db, $id) {
  //$id_clean = filter_var($id, FILTER_SANITIZE_NUMBER_INT);
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

function getConciertos($db) {
  $res = mysqli_query($db, "SELECT * from conciertos");

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

function VIEW_listadoConciertos($bd, $accion) {
  $result = mysqli_query($bd, "SELECT * FROM conciertos");
  //se despliega el resultado
  echo "<table>";
  echo "<tr>";
  echo "<th>Codigo de concierto</th>";
  echo "<th>Fecha</th>";
  echo "<th>Ciudad</th>";
  echo "<th>Lugar</th>";
  echo "<th>Acción</th>";
  echo "</tr>";
  while ($row = mysqli_fetch_row($result)){
  	echo "<tr>";
      echo "<td>".$row[0]."</td>";
      echo "<td>".$row[1]."</td>";
      echo "<td>".$row[2]."</td>";
      echo "<td>".$row[3]."</td>";
      echo "<td class='user_botones'><form action='$accion' method='GET'>
            <input type='hidden' name='id' value='{$row['0']}' />
            <input type='submit' name='editar_concierto' value='Editar' />
            <input type='submit' name='borrar_concierto' value='Borrar' />
            </form></td>";
    	echo "</tr>";
  }
  echo "</table>";
}

function DB_addConcierto($db,$datos){
  $conc_fecha_clean = mysqli_real_escape_string($db,$datos['conc_fecha']);
  $conc_ciudad_clean = mysqli_real_escape_string($db,$datos['conc_ciudad']);
  $conc_lugar_clean = mysqli_real_escape_string($db,$datos['conc_lugar']);
  $res = mysqli_query($db,"SELECT fecha FROM conciertos WHERE fecha='$conc_fecha_clean'");
  $usuario = mysqli_fetch_assoc($res);
  mysqli_free_result($res);

  if ($usuario['fecha']==$datos['conc_fecha']){
    $info[] = 'Ya hay otro concierto con la misma fecha.';
  }else {
    $res = mysqli_query($db,"INSERT INTO conciertos (fecha,ciudad,lugar) VALUES (str_to_date('$conc_fecha_clean','%Y-%m-%d'),'$conc_ciudad_clean','$conc_lugar_clean')");

    if (!$res) {
      $info[] = 'Error al añadir nuevo concierto';
      $info[] = mysqli_error($db);
    }
  }

  if (isset($info))
    return $info;
  else{
    DB_addLog($db, "Se ha añadido un nuevo concierto en {$datos['conc_ciudad']} con lugar en {$datos['conc_lugar']}");
    return true; // OK
  }
}

function DB_getConcierto($db, $id) {
  $id_clean = filter_var($id, FILTER_SANITIZE_NUMBER_INT);
  $res = mysqli_query($db, "SELECT * from conciertos WHERE codconcierto='$id_clean'");

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

function DB_actConcierto($db,$id,$datos) {
  $id_clean = filter_var($id, FILTER_SANITIZE_NUMBER_INT);
  $fecha_clean = mysqli_real_escape_string($db,$datos['fecha']);
  $ciudad_clean = mysqli_real_escape_string($db,$datos['ciudad']);
  $lugar_clean = mysqli_real_escape_string($db,$datos['lugar']);
  $res = mysqli_query($db,"SELECT fecha FROM conciertos WHERE fecha='$fecha_clean'");
  $usuario = mysqli_fetch_assoc($res);
  mysqli_free_result($res);

  $res2 = mysqli_query($db,"SELECT codconcierto FROM conciertos WHERE fecha='$fecha_clean'");
  $idcomprueba = mysqli_fetch_assoc($res2);
  mysqli_free_result($res2);

  if ($usuario['fecha']==$datos['fecha'] && $id_clean != $idcomprueba["codconcierto"]){
    $info[] = 'Ya hay otra cuenta con la misma fecha.';
  }else {
    $res = mysqli_query($db, "UPDATE conciertos SET fecha='$fecha_clean',ciudad='$ciudad_clean', lugar='$lugar_clean' WHERE codconcierto='$id_clean'");
    if (!$res) {
      $info[] = 'Error al actualizar';
      $info[] = mysqli_error($db);
    }
  }

  if (isset($info))
    return $info;
  else{
    DB_addLog($db, "Se ha actualizado un concierto a la ciudad {$datos['ciudad']} con lugar en {$datos['lugar']}");
    return true; // OK
  }
}

function DB_delConcierto($db,$id) {
  $id_clean = filter_var($id, FILTER_SANITIZE_NUMBER_INT);
  mysqli_query($db, "DELETE FROM conciertos WHERE codconcierto='$id_clean'");
  if (mysqli_affected_rows($db)==1){
    DB_addLog($db, "Se ha borrado un concierto con id $id");
    return true;
  }else
    return false;
}

function DB_getSecciones($db) {
  $res = mysqli_query($db, "SELECT titulo, link, cuerpo, id from secciones");
  $secciones = array();

  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $tabla = mysqli_fetch_all($res,MYSQLI_ASSOC);
      foreach ($tabla as $fila) {
        $titulo = $fila['titulo'];
        $link = $fila['link'];
        $cuerpo = $fila['cuerpo'];
        $id = $fila['id'];
        $secciones[] = new SeccionBio($titulo, $link, $cuerpo, $id);

      }
    } else { // No hay resultados para la consulta
      $tabla = [];
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
    } else { // Error en la consulta
      $tabla = false;
    }
    return $secciones;
}

function DB_getSeccionID($db, $seccion){
  if($db){
    $titulo = mysqli_real_escape_string($db,$seccion->titulo);
    $res = mysqli_query($db,"SELECT id from `canciones` where titulo='$titulo';");
    if(mysqli_num_rows($res) == 1){
      $tupla = mysqli_fetch_array($res);
      $id = $tupla['id'];
      return $id;
    }
    else
      return -1;
  }
}

function DB_updateSeccion($db, $seccion) {
  $sql = "UPDATE `secciones` SET titulo=?, link=?,  cuerpo=? ";
  if($db){
    $id = $seccion->id;
    if($id != -1 && $seccion->titulo !== ""){
      $sql .= " WHERE id=?;";
      $stmt = $db->prepare($sql);
      $stmt->bind_param('sssi', $seccion->titulo, $seccion->img, $seccion->cuerpo, $id);
      $stmt->execute();
      if($stmt->affected_rows == 1){
        DB_addLog($db, "Se ha modificado la seccion con id #$id");
        return true;
      }
    }
    else
      return false;
  }
  else{
    echo mysqli_error($db);
  }
  return false;
}

function DB_createSeccion($db, $seccion){
  $sql = "INSERT INTO `secciones` (titulo,link,cuerpo) VALUES (?, ?, ?)";
  if($db){
    $stmt = $db->prepare($sql);
    $stmt->bind_param('sss', $seccion->titulo, $seccion->img, $seccion->cuerpo);
    $stmt->execute();
    if($stmt->affected_rows == 1){
      DB_addLog($db, "Se ha creado una nueva sección en la biografia con titulo $seccion->titulo");
      return true;
    }
  }
  else{
    echo mysqli_error($db);
  }
  return false;
}

function DB_borrarSeccion($db, $id){
  $sql = "DELETE FROM `secciones` WHERE id=?";
  if($db){
    $stmt = $db->prepare($sql);
    $stmt->bind_param('i', $id);
    $stmt->execute();
    if($stmt->affected_rows == 1){
      DB_addLog($db, "Se ha borrado la sección de la biografia con id #$id");
      return true;
    }
  }
  else{
    echo mysqli_error($db);
  }
  return false;
}


function DB_getCanciones($db) {
  $res = mysqli_query($db, "SELECT titulo, duracion, id_disco, id from canciones");
  $secciones = array();

  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $tabla = mysqli_fetch_all($res,MYSQLI_ASSOC);
      foreach ($tabla as $fila) {
        $titulo = $fila['titulo'];
        $duracion = $fila['duracion'];
        $id_disco = $fila['id_disco'];
        $id = $fila['id'];
        $secciones[] = new Cancion($titulo, $duracion, $id, $id_disco);
      }
    } else { // No hay resultados para la consulta
      $tabla = [];
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
    } else { // Error en la consulta
      $tabla = false;
    }
    return $secciones;
}


function DB_getCancionesDiscoID($db, $id_disco) {
  $id_disco_clean = filter_var($id_disco, FILTER_SANITIZE_NUMBER_INT);
  $res = mysqli_query($db, "SELECT titulo, duracion, id_disco, id from canciones WHERE id_disco=$id_disco_clean");
  $secciones = array();

  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $tabla = mysqli_fetch_all($res,MYSQLI_ASSOC);
      foreach ($tabla as $fila) {
        $titulo = $fila['titulo'];
        $duracion = $fila['duracion'];
        $id_disco = $fila['id_disco'];
        $id = $fila['id'];
        $secciones[] = new Cancion($titulo, $duracion, $id, $id_disco);
      }
    } else { // No hay resultados para la consulta
      $tabla = [];
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
    } else { // Error en la consulta
      $tabla = false;
    }
    return $secciones;
}

function DB_getCancionesDisco($db, $disco){
  return DB_getCancionesDiscoID($db, $disco->id);
}

function DB_getCancionID($db, $cancion){
  if($db){
    $titulo = mysqli_real_escape_string($db,$cancion->titulo);
    $res = mysqli_query($db,"SELECT id from `canciones` where titulo='$titulo';");
    if(mysqli_num_rows($res) == 1){
      $tupla = mysqli_fetch_array($res);
      $id = $tupla['id'];
      return $id;
    }
    else
      return -1;
  }
}

function DB_updateCancion($db, $cancion) {
  $sql = "UPDATE `canciones` SET titulo=?, duracion=?,  id_disco=? ";
  if($db){
    $id = $cancion->id;
    if($id != -1 && $cancion->titulo !== "" && $cancion->duracion > 0){
      $sql .= " WHERE id=?;";
      $stmt = $db->prepare($sql);
      $stmt->bind_param('siii', $cancion->titulo, $cancion->duracion,  $cancion->id_disco, $id);
      $stmt->execute();
      if($stmt->affected_rows == 1){
        DB_addLog($db, "Se ha modificado la cancion con id #$id y titulo $cancion->titulo");
        return true;
      }
    }
    else
      return false;
  }
  else{
    echo mysqli_error($db);
  }
  return false;
}

function DB_createCancion($db, $cancion){
  $sql = "INSERT INTO `canciones` (titulo,duracion,id_disco) VALUES (?, ?, ?)";
  if($db){
    if($cancion->titulo !== "" && $cancion->duracion > 0){
      $stmt = $db->prepare($sql);
      $stmt->bind_param('sii', $cancion->titulo, $cancion->duracion, $cancion->id_disco);
      $stmt->execute();
      if($stmt->affected_rows == 1){
        DB_addLog($db, "Se ha creado una nueva cancion con titulo $cancion->titulo");
        return true;
      }
    }
  }
  else{
    echo mysqli_error($db);
  }
  echo $sql;
  print_r($cancion);
  return false;
}

function DB_borrarCancion($db, $id){
  $sql = "DELETE FROM `canciones` WHERE id=?";
  if($db){
    $stmt = $db->prepare($sql);
    $stmt->bind_param('i', $id);
    $stmt->execute();
    if($stmt->affected_rows == 1){
      DB_addLog($db, "Se ha borrado la cancion con id #$id");
      return true;
    }
  }
  else{
    echo mysqli_error($db);
  }
  return false;
}


function DB_getDiscoNoSencillos($db) {
  $res = mysqli_query($db, "SELECT titulo, img, web, sencillo, anio, id, precio from discos  where sencillo=0");
  $discos = array();

  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $tabla = mysqli_fetch_all($res,MYSQLI_ASSOC);
      foreach ($tabla as $fila) {
        $discos[] = DB_constructDiscoFromRow($fila);
      }
    } else { // No hay resultados para la consulta
      $tabla = [];
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
    } else { // Error en la consulta
      $tabla = false;
    }
    return $discos;
}

function DB_getDiscoSencillos($db) {
  $res = mysqli_query($db, "SELECT titulo, img, web, sencillo, anio, id, precio from discos where sencillo=1");
  $discos = array();

  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $tabla = mysqli_fetch_all($res,MYSQLI_ASSOC);
      foreach ($tabla as $fila) {
        $discos[] = DB_constructDiscoFromRow($fila);
      }
    } else { // No hay resultados para la consulta
      $tabla = [];
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
    } else { // Error en la consulta
      $tabla = false;
    }
    return $discos;
}


function DB_getDisco($db) {
  $res = mysqli_query($db, "SELECT titulo, img, web, sencillo, anio, id, precio from discos ORDER BY anio DESC");
  $discos = array();

  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $tabla = mysqli_fetch_all($res,MYSQLI_ASSOC);
      foreach ($tabla as $fila) {
        $discos[] = DB_constructDiscoFromRow($fila);
      }
    } else { // No hay resultados para la consulta
      $tabla = [];
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
    } else { // Error en la consulta
      $tabla = false;
    }
    return $discos;
}

function DB_getDiscoConCaratula($db) {
  $res = mysqli_query($db, "SELECT titulo, img, web, sencillo, anio, id, precio from discos where img!=\"\"");
  $discos = array();

  if ($res) { // Si no hay error
    if (mysqli_num_rows($res)>0) { // Si hay alguna tupla de respuesta
      $tabla = mysqli_fetch_all($res,MYSQLI_ASSOC);
      foreach ($tabla as $fila) {
        $discos[] = DB_constructDiscoFromRow($fila);
      }
    } else { // No hay resultados para la consulta
      $tabla = [];
    }
    mysqli_free_result($res); // Liberar memoria de la consulta
    } else { // Error en la consulta
      $tabla = false;
    }
    return $discos;
}

function DB_constructDiscoFromRow($fila){
  $titulo = $fila['titulo'];
  $web = $fila['web'];
  $sencillo = $fila['sencillo'];
  $img = $fila['img'];
  $anio = $fila['anio'];
  $precio = $fila['precio'];
  $id = $fila['id'];
  return new Disco($titulo, $img, $web, $sencillo, $anio, $precio, $id);
}

function DB_getDiscoID($db, $disco){
  if($db){
    $titulo = mysqli_real_escape_string($db,$disco->titulo);
    $res = mysqli_query($db,"SELECT id from `canciones` where titulo='$titulo';");
    if(mysqli_num_rows($res) == 1){
      $tupla = mysqli_fetch_array($res);
      $id = $tupla['id'];
      return $id;
    }
    else
      return -1;
  }
}

function DB_getDiscoByID($db, $id){
  if($db){
    $id_clean = filter_var($id, FILTER_SANITIZE_NUMBER_INT);
    $res = mysqli_query($db,"SELECT titulo, img, web, sencillo, anio, id, precio from `discos` WHERE id=$id_clean;");
    if(mysqli_num_rows($res) == 1){
      $tupla = mysqli_fetch_array($res);
      return DB_constructDiscoFromRow($tupla);
    }
    else
      return null;
  }
}
function DB_updateDisco($db, $disco) {
  $sql = "UPDATE `discos` SET titulo=?, img=?,  web=?, sencillo=?, anio=?, precio=? ";
  if($db){
    $id = $disco->id;
    if($id != -1 && $disco->titulo !== ""){
      $sql .= " WHERE id=?;";
      $stmt = $db->prepare($sql);
      $stmt->bind_param('sssiidi', $disco->titulo, $disco->img, $disco->web, $disco->sencillo, $disco->anio, $disco->precio, $id);
      $stmt->execute();
      if($stmt->affected_rows == 1){
        DB_addLog($db, "Se ha modificado el disco con id #$id y titulo $disco->titulo");
        return true;
      }
    }
    else
      return false;
  }
  else{
    echo mysqli_error($db);
  }
  return false;
}

function DB_createDisco($db, $disco){
  $sql = "INSERT INTO `discos` (titulo,img,web,sencillo,anio,precio) VALUES (?, ?, ?, ?, ?, ?)";
  if($db){
    $stmt = $db->prepare($sql);
    $stmt->bind_param('sssiid', $disco->titulo, $disco->img, $disco->web, $disco->sencillo, $disco->anio, $disco->precio);
    $stmt->execute();
    if($stmt->affected_rows == 1){
      DB_addLog($db, "Se ha creado un nuevo disco con titulo $disco->titulo");
      return true;
    }
  }
  else{
    echo mysqli_error($db);
  }
  return false;
}

function DB_borrarDisco($db, $id){
  $sql = "DELETE FROM `discos` WHERE id=?";
  if($db){
    $stmt = $db->prepare($sql);
    $stmt->bind_param('i', $id);
    $stmt->execute();
    if($stmt->affected_rows == 1){
      DB_addLog($db, "Se ha borrado el disco con id #$id");
      return true;
    }
  }
  else{
    echo mysqli_error($db);
  }
  return false;
}


function VIEW_TablaConciertos($bd) {
  $set = mysqli_query($bd, "SET lc_time_names = 'es_ES'");
  $result = mysqli_query($bd, "SELECT date_format(fecha,'%d %M de %Y'), ciudad, lugar FROM conciertos");
  //se despliega el resultado
  echo "<table>";
  echo "<tr>";
  echo "<th>Fecha</th>";
  echo "<th>Ciudad</th>";
  echo "<th>Lugar</th>";
  echo "</tr>";
  while ($row = mysqli_fetch_row($result)){
  	echo "<tr>";
      echo "<td>".$row[0]."</td>";
      echo "<td>".$row[1]."</td>";
      echo "<td>".$row[2]."</td>";
    	echo "</tr>";
  }
  echo "</table>";
}

function VIEW_TablalogEventos($bd) {
  $set = mysqli_query($bd, "SET lc_time_names = 'es_ES'");
  $result = mysqli_query($bd, "SELECT descripcion, date_format(fecha,'%d %M de %Y a las %H:%i') FROM logEventos  ORDER BY fecha DESC");
  //se despliega el resultado
  echo "<table>";
  echo "<tr>";
  echo "<th>Descripción</th>";
  echo "<th>Fecha</th>";
  echo "</tr>";
  while ($row = mysqli_fetch_row($result)){
  	echo "<tr>";
      echo "<td>".$row[0]."</td>";
      echo "<td>".$row[1]."</td>";
    	echo "</tr>";
  }
  echo "</table>";
}

function DB_addLog($db,$mensaje){
  $mensaje_clean = mysqli_real_escape_string($db,$mensaje);
  $res = mysqli_query($db,"INSERT INTO logEventos (descripcion,fecha) values('$mensaje_clean',now())");
  if (!$res) {
    $info[] = 'Error al añadir nuevo concierto';
    $info[] = mysqli_error($db);
  }

  if (isset($info))
    return $info;
  else
    return true; // OK
}

function getPedidos($db) {
  $res = mysqli_query($db, "SELECT * from pedidos");

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


function VIEW_listadoPedidosPendientes($bd, $accion) {
  $result = mysqli_query($bd, "SELECT * FROM pedidos WHERE estado='Pendiente'");
  $result2 = mysqli_query($bd, "SELECT titulo, precio FROM pedidos p, discos d WHERE p.idDisco=d.id");
  //se despliega el resultado
  echo "<table>";
  echo "<tr>";
  echo "<th>Codigo de pedido</th>";
  echo "<th>Fecha</th>";
  echo "<th>Estado</th>";
  echo "<th>Articulo</th>";
  echo "<th>Precio</th>";
  echo "<th>Codigo de articulo</th>";
  echo "<th>Acción</th>";
  echo "</tr>";
  while ($row = mysqli_fetch_row($result) and $row2 = mysqli_fetch_row($result2)){
  	echo "<tr>";
      echo "<td>".$row[0]."</td>";
      echo "<td>".$row[1]."</td>";
      echo "<td>".$row[2]."</td>";
      echo "<td>".$row2[0]."</td>";
      echo "<td>".$row2[1]."</td>";
      echo "<td>".$row[6]."</td>";
      echo "<td class='user_botones'><form action='$accion' method='GET'>
            <input type='hidden' name='id' value='{$row['0']}' />
            <input type='submit' name='aceptar_pedido' value='Aceptar' />
            <input type='submit' name='denegar_pedido' value='Denegar' />
            </form></td>";
    	echo "</tr>";
  }
  echo "</table>";
}

function DB_editPedidoAceptar($db,$datos,$user) {
  $mensaje_correo_clean = mysqli_real_escape_string($db,$datos['mensaje_correo']);
  $id_clean = filter_var($datos['id'], FILTER_SANITIZE_NUMBER_INT);
  $res = mysqli_query($db, "UPDATE pedidos SET estado='Aceptado', correoEnviado='$mensaje_correo_clean', usuarioGestor='$user' WHERE codped='$id_clean'");
  if (!$res) {
    $info[] = 'Error al actualizar';
    $info[] = mysqli_error($db);
  }

  if (isset($info))
    return $info;
  else{
    DB_addLog($db, "Se ha aceptado el pedido con id #{$datos['id']}");
    return true; // OK
  }
}

function DB_editPedidoDenegar($db,$datos,$user) {
  $motivo_denied_clean = mysqli_real_escape_string($db,$datos['motivo_denied']);
  $mensaje_correo_clean = mysqli_real_escape_string($db,$datos['mensaje_correo']);
  $id_clean = filter_var($datos['id'], FILTER_SANITIZE_NUMBER_INT);
  $res = mysqli_query($db, "UPDATE pedidos SET estado='Denegado', motivoDenied='$motivo_denied_clean', correoEnviado='$mensaje_correo_clean', usuarioGestor='$user' WHERE codped='$id_clean'");
  if (!$res) {
    $info[] = 'Error al actualizar';
    $info[] = mysqli_error($db);
  }

  if (isset($info))
    return $info;
  else{
    DB_addLog($db, "Se ha denegado el pedido con id #{$datos['id']}");
    return true; // OK
  }
}

function VIEW_listadoPedidos($bd, $accion) {
  $result = mysqli_query($bd, "SELECT * FROM pedidos WHERE estado='Denegado' or estado='Aceptado' ORDER BY estado");
  $result2 = mysqli_query($bd, "SELECT titulo, precio FROM pedidos p, discos d WHERE p.idDisco=d.id");
  //se despliega el resultado
  echo "<table>";
  echo "<tr>";
  echo "<th>Codigo de pedido</th>";
  echo "<th>Fecha</th>";
  echo "<th>Estado</th>";
  echo "<th>Mensaje correo</th>";
  echo "<th>Motivo denegación</th>";
  echo "<th>Usuario gestor</th>";
  echo "<th>Articulo</th>";
  echo "<th>Precio</th>";
  echo "</tr>";
  while ($row = mysqli_fetch_row($result) and $row2 = mysqli_fetch_row($result2)){
  	echo "<tr>";
      echo "<td>".$row[0]."</td>";
      echo "<td>".$row[1]."</td>";
      echo "<td>".$row[2]."</td>";
      echo "<td>".$row[3]."</td>";
      echo "<td>".$row[4]."</td>";
      echo "<td>".$row[5]."</td>";
      echo "<td>".$row2[0]."</td>";
      echo "<td>".$row2[1]."</td>";

    	echo "</tr>";
  }
  echo "</table>";
}

function getDiscos($db) {
  $res = mysqli_query($db, "SELECT * from discos");

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

function VIEW_listadoDiscos($bd, $accion) {
  $result = mysqli_query($bd, "SELECT id, titulo, precio FROM discos");
  //se despliega el resultado
  echo "<table>";
  echo "<tr>";
  echo "<th>Codigo de disco</th>";
  echo "<th>Titulo</th>";
  echo "<th>Precio</th>";
  echo "<th>Acción</th>";
  echo "</tr>";
  while ($row = mysqli_fetch_row($result)){
  	echo "<tr>";
      echo "<td>".$row[0]."</td>";
      echo "<td>".$row[1]."</td>";
      echo "<td>".$row[2]."</td>";
      echo "<td class='user_botones'><form action='$accion' method='GET'>
            <input type='hidden' name='id' value='{$row['0']}' />
            <input type='submit' name='modificar_precio' value='Modificar precio' />
            </form></td>";
    	echo "</tr>";
  }
  echo "</table>";
}

function DB_editPrecioDisco($db,$datos) {
  $id_clean = filter_var($datos['id'], FILTER_SANITIZE_NUMBER_INT);
  $disc_precio_clean = mysqli_real_escape_string($db,$datos['disc_precio']);
  $res = mysqli_query($db, "UPDATE discos SET precio='$disc_precio_clean' WHERE id='$id_clean'");
  if (!$res) {
    $info[] = 'Error al actualizar';
    $info[] = mysqli_error($db);
  }

  if (isset($info))
    return $info;
  else{
    DB_addLog($db, "Se ha modificado el precio del disco con id #{$datos['id']}");
    return true; // OK
  }
}

function VIEW_checkboxLugares($bd) {
  $result = mysqli_query($bd, "SELECT lugar FROM conciertos");

  if (!$result) {
    $info[] = 'Error al consultar';
    $info[] = mysqli_error($db);
  }

  if (isset($info))
    return $info;
  else{
    while ($row = mysqli_fetch_row($result)){
      echo "<input type=\"checkbox\" name=\"lugares[]\" value=\"$row[0]\"> $row[0]<br>";
    }
    return true;
  }
}

function busquedaTituloDisco($bd, $palabra){
  if($palabra!=""){
    $palabra_clean = mysqli_real_escape_string($bd,$palabra);
    $result = mysqli_query($bd, "SELECT titulo FROM discos WHERE titulo LIKE '%$palabra_clean%'");
  }else {
    echo "<h2>No se han encontrado resultados.</h2>";
    return false;
  }

  if (!$result) {
    $info[] = 'Error al consultar';
    $info[] = mysqli_error($db);
  }

  if (isset($info))
    return $info;
  else{
    if(mysqli_num_rows($result)>0){
      echo "<ul>";
      while ($row = mysqli_fetch_row($result)){
        echo "<li>".$row[0]."</li>";
      }
      echo "</ul>";
    }else{
      echo "<h2>No se han encontrado resultados.</h2>";
    }
    return true;
  }
}

function busquedaConciertoFecha($bd, $f_ini, $f_fin){
  $f_ini_clean = mysqli_real_escape_string($bd,$f_ini);
  $f_fin_clean = mysqli_real_escape_string($bd,$f_fin);
  $result = mysqli_query($bd, "SELECT fecha, ciudad, lugar FROM conciertos WHERE fecha>='$f_ini_clean' AND fecha<='$f_fin_clean'");

  if (!$result) {
    $info[] = 'Error al consultar';
    $info[] = mysqli_error($db);
  }

  if (isset($info))
    return $info;
  else{
    if(mysqli_num_rows($result)>0){
      echo "<ul>";
      while ($row = mysqli_fetch_row($result)){
        echo "<li>".$row[0]." ".$row[1]."  ".$row[2]."</li>";
      }
      echo "</ul>";
    }else{
      echo "<h2>No se han encontrado resultados.</h2>";
    }
    return true;
  }
}

function busquedaConciertoLugar($bd, $lugares){
  for($i = 0; $i<count($lugares); $i++){
    $lugar = mysqli_real_escape_string($bd,$lugares[$i]);
    $result[$i] = mysqli_query($bd, "SELECT fecha, ciudad, lugar FROM conciertos WHERE lugar='$lugar'");
  }

  if (!$result) {
    $info[] = 'Error al consultar';
    $info[] = mysqli_error($db);
  }

  $comprueba = false;

  if (isset($info))
    return $info;
  else{
    echo "<ul>";
    for($i = 0; $i<count($result); $i++){
      if(mysqli_num_rows($result[$i])>0){
        $comprueba = true;
        while($i!=count($lugares)){
          while ($row = mysqli_fetch_row($result[$i])){
            echo "<li>".$row[0]." ".$row[1]."  ".$row[2]."</li>";
          }
          $i++;
        }
      }
    }
    if($comprueba==false)
      echo "<h2>No se han encontrado resultados.</h2>";
    echo "</ul>";
    return true;
  }
}

function busquedaConciertoLugarFecha($bd, $lugares, $f_ini, $f_fin){
  $f_ini_clean = mysqli_real_escape_string($bd,$f_ini);
  $f_fin_clean = mysqli_real_escape_string($bd,$f_fin);
  for($i = 0; $i<count($lugares); $i++){
    $lugar = mysqli_real_escape_string($bd,$lugares[$i]);
    $result[$i] = mysqli_query($bd, "SELECT fecha, ciudad, lugar FROM conciertos WHERE lugar='$lugar' AND fecha>='$f_ini_clean' AND fecha<='$f_fin_clean'");
  }

  if (!$result) {
    $info[] = 'Error al consultar';
    $info[] = mysqli_error($db);
  }

  $comprueba = false;

  if (isset($info))
    return $info;
  else{
    echo "<ul>";
    for($i = 0; $i<count($result); $i++){
      if(mysqli_num_rows($result[$i])>0){
        $comprueba = true;
        while($i!=count($lugares)){
          while ($row = mysqli_fetch_row($result[$i])){
            echo "<li>".$row[0]." ".$row[1]."  ".$row[2]."</li>";
          }
          $i++;
        }
      }
    }
    if($comprueba==false)
      echo "<h2>No se han encontrado resultados.</h2>";
    echo "</ul>";
    return true;
  }
}

function busquedaDiscosFecha($bd, $f_ini, $f_fin){
  $f_ini_clean = mysqli_real_escape_string($bd,$f_ini);
  $f_fin_clean = mysqli_real_escape_string($bd,$f_fin);
  $fini = substr($f_ini_clean, 0, 4);
  $ffin = substr($f_fin_clean, 0, 4);
  $result = mysqli_query($bd, "SELECT titulo FROM discos WHERE anio>='$fini' AND anio<='$ffin'");

  if (!$result) {
    $info[] = 'Error al consultar';
    $info[] = mysqli_error($db);
  }

  if (isset($info))
    return $info;
  else{
    if(mysqli_num_rows($result)>0){
      echo "<ul>";
      while ($row = mysqli_fetch_row($result)){
        echo "<li>".$row[0]."</li>";
      }
      echo "</ul>";
    }else{
      echo "<h2>No se han encontrado resultados.</h2>";
    }
    return true;
  }
}

function busquedaDiscoPalabraFecha($bd, $palabra, $f_ini, $f_fin){
  $f_ini_clean = mysqli_real_escape_string($bd,$f_ini);
  $f_fin_clean = mysqli_real_escape_string($bd,$f_fin);
  $fini = substr($f_ini_clean, 0, 4);
  $ffin = substr($f_fin_clean, 0, 4);
  $palabra_clean = mysqli_real_escape_string($bd,$palabra);
  $result = mysqli_query($bd, "SELECT titulo FROM discos WHERE anio>='$fini' AND anio<='$ffin' AND titulo LIKE '%$palabra_clean%'");

  if (!$result) {
    $info[] = 'Error al consultar';
    $info[] = mysqli_error($db);
  }

  if (isset($info))
    return $info;
  else{
    if(mysqli_num_rows($result)>0){
      echo "<ul>";
      while ($row = mysqli_fetch_row($result)){
        echo "<li>".$row[0]."</li>";
      }
      echo "</ul>";
    }else{
      echo "<h2>No se han encontrado resultados.</h2>";
    }
    return true;
  }
}

function DB_backup($db){
  // Obtener listado de tablas
  $tablas = array();
  $result = mysqli_query($db,'SHOW TABLES');
  while($row = mysqli_fetch_row($result))
    $tablas[] = $row[0];

  // Salvar cada tabla
  $salida = '';
  foreach($tablas as $tab) {
    $result = mysqli_query($db, 'SELECT * FROM '.$tab);
    $num = mysqli_num_fields($result);
    $salida .= 'DROP TABLE ' .$tab.';';
    $row2 = mysqli_fetch_row(mysqli_query($db,'SHOW CREATE TABLE '.$tab));
    $salida .= "\n\n" .$row2[1].";\n\n";  // row2[0]=nombre de tabla
    while($row = mysqli_fetch_row($result)) {
      $salida .= 'INSERT INTO '.$tab.' VALUES(';
      for($j=0; $j<$num; $j++) {
        $row[$j] = addslashes($row[$j]);
        $row[$j] = preg_replace("/\n/","\\n",$row[$j]);

        if(isset($row[$j]))
          $salida .=  '"'.$row[$j].'"';
        else
          $salida .= '""';

        if($j < ($num-1)) $salida .= ',';
      }
      $salida .= ");\n";
    }
    $salida .= "\n\n\n";
  }
  return $salida;
}

function DB_clearALL($db){

  mysqli_query($db,'SET FOREIGN_KEY_CHECKS=0');

  $result = mysqli_query($db,'SHOW TABLES');
  $errores = array();
  while($row= mysqli_fetch_row($result)){
    $sql = 'DELETE FROM ';
    if($row[0] !== "usuarios"){
      $sql .= "`$row[0]`";
    }
    else{
      $sql .= "`$row[0]` WHERE usuario!='admin' AND usuario!='gpedidos'";
    }
    if(!mysqli_query($db,$sql))
      $errores[] = mysqli_error($db);
  }

  mysqli_query($db,'SET FOREIGN_KEY_CHECKS=1');

  return $errores;
}

function DB_restore($db, $f){
  mysqli_query($db,'SET FOREIGN_KEY_CHECKS=0');

  $result = mysqli_query($db,'SHOW TABLES');
  while($row= mysqli_fetch_row($result))
    mysqli_query($db,'DELETE FROM '.$row[0]);

  $error = array();
  $sql = file_get_contents($f);
  $queries= explode(';',$sql);
  foreach($queries as $q){
    $quer = trim($q);
    if($quer !== ""){
      if(!mysqli_query($db,$quer))
        $error[] = mysqli_error($db);
    }
  }

  mysqli_query($db,'SET FOREIGN_KEY_CHECKS=1');

  return $error;
}

?>
