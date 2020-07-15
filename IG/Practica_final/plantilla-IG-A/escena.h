#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "jerarquico.h"
#include "luz.h"
#include "camara.h"
#include "objetoSeleccion.h"

#define CAMARA_ORTOGONAL  0
#define CAMARA_PERSPECTIVA  1

class Escena
{

   private:

   Ejes ejes;

   // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;
   GLfloat zoom;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

  void clear_window();
	void dibujar_objeto_actual();

   // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();

   int objeto_actual = 0 , // objeto actual (el que se visualiza)
       num_objetos   = 0 ; // número de objetos (actualizado al crear los objetos en el constructor)

   int modo_actual = 0 , // modo actual (el que se visualiza)
       num_modos   = 0 ; // número de modos (actualizado al crear los objetos en el constructor)

   int dibujado_actual = 0 ,
       num_dibujados = 0;

   int luz_actual = 0 ,
       num_luces = 0;

   int suavizado_actual=0;

   int material_actual = 0 ,
       num_materiales = 0;

   float valor_na = 0.0;
   float rotacion_luz = 0.0;

   // Objetos de la escena
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr ;
   ObjPLY * objeto_ply = nullptr ;
   ObjRevolucion * objeto_revolucion = nullptr;
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;
   ObjJerarquico * objeto_jerarquico = nullptr;
   Cuadro * cuadro = nullptr;
   Cubo * cubo_skybox = nullptr;
   Piramide * piramide = nullptr;
   ObjetoSeleccion * objeto_seleccion = nullptr;

   //Variable activar o desactivar Animaciones
   bool animacionesActivadas;

   //LUCES
   Luz luz0;
   Luz luz1;
   bool activaLuz0=false, activaLuz1=false, activaLuz01=false;

   //RATÓN
   int estadoRaton;

   //CAMARAS
   Camara camara_ortogonal;
   Camara camara_perspectiva;
   vector<Camara> camaras;
   int camaraActiva;

   public:

   Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

  void conmutarAnimaciones();

  void dibujaPiramides(bool bufferTrasero);
  void draw_objects();
  void draw_objects_seleccion();
  void procesar_color(unsigned char color[3]);

  void mgeDesocupado();
  //CAMARA
  void moverCamara(int x, int y);
  void zoomCamara(GLfloat zoom_positivo, GLfloat zoom_negativo);
  void pick_color(int x, int y);
};
#endif
