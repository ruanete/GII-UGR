#ifndef _INC_LUZ_H
#define _INC_LUZ_H

#include <GL/glut.h>
#include "tuplasg.h"

class Luz {
  private:
    GLenum nombre;
    Tupla4f ambiental;
    Tupla4f difuso;
    Tupla4f especular;
    Tupla4f posicion;
  public:
    Luz();
    Luz(GLenum nombre, Tupla4f ambiental, Tupla4f difuso, Tupla4f especular, Tupla4f posicion);
    void activar();
    void desactivar();
    void setNombre(const GLenum &n);
    void setAmbiental(const Tupla4f &a);
    void setDifuso(const Tupla4f &d);
    void setEspecular(const Tupla4f &e);
    void setPosicion(const Tupla4f &p);
    float getPosicion(int i);
};

#endif
