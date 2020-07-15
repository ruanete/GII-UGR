<?php
require_once('cancion.php');
require_once('bd.php');

class Disco{
  public $titulo;
  public $img;
  public $web;
  public $sencillo;
  public $anio;
  public $canciones;
  public $id;

  public function  __construct($titulo, $img, $web, $sencillo, $anio, $precio, $id) {
    $this->titulo = $titulo;
    $this->img = $img;
    $this->web = $web;
    $this->sencillo = $sencillo;
    $this->anio = $anio;
    $this->precio = $precio;
    $this->id = $id;
  }


  public function htmlView(){
    $var = '<div class="imagen">';
    $var .= "<a href=\"$this->web\"><img src=\"$this->img\" alt=\"$this->titulo\"/></a>";
    $var .= '</div>' . PHP_EOL;

    return $var;
  }

  public function htmlFormView($formulario){
    $var ='<form action="'.implode($formulario).'" method="POST">' . PHP_EOL;
    $var .= "\tTitulo: <input name=\"titulo\" type=\"text\" value=\"$this->titulo\"><br>". PHP_EOL;
    $var .= "\tURL Imagen: <input name=\"img\" type=\"text\" value=\"$this->img\"><br>". PHP_EOL;
    if(!empty($this->img)){
      $var .= "\t<img src=\"$this->img\" alt=\"$this->titulo\" style=\"width: 300px\"/><br>" . PHP_EOL;
    }
    $var .= "\tURL html: <input name=\"web\" type=\"text\" value=\"$this->web\"><br>". PHP_EOL;
    if($this->sencillo == 1)
      $checked = "checked";
    else
      $checked = "";
    $var .= "\tAño: <input name=\"anio\" value=\"$this->anio\" type=\"number\"><br>". PHP_EOL;
    $var .= "\tPrecio: <input name=\"precio\" value=\"$this->precio\" type=\"number\"><br>". PHP_EOL;
    $var .= "\tSencillo: <input name=\"sencillo\" type=\"checkbox\" value=\"sencillo\" $checked><br>". PHP_EOL;
    if($this->id != -1)
      $var .= "\t<input name=\"id\" type=\"hidden\" value=\"$this->id\">". PHP_EOL;
    $var .= "\t<input type=\"submit\" >" . PHP_EOL;
    $var .= "</form>" . PHP_EOL;

    if($this->id != -1){
      $var .= '<form action="'.implode($formulario).'" method="GET">' . PHP_EOL;
      $var .= "\t<input name=\"id\" type=\"hidden\" value=\"$this->id\">". PHP_EOL;
      $var .= "\t<input type=\"submit\" name=\"borrar_seccion\" value=\"Borrar disco\">" . PHP_EOL;
      $var .= "</form>" . PHP_EOL;
    }
    $db = DB_conexion();
    $canciones = DB_getCancionesDisco($db,$this);
    DB_desconexion($db);
    $var .= "<h4> Canciones </h4><hr>". PHP_EOL;
    foreach ($canciones as $cancion) {
      $var .= $cancion->htmlFormViewIDnoEditable($formulario[0]."?editar_cancion=true");
      echo "<hr>" . PHP_EOL;
    }
    $id = urlencode(filter_var($this->id, FILTER_SANITIZE_NUMBER_INT));
    $var .= "<form action='$formulario[0]' method='GET'>". PHP_EOL;
    $var .= "\t<input type=\"hidden\" name=\"id_disco\" value=\"$id\">" . PHP_EOL;
    $var .= "\t<input type=\"hidden\" name=\"nueva_cancion\" value=\"true\">" . PHP_EOL;
    $var .= "  <input type='submit' value='Añadir nueva cancion'/>" . PHP_EOL;
    $var .= "</form>" . PHP_EOL;
    return $var;
  }
  public function htmlFormViewNoSongs($formulario){
    $var ='<form action="'.implode($formulario).'" method="POST">' . PHP_EOL;
    $var .= "\tTitulo: <input name=\"titulo\" type=\"text\" value=\"$this->titulo\"><br>". PHP_EOL;
    $var .= "\tURL Imagen: <input name=\"img\" type=\"text\" value=\"$this->img\"><br>". PHP_EOL;
    if(!empty($this->img)){
      $var .= "\t<img src=\"$this->img\" alt=\"$this->titulo\" style=\"width: 300px\"/><br>" . PHP_EOL;
    }
    $var .= "\tURL html: <input name=\"web\" type=\"text\" value=\"$this->web\"><br>". PHP_EOL;
    if($this->sencillo == 1)
      $checked = "checked";
    else
      $checked = "";
    $var .= "\tAño: <input name=\"anio\" value=\"$this->anio\" type=\"number\"><br>". PHP_EOL;
    $var .= "\tPrecio: <input name=\"precio\" value=\"$this->precio\" type=\"number\"><br>". PHP_EOL;
    $var .= "\tSencillo: <input name=\"sencillo\" type=\"checkbox\" value=\"sencillo\" $checked><br>". PHP_EOL;
    if($this->id != -1)
      $var .= "\t<input name=\"id\" type=\"hidden\" value=\"$this->id\">". PHP_EOL;
    $var .= "\t<input type=\"submit\" >" . PHP_EOL;
    $var .= "</form>" . PHP_EOL;

    if($this->id != -1){
      $var .= '<form action="'.implode($formulario).'" method="GET">' . PHP_EOL;
      $var .= "\t<input name=\"id\" type=\"hidden\" value=\"$this->id\">". PHP_EOL;
      $var .= "\t<input type=\"submit\" name=\"borrar_seccion\" value=\"Borrar disco\">" . PHP_EOL;
      $var .= "</form>" . PHP_EOL;
    }
    return $var;
  }
}
?>
