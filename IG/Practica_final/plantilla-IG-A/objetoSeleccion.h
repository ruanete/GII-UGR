#include "malla.h"

class ObjetoSeleccion{
private:
  std::vector<bool> objetoSeleccionado;
  Piramide * objeto = nullptr;

public:
  ObjetoSeleccion();
  void draw();
  void drawCaras();
  void drawSeleccion();
  void drawSeleccionCaras();
  void procesar_color(GLubyte * pixel);
};
