#include "mapGeneration.h"
#define debX 252.6337127685547
#define debZ -75.0084457397461
#define vX -12991/32767.0f
#define vZ -30081/32767.0f
#define windowRes 50
#define yRes 40 //Distancia en metros hacia delante que cubre mascara


namespace plt = matplotlibcpp;
// Leer archivo

readVector readFile(std::string nameFile, int nSkip, int nCols, bool* indexes){
	std::fstream file;
	std::string tempLine = "ERROR";
	char formater = ' ';
	readVector retorno;
	file.open(nameFile);
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
	Matrix wCenterline = window(centerline,debX ,debZ, windowRes);
	Matrix wInnerLimit = window(innerLimit,debX ,debZ, windowRes);
	Matrix wOuterLimit = window(outerLimit,debX ,debZ, windowRes);
	Matrix wRaceLine = window(raceLine,debX ,debZ, windowRes);
	//rotation
	rotation(wCenterline, vX, vZ);
	rotation(wInnerLimit,vX, vZ);
	rotation(wOuterLimit,vX, vZ);
	rotation(wRaceLine,vX, vZ);
	//plt::figure_size(1920, 1080);
	//TEMP
	std::vector<double> test = manyDistances(wOuterLimit, wInnerLimit, wRaceLine, 0.0f, 0.0f);
	for(unsigned int i = 0; i < test.size(); i++){
		std::cout << test.at(i) << std::endl;
	}
	plotXZ(wInnerLimit, "innerLimit", "b-");
	plotXZ(wOuterLimit, "outerLimit", "g-");
	if(center){
		plotXZ(wCenterline, "centerline", "k-");
	}
	if(racingLine){
		plotXZ(wRaceLine, "racingLine", "m-");
	}



	std::vector<double> testX;
	std::vector<double> testZ;
	testX.push_back(0);
	testZ.push_back(0);
	plt::plot(testX, testZ, {{"c", "red"}, {"marker", "o"}});
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
	float a11 =  -zVal/hypot;
	float a12 = xVal/hypot;
	float a21 =  -xVal/hypot;
	float a22 =  -zVal/hypot;
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
	for(unsigned int i = 0; i < Vx->size(); i++){
		distance = pow(Vx->at(i)-xVal, 2) + pow(Vz->at(i)-zVal, 2);
		if(distance <= pow(epsilon,2)){
			retorno.addX(Vx->at(i)-xVal);
			retorno.addY(Vz->at(i)-zVal);
		}
	}
	return retorno;
}


// - Distancia horizontal

std::vector<double> manyDistances(Matrix& leftBorder, Matrix& rightBorder, Matrix& racingLine, float x, float y, int n)
{
	//en este caso, x e y representan la posición del auto
	std::vector<double> retorno;
	float delta = yRes/n; // FALTA CALIBRAR EL SALTO HACIA ADELANTE!
	for(int i = 0; i < n; i ++){
		retorno.push_back(oneDistance(leftBorder, rightBorder, racingLine, x, y + (delta*i)));
	}

	return retorno;
}

double oneDistance(Matrix& leftBorder, Matrix& rightBorder, Matrix& racingLine, float x, float y)
{
	// en este caso, x e y representan una posición que puede ser la del auto,
	// pero no necesariamente
	std::vector<float> leftBorderX =leftBorder.getX();
	std::vector<float> leftBorderY =leftBorder.getY();
	std::vector<float> rightBorderX =rightBorder.getX();
	std::vector<float> rightBorderY =rightBorder.getY();
	std::vector<float> racingX = racingLine.getX();
	std::vector<float> racingY = racingLine.getY();

	float NOTVALID = 100000;
	float dleft = NOTVALID;
	float dright = NOTVALID;
	float drace = NOTVALID;
	float xl = NOTVALID;
	float xr = NOTVALID;
	float xRace = NOTVALID;

	for (unsigned int i = 0; i < leftBorderX.size(); i++){
		if(((leftBorderY.at(i) - y) < dleft) && (leftBorderY.at(i) >= y)) {
			dleft = leftBorderY.at(i) - y;
			xl = leftBorderX.at(i);
		}
	}
	for (unsigned int i = 0; i < racingX.size(); i++){
		if(((racingY.at(i) - y) < drace) && (racingY.at(i) >= y)) {
			drace = racingY.at(i) - y;
			xRace = racingX.at(i);
		}
	}

	for (unsigned int i = 0; i < rightBorderX.size(); i++){
		if(((rightBorderY.at(i) - y) < dright) && (rightBorderY.at(i) >= y)) {
			dright = rightBorderY.at(i) - y;
			xr = rightBorderX.at(i);
		}
	}
	return (double) ((xRace - xl)/(xr - xl));
}
