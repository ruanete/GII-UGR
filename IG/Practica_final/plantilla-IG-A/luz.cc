#include "luz.h"

Luz::Luz() {

}

Luz::Luz(GLenum nombre, Tupla4f ambiental, Tupla4f difuso, Tupla4f especular, Tupla4f posicion){
  this->nombre = nombre;
  this->ambiental = ambiental;
  this->difuso = difuso;
  this->especular = especular;
  this->posicion = posicion;
}

void Luz::activar() {
  glEnable(nombre);
  glLightfv(nombre,GL_AMBIENT,(GLfloat *) &ambiental);
  glLightfv(nombre,GL_DIFFUSE,(GLfloat *) &difuso);
  glLightfv(nombre,GL_SPECULAR,(GLfloat *) &especular);
  glLightfv(nombre,GL_POSITION,(GLfloat *) &posicion);
}

void Luz::desactivar() {
  glDisable(nombre);
}

void Luz::setNombre(const GLenum &n) {
  nombre = n;
}

void Luz::setPosicion(const Tupla4f &p) {
  posicion[0] = p[0];
  posicion[1] = p[1];
  posicion[2] = p[2];
  posicion[3] = p[3];
}

void Luz::setAmbiental(const Tupla4f &a) {
  ambiental = a;
}

void Luz::setDifuso(const Tupla4f &d) {
  difuso = d;
}

void Luz::setEspecular(const Tupla4f &e) {
  especular = e;
}

float Luz::getPosicion(int i){
  return posicion[i];
}
