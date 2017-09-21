#include <iostream>
#include <vector>
#include <numeric>

#include <algorithm>
#include <iterator>
#include <omp.h>

#include "mdimension.hpp"
#include "mmatrix.hpp"

int main(){


    mmatrix MatA(0), MatB(0), MatC(0);


    std::size_t Row = 4089, Col = 4089;

    for(int i = 0; i < Row; i++){
        std::vector<double> Tmp(Col,0);
        std::iota(Tmp.begin(),Tmp.end(),i);
        MatA.push_back(Tmp);
    }

    for(int i = 0; i < Col; i++){
        std::vector<double> Tmp(Row,0);
        std::iota(Tmp.begin(),Tmp.end(),i);
        MatB.push_back(Tmp);
    }


    MatC = MatA*MatB;

    //std::cout << MatC.to_string() << std::endl;
}