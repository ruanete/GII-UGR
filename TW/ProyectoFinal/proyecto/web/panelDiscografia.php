<?php
	require_once('base_web.php');
	require_once('bd.php');
	require('checkAdmin.php');

	cabecera_NOMenu("administracion");
	sidenav();

	echo "<div class=\"main\">";

	$db = DB_conexion();
	$scriptName = "panelDiscografia.php";
	if(isset($_REQUEST['editar_seccion'])){
		if(isset($_POST["titulo"]) && isset($_POST["img"]) && isset($_POST["web"])  && isset($_POST["anio"]) && isset($_POST["precio"]) && isset($_POST["id"])){
			// Modificar un disco que ya existe
			$sencillo =   isset($_POST["sencillo"]) ? 1 : 0;
			$disco = new Disco($_POST["titulo"], $_POST["img"], $_POST["web"], $sencillo, $_POST["anio"], $_POST["precio"], $_POST["id"]);
			if(DB_updateDisco($db, $disco)){
				echo "<h1> Cambios Realizados correctamente</h1>" .PHP_EOL;
			}
			else{
				echo "<h1>Fallo en la modificacion</h1>" .PHP_EOL;
			}
			echo "<a href=\"administracion.php?editar_discografia=yes\">Volver</a>" .PHP_EOL;
		}
		else{
			echo<<<HTML
			<h1>Editar Discografía</h1>
            <form action='./panelDiscografia.php' method='GET'>
              <input type='submit' name='nueva_seccion' value='Crear nuevo disco'/>
            </form>
			<hr>
HTML;
			$discos = DB_getDisco($db);
			foreach ($discos as $val) {
				echo $val->htmlFormView(array($scriptName, "?editar_seccion")) . PHP_EOL;
				echo "<hr>" . PHP_EOL;
			}
		}
	}
	else if(isset($_REQUEST['nueva_seccion'])){
		if(isset($_POST["titulo"]) && isset($_POST["img"]) && isset($_POST["web"]) && isset($_POST["precio"]) && isset($_POST["anio"])){
			//Nuevo disco
			$sencillo =  isset($_POST["sencillo"]) ? 1 : 0;
			$disco = new Disco($_POST["titulo"], $_POST["img"], $_POST["web"], $sencillo, $_POST["anio"], $_POST["precio"], -1);
			if(DB_createDisco($db, $disco)){
				echo "<h1> Nuevo disco añadido correctamente</h1>" .PHP_EOL;
			}
			else{
				echo "<h1>Fallo en la creación</h1>" .PHP_EOL;
			}
			echo "<a href=\"administracion.php?editar_discografia=yes\">Volver</a>" .PHP_EOL;
		}
		else{
			$disco = new Disco("", "", "", 0, 0, 0, -1);
			echo $disco->htmlFormViewNoSongs(array($scriptName, "?nueva_seccion"));
		}
	}
	else if(isset($_REQUEST['borrar_seccion'])){
		if(isset($_GET["id"])){
			if(DB_borrarDisco($db, $_GET["id"])){
				echo "<h1> Disco borrado correctamente</h1>" .PHP_EOL;
			}
			else{
				echo "<h1>Fallo al borrar la seccion</h1>" .PHP_EOL;
			}
			echo "<a href=\"administracion.php?editar_discografia=yes\">Volver</a>" .PHP_EOL;
		}
	}
	else if(isset($_REQUEST['editar_cancion'])){
		if(isset($_POST["titulo"]) && isset($_POST["duracion"]) && isset($_POST["id_disco"]) && isset($_POST["id"])){
			// Modificar una canción que ya existe
			$cancion = new Cancion($_POST["titulo"], $_POST["duracion"], $_POST["id"], $_POST["id_disco"]);
			if(DB_updateCancion($db, $cancion)){
				echo "<h1> Cambios Realizados correctamente</h1>" .PHP_EOL;
			}
			else{
				echo "<h1>Fallo en la modificacion</h1>" .PHP_EOL;
			}
			echo "<a href=\"administracion.php?editar_discografia=yes\">Volver</a>" .PHP_EOL;
		}
		else{
			echo<<<HTML
			<h1>Editar Discografía</h1>
            <form action='./panelDiscografia.php' method='GET'>
              <input type='submit' name='nueva_seccion' value='Crear nuevo disco'/>
            </form>
			<hr>
HTML;
			$discos = DB_getDisco($db);
			foreach ($discos as $val) {
				echo $val->htmlFormView(array($scriptName, "?editar_seccion")) . PHP_EOL;
				echo "<hr>" . PHP_EOL;
			}
		}
	}
	else if(isset($_REQUEST['nueva_cancion'])){
		if(isset($_POST["titulo"]) && isset($_POST["duracion"]) && isset($_POST["id_disco"])){
			//Nueva canción
			$cancion = new Cancion($_POST["titulo"], $_POST["duracion"], -1, $_POST["id_disco"]);
			if(DB_createCancion($db, $cancion)){
				echo "<h1> Nueva canción añadida correctamente</h1>" .PHP_EOL;
			}
			else{
				echo "<h1>Fallo en la creación de la nueva cancion</h1>" .PHP_EOL;
			}
			echo "<a href=\"administracion.php?editar_discografia=yes\">Volver</a>" .PHP_EOL;
		}
		else{
			$id_disco = isset($_GET["id_disco"]) ? $_GET["id_disco"] : -1;
			if($id_disco != -1){
				$disco = DB_getDiscoByID($db, $id_disco);
				if($disco != null)
					$titulo = $disco->titulo;
				else
					$titulo = "";
			}
			else
				$titulo = "";

			echo "<h1>Nueva cancion - $titulo</h1>" .PHP_EOL;
			$cancion = new Cancion("", 0, -1, $id_disco);
			if($titulo === "")
				echo $cancion->htmlFormView($scriptName."?nueva_cancion=true");
			else
				echo $cancion->htmlFormViewIDnoEditable($scriptName."?nueva_cancion=true");
		}
	}
	else if(isset($_REQUEST['borrar_cancion'])){
		if(isset($_GET["id"])){
			if(DB_borrarCancion($db, $_GET["id"])){
				echo "<h1> Canción borrada correctamente</h1>" .PHP_EOL;
			}
			else{
				echo "<h1>Fallo al borrar la seccion</h1>" .PHP_EOL;
			}
			echo "<a href=\"administracion.php?editar_discografia=yes\">Volver</a>" .PHP_EOL;
		}
	}
	else{
		echo<<<HTML
		<h1>Editar Discografía</h1>
        <form action='./panelDiscografia.php' method='GET'>
          <input type='submit' name='nueva_seccion' value='Crear nuevo disco'/>
        </form>
		<hr>
HTML;
		$discos = DB_getDisco($db);
		foreach ($discos as $val) {
			echo $val->htmlFormView(array($scriptName, "?editar_seccion")) . PHP_EOL;
			echo "<hr>" . PHP_EOL;
		}
	}
	echo "</div>";
	DB_desconexion($db);
?>
