#include "minDistance.h"


float minDistance(vector<float> Izq_X,vector<float> Izq_Y,vector<float> Der_X,vector<float> Der_Y float ref_X, float ref_Y ){
    for (int i = index; i < index + 5; i++){
        distancia1 = sqrt((Izq_X[index] - ref_X)*(Izq_X[index] - ref_X) + (Izq_Y[index] - ref_X)*(Izq_Y[index] - ref_X));
        distancia2 = sqrt((Der_X[index] - ref_X)*(Der_X[index] - ref_X) + (Der_Y[index] - ref_X)*(Der_Y[index] - ref_X));
        if(distancia1 < dmin1){
            dmin1 = distancia;
        }
        if(distancia2 < dmin2){
            dmin2 = distancia2;
        }
    }
    return dmin1;
}

float distancia1;
float distancia1;
vector<float> Izq_X={ 1.2, 2.3, 3.1, 4.5, 5.1, 6.6 };
vector<float> Izq_Y={ 1, 1.5, 2, 2.5, 3, 4 };
vector<float> Der_X={ 1.2, 2.3, 3.1, 4.5, 5.1, 6.6 };
vector<float> Der_Y={ 1, 1.5, 2, 2.5, 3, 4 };
float Auto_X = 4.0;
float Auto_Y = 1.2;

float dmin1=0;
float dmin2=0;
int index = 0;
int main()
{



minDistance(Izq_X,Izq_Y,Der_X,Der_Y,Auto_X,Auto_Y);


cout <<"("<< dmin1 << "+" <<dmin2 <<"="<<dmin1 + dmin2 <<"\n";
//cout <<"("<< Izq_X[index] << "," <<Izq_Y[index] <<")"<< "\n";
    return 0;
}



 