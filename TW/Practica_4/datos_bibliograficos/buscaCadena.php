<?php
  function peticion_get($web){
    $conexion = curl_init();
    curl_setopt($conexion, CURLOPT_URL,$web);
    curl_setopt($conexion, CURLOPT_HTTPGET, TRUE);
    curl_setopt($conexion, CURLOPT_HTTPHEADER,array('Content-Type: application/json'));
    curl_setopt($conexion, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($conexion,CURLOPT_USERAGENT,'Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.8.1.13) Gecko/20080311 Firefox/2.0.0.13');
    $respuesta=curl_exec($conexion);

    curl_close($conexion);


    if ( preg_match_all('#<span class="title".*><a.*>((\n|.)*?)<\/a>#', $respuesta , $titulos) ){
      if(preg_match_all('#<a id="authorDisplayLinkComponent.*>((\n|.)*?)<\/a>#', $respuesta , $autores)){
        for ($i = 0; $i < count($titulos[1]); $i++) {
          echo "<p><b>$i.";
          $t = $titulos[1][$i];
          echo "$t </b>";
          if($i<count($autores[1])){
            $a = $autores[1][$i];
            echo "<b><i>$a</i><b/>";
          }
          echo "</p>";
        }
      }
    }
  }

  if (isset($_GET["cadena"])) {
    $cadena = $_GET["cadena"];
    echo "<p>La cadena que quieres buscar es: $cadena</p>";
    echo "<p>¡¡ATENCION!! Si algun libro no tiene autor, puede ser que los autores no se correspondan con su libro.</p>";
  }

  $cadenaBusqueda = str_replace(" ", "+", $cadena);
  //echo "<p>Cadena cambiada: $cadenaBusqueda</p>";

  $web = "http://bencore.ugr.es/iii/encore/search?formids=target&lang=spi&suite=def&reservedids=lang%2Csuite&submitmode=&submitname=&target=$cadenaBusqueda&submit.x=13&submit.y=9";
  //echo "<p>Pagina web ha visitar: $web</p>";

  peticion_get($web);
?>
