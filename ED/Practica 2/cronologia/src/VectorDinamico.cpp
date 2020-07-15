#include <cassert>
#include <iostream>

template<class T>
VectorDinamico<T>::VectorDinamico(){
  nelementos=0;
  datos=NULL;
}

template<class T>
VectorDinamico<T>::VectorDinamico(int n){
  assert(n>=0);
  if (n>0)
    datos= new T[n];
  nelementos=n;
}

template<class T>
VectorDinamico<T>::VectorDinamico(const VectorDinamico<T>& original){
  nelementos=original.nelementos;
  if(nelementos>0){
    datos=new T[nelementos];
    for(int i=0;i<nelementos;i++)
      datos[i]=original.datos[i];
  }else
    datos=0;
}

template<class T>
VectorDinamico<T>::~VectorDinamico(){
  nelementos=0;
  delete [] datos;
}

template<class T>
int VectorDinamico<T>::size() const{
  return nelementos;
}

template<class T>
void VectorDinamico<T>::pushback(T elemento){
  if(nelementos==0){
    nelementos=1;
    datos=new T[nelementos];
    datos[0]=elemento;
  }else{
    T* datosaux = new T[nelementos+1];
    for(int i=0;i<nelementos;i++)
      datosaux[i]=datos[i];
    datosaux[nelementos]=elemento;
    delete[]datos;
    datos=datosaux;
    nelementos=nelementos+1;
  }
}

template<class T>
T& VectorDinamico<T>::operator[] (int i){
  assert (0<=i && i<nelementos);
  return datos[i];
}

template<class T>
const T& VectorDinamico<T>::operator[] (int i) const{
  assert (0<=i && i<nelementos);
  return datos[i];
}

template<class T>
void VectorDinamico<T>::resize (int n){
  assert (n>=0);
  if (n!=nelementos) {
    if (n!=0) {
      T * nuevos_datos;
      nuevos_datos= new T[n];
      if (nelementos>0) {
	       int minimo;
	        minimo= nelementos<n?nelementos:n;
	        for (int i= 0; i<minimo;++i)
	         nuevos_datos[i]= datos[i];
	        delete[] datos;
      }
      nelementos= n;
      datos= nuevos_datos;
    }
    else {
      if (nelementos>0)
	     delete[] datos;
      datos= 0;
      nelementos= 0;
    }
  }
}

template<class T>
VectorDinamico<T>& VectorDinamico<T>::operator= (const VectorDinamico<T>& original){
  if(this!=&original){
    if(nelementos>0)
      delete[]datos;
    nelementos=original.nelementos;
    datos=new T[nelementos];
    for(int i=0;i<nelementos;++i)
      datos[i]=original.datos[i];
  }
  return *this;
}
