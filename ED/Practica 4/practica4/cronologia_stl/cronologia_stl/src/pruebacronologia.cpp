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
   f>>mi_cronologia; //Cargamos en memoria, en el traductor.

   //cout << "Cronologia: " << endl;
   //(cout << mi_cronologia;

   /*int anio;
   cout<<"Dime un año a consultar:";
   cin >> anio;

   FechaHistorica eventos;
   eventos = mi_cronologia.GetEventos(anio);  //Asumimos que Cronologia::GetEventos() devuelve objeto de clase EventoHistorico

   // Recorremos con iterador los acontecimientos para mostrarlos por pantalla
   // Este proceso requiere la definición de un tipo iterator // const_iterator en EventoHistorico
   // Y la definición de los métodos begin() y end() en EventoHistorico
   FechaHistorica::Iterator it;
   cout << anio << ":";              //Imprimimos el anio
   for (it=eventos.begin(); it!=eventos.end();++it)
     cout<<(*it)<<'#';
   cout<<endl;*/

   /*//PRUEBA INTERVALO//
   Cronologia intervalo;
   intervalo = mi_cronologia.eventosFechas(1900,1903);
   cout << "Los eventos desde 1900-1903 son: " << endl;
   cout << intervalo << endl;
   //FIN//*/

   //PRUEBA FILTRADO STRING//
   /*Cronologia filtrado;
   string texto;
   cout << "Introduzca una palabra: ";
   getline(cin,texto);
   filtrado = mi_cronologia.buscarEventos(texto);
   cout << "Los eventos con string son: " << endl;
   cout << filtrado << endl;*/
   //FIN//

   //RECUENTO DE EVENTOS//
   /*pair<int,int> max;
   max=mi_cronologia.eventosMax();
   cout << "El numero total de eventos en la cronologia es de: " << mi_cronologia.totalEventos() << endl;
   cout << "El evento con fecha " << max.first << " es el que más eventos tiene en un año con un total de " << max.second << " eventos" << endl;
   cout << "El promedio de acontecimiento por año es de " << mi_cronologia.totalEventos()/mi_cronologia.numeroAnios() << " eventos" << endl;
   *///FIN//

   //UNION CRONOLOGIAS/

   //FIN//

}
