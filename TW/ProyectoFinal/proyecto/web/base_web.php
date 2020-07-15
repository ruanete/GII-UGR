<?php
  function cabecera($archivo_css){
    if(!isset($_SESSION))
      session_start();

    echo "<!DOCTYPE html>
    <html>
      <head>
        <meta charset=\"utf-8\">
        <title>C.Tangana</title>
        <link rel=\"shortcut icon\" type=\"image/png\" href=\"./img/favicon.ico\"/>
      </head>
      <body>
      <div class=\"sombreado\">
        <div class=\"menu_usuario\">";
        if(isset($_SESSION["sesion_admin"])){
          $admin = $_SESSION["sesion_admin"];
          echo "<a href=\"./identificacion.php\"> $admin</a>";
        }else if(isset($_SESSION["sesion_compras"])){
          $gestor_compras = $_SESSION["sesion_compras"];
          echo "<a href=\"./identificacion.php\"> $gestor_compras</a>";
        }else
          echo "<a href=\"./identificacion.php\"> Iniciar sesión</a>";
        echo "
        </div>
        <header>
          <h1>C. Tangana</h1>
          <!--<div align=\"center\"><img src=\"./img/logo_ctangana.jpg\" alt=\"Logo C.Tangana\" width=\"300\"/></div>-->
          <link href=\"https://fonts.googleapis.com/css?family=Inconsolata\" rel=\"stylesheet\">
          <link href=\"https://fonts.googleapis.com/css?family=Source+Sans+Pro\" rel=\"stylesheet\">
          <link rel=\"stylesheet\" href=\"./css/estilo_base.css\">
          <link rel=\"stylesheet\" href=\"./css/$archivo_css.css\">
        </header>

        <nav class=\"estilo_base\">
          <p><a href=\"./index.php\"> Inicio</a></p>
          <p><a href=\"./biografia.php\"> Biografía</a></p>
          <p><a href=\"./discografia.php\"> Discografía</a></p>
          <p><a href=\"./busqueda.php\"> Busqueda</a></p>
        </nav>
      </div>";
  }

  function sidenav(){    
    echo "<div class=\"sidenav\">
    <a href=\"administracion.php?editar_biografia=yes\">Editar biografía</a>
    <a href=\"administracion.php?editar_discografia=yes\">Editar discografía</a>
    <a href=\"administracion.php?editar_conciertos=yes\">Editar conciertos</a>
    <a href=\"administracion.php?editar_usuarios=yes\">Editar usuarios</a>
    <a href=\"administracion.php?log_eventos=yes\">Log de eventos</a>
    <a href=\"administracion.php?backup=yes\">Copia de Seguridad</a>
    <a href=\"./index.php\" id=\"volver\">Volver a la web</a>
    <a href=\"./cerrar_sesion.php\" id=\"cerrar\">Cerrar sesión</a>
    </div>";
  }
  function cabecera_NOMenu($estilo){
    if(!isset($_SESSION))
      session_start();

    echo "<!DOCTYPE html>
    <html>
      <head>
        <meta charset=\"utf-8\">
        <title>C.Tangana</title>
        <link rel=\"shortcut icon\" type=\"image/png\" href=\"./img/favicon.ico\"/>
      </head>
      <body>
        <header>
          <link href=\"https://fonts.googleapis.com/css?family=Inconsolata\" rel=\"stylesheet\">
          <link href=\"https://fonts.googleapis.com/css?family=Source+Sans+Pro\" rel=\"stylesheet\">
          <link rel=\"stylesheet\" href=\"./css/estilo_base.css\">
          <link rel=\"stylesheet\" href=\"./css/$estilo.css\">
        </header>
      </div>";
  }

  function pieDePagina(){
    echo "
        <footer><h6>Web by Raúl Ruano Narváez & Juan Carlos Pulido</h6></footer>
      </body>
    </html>";
  }
?>
