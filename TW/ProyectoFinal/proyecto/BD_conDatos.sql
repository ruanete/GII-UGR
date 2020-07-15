DROP TABLE canciones;

CREATE TABLE `canciones` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `id_disco` int(11) NOT NULL,
  `titulo` text COLLATE utf8_spanish_ci NOT NULL,
  `duracion` int(11) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id` (`id`),
  KEY `id_disco` (`id_disco`),
  CONSTRAINT `canciones_ibfk_1` FOREIGN KEY (`id_disco`) REFERENCES `discos` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

INSERT INTO canciones VALUES("1","4","Guerrera","25");
INSERT INTO canciones VALUES("16","26","C.Tangana - Ídolo","120");



DROP TABLE conciertos;

CREATE TABLE `conciertos` (
  `codconcierto` int(11) NOT NULL AUTO_INCREMENT,
  `fecha` date NOT NULL,
  `ciudad` varchar(100) NOT NULL,
  `lugar` varchar(100) NOT NULL,
  PRIMARY KEY (`codconcierto`),
  UNIQUE KEY `fecha` (`fecha`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

INSERT INTO conciertos VALUES("2","2018-10-26","Granada","Sala tren");
INSERT INTO conciertos VALUES("3","2018-06-30","Sevilla","Palacio de deportes");
INSERT INTO conciertos VALUES("4","2018-08-31","Malaga","Sala Paris 15");
INSERT INTO conciertos VALUES("6","2018-06-13","Sevilla","Sala City");



DROP TABLE discos;

CREATE TABLE `discos` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `titulo` varchar(100) COLLATE utf8_spanish_ci NOT NULL,
  `img` text COLLATE utf8_spanish_ci NOT NULL,
  `web` text COLLATE utf8_spanish_ci NOT NULL,
  `sencillo` tinyint(1) NOT NULL,
  `anio` int(11) DEFAULT NULL,
  `precio` decimal(4,2) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `titulo` (`titulo`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

INSERT INTO discos VALUES("1","C.Tangana - Ídolo","./img/disco_idolo_ctangana.jpg","./ctangana_idolo.php","0","2017","19.95");
INSERT INTO discos VALUES("3","C.Tangana - Antes de morirme (feat. Rosalia)","./img/sencillo_antesdemorirme_ctangana.jpg","./ctangana_antesdemorirme.php","1","2016","10.00");
INSERT INTO discos VALUES("4","C.Tangana, Dellafuente - Guerrera","./img/sencillo_guerrera_ctangana.jpg","./ctangana_guerrera.php","1","2018","14.00");
INSERT INTO discos VALUES("5","Madrid files (Maqueta)","","","0","2006","10.00");
INSERT INTO discos VALUES("6","Septiembre (Maqueta)","","","0","2006","10.00");
INSERT INTO discos VALUES("7","ElesCrema (Maqueta)","","","0","2006","10.00");
INSERT INTO discos VALUES("8","Desde la octava ventana del bloque (Maqueta)","","","0","2007","10.00");
INSERT INTO discos VALUES("11","Agorazein (LP, Es Tao Chungo Records)","","","0","2008","10.00");
INSERT INTO discos VALUES("12","Agorazein presenta... C.Tangana","","","0","2011","10.00");
INSERT INTO discos VALUES("13","Trouble + Presidente","","","0","2015","10.00");
INSERT INTO discos VALUES("14","10/15","","","0","2015","10.00");
INSERT INTO discos VALUES("15","C. Tangana & Baboon Estudios - Cakes","","","1","2011","10.00");
INSERT INTO discos VALUES("16","C. Tangana - If she don\'t","","","1","2011","10.00");
INSERT INTO discos VALUES("17","C. Tangana - Bésame mucho","","","1","2012","10.00");
INSERT INTO discos VALUES("18","C. Tangana - Sympósion (con Jerv.agz)","","","1","2013","10.00");
INSERT INTO discos VALUES("19","C. Tangana & Rosalía - Antes de morirme","","","1","2016","10.00");
INSERT INTO discos VALUES("26","C.Tangana - ÍdoloLOVES","./img/disco_loves_ctangana.jpg","./ctangana_loves.php","0","2016","10.00");



DROP TABLE logEventos;

CREATE TABLE `logEventos` (
  `codlog` int(11) NOT NULL AUTO_INCREMENT,
  `descripcion` varchar(100) NOT NULL,
  `fecha` datetime NOT NULL,
  PRIMARY KEY (`codlog`)
) ENGINE=InnoDB AUTO_INCREMENT=216 DEFAULT CHARSET=latin1;

INSERT INTO logEventos VALUES("190","Intento fallido de inicio de sesión.","2018-06-11 01:45:26");
INSERT INTO logEventos VALUES("191","Ha iniciado sesión el administrador admin","2018-06-11 01:45:30");
INSERT INTO logEventos VALUES("192","Se ha modificado la cancion con id #1 y titulo Guerrera","2018-06-11 01:51:03");
INSERT INTO logEventos VALUES("193","Se ha modificado la cancion con id #1 y titulo Guerrera","2018-06-11 01:51:09");
INSERT INTO logEventos VALUES("194","Se ha borrado la cancion con id #14","2018-06-11 01:54:19");
INSERT INTO logEventos VALUES("195","Se ha modificado el disco con id #4 y titulo C.Tangana, Dellafuente - Guerrera","2018-06-11 01:57:27");
INSERT INTO logEventos VALUES("196","Se ha modificado la cancion con id #1 y titulo Guerrera","2018-06-11 02:24:32");
INSERT INTO logEventos VALUES("197","Se ha modificado el usuario admin","2018-06-11 15:04:54");
INSERT INTO logEventos VALUES("198","Se ha modificado el usuario gpedidos","2018-06-11 15:05:09");
INSERT INTO logEventos VALUES("199","Intento fallido de inicio de sesión.","2018-06-11 15:05:15");
INSERT INTO logEventos VALUES("200","Intento fallido de inicio de sesión.","2018-06-11 15:05:20");
INSERT INTO logEventos VALUES("201","Intento fallido de inicio de sesión.","2018-06-11 15:05:30");
INSERT INTO logEventos VALUES("202","Ha iniciado sesión el administrador admin","2018-06-11 15:07:04");
INSERT INTO logEventos VALUES("203","Se ha modificado el usuario gpedidos","2018-06-11 15:07:43");
INSERT INTO logEventos VALUES("204","Ha iniciado sesión el gestor de pedidos gpedidos","2018-06-11 15:07:51");
INSERT INTO logEventos VALUES("205","Se ha aceptado el pedido con id #33","2018-06-11 15:08:23");
INSERT INTO logEventos VALUES("206","Se ha denegado el pedido con id #34","2018-06-11 15:09:02");
INSERT INTO logEventos VALUES("207","Ha iniciado sesión el administrador admin","2018-06-11 15:09:14");
INSERT INTO logEventos VALUES("208","Se ha modificado el disco con id #4 y titulo C.Tangana, Dellafuente - Guerrera","2018-06-11 15:10:53");
INSERT INTO logEventos VALUES("209","Se ha modificado el disco con id #1 y titulo C.Tangana - Ídolo","2018-06-11 15:11:03");
INSERT INTO logEventos VALUES("210","Se ha modificado el disco con id #3 y titulo C.Tangana - Antes de morirme (feat. Rosalia)","2018-06-11 15:11:16");
INSERT INTO logEventos VALUES("211","Se ha modificado el disco con id #26 y titulo C.Tangana - ÍdoloLOVES","2018-06-11 15:11:26");
INSERT INTO logEventos VALUES("212","Se ha modificado el disco con id #4 y titulo C.Tangana, Dellafuente - Guerrera","2018-06-11 15:12:14");
INSERT INTO logEventos VALUES("213","Se ha modificado el disco con id #1 y titulo C.Tangana - Ídolo","2018-06-11 15:12:21");
INSERT INTO logEventos VALUES("214","Se ha modificado el disco con id #3 y titulo C.Tangana - Antes de morirme (feat. Rosalia)","2018-06-11 15:12:35");
INSERT INTO logEventos VALUES("215","Se ha modificado el disco con id #26 y titulo C.Tangana - ÍdoloLOVES","2018-06-11 15:12:46");



DROP TABLE pedidos;

CREATE TABLE `pedidos` (
  `codped` int(11) NOT NULL AUTO_INCREMENT,
  `fecha` datetime NOT NULL,
  `estado` enum('Aceptado','Denegado','Pendiente') NOT NULL DEFAULT 'Pendiente',
  `correoEnviado` varchar(100) DEFAULT NULL,
  `motivoDenied` varchar(200) DEFAULT NULL,
  `usuarioGestor` varchar(100) DEFAULT NULL,
  `idDisco` int(11) NOT NULL,
  PRIMARY KEY (`codped`),
  KEY `usuarioGestor` (`usuarioGestor`),
  KEY `idDisco` (`idDisco`),
  CONSTRAINT `pedidos_ibfk_1` FOREIGN KEY (`usuarioGestor`) REFERENCES `usuarios` (`usuario`),
  CONSTRAINT `pedidos_ibfk_2` FOREIGN KEY (`idDisco`) REFERENCES `discos` (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=35 DEFAULT CHARSET=latin1;

INSERT INTO pedidos VALUES("30","2018-06-11 00:39:07","Aceptado","Pedido enviado.","","","4");
INSERT INTO pedidos VALUES("31","2018-06-11 00:42:24","Denegado","Pedido denegado.","Falta pago.","","1");
INSERT INTO pedidos VALUES("32","2018-06-11 00:42:48","Aceptado","OK!","","","3");
INSERT INTO pedidos VALUES("33","2018-06-11 15:08:04","Aceptado","Bien","","gpedidos","4");
INSERT INTO pedidos VALUES("34","2018-06-11 15:08:53","Denegado","fallo","pago","gpedidos","1");



DROP TABLE secciones;

CREATE TABLE `secciones` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `titulo` text COLLATE utf8_spanish_ci NOT NULL,
  `link` text COLLATE utf8_spanish_ci NOT NULL,
  `cuerpo` text COLLATE utf8_spanish_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;

INSERT INTO secciones VALUES("1","Biografía","./img/cantante_ctangana.jpg","Antón Álvarez se da a conocer como \"Crema\" gracias al fenómeno en línea a partir de 2006, cuando empiezan a circular sus maquetas entre los jóvenes.
\n
\nEstudió en colegio San Viator hasta terminar bachillerato y posteriormente estudió la carrera de filosofía en la Universidad Complutense de Madrid. Por aquel entonces, su nombre ya era popular entre los jóvenes que se sentían atraídos por el rap urbano. No fue hasta presentar su maqueta Agorazein en mayo de 2008 cuando consiguió hacerse un sitio en los reproductores de música de la juventud.
\n
\nDespués de aquello, a pesar de tener un buen puesto en el panorama de la música underground, no presentó ninguna maqueta. Solo se dieron a conocer temas en colaboración con otros músicos y cantantes del movimiento independiente. Reapareció en 2011 con un grupo de amigos bajo el nombre de Agorazein, y en ese mismo año dio a conocer un trabajo que llevaba como título su nuevo nombre (C. Tangana) y nuevos sonidos, lo que le valió tantas malas críticas como elogios y nuevos adeptos.
\n
\nC. Tangana había sustituido su particular estilo de frases cortas y directas con frases breves, aparentemente inconexas y cargadas de anglicismos, y las antiguas bases dieron paso a un universo sonoro que realzaba la parte más creativa de la música. Antón señaló en todo momento que su música no tenía más pretensión que la de hacer disfrutar y huía de ser catalogado como músico profesional. Mientras jugaba con la música se ganó la vida trabajando en un Pans and Company y en un \"call center\" de Vodafone, pero su idilio con la música no tuvo más ceses. Estrenando nuevo trabajo en 2012 (que le valió un amplio reconocimiento y un aumento en el fenómeno fan), decidió vivir aislado de los medios de comunicación desde enero de 2013 en su casa en el barrio de Pueblo Nuevo para afrontar una fama con la que no terminaba de sentirse cómodo. Se destapó ante el mundo de internet a través de Twitter en febrero de ese año, caracterizándose por ser escueto y directo como lo es con su música y por generar gran expectación con cada uno de sus movimientos aparentemente calculados con antelación.
\n
\nEn 2016 dio sus primeros conciertos en Hispanoamérica como C. Tangana, donde se había labrado cierto reconocimiento y ya había actuado con su grupo Agorazein, y abandonó su trabajo desde 2015 para dedicarse por completo a la música.
\n
\nEn 2017, inició una gira por Latinoamérica llamada \"C.Tangana Latino Tour\". Tras la gira, anuncia oficialmente su firma con la discográfica Sony Music. Junto a Sony Music lanzó \"Mala Mujer\" alcanzando la fama en España.4​ Dicho tema, ocupó las primeras posiciones en las listas virales de Spotify de diferentes países de Europa y América Latina así como de las principales listas españolas. De esta manera, \"Mala Mujer\" se ha convertido en una de las canciones del verano 2017 consiguiendo el disco de platino, primera certificación de la carrera de C. Tangana. Dicha canción suena actualmente en las principales radios y discotecas de nuestro país.");
INSERT INTO secciones VALUES("2","Estilo","./img/ctangana_cantando.jpg","Con Agorazein irrumpió entre la gente gracias a la fusión entre unas bases que presentaban buenos ritmos y unas melodías que desprendían tristeza y rebeldía adolescentes. Acostumbrados a la dureza del rap tanto en letras como en bases, los sonidos suaves de C. Tangana pasaron a ser tan importantes como la voz, y a esta le empezó a dar tratamiento sonoro. Visualmente también rompió esquemas al presentarse sin complejos con ropa de marca y entornos de clase media-alta, algo que chocaba frontalmente con los prejuicios y la moral imperante en el hip-hop en España. La inmensa mayoría de grupos de entonces todavía presentaban orgullo de clase obrera y se consideraba propio de los suburbios y la ropa deportiva, aunque era un hecho que las multinacionales, el éxito y el dinero ya formaban parte del mundo del rap. En 2015 recuperó un estilo lírico más tradicional pero continuó defendiendo la parte más creativa de su música.
\n
\nEn 2015 vivió una agria polémica con Los Chikos del Maiz, que incluyeron en un videoclip una parodia del estilo de C. Tangana. La polémica, duró hasta 2016, intercambiando canciones de respuesta, lo que en la jerga del rap se conoce como \"beef\". Cuando C.Tangana publicó el videoclip de Alligators hacía alusión a la marca de ropa Lacoste, esto lo aprovecharon Los Chikos del Maiz para parodiarlo en el clip de su canción “Tú al gulag y yo a California”. Como respuesta, C. Tangana sacó la canción \"Nada\", donde su intención fue narrar en forma de canción la vivencia del propio C. Tangana a modo de algo llamado, en el mundo del rap underground \"praw lesson\", no intentar insultar o discutir de forma intrascendente. Una vez pasada la polémica declaró a Seven Star Radio que Los Chikos del Maiz hacen negocio de la imagen revolucionaria de izquierda, alegando que es un grupo que se recrea en ideas que no aportan nada nuevo y su música es publicidad de un sector reducido de la población. En 2016 Los Chikos del Maiz le dedican \"Los Pollos hermanos\", al que C. Tangana contesta a las pocas horas, con \"Los Chikos de Madriz\".
\n
\nEn sus canciones, C. Tangana transmite ideales individualistas, y a veces ciertos medios de comunicación han interpretado frases machistas.​ Respecto a sus opiniones políticas, explicó que «no creo en la democracia representativa».​");
INSERT INTO secciones VALUES("3","Influencias","","Su primer contacto con el rap fue a través del disco Ill Communication de Beastie Boys y la película Fear of a Black Hat, tal y como menciona en el tema \"Diez años\". Entre sus influencias ha mencionado el If You’re Reading This It’s Too Late de Drake, a Pharrell Williams o a Kanye West, destacando de estos su capacidad y tendencia para innovar y captar la atención del público. Sin embargo, en varias ocasiones ha manifestado que escucha música de todos los estilos y que de todo consigue obtener algo interesante. Su influencia no procede de músicos concretos, sino de movimientos y tendencias musicales que acoge en sus trabajos");



DROP TABLE usuarios;

CREATE TABLE `usuarios` (
  `usuario` varchar(100) NOT NULL,
  `nombre` varchar(100) NOT NULL,
  `apellidos` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `password` varchar(255) NOT NULL,
  `telefono` varchar(20) NOT NULL,
  `tipo_usuario` enum('Administrador','Gestor_Compras') NOT NULL,
  PRIMARY KEY (`usuario`),
  UNIQUE KEY `email` (`email`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

INSERT INTO usuarios VALUES("admin","admin","admin","admin@correo.es","$2y$10$KIgtu6mAyAYuCNlDkisTyOyTcjkz3XhmBhrUtwmz2CMyl4/WGezAa","622222222","Administrador");
INSERT INTO usuarios VALUES("gpedidos","gpedidos","gpedidos","gpedidos@correo.es","$2y$10$HQkl2UenqyTQNvjDH7haHehPIt6efTT3FJcHB1QFfXgtcm0UjeFQK","622222222","Gestor_Compras");
