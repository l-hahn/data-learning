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
    std::vector<double> data;
    std::string Line;

    std::ifstream Input("Hidden.data");
    while(!Input.eof()){
        std::getline(Input,Line);
        data = split(Line, ' ');
        if(data.size() != 0){
            DataMat.push_back(data);
        }
    }
    Input.close();

    CovMat = mmatrix<double>::covariance(DataMat);
    std::cout << CovMat.to_string() << std::endl;
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