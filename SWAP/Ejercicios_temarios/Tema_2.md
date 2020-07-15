## EJERCICIO 2.1: Calcular la disponibilidad del sistema si tenemos dos réplicas de cada elemento (en total 3 elementos en cada subsistema). 

Las tablas con los datos estan en las transparencias.
Para calcular la tabla con tres elementos utilizaremos la siguiente ecuación:

  As = ACn-1 + ((1 - ACn-1) * ACn)
  
Tenemos entonces: 99.6625 % * 99.9 % * 99.9999999 % * 99.9992 % * 99.6625 % * 99.9999 % * 99.99 % * 99.9875 % = 99.2035 %

## EJERCICIO 2.2: Buscar frameworks y librerías para diferentes lenguajes que permitan hacer aplicaciones altamente disponibles con relativa facilidad.Como ejemplo, examina PM2 https://github.com/Unitech/pm2 que sirve para administrar clústeres de NodeJS. 

-NodeJS: PM2.

-Java: JBoss.

-Python:: Django, TurboGears.

-PHP: Yii, Phalcon, Symfony.

-JavaScript: AngularJS.

## EJERCICIO 2.3: ¿Cómo analizar el nivel de carga de cada uno de los subsistemas en el servidor? Buscar herramientas y aprender a usarlas. ...¡o recordar cómo usarlas! 

Para monitorizar hardware, software, redes de manera más especifica:
- Zabbix
- Apache benchmark
- Nagios
- Munin 

Luego tenemos herramientas del propio linux para monitorizar procesos en ejecucion..:
- Top
- ps

## EJERCICIO 2.4: Buscar ejemplos de balanceadores software y hardware (productos comerciales). Buscar productos comerciales para servidores de aplicaciones. Buscar productos comerciales para servidores de almacenamiento. 

Balanceadores software: HAProxy, LVS (Linux Virtual Server), Nginx, Pound, Zen Load Balancer...
Balanceadores hardware: CISCO, F5 BIG-IP LTM, Ondemand Switch, Barracuda...

En cuanto a productos comerciales para servidores de aplicaciones:
- WebLogic de Oracle. 
- WebSphere de IBM. 
- JBoss AS de JBoss (RedHat). 
- Geronimo y TomEE de Apache. 

En cuanto a productos comerciales para servidores de almacenamiento:
- Amazon EC2
- Microsoft Azure
- Lenovo thinkserver
- Dell EMC
