#ifndef _INC_TEXTURA_H
#define _INC_TEXTURA_H

#include <GL/glut.h>
#include "tuplasg.h"
#include "CImg.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace cimg_library;

class Textura{
  private:
    GLuint textura_id;
    vector<GLfloat> verticesObjeto;
    vector<GLfloat> verticesTextura;
    vector<unsigned char> data;
    CImg<unsigned char> imagen;
  public:
    Textura();
    Textura(const char* archivo, const vector<GLfloat> v, const vector<GLfloat> t);
    void activar();
};

#endif /* _INC_TEXTURA_H */
