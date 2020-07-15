#include "aux.h"
#include "ply_reader.h"
#include "malla.h"

using namespace std;

// *****************************************************************************
//
// Clase ObjMallaIndexada
//
// *****************************************************************************

//Método para calcular caras pares e impares y las devuelve en un vector
std::vector<Tupla3i> ObjMallaIndexada::getTriangulosParImpar(bool modo){
   std::vector<Tupla3i> triangulos_paridad;

   unsigned int i;

   //Si modo es 0 es par si modo es 1 es impar
   if(modo)
    i=0;
   else
    i=1;

   for( ;i<triangulos.size(); i+=2){
      triangulos_paridad.push_back(triangulos.at(i));
   }

   return triangulos_paridad;
}

//Numero de vertices
int ObjMallaIndexada::getVertices(){
  return vertices.size();
}

//Numero de Triangulos
int ObjMallaIndexada::getTriangulos(){
  return triangulos.size();
}

//Crear VBOs
GLuint ObjMallaIndexada::CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram )
{
  GLuint id_vbo ; // resultado: identificador de VBO
  glGenBuffers( 1, & id_vbo ); // crear nuevo VBO, obtener identificador (nunca 0)
  glBindBuffer( tipo_vbo, id_vbo ); // activar el VBO usando su identificador
  // esta instrucción hace la transferencia de datos desde RAM hacia GPU
  glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
  glBindBuffer( tipo_vbo, 0 ); // desactivación del VBO (activar 0)
  return id_vbo ; // devolver el identificador resultado
}

// Visualización en modo inmediato con 'glDrawElements'

void ObjMallaIndexada::draw_ModoInmediato(bool iluminacionActiva)
{
  //Le dice a OpenGL especificandole un puntero a una tabla de vertices
  glEnableClientState( GL_VERTEX_ARRAY ); // habilitar ’vertex arrays’

  //Si la iluminación esta activa uso vector de normales y activo la iluminación
  if(iluminacionActiva){
    glEnableClientState( GL_NORMAL_ARRAY );
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glNormalPointer( GL_FLOAT, 0, normales_vertices.data() );
  }

  // especificar puntero a tabla de coords. de vértices (vertices.data() devuelve el puntero a la primera posicion del vector)
  glVertexPointer( 3, GL_FLOAT, 0, vertices.data() );
  // dibujar usando vértices indexados (tringulos.data() lo mismo que antes devuelve el puntero a la primera posicion del vector)
  glDrawElements( GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, triangulos.data() ) ;

  //Desactivo la iluminación y el vector de normales
  if(iluminacionActiva){
    glDisable(GL_LIGHTING);
    glDisable(GL_NORMALIZE);
    glDisableClientState( GL_NORMAL_ARRAY );
  }

  glDisableClientState( GL_VERTEX_ARRAY ); //desabilita el uso de las coordenadas de vertices
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void ObjMallaIndexada::draw_ModoDiferido(bool iluminacionActiva)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
   // completar (práctica 1)

   if(id_vbo_ver==0)
    id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, 3*vertices.size()*sizeof(float), vertices.data());

   if(id_vbo_tri==0)
    id_vbo_tri = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, 3*triangulos.size()*sizeof(int), triangulos.data());

   // especificar localización y formato de la tabla de vértices, habilitar tabla
   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver ); // activar VBO de vértices
   glVertexPointer( 3, GL_FLOAT, 0, 0 ); // especifica formato y offset (=0)
   glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de vértices.
   glEnableClientState( GL_VERTEX_ARRAY ); // habilitar tabla de vértices

   //Si la iluminación esta activa uso vector de normales y activo la iluminación
   if(iluminacionActiva){
     glEnableClientState( GL_NORMAL_ARRAY );
     glEnable(GL_LIGHTING);
     glEnable(GL_NORMALIZE);
     glNormalPointer( GL_FLOAT, 0, normales_vertices.data() );
   }

   // visualizar triángulos con glDrawElements (puntero a tabla == 0)
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri );// activar VBO de triángulos
   glDrawElements( GL_TRIANGLES, 3*triangulos.size(), GL_UNSIGNED_INT, 0 ) ;
   glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); // desactivar VBO de triángulos

   //Desactivo la iluminación y el vector de normales
   if(iluminacionActiva){
     glDisable(GL_LIGHTING);
     glDisable(GL_NORMALIZE);
     glDisableClientState( GL_NORMAL_ARRAY );
   }

   // desactivar uso de array de vértices
   glDisableClientState( GL_VERTEX_ARRAY );
}

//Metodo que pinta en modo ajedrez el modelo en modo inmediato
void ObjMallaIndexada::draw_ModoInmediatoAjedrez(){
  std::vector<Tupla3i> triangulos_par = getTriangulosParImpar(0);
  std::vector<Tupla3i> triangulos_impar = getTriangulosParImpar(1);

  glShadeModel(GL_FLAT);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, &vertices.at(0) );
  glColor3f( 1.0, 0.0, 0.0 );
  glDrawElements( GL_TRIANGLES, triangulos_impar.size()*3 , GL_UNSIGNED_INT, &(triangulos_impar.at(0)));

  glColor3f( 0.0, 1.0, 0.0 );
  glDrawElements( GL_TRIANGLES, triangulos_par.size()*3 , GL_UNSIGNED_INT, &(triangulos_par.at(0)));
}

void ObjMallaIndexada::draw_solido(float r, float g, float b, int modo, vector<bool> seleccion){
  if (modo==1)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  else
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  //glColor3f(r,g,b);
  //glLineWidth(3);

  glBegin(GL_TRIANGLES);
  for (int i=0;i<triangulos.size();i++){
    if(seleccion[i]==true){
      glColor3f(0,1,0);
    }else{
      glColor3f(1,0,0);
    }
    glVertex3f(vertices[triangulos[i][0]][0],vertices[triangulos[i][0]][1],vertices[triangulos[i][0]][2]);
    glVertex3f(vertices[triangulos[i][1]][0],vertices[triangulos[i][1]][1],vertices[triangulos[i][1]][2]);
    glVertex3f(vertices[triangulos[i][2]][0],vertices[triangulos[i][2]][1],vertices[triangulos[i][2]][2]);
  }
  glEnd();
}

void ObjMallaIndexada::draw_seleccion_color(float r, float g, float b){
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //glLineWidth(3);

  glBegin(GL_TRIANGLES);
  for (int i=0;i<triangulos.size();i++){
    glColor3ub(i,g,b);
    glVertex3f(vertices[triangulos[i][0]][0],vertices[triangulos[i][0]][1],vertices[triangulos[i][0]][2]);
    glVertex3f(vertices[triangulos[i][1]][0],vertices[triangulos[i][1]][1],vertices[triangulos[i][1]][2]);
    glVertex3f(vertices[triangulos[i][2]][0],vertices[triangulos[i][2]][1],vertices[triangulos[i][2]][2]);
  }
  glEnd();
}

//Modos de representacion (Vertices, Aristas, Solido y Ajedrez)
void ObjMallaIndexada::dibujaPuntos(float R, float G, float B, float pointSize){
  glShadeModel(GL_FLAT);
  glColor3f(R,G,B);
  glPointSize(pointSize);
  glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
}

