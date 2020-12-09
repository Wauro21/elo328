#include "mapGeneration.h"
namespace plt = matplotlibcpp;
// Leer archivo
readVector readFile(std::string nameFile, int nSkip, int nCols, bool* indexes){
	std::fstream file;
	std::string tempLine = "ERROR";
	char formater = ' ';
	std::vector<std::vector<float>> retorno;
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
	std::cout << "debug " << toPrint.size() << std::endl;
}

// Plotear

void plotXZ(readVector input){
	BidimensionalMatrix test(input);
	plt::plot(test.getX(), test.getY());
}

// - Defecto silverstone

void plotSilverstone(){
	// Nombres archivos
	std::string trackArray[] = {"silverstone_2020_centerline.track","silverstone_2020_innerlimit.track", "silverstone_2020_outerlimit.track","silverstone_2020_racingline.track"};
	bool selCols[] = {false, true, true, false, false, false};
	//Valores de pista
	readVector centerline = readFile(SILVERPATH+trackArray[0],2,6,selCols);
	readVector innerLimit = readFile(SILVERPATH+trackArray[1],2,6,selCols);
	readVector outerLimit = readFile(SILVERPATH+trackArray[2],2,6,selCols);
	readVector raceLine   = readFile(SILVERPATH+trackArray[3],2,6,selCols);
	plotXZ(centerline);
	plotXZ(innerLimit);
	plotXZ(outerLimit);
	plotXZ(raceLine);
	plt::show();
}
