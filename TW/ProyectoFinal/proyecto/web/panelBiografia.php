<?php
	require_once('base_web.php');
	require_once('bd.php');
	require('checkAdmin.php');

	if(isset($_GET["nueva_seccion"]) || isset($_GET["editar_seccion"]) || isset($_GET["borrar_seccion"])){
		cabecera_NOMenu("administracion");
		sidenav();

		echo "<div class=\"main\">";
	}
	$db = DB_conexion();
	$scriptName = "panelBiografia.php";
	if(!isset($_GET['nueva_seccion']) && !isset($_GET['borrar_seccion'])){
		if(isset($_POST["titulo"]) && isset($_POST["link"]) && isset($_POST["cuerpo"]) && isset($_POST["id"])){
			// Modificar una seccion que ya existe
			$seccion = new SeccionBio($_POST["titulo"], $_POST["link"], $_POST["cuerpo"], $_POST["id"]);
			if(DB_updateSeccion($db, $seccion)){
				echo "<h1> Cambios Realizados correctamente</h1>" .PHP_EOL;
			}
			else{
				echo "<h1>Fallo en la modificacion</h1>" .PHP_EOL;
			}
			echo "<a href=\"administracion.php\">Volver</a>" .PHP_EOL;
		}
		else{
			$secciones = DB_getSecciones($db);
			echo<<<HTML
			<h1>Editar Secciones de Biografía</h1>
            <form action='./panelBiografia.php' method='GET'>
              <input type='submit' name='nueva_seccion' value='Crear nueva seccion'/>
            </form>
			<hr>
HTML;

			foreach ($secciones as $sec) {
				echo $sec->htmlFormView($scriptName) . PHP_EOL;
				echo "<hr>" . PHP_EOL;
			}
		}
	}
	else if(isset($_GET['nueva_seccion'])){
		if (isset($_POST["titulo"]) && isset($_POST["link"]) && isset($_POST["cuerpo"])) {
			//Nueva Seccion
			$seccion = new SeccionBio($_POST["titulo"], $_POST["link"], $_POST["cuerpo"], -1);
			if(DB_createSeccion($db, $seccion)){
				echo "<h1> Nueva sección añadida correctamente</h1>" .PHP_EOL;
			}
			else{
				echo "<h1>Fallo en la creación</h1>" .PHP_EOL;
			}
			echo "<a href=\"administracion.php\">Volver</a>" .PHP_EOL;
		}
		else{
			$seccion = new SeccionBio("" , "", "" , -1);
			echo $seccion->htmlFormView($scriptName."?nueva_seccion");
		}
	}
	else if(isset($_GET['borrar_seccion'])){
		if(isset($_GET["id"])){
			if(DB_borrarSeccion($db, $_GET["id"])){
				echo "<h1> Sección borrada correctamente</h1>" .PHP_EOL;
			}
			else{
				echo "<h1>Fallo al borrar la seccion</h1>" .PHP_EOL;
			}
			echo "<a href=\"administracion.php\">Volver</a>" .PHP_EOL;
		}
	}
	else{
		$secciones = DB_getSecciones($db);
		echo "<h1>Editar Secciones de Biografía</h1>";
		foreach ($secciones as $sec) {
			echo $sec->htmlFormView($scriptName);
		}
	}
	if(isset($_GET["nueva_seccion"]) || isset($_GET["editar_seccion"]) || isset($_GET["borrar_seccion"]))
		echo "</div>";
	DB_desconexion($db);
?>
