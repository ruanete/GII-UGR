#include <iostream>
#include <vector>
#include <chrono>
#include <time.h>

using namespace std;
using namespace std::chrono;

bool ordenado=false;

void sintaxis(){
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
void quicksort(int *v, int inicio, int final){
  pair<int,int> p;

  if (inicio < final) {
      p=pivote(v,v[inicio],inicio,final);

      // Ordeno la lista de los menores
      quicksort(v, inicio, p.first-1);

      // Ordeno la lista de los mayores
      quicksort(v, p.second+1, final);
  }
}

pair<int, int> Moda(int v[], int inicio, int final) {
	pair<int, int> moda;
	int *homogeneo=new int[final];
	int *heterogeneo=new int[final];
	int tamanoHo = 0, tamanoHe = 0;
	int j = 0;

	moda.first = 0;
	moda.second = 0;

	if (!ordenado){
		quicksort(v, inicio, final);
		ordenado = true;
	}

	do{
		homogeneo[tamanoHo] = v[j];
		++j;
		++tamanoHo;
	}while (v[j] == v[j-1]);

	while (tamanoHe < (final - tamanoHo)){
		heterogeneo[tamanoHe] = v[j];
		++j;
		++tamanoHe;
	}

	if (tamanoHo > tamanoHe && tamanoHo > 1){
		moda.first = homogeneo[0];
		moda.second = tamanoHo;
	}else{
   	pair<int, int> modaheterogeneo =  Moda(heterogeneo, tamanoHo, tamanoHe);
		if (modaheterogeneo.second > moda.second){
			moda.first = modaheterogeneo.first;
			moda.second = modaheterogeneo.second;
		}
	}
	return moda;
}

int main(int argc, char * argv[]){
  if (argc!=3)
    sintaxis();
  int tam=atoi(argv[1]);
  int vmax=atoi(argv[2]);
  if (tam<=0 || vmax<=0)
    sintaxis();

  int *v=new int[tam];

  srand(time(0));
  for (int i=0; i<tam; i++){
    v[i] = rand() % vmax;
  }

  /*cout << "Vector: ";
  for (int i=0; i<tam; i++)
    cout << v[i] << " ";

  cout << endl;*/

  high_resolution_clock::time_point start, end;
	duration<double> tiempo_transcurrido;

	start = high_resolution_clock::now();

  pair<int,int> p;
  p = Moda(v,0,tam);
  //cout << "La moda es: " << p.first << "-" << p.second << endl;

  end = high_resolution_clock::now();

	tiempo_transcurrido  = duration_cast<duration<double> >(end - start);

	cout << tam << "\t" << tiempo_transcurrido.count() << endl;

}
