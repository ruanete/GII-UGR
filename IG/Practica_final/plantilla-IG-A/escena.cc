#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 0.1;
    Back_plane        = 2000.0;
    Observer_distance = 4.0;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;
    zoom = 1.0;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de las prácticas: Mallas o Jerárquicos....
    cubo = new Cubo();
    tetraedro = new Tetraedro();
    objeto_ply = new ObjPLY("plys/beethoven.ply");
    objeto_revolucion = new ObjRevolucion("plys/peon.ply");
    cilindro = new Cilindro(5,20);
    cono = new Cono(5,20);
    esfera = new Esfera(20,20);
    objeto_jerarquico = new ObjJerarquico();
    cuadro = new Cuadro("./images/imagen.png");
    cubo_skybox = new Cubo("./images/skybox.png");
    piramide = new Piramide();
    objeto_seleccion = new ObjetoSeleccion();

    // .......completar: ...
    // .....

    num_objetos = 11 ; // se usa al pulsar la tecla 'O' (rotar objeto actual)
    num_modos = 6; //Vertices, Aristas, Solido, Ajedrez, Iluminacion y Textura
    num_dibujados = 2; //Diferido e inmediato
    num_luces = 3;  //Luz blanca, Luz Magenta y Ambas activadas
    num_materiales = 4;  //Esmeralda, Rubí, Plastico amarillo y Oro

    //LUCES
    luz0 = Luz(GL_LIGHT0,Tupla4f(0.0,0.0,0.0,0.0),Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,1.0,1.0,1.0),Tupla4f(1.0,0.0,0.0,0.0));
    luz1 = Luz(GL_LIGHT1,Tupla4f(0.0,0.0,0.0,1.0),Tupla4f(1.0,0.0,1.0,1.0),Tupla4f(1.0,0.0,1.0,1.0),Tupla4f(-30.0,0.0,0.0,1.0));

    //CAMARAS
    GLfloat ratio = float(Width)/float(Height);
    GLfloat wy = 0.84 * Front_plane;
    GLfloat wx = ratio * wy;
    //camara_ortogonal = Camara(Tupla3f(0.0,0.0,4.0), Tupla3f(0.0,0.0,0.0), Tupla3f(0.0,1.0,0.0), -10,10,-10,10,Front_plane,Back_plane,0);
    //camara_perspectiva = Camara(Tupla3f(0.0,0.0,4.0), Tupla3f(0.0,0.0,0.0), Tupla3f(0.0,1.0,0.0), -(((float)500/(float)500)*(0.84*Front_plane)),(((float)500/(float)500)*(0.84*Front_plane)),-(0.84*Front_plane),(0.84*Front_plane),Front_plane,Back_plane,1);
    camara_ortogonal = Camara(Tupla3f(0.0,0.0,5.0), Tupla3f(0.0,0.0,0.0), Tupla3f(0.0,1.0,0.0), -wx*20,wx*20,-wy*20,wy*20,Front_plane,Back_plane,0);
    camara_perspectiva = Camara(Tupla3f(0.0,0.0,5.0), Tupla3f(0.0,0.0,0.0), Tupla3f(0.0,1.0,0.0), -wx,wx,-wy,wy,Front_plane,Back_plane,1);
    camaras.push_back(camara_ortogonal);
    camaras.push_back(camara_perspectiva);
    camaraActiva=0;

    animacionesActivadas=false;
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer

  redimensionar(UI_window_width, UI_window_height);
}

// **************************************************************************
// Metodo que activa o desactiva las animaciones
// (llamada desde Escena::teclaPulsada)
// ***************************************************************************

void Escena::conmutarAnimaciones(){
  if(objeto_actual==7){
    animacionesActivadas=!animacionesActivadas;

    if(animacionesActivadas){
      objeto_jerarquico->inicioAnimaciones();
      glutIdleFunc( funcion_desocupado );
    }else{
      glutIdleFunc( nullptr );
    }
  }else
    std::cout << "No es el objeto jerarquico, no se pueden activar las animaciones." << std::endl;
}

// **************************************************************************
// Metodo que se llama con las animaciones activadas cada cierto tiempo
// ***************************************************************************

void Escena::mgeDesocupado(){
  objeto_jerarquico->actualizarEstado();
  glutPostRedisplay();
}

// **************************************************************************
// Funcion que dibuja el objeto activo actual, usando su método 'draw'
// (llamada desde Escena::dibujar)
// ***************************************************************************

