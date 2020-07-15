
<?php
//<script type="text/javascript" src="./js/ValidacionFormularios.js"></script>

class SeccionBio{
  public $titulo;
  public $img;
  public $cuerpo;
  public $id;

  public function  __construct($titulo, $img, $cuerpo, $id) {
    $this->titulo = $titulo;
    $this->img = $img;
    $this->cuerpo = $cuerpo;
    $this->id = $id;
  }

  public function htmlSectionView(){
    $var = "<section>" . PHP_EOL;
    $var .= "\t<h3>$this->titulo</h3>". PHP_EOL;
    if(strlen($this->img) > 0)
      $var .= "\t".'<img src="'.$this->img.'" width="300"/>' . PHP_EOL;
    foreach(preg_split("/((\r?\n)|(\r\n?))/", $this->cuerpo) as $line){
        if(strlen(str_replace(array("\n", "\r\n", "\r"), '', $line)) > 0)
          $var .= "\t<p>" .$line . "</p>" . PHP_EOL;
    }
    $var .= "</section>" . PHP_EOL;

    return $var;
  }

  public function htmlFormView($formulario){
    $var ='<form action="'.$formulario.'" method="POST" onsubmit="return validarSeccion();">' . PHP_EOL;
    $var .= "\tTitulo: <input name=\"titulo\" id=\"titulo\" type=\"text\" value=\"$this->titulo\"><br>". PHP_EOL;
    $var .= "\tURL Imagen: <input name=\"link\" id=\"link\" type=\"text\" value=\"$this->img\"><br>". PHP_EOL;
    $var .= "\t<textarea name=\"cuerpo\" id=\"cuerpo\" rows=\"40\" cols=\"60\">$this->cuerpo</textarea><br>" . PHP_EOL;
    if($this->id != -1)
      $var .= "\t<input name=\"id\" type=\"hidden\" value=\"$this->id\">". PHP_EOL;
    $var .= "\t<input type=\"submit\" >" . PHP_EOL;
    $var .= "</form>" . PHP_EOL;

    if($this->id != -1){
      $var .='<form action="'.$formulario.'" method="GET">' . PHP_EOL;
      $var .= "\t<input name=\"id\" type=\"hidden\" value=\"$this->id\">". PHP_EOL;
      $var .= "\t<input type=\"submit\" name=\"borrar_seccion\" value=\"Borrar\">" . PHP_EOL;
      $var .= "</form>" . PHP_EOL;
    }
    return $var;
  }
}
?>
