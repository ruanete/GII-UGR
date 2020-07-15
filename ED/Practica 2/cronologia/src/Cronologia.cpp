#include <iostream>
#include <sstream>
#include <cstring>
#include "Cronologia.h"
#include "VectorDinamico.h"

using namespace std;

void Cronologia::ordenar(){
   for (int i=cronologia.size()-1; i>0; --i)
    for (int j=0; j<i; ++j)
       if (cronologia[j].getAnio() > cronologia[j+1].getAnio()) {
          FechaHistorica aux;
          aux = cronologia[j];
          cronologia[j] = cronologia[j+1];
          cronologia[j+1]= aux;
       }
}

Cronologia::Cronologia(){
;
}

Cronologia::Cronologia(VectorDinamico<FechaHistorica> c){
  cronologia.resize(c.size());
  for(int i=0;i<cronologia.size();i++)
    cronologia[i]=c[i];
}

Cronologia::Cronologia(const Cronologia& c){
  cronologia.resize(c.size());
  for(int i=0;i<c.size();i++)
    cronologia[i]=c.cronologia[i];
}

Cronologia::~Cronologia(){
  //cronologia.~VectorDinamico();
}

int Cronologia::size() const{
  return cronologia.size();
}

void Cronologia::aniadirEvento(FechaHistorica& f){
  cronologia.pushback(f);
  ordenar();
}

int Cronologia::buscarAnio(int f){
  int i=0;
  bool valido=false;

  while(i<cronologia.size() && !valido){
     if(cronologia[i].getAnio()==f)
        valido = true;
     else
        ++i;
  }
  if(!valido)
     i=-1;
  return i;
}

Cronologia Cronologia::buscarEventos(string s){
  Cronologia nuevo;
  for (int i=0; i < cronologia.size(); ++i){
     FechaHistorica aux;
     if(cronologia[i].buscarHechos(s,aux)){
        nuevo.aniadirEvento(aux);
     }
  }
  nuevo.ordenar();
  return nuevo;
}

Cronologia Cronologia::eventosPalabra(string palabra){
  Cronologia nuevo;
  nuevo = buscarEventos(palabra);
  if(nuevo.cronologia.size() == 0)
    cout << endl << "No hay ningún evento con esa palabra." << endl;

  return nuevo;
}

Cronologia Cronologia::eventosFechas(int inicio,int final){
  int pos_ini,pos_fin;
  Cronologia nuevo;
  pos_ini = buscarAnio(inicio);
  pos_fin = buscarAnio(final);

  if(pos_ini == -1 or pos_fin == -1){
    cout << endl << "Fecha no valida. " << endl;
  }else{
    for(int i = pos_ini;i <= pos_fin;i++)
    nuevo.cronologia.pushback(cronologia[i]);
  }
  return nuevo;
}

Cronologia Cronologia::eventosAnio(int fecha){
  int pos;
  Cronologia nuevo;
  pos = buscarAnio(fecha);

  if(pos == -1){
    cout << endl << "No existe ningún evento para esa fecha. " << endl;
  }else{
    nuevo.cronologia.pushback(cronologia[pos]);
  }

  return nuevo;
}


FechaHistorica Cronologia::getHecho(int i){
  return cronologia[i];
}

Cronologia& Cronologia::operator= (const Cronologia& original){
  if(this!=&original){
    cronologia=original.cronologia;
  }
  return *this;
}

Cronologia Cronologia::operator+ (const Cronologia& original){
  Cronologia final;
  int tamanio,tamanio1;
  tamanio = cronologia.size();
  tamanio1 = original.cronologia.size();
  for(int i = 0;i < tamanio;i++){
    final.cronologia.pushback(cronologia[i]);
  }

  for(int j = 0;j < tamanio1 ;j++){
    final.cronologia.pushback(original.cronologia[j]);
  }
  final.ordenar();

  return final;
}

ostream& operator<< (ostream& os, const Cronologia& c){
  for(int i=0;i<c.size();++i)
    os << c.cronologia[i] << endl;

  return os;
}

istream& operator>> (istream& is, Cronologia& c){
  string linea;

  while(!is.eof()){
    getline(is,linea,'\n');

    if((strcmp(linea.c_str(),""))!=0){
      FechaHistorica fecha;
      stringstream ss(linea);
      ss >> fecha;
      c.cronologia.pushback(fecha);
    }
  }

  return is;
}
