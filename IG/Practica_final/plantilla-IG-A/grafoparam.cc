// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: GrafoParam.cc
// -- implementación del objeto jerárquico de la práctica 3
//
// #############################################################################


#include "grafoparam.h"

// -----------------------------------------------------------------------------
// constructor: crea mallas indexadas en los nodos terminales del grafo

GrafoParam::GrafoParam()
{
   cono     = new Cono(4,16);
   esfera     = new Esfera(20,20);
   cubo     = new Cubo();
   cilindro = new Cilindro( 4, 16 );
   pierna = new Cilindro( 4, 16 );
   brazo = new Cilindro( 4, 16 );
   tronco = new Esfera(5,16);
}
// -----------------------------------------------------------------------------
// actualizar valor efectivo de un parámetro (a partir de su valor no acotado)

void GrafoParam::actualizarValorEfe( const unsigned iparam, const float valor_na )
{
   assert( iparam < num_parametros );

   using namespace std ;
   //cout << "GrafoParam::actualizarValorEfe( " << iparam << ", " << valor_na << " )" << endl ;

   constexpr float vp = 2.5 ;

   switch( iparam )
   {
      case 0:
         cabeza_rotacion = 10*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 1:
         brazo_rotacion1 = 45*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 2:
         rotacion_antebrazo1 = 45*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 3:
         brazo_rotacion2 = 45*sin( 0.5*(2.0*M_PI*valor_na));
         break ;
      case 4:
         rotacion_antebrazo2 = 45*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 5:
         pierna_rotacion1 = 45*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 6:
         rotacion_antepierna1 = 25*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 7:
         pierna_rotacion2 = 45*sin( 0.5*(2.0*M_PI*valor_na));
         break ;
      case 8:
         rotacion_antepierna2 = 25*sin( 0.5*(2.0*M_PI*valor_na) );
         break ;
      case 9:
         rotacion_total = 0.0 + 360.0*0.05*valor_na ;
         break ;
   }
}

// -----------------------------------------------------------------------------
// visualización del objeto Jerárquico con OpenGL,
// mediante llamadas a los métodos 'draw' de los sub-objetos

void GrafoParam::draw(const ModoVis p_modo_vis, const bool p_usar_diferido, const int p_suavizado_actual, const int p_material_actual)
{
   // asegurarnos que está inicializado ok

   assert( cilindro != nullptr );
   assert( cono != nullptr );
   assert( esfera != nullptr );
   assert( pierna != nullptr );
   assert( brazo != nullptr );
   assert( tronco != nullptr );

   // guardar parametros de visualización para esta llamada a 'draw'
   // (modo de visualización, modo de envío)

   modo_vis      = p_modo_vis ;
   usar_diferido = p_usar_diferido ;
   suavizado_actual = p_suavizado_actual;
   material_actual = p_material_actual;

   // dibujar objetos
   glPushMatrix();
    glRotatef(rotacion_total, 0.0, 1.0, 0.0);
    glTranslatef(2.0, 2.75, 0.0);

    glPushMatrix();
      glTranslatef(0,-0.75,0);
      glRotatef(cabeza_rotacion,0,0,1);
      glScalef(0.9,0.9,0.9);
      cabeza();
    glPopMatrix();
    glPushMatrix();
      cuerpo();
      piernas(pierna_rotacion1, pierna_rotacion2, rotacion_antepierna1, rotacion_antepierna2);
      brazos(brazo_rotacion1, brazo_rotacion2, rotacion_antebrazo1, rotacion_antebrazo2);
    glPopMatrix();
   glPopMatrix();
}

void GrafoParam::cuerpo(){
  glPushMatrix();
    glTranslatef(0.0,-1.25,0.0);
    glScalef(0.55,0.7,0.4 );
    tronco->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
  glPopMatrix();
}

void GrafoParam::cabeza(){
  glPushMatrix();
    glTranslatef(0,0.75,0);
    glPushMatrix();
      glTranslatef( 0.0, 0.25, 0.0 );
      glScalef(0.75,0.75,0.75 );
      cono->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
    glPushMatrix();
      glScalef(0.5,0.5,0.5 );
      esfera->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
  glPopMatrix();
  glPushMatrix();
    glTranslatef(0.0,0.0,0.0);
    glScalef(0.25,0.5,0.25);
    cilindro->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
  glPopMatrix();
}

void GrafoParam::piernas(float rotacion_pierna1, float rotacion_pierna2, float rotacion_antepierna1, float rotacion_antepierna2){
  glPushMatrix();
    glTranslatef(-0.2,-1.75,0.0);
    glRotatef(180+rotacion_pierna1,1,0,0);
    glPushMatrix();
      glTranslatef(0.0,0.0,0.0);
      glScalef(0.1,0.5,0.1);
      pierna->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.0,0.5,0.0);
      glScalef(0.1,0.1,0.1);
      esfera->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.0,0.5,0.0);
      glRotatef(rotacion_antepierna1,1,0,0);
      glTranslatef(0.0,0.0,0.0);
      glScalef(0.1,0.5,0.1);
      pierna->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.2,-1.75,0.0);
    glRotatef(180+rotacion_pierna2,1,0,0);
    glPushMatrix();
      glTranslatef(0.0,0.0,0.0);
      glScalef(0.1,0.5,0.1);
      pierna->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.0,0.5,0.0);
      glScalef(0.1,0.1,0.1);
      esfera->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.0,0.5,0.0);
      glRotatef(rotacion_antepierna2,1,0,0);
      glTranslatef(0.0,0.0,0.0);
      glScalef(0.1,0.5,0.1);
      pierna->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
  glPopMatrix();
}

void GrafoParam::brazos(float rotacion_brazo1, float rotacion_brazo2, float rotacion_antebrazo1, float rotacion_antebrazo2){
  glPushMatrix();
    glTranslatef(-0.35,-1.0,0);
    glRotatef(90+rotacion_brazo1,0,0,1);
    glPushMatrix();
      glTranslatef(0.0,0.0,0.0);
      glScalef(0.1,0.5,0.1);
      brazo->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.0,0.5,0.0);
      glScalef(0.1,0.1,0.1);
      esfera->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
    glPushMatrix();
      glTranslatef(0.0,0.5,0.0);
      glRotatef(rotacion_antebrazo1,0,0,1);
      glTranslatef(0.0,0.0,0.0);
      glScalef(0.1,0.5,0.1);
      brazo->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.35,-1.0,0.0);
    glRotatef(270+rotacion_brazo2,0,0,1);
    glTranslatef(-1.0,0.0,0.0);
    glPushMatrix();
      glTranslatef(1.0,0.0,0.0);
      glScalef(0.1,0.5,0.1);
      brazo->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
    glPushMatrix();
      glTranslatef(1.0,0.5,0.0);
      glScalef(0.1,0.1,0.1);
      esfera->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
    glPushMatrix();
      glTranslatef(1.0,0.5,0.0);
      glRotatef(rotacion_antebrazo2,0,0,1);
      glTranslatef(0.0,0.0,0.0);
      glScalef(0.1,0.5,0.1);
      brazo->draw(modo_vis, usar_diferido, suavizado_actual, material_actual) ;
    glPopMatrix();
  glPopMatrix();
}
