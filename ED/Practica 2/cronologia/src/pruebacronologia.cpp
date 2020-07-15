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
   f>>mi_cronologia; //Cargamos en memoria la cronología.
   cout << "El archivo ha sido cargado perfectamente." << endl << endl;

   char opcion;

   do{
     cout << "OPCION 1) Obtener los eventos acaecidos en un año dado. " << endl;
     cout << "OPCION 2) Obtener la (sub)cronología de eventos históricos acaecidos en [anioDesde, anioHasta], donde anioDesde y anioHasta son proporcionados por el usuario" << endl;
     cout << "OPCION 3) Obtener la (sub)cronología de eventos históricos asociados a una palabra clave. Ejemplo: la cronología de eventos asociados a Einstein" << endl;
     cout << "OPCION 4) Operadores sobre cronologías, ejemplo: Unión de dos cronologías (la cronología resultante debería estar ordenada)" << endl << endl;
     cout << "UTILIZA LA OPCIÓN q PARA SALIR DEL PROGRAMA" << endl << endl;
     cout << "¿Que deseas realizar con los datos cargados?: ";
     cin >> opcion;

     if(opcion=='1'){
       Cronologia aux;
       int fecha;
       cout << "Fecha de los eventos a consultar: ";
       cin >> fecha;
       aux = mi_cronologia.eventosAnio(fecha);
       if(mi_cronologia.buscarAnio(fecha)!=-1){
        cout << endl << "LOS EVENTOS CON FECHA " << fecha << " SON: " << endl;
        cout << aux << endl;
       }

       cout << "------------------------" << endl;
     }else if(opcion=='2'){
       int fecha_ini,fecha_fin;

       cout << "Introduzca la fecha de inicio: ";
       cin >> fecha_ini;
       cout << "Introduzca la fecha final: ";
       cin >> fecha_fin;

       Cronologia aux;
       aux = mi_cronologia.eventosFechas(fecha_ini,fecha_fin);
       if(mi_cronologia.buscarAnio(fecha_ini)!=-1 && mi_cronologia.buscarAnio(fecha_fin)!=-1){
        cout << endl << "LOS EVENTOS ENTRE LA FECHA " << fecha_ini << " Y LA FECHA " << fecha_fin << " SON: " << endl;
        cout << aux <<endl;
       }

       cout << "------------------------" << endl;
     }else if(opcion=='3'){
       string palabra_clave;
       cout << endl << "Introduzca la palabra clave a buscar: ";
       cin >> palabra_clave;

       Cronologia crono1;
       crono1 = mi_cronologia.eventosPalabra(palabra_clave);

       if(crono1.size()!=0){
        cout << endl << "LOS EVENTOS CON LA PALABRA " << palabra_clave << " SON: " << endl;
        cout << crono1 << endl;
       }

       cout << "------------------------" << endl;
     }else if(opcion=='4'){
       string ruta;

       cout << endl << "Introduzca la ruta de otro fichero cronologia: ";
       cin >> ruta;

       ifstream s(ruta.c_str());

       if (!s){
        cout<< endl << "No puedo abrir el fichero "<<ruta<<endl << endl;
       }else{
         Cronologia otra_cronologia, final;
         s >> otra_cronologia;

         cout << endl << "LA CRONOLOGIA FINAL CON LAS DOS CONCATENADAS SON: " << endl;
         final = mi_cronologia + otra_cronologia;
         cout << final << endl;
         cout << "------------------------" << endl;
       }
      }
   }while (opcion != 'q' && opcion != 'Q');


   /* Exhibir aquí la funcionalidad programada para el TDA Cronologia / TDA FechaHistorica */

   // Algunas sugerencias:
   // - Obtener los eventos acaecidos en un año dado
   // - Obtener la (sub)cronología de eventos históricos acaecidos en [anioDesde, anioHasta], donde anioDesde y anioHasta son proporcionados por el usuario
   // - Obtener la (sub)cronología de eventos históricos asociados a una palabra clave. Ejemplo: la cronología de eventos asociados a "Einstein"
   // - Operadores sobre cronologías, ejemplo: Unión de dos cronologías (la cronología resultante debería estar ordenada)
   // - Cualquier otra funcionalidad que consideréis de interés


}
