#include <iostream>
#include <vector>
#include <numeric>

#include <algorithm>
#include <iterator>
#include <omp.h>

#include "mdimension.hpp"
#include "mmatrix.hpp"

int main(){
    std::vector<double> A = {1,2,3}, B = {4,5,6};
    std::vector<double> C = {1,2}, D = {3,4}, E = {5,6};

    mmatrix MatA(0), MatB(0), MatC(0);
    MatA.push_back(A);
    MatA.push_back(B);

    MatB.push_back(C);
    MatB.push_back(D);
    MatB.push_back(E);


    std::cout << MatA.to_string() << std::endl;
    std::cout << MatB.to_string() << std::endl;

    MatC = MatB*MatA;

    std::cout << MatC.to_string() << std::endl;
}