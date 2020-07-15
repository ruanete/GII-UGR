
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




DROP TABLE conciertos;

CREATE TABLE `conciertos` (
  `codconcierto` int(11) NOT NULL AUTO_INCREMENT,
  `fecha` date NOT NULL,
  `ciudad` varchar(100) NOT NULL,
  `lugar` varchar(100) NOT NULL,
  PRIMARY KEY (`codconcierto`),
  UNIQUE KEY `fecha` (`fecha`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;




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




DROP TABLE logEventos;

CREATE TABLE `logEventos` (
  `codlog` int(11) NOT NULL AUTO_INCREMENT,
  `descripcion` varchar(100) NOT NULL,
  `fecha` datetime NOT NULL,
  PRIMARY KEY (`codlog`)
) ENGINE=InnoDB AUTO_INCREMENT=210 DEFAULT CHARSET=latin1;




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
) ENGINE=InnoDB AUTO_INCREMENT=33 DEFAULT CHARSET=latin1;




DROP TABLE secciones;

CREATE TABLE `secciones` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `titulo` text COLLATE utf8_spanish_ci NOT NULL,
  `link` text COLLATE utf8_spanish_ci NOT NULL,
  `cuerpo` text COLLATE utf8_spanish_ci NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8 COLLATE=utf8_spanish_ci;




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

INSERT INTO usuarios VALUES("admin","admin","admin admin","admin@correo.es","$2y$10$KIgtu6mAyAYuCNlDkisTyOyTcjkz3XhmBhrUtwmz2CMyl4/WGezAa","622222222","Administrador");
INSERT INTO usuarios VALUES("gpedidos","gpedidos","gpedidos gpedidos","gpedidos@correo.es","$2y$10$tZd0r762a0T9SdpaiaNUl.Kqe9IMqFQAAxPJbXc.va9MPa3q/xma2","622222222","Gestor_Compras");



