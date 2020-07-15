<?php
  require_once('base_web.php');
  require_once('bd.php');
  require_once('seccionbio.php');
  cabecera("biografia");

  $db = DB_conexion();
  $secciones = DB_getSecciones($db);
  DB_desconexion($db);

  echo PHP_EOL;
  echo "\t<div class=\"seccion_web\">" . PHP_EOL;
  echo "\t\t<article>"  . PHP_EOL;
  foreach ($secciones as  $val) {
    echo $val->htmlSectionView() . PHP_EOL;
  }
  echo "\t\t</article>"  . PHP_EOL;
  echo "\t</div>" . PHP_EOL;
  pieDePagina()
?>