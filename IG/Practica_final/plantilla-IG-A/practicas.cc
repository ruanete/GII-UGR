//**************************************************************************
// Prácticas
//
// F.J. melero
//
// GPL
//**************************************************************************


#include "aux.h" // includes de OpenGL, windows, y librería std de C++
#include "escena.h"

// variable que contiene un puntero a la escena
Escena *escena = nullptr ;
int estadoRaton=0;


//***************************************************************************
// Funcion principal que redibuja la escena
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void draw_scene(void)
{
	if ( escena != nullptr )
      escena->dibujar();
	//Antes de hacer seleccion tenia esto descomentado, para poder usar seleccion tuve que llamarlo
	//en el dibujar de escena
	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size( int newWidth, int newHeight )
{
	if ( escena != nullptr )
      escena->redimensionar(newWidth,newHeight);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys( unsigned char tecla, int x, int y )
{
	int salir = 0;

   if ( escena!= nullptr )
      salir = escena->teclaPulsada( tecla, x, y );

	if ( salir )
   {
		delete escena;
      escena = nullptr ;
		exit(0);
	}
   else
		glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys( int tecla, int x, int y )
{
	if (escena!=NULL)
		escena->teclaEspecial( tecla, x, y );
	glutPostRedisplay();
}

//***************************************************************************
// Función que gestora del evento desocupado
//***************************************************************************

void funcion_desocupado(){
	escena->mgeDesocupado();
}

//***************************************************************************
// Función que imprime un manual de uso del programa
//***************************************************************************

void MenuUso(){
	cout << endl << "**********TECLAS**********" << endl;
	cout << "-> Q para salir." << endl;
	cout << "-> O para cambiar de objeto." << endl;
	cout << "-> M para cambiar de modo (Vertices, Aristas, Solido, Ajedrez, Iluminacion y Textura)." << endl;
	cout << "-> V para cambiar entre modo Inmediato y Diferido." << endl;
	cout << "-> A para activar animación del modelo jerarquico." << endl;
	cout << "-> P para cambiar parametro a modificar del modelo jerarquico." << endl;
	cout << "-> Z incrementa el valor del parametro del modelo jerarquico." << endl;
	cout << "-> z decrementa el valor del parametro del modelo jerarquico." << endl;
	cout << "-> > acelera la animacion del modelo jerarquico." << endl;
	cout << "-> < decelera la animacion del modelo jerarquico." << endl;
	cout << "-> L cambia entre las diferentes luces (BLANCA, MAGENTA y AMBAS)." << endl;
	cout << "-> S cambia el suavizado en el modo iluminación." << endl;
	cout << "-> N cambia el material del objeto." << endl;
	cout << "-> 1 decrementa el angulo de la luz MAGENTA." << endl;
	cout << "-> 2 aumenta el angulo de la luz MAGENTA." << endl;
	cout << "-> Rueda de ratón realiza zoom." << endl;
	cout << "-> Matén pulsado botón derecho del raton y muevelo para mover la camara." << endl;
	cout << "-> Usa el click izquierdo del raton para realizar la seleccion en el ultimo objeto (OBJETO 10)." << endl;
	cout << "-> F1 cámara ortogonal." << endl;
	cout << "-> F2 cámara perspectiva." << endl;
	cout << "-> R pone la cámara en la posición inicial." << endl;
	cout << "**************************" << endl;
}

//***************************************************************************
// Función que gestiona el Click del Ratón
//***************************************************************************
int ant_x=0, ant_y=0;

void clickRaton(int boton, int estado, int x, int y){
	if(boton == GLUT_RIGHT_BUTTON){
		if(estado == GLUT_DOWN){
			//cout << "Se pulsa el botón derecho, por lo que se entra en el estado -moviendo cámara-" << endl;
      estadoRaton = 1;
			ant_x = x;
			ant_y = y;
		}else{
			//cout << "Se levanta el botón derecho, por lo que se sale del estado -moviendo cámara-" << endl;
      estadoRaton = 0;
		}
		glutPostRedisplay();
	}else if(boton == 3 || boton == 4){
		if ( boton == 3 ){
			//cout << "Zoom positivo" << endl;
			escena->zoomCamara(1.0,1.2);
		}else if( boton == 4 ){
			//cout << "Zoom negativo" << endl;
			escena->zoomCamara(1.2,1.0);
		}
		glutPostRedisplay();
	}else if(boton== GLUT_LEFT_BUTTON) {
	  if( estado == GLUT_DOWN) {
	      estadoRaton = 2;
	      ant_x=x;
	      ant_y=y;
	      escena->pick_color(ant_x, ant_y);
	  }
	}
}

//***************************************************************************
// Función que gestiona el Movimiento del Ratón
//***************************************************************************

void ratonMovido(int x, int y){
	if(estadoRaton==1)
		escena->moverCamara(x-ant_x,y-ant_y);

	ant_x = x;
	ant_y = y;
	glutPostRedisplay();
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main( int argc, char **argv )
{
   using namespace std ;

   // crear la escena (un puntero a la misma)
   escena = new Escena();

   // Incialización de GLUT

   // se llama a la inicialización de glut
   glutInit( &argc, argv );

   // se indica las caracteristicas que se desean para la visualización con OpenGL
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

   // variables que determninan la posicion y tamaño de la ventana X
   const int UI_window_pos_x  = 50,
             UI_window_pos_y  = 50,
             UI_window_width  = 500,
             UI_window_height = 500;

   // posicion de la esquina inferior izquierdad de la ventana
   glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

   // tamaño de la ventana (ancho y alto)
   glutInitWindowSize(UI_window_width,UI_window_height);

   // llamada para crear la ventana, indicando el titulo
   glutCreateWindow("Practicas IG: Raul Ruano Narvaez");

   // asignación de la funcion llamada "dibujar" al evento de dibujo
   glutDisplayFunc( draw_scene );

   // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
   glutReshapeFunc( change_window_size );

   // asignación de la funcion llamada "tecla_normal" al evento correspondiente
   glutKeyboardFunc( normal_keys );

   // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
   glutSpecialFunc( special_keys );

   // inicialización de librería GLEW (solo en Linux)
   #ifdef LINUX
   const GLenum codigoError = glewInit();

   if ( codigoError != GLEW_OK ) // comprobar posibles errores
   {
      cout << "Imposible inicializar ’GLEW’, mensaje recibido: "
             << glewGetErrorString(codigoError) << endl ;
      exit(1) ;
   }
   #endif

   // funcion de inicialización de la escena (necesita que esté la ventana creada)
   escena->inicializar( UI_window_width, UI_window_height );

   // TEST

	 MenuUso();

	 //Uso del ratón en Escena
	 glutMouseFunc (clickRaton);
	 glutMotionFunc (ratonMovido);

   // ejecutar del bucle de eventos
   glutMainLoop();

   return 0;
}
