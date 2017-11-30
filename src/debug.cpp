#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "../lib/mmatrix.hpp"
#include "../lib/mining.hpp"
#include "../lib/learning.hpp"
#include "../lib/clustering.hpp"

void split(const std::string &s, char delim, std::vector<double> &elems);
std::vector<double> split(const std::string &s, char delim);

int main(){
    mmatrix<double> DataMat, EigSpec, PrinComp, EigenVectors;
    std::vector<double> data;
    std::string Line;

    std::ifstream Input("test-data/Hidden.dat");
    while(!Input.eof()){
        std::getline(Input,Line);
        data = split(Line, ' ');
        if(data.size() != 0){
            DataMat.push_back(data);
        }
    }
    Input.close();
    
    std::ofstream Output("test-data/EigenSpectum.dat"); 
    data_learning::mining::pca<double> PCA = data_learning::mining::pca<double>(DataMat);
    EigSpec = PCA.eigen_spectrum();
    for(unsigned i = 0; i < EigSpec.col_size(); i++){
        Output << EigSpec[0][i] << std::endl;
    }
    Output.close();

    Output = std::ofstream("test-data/PrincipleComponents.dat");
    PrinComp = PCA.principle_components();
    for(unsigned i = 0; i < PrinComp.row_size(); i++){
        for(unsigned j = 0; j < PrinComp.col_size()-1; j++){
            Output << PrinComp[i][j] << "\t";
        }
        Output << PrinComp[i][PrinComp.col_size()-1] << std::endl;
    }
    Output.close();

    Output = std::ofstream("test-data/Loadings.dat");
    EigenVectors = PCA.loadings();
    for(unsigned i = 0; i < EigenVectors.row_size(); i++){
        for(unsigned j = 0; j < EigenVectors.col_size()-1; j++){
            Output << EigenVectors[i][j] << "\t";
        }
        Output << EigenVectors[i][EigenVectors.col_size()-1] << std::endl;
    }
    Output.close();

    return 0;
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