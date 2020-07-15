<?php
  if(!isset($_SESSION))
    session_start();

  if(!isset($_SESSION["sesion_admin"])){  	
    header('Location: ./identificacion.php');
  }
?>