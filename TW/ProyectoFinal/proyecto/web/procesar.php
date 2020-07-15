<script type="text/javascript" src="./js/ValidacionFormularios.js"></script>
<?php
  require_once('bd.php');

  if(isset($_POST["id"], $_POST["nombre"],$_POST["apellidos"],$_POST["telefono"],$_POST["correo"],$_POST["metodo_pago"],$_POST["numero_tarjeta"],$_POST["mes_caducidad"],
    $_POST["anio_caducidad"],$_POST["codigo_cvc"],$_POST["provincia"],$_POST["poblacion"],$_POST["codigo_postal"],$_POST["calle"])){

    $id = $_POST["id"];
    $bd = DB_conexion();
    $result = mysqli_query($bd, "INSERT INTO pedidos (fecha, idDisco) VALUES (now(),'$id')");

    if (!$result) {
      $info[] = 'Error al insertar en la base de datos el pedido.';
      $info[] = mysqli_error($bd);
    }else{
      require_once('base_web.php');
      require_once('bd.php');
      cabecera("tienda");
      echo "<h2>Pedido realizado. Gracias por su compra.</h2>";
      //header('Location: index.php');?>
      <script type="text/javascript">
      function redireccionarPagina() {
        window.location = "./index.php";
      }

      setTimeout("redireccionarPagina()", 2000);
      </script>
  <?php  }

    DB_desconexion($bd);
  }else{
    header('Location: index.php');
  }
?>