void ObjMallaIndexada::dibujaAristas(float R, float G, float B){
  glShadeModel(GL_FLAT);
  glColor3f(R,G,B);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void ObjMallaIndexada::dibujaSolido(float R, float G, float B){
  glShadeModel(GL_FLAT);
  glColor3f(R,G,B);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
}

void ObjMallaIndexada::modoIluminacion(int suavizado_actual, int material_actual){
  if(suavizado_actual==0)
    glShadeModel(GL_SMOOTH);
  else
    glShadeModel(GL_FLAT);

  if(material_actual==0)
    esmeralda.activar();
  else if(material_actual==1)
    rubi.activar();
  else if(material_actual==2)
    plastico_amarillo.activar();
  else
    oro.activar();
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido

void ObjMallaIndexada::draw(const ModoVis p_modo_vis, const bool p_usar_diferido, const int p_suavizado_actual, const int p_material_actual)
{
   //glEnable(GL_CULL_FACE);
   if(!normalesCalculadas){
     calcular_normales();
     normalesCalculadas=true;
   }

   switch(p_modo_vis)
   {
      case 0:
        iluminacionActiva=false;
        dibujaPuntos(1.0,0.0,0.0,3.0);
        break ;
      case 1:
        dibujaAristas(1.0,0.0,0.0);
        break ;
      case 2:
        dibujaSolido(1.0,0.0,0.0);
        break ;
      case 3:
        draw_ModoInmediatoAjedrez();
        break ;
      case 4:
        iluminacionActiva=true;
        modoIluminacion(p_suavizado_actual, p_material_actual);
        break;
      case 5:
        iluminacionActiva=false;
        textura.activar();
        break;
      default:
        cout << "modo: el número de modo de dibujo actual (" << p_modo_vis << ") es incorrecto." << endl ;
      break ;
    }

    if(p_usar_diferido && p_modo_vis!=3 && p_modo_vis!=5)
      draw_ModoDiferido(iluminacionActiva);
    else if(!p_usar_diferido && p_modo_vis!=3 && p_modo_vis!=5)
      draw_ModoInmediato(iluminacionActiva);
}
// -----------------------------------------------------------------------------
// Recalcula la tabla de normales de vértices (el contenido anterior se pierde)
void ObjMallaIndexada::calcular_normales(){
  Tupla3f lado1, lado2, normal_cara;
  int posv0,posv1,posv2;
  Tupla3f inicial=Tupla3f(0.0,0.0,0.0);

  normales_vertices.assign(vertices.size(),inicial);

  for(int i=0;i<triangulos.size();i++){
    posv0 = triangulos[i][0];
    posv1 = triangulos[i][1];
    posv2 = triangulos[i][2];

    lado1=vertices[posv1]-vertices[posv0];
    lado2=vertices[posv2]-vertices[posv0];
    normal_cara = lado1.cross(lado2).normalized();
    normales_caras.push_back(normal_cara);
    normales_vertices[posv0] = (normales_vertices[posv0] + normal_cara);
    normales_vertices[posv1] = (normales_vertices[posv1] + normal_cara);
    normales_vertices[posv2] = (normales_vertices[posv2] + normal_cara);
  }

  /*for(int i=0;i<normales_vertices.size();i++){
    normales_vertices[i] = normales_vertices[i].normalized();
  }*/
}

// *****************************************************************************
//
// Clase Cubo (práctica 1)
//
// *****************************************************************************

Cubo::Cubo()
{

   // inicializar la tabla de vértices
   vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                  { -0.5, -0.5, +0.5 }, // 1
                  { -0.5, +0.5, -0.5 }, // 2
                  { -0.5, +0.5, +0.5 }, // 3
                  { +0.5, -0.5, -0.5 }, // 4
                  { +0.5, -0.5, +0.5 }, // 5
                  { +0.5, +0.5, -0.5 }, // 6
                  { +0.5, +0.5, +0.5 }  // 7
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                  { 1, 5, 3 }, { 3, 5, 7 },
                  { 1, 3, 0 }, { 0, 3, 2 },
                  { 5, 4, 7 }, { 7, 4, 6 },
                  { 1, 0, 5 }, { 5, 0, 4 },
                  { 3, 7, 2 }, { 2, 7, 6 }
                } ;
}

Cubo::Cubo(const char* archivo){
  vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                 { -0.5, -0.5, +0.5 }, // 1
                 { -0.5, +0.5, -0.5 }, // 2
                 { -0.5, +0.5, +0.5 }, // 3
                 { +0.5, -0.5, -0.5 }, // 4
                 { +0.5, -0.5, +0.5 }, // 5
                 { +0.5, +0.5, -0.5 }, // 6
                 { +0.5, +0.5, +0.5 }  // 7
              };

  triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                 { 1, 5, 3 }, { 3, 5, 7 },
                 { 1, 3, 0 }, { 0, 3, 2 },
                 { 5, 4, 7 }, { 7, 4, 6 },
                 { 1, 0, 5 }, { 5, 0, 4 },
                 { 3, 7, 2 }, { 2, 7, 6 }
               } ;

  verticesObjeto = { -0.5, +0.5, -0.5, // 2
                     +0.5, +0.5, -0.5, // 6
                     +0.5, -0.5, -0.5, // 4
                     -0.5, -0.5, -0.5, // 0

                     +0.5, +0.5, -0.5, // 6
                     +0.5, +0.5, +0.5, // 7
                     +0.5, -0.5, +0.5, // 5
                     +0.5, -0.5, -0.5, // 4

                     +0.5, +0.5, +0.5, // 7
                     -0.5, +0.5, +0.5, // 3
                     -0.5, -0.5, +0.5, // 1
                     +0.5, -0.5, +0.5, // 5

                     -0.5, +0.5, +0.5, // 3
                     -0.5, +0.5, -0.5, // 2
                     -0.5, -0.5, -0.5, // 0
                     -0.5, -0.5, +0.5, // 1

                     +0.5, -0.5, -0.5, // 4
                     +0.5, -0.5, +0.5, // 5
                     -0.5, -0.5, +0.5, // 1
                     -0.5, -0.5, -0.5, // 0

                     -0.5, +0.5, -0.5, // 2
                     -0.5, +0.5, +0.5, // 3
                     +0.5, +0.5, +0.5, // 7
                     +0.5, +0.5, -0.5, // 6
                    };

  verticesTextura = { 0.0,    (1.0/3), //2
                      0.25,   (1.0/3), //6
                      0.25, 2*(1.0/3), //4
                      0.0,  2*(1.0/3), //0

                      0.25,   (1.0/3), //6
                      0.5,    (1.0/3), //7
                      0.5,  2*(1.0/3), //5
                      0.25, 2*(1.0/3), //4

                      0.5,    (1.0/3), //7
                      0.75,   (1.0/3), //3
                      0.75, 2*(1.0/3), //1
                      0.5,  2*(1.0/3), //5

                      0.75,   (1.0/3), //3
                      1.0,    (1.0/3), //2
                      1.0,  2*(1.0/3), //0
                      0.75, 2*(1.0/3), //1

                      0.25, 2*(1.0/3), //4
                      0.5,  2*(1.0/3), //5
                      0.5,        1.0, //1
                      0.25,       1.0, //0

                      0.25,       0.0, //2
                      0.5,        0.0, //3
                      0.5,    (1.0/3), //7
                      0.25,   (1.0/3), //6
                    };

  textura = Textura(archivo, verticesObjeto, verticesTextura);
}

// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices
   vertices =  {  { 0, 0.5, 0 }, // 0
                  { 0.5, 0, -0.5 }, // 1
                  { 0, 0, 0.5 }, // 2
                  { -0.5, 0, -0.5 } // 3
               };

   // inicializar la tabla de caras o triángulos:
   // (es importante en cada cara ordenar los vértices en sentido contrario
   //  de las agujas del reloj, cuando esa cara se observa desde el exterior del cubo)

   triangulos = { { 1, 2, 3 }, { 1, 0, 2 },
                  { 2, 0, 3 }, { 3, 0, 1 }
                } ;
}

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read( nombre_archivo, vertices, triangulos );
}


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)
void ObjRevolucion::CrearMalla(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf){
  // completar ......(práctica 2)
  float x, y, z;
  Tupla3f vertice;
  Tupla3i triangulo;
  int a, b;
  bool tapa_superior=false, tapa_inferior=false;

  //Calculos todos los puntos rotados en función de los puntos que me dan, rotandolos en el eje Y
  for(int i=0;i<=num_instancias_perf-1;i++){
    for(int j=0;j<=perfil_original.size()-1;j++){
      x=perfil_original[j][0]*(cos(2*i*M_PI/num_instancias_perf)+perfil_original[j][2]*sin(2*i*M_PI/num_instancias_perf));
      y=perfil_original[j][1];
      z=perfil_original[j][0]*(-sin(2*i*M_PI/num_instancias_perf))+perfil_original[j][2]*(cos(2*i*M_PI/num_instancias_perf));
      vertice=Tupla3f(x,y,z);
      vertices.push_back(vertice);
    }
  }

  //Compruebo si el objeto tiene o no tapa inferior. Tiene tapa inferior cuando el primer punto
  //que hemos leido su valor de x no es 0. Si tiene tapa superior genero el vertice central de la tapa.
  if(perfil_original[0][0]!=0){
    x=0.0;
    y=perfil_original[0][1];
    z=0.0;

    vertice=Tupla3f(x,y,z);
    vertices.push_back(vertice);
    tapa_inferior=true;
  }

  //Compruebo si el objeto tiene o no tapa superior. Tiene tapa superior cuando el ultimo punto
  //que hemos leido su valor de x no es 0. Si tiene tapa superior genero el vertice central de la tapa.
  if(perfil_original[perfil_original.size()-2][0]!=0){
    x=0.0;
    y=perfil_original[perfil_original.size()-1][1];
    z=0.0;

    vertice=Tupla3f(x,y,z);
    vertices.push_back(vertice);
    tapa_superior=true;
  }

  //Genero los triangulos que forman la tapa inferior si es que tiene, para ello compruebo con la variable booleana
  //correspondiente a la tapa inferior
  if(tapa_inferior){
    for(int i=0;i<num_instancias_perf;i++){
      triangulo=Tupla3i(num_instancias_perf*perfil_original.size() , perfil_original.size()*((i+1)%num_instancias_perf) ,i*perfil_original.size() ) ;
      triangulos.push_back(triangulo);
    }
  }

  //Genero los triangulos del cuerpo del objeto
  for(int i=0;i<=num_instancias_perf-1;i++){
    for(int j=0;j<=perfil_original.size()-2;j++){
      a=perfil_original.size()*i+j;
      b=perfil_original.size()*((i+1)%num_instancias_perf)+j;
      triangulo=Tupla3i(a,b,b+1);
      triangulos.push_back(triangulo);
      triangulo=Tupla3i(a,b+1,a+1);
      triangulos.push_back(triangulo);
    }
  }

  //Genero los triangulos que forman la tapa superior si es que tiene, para ello compruebo con la variable booleana
  //correspondiente a la tapa superior
  if(tapa_superior){
    for(int i=0;i<num_instancias_perf;i++){
      triangulo=Tupla3i(num_instancias_perf*perfil_original.size()+1 ,perfil_original.size()*(i+1)-1, perfil_original.size()*((i+1)%num_instancias_perf)+perfil_original.size()-1 );
      triangulos.push_back(triangulo);
    }
  }
}

void ObjRevolucion::CrearMallaEspecial(const std::vector<Tupla3f> & perfil_original, const int num_instancias_perf, bool conoActivo){
  // completar ......(práctica 2)
  float x, y, z;
  Tupla3f vertice;
  Tupla3i triangulo;
  int a, b;
  bool tapa_superior=false, tapa_inferior=false;

  //Calculos todos los puntos rotados en función de los puntos que me dan, rotandolos en el eje Y
  for(int i=0;i<=num_instancias_perf-1;i++){
    for(int j=0;j<=perfil_original.size()-1;j++){
      x=perfil_original[j][0]*(cos(2*i*M_PI/num_instancias_perf)+perfil_original[j][2]*sin(2*i*M_PI/num_instancias_perf));
      y=perfil_original[j][1];
      z=perfil_original[j][0]*(-sin(2*i*M_PI/num_instancias_perf))+perfil_original[j][2]*(cos(2*i*M_PI/num_instancias_perf));
      vertice=Tupla3f(x,y,z);
      vertices.push_back(vertice);
    }
  }

  //Genero las tapas del cono o de la esfera dependiendo de que figura sea los puntos de sus tapas
  //será diferentes.
  if(!conoActivo){
    x=0.0;
    y=-1.0;
    z=0.0;

    vertice=Tupla3f(x,y,z);
    vertices.push_back(vertice);
    tapa_inferior=true;

    x=0.0;
    y=1.0;
    z=0.0;

    vertice=Tupla3f(x,y,z);
    vertices.push_back(vertice);
    tapa_superior=true;
  }else{
    x=0.0;
    y=perfil_original[0][1];
    z=0.0;

    vertice=Tupla3f(x,y,z);
    vertices.push_back(vertice);
    tapa_inferior=true;

    x=0.0;
    y=1.0;
    z=0.0;

    vertice=Tupla3f(x,y,z);
    vertices.push_back(vertice);
    tapa_superior=true;
  }

  //Genero los triangulos que forman la tapa inferior si es que tiene, para ello compruebo con la variable booleana
  //correspondiente a la tapa inferior
  if(tapa_inferior){
    for(int i=0;i<num_instancias_perf;i++){
      triangulo=Tupla3i(num_instancias_perf*perfil_original.size() , perfil_original.size()*((i+1)%num_instancias_perf) ,i*perfil_original.size() ) ;
      triangulos.push_back(triangulo);
    }
  }

  //Genero los triangulos del cuerpo del objeto
  for(int i=0;i<=num_instancias_perf-1;i++){
    for(int j=0;j<=perfil_original.size()-2;j++){
      a=perfil_original.size()*i+j;
      b=perfil_original.size()*((i+1)%num_instancias_perf)+j;
      triangulo=Tupla3i(a,b,b+1);
      triangulos.push_back(triangulo);
      triangulo=Tupla3i(a,b+1,a+1);
      triangulos.push_back(triangulo);
    }
  }

  //Genero los triangulos que forman la tapa superior si es que tiene, para ello compruebo con la variable booleana
  //correspondiente a la tapa superior
  if(tapa_superior){
    for(int i=0;i<num_instancias_perf;i++){
      triangulo=Tupla3i(num_instancias_perf*perfil_original.size()+1 ,perfil_original.size()*(i+1)-1, perfil_original.size()*((i+1)%num_instancias_perf)+perfil_original.size()-1 );
      triangulos.push_back(triangulo);
    }
  }
}

