#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

#include "mmatrix.hpp"

int main(){
    std::size_t Row = 10000, Col = 100;

    std::vector< std::vector<int> > A,B,C;
    A = std::vector< std::vector<int> >(Row,std::vector<int>(Col,2));
    B = std::vector< std::vector<int> >(Col,std::vector<int>(Row,3));
    C = std::vector< std::vector<int> >(Row,std::vector<int>(Row,0));


    std::vector< int* > Cl(B.size());
    int **SrcR = &Cl.front();

    std::vector< int > * SVL = &A.front();
    std::vector< int > * SV = &C.front();

    for(unsigned int i = 0; i < B.size(); i++){
        SrcR[i] = &B[i].front();
    }
    for(unsigned int i = 0; i < Row; i++){
        for(unsigned int j = 0; j < Row; j++){
            int * SrcL = &SVL[i].front();
            int * Sink = &SV[i].front();
            for(unsigned int k = 0; k < Cl.size(); k++){
                Sink[j] += SrcL[k] * SrcR[k][j];
            }
        }
    }


    // mmatrix<int> A(Row,Col,2);
    // mmatrix<int> B(Col,Row,3);
    // mmatrix<int> C = A*B;
    // std::cout << C.size().to_string() << std::endl;

    std::cout << C[99][99] << std::endl;
}