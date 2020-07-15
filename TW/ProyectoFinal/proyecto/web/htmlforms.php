<script type="text/javascript" src="./js/ValidacionFormularios.js"></script>

<?php

function msgCount($msg) {
  if (is_array($msg))
    if (count($msg)==0)
      return 0;
    else
      return msgCount($msg[0])+msgCount(array_slice($msg,1));
  else if (!is_bool($msg))
    return 1;
  else
    return 0;
}

function msgError($msg,$tipo='msgerror'){
  echo "<div class='$tipo'>";
  _msgErrorR($msg);
  echo '</div>';
}

function _msgErrorR($msg) {
  if (is_array($msg))
    foreach ($msg as $v)
      _msgErrorR($v);
  else
    echo "<p>$msg</p>";
}

function FORM_editUsuario($titulo,$datos,$accion, $url) {
  if (isset($datos['editable']) && $datos['editable']=="false"){
    $disabled='readonly="readonly"';
    $disabled_select='disabled';
  }else{
    $disabled='';
    $disabled_select='';
  }

  $tipo_usuario = $datos[0]["tipo_usuario"];

  if($tipo_usuario === "Administrador"){
    $selectedAdmin = 'selected';
    $selectedGestor = '';
  }else{
    $selectedGestor = 'selected';
    $selectedAdmin = '';
  }

  $id = $datos["id"];

  echo <<< HTML
  <div class='frm_usuario'> <form action='$url' method='POST' onsubmit="return validarUsuario();">
  <h3>$titulo</h3>
  <input type='hidden' name='id' value='{$datos["id"]}'/>
  <div class='frm_usuario_input'><label for='user_usuario'>Usuario:</label>
    <input type='text' id="usuario" name='user_usuario' value='{$datos[0]["usuario"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_nombre'>Nombre:</label>
    <input type='text' id="nombre" name='user_nombre' value='{$datos[0]["nombre"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_apellidos'>Apellidos:</label>
    <input type='text' id="apellidos" name='user_apellidos' value='{$datos[0]["apellidos"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_email'>Email:</label>
    <input type='text' id="email" name='user_email' value='{$datos[0]["email"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_contraseña'>Contraseña:</label>
    <input type='text' id="contraseña" name='user_contraseña' value='{$datos[0]["password"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_tlf'>Telefono:</label>
    <input type='text' id="telefono" name='user_tlf' value='{$datos[0]["telefono"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_tipo_usuario'>Tipo de usuario:</label>
    <select name="user_tipo_usuario" id="tipo_usuario" selected='{$datos[0]["tipo_usuario"]}'>
      <option $selectedAdmin $disabled_select>Administrador</option>
      <option $selectedGestor $disabled_select>Gestor_Compras</option>
    </select>
  <div class='frm_usuario_input'>
    <input type='submit' name='accion' value='$accion' />
    <input type="button" onclick="location.href='administracion.php?editar_usuarios=yes';" name="accion" value="Cancelar"></div>
  </form> </div>
HTML;
}

function FORM_newUsuario($titulo,$accion) {
  $hoy=date("Y-m-d");
  echo <<< HTML
  <div class='frm_usuario'> <form action='panelUsuarios.php?nuevo_usuario=Crear+un+nuevo+usuario' method='POST' onsubmit="return validarUsuario();">
  <h3>$titulo</h3>
  <div class='frm_usuario_input'><label for='user_usuario'>Usuario:</label>
    <input type='text' id="usuario" name='user_usuario'/></div>
  <div class='frm_usuario_input'> <label for='user_nombre'>Nombre:</label>
    <input type='text' id="nombre" name='user_nombre'/></div>
  <div class='frm_usuario_input'> <label for='user_apellidos'>Apellidos:</label>
    <input type='text' id="apellidos" name='user_apellidos'/></div>
  <div class='frm_usuario_input'> <label for='user_email'>Email:</label>
    <input type='text' id="email" name='user_email'/></div>
  <div class='frm_usuario_input'> <label for='user_contraseña'>Contraseña:</label>
    <input type='password' id="contraseña" name='user_contraseña'/></div>
  <div class='frm_usuario_input'> <label for='user_tlf'>Telefono:</label>
    <input type='text' id="telefono" name='user_tlf'/></div>
  <div class='frm_usuario_input'> <label for='user_tipo_usuario'>Tipo de usuario:</label>
    <select name="user_tipo_usuario" id="tipo_usuario">
      <option>Administrador</option>
      <option>Gestor_Compras</option>
    </select>
  <div class='frm_usuario_input'>
    <input type='submit' name='accion' value='$accion' />
    <input type="button" onclick="location.href='administracion.php?editar_usuarios=yes';" name="accion" value="Cancelar"></div>
  </form> </div>
HTML;
}

