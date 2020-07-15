#include "objetoSeleccion.h"

ObjetoSeleccion::ObjetoSeleccion(){
  objeto = new Piramide();
  //objetoSeleccionado = {false, false, false, false, false};
  objetoSeleccionado.assign(objeto->getTriangulos(), false);
}

void ObjetoSeleccion::drawCaras(){
  glPushMatrix();
    glRotatef(45, 0.0, 1.0, 0.0);
    objeto->draw_solido(1,0,0,0,objetoSeleccionado);
  glPopMatrix();
}

void ObjetoSeleccion::draw(){
  glPushMatrix();
    glTranslatef(-0.35,0.0,0.35);
    glRotatef(45, 0.0, 1.0, 0.0);
    if (objetoSeleccionado[0])
       objeto->dibujaSolido(0,1,0);
    else
       objeto->dibujaSolido(1,0,0);
    objeto->draw_ModoInmediato(false);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.35,0.0,-0.35);
    glRotatef(45, 0.0, 1.0, 0.0);
    if (objetoSeleccionado[1])
       objeto->dibujaSolido(0,1,0);
    else
       objeto->dibujaSolido(1,0,0);
    objeto->draw_ModoInmediato(false);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.35,0.0,0.35);
    glRotatef(45, 0.0, 1.0, 0.0);
    if (objetoSeleccionado[2])
       objeto->dibujaSolido(0,1,0);
    else
       objeto->dibujaSolido(1,0,0);
    objeto->draw_ModoInmediato(false);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.35,0.0,-0.35);
    glRotatef(45, 0.0, 1.0, 0.0);
    if (objetoSeleccionado[3])
       objeto->dibujaSolido(0,1,0);
    else
       objeto->dibujaSolido(1,0,0);
    objeto->draw_ModoInmediato(false);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0,0.5,0.0);
    glRotatef(45, 0.0, 1.0, 0.0);
    if (objetoSeleccionado[4])
       objeto->dibujaSolido(0,1,0);
    else
       objeto->dibujaSolido(1,0,0);
    objeto->draw_ModoInmediato(false);
  glPopMatrix();
}

void ObjetoSeleccion::drawSeleccion(){
  glDisable(GL_DITHER);
  glPushMatrix();
    glTranslatef(-0.35,0.0,0.35);
    glRotatef(45, 0.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3ub(0,100,0);
    objeto->draw_ModoInmediato(false);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.35,0.0,-0.35);
    glRotatef(45, 0.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3ub(1,125,0);
    objeto->draw_ModoInmediato(false);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.35,0.0,0.35);
    glRotatef(45, 0.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3ub(2,150,0);
    objeto->draw_ModoInmediato(false);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.35,0.0,-0.35);
    glRotatef(45, 0.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3ub(3,175,0);
    objeto->draw_ModoInmediato(false);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.0,0.5,0.0);
    glRotatef(45, 0.0, 1.0, 0.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glColor3ub(4,200,0);
    objeto->draw_ModoInmediato(false);
  glPopMatrix();
  glEnable(GL_DITHER);
}

void ObjetoSeleccion::drawSeleccionCaras(){
  glPushMatrix();
    glRotatef(45, 0.0, 1.0, 0.0);
    objeto->draw_seleccion_color(0,100,0);
  glPopMatrix();
}

void ObjetoSeleccion::procesar_color(GLubyte * pixel){
  for (unsigned int i = 0; i < objetoSeleccionado.size(); i++)
    if (pixel[0] == i)
      objetoSeleccionado[i] = !objetoSeleccionado[i];
}
