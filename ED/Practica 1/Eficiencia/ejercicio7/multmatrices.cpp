#include <iostream>
#include <ctime>    // Recursos para medir tiempos
#include <cstdlib>  // Para generación de números pseudoaleatorios

using namespace std;

void sintaxis()
{
  cerr << "Sintaxis:" << endl;
  cerr << "  TAM: Tamaño de la matriz (>0)" << endl;
  cerr << "  VMAX: Valor máximo que puede tomar una posicion (>0)" << endl;
  cerr << "Se generan tres matrices de tamaño TAMxTAM con elementos aleatorios en [0,VMAX] para dos de ellas y se multiplican" << endl;
  exit(EXIT_FAILURE);
}

int main(int argc, char * argv[])
{
  // Lectura de parámetros
  if (argc!=3)
    sintaxis();
  int tam=atoi(argv[1]);     // Tamaño del vector
  int vmax=atoi(argv[2]);    // Valor máximo
  if (tam<=0 || vmax<=0)
    sintaxis();

  // Generación de las matrices
  int **a, **b, **c;
  a=new int* [tam];
  b=new int* [tam];
  c=new int* [tam];
  for(int i=0;i<tam;i++){
    a[i]=new int[tam];
    b[i]=new int[tam];
    c[i]=new int[tam];
  }

  srand(time(0));            // Inicialización del generador de números pseudoaleatorios

  //Inicializo las matrices a y b con numeros aleatorios y c con 0 ya que va a ser la matriz resultado
  for (int i=0; i<tam; i++){
    for(int j=0;j<tam;j++){
      a[i][j] = rand() % vmax;
      b[i][j]=rand() % vmax;
      c[i][j]=0;
    }
  }
  clock_t tini;    // Anotamos el tiempo de inicio
  tini=clock();

  for(int i=0; i<tam; ++i)
        for(int j=0; j<tam; ++j)
            for(int z=0; z<tam; ++z)
                c[i][j] += a[i][z] * b[z][j];

  clock_t tfin;    // Anotamos el tiempo de finalización
  tfin=clock();

  // Mostramos resultados
  cout << tam << "\t" << (tfin-tini)/(double)CLOCKS_PER_SEC << endl;

  // Liberamos memoria dinámica
  for (int i = 0; i < tam;i++){
      delete[] a[i];
      delete[] b[i];
      delete[] c[i];
  }

  delete[] a;
  delete[] b;
  delete[] c;

}
