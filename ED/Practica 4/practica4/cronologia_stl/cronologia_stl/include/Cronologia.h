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
#include <map>
#include "FechaHistorica.h"

using namespace std;

/**
  *  @brief T.D.A. Cronologia
  *
  * Una instancia @e c del tipo de datos abstracto @c Cronologia es un objeto
  * con un campo, map con clave entera que hace referencia al año y de objetos de FechaHistorica
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
    map<int,FechaHistorica> cronologia;

    typedef typename map<int,FechaHistorica>::iterator iterator;
    typedef typename map<int,FechaHistorica>::const_iterator const_iterator;

    void ordenar();
  public:
    //Iteradores//
    class Iterator {
      private:
        iterator it;
      public:
        friend class Cronologia;

        Iterator(){
          ;
        }

        Iterator(const Iterator & i){
          it = i.it;
        }

        Iterator& operator++(){
          ++it;
          return *this;
        }

        Iterator operator++(int){
          Iterator temp;
          temp.it = it;
          ++it;
          return temp;
        }

        Iterator& operator--(){
          --it;
          return *this;
        }

        Iterator operator--(int){
          Iterator temp;
          temp.it = it;
          --it;
          return temp;
        }

        const FechaHistorica& operator * () const{
          return it->second;
        }

        bool operator ==(const Iterator &i){
          return i.it==it;
        }

        bool operator !=(const Iterator &i){
          return i.it!=it;
        }

        Iterator& operator= (iterator& original){
          it = original;
          return *this;
        }
    };

    Iterator begin(){
      Iterator i;
      i.it = cronologia.begin();
      return i;
    }

    Iterator end(){
      Iterator i;
      i.it = cronologia.end();
      return i;
    }

    class Const_Iterator {
      private:
        const_iterator it;
      public:
        friend class Cronologia;

        Const_Iterator(){
          ;
        }

        Const_Iterator(const Const_Iterator & i){
          it = i.it;
        }

        Const_Iterator& operator++(){
          ++it;
          return *this;
        }

        Const_Iterator operator++(int){
          Const_Iterator temp;
          temp.it = it;
          ++it;
          return temp;
        }

        Const_Iterator& operator--(){
          --it;
          return *this;
        }

        Const_Iterator operator--(int){
          Const_Iterator temp;
          temp.it = it;
          --it;
          return temp;
        }

        const FechaHistorica& operator * () const{
          return it->second;
        }

        bool operator ==(const Const_Iterator &i){
          return i.it==it;
        }

        bool operator !=(const Const_Iterator &i){
          return i.it!=it;
        }

        Const_Iterator& operator= (const_iterator& original){
          it = original;
          return *this;
        }
    };

    Const_Iterator begin() const{
      Const_Iterator i;
      i.it = cronologia.begin();
      return i;
    }

    Const_Iterator end() const{
      Const_Iterator i;
      i.it = cronologia.end();
      return i;
    }
    //Fin iteradores//

    /**
      * @brief Constructor por defecto de la clase. Lo creamos sencillamente para evitar
      * errores o asignaciones de basura a objetos de nuestra clase. Crea una Cronologia
      * por defecto.
      */

    Cronologia();

    /**
      * @brief Constructor por parametros de la clase
      * @param f entero con el año
      * @param fh objeto de la clase FechaHistorica
      * @return Crea la cronologia con FechaHistorica fh asociada a un año f
      */

    Cronologia(int f, FechaHistorica fh);

    /**
      * @brief Constructor de copias de la clase
      * @param c objeto de la clase que se quiere copiar
      * @return Crea el evento con los datos de c
      */

    Cronologia(const Cronologia& c);

    /**
      * @brief Destructor de la clase.
      */

    ~Cronologia();

    /**
      * @brief Devuelve el tamaño del map de Cronologia
      * @return Devuelve un entero con el tamaño del Map
      */

    int size() const;

    /**
      * @brief Añade un FechaHistorica en la Cronología
      * @param f la nueva FechaHistorica
      * @return no devuelve nada
      */

    void aniadirEvento(FechaHistorica& f);

    /**
      * @brief Busca los eventos que contengan el string s
      * @param s string de la palabra a buscar
      * @return devuelve una Cronologia con las FechaHistoricas que contengan el string s
      */

    Cronologia buscarEventos(string s);

    /**
    * @brief cronologia entre dos fechas
    * @param inicio fecha inicial
    * @param final fecha final
    * @return Devuelve una Cronología
    */

    Cronologia eventosFechas(int inicio,int final);

    /**
    * @brief devuelve todos los eventos de un año
    * @param anio año a buscar
    * @return Devuelve una Cronología
    */

    FechaHistorica GetEventos(int anio);

    /**
      * @brief Método que devuelve el FechaHistorica que hay en la posición i del vector
      * @param i con la posición de cronologia
      * @return FechaHistorica de esa posición
      */

    FechaHistorica getHecho(int i);

    /**
      * @brief Método que devuelve el numero total de eventos de una cronologia
      * @return int numero total de eventos
      */

    int totalEventos();

    /**
      * @brief Método que devuelve un pair con el año y el valor de eventos maximo de toda la cronologia
      * @return pair<int,int> con el año y eventos maximos
      */

    pair<int,int> eventosMax();

    /**
      * @brief Método que devuelve el numero total de años que hay en una cronologia
      * @return int con el numero total de años
      */

    int numeroAnios();

    /**
      * @brief Método que devuelve la union de dos cronologias
      * @param c1 cronologia 1
      * @param c2 cronologia 2
      * @return Cronologia union de c1 y c2
      */

    void Union(const Cronologia& c1, const Cronologia& c2);

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
