#include <iostream>
#include <vector>
#include <numeric>

#include <algorithm>
#include <iterator>
#include <omp.h>

#include <functional>

#include "mdimension.hpp"
#include "mmatrix.hpp"

int main(){
    std::vector< std::vector<double> > _Matrix = {{1,2,3,4},{5,6,7,8},{9,0,1,2}};
    std::vector< std::vector<double> > _MatrixT = {{1,2,3},{4,5,6},{7,8,9},{0,1,2}};
    mmatrix MatA, MatB, MatC;

    MatA.push_back(_Matrix[0]);
    MatA.push_back(_Matrix[1]);
    MatA.push_back(_Matrix[2]);

    MatB.push_back(_MatrixT[0]);
    MatB.push_back(_MatrixT[1]);
    MatB.push_back(_MatrixT[2]);
    MatB.push_back(_MatrixT[3]);

    std::cout << MatA.to_string() << std::endl << std::endl;
    std::cout << MatB.to_string() << std::endl << std::endl;

    MatC = MatA;
    MatC *= MatB;
    std::cout << std::endl << MatC.to_string() << std::endl;
    MatC.transpose();
    std::cout << std::endl << MatC.to_string() << std::endl;
}