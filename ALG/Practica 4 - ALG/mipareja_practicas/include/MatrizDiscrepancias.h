#ifndef __MATRIZDISCREPANCIA__
#define __MATRIZDISCREPANCIA__

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <limits>
#include <cstdlib>


using namespace std;

vector<vector<int> > matrizDiscrepancias(ifstream &f);

vector<vector<int> > matrizDiscrepanciasTiempos(int tam);

ostream &operator<<(ostream &os, const vector<vector<int> > &obj);

#endif
