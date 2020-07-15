// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: ObjMallaIndexada.h
// -- declaraciones de clase ObjMallaIndexada (mallas indexadas) y derivados
//
// #############################################################################

#ifndef OBJETOS_H_INCLUDED
#define OBJETOS_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"
#include <string>

typedef int ModoVis;

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class ObjMallaIndexada
{
   public:

   //Método para sacar triangulos pares e impares
   std::vector<Tupla3i> getTriangulosParImpar(bool modo);

   //Numero de vertices
   int getVertices();

   //Numero de triangulos
   int getTriangulos();

   // crear VBOs
   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato(bool iluminacionActiva);

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido(bool iluminacionActiva);

   // dibuja el objeto en modo diferido y en modo ajedrez
   void draw_ModoInmediatoAjedrez();

   //PRUEBA
   void draw_solido(float r, float g, float b, int modo, vector<bool> seleccion);
   void draw_seleccion_color(float r, float g, float b);
   //PRUEBA

   void dibujaPuntos(float R, float G, float B, float pointSize);

   void dibujaAristas(float R, float G, float B);

   void dibujaSolido(float R, float G, float B);

   void modoIluminacion(int suavizado_actual, int material_actual);

   void activarTextura();

   // función que redibuja el objeto
   // está función llama a 'draw_MI' (modo inmediato)
   // o bien a 'draw_MD' (modo diferido, VBOs)
   void draw(const ModoVis p_modo_vis, const bool p_usar_diferido, const int p_suavizado_actual, const int p_material_actual) ;

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> vertices ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> triangulos ; // una terna de 3 enteros por cada cara o triángulo

   //Normales (ambiental difusa especular)
   std::vector<Tupla3f> normales_caras ;
   std::vector<Tupla3f> normales_vertices ;
   bool normalesCalculadas=false;
   //Esmeralda
   Material esmeralda = Material(Tupla4f(0.0215, 0.1745, 0.0215, 1.0),Tupla4f(0.07568, 0.61424, 0.07568, 1.0),Tupla4f(0.633, 0.727811, 0.633, 1.0),128*0.6);
   //Rubí
   Material rubi = Material(Tupla4f(0.1745, 0.01175, 0.01175, 1.0),Tupla4f(0.61424, 0.04136, 0.04136, 1.0),Tupla4f(0.727811, 0.626959, 0.626959, 1.0),128*0.6);
   //Plastico amarillo
   Material plastico_amarillo = Material(Tupla4f(0.05, 0.05, 0.0, 1.0),Tupla4f(0.5, 0.5, 0.4, 1.0),Tupla4f(0.7, 0.7, 0.04, 1.0),128*0.078125);
   //Oro
   Material oro = Material(Tupla4f(0.24725, 0.1995, 0.0745, 1.0),Tupla4f(0.75164, 0.60648, 0.22648, 1.0),Tupla4f(0.628281, 0.555802, 0.366065, 1.0),128*0.4);
   bool iluminacionActiva=false;
   //TEXTURA
   Textura textura;

   GLuint id_vbo_ver=0, id_vbo_tri=0;

} ;

// *****************************************************************************
//
// clases derivadas de ObjMallaIndexada (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad
// (tiene 9 vertices y 6 caras)

class Cubo : public ObjMallaIndexada
{
   private:
     vector<GLfloat> verticesObjeto;
     vector<GLfloat> verticesTextura;
   public:
     Cubo() ;
     Cubo(const char* archivo) ;
} ;

// *****************************************************************************
// Tetraedro con centro en el origen y lado unidad
// (tiene 4 vertices y 4 caras)

class Tetraedro : public ObjMallaIndexada
{
   public:
     Tetraedro() ;
} ;

// *****************************************************************************
// objeto leído de un archivo PLY

class ObjPLY : public ObjMallaIndexada
{
   public:
      ObjPLY( const std::string & nombre_archivo );
} ;

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

class ObjRevolucion : public ObjMallaIndexada
{
   public:
      ObjRevolucion();
      ObjRevolucion( const std::string & nombre_ply_perfil);
   protected:
      void CrearMalla(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf);
      void CrearMallaEspecial(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, bool conoActivo);
} ;

// *****************************************************************************
// Cilindro

class Cilindro : public ObjRevolucion
{
  public:
    Cilindro( const int num_vert_perfil, const int num_instancias_perf );
} ;

// *****************************************************************************
// Cono

class Cono : public ObjRevolucion
{
  public:
    Cono( const int num_vert_perfil, const int num_instancias_perf );
} ;

// *****************************************************************************
// Esfera

class Esfera : public ObjRevolucion
{
  public:
    Esfera( const int num_vert_perfil, const int num_instancias_perf );
} ;


// *****************************************************************************
// Cuadro (uso de texturas)
// (tiene 4 vertices y 2 caras)

class Cuadro : public ObjMallaIndexada
{
  private:
    vector<GLfloat> verticesObjeto;
    vector<GLfloat> verticesTextura;
  public:
    Cuadro(const char* archivo);
} ;

// *****************************************************************************
// Piramide con centro en el origen y lado unidad
// (tiene 5 vertices y 5 caras)

class Piramide : public ObjMallaIndexada
{
   public:
     Piramide() ;
} ;

#endif
