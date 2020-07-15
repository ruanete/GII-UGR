#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <set>
#include <cctype>
//#include <cstdio>
#include <cstring>
#include "FechaHistorica.h"

using namespace std;

//FUNCION PARA PASAR UN STRING A MINUSCULAS
void to_lower(string &s){
  for(unsigned int i=0;i<s.length();i++)
    s[i] = tolower(s[i]);
}
//

FechaHistorica::FechaHistorica(){
  fechahistorica.first = 0;
}

FechaHistorica::FechaHistorica(int f, set<string> fh){
  assert(f>=0 && f<=9999);
  fechahistorica.first = f;
  fechahistorica.second = fh;
}

FechaHistorica::FechaHistorica(const FechaHistorica& fh){
  fechahistorica.first = fh.fechahistorica.first;
  fechahistorica.second = fh.fechahistorica.second;
}

FechaHistorica::~FechaHistorica(){
  ;
}

int FechaHistorica::getAnio(){
  return fechahistorica.first;
}

string FechaHistorica::getHecho(int i){
  //assert(i>=0 && i<=fechahistorica.second.size());

  int contador=0;
  set<string>::iterator it;
  it=fechahistorica.second.begin();

  while(contador!=i){
    it++;
    contador++;
  }

  return *it;
}

set<string> FechaHistorica::getHechos() const{
  return fechahistorica.second;
}

void FechaHistorica::addHechos(set<string> hechos){
  FechaHistorica::iterator it;
  for(it=hechos.begin();it!=hechos.end();it++){
    fechahistorica.second.insert(*it);
  }
}

void FechaHistorica::setAnio(int a){
  fechahistorica.first = a;
}

void FechaHistorica::aniadirHechos(string& hecho){
  fechahistorica.second.insert(hecho);
}

bool FechaHistorica::buscarHechos(string s, FechaHistorica& matches){
  bool encontrado=false;
  set<string>::iterator it;
  string s1_minusculas, s2_minusculas;
  s1_minusculas=s;
  to_lower(s1_minusculas);

  for(it=fechahistorica.second.begin();it!=fechahistorica.second.end();it++){
    s2_minusculas = *it;
    to_lower(s2_minusculas);
    if(strstr(s2_minusculas.c_str(),s1_minusculas.c_str())!=NULL){
      encontrado = true;
      matches.fechahistorica.first = fechahistorica.first;
      matches.fechahistorica.second.insert(*it);
    }
  }

  return encontrado;
}

int FechaHistorica::numeroEventos(){
  FechaHistorica::iterator it;
  int numEventos=0;
  for(it=fechahistorica.second.begin();it!=fechahistorica.second.end();it++){
    numEventos++;
  }

  return numEventos;
}

FechaHistorica& FechaHistorica::operator= (const FechaHistorica& original){
  if(this!=&original){
    fechahistorica.first = original.fechahistorica.first;
    fechahistorica.second = original.fechahistorica.second;
  }
  return *this;
}

ostream& operator<< (ostream& os, const FechaHistorica& e){
  os << e.fechahistorica.first;
  for(set<string>::iterator it=e.fechahistorica.second.begin();it!=e.fechahistorica.second.end();it++)
    os << "#" << *it << endl;

  return os;
}

istream& operator>> (istream& is, FechaHistorica& e){
  string linea, linea_aux, year;
  int i=0;

  getline(is,linea);

  year = linea;
  e.fechahistorica.first = atoi(year.erase(4).c_str());
  linea.erase(0,5);

  while((linea.find("#")) != string::npos){
    linea_aux = linea.substr(0,linea.find('#'));
    e.fechahistorica.second.insert(linea_aux);
    linea.erase(0,linea.find('#')+1);
    i++;
  }

  e.fechahistorica.second.insert(linea);

  /*cout << endl << endl << "FECHA: " << e.fechahistorica.first << endl;
  cout << "FECHA HISTORICA: " << endl;
  for(set<string>::iterator it=e.fechahistorica.second.begin();it!=e.fechahistorica.second.end();it++)
    cout << "#" << *it;*/

  return is;
}
