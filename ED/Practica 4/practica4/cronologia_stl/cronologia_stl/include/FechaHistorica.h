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
#include <set>

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

    pair< int,set<string> > fechahistorica;

    typedef typename set<string>::iterator iterator;
    typedef typename set<string>::const_iterator const_iterator;

  public:
    //Iteradores//
    class Iterator {
      private:
        iterator it;
      public:
        friend class FechaHistorica;

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

        const string &operator * () const{
          return *it;
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
      i.it = fechahistorica.second.begin();
      return i;
    }

    Iterator end(){
      Iterator i;
      i.it = fechahistorica.second.end();
      return i;
    }

    class Const_Iterator {
      private:
        const_iterator it;
      public:
        friend class FechaHistorica;

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

        const string &operator * () const{
          return *it;
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
      i.it = fechahistorica.second.begin();
      return i;
    }

    Const_Iterator end() const{
      Const_Iterator i;
      i.it = fechahistorica.second.end();
      return i;
    }
    //Fin iteradores//

    /**
      * @brief Constructor por defecto de la clase. Lo creamos sencillamente para evitar
      * errores o asignaciones de basura a objetos de nuestra clase. Crea una Fecha Historica
      * por defecto con año 0.
      */

    FechaHistorica();

    /**
      * @brief Constructor de la clase
      * @param f año del evento a construir
      * @param fh Set de string con el evento o eventos de ese año
      * @return Crea el evento con año a y los eventos asociados
      * @pre a debe ser mayor o igual que 0 y menos o igual que 9999
      */

    FechaHistorica(int f, set<string> fh);

    /**
      * @brief Constructor de copias de la clase
      * @param fh objeto de la clase que se quiere copiar
      * @return Crea el evento con los datos de fh
      */

    FechaHistorica(const FechaHistorica& fh);

    /**
      * @brief Destructor de la clase.
      */

    ~FechaHistorica();

    /**
      * @brief Método de acceso al año de la FechaHistorica
      * @return int con el valor del campo anio
      */

    int getAnio();

    /**
      * @brief Método que devuelve el hecho que hay en la posición i del Set
      * @param i con la posición del Set que queremos devolver
      * @return string con el hecho en esa posición
      */

    string getHecho(int i);

    /**
      * @brief Método que devuelve un set<string> con todos los hechos
      * @return set<string> con el hechos
      */

    set<string> getHechos() const;

    /**
      * @brief Método que añade al final de un FechaHistorica todos los eventos del set<string> que se le pasa
      * @param hechos con el set<string> de todos los hechos
      */

    void addHechos(set<string> hechos);

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
      * @brief Devuelve el numero de eventos que tiene un FechaHistorica
      * @return Devuelve un entero con el numero de eventos del FechaHistorica
      */

    int numeroEventos();

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
