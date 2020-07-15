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

void swap(int v[], int i, int j){
        int tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
}

pair<int,int> pivote(int *v, int pivote, int inicio, int final){
  pair<int,int>p;
  p.first=inicio;
  p.second=final;
  int i=inicio;

  while(i<=p.second){
    if(v[i]<pivote){
      swap(v,p.first++,i++);
    }else if(v[i]>pivote){
      swap(v,i,p.second--);
    }else{
      i++;
    }
  }
  return p;
}

// Función recursiva para hacer el ordenamiento
void quicksort(int *zapatos, int* pies, int inicio, int final){
  pair<int,int> p;

  if (inicio < final) {
      p=pivote(pies,zapatos[inicio],inicio,final);
      p=pivote(zapatos,pies[p.second],inicio,final);

      // Ordeno la lista de los menores
      quicksort(zapatos, pies, inicio, p.first-1);

      // Ordeno la lista de los mayores
      quicksort(zapatos, pies, p.second+1, final);
  }
}

int main(int argc, char * argv[]){
  if (argc!=3)
    sintaxis();
  int tam=atoi(argv[1]);
  int vmax=atoi(argv[2]);
  if (tam<=0 || vmax<=0)
    sintaxis();

  int *zapatos=new int[tam];
  int *pies=new int[tam];

  srand(time(0));
  int j=tam-1;
  for (int i=0; i<tam; i++){
    zapatos[j]=pies[i] = rand() % vmax;
    j--;
  }

  /*cout << "Vector zapatos sin ordenar: ";
  for (int i=0; i<tam; i++)
    cout << zapatos[i] << " ";

  cout << endl << "Vector pies sin ordenar: ";
  for (int i=0; i<tam; i++)
    cout << pies[i] << " ";

  cout << endl;*/


  high_resolution_clock::time_point start, end;
	duration<double> tiempo_transcurrido;

	start = high_resolution_clock::now();

  pair<int,int> p;
  quicksort(zapatos,pies,0,tam);

  end = high_resolution_clock::now();

	tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

	cout << tam << "\t" << tiempo_transcurrido.count() << endl;

  /*cout << endl << "Vector zapatos ordenado: ";
  for (int i=0; i<tam; i++)
    cout << zapatos[i] << " ";

  cout << endl << "Vector pies ordenado:    ";
  for (int i=0; i<tam; i++)
    cout << pies[i] << " ";

  cout << endl;*/
}
