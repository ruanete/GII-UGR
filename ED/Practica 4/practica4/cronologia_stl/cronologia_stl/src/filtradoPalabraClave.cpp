#include "Cronologia.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char * argv[]){
  if (argc!=3 && argc!=4){
      cout<<"Error: debe dar al menos el nombre de un fichero con cronologías. " << endl;
      cout<<"[Opcional]: un segundo nombre de fichero para guardar la cronología resultante."<<endl;
      return 0;
  }

   ifstream f1 (argv[1]);
   if (!f1){
    cout << "No puedo abrir el fichero " << argv[1] << endl;
    return 0;
   }

   if(argc==4){
     ifstream f2 (argv[3]);
     if (!f2){
       cout << "No puedo abrir el fichero " << argv[4] << endl;
       return 0;
     }
   }

   Cronologia mi_cronologia;
   f1>>mi_cronologia;

   Cronologia filtrado;
   filtrado = mi_cronologia.buscarEventos(argv[2]);
   cout << endl << "Los eventos con la cadena \"" << argv[2] << "\" son: " << endl;
   cout << filtrado << endl;
}