ObjRevolucion::ObjRevolucion(){
  ;
}

ObjRevolucion::ObjRevolucion( const std::string & nombre_ply_perfil)
{
  std::vector<Tupla3f> perfil_original;

  //Leo los vertices en una variable auxiliar del archivo PLY
  ply::read_vertices(nombre_ply_perfil, perfil_original);

  //Genero la malla de esos vertices
  CrearMalla(perfil_original,20);
}

Cilindro::Cilindro( const int num_vert_perfil, const int num_instancias_perf ){
  if(num_vert_perfil>=2){
    std::vector<Tupla3f> verticesAux;
    Tupla3f vertice;
    double aumento=1.0/(num_vert_perfil-1);
    double acumulador=0.0;

    vertice=Tupla3f(1.0,acumulador,0.0);
    verticesAux.push_back(vertice);
    for(int i=0;i<num_vert_perfil-1;i++){
      acumulador+=aumento;
      vertice=Tupla3f(1.0,acumulador,0.0);
      verticesAux.push_back(vertice);
    }

    CrearMalla(verticesAux,num_instancias_perf);
  }else{
    cout << "Para generar un cono tienes que usar 2 o mas vertices." << endl;
  }
}

Cono::Cono( const int num_vert_perfil, const int num_instancias_perf ){
  if(num_vert_perfil>=2){
    std::vector<Tupla3f> verticesAux;
    Tupla3f vertice;
    double aumento=1.0/(num_vert_perfil-1);
    double x=1.0, y=0.0;

    vertice=Tupla3f(x,y,0.0);
    verticesAux.push_back(vertice);
    for(int i=0;i<num_vert_perfil-2;i++){
      x-=aumento;
      y+=aumento;
      vertice=Tupla3f(x,y,0.0);
      verticesAux.push_back(vertice);
    }

    CrearMallaEspecial(verticesAux,num_instancias_perf, true);
  }else{
    cout << "Para generar un cono tienes que usar 2 o mas vertices." << endl;
  }
}

Esfera::Esfera( const int num_vert_perfil, const int num_instancias_perf ){
  if(num_vert_perfil>=3){
    float const R = 1./(float)(num_vert_perfil-1);
    std::vector<Tupla3f> verticesAux;
    Tupla3f vertice;

    for(int i = 1; i < num_vert_perfil-1; i++) {
      float const y = sin( -M_PI_2 + M_PI * i * R );
      float const x = cos(2*M_PI) * sin( M_PI * i * R );
      float const z = 0.0;
      vertice=Tupla3f(x,y,z);
      verticesAux.push_back(vertice);
    }
    /*float angulo = 180;
    float aumento=angulo/(num_vert_perfil-1);
    float radioFinal= 1.0;
    std::vector<Tupla3f> verticesAux;
    Tupla3f vertice;

    for(float i=0.0f;i<=angulo; i+=aumento) {
      float radio = M_PI*i/180;
      float x = 0.0+radioFinal*sin(radio);
      float y = 0.0+radioFinal*cos(radio);
      vertice=Tupla3f(x,y,0.0);
      verticesAux.push_back(vertice);
    }*/

    CrearMallaEspecial(verticesAux,num_instancias_perf, false);
  }else{
    cout << "Para generar una esfera tienes que usar 3 o mas vertices." << endl;
  }
}

//CLASE CUADRO//

