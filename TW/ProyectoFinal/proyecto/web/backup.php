<?php
	require_once('base_web.php');
	require_once('bd.php');
	require('checkAdmin.php');

	if (isset($_GET['download'])) {
		$db=DB_conexion();
		if ($db) {
			header('Content-Type: application/octet-stream');
			header('Content-Disposition: attachment; filename="db_backup.sql"');
			$salida = DB_backup($db);
			echo($salida);
		}
  		DB_desconexion($db);
	} 
	else if(isset($_GET['clear'])) {
		if(isset($_GET['confirm'])){
			$db=DB_conexion();
			if ($db) {
				$errores = DB_clearALL($db);
				if(count($errores) == 0){
					echo("<h1>Base de datos borrada correctamente</h1>");
				}
				else{
					echo("<h1>Error al borrar la base de datos</h1>");
					print_r($errores);
				}
			}
	  		DB_desconexion($db);
		}
		else{
			echo<<<HTML
			<a href='{$_SERVER['SCRIPT_NAME']}?backup=yes&clear=yes&confirm=yes' style="color: red">Pulse aquí</a> para confirmar el BORRADO completo de la BASE DE DATOS
HTML;
		}
	} 
	else if (isset($_POST['subido'])) {
		/* Comprobar que se ha subido algún fichero */
		if((sizeof($_FILES)==0) || !array_key_exists("fichero",$_FILES))
			$error = "No se ha podido subir el fichero";
		else if (!is_uploaded_file($_FILES['fichero']['tmp_name']))
			$error = "Fichero no subido. Código de error: ".$_FILES['fichero']['error'];
		else {
			$db=DB_conexion();
			$error = DB_restore($db,$_FILES['fichero']['tmp_name']);
			DB_desconexion($db);
		}

		if (isset($error) && count($error) > 0){
			echo($error);
		}
		else{
			echo("<h1>Base de datos restaurada correctamente</h1>");
		}
	} 
	else {
		echo<<<HTML

		<h1>Descargar copia de seguridad</h1>
		<a href='backup.php?download'>Pulse aquí</a> para descargar un fichero con los datos de la copia de seguridad	
		<h1>Restaurar copia de seguridad</h1>
		<form action="{$_SERVER['SCRIPT_NAME']}?backup=yes" method='post' enctype='multipart/form-data'>
			<label for='fichero'>Fichero: </label>
			<input type='file' name='fichero'><br>
			<input type='submit' value='Subir' name='subido'>
		</form> 
		<h1>Limpiar Base de datos</h1>
		<a href='{$_SERVER['SCRIPT_NAME']}?backup=yes&clear=yes' style="color: red">Pulse aquí</a> limpiar la Base de datos 
HTML;
	}
?>