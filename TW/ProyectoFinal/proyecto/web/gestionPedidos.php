<?php
require_once('base_web.php');
session_start();
if(isset($_SESSION["sesion_compras"])){
  cabecera_NOMenu("administracion");?>
  <div class="sidenav">
    <a href="?pedidos_pendientes=yes">Pedidos pendientes</a>
    <a href="?historico_pedidos=yes">Historico pedidos</a>
    <a href="?editar_precios=yes">Editar precios</a>
    <a href="./index.php" id="volver">Volver a la web</a>
    <a href="./cerrar_sesion.php" id="cerrar">Cerrar sesión</a>
  </div>

<?php
  if(isset($_GET["pedidos_pendientes"])){
    echo "<div class=\"main\">";
      require 'panelGestor.php';
    echo "</div>";
  }else if(isset($_GET["historico_pedidos"])){
    echo "<div class=\"main\">";
      require 'panelHistoricoPedidos.php';
    echo "</div>";
  }else if(isset($_GET["editar_precios"])){
    echo "<div class=\"main\">";
      require 'panelModPrecios.php';
    echo "</div>";
  }else{
    header('Location: ./gestionPedidos.php?pedidos_pendientes=yes');
  }
}else{
  header('Location: ./identificacion.php');
}
pieDePagina();
?>
