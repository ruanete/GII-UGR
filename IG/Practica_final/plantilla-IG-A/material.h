#ifndef _INC_MATERIAL_H
#define _INC_MATERIAL_H
#include <GL/glut.h>
#include "tuplasg.h"

class Material{
  private:
    Tupla4f ambiental;
    Tupla4f difusa;
    Tupla4f especular;
    GLfloat brillo;

  public:
    Material();
    Material(Tupla4f ambiental, Tupla4f difusa, Tupla4f especular, GLfloat brillo);
    void activar();
    void setAmbiental(const Tupla4f &a);
    void setDifusa(const Tupla4f &d);
    void setEspecular(const Tupla4f &e);
    void setBrillo(const GLfloat &b);
};

#endif
