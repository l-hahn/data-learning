/*===Libraries================================================================*/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <omp.h>

#include "../src/mmatrix.hpp"
#include "../src/mining.hpp"
#include "../src/learning.hpp"
#include "../src/clustering.hpp"

/*===Classes-Structurres======================================================*/

/*===Variables================================================================*/

/*===Prototypes===============================================================*/
void debug_kmeans();
void debug_pca();
void debug_mds();

void split(const std::string &s, char delim, std::vector<double> &elems);
std::vector<double> split(const std::string &s, char delim);


/*===Main=====================================================================*/
int main(){
    //debug_kmeans();
    //debug_matrix();
    debug_pca();
    //debug_mds();

    return 0;
}


/*---clustering-------------------------------------------------------------*/
void debug_kmeans(){
    mmatrix<double> DataMat;
    std::vector<double> data;
    std::string Line;
    std::size_t K;

    std::ifstream Input("data-test/Cluster.dat");
    if(Input.is_open()){
        while(std::getline(Input,Line)){
            if(Line.size() != 0){
                data = split(Line, ' ');
                DataMat.push_back(data);
            }
        }
    }
    Input.close();

    K = 4;
    data_learning::clustering::kmeans<double> KMeans = data_learning::clustering::kmeans<double>(DataMat,K);

    std::ofstream Output("data-test/Cls_ErrDev.dat"); 
    std::vector<double> ErrDev = KMeans.clustering();
    for(std::size_t i = 0; i < ErrDev.size(); i++){
        Output << ErrDev[i] << std::endl;
    }
    Output.close();

    Output = std::ofstream("data-test/clustered.dat"); 
    std::vector< mmatrix<double> > Clusters = KMeans.clusters();
    for(std::size_t i = 0; i < Clusters.size(); i++){
        Output << Clusters[i].to_string() << std::endl << std::endl;
    }
    Output.close();
}



/*---data-mining------------------------------------------------------------*/
void debug_pca(){
    mmatrix<double> DataMat, EigSpec, PrinComp, EigenVectors;
    std::vector<double> data;
    std::string Line;

    std::ifstream Input("test_data/Hidden2.dat");
    while(!Input.eof()){
        std::getline(Input,Line);
        data = split(Line, ' ');
        if(data.size() != 0){
            DataMat.push_back(data);
        }
    }
    Input.close();
    
    data_learning::mining::pca<double> PCA = data_learning::mining::pca<double>(DataMat);

    unsigned EigNumb = 10;


    std::ofstream Output("test_data/EigenSpectum_PCA.dat"); 
    EigSpec = PCA.eigen_spectrum();
    for(unsigned i = 0; i < EigSpec.col_size(); i++){
        Output << EigSpec[0][i] << std::endl;
    }
    Output.close();

    Output = std::ofstream("test_data/PrincipleComponents_PCA.dat");
    PrinComp = PCA.principle_components(EigNumb);
    for(unsigned i = 0; i < PrinComp.row_size(); i++){
        for(unsigned j = 0; j < PrinComp.col_size()-1; j++){
            Output << PrinComp[i][j] << "\t";
        }
        Output << PrinComp[i][PrinComp.col_size()-1] << std::endl;
    }
    Output.close();

    Output = std::ofstream("test_data/Loadings_PCA.dat");
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

    std::ifstream Input("data-test/Hidden.dat");
    while(!Input.eof()){
        std::getline(Input,Line);
        data = split(Line, ' ');
        if(data.size() != 0){
            DataMat.push_back(data);
        }
    }
    Input.close();

    data_learning::mining::mds<double> MDS = data_learning::mining::mds<double>(DataMat);

    std::ofstream Output("data-test/EigenSpectum_MDS.dat"); 
    EigSpec = MDS.eigen_spectrum(2);
    for(unsigned i = 0; i < EigSpec.col_size(); i++){
        Output << EigSpec[0][i] << std::endl;
    }
    Output.close();

    Output = std::ofstream("data-test/PrincipleComponents_MDS.dat");
    PrinComp = MDS.principle_components(2);
    for(unsigned i = 0; i < PrinComp.row_size(); i++){
        for(unsigned j = 0; j < PrinComp.col_size()-1; j++){
            Output << PrinComp[i][j] << "\t";
        }
        Output << PrinComp[i][PrinComp.col_size()-1] << std::endl;
    }
    Output.close();
}

/*---Auxilliary---------------------------------------------------------------*/


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
