<?php
function my_bcmod( $x, $y )
{
    $take = 5;
    $mod = '';

    do
    {
        $a = (int)$mod.substr( $x, 0, $take );
        $x = substr( $x, $take );
        $mod = $a % $y;
    }
    while ( strlen($x) );

    return (int)$mod;
}

function compruebaIBAN($iban){
    $letras=array("A"=>10, "B"=>11, "C"=>12, "D"=>13, "E"=>14, "F"=>15, "G"=>16,"H"=>17, "I"=>18, "J"=>19, "K"=>20, "L"=>21, "M"=>22,
      "N"=>23, "O"=>24, "P"=>25, "Q"=>26, "R"=>27, "S"=>28, "T"=>29, "U"=>30, "V"=>31, "W"=>32, "X"=>33, "Y"=>34, "Z"=>35);

    //Eliminar espacios inicio y final
    $iban=trim($iban);

    //Pasar todo a mayusculas
    $iban=strtoupper($iban);

    //Elimino espacios y guiones posibles que esten en el IBAN
    $iban=str_replace(array(" ","-"),"",$iban);

    //Compruebo que todo ocupa 24 caracteres
    if(strlen($iban)==24){
        //Cojo las dos primeras letras
        $valorLetra1 = $letras[substr($iban, 0, 1)];
        $valorLetra2 = $letras[substr($iban, 1, 1)];

        //Cojo los siguientes dos valores a las letras
        $siguienteNumeros= substr($iban, 2, 2);

        $valor = substr($iban, 4, strlen($iban)).$valorLetra1.$valorLetra2.$siguienteNumeros;

        if(my_bcmod($valor,97)==1){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

function compruebaParametros($post){
  $errores = array();
  $datos = array();
  $patron_texto = "/^[a-zA-ZáéíóúÁÉÍÓÚäëïöüÄËÏÖÜàèìòùÀÈÌÒÙ\s]+$/";
  $patron_direccionPostal = "/[a-zA-Z1-9À-ÖØ-öø-ÿ]+\.?(( |\-)[a-zA-Z1-9À-ÖØ-öø-ÿ]+\.?)*/";
  $patron_anio = "/[0-9]{4}/";
  $patron_dia = "/[0-9]{2}$/";
  $patron_mes = "/-([0-9]{2})-/";
  $patron_telefono = "/^[9|6|7][0-9]{8}$/";
  $patron_email = "/^[_a-z0-9-]+(\.[_a-z0-9-]+)*@[a-z0-9-]+(\.[a-z0-9-]+)*(\.[a-z]{2,3})$/";
  $patron_numeroCC = "/(([X-Z]{1})([-]?)(\d{7})([-]?)([A-Z]{1}))|((\d{8})([-]?)([A-Z]{1}))/";
  $patron_visa = "/^4\d{3}-?\d{4}-?\d{4}-?\d{4}$/";
  $patron_mastercard = "/^5[1-5]\d{2}-?\d{4}-?\d{4}-?\d{4}$/";
  $patron_cvc = "/^[0-9]{3}$/";

  if(!empty($post)){
    if(isset($post["nombre"],$post["apellido"],$post["direccion_postal"],$post["fecha_nacimiento"],$post["telefono"],$post["email"],$post["numero_cc"],
  $post["numero_tarjeta"],$post["anio_caducidad"],$post["codigo_cvc"]/*, $post["tematica_elegida"]*/)) {
      //Comprobación de nombre
      if(empty($post["nombre"])){
        $errores['nombre'] = 'Debe especificar el nombre';
      }else{
        if(preg_match($patron_texto, $post["nombre"]))
          $datos['nombre'] = $post["nombre"];
        else
          $errores['nombre'] = 'El nombre sólo puede contener letras y espacios.';
      }

      //Comprobación de apellido
      if(empty($post["apellido"])){
        $errores['apellido'] = 'Debe especificar el apellido';
      }else{
        if(preg_match($patron_texto, $post["apellido"]))
          $datos['apellido'] = $post["apellido"];
        else
          $errores['apellido'] = 'El apellido sólo puede contener letras y espacios.';
      }

      //Comprobación de direccion_postal
      if(empty($post["direccion_postal"])){
        $errores['direccion_postal'] = 'Debe especificar la direccion postal';
      }else{
        if(preg_match($patron_direccionPostal, $post["direccion_postal"]))
          $datos['direccion_postal'] = $post["direccion_postal"];
        else
          $errores['direccion_postal'] = 'La direccion sólo puede contener letras, espacios y numeros.';
      }

      //Comprobacion de la fecha de fecha_nacimiento
      preg_match($patron_mes, $post["fecha_nacimiento"], $mes_nacimiento);
      preg_match($patron_anio, $post["fecha_nacimiento"], $anio_nacimiento);
      preg_match($patron_dia, $post["fecha_nacimiento"], $dia_nacimiento);

      $anio_maximo = date ("Y")-18;
      $mes_maximo = date ("m");
      $dia_maximo = date ("d");

      if(empty($post["fecha_nacimiento"])){
        $errores['fecha_nacimiento'] = 'Debe especificar la fecha de nacimiento';
      }else{
        if($anio_nacimiento[0]<$anio_maximo || $anio_nacimiento[0]==$anio_maximo && $mes_nacimiento[1] >= 01 && $mes_nacimiento[1] < $mes_maximo || $anio_nacimiento[0]==$anio_maximo && $mes_nacimiento[1] == $mes_maximo && $dia_nacimiento[0]>=01 && $dia_nacimiento[0]<=$dia_maximo){
          $datos['fecha_nacimiento'] = $post["fecha_nacimiento"];
        }else
          $errores['fecha_nacimiento'] = 'Tienes que ser mayor de edad.';
      }

      //Comprobación de telefono
      if(empty($post["telefono"])){
        $errores['telefono'] = 'Debe especificar el numero de telefono';
      }else{
        if(preg_match($patron_telefono, $post["telefono"]))
          $datos['telefono'] = $post["telefono"];
        else
          $errores['telefono'] = 'El número de telefono solo puede contener numeros y ser máximo de 9 digitos.';
      }

      //Comprobación de email
      if(empty($post["email"])){
        $errores['email'] = 'Debe especificar el email';
      }else{
        $email = filter_var($post["email"], FILTER_SANITIZE_EMAIL);
        if(!filter_var($email, FILTER_VALIDATE_EMAIL) === false)
          $datos['email'] = $post["email"];
        else
          $errores['email'] = 'El email tiene que tener forma de usuario@servidor.dominio.';
      }

      //Comprobación del numero CC
      if(empty($post["numero_cc"])){
        $errores['numero_cc'] = 'Debe especificar el número de cuenta';
      }else{
      if(/*preg_match($patron_numeroCC, $post["numero_cc"])*/compruebaIBAN($post["numero_cc"]))
          $datos['numero_cc'] = $post["numero_cc"];
        else
          $errores['numero_cc'] = 'El número de cuenta introducido no es válido.';
      }

      //Guardo valores que han sido obligados a poner en el formulario es el caso de la tematica, tipo de subcripción y el modo de pago
      //$datos['tematica_elegida'] = $post["tematica_elegida"];
      $datos['tipo_subscripcion'] = $post["tipo_subscripcion"];
      $datos['modo_pago'] = $post["modo_pago"];

      if($post["modo_pago"] == "tarjeta_credito"){
        //Comprobación de tipo_tarjeta Visa o Mastercard y en funcion de esta se comprobara el numero de tarjeta de manera diferente
        $datos['tipo_tarjeta'] = $post["tipo_tarjeta"];
        if($post["tipo_tarjeta"] == "Visa"){
          if(empty($post["numero_tarjeta"])){
            $errores['numero_tarjeta'] = 'Debe especificar el numero de la tarjeta de credito.';
          }else{
            if(preg_match($patron_visa, $post["numero_tarjeta"]))
              $datos['numero_tarjeta'] = $post["numero_tarjeta"];
            else
              $errores['numero_tarjeta'] = 'El numero de su tarjeta Visa no es válida';
          }
        }else{
          if(empty($post["numero_tarjeta"])){
            $errores['numero_tarjeta'] = 'Debe especificar el numero de la tarjeta de credito.';
          }else{
            if(preg_match($patron_mastercard, $post["numero_tarjeta"]))
              $datos['numero_tarjeta'] = $post["numero_tarjeta"];
            else
              $errores['numero_tarjeta'] = 'El numero de su tarjeta Mastercard no es válido';
          }
        }

        //Comprobacion de anio_caducidad superior al año actual
        preg_match($patron_anio, $post["anio_caducidad"], $valor_anio);
        $mes_caducidad = $post["mes_caducidad"];
        $datos['mes_caducidad'] = $mes_caducidad;

        if(empty($post["anio_caducidad"])){
          $errores['anio_caducidad'] = 'Debe especificar el año de caducidad de la tarjeta de credito.';
        }else{
          if(!empty($valor_anio) && $valor_anio[0]>date("Y") || !empty($valor_anio) && $valor_anio[0]==date("Y") &&  $mes_caducidad > date("m")){
            $datos['anio_caducidad'] = $post["anio_caducidad"];
          }else{
            $errores['anio_caducidad'] = 'Datos de caducidad de tarjeta inválidos, tarjeta cumplidad.';
            $errores['mes_caducidad'] = 'Datos de caducidad de tarjeta inválidos, tarjeta cumplida.';
          }
        }

        //Comprobacion codigo_cvc
        if(empty($post["codigo_cvc"])){
          $errores['codigo_cvc'] = 'Debe especificar el código CVC de la tarjeta de credito.';
        }else{
          if(preg_match($patron_cvc, $post["codigo_cvc"])){
            $datos['codigo_cvc'] = $post["codigo_cvc"];
          }else
            $errores['codigo_cvc'] = 'El código de validación es invalido, máximo 3 cifras.';
        }
      }

      //Añado variables intereses y subscripcion a publicidad_email
      if(!empty($post["intereses"]) && !empty($post["publicidad_email"])){
        $datos['intereses'] = $post["intereses"];
        $datos['publicidad_email'] = $post["publicidad_email"];
      }else if(!empty($post["intereses"]) && empty($post["publicidad_email"])){
        $datos['intereses'] = $post["intereses"];
      }else if(empty($post["intereses"]) && !empty($post["publicidad_email"])){
        $datos['publicidad_email'] = $post["publicidad_email"];
      }
    }/*else{ /* Si no se han recibido datos del formulario
      echo "<p>Alguna variable no ha sido recibida</p>";*/
  }
  $resultados[0] = $datos;
  $resultados[1] = $errores;
  return $resultados;
}

function imprimirValores($valores){
  echo('<pre>');
  print_r($valores);
  echo('</pre>');
}
?>

<?php
function muestraFormulario($resultados){
  $datos = $resultados[0];
  $errores = $resultados[1];
  ?>
  <!DOCTYPE html>
  <html>
    <head>
      <meta charset="utf-8">
      <title>Practica 4: PHP</title>
    </head>
    <body>
      <fieldset>
        <legend>Formulario de subscripción</legend>
        <form action="./procesamiento_formulario.php" method="post">
          <fieldset>
            <legend>Información personal</legend>
            <?php
              if(array_key_exists('nombre', $errores)){
                $error = $errores['nombre'];
                echo "<p>Nombre: <input type=\"text\" name=\"nombre\"/> <h6 style=\"color:#FF0000\";>$error</h6></p>";
              }else{
                $dato = $datos['nombre'];
                echo "<p>Nombre: <input type=\"text\" name=\"nombre\" value=\"$dato\"/></p>";
              }

              if(array_key_exists('apellido', $errores)){
                $error = $errores['apellido'];
                echo "<p>Apellidos: <input type=\"text\" name=\"apellido\"/> <h6 style=\"color:#FF0000\";>$error</h6></p>";
              }else{
                $dato = $datos['apellido'];
                echo "<p>Apellidos: <input type=\"text\" name=\"apellido\" value=\"$dato\"/></p>";
              }

              if(array_key_exists('direccion_postal', $errores)){
                $error = $errores['direccion_postal'];
                echo "<p>Dirección postal: <input type=\"text\" name=\"direccion_postal\"/> <h6 style=\"color:#FF0000\";>$error</h6></p>";
              }else{
                $dato = $datos['direccion_postal'];
                echo "<p>Dirección postal: <input type=\"text\" name=\"direccion_postal\" value=\"$dato\"/></p>";
              }

              if(array_key_exists('fecha_nacimiento', $errores)){
                $error = $errores['fecha_nacimiento'];
                echo "<p>Fecha nacimiento: <input type=\"date\" name=\"fecha_nacimiento\"/><h6 style=\"color:#FF0000\";>$error</h6></p>";
              }else{
                $dato = $datos['fecha_nacimiento'];
                echo "<p>Fecha nacimiento: <input type=\"date\" name=\"fecha_nacimiento\" value=\"$dato\"/></p>";
              }

              if(array_key_exists('telefono', $errores)){
                $error = $errores['telefono'];
                echo "<p>Teléfono: <input type=\"text\" name=\"telefono\"/> <h6 style=\"color:#FF0000\";>$error</h6></p>";
              }else{
                $dato = $datos['telefono'];
                echo "<p>Teléfono: <input type=\"text\" name=\"telefono\" value=\"$dato\"/></p>";
              }

              if(array_key_exists('email', $errores)){
                $error = $errores['email'];
                echo "<p>Email: <input type=\"text\" name=\"email\"/> <h6 style=\"color:#FF0000\";>$error</h6></p>";
              }else{
                $dato = $datos['email'];
                echo "<p>Email: <input type=\"text\" name=\"email\" value=\"$dato\"/></p>";
              }

              if(array_key_exists('numero_cc', $errores)){
                $error = $errores['numero_cc'];
                echo "<p>Número de CC: <input type=\"text\" name=\"numero_cc\"/> <h6 style=\"color:#FF0000\";>$error</h6></p>";
              }else{
                $dato = $datos['numero_cc'];
                echo "<p>Número de CC: <input type=\"text\" name=\"numero_cc\" value=\"$dato\"/></p>";
              }
            ?>
          </fieldset>

          <fieldset>
            <legend>Información sobre la subscripción</legend>
            <p>REVISTA ELEGIDA: <?php /*echo $datos['tematica_elegida'];*/?></p>

            <?php
              $dato = $datos['tipo_subscripcion'];
              if(strcmp($dato, 'Anual') === 0){
                echo "<p>Tipo de subscripción:
                  <select name=\"tipo_subscripcion\">
                    <option selected>Anual</option>
                    <option>Bianual</option>
                  </select>
                </p>";
              }else{
                echo "<p>Tipo de subscripción:
                  <select name=\"tipo_subscripcion\">
                    <option>Anual</option>
                    <option selected>Bianual</option>
                  </select>
                </p>";
              }
            ?>
            <p>Selecciona método de pago:
              <br>
                <?php
                  $dato = $datos['modo_pago'];
                  if($dato === 'tarjeta_credito'){
                    echo "<input type=\"radio\" name=\"modo_pago\" value=\"tarjeta_credito\" checked/>Tarjeta de crédito";
                    echo "<input type=\"radio\" name=\"modo_pago\" value=\"contrareembolso\"/>Contrareembolso";
                  }else{
                    echo "<input type=\"radio\" name=\"modo_pago\" value=\"tarjeta_credito\"/>Tarjeta de crédito";
                    echo "<input type=\"radio\" name=\"modo_pago\" value=\"contrareembolso\" checked/>Contrareembolso";
                  }
                ?>
              </br>
                <dl>
                  <dt>Información tarjeta de crédito (rellenar si ha elegido pago por tarjeta):</dt>
                    <dd>Tipo tarjeta:
                      <?php
                        if(array_key_exists('modo_pago', $datos) && $datos['modo_pago'] === 'tarjeta_credito'){
                          $dato = $datos['tipo_tarjeta'];
                          if($dato === 'Visa'){
                            echo "<select name=\"tipo_tarjeta\">
                                    <option selected>Visa</option>
                                    <option>Mastercard</option>
                                  </select>";
                          }else{
                            echo "<select name=\"tipo_tarjeta\">
                                    <option>Visa</option>
                                    <option selected>Mastercard</option>
                                  </select>";
                          }
                        }else{
                          echo "<select name=\"tipo_tarjeta\">
                                  <option selected>Visa</option>
                                  <option>Mastercard</option>
                                </select>";
                        }
                      ?>
                    </dd>
                    <dd>
                      <?php
                        if(array_key_exists('modo_pago', $datos) && $datos['modo_pago'] === 'tarjeta_credito'){
                          if(array_key_exists('numero_tarjeta', $errores)){
                            $error = $errores['numero_tarjeta'];
                            echo "<p>Número de tarjeta: <input type=\"text\" name=\"numero_tarjeta\"/> <h6 style=\"color:#FF0000\";>$error</h6></p>";
                          }else{
                            $dato = $datos['numero_tarjeta'];
                            echo "<p>Número de tarjeta: <input type=\"text\" name=\"numero_tarjeta\" value=\"$dato\"/></p>";
                          }
                        }else{
                          echo "<p>Número de tarjeta: <input type=\"text\" name=\"numero_tarjeta\"/></p>";
                        }
                      ?>
                    </dd>
                    <dd>Mes de caducidad:
                      <select name="mes_caducidad">
                        <option selected>01</option>
                        <option>02</option>
                        <option>03</option>
                        <option>04</option>
                        <option>05</option>
                        <option>06</option>
                        <option>07</option>
                        <option>08</option>
                        <option>09</option>
                        <option>10</option>
                        <option>11</option>
                        <option>12</option>
                      </select>
                    </dd>
                    <dd>
                      <?php
                        if(array_key_exists('modo_pago', $datos) && $datos['modo_pago'] === 'tarjeta_credito'){
                          if(array_key_exists('anio_caducidad', $errores)){
                            $error = $errores['anio_caducidad'];
                            echo "<p>Año de caducidad: <input type=\"text\" name=\"anio_caducidad\"/> <h6 style=\"color:#FF0000\";>$error</h6></p>";
                          }else{
                            $dato = $datos['anio_caducidad'];
                            echo "<p>Año de caducidad: <input type=\"text\" name=\"anio_caducidad\" value=\"$dato\"/></p>";
                          }
                        }else{
                          echo "<p>Año de caducidad: <input type=\"text\" name=\"anio_caducidad\"/></p>";
                        }
                      ?>
                    </dd>
                    <dd>
                      <?php
                        if(array_key_exists('modo_pago', $datos) && $datos['modo_pago'] === 'tarjeta_credito'){
                          if(array_key_exists('codigo_cvc', $errores)){
                            $error = $errores['codigo_cvc'];
                            echo "<p>Código CVC: <input type=\"text\" name=\"codigo_cvc\"/> <h6 style=\"color:#FF0000\";>$error</h6></p>";
                          }else{
                            $dato = $datos['codigo_cvc'];
                            echo "<p>Código CVC: <input type=\"text\" name=\"codigo_cvc\" value=\"$dato\"/></p>";
                          }
                        }else{
                          echo "<p>Código CVC: <input type=\"text\" name=\"codigo_cvc\"/></p>";
                        }
                      ?>
                    </dd>
                </dl>
            </p>
          </fieldset>

          <fieldset>
            <legend>Otra información</legend>
            <p>Temas de interés:
              <br>
                <?php
                  if(array_key_exists('intereses', $datos) && in_array("divulgacion", $datos['intereses'])){
                    echo "<input type=\"checkbox\" name=\"intereses[]\" value=\"divulgacion\" checked/>Divulgación";
                  }else{
                    echo "<input type=\"checkbox\" name=\"intereses[]\" value=\"divulgacion\"/>Divulgación";
                  }

                  if(array_key_exists('intereses', $datos) && in_array("motor", $datos['intereses'])){
                    echo "<input type=\"checkbox\" name=\"intereses[]\" value=\"motor\" checked/>Motor";
                  }else{
                    echo "<input type=\"checkbox\" name=\"intereses[]\" value=\"motor\"/>Motor";
                  }

                  if(array_key_exists('intereses', $datos) && in_array("viajes", $datos['intereses'])){
                    echo "<input type=\"checkbox\" name=\"intereses[]\" value=\"viajes\" checked/>Viajes";
                  }else{
                    echo "<input type=\"checkbox\" name=\"intereses[]\" value=\"viajes\"/>Viajes";
                  }
                ?>
              </br>
            </p>
            <p>Subscripción a newsletter:
              <?php
                if(array_key_exists('publicidad_email', $datos)){
                  echo "<input type=\"checkbox\" name=\"publicidad_email\" value=\"si\" checked/>Avisame de ofertas y nuevas revistas en mi correo";
                }else{
                  echo "<input type=\"checkbox\" name=\"publicidad_email\" value=\"si\"/>Avisame de ofertas y nuevas revistas en mi correo";
                }
              ?>
            </p>
          </fieldset>

          <br>
            <input type="submit" value="Enviar datos"/>
            <input type="reset" value="Limpiar formulario"/>
          </br>
        </form>
      </fieldset>
    </body>
  </html>
  <?php
}
?>

<?php
  $resultados = compruebaParametros($_POST);
  if (count($resultados[1])==0) {
    echo "<h1>Formulario validado: </h1>";
    imprimirValores($resultados[0]);
  }else{
    muestraFormulario($resultados);
  }
?>
