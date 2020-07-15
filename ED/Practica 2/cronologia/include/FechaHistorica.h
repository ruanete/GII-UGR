/**
  * @file FechaHistorica.h
  * @brief Fichero cabecera del TDA FechaHistorica
  *
  */

#ifndef _FECHAHISTORICA_H_
#define _FECHAHISTORICA_H_

/**
  *  @brief T.D.A. FechaHistorica
  *
  * Una instancia @e c del tipo de datos abstracto @c FechaHistorica es un objeto
  * con dos campos, un entero y un vector del tipo abstracto VectorDinamico de string
  * El entero es la fecha base del conjunto de eventos
  *
  * Año#FechaHistorica_1#...#...#FechaHistorica_N
  *
  * Un ejemplo de su uso:
  * @include pruebacronologia.cpp
  *
  * @author Raúl Ruano Narváez
  * @author Manuel Vallejo Felipe
  * @date
  */

#include <iostream>
#include <cassert>
#include <string>
#include "VectorDinamico.h"

using namespace std;

class FechaHistorica {
  private:
    /**
      * @page repConjunto Rep del TDA FechaHistorica
      *
      * @section invConjunto Invariante de la representación
      *
      * El invariante es \e rep.anio > 0 && rep.anio < 9999
      *
      * Fijamos como limite que los años no sean ni negativos ni superiores a 9999.
      *
      * @section faConjunto Función de abstracción
      *
      * Un objeto válido @e rep del TDA FechaHistorica representa al valor
      *
      * Año#FechaHistorica_1#...#...#FechaHistorica_N
      *
      *
      */

    int anio;
    VectorDinamico<string> hechos;
  public:

    /**
      * @brief Constructor por defecto de la clase. Lo creamos sencillamente para evitar
      * errores o asignaciones de basura a objetos de nuestra clase. Crea una Fecha Historica
      * por defecto con año 0 y con el vector nulo
      */

    FechaHistorica();

    /**
      * @brief Constructor de la clase
      * @param a año del evento a construir
      * @param h VectorDinamico de string con el evento o eventos de ese año
      * @return Crea el evento con año a y los eventos asociados
      * @pre a debe ser mayor o igual que 0 y menos o igual que 9999
      */

    FechaHistorica(int a, VectorDinamico<string> h);

    /**
      * @brief Constructor de copias de la clase
      * @param fh objeto de la clase que se quiere copiar
      * @return Crea el evento con los datos de fh
      */

    FechaHistorica(const FechaHistorica& fh);

    /**
      * @brief Destructor de la clase. Hace un delete del VectorDinamico de string
      */

    ~FechaHistorica();

    /**
      * @brief Método de acceso al año de la FechaHistorica
      * @return int con el valor del campo anio
      */

    int getAnio();

    /**
      * @brief Método que devuelve el hecho que hay en la posición i del vector
      * @param i con la posición del vector que queremos devolver
      * @return string con el hecho en esa posición
      */

    string getHecho(int i);

    /**
      * @brief Método para cambiar el valor de anio
      * @param a con el valor del anio
      */

    void setAnio(int a);

    /**
      * @brief Añade un hecho
      * @param event string con hecho a añadir
      */

    void aniadirHechos(string& event);

    /**
      * @brief Búsqueda de hechos en una FechaHistorica dada una palabra clave s
      * @param s string con la palabra a buscar
      * @param matches nueva FechaHistorica donde se introducen únicamente los eventos de this que contienen el string s
      * @return Devuelve true o false indicando si hay o no algún match de la cadena clave s en los eventos de this
      */

    bool buscarHechos(string s, FechaHistorica& matches);

    /**
      * @brief Operador = para sustituir una FechaHistorica por otra
      * @param original FechaHistorica que vamos a sustituir por la FechaHistorica del this
      * @return this FechaHistorica inicial ya habiendo realizado la sustitución
      */

    FechaHistorica& operator= (const FechaHistorica& original);

    /**
      * @brief Salida de un FechaHistorica a ostream
      * @param os stream de salida
      * @param e FechaHistorica a escribir
      * @post Se muestra la FechaHistorica en formato "año#evento1#evento2#...#eventoN"
      */

    friend ostream& operator<< (ostream& os, const FechaHistorica& e);

    /**
      * @brief Entrada de un FechaHistorica desde istream
      * @param is stream de entrada
      * @param e FechaHistorica que recibe el valor
      * @retval El FechaHistorica leído en e
      * @pre La entrada tiene el formato "año#evento1#evento2#...#eventoN
      */

    friend istream& operator>> (istream& is, FechaHistorica& e);
};

#endif