function FORM_newConcierto($titulo,$accion) {
  $hoy=date("Y-m-d");
  echo <<< HTML
  <div class='frm_usuario'> <form action='panelConciertos.php?nuevo_concierto=Crear+un+nuevo+concierto' method='POST' onsubmit="return validarConcierto();">
  <h3>$titulo</h3>
  <div class='frm_usuario_input'><label for='conc_fecha'>Fecha:</label>
    <input type="date" id="fecha" name="conc_fecha"></div>
  <div class='frm_usuario_input'> <label for='conc_ciudad'>Ciudad:</label>
    <input type='text' id="ciudad" name='conc_ciudad'/></div>
  <div class='frm_usuario_input'> <label for='conc_lugar'>Lugar:</label>
    <input type='text' id="lugar" name='conc_lugar'/></div>
  <div class='frm_usuario_input'>
    <input type='submit' name='accion' value='$accion' />
    <input type="button" onclick="location.href='administracion.php?editar_conciertos=yes';" name="accion" value="Cancelar"></div>
  </form> </div>
HTML;
}

function FORM_editConcierto($titulo,$datos,$accion, $url) {
  if (isset($datos['editable']) && $datos['editable']=="false")
    $disabled='readonly="readonly"';
  else
    $disabled='';

  $id = $datos["id"];
  $hoy=date("Y-m-d");

  echo <<< HTML
  <div class='frm_usuario'> <form action='$url' method='POST' onsubmit="return validarConcierto();">
  <h3>$titulo</h3>
  <input type='hidden' name='id' value='{$datos["id"]}'/>
  <div class='frm_usuario_input'><label for='conc_fecha'>Fecha:</label>
    <input type='date' name='conc_fecha' id="fecha" value='{$datos[0]["fecha"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='conc_ciudad'>Ciudad:</label>
    <input type='text' name='conc_ciudad' id="ciudad" value='{$datos[0]["ciudad"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='conc_lugar'>Lugar:</label>
    <input type='text' name='conc_lugar' id="lugar" value='{$datos[0]["lugar"]}' $disabled/></div>
  <div class='frm_usuario_input'>
    <input type='submit' name='accion' value='$accion' />
    <input type="button" onclick="location.href='administracion.php?editar_conciertos=yes';" name="accion" value="Cancelar"></div>
  </form> </div>
HTML;
}

function FORM_aceptaPedido($titulo,$id,$accion) {
  echo <<< HTML
  <div class='frm_usuario'> <form action='panelGestor.php?aceptar_pedido=Aceptar+pedido' method='POST' onsubmit="return validarAceptacionPedido();">
  <h3>$titulo</h3>
  <input type='hidden' name='id' value='$id'/>
  <div class='frm_usuario_input'>
    <textarea name="mensaje_correo" id="mensaje" rows="20" cols="50"></textarea></div>
  <div class='frm_usuario_input'>
    <input type='submit' name='accion' value='$accion' />
    <input type="button" onclick="location.href='gestionPedidos.php?pedidos_pendientes=yes';" name="accion" value="Cancelar"></div>
  </form> </div>
HTML;
}

function FORM_deniegaPedido($titulo1,$titulo2,$id,$accion) {
  echo <<< HTML
  <div class='frm_usuario'> <form action='panelGestor.php?denegar_pedido=Denegar' method='POST' onsubmit="return validarDenegacionPedido();">
  <h3>$titulo1</h3>
  <input type='hidden' name='id' value='$id'/>
  <div class='frm_usuario_input'>
    <textarea name="mensaje_correo" id="mensaje" rows="20" cols="50"></textarea></div>
  <h3>$titulo2</h3>
  <div class='frm_usuario_input'>
    <textarea name="motivo_denied" id="motivo" rows="20" cols="50"></textarea></div>
  <div class='frm_usuario_input'>
    <input type='submit' name='accion' value='$accion' />
    <input type="button" onclick="location.href='gestionPedidos.php?pedidos_pendientes=yes';" name="accion" value="Cancelar"></div>
  </form> </div>
HTML;
}

function FORM_editDisco($titulo,$id,$accion) {
  echo <<< HTML
  <div class='frm_usuario'> <form action='panelModPrecios.php?modificar_precio=Modificar+precio' method='POST' onsubmit="return validarEditarPrecioDisco();">
  <h3>$titulo</h3>
  <input type='hidden' name='id' value='$id'/>
  <div class='frm_usuario_input'>
    <input type='text' name='disc_precio' id="precio"/></div>
  <div class='frm_usuario_input'>
    <input type='submit' name='accion' value='$accion' />
    <input type="button" onclick="location.href='gestionPedidos.php?editar_precios=yes';" name="accion" value="Cancelar"></div>
  </form> </div>
HTML;
}
?>
