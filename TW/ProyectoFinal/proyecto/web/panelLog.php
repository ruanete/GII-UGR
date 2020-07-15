<?php
	require_once('base_web.php');
	require_once('bd.php');
	require('checkAdmin.php');

  $bd = DB_conexion();
  //DB_addLog($bd, "ESTAMOS PROBANDO QUE FUNCIONE EL LOG CORRECTAMENTE");
  VIEW_TablalogEventos($bd)

?>
