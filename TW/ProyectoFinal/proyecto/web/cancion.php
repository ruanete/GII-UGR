<?php
class Cancion{
  public $titulo;
  public $duracion;
  public $id_disco;
  public $id;

  public function  __construct($titulo, $duracion, $id, $id_disco) {
    $this->titulo = $titulo;
    $this->duracion = $duracion;
    $this->id = $id;
    $this->id_disco = $id_disco;
  }

  public function htmlView(){
    $var = '<div class="imagen">';
    $var .= "<a href=\"$this->web\"><img src=\"$this->img\" alt=\"$this->titulo\"/></a>";
    $var .= '</div>' . PHP_EOL;

    return $var;
  }

  public function htmlFormView($formulario){
    $var ='<div>' . PHP_EOL;
    $var .='<form action="'.$formulario.'" style="display:inline-block" method="POST">' . PHP_EOL;
    $var .= "\tTitulo: <input name=\"titulo\" type=\"text\" value=\"$this->titulo\">". PHP_EOL;
    $var .= "\tDuracion (segundos): <input name=\"duracion\" type=\"number\" value=\"$this->duracion\">". PHP_EOL;
    $var .= "\tID del disco<input name=\"id_disco\" type=\"number\" value=\"$this->id_disco\">". PHP_EOL;

    if($this->id != -1)
      $var .= "\t<input name=\"id\" type=\"hidden\" value=\"$this->id\">". PHP_EOL;

    $var .= "\t<input type=\"submit\" value=\"Enviar Cambios\">" . PHP_EOL;
    $var .= "</form>" . PHP_EOL;

    if($this->id != -1){
      $var .= '<form action="'.$formulario.'" style="display:inline-block" method="GET">' . PHP_EOL;
      $var .= "\t<input name=\"id\" type=\"hidden\" value=\"$this->id\">". PHP_EOL;
      $var .= "\t<input type=\"submit\" name=\"borrar_cancion\" value=\"Borrar\">" . PHP_EOL;
      $var .= "</form>" . PHP_EOL;
    }
    $var .='</div>' . PHP_EOL;

    return $var;
  }

  public function htmlFormViewIDnoEditable($formulario){
    $var ='<div>' . PHP_EOL;
    $var .='<form action="'.$formulario.'" style="display:inline-block" method="POST">' . PHP_EOL;
    $var .= "\tTitulo: <input name=\"titulo\" type=\"text\" value=\"$this->titulo\">". PHP_EOL;
    $var .= "\tDuracion (segundos): <input name=\"duracion\" type=\"number\" value=\"$this->duracion\">". PHP_EOL;
    $var .= "\t<input name=\"id_disco\" type=\"hidden\" value=\"$this->id_disco\">". PHP_EOL;
    if($this->id != -1)
      $var .= "\t<input name=\"id\" type=\"hidden\" value=\"$this->id\">". PHP_EOL;
    $var .= "\t<input type=\"submit\" value=\"Enviar Cambios\">" . PHP_EOL;
    $var .= "</form>" . PHP_EOL;
    if($this->id != -1){
      $var .= '<form action="'.$formulario.'" style="display:inline-block" method="GET">' . PHP_EOL;
      $var .= "\t<input name=\"id\" type=\"hidden\" value=\"$this->id\">". PHP_EOL;
      $var .= "\t<input type=\"submit\" name=\"borrar_cancion\" value=\"Borrar\">" . PHP_EOL;
      $var .= "</form>" . PHP_EOL;
    }
    $var .='</div>' . PHP_EOL;
    return $var;
  }
}
?>
