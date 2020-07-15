<?php
  require_once('base_web.php');
  require_once('bd.php');
  cabecera("discografia");

  echo <<< HTML
  <div class="seccion_web">
    <div class="columnas">
      <div class="columna">
        <h3>Discos</h3>
        <div id="contenedor_principal">

HTML;

  $db = DB_conexion();
  $discos = DB_getDiscoConCaratula($db);
  foreach ($discos as $val) {
    $disco_string = $val->htmlView();
    $id = $val->id;
    $precio = $val->precio;
echo <<< HTML
        <div class="producto">
          {$disco_string}
          <div class="boton_compra">
            <a class="boton_personalizado" href="./tienda.php?id={$id}&precio={$precio}">Comprar</a>
          </div>
        </div>

HTML;
  }

echo <<<HTML
      </div>
    </div>
    <div class="columna">
      <h3>Discos</h3>
      <ul>

HTML;

  $discos = DB_getDiscoNoSencillos($db);
  foreach ($discos as $val) {
      $titulo = $val->titulo;
      $anio = $val->anio;
      echo("      <li>{$titulo} ({$anio})</li>" . PHP_EOL);
  }

echo <<< HTML
      </ul>
      <h3>Sencillos</h3>
      <ul>

HTML;

  $sencillos = DB_getDiscoSencillos($db);
  foreach ($sencillos as $val) {
      $titulo = $val->titulo;
      $anio = $val->anio;
      echo("      <li>{$titulo} ({$anio})</li>" . PHP_EOL);
  }

echo <<< HTML
      </ul>
    </div>
  </div>

HTML;

  DB_desconexion($db);
  pieDePagina();
?>
