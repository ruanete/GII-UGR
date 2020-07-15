
	//----- Sección de Declaraciones --------------//

%{
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iomanip>

using namespace std;

int nc, np, nl;
vector<vector<string>> datosObtenidos;
int indice=0;

void escribir_datos (string paginasTotales, vector<vector<string>> datosObtenidos, ostream& os);
string paginasTotales;
string palabra_buscada;
string busqueda_final;
string amazon = "https://www.amazon.es/s/ref=nb_sb_noss_2?__mk_es_ES=ÅMÅŽÕÑ&url=search-alias%3Daps&field-keywords=";
%}

numero_producto <li[ ]id=\"result_[0-9]*
num_paginas_totales <span[ ]class=\"pagnDisabled\">[0-9]*<\/span>
nombre_producto <h2[ ]data-attribute=\"([^\"]*)
precio_producto <span[ ]class=\"a-size-base[ ]a-color-price[ ]s-price[ ]a-text-bold\">EUR[ ][0-9]+([,][0-9]+)?<\/span>
estrellas_producto  <span[ ]class=\"a-icon-alt\">[0-9]+([,][0-9]+)?[ ]de[ ]un[ ]máximo[ ]de[ ]5[ ]estrellas<\/span>
link_producto <div[ ]aria-hidden=\"true\"[ ]class=\"a-column[ ]a-span12[ ]a-text-left\"><div[ ]class=\"a-section[ ]a-spacing-none[ ]a-inline-block[ ]s-position-relative\"><a[ ]class=\"a-link-normal[ ]a-text-normal\"[ ]href=\"([^\"]*)
%%
	//----- Sección de Reglas ---------------- //
.|\n {}

{numero_producto} {
                    string num_producto = yytext;
                    indice = stoi(num_producto.substr(num_producto.find("_")+1,num_producto.length()));
                    datosObtenidos.resize(indice+1);
                    datosObtenidos[datosObtenidos.size()-1].assign(4,"X");
                  }

{num_paginas_totales} {
                        string pag_totales = yytext;
                        string final = pag_totales.substr(27, pag_totales.find("</"));
                        paginasTotales = final.substr(0,final.find("<"));
                      }

{nombre_producto} {
                    string nombre_producto = yytext;
                    datosObtenidos[indice][0] = nombre_producto.substr(20, nombre_producto.length());
                  }

{precio_producto} {
                    string precio_producto = yytext;
                    precio_producto = precio_producto.substr(precio_producto.find("EUR"));
                    precio_producto = precio_producto.substr(0,precio_producto.length()-7);
                    datosObtenidos[indice][1] = precio_producto;
                  }

{estrellas_producto}  {
                        string valoracion = yytext;
                        valoracion = valoracion.substr(25,valoracion.length());
                        valoracion = valoracion.substr(0,valoracion.find(" "));
                        datosObtenidos[indice][2] = valoracion + "/5";
                      }

{link_producto} {
                  string link_producto = yytext;
                  datosObtenidos[indice][3] = link_producto.substr(180, link_producto.length());
                }
%%

using namespace std;

int main(int argc, char** argv){
  int out;
  string opcion;
  FILE* file;
  bool ejecucion = false;
  nc = np = nl = 0;

  int saved_stdout = dup(1);
  dup2(NULL, 1);

  if(argc==2)
    opcion=argv[1];

  //MODO 1: Se realiza petición con las palabras claves que se han buscado
  if(argc == 1){
    cout << "¿Que deseas buscar en Amazon.es" << endl;
    cin >> palabra_buscada;

    busqueda_final="\""+amazon+palabra_buscada+"\"";
    string wgetFinal="wget -U \"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/61.0.3163.79 Safari/537.36\" --output-document=./datos/index.html "+busqueda_final;

    out = system((const char*)wgetFinal.c_str());
    cerr << setw(20) << "wget" << "-->" << strerror(out)  << left << endl;

    file = fopen("./datos/index.html", "r");
    if (file == NULL) {
      cout << strerror(ferror(file)) << endl;
      exit (-1);
      yyin = file;
    }else
      yyin = file;

    ejecucion=true;
  }else if(argc == 2 && opcion.compare("-i")==0){
    cout << "USO: ./P2 [archivo] o ./P2" << endl << "La primera opción es para pasarle un HTML de Amazon y la segunda opción realiza una petición a Amazon." << endl;
    return 0;
  }else{
    file = fopen(opcion.c_str(), "r");
    if (file == NULL) {
      cout << "El fichero no existe o no has dado la ruta correcta." << endl;
      exit (-1);
    }else{
      yyin = file;
      ejecucion=true;
    }
  }

  if(ejecucion){
    yylex();
    dup2(saved_stdout, 1);
    close(saved_stdout);
    escribir_datos(paginasTotales, datosObtenidos, cout);
  }
}

void escribir_datos (string paginasTotales, vector<vector<string>> datosObtenidos, ostream& os){
  string separator = string(79,'-');
  string flag = "\033[0m";
  cout << endl;
  cout << "SI SE ENCUENTRA UNA \"X\" EN LOS RESULTADOS ES QUE EL PRODUCTO NO TIENE ESE DATO." << endl << "LOS TITULOS NO ESTAN COMPLETOS DEBIDO A QUE SON DEMASIADO EXTENSO, SE HAN ACORTADO A 30 CARACTERES." << endl;
  cout << flag << separator << endl;
  cout <<"| " << "#" << setw(4) << " | " << "Nombre producto" << setw(25) << " | " << "Precio " << setw(11) << " | " << setw(10) << "Valoraciones" << " | "  << endl;

  cout << flag << separator  << "\033[0m" << endl;
  for(int i=0;i<datosObtenidos.size();i++){
    if(i<10){
      cout << flag << separator << endl;
      cout <<"| " << i << setw(4) << " | " << datosObtenidos[i][0].substr(0,30) << setw(10) << " | ";
      cout.width(10);
      cout << datosObtenidos[i][1] << setw(8) << " | ";
      cout.width(5);
      cout << datosObtenidos[i][2] << setw(10) << " | "  << endl;
      cout << separator << endl;
    }else{
      cout << flag << separator << endl;
      cout <<"| " << i << setw(3) << " | " << datosObtenidos[i][0].substr(0,30) << setw(10) << " | ";
      cout.width(10);
      cout << datosObtenidos[i][1] << setw(8) << " | ";
      cout.width(5);
      cout << datosObtenidos[i][2] << setw(10) << " | "  << endl;
      cout << separator << endl;
    }
  }
}
