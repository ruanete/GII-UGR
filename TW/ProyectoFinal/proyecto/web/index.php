<?php
  require_once('base_web.php');
  require_once('bd.php');
  cabecera("principal");
?>

<div class="seccion_web">
  <div class="columnas">
    <div class="columna">
      <h3>¿Quien es C.Tangana?</h3>
      <p>Antón Álvarez Alfaro, más conocido como C. Tangana (también como Pucho o como Crema hasta 2011 y como Caballo Ganador en 2017) es un músico nacido en 1990 en Madrid.​ Es miembro del grupo Agorazein junto con Sticky M.A. (antes conocido como Manto), Jerv.Agz., Fabianni e I-Ace. Comenzó su carrera musical en 2006, bajo el pseudónimo de Crema, con una maqueta llamada Elescrema.</p>

      <h3>Algunos exitos</h3>
      <ul>
        <li>C. Tangana - Mala Mujer (2017)</li>
        <li>C. Tangana - Tiempo (2017)</li>
        <li>C. Tangana - No te pegas (2018)</li>
        <li>C. Tangana - Still Rapping (2018)</li>
      </ul>
<?php
echo <<<HTML
      <h3>Articulos en venta destacados</h3>
      <div id="contenedor_principal">

HTML;

  $db = DB_conexion();
  $discos = DB_getDiscoConCaratula($db);
  foreach ($discos as $val) {
    $disco_string = $val->htmlView();

echo <<< HTML
        <div class="producto">
          {$disco_string}
        </div>

HTML;
  }

echo <<<HTML
      </div>
HTML;
  DB_desconexion($db);
?>
    </div>
    <div class="columna">
      <h3>Próxima gira</h3>
      <img src="./img/gira_ctangana.jpeg" alt="Cartel gira C.Tangana" width="300"/>
    </div>
    <div class="columna">
      <?php
        $bd = DB_conexion();
        VIEW_TablaConciertos($bd);
      ?>
    </div>
  </div>
</div>

<?php pieDePagina()?>
