#include "textura.h"

using namespace std;

Textura::Textura(){
  ;
}

Textura::Textura(const char* archivo, const vector<GLfloat> v, const vector<GLfloat> t){
  verticesObjeto = v;
  verticesTextura = t;

  imagen.load(archivo);

  // empaquetamos bien los datos
  for (long y = 0; y < imagen.height(); y ++){
    for (long x = 0; x < imagen.width(); x ++){
      unsigned char *r = imagen.data(x, y, 0, 0);
      unsigned char *g = imagen.data(x, y, 0, 1);
      unsigned char *b = imagen.data(x, y, 0, 2);
      data.push_back(*r);
      data.push_back(*g);
      data.push_back(*b);
    }
  }
  glGenTextures(1, &textura_id);
}

void Textura::activar(){
  glColor3f(1.0,1.0,1.0);
  glBindTexture(GL_TEXTURE_2D, textura_id);

  glActiveTexture(GL_TEXTURE0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  // TRASFIERE LOS DATOS A GPU
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen.width(), imagen.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);

  glEnable(GL_TEXTURE_2D);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textura_id);

  glVertexPointer(3, GL_FLOAT, 0, verticesObjeto.data());
  glTexCoordPointer(2, GL_FLOAT, 0, verticesTextura.data());

  glDrawArrays(GL_QUADS, 0, (verticesObjeto.size()/3));

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glDeleteTextures(1, &textura_id);
}
