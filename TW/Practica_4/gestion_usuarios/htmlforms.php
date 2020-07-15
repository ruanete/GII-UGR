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

function FORM_editUsuario($titulo,$datos,$accion) {
  if (isset($datos['editable']) && $datos['editable']=="false")
    $disabled='readonly="readonly"';
  else
    $disabled='';

  echo <<< HTML
  <div class='frm_usuario'> <form action='$_SERVER[PHP_SELF]' method='POST'>
  <h3>$titulo</h3>
  <input type='hidden' name='id' value='{$datos["id"]}'/>
  <div class='frm_usuario_input'><label for='user_usuario'>Usuario:</label>
    <input type='text' name='user_usuario' value='{$datos[0]["usuario"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_nombre'>Nombre:</label>
    <input type='text' name='user_nombre' value='{$datos[0]["nombre"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_apellidos'>Apellidos:</label>
    <input type='text' name='user_apellidos' value='{$datos[0]["apellidos"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_email'>Email:</label>
    <input type='text' name='user_email' value='{$datos[0]["email"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_contraseña'>Contraseña:</label>
    <input type='text' name='user_contraseña' value='{$datos[0]["password"]}' $disabled/></div>
  <div class='frm_usuario_input'> <label for='user_tipo_usuario'>Tipo de usuario:</label>
    <input type='text' name='user_tipo_usuario' value='{$datos[0]["tipo_usuario"]}' $disabled/></div>
  <div class='frm_usuario_input'>
    <input type='submit' name='accion' value='$accion' />
    <input type='submit' name='accion' value='Cancelar' /></div>
  </form> </div>
HTML;
}

function FORM_newUsuario($titulo,$accion) {
  echo <<< HTML
  <div class='frm_usuario'> <form action='$_SERVER[PHP_SELF]' method='POST'>
  <h3>$titulo</h3>
  <div class='frm_usuario_input'><label for='user_usuario'>Usuario:</label>
    <input type='text' name='user_usuario'/></div>
  <div class='frm_usuario_input'> <label for='user_nombre'>Nombre:</label>
    <input type='text' name='user_nombre'/></div>
  <div class='frm_usuario_input'> <label for='user_apellidos'>Apellidos:</label>
    <input type='text' name='user_apellidos'/></div>
  <div class='frm_usuario_input'> <label for='user_email'>Email:</label>
    <input type='text' name='user_email'/></div>
  <div class='frm_usuario_input'> <label for='user_contraseña'>Contraseña:</label>
    <input type='password' name='user_contraseña'/></div>
  <div class='frm_usuario_input'> <label for='user_tipo_usuario'>Tipo de usuario:</label>
    <input type='text' name='user_tipo_usuario'/></div>
  <div class='frm_usuario_input'>
    <input type='submit' name='accion' value='$accion' />
    <input type='submit' name='accion' value='Cancelar' /></div>
  </form> </div>
HTML;
}

?>
