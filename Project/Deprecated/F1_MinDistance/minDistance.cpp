#include "minDistance.h"



float minDistance(vector<float> Izq_X,vector<float> Izq_Y,vector<float> Der_X,vector<float> Der_Y, float ref_X, float ref_Y ){
    float distancia1;
    float distancia2;
    float dmin1=100000000;
    float dmin2=100000000;
    int index = 0;
    for (int i = index; i < index + 5; i++){
        distancia1 = sqrt((Izq_X[index] - ref_X)*(Izq_X[index] - ref_X) + (Izq_Y[index] - ref_X)*(Izq_Y[index] - ref_X));
        cout << "distancia1" << "="<<distancia1<<"\n";
        distancia2 = sqrt((Der_X[index] - ref_X)*(Der_X[index] - ref_X) + (Der_Y[index] - ref_X)*(Der_Y[index] - ref_X));
        cout << "distancia2" << "="<<distancia2<<"\n";
        if(distancia1 < dmin1){
            dmin1 = distancia1;
        }
        if(distancia2 < dmin2){
            dmin2 = distancia2;
        }
        cout << "dmin1" << "="<<dmin1<<"\n";
        cout << "dmin2" << "="<<dmin2<<"\n";
    }
    return dmin1+dmin2;
}





 