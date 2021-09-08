#include <iostream>
#include <fstream>
#include <ostream>
#include <cstdio>

int main(int argc, char* argv[]){

    if(argc < 2)
        return -1;

    std::string filename(argv[1]);

    std::ifstream filecsv(filename.c_str());
    std::ofstream fileout("out.csv");

    std::string line_buffer;

    while(std::getline(filecsv, line_buffer)){
        fileout << line_buffer << "\n";
        fileout << line_buffer << "\n";
        fileout << line_buffer << "\n";
    }

    filecsv.close();
    fileout.close();
    std::remove(filename.c_str());

    std::rename("out.csv", filename.c_str());

    return 0;
}