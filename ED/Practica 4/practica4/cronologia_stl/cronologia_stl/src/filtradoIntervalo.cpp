#include "Cronologia.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char * argv[]){
  if (argc!=4 && argc!=5){
      cout<<"Error: debe dar al menos los nombres de dos ficheros con cronologías. "<<endl;
      cout<<"[Opcional]: un tercer nombre de fichero para guardar la cronología resultante."<<endl;
      return 0;
   }

   ifstream f1 (argv[1]);
   if (!f1){
    cout<<"No puedo abrir el fichero "<<argv[1]<<endl;
    return 0;
   }

   if(argc==5){
     ifstream f2 (argv[4]);
     if (!f2){
       cout<<"No puedo abrir el fichero "<<argv[4]<<endl;
       return 0;
     }
   }

   Cronologia mi_cronologia;
   f1>>mi_cronologia;

   Cronologia intervalo;
   intervalo = mi_cronologia.eventosFechas(atoi(argv[2]),atoi(argv[3]));
   cout << "Los eventos desde " << atoi(argv[2]) << "-" << atoi(argv[3]) << " son: " << endl;
   cout << intervalo << endl;
}
