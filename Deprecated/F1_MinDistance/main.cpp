#include "minDistance.h"


vector<float> Izq_X={ 1.2, 2.3, 3.1, 4.5, 5.1, 6.6 };
vector<float> Izq_Y={ 1, 1.5, 2, 2.5, 3, 4 };
vector<float> Der_X={ 1.2, 2.3, 3.1, 4.5, 5.1, 6.6 };
vector<float> Der_Y={ 1, 1.5, 2, 2.5, 3, 4 };
float Auto_X = 4.0;
float Auto_Y = 1.2;
float minima;

int main()
{

minima = minDistance(Izq_X,Izq_Y,Der_X,Der_Y,Auto_X,Auto_Y);

cout << "\ndistancia minima entre bordes" << "="<<minima<<"\n";
//cout <<"("<< Izq_X[index] << "," <<Izq_Y[index] <<")"<< "\n";
    return 0;
}
