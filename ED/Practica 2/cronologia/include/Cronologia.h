/**
  * @file Cronologia.h
  * @brief Fichero cabecera del TDA Cronologia
  *
  */

#ifndef _CRONOLOGIA_H_
#define _CRONOLOGIA_H_

#include <iostream>
#include <cassert>
#include <string>
#include "VectorDinamico.h"
#include "FechaHistorica.h"

using namespace std;

/**
  *  @brief T.D.A. Cronologia
  *
  * Una instancia @e c del tipo de datos abstracto @c Cronologia es un objeto
  * con un campo, VectorDinamico de objetos de FechaHistorica
  *
  * Año#FechaHistorica_1#...#...#FechaHistorica_N
  * Año#FechaHistorica_1#...#...#FechaHistorica_N
  * ...
  * Año#FechaHistorica_1#...#...#FechaHistorica_N
  *
  * Un ejemplo de su uso:
  * @include pruebacronologia.cpp
  *
  * @author Raúl Ruano Narváez
  * @author Manuel Vallejo Felipe
  * @date
  */


class Cronologia {
  private:
    /**
      * @page repConjunto Rep del TDA Cronologia
      *
      * @section invConjunto Invariante de la representación
      *
      * El invariante está ligado al de los FechaHistorica \e rep.anio < 0 && rep.anio > 9999
      * que ya hemos fijado anteriormente
      *
      * @section faConjunto Función de abstracción
      *
      * Un objeto válido @e rep del TDA Cronologia representa al valor
      *
      * Año#FechaHistorica_1#...#...#FechaHistorica_N
      * Año#FechaHistorica_1#...#...#FechaHistorica_N
      * ...
      * Año#FechaHistorica_1#...#...#FechaHistorica_N
      *
      */

    VectorDinamico<FechaHistorica> cronologia;

    void ordenar();
  public:

    /**
      * @brief Constructor por defecto de la clase. Lo creamos sencillamente para evitar
      * errores o asignaciones de basura a objetos de nuestra clase. Crea una Cronologia
      * por defecto con el VectorDinamico nulo
      */

    Cronologia();

    /**
      * @brief Constructor de la clase
      * @param c vector de FechaHistorica
      * @return Crea la cronologia con FechaHistorica c asociada
      */

    Cronologia(VectorDinamico<FechaHistorica> c);

    /**
      * @brief Constructor de copias de la clase
      * @param c objeto de la clase que se quiere copiar
      * @return Crea el evento con los datos de c
      */

    Cronologia(const Cronologia& c);

    /**
      * @brief Destructor de la clase. Hace un delete del vector de FechaHistorica
      */

    ~Cronologia();

    /**
      * @brief Devuelve el tamaño del VectorDinamico de Cronologia
      * @return Devuelve un entero con el tamaño del VectorDinamico
      */

    int size() const;

    /**
      * @brief Añade un FechaHistorica en la Cronología
      * @param f la nueva FechaHistorica
      * @return no devuelve nada
      */

    void aniadirEvento(FechaHistorica& f);

    /**
      * @brief Busca una FechaHistorica dada su fecha
      * @param f la fecha del evento a buscar
      * @return Devuelve el indice donde se encuentra el año y si falla -1
      */

    int buscarAnio(int f);

    /**
    * @brief buscador de eventos dado una palabra clave
    * @param s vector de string con la palabra a buscar
    * @return Devuelve una Cronología
    */

    Cronologia buscarEventos(string s);

    /**
    * @brief buscador de eventos dado una palabra clave
    * @param palabra palabra para buscar
    * @return Devuelve una Cronología
    */

    Cronologia eventosPalabra(string palabra);

    /**
    * @brief cronologia entre dos fechas
    * @param inicio fecha inicial
    * @param final fecha final
    * @return Devuelve una Cronología
    */

    Cronologia eventosFechas(int inicio,int final);

    /**
    * @brief buscador de eventos en un año
    * @param fecha entero con la fecha a buscar
    * @return Devuelve una Cronología
    */

    Cronologia eventosAnio(int fecha);

    /**
      * @brief Método que devuelve el FechaHistorica que hay en la posición i del vector
      * @param i con la posición del vector que queremos devolver
      * @return FechaHistorica de esa posición
      */

    FechaHistorica getHecho(int i);

    /**
      * @brief Operador = para sustituir una Cronologia por otra
      * @param original Cronologia que vamos a sustituir por la Cronologia del this
      * @return this Cronologia inicial ya habiendo realizado la sustitución
      */

    Cronologia& operator= (const Cronologia& original);

    /**
      * @brief Concatena dos Cronologias
      * @param original Cronologia a cocatenar
      * @post Se obtiene una Cronologia en la que se concatenan this y original
      */

    Cronologia operator+ (const Cronologia& original);

    /**
      * @brief Salida de una Cronologia a ostream
      * @param os stream de salida
      * @param original Cronologia a escribir
      * @post Se obtienen varios años seguidos de la cadena de FechaHistorica con el formato
      * de FechaHistorica
      */

    friend ostream& operator<< (ostream& os, const Cronologia& e);

    /**
      * @brief Entrada de una Cronologia desde istream
      * @param is stream de entrada
      * @param e Cronologia que recibe el valor
      * @retval La Cronologia leída en c
      * @pre La entrada tiene el formato de FechaHistorica
      */

    friend istream& operator>> (istream& is, Cronologia& e);
};

#endif
