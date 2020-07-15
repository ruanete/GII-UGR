#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "FechaHistorica.h"
#include "VectorDinamico.h"

using namespace std;

FechaHistorica::FechaHistorica(){
  anio=0;
}

FechaHistorica::FechaHistorica(int a, VectorDinamico<string> h){
  assert(a>=0 && a<=9999);
  anio=a;
  hechos.resize(h.size());
  for(int i=0;i<h.size();i++)
    hechos[i]=h[i];
}

FechaHistorica::FechaHistorica(const FechaHistorica& fh){
  hechos.resize(fh.hechos.size());
  anio=fh.anio;
  for(int i=0;i<fh.hechos.size();i++)
    hechos[i]=fh.hechos[i];
}

FechaHistorica::~FechaHistorica(){
  anio=0;
  //hechos.~VectorDinamico();
}

int FechaHistorica::getAnio(){
  return anio;
}

string FechaHistorica::getHecho(int i){
  return hechos[i];
}

void FechaHistorica::setAnio(int a){
  anio=a;
}

void FechaHistorica::aniadirHechos(string& event){
  hechos.pushback(event);
}

bool FechaHistorica::buscarHechos(string s, FechaHistorica& matches){
  bool encontrado=false;
  for (int i=0; i < hechos.size(); ++i){
     if(hechos[i].find(s) != string::npos){
        matches.aniadirHechos(hechos[i]);
        encontrado = true;
     }
  }
  if (encontrado){
     matches.anio=anio;
   }
 return encontrado;
}

FechaHistorica& FechaHistorica::operator= (const FechaHistorica& original){
  if(this!=&original){
    anio=original.anio;
    hechos=original.hechos;
  }
  return *this;
}

ostream& operator<< (ostream& os, const FechaHistorica& e){
  os << e.anio;
  for(int i=0;i<e.hechos.size();++i)
    os << "#" << e.hechos[i];
  return os;
}

istream& operator>> (istream& is, FechaHistorica& e){
  string linea, linea_aux, year;

  getline(is,linea);

  year = linea;
  e.anio = atoi(year.erase(4).c_str());
  linea.erase(0,5);

  while((linea.find("#")) != string::npos){
    linea_aux = linea.substr(0,linea.find('#'));
    e.hechos.pushback(linea_aux);
    linea.erase(0,linea.find('#')+1);
  }

  e.hechos.pushback(linea);

  return is;
}
