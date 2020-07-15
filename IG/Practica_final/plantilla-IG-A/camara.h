#ifndef _CAMARA_H
#define _CAMARA_H

#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include "tuplasg.h"

#define CAMARA_ORTOGONAL  0
#define CAMARA_PERSPECTIVA  1

using namespace std;

class Camara{
  private:
    Tupla3f eye;
    Tupla3f center;
    Tupla3f up;

    int tipo; //TIPO: Ortogonal(0) o Perspectiva(1)

    float left, right, bottom, top, near, far;

    float radio;
  public:
    Camara();
    Camara(Tupla3f eye, Tupla3f at, Tupla3f up, float left, float right, float bottom, float top, float near, float far, int tipo);
    void setProyeccion();
    void setProyeccion(float left, float right, float bottom, float top, float near, float far);
    void setObservador();
    void setObservador(float angulo_x, float angulo_y);
    int tipoCamara();
    Tupla3f getEye();
};

#endif
