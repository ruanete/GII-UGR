## EJERCICIO 4.1: Buscar información sobre cuánto costaría en la actualidad un mainframe. Comparar precio y potencia entre esa máquina y una granja web de unas prestaciones similares. 

Se encuentra poca información acerca de mainframes debido a que ya practicamente no se usan por su coste, mantenimiento... Teniendo en cuenta esto, he leido en la siguiente [noticia](http://www.cioal.com/2011/08/26/ibm-lanza-mainframe-de-bajo-costo-en-latinoamerica/) que el modelo de IBM Z114 cuesta alrededor de 410 mil dolares incluyendo tres años de mantenimiento y SW de virtualización.

En cuanto a una granja web podemos ver en la siguiente [web](https://www.gmv.com/blog_gmv/solucion-caso-de-gestion-la-granja-web/) en la que hicieron calculos de cuanto costaria una granja web, y podriamos decir que para estar al nivel del mainframe tendriamos que gastar alrededor de los 100000€.

## EJERCICIO 4.2: Buscar información sobre precio y características de balanceadores hardware específicos. Compara las prestaciones que ofrecen unos y otros.

Dejo una [web](https://kemptechnologies.com/es/server-load-balancing-appliances/product-matrix.html) con la comparativa de precios y de hardware entre los diferentes balanceadores de esta compañia, destacar que el precio ronda desde los 4000-58000€

## EJERCICIO 4.3: Buscar información sobre los métodos de balanceo que implementan los dispositivos recogidos en el ejercicio 4.2.

No he encontrado en su web información al respecto.

## EJERCICIO 4.4: Instala y configura en una máquina virtual el balanceador ZenLoadBalancer. 

Por falta de tiempo no he realizado su instalación.

## EJERCICIO 4.5: Probar las diferentes maneras de redirección HTTP. ¿Cuál es adecuada y cuál no lo es para hacer balanceo de carga global? ¿Por qué? 

En la mayoría de los casos se utiliza un archivo .htaccess o un script PHP para redireccionar un dominio. La ventaja de estos métodos reside en que es posible definir individualmente qué código de estado HTTP debe mostrarse al agente de usuario, caracterizando así las redirecciones como temporales o permanentes. Así, resultan relevantes especialmente dos códigos de estado HTTP, el 301 y el 302:

301 – Moved Permanently: la página solicitada por el agente de usuario estará disponible de manera permanente bajo la URL       redireccionada. La antigua URL será, por lo tanto, inválida.

302 – Moved Temporarily: la página solicitada por el agente de usuario está temporalmente disponible bajo la nueva URL. A       diferencia de la redirección 301, la antigua dirección sigue siendo válida.

En caso de que no se defina específicamente el código de estado HTTP, el servidor mostrará por defecto un código de estado 302, lo que no siempre es ideal. Por lo tanto, es aconsejable introducir manualmente todos los códigos de estado para evitar errores de indexación como el URL Hijacking. A diferencia de la redirección 301, el código de estado 302 le comunica al crawler que la URL original debe seguir siendo indexada. De mantenerse activa, la URL antigua competirá con la nueva en el índice de los motores de búsqueda.

## EJERCICIO 4.7: Buscar información sobre los bloques de IP para los distintos países o continentes. Implementar en JavaScript o PHP la detección de la zona desde donde se conecta un usuario.

Un script para detectarlo:
  ~~~
<?php
error_reporting(E_ALL & ~E_NOTICE);
include("geoiploc.php"); 
  if (empty($_POST['checkip']))
  {
	$ip = $_SERVER["REMOTE_ADDR"]; 
  }
  else
  {
	$ip = $_POST['checkip']; 
  }
?> 
~~~

[Web](https://www.countryipblocks.net/country_selection.php) de bloques de ip por pais.

## EJERCICIO 4.8: Buscar información sobre métodos y herramientas para implementar GSLB. 

Adjunto [web](https://www.digitalocean.com/community/questions/how-to-setup-global-load-balancing-using-digital-ocean-dns-ubuntu-and-nginx) donde lo explican con ubuntu server y nginx.

