#include <iostream>
#include <sstream>
#include <cstring>
#include <map>
#include "Cronologia.h"

using namespace std;

Cronologia::Cronologia(){
  ;
}

Cronologia::Cronologia(int f, FechaHistorica fh){
  pair<int,FechaHistorica> c;
  c.first = f;
  c.second = fh;
  cronologia.insert(c);
}

Cronologia::Cronologia(const Cronologia& c){
  cronologia = c.cronologia;
}

Cronologia::~Cronologia(){
  ;
}

int Cronologia::size() const{
  return cronologia.size();
}

void Cronologia::aniadirEvento(FechaHistorica& f){
  pair<int,FechaHistorica> c;
  c.first = f.getAnio();
  c.second = f;
  cronologia.insert(c);
  //ordenar();
}

Cronologia Cronologia::buscarEventos(string s){
  Cronologia nuevo;
  map<int,FechaHistorica>::iterator it;

  for(it=cronologia.begin();it!=cronologia.end();it++){
    FechaHistorica aux;
    if(it->second.buscarHechos(s,aux))
      nuevo.aniadirEvento(aux);
  }
  return nuevo;
}

Cronologia Cronologia::eventosFechas(int inicio, int final){
  Cronologia nueva;
  Cronologia::iterator it;
  pair<int,FechaHistorica> valor;

  it = cronologia.find(final);

  for(it=cronologia.find(inicio);it!=cronologia.find(final+1);it++){
    valor.first = it->first;
    valor.second = it->second;
    nueva.cronologia.insert(valor);
  }
  return nueva;
}

FechaHistorica Cronologia::GetEventos(int anio){
  FechaHistorica fecha;
  iterator it = cronologia.find(anio);
  fecha = it->second;
  return fecha;
}

FechaHistorica Cronologia::getHecho(int i){
  return cronologia[i];
}

int Cronologia::totalEventos(){
  Cronologia::iterator it;
  int totalEventos=0;
  for(it=cronologia.begin();it!=cronologia.end();it++){
    totalEventos+=it->second.numeroEventos();
  }
  return totalEventos;
}

pair<int,int> Cronologia::eventosMax(){
  Cronologia::iterator it;
  pair<int,int> maximo;
  int max=0, numEventos=0;
  for(it=cronologia.begin();it!=cronologia.end();it++){
    numEventos=it->second.numeroEventos();
    if(numEventos>max){
      max=numEventos;
      maximo.first=it->first;
      maximo.second=max;
    }
  }
  return maximo;
}

int Cronologia::numeroAnios(){
  Cronologia::iterator it;
  int numAnios=0;
  for(it=cronologia.begin();it!=cronologia.end();it++){
    numAnios++;
  }

  return numAnios;
}

void Cronologia::Union(const Cronologia& c1, const Cronologia& c2){
  Cronologia::const_iterator it;
  set<string> insertar;
  pair<int,FechaHistorica> cinsert;
  *this = c1;

  //cronologia.insert(c2.cronologia.cbegin(),c2.cronologia.cend());
  for(it=c2.cronologia.begin();it!=c2.cronologia.end();it++){
    if(cronologia.find(it->first)!=cronologia.end()){
      cronologia[it->first].addHechos((it->second).getHechos());
    }else{
      cinsert.first = it->first;
      cinsert.second = it->second;
      cronologia.insert(cinsert);
    }
  }
}

Cronologia& Cronologia::operator= (const Cronologia& original){
  if(this!=&original){
    map<int,FechaHistorica>::const_iterator it;
    cronologia.clear();
    for(it=original.cronologia.begin();it!=original.cronologia.end();it++){
      pair<int,FechaHistorica> c;
      c.first = it->first;
      c.second = it->second;
      cronologia.insert(c);
    }
  }
  return *this;
}

ostream& operator<< (ostream& os, const Cronologia& c){
  map<int,FechaHistorica>::const_iterator it;
  for(it=c.cronologia.begin();it!=c.cronologia.end();it++)
    os << it->second << endl;

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
      c.aniadirEvento(fecha);
    }
  }

  return is;
}
