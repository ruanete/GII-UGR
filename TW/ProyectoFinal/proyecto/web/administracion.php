<?php
require_once('base_web.php');
session_start();
if(isset($_SESSION["sesion_admin"])){
  cabecera_NOMenu("administracion");
  sidenav();

  if(isset($_GET["editar_biografia"])){
    echo "<div class=\"main\">";
      require 'panelBiografia.php';
    echo "</div>";
  }else if(isset($_GET["editar_discografia"])){
    echo "<div class=\"main\">";
      require 'panelDiscografia.php';
    echo "</div>";
  }else if(isset($_GET["editar_conciertos"])){
    echo "<div class=\"main\">";
      require 'panelConciertos.php';
    echo "</div>";
  }else if(isset($_GET["editar_usuarios"])){
    echo "<div class=\"main\">";
      require 'panelUsuarios.php';
    echo "</div>";
  }else if(isset($_GET["log_eventos"])){
    echo "<div class=\"main\">";
      require 'panelLog.php';
    echo "</div>";
  }else if(isset($_GET["backup"])){
    echo "<div class=\"main\">";
      require 'backup.php';
    echo "</div>";
  }else{
    header('Location: ./administracion.php?editar_biografia=yes');
  }
}else{
  header('Location: ./identificacion.php');
}
pieDePagina();
?>
