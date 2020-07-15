#include "material.h"

Material::Material(){

}

Material::Material(Tupla4f ambiental, Tupla4f difusa, Tupla4f especular, GLfloat brillo){
  this->ambiental = ambiental;
  this->difusa = difusa;
  this->especular = especular;
  this->brillo = brillo;
}

void Material::setBrillo(const GLfloat &b) {
  brillo = b;
}

void Material::setAmbiental(const Tupla4f &a) {
  ambiental = a;
}

void Material::setDifusa(const Tupla4f &d) {
  difusa = d;
}

void Material::setEspecular(const Tupla4f &e) {
  especular = e;
}

void Material::activar() {
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,(GLfloat *) &ambiental);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,(GLfloat *) &difusa);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &especular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);
}
