#include "MatrizDiscrepancias.h"

vector<vector<int> > matrizDiscrepancias(ifstream &f) {
    int individuos, car;

    string str;
    getline(f, str);
    f >> individuos >> car;

    vector<vector<int> > matriz;

    int i, j, val;
    i = j = val = 0;

    while (i < individuos) {
        j = 0;
        vector<int> carInd;
        while (j < car) {
            f >> val;
            carInd.push_back(val);
            j++;
        }
        matriz.push_back(carInd);
        i++;
    }

    vector<vector<int> > mDisc(individuos);
    for (i = 0; i < mDisc.size(); i++) {
        mDisc[i].resize(individuos);
    }

    int disc;
    int max = std::numeric_limits<int>::max();

    for (i = 0; i < mDisc.size(); i++) {
        for (j = 0; j < mDisc[i].size(); j++) {
            if (i == j) {
                mDisc[i][j] = max;
            } else {
                disc = 0;
                for (int k = 0; k < car; k++) {
                    disc += abs(matriz[i][k] - matriz[j][k]);
                }
                mDisc[i][j] = disc;
            }
        }
    }

    return mDisc;
}

vector<vector<int> > matrizDiscrepanciasTiempos(int tam) {
    int car = 10;
    vector<vector<int> > matriz;

    int i, j, val;
    i = j = val = 0;

    while (i < tam) {
        j = 0;
        vector<int> carInd;
        while (j < car) {
            val = rand()%10+1;
            carInd.push_back(val);
            j++;
        }
        matriz.push_back(carInd);
        i++;
    }

    vector<vector<int> > mDisc(tam);
    for (i = 0; i < mDisc.size(); i++) {
        mDisc[i].resize(tam);
    }

    int disc;
    int max = std::numeric_limits<int>::max();

    for (i = 0; i < mDisc.size(); i++) {
        for (j = 0; j < mDisc[i].size(); j++) {
            if (i == j) {
                mDisc[i][j] = max;
            } else {
                disc = 0;
                for (int k = 0; k < car; k++) {
                    disc += abs(matriz[i][k] - matriz[j][k]);
                }
                mDisc[i][j] = disc;
            }
        }
    }

    return mDisc;
}

ostream &operator<<(ostream &os, const vector <vector<int> > &obj) {
    int max = std::numeric_limits<int>::max();
    int val;

    for (unsigned int i = 0; i < obj.size(); i++) {
        for (unsigned int j = 0; j < obj[i].size(); j++) {
            val = obj[i][j];
            if (val == max) {
                os << std::setw(4) << "inf";
            } else {
                os << std::setw(4) << val;
            }
        }
        os << endl;
    }
    return os;
}
