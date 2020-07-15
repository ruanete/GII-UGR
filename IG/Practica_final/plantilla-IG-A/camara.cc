#include "camara.h"

Camara::Camara(){
  ;
}

Camara::Camara(Tupla3f eye, Tupla3f center, Tupla3f up, float left, float right, float bottom, float top, float near, float far, int tipo){
  this->eye = eye;
  this->center = center;
  this->up = up;
  this->left = left;
  this->right = right;
  this->bottom = bottom;
  this->top = top;
  this->near = near;
  this->far = far;
  this->tipo = tipo;

  radio=sqrt(pow(eye[0]-center[0],2)+pow(eye[1]-center[1],2)+pow(eye[2]-center[2],2));
}

void Camara::setProyeccion(){
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();

  if(tipo==CAMARA_ORTOGONAL){ //Camara Ortogonal
    glOrtho(left, right, bottom, top, near, far);
  }else if(tipo==CAMARA_PERSPECTIVA){  //Camara perspectiva
	  glFrustum(left, right, bottom, top, near, far);
  }

  glMatrixMode( GL_MODELVIEW );
}

void Camara::setProyeccion(float left, float right, float bottom, float top, float near, float far){
  this->left = left;
  this->right = right;
  this->bottom = bottom;
  this->top = top;

  setProyeccion();
}

void Camara::setObservador(){
  gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
}

void Camara::setObservador(float angulo_x, float angulo_y){
  float up_aux=1.0;

  int ang_x = angulo_x;
  int ang_y = angulo_y;
  ang_x %=360;
  ang_y %=360;

  float x = sin((angulo_y*M_PI)/180.0) * cos((angulo_x*M_PI)/180.0) * radio;
  float y = sin((angulo_x*M_PI)/180.0) * radio;
  float z = cos((angulo_y*M_PI)/180.0) * cos((angulo_x*M_PI)/180.0) * radio;

  if(ang_x<-90 && ang_x>=-270 or ang_x>90 && ang_x<=270){
    up_aux = -1.0;
  }else{
    up_aux = 1.0;
  }

  /*cout << "ANGULO X: " << ang_x << endl << "ANGULO Y: " << ang_y << endl;
  cout << "X: " << x << endl << "Y: " << sin((angulo_x*M_PI)/180.0) << endl << "Z: " << z << endl;
  cout << "UP: " << up_aux << endl;*/

  if(angulo_x==0.0 and angulo_y==0.0)
    gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);
  else
    gluLookAt(x, y, z, center[0], center[1], center[2], up[0], up_aux, up[2]);
}

int Camara::tipoCamara(){
  return tipo;
}

Tupla3f Camara::getEye(){
  return eye;
}
