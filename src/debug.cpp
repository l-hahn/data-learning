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

void debug_matrix();
void debug_pca();
void debug_mds();


void split(const std::string &s, char delim, std::vector<double> &elems);
std::vector<double> split(const std::string &s, char delim);

int main(){
    //debug_matrix();
    //debug_pca();
    //debug_mds();

    return 0;
}

/*---Auxilliary---------------------------------------------------------------*/

void debug_matrix(){
    mmatrix<double> Mat1 = {{1,2,3},{4,5,6},{7,8,9}};
    mmatrix<double> Mat2 = {{0,1,2},{3,4,5},{6,7,8}};
    mmatrix<double> Vec1 = {10.0,11.0,12.0};
    std::vector<double> Vec2 = {11.0,12.0,13.0};
    double factor = 3;

    std::cout << "Matrix 1:\n" << Mat1.to_string() << "\nMatrix2:\n" << Mat2.to_string() << std::endl << std::endl;
    std::cout << "Vec 1:\n" << Vec1.to_string() << "\nVec2:\n";
    for(auto Val : Vec2){
        std::cout << Val << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "M1+ M2 : \n" << (Mat1+Mat2).to_string() << std::endl << std::endl;
    Mat1 += Mat2;
    std::cout << "M1+=M2 : \n" << Mat1.to_string() << std::endl << std::endl;
    std::cout << "M1- M2 : \n" << (Mat1-Mat2).to_string() << std::endl << std::endl;
    Mat1 -= Mat2;
    std::cout << "M1-=M2 : \n" << Mat1.to_string() << std::endl << std::endl;

    std::cout << "M1* M2 : \n" << (Mat1*Mat2).to_string() << std::endl << std::endl;
    Mat1 *= Mat2;
    std::cout << "M1* " << factor << "  : \n" << (Mat1*factor).to_string() << std::endl << std::endl;
    Mat1 *= factor;
    std::cout << "M1*=" << factor << "  : \n" << Mat1.to_string() << std::endl << std::endl;

    std::cout << "M1* V1': \n" << (Mat1*Vec1.transposition()).to_string() << std::endl << std::endl;
    std::cout << "M1* V2 : \n" << (Mat1*Vec2).to_string() << std::endl << std::endl;
    Mat1 *= Vec1.transposition();
    std::cout << "M1*=V1 : \n" << Mat1.to_string() << std::endl << std::endl; 
    Mat1.transpose();
    Mat1 *= Vec2;
    std::cout << "M1'*=V2 : \n" << Mat1.to_string() << std::endl << std::endl;

}

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