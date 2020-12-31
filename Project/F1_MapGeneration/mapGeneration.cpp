#include "mapGeneration.h"
namespace plt = matplotlibcpp;
// Leer archivo

readVector readFile(std::string nameFile, int nSkip, int nCols, bool* indexes){
	std::fstream file;
	std::string tempLine = "ERROR";
	char formater = ' ';
	readVector retorno;
	file.open(nameFile);
	std::cout << "AAA " << sizeof(indexes) << std::endl;
	if(file.is_open()){
		for(int i = 0; i < nSkip; i++){
			getline(file,tempLine);      // Saltar linea de descripcion
		}
		while(!file.eof()){
			std::vector<float> tempVector;
			for(int i = 0; i < nCols; i++){
				if(i != (nCols-1)){
					formater = ',';
				}
				else{
					formater = '\n';
				}
				getline(file, tempLine, formater);
				if(tempLine.length() == 0){
					break;
				}
				else{
					if(indexes[i]){
						tempVector.push_back(std::stof(tempLine));
					}
				}
			}
			if(tempVector.size() != 0){
				retorno.push_back(tempVector);
			}
		}
		file.close();
	}
	else{
		std::cout << "¡Archivo " << nameFile << " no encontrado!" << std::endl;
	}
	return retorno;
}


void printVector(readVector toPrint){
	std::cout << std::fixed;
	std::cout << std::setprecision(13);
	 for (unsigned int i = 0; i < toPrint.size(); i++) {
		for (unsigned int j = 0; j < toPrint[i].size(); j++){
			std::cout << toPrint[i][j] << '\t';
		}
		std::cout << std::endl;
	}
}

// Plotear - Wrapper


void plotXZ(Matrix input, std::string name, std::string style){
	plt::named_plot(name, input.getX(), input.getY(), style);
}



// - Defecto silverstone

void plotSilverstone(bool center, bool racingLine, std::string saveName){
	// Nombres archivos
	std::string trackArray[] = {"silverstone_2020_centerline.track","silverstone_2020_innerlimit.track", "silverstone_2020_outerlimit.track","silverstone_2020_racingline.track"};
	bool selCols[] = {false, true, true, false, false, false};
	//Valores de pista
	Matrix centerline(readFile(SILVERPATH+trackArray[0],2,6,selCols));
	Matrix innerLimit(readFile(SILVERPATH+trackArray[1],2,6,selCols));
	Matrix outerLimit(readFile(SILVERPATH+trackArray[2],2,6,selCols));
	Matrix raceLine(readFile(SILVERPATH+trackArray[3],2,6,selCols));
	//window
	Matrix wCenterline = window(centerline,464.4882202 ,-559.611145, 300);
	Matrix wInnerLimit = window(innerLimit,464.4882202 ,-559.611145, 300);
	Matrix wOuterLimit = window(outerLimit,464.4882202 ,-559.611145, 300);
	Matrix wRaceLine = window(raceLine,464.4882202 ,-559.611145, 300);
	//rotation
	rotation(wCenterline,(-26251/32767),(19610.23/32767));
	rotation(wCenterline,(-26251/32767),(19610.23/32767));
	rotation(wInnerLimit,(-26251/32767),(19610.23/32767));
	rotation(wOuterLimit,(-26251/32767),(19610.23/32767));
	rotation(wRaceLine,(-26251/32767),(19610.23/32767));
	plt::figure_size(1920, 1080);
	//TEMP
	plotXZ(wInnerLimit, "innerLimit", "b-");
	plotXZ(wOuterLimit, "outerLimit", "g-");
	if(center){
		plotXZ(wCenterline, "centerline", "k-");
	}
	if(racingLine){
		plotXZ(wRaceLine, "racingLine", "m-");
	}
	plt::title("Pista: silverstone");
	plt::legend();
	if(saveName.length() != 0){
		plt::save(saveName+".png");
	}
	plt::show();
}

// - Aplicar rotacion y traslacion
void rotation(Matrix& input, float xVal, float zVal){
	//Varibles primas
	float xPrime = 0.0f;
	float zPrime = 0.0f;
	//Calculo de cos/sin desde vector de entrada
	float hypot = sqrt(pow(xVal, 2) + pow(zVal, 2));
	float a11 =  zVal/hypot;
	float a12 = -xVal/hypot;
	float a21 =  xVal/hypot;
	float a22 =  zVal/hypot;
	// Obtencion vectores de Matrix
	std::vector<float>* Vx = input.getpX();
	std::vector<float>* Vz = input.getpY();
	for(int i = 0; i < input.getSize(); i++){
		xPrime = Vx->at(i)*a11 + Vz->at(i)*a12;
		zPrime = Vx->at(i)*a21 + Vz->at(i)*a22;
		(*Vx)[i] = xPrime;
		(*Vz)[i] = zPrime;
	}
}

// - Seleccion de ventana dado punto
Matrix window(Matrix& input, float xVal, float zVal, float epsilon){
	Matrix retorno;
	std::vector<float>* Vx = input.getpX();
	std::vector<float>* Vz = input.getpY();
	float distance = 0.0f;
	std::cout << "xSize"  << Vx->size() << " ySize" << Vz->size() << std::endl;
	for(unsigned int i = 0; i < Vx->size(); i++){
		distance = pow(Vx->at(i)-xVal, 2) + pow(Vz->at(i)-zVal, 2);
		//std::cout << distance << std::endl;
		if(distance <= pow(epsilon,2)){
			std::cout << "OK" << std::endl;
			retorno.addX(Vx->at(i));
			retorno.addY(Vz->at(i));
		}
	}
	return retorno;
}


// - Distancia horizontal

std::vector<double> manyDistances(Matrix leftBorder, Matrix rightBorder, float x, float y, int n)
{
	//en este caso, x e y representan la posición del auto
	std::vector<double> retorno;
	float temp = 10;
	float delta = temp; // FALTA CALIBRAR EL SALTO HACIA ADELANTE! Valor Temp
	for(int i = 0; i < n; i ++){
		retorno.push_back(oneDistance(leftBorder, rightBorder, x, y + (delta*i));
	}

	return retorno;
}

double oneDistance(Matrix leftBorder, Matrix rightBorder, float x, float y)
{
	// en este caso, x e y representan una posición que puede ser la del auto,
	// pero no necesariamente
	std::vector<float> leftBorderX =leftBorder.getX();
	std::vector<float> leftBorderY =leftBorder.getY();
	std::vector<float> rightBorderX =rightBorder.getX();
	std::vector<float> rightBorderY =rightBorder.getY();

	float NOTVALID = 100000;
	float dleft = NOTVALID;
	float dright = NOTVALID;
	float xl = NOTVALID;
	float xr = NOTVALID;

	for (unsigned int i = 0; i < leftBorderX.size(); i++){
		if(leftBorderX.at(i) < x){ // Verificar si esta a la izquierda de x
			if((leftBorderY.at(i) - y) < dleft) && (leftBorderY.at(i) >= y) {
				dleft = leftBorderY.at(i) - y;
				xl = leftBorderX.at(i);
			}
		}
	}
	for (unsigned int i = 0; i < rightBorderX.size(); i++){
		if(rightBorderX.at(i) > x){ //Verificar si esta a la derecha de x
			if((rightBorderY.at(i) - y) < dright) && (rightBorderY.at(i) >= y) {
				dright = rightBorderY.at(i) - y;
				xr = rightBorderX.at(i);
			}
		}
	}

	return (double)(xr - xl);
}
