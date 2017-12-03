#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <omp.h>

#include "../lib/mmatrix.hpp"
#include "../lib/mining.hpp"
#include "../lib/learning.hpp"
#include "../lib/clustering.hpp"

void debug_pca();
void debug_mds();


void split(const std::string &s, char delim, std::vector<double> &elems);
std::vector<double> split(const std::string &s, char delim);

int main(){
    //debug_pca();
    //debug_mds();

    return 0;
}

/*---Auxilliary---------------------------------------------------------------*/

void debug_pca(){
    mmatrix<double> DataMat, EigSpec, PrinComp, EigenVectors;
    std::vector<double> data;
    std::string Line;

    std::ifstream Input("test-data/Hidden2.dat");
    while(!Input.eof()){
        std::getline(Input,Line);
        data = split(Line, ' ');
        if(data.size() != 0){
            DataMat.push_back(data);
        }
    }
    Input.close();
    
    data_learning::mining::pca<double> PCA = data_learning::mining::pca<double>(DataMat);

    unsigned EigNumb = 2;

    std::ofstream Output("test-data/EigenSpectum_PCA.dat"); 
    EigSpec = PCA.eigen_spectrum();
    for(unsigned i = 0; i < EigSpec.col_size(); i++){
        Output << EigSpec[0][i] << std::endl;
    }
    Output.close();

    Output = std::ofstream("test-data/PrincipleComponents_PCA.dat");
    PrinComp = PCA.principle_components(EigNumb);
    for(unsigned i = 0; i < PrinComp.row_size(); i++){
        for(unsigned j = 0; j < PrinComp.col_size()-1; j++){
            Output << PrinComp[i][j] << "\t";
        }
        Output << PrinComp[i][PrinComp.col_size()-1] << std::endl;
    }
    Output.close();

    Output = std::ofstream("test-data/Loadings_PCA.dat");
    EigenVectors = PCA.loadings();
    for(unsigned i = 0; i < EigenVectors.row_size(); i++){
        for(unsigned j = 0; j < EigenVectors.col_size()-1; j++){
            Output << EigenVectors[i][j] << "\t";
        }
        Output << EigenVectors[i][EigenVectors.col_size()-1] << std::endl;
    }
    Output.close();
}

void debug_mds(){
    mmatrix<double> DataMat, EigSpec, PrinComp;
    std::vector<double> data;
    std::string Line;
    
    mmatrix<double>::thread(4);

    std::ifstream Input("test-data/Hidden2.dat");
    while(!Input.eof()){
        std::getline(Input,Line);
        data = split(Line, ' ');
        if(data.size() != 0){
            DataMat.push_back(data);
        }
    }
    Input.close();

    data_learning::mining::mds<double> MDS = data_learning::mining::mds<double>(DataMat);

    std::ofstream Output("test-data/EigenSpectum_MDS.dat"); 
    EigSpec = MDS.eigen_spectrum(2);
    for(unsigned i = 0; i < EigSpec.col_size(); i++){
        Output << EigSpec[0][i] << std::endl;
    }
    Output.close();

    Output = std::ofstream("test-data/PrincipleComponents_MDS.dat");
    PrinComp = MDS.principle_components(2);
    for(unsigned i = 0; i < PrinComp.row_size(); i++){
        for(unsigned j = 0; j < PrinComp.col_size()-1; j++){
            Output << PrinComp[i][j] << "\t";
        }
        Output << PrinComp[i][PrinComp.col_size()-1] << std::endl;
    }
    Output.close();
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