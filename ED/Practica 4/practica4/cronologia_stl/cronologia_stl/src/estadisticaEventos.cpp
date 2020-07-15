#include "Cronologia.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]){

  if (argc!=2){
      cout<<"Dime el nombre del fichero con la cronologia"<<endl;
      return 0;
   }

   ifstream f (argv[1]);
   if (!f){
    cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
    return 0;
   }

   Cronologia mi_cronologia;
   f>>mi_cronologia;

   pair<int,int> max;
   max=mi_cronologia.eventosMax();

   cout << "El numero total de acontecimientos en la cronologia es de: " << mi_cronologia.totalEventos() << endl;
   cout << "El año " << max.first << " es el que más eventos tiene en un año con un total de " << max.second << " eventos" << endl;
   cout << "El promedio de acontecimientos por año es de " << mi_cronologia.totalEventos()/mi_cronologia.numeroAnios() << " eventos" << endl;
}
