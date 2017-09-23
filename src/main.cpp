#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "mmatrix.hpp"

void split(const std::string &s, char delim, std::vector<double> &elems);
std::vector<double> split(const std::string &s, char delim);

int main(){
    mmatrix<double> DataMat, CovMat;
    std::ifstream Input("Hidden.data");

    std::string Line;
    std::vector<double> data;
    while(!Input.eof()){
        std::getline(Input,Line);
        data = split(Line, ' ');
        if(data.size() != 0){
            DataMat.push_back(data);
        }
    }

    CovMat = DataMat.transposition() * DataMat / DataMat.row_size();
    std::cout << CovMat.size().to_string() << std::endl;
    std::cout << CovMat.to_string() << std::endl;

    Input.close();
}

void split(const std::string &s, char delim, std::vector<double> &elems){
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if(item.empty() == false){
            elems.push_back(std::stof(item));
        }
    }
}

std::vector<double> split(const std::string &s, char delim){
    std::vector<double> elems;
    split(s, delim, elems);
    return elems;
}