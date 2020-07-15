/**
  * @file VectorDinamico.h
  * @brief Fichero cabecera del TDA Vector Dinamico
  *
  * Se crea un vector con capacidad de crecer y decrecer
  *
  */

#ifndef __VECTORDINAMICO_H
#define __VECTORDINAMICO_H

#include <iostream>
#include <string>

using namespace std;

/**
*  @brief T.D.A. VectorDinamico
*
*
* Una instancia @e v del tipo de datos abstracto @c Vector_Dinamico sobre el
* tipo @c T es un array 1-dimensional de un determinado tama�o @e n, que
* puede crecer y decrecer a petici�n del usuario. Lo podemos representar como
*
*  {v[0],v[1],...,v[n-1]}
*
* donde  v[i] es el valor almacenado en la posici�n  i del vector
*
* La eficiencia en espacio es @e O(n).
*
*
*/

template<class T>
class VectorDinamico {
  private:
    /**
       * @page repVectorDinamico Rep del TDA VectorDinamico
       *
       * @section invVectorDinamico Invariante de la representaci�n
       *
       * Un objeto v�lido @e v del TDA VectorDinamico debe cumplir
       * - @c v.nelementos>= 0
       * - @c v.datos apunta a una zona de memoria con capacidad para albergar
       *   @c nelementos valores de tipo @c T
       *
       * @section faVectorDinamico  Funci�n de abstracci�n
       *
       * Un objeto v�lido @e rep del TDA VectorDinamico representa al vector de
       * tama�o @e n
       *
       * {v.datos[0],v.datos[1],...,v.datos[v.nelementos-1]}
       *
    */
    T* datos;
    int nelementos;
  public:

    /**
     * @brief Constructor por defecto
     * @note
     *   Este constructor tambi�n corresponde al de por defecto
     */

    VectorDinamico();

    /**
     * @brief Constructor por parametros
     * @param n numero de espacio que queremos reservar
     */

    VectorDinamico(int n);

    /**
     * @brief Constructor de copia
     * @param original VectorDinamico de tipo T que queremos copiar al this
     */

    VectorDinamico(const VectorDinamico<T>& original);

    /**
      * @brief Destructor de la clase. Hace un delete del VectorDinamico
      */

    ~VectorDinamico();

    /**
      * @brief Devuelve el tamaño del VectorDinamico
      * @return Devuelve un entero con el tamaño del VectorDinamico
      */

    int size() const;

    /**
      * @brief Metodo para introducir un valor de tipo T al final del vector
      * @param elemento Valor de tipo T que queremos introducir en el vector
      */

    void pushback(T elemento);

    /**
     * @brief Acceso a un elemento
     * @param i la posici�n del vector donde est� el componente. 0<=i<size()
     * @return La referencia al elemento. Por tanto, se puede usar para almacenar
     *     un valor en esa posici�n.
     */

    T& operator[] (int i);

    /**
     * @brief Acceso a un elemento de un vector constante
     * @param i la posici�n del vector donde est� el componente. 0<=i<size()
     * @return La referencia al elemento. Se supone que el vector no se puede
        modificar y por tanto es acceso de s�lo lectura
     */

    const T& operator[] (int i) const;

    /**
     * @brief Redimensi�n del vector
     * @param n El nuevo tama�o del vector. n>=0
     * @post Los valores almacenados antes de la redimensi�n no se pierden
     *  (excepto los que se salen del nuevo rango de �ndices)
     */

    void resize (int n);

    /**
      * @brief Operador = para sustituir un VectorDinamico por otro
      * @param original VectorDinamico que vamos a sustituir por la VectorDinamico del this
      * @return this VectorDinamico inicial ya habiendo realizado la sustitución
      */

    VectorDinamico<T>& operator= (const VectorDinamico<T>& original);
};

#include "../src/VectorDinamico.cpp"
#endif
