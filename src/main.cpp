#include <iostream>
#include <vector>
#include <numeric>

#include "mdimension.hpp"
#include "mmatrix.hpp"

int main(){
    std::size_t Row = 1000, Col = 1000;
    mdimension Dim(Row,Col);
    mmatrix Mat(Dim,0), MatR;
    for(int i = 0; i < Row; i++){
        std::vector<double> MRow(Col,0);
        std::iota(MRow.begin(), MRow.end(),i);
        Mat[i] = MRow;
    }
    MatR = Mat+Mat;
}