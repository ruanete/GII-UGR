<?php
  require_once('base_web.php');
  require_once('bd.php');
  cabecera("principal");

echo "<div class=\"seccion_web\">
  <div class=\"columnas\">";
    if(!isset($_POST["accion"])){
      echo "<form id=\"buscador\" name=\"buscador\" method=\"post\" action=\"busqueda.php\">
        <input id=\"buscar\" name=\"texto_busqueda\" type=\"search\" placeholder=\"Buscar aquí...\" autofocus >
        <select name=\"tipo_busqueda\" id=\"tipo_busqueda\">
          <option>Discografía</option>
          <option>Conciertos</option>
        </select>
        <p>Fecha inicio: </p>
        <input id=\"fecha_inicio\" name=\"fecha_inicio\" type=\"date\">
        <p>Fecha final: </p>
        <input id=\"fecha_final\" name=\"fecha_final\" type=\"date\">
        <p>
        Selecciona lugares si vas a realizar la busqueda de conciertos:
        </p>
        ";
        $bd = DB_conexion();
        VIEW_checkboxLugares($bd);
        DB_desconexion($bd);
        echo "
        <input type=\"submit\" name=\"accion\" class=\"boton peque aceptar\" value=\"Buscar\">
      </form>";
    }else if(isset($_POST["texto_busqueda"],$_POST["tipo_busqueda"],$_POST["accion"],$_POST["fecha_inicio"],$_POST["fecha_final"])){
      if($_POST["tipo_busqueda"] === "Discografía"){
        //echo "<h2>Resultados de busqueda: </h2>";
        $bd = DB_conexion();
        if($_POST["texto_busqueda"]!="" && $_POST["fecha_inicio"]=="" && $_POST["fecha_final"]=="")
          busquedaTituloDisco($bd, $_POST["texto_busqueda"]);
        else if($_POST["fecha_inicio"]!="" && $_POST["fecha_final"]!="" && $_POST["texto_busqueda"]=="")
          busquedaDiscosFecha($bd, $_POST["fecha_inicio"], $_POST["fecha_final"]);
        else if($_POST["fecha_inicio"]!="" && $_POST["fecha_final"]!="" && $_POST["texto_busqueda"]!="")
          busquedaDiscoPalabraFecha($bd, $_POST["texto_busqueda"], $_POST["fecha_inicio"], $_POST["fecha_final"]);
        else
          echo "<h2>Ha ocurrido un error, busqueda sin datos. </h2>";
        DB_desconexion($bd);
      }else if($_POST["tipo_busqueda"] === "Conciertos"){
        $bd = DB_conexion();
        if(!isset($_POST["lugares"]) && $_POST["fecha_inicio"]!="" && $_POST["fecha_final"]!="")
          busquedaConciertoFecha($bd, $_POST["fecha_inicio"], $_POST["fecha_final"]);
        else if(isset($_POST["lugares"]) && $_POST["fecha_inicio"]=="" && $_POST["fecha_final"]=="")
          busquedaConciertoLugar($bd, $_POST["lugares"]);
        else if(isset($_POST["lugares"]) && $_POST["fecha_inicio"]!="" && $_POST["fecha_final"]!="")
          busquedaConciertoLugarFecha($bd, $_POST["lugares"], $_POST["fecha_inicio"], $_POST["fecha_final"]);
        else
          echo "<h2>Ha ocurrido un error, busqueda sin datos. </h2>";
        DB_desconexion($bd);
      }else{
        header('Location: index.php');
      }
    }
  echo "</div>
</div>";

pieDePagina();
?>