void Escena::dibujar_objeto_actual()
{
   using namespace std ;

   // (1) configurar OpenGL para el modo actual (puntos/lineas/sólido)
   //    llamar glPolygonMode, glColor... (y alguna cosas más), según dicho modo
   // .........completar (práctica 1)

   if(modo_actual==4){
     if(luz_actual==0){
       luz1.desactivar();
       luz0.activar();
       if(!activaLuz0){
         cout << "Luz actual == " << luz_actual << " LUZ BLANCA EN EL INFINITO"<< endl ;
         activaLuz0=true;
         activaLuz1=activaLuz01=false;
       }
     }else if(luz_actual==1){
       luz0.desactivar();
       glPushMatrix();
         glRotatef(rotacion_luz,0.0,1.0,0.0);
         luz1.activar();
       glPopMatrix();
       //luz1.activar();
       if(!activaLuz1){
         cout << "Luz actual == " << luz_actual << " LUZ MAGENTA"<< endl ;
         activaLuz1=true;
         activaLuz0=activaLuz01=false;
       }
     }else if(luz_actual==2){
       luz0.activar();
       glPushMatrix();
         glRotatef(rotacion_luz,0.0,1.0,0.0);
         luz1.activar();
       glPopMatrix();
       //luz1.activar();
       if(!activaLuz01){
         cout << "Luz actual == " << luz_actual << " LUZ BLANCA EN EL INFINITO Y LUZ MAGENTA"<< endl ;
         activaLuz01=true;
         activaLuz0=activaLuz1=false;
       }
     }
   }

   switch( objeto_actual )
   {
      case 0:
         cubo->draw(modo_actual, dibujado_actual, suavizado_actual, material_actual) ;
         break ;
      case 1:
         tetraedro->draw(modo_actual, dibujado_actual, suavizado_actual, material_actual) ;
         break ;
      case 2:
         objeto_ply->draw(modo_actual, dibujado_actual, suavizado_actual, material_actual) ;
         break ;
      case 3:
         objeto_revolucion->draw(modo_actual, dibujado_actual, suavizado_actual, material_actual) ;
         break ;
      case 4:
         cilindro->draw(modo_actual, dibujado_actual, suavizado_actual, material_actual) ;
         break ;
      case 5:
         cono->draw(modo_actual, dibujado_actual, suavizado_actual, material_actual) ;
         break ;
      case 6:
         esfera->draw(modo_actual, dibujado_actual, suavizado_actual, material_actual) ;
         break ;
      case 7:
         objeto_jerarquico->draw(modo_actual, dibujado_actual, suavizado_actual, material_actual) ;
         break;
      case 8:
         cuadro->draw(modo_actual, dibujado_actual, suavizado_actual, material_actual) ;
         break;
      case 9:
         cubo_skybox->draw(modo_actual, dibujado_actual, suavizado_actual, material_actual) ;
         break;
      case 10:
         objeto_seleccion->draw();
         break;
      default:
         cout << "draw_object: el número de objeto actual (" << objeto_actual << ") es incorrecto." << endl ;
         break ;
   }
}

// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
  change_observer();
  ejes.draw();
  dibujar_objeto_actual();
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
   using namespace std ;
   cout << "Tecla pulsada: '" << tecla << "'" << endl;

   if(tecla=='z'){
     objeto_jerarquico->decrementaParamAct();
   }else{
     switch( toupper(tecla) )
     {
        case 'Q' :
           // salir
           return true ;
           break ;
        case 'O' :
           // activar siguiente objeto
           objeto_actual = (objeto_actual+1) % num_objetos ;

           //Si estamos en el objeto que tiene textura y cambiamos a otro y este no tiene
           //solo tiene 5 modos de dibujado en vez de 6 con textura asi que inicializo a 0
           if((objeto_actual!=9) && modo_actual==5)
            modo_actual=0;

           cout << "objeto actual == " << objeto_actual << endl ;
           break ;
        case 'M' :
          // activar el siguiente modo de representacion
          //Si el objeto tiene textura (objeto 8) solo puede usar 5 de los 6 modos
          if(objeto_actual==8 or objeto_actual==9)
            modo_actual = (modo_actual+1) % num_modos;
          else
            modo_actual = (modo_actual+1) % (num_modos-1);

          if(modo_actual==0)
            cout << "Modo actual == " << modo_actual << " MODO VERTICES " << endl ;
          else if(modo_actual==1)
            cout << "Modo actual == " << modo_actual << " MODO ARISTAS " << endl ;
          else if(modo_actual==2)
            cout << "Modo actual == " << modo_actual << " MODO SOLIDO " << endl ;
          else if(modo_actual==3)
            cout << "Modo actual == " << modo_actual << " MODO AJEDREZ " << endl ;
          else if(modo_actual==4)
            cout << "Modo actual == " << modo_actual << " MODO ILUMINACION " << endl ;
          else if(modo_actual==5)
            cout << "Modo actual == " << modo_actual << " MODO TEXTURA " << endl ;
          break ;
        case 'V' :
          // activar el siguiente modo de dibujado (0==modo inmediato y 1==modo diferido)
          dibujado_actual = (dibujado_actual+1) % num_dibujados;
          if(dibujado_actual==0)
            cout << "Modo dibujado == " << dibujado_actual << " Modo INMEDIATO"<< endl ;
          else
            cout << "Modo dibujado == " << dibujado_actual << " Modo DIFERIDO"<< endl ;
          break ;
        case 'P' :
          objeto_jerarquico->siguienteParametro();
          break ;
        case 'A' :
          conmutarAnimaciones();
          break;
        case 'Z' :
          objeto_jerarquico->incrementaParamAct();
          break;
        case '>' :
          objeto_jerarquico->acelerar();
          break;
        case '<' :
          objeto_jerarquico->decelerar();
          break;
        case 'L' :
          luz_actual = (luz_actual+1) % num_luces ;
          break ;
        case 'S':
          suavizado_actual = (suavizado_actual+1) % 2;
          if(suavizado_actual==0)
            cout << "Sombreado actual == " << suavizado_actual << " SOMBREADO GOURAUD"<< endl ;
          else
            cout << "Sombreado actual == " << suavizado_actual << " SOMBREADO PLANO"<< endl ;
          break;
        case 'N':
          material_actual = (material_actual+1) % num_materiales;
          if(material_actual==0)
            cout << "Material actual == " << material_actual << " MATERIAL ESMERALDA"<< endl ;
          else if(material_actual==1)
            cout << "Material actual == " << material_actual << " MATERIAL RUBÍ"<< endl ;
          else if(material_actual==2)
            cout << "Material actual == " << material_actual << " MATERIAL PLASTICO AMARILLO"<< endl ;
          else
            cout << "Material actual == " << material_actual << " MATERIAL ORO"<< endl ;
          break;
        case '1':
          valor_na-=0.5;
          rotacion_luz = 0.0 + 360.0*0.01*valor_na ;
          /*glPushMatrix();
            glRotatef(rotacion_luz,0.0,1.0,0.0);
            luz1.activar();
          glPopMatrix();*/
          //luz1.setPosicion(Tupla4f(-sin(angulo_luz*3.1617/180),0.0,cos(angulo_luz*3.1617/180),1.0));
          cout << "DISMINUYE ANGULO DE LA LUZ MAGENTA == " << rotacion_luz << endl;
          break;
        case '2':
          valor_na+=0.5;
          rotacion_luz = 0.0 + 360.0*0.01*valor_na ;
          /*glPushMatrix();
            glRotatef(rotacion_luz,0.0,1.0,0.0);
            luz1.activar();
          glPopMatrix();*/
          //luz1.setPosicion(Tupla4f(-sin(angulo_luz*3.1617/180),0.0,cos(angulo_luz*3.1617/180),1.0));
          cout << "AUMENTA ANGULO DE LA LUZ MAGENTA == " << rotacion_luz << endl;
          break;
        case 'R':
          Observer_angle_x=0.0;
          Observer_angle_y=0.0;
          cout << "CÁMARA REINICIADA A POSICIÓN INICIAL" << endl;
          break;
     }
   }
   return false ;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         zoom *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         zoom /= 1.2 ;
         break;
     case GLUT_KEY_F1:
         camaraActiva=0;
         Observer_angle_x=0.0;
         Observer_angle_y=0.0;
         //change_projection( float(Width)/float(Height) );
         cout << "CÁMARA ORTOGONAL ACTIVADA" << endl;
         break;
     case GLUT_KEY_F2:
         camaraActiva=1;
         Observer_angle_x=0.0;
         Observer_angle_y=0.0;
         //change_projection( float(Width)/float(Height) );
         cout << "CÁMARA PERSPECTIVA ACTIVADA" << endl;
         break;

	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   const float wy = 0.84*Front_plane, wx = ratio_xy*wy ;

   if(camaras[camaraActiva].tipoCamara()==0){
     camaras[camaraActiva].setProyeccion((-wx)*20*zoom,wx*20*zoom,(-wy)*20*zoom,(wy)*20*zoom,Front_plane,Back_plane);
   }else if(camaras[camaraActiva].tipoCamara()==1){
     camaras[camaraActiva].setProyeccion((-wx)*zoom,wx*zoom,(-wy)*zoom,wy*zoom,Front_plane,Back_plane);
   }

}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth;
   Height = newHeight;
   change_projection( float(Width)/float(Height) );
   glViewport( 0, 0, Width, Height );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   change_projection( float(Width)/float(Height) );
   camaras[camaraActiva].setObservador(Observer_angle_x, Observer_angle_y);
}

void Escena::moverCamara(int x, int y){
  Observer_angle_x += y;
  Observer_angle_y += x;
}

void Escena::zoomCamara(GLfloat zoom_positivo, GLfloat zoom_negativo){
  zoom *= zoom_positivo ;
  if(zoom>0.5)
    zoom /= zoom_negativo ;
}

void Escena::pick_color(int x, int y){
  GLint viewport[4];
  unsigned char pixel[3];

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar la pantalla
  objeto_seleccion->drawSeleccion();

  glGetIntegerv(GL_VIEWPORT, viewport);
  glReadPixels(x,viewport[3]-y,1,1,GL_RGB,GL_UNSIGNED_BYTE,(GLubyte *) &pixel[0]);
  //printf(" valor x %d, valor y %d, color %d, %d, %d \n",x,y,pixel[0],pixel[1],pixel[2]);
  objeto_seleccion->procesar_color(pixel);
  glutPostRedisplay();
}
