## EJERCICIO 7.1: ¿Qué tamaño de unidad de unidad RAID se obtendrá al configurar un RAID 0 a partir de dos discos de 100 GB y 100 GB? ¿Qué tamaño de unidad de unidad RAID se obtendrá al configurar un RAID 0 a partir de tres discos de 200 GB cada uno? 

Para la primera pregunta serían 200GB y para la segunda pregunta serian 600GB

## EJERCICIO 7.2: ¿Qué tamaño de unidad de unidad RAID se obtendrá al configurar un RAID 1 a partir de dos discos de 100 GB y 100 GB? ¿Qué tamaño de unidad de unidad RAID se obtendrá al configurar un RAID 1 a partir de tres discos de 200 GB cada uno? 

Para la primera pregunta serían 100GB ya que es en forma de espejo y para la segunda pregunta serían 200GB por lo mismo. 

## EJERCICIO 7.3: Buscar información sobre los sistemas de ficheros en red más utilizados en la actualidad y comparar sus características. Hacer una lista de ventajas e inconvenientes de todos ellos, así como grandes sistemas en los que se utilicen.
Configurar en una máquina virtual un servidor NFS. Montar desde otra máquina virtual en la misma subred la carpeta exportada y comprobar que ambas pueden acceder a la misma para lectura y escritura. 

A nivel domestico los sistemas de ficheros de red son SMB (microsoft), NFS (unix), AFP (apple) destacar que en linux tambien se recomienda SAMBA en lugar de NFS por su mejores características SMB1 era propietario, NFS se ha quedado desfasado, ademas de ser lento, AFP no incorpora el sistema de cuotas de disco y las opciones de seguridad de SMB2, por lo que todo el mundo recomienda usar SMB2 ya que es un estandar abierto
