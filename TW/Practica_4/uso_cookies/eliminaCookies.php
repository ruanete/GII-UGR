<?php
  if (isset($_POST['finalizar_compra'])) {
    setcookie("nombre",'0',time()-1000);
    setcookie("producto",'0',time()-1000);
    setcookie("talla",'0',time()-1000);
    setcookie("color",'0',time()-1000);
    header('Location: ./formulario_producto.html');
  }
?>
