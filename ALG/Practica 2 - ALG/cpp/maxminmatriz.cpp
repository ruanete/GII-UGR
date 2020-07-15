#include <iostream>
#include <chrono>
#include <time.h>

using namespace std;
using namespace std::chrono;

void sintaxis()
{
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño del vector (>0)" << endl;
  cerr << "  VMAX: Valor máximo (>0)" << endl;
  cerr << "Se genera un vector de tamaño TAM con elementos aleatorios en [0,VMAX[" << endl;
  exit(EXIT_FAILURE);
}

pair<int ,int> Max_Min(int ** M,int inicioi,int inicioj,int n){
  pair<int,int> resultado, p1, p2, p3, p4;
  if(n==1){
    resultado.first = M[inicioi][inicioj];
    resultado.second = M[inicioi][inicioj];

    return resultado;
  }else{
    p1=Max_Min(M,inicioi,inicioj,n/2);
    p2=Max_Min(M,inicioi,inicioj+n/2,n/2);
    p3=Max_Min(M,inicioi+n/2,inicioj,n/2);
    p4=Max_Min(M,inicioi+n/2,inicioj+n/2,n/2);

    resultado.first = p1.first;
    resultado.second = p1.second;

    if (p2.first > resultado.first)
        resultado.first = p2.first;

    if (p2.second < resultado.second)
        resultado.second = p2.second;


    if (p3.first > resultado.first)
        resultado.first = p3.first;

    if (p3.second < resultado.second)
        resultado.second = p3.second;


    if (p4.first > resultado.first)
        resultado.first = p4.first;

    if (p4.second < resultado.second)
        resultado.second = p4.second;

    return resultado;
  }
}

int main(int argc, char * argv[]){
  if (argc!=3)
    sintaxis();
  int tam=atoi(argv[1]);
  int vmax=atoi(argv[2]);
  if (tam<=0 || vmax<=0)
    sintaxis();

  int **M = new int*[tam];
  for (int i = 0; i < tam; i++) {
    M[i] = new int[tam];
  }

  for(int i=0;i<tam;i++)
    for(int j=0;j<tam;j++)
      M[i][j]=rand() % vmax;

  /*cout << "Matriz: " << endl;
  for(int i=0;i<tam;i++){
    for(int j=0;j<tam;j++)
      cout << M[i][j] << " ";
    cout << endl;
  }*/

  pair<int, int> max_min;


  //cout << "Maximo: " << max_min.first << endl;
  //cout << "Minimo: " << max_min.second << endl;

  high_resolution_clock::time_point start, end;
	duration<double> tiempo_transcurrido;

	start = high_resolution_clock::now();

  pair<int,int> p;
  max_min = Max_Min(M,0,0,tam);

  end = high_resolution_clock::now();

	tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

	cout << tam << "\t" << tiempo_transcurrido.count() << endl;
}
