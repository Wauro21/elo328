#include "mapGeneration.h"
// Leer archivo
std::vector<std::vector<float>> readFile(std::string nameFile, int nSkip, int nCols, bool* indexes){
	std::fstream file;
	std::string tempLine = "ERROR";
	char formater = ' ';
	std::vector<std::vector<float>> retorno;
	try{
		file.open(nameFile);
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
			retorno.push_back(tempVector);
		}
	}
	catch (const std::ifstream::failure& e){
		std::cout << "¡Archivo no encontrado!" << std::endl;
	}
	return retorno;
}

void printVector(std::vector<std::vector<float>> toPrint){
	std::cout << std::fixed;
	std::cout << std::setprecision(13);
	 for (int i = 0; i < toPrint.size(); i++) {
		for (int j = 0; j < toPrint[i].size(); j++){
			std::cout << toPrint[i][j] << '\t';
		}
		std::cout << std::endl;
	}
}

// Plotear

void 
