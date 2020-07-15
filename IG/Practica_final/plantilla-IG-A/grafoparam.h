// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.h
// -- declaraciones de clase para el objeto jerárquico de la práctica 3
//
// #############################################################################

#ifndef GRAFOPARAM_H_INCLUDED
#define GRAFOPARAM_H_INCLUDED

#include "malla.h" // añadir .h de cualquier objetos malla indexada usados....

constexpr int num_parametros = 10 ; // número de parámetros o grados de libertad
                                   // de este modelo

typedef int ModoVis;

class GrafoParam
{
   public:

   // crea mallas indexadas (nodos terminales del grafo)
   GrafoParam();

   // función principal de visualización
   void draw( const ModoVis p_modo_vis, const bool p_usar_diferido, const int p_suavizado_actual, const int p_material_actual );

   // actualizar valor efectivo de un parámetro (a partir de su valor no acotado)
   void actualizarValorEfe( const unsigned iparam, const float valor_na );

   // devuelve el número de parámetros
   unsigned numParametros() { return num_parametros ; }

   private:

   // métodos de dibujo de subgrafos
   void cuerpo();
   void cabeza();
   void piernas(float rotacion_pierna1, float rotacion_pierna2, float rotacion_antepierna1, float rotacion_antepierna2);
   void brazos(float rotacion_brazo1, float rotacion_brazo2, float rotacion_antebrazo1, float rotacion_antebrazo2);

   // objetos tipo malla indexada (nodos terminales)

   Cono *     cono     = nullptr ;
   Esfera *   esfera   = nullptr ;
   Esfera *   tronco  = nullptr;
   Cubo *     cubo     = nullptr ;
   Cilindro * cilindro  = nullptr ;
   Cilindro * pierna  = nullptr ;
   Cilindro * brazo  = nullptr ;

   // parámetros de la llamada actual (o última) a 'draw'
   ModoVis modo_vis ;      // modo de visualización
   bool    usar_diferido ; // modo de envío (true -> diferido, false -> inmediato)
   int suavizado_actual;
   int material_actual;

   // valores efectivos de los parámetros (angulos, distancias, factores de
   // escala, etc.....) calculados a partir de los valores no acotados

   float brazo_rotacion1,
         brazo_rotacion2,
         rotacion_antebrazo1,
         rotacion_antebrazo2,
         cabeza_rotacion,
         pierna_rotacion1,
         pierna_rotacion2,
         rotacion_antepierna1,
         rotacion_antepierna2,
         rotacion_total;
} ;

#endif