Cuadro::Cuadro(const char* archivo){
  vertices =  {  { -1.0, 0.0, 0.0 }, // 0
                 { -1.0, 0.5, 0.0 }, // 1
                 { 1.0, 0.5, 0.0 }, // 2
                 { 1.0, 0.0, 0.0 } // 3
              };

  triangulos = { { 0, 1, 2 }, { 0, 2, 3 }
               } ;

  verticesObjeto = {-1.0, 0.0, 0.0,
                    -1.0, 0.5, 0.0,
                     1.0, 0.5, 0.0,
                     1.0, 0.0, 0.0};

  verticesTextura = {0.0, 1.0,
               			 0.0, 0.0,
               			 1.0, 0.0,
               			 1.0, 1.0};

  //CUBO TEXTURA
  /*vertices =  {  { -0.5, -0.5, -0.5 }, // 0
                 { -0.5, -0.5, +0.5 }, // 1
                 { -0.5, +0.5, -0.5 }, // 2
                 { -0.5, +0.5, +0.5 }, // 3
                 { +0.5, -0.5, -0.5 }, // 4
                 { +0.5, -0.5, +0.5 }, // 5
                 { +0.5, +0.5, -0.5 }, // 6
                 { +0.5, +0.5, +0.5 }  // 7
              };

  triangulos = { { 0, 2, 4 }, { 4, 2, 6 },
                 { 1, 5, 3 }, { 3, 5, 7 },
                 { 1, 3, 0 }, { 0, 3, 2 },
                 { 5, 4, 7 }, { 7, 4, 6 },
                 { 1, 0, 5 }, { 5, 0, 4 },
                 { 3, 7, 2 }, { 2, 7, 6 }
               } ;

  verticesObjeto = { -0.5, +0.5, -0.5, // 2
                     +0.5, +0.5, -0.5, // 6
                     +0.5, -0.5, -0.5, // 4
                     -0.5, -0.5, -0.5, // 0

                     +0.5, +0.5, -0.5, // 6
                     +0.5, +0.5, +0.5, // 7
                     +0.5, -0.5, +0.5, // 5
                     +0.5, -0.5, -0.5, // 4

                     +0.5, +0.5, +0.5, // 7
                     -0.5, +0.5, +0.5, // 3
                     -0.5, -0.5, +0.5, // 1
                     +0.5, -0.5, +0.5, // 5

                     -0.5, +0.5, +0.5, // 3
                     -0.5, +0.5, -0.5, // 2
                     -0.5, -0.5, -0.5, // 0
                     -0.5, -0.5, +0.5, // 1

                     +0.5, -0.5, -0.5, // 4
                     +0.5, -0.5, +0.5, // 5
                     -0.5, -0.5, +0.5, // 1
                     -0.5, -0.5, -0.5, // 0

                     -0.5, +0.5, -0.5, // 2
                     -0.5, +0.5, +0.5, // 3
                     +0.5, +0.5, +0.5, // 7
                     +0.5, +0.5, -0.5, // 6
                    };

  verticesTextura = { 0.0,    (1.0/3), //2
                      0.25,   (1.0/3), //6
                      0.25, 2*(1.0/3), //4
                      0.0,  2*(1.0/3), //0

                      0.25,   (1.0/3), //6
                      0.5,    (1.0/3), //7
                      0.5,  2*(1.0/3), //5
                      0.25, 2*(1.0/3), //4

                      0.5,    (1.0/3), //7
                      0.75,   (1.0/3), //3
                      0.75, 2*(1.0/3), //1
                      0.5,  2*(1.0/3), //5

                      0.75,   (1.0/3), //3
                      1.0,    (1.0/3), //2
                      1.0,  2*(1.0/3), //0
                      0.75, 2*(1.0/3), //1

                      0.25, 2*(1.0/3), //4
                      0.5,  2*(1.0/3), //5
                      0.5,        1.0, //1
                      0.25,       1.0, //0

                      0.25,       0.0, //2
                      0.5,        0.0, //3
                      0.5,    (1.0/3), //7
                      0.25,   (1.0/3), //6
                    };*/

  textura = Textura(archivo, verticesObjeto, verticesTextura);
}

// *****************************************************************************
//
// Clase Tetraedro (práctica 1)
//
// *****************************************************************************

Piramide::Piramide()
{

   vertices =  {  { -0.5, 0.0,  0.0 }, // 0
                  {  0.0, 0.0, -0.5 }, // 1
                  {  0.5, 0.0,  0.0 }, // 2
                  {  0.0, 0.0,  0.5 }, // 3
                  {  0.0, 0.5,  0.0 }, // 4
               };

   triangulos = { { 1, 0, 4 }, { 2, 1, 4 },
                  { 3, 2, 4 }, { 0, 3, 4 },
                  { 1, 3, 0 }, { 2, 3, 1 }
                } ;
}
