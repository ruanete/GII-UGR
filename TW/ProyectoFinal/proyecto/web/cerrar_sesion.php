<?php
  // La sesión debe estar iniciada
  if (session_status()==PHP_SESSION_NONE)
    session_start();
  // Destruir sesión
  session_destroy();
  header('Location: ./index.php');
?>
