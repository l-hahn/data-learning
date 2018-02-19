/*===Libraries================================================================*/
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "../src/mmatrix.hpp"

/*===Classes-Structurres======================================================*/

/*===Variables================================================================*/

/*===Prototypes===============================================================*/
void constructors();
void push_back();
void memory();
void operator();
void static_operations();
void static_norms();
void thread();  


/*===Main=====================================================================*/
int main(){
    constructors();
}

/**
 * Check if constructors are working and modification is still possible.
 */
void constructors(){
    mmatrix<double> MatrixHc = {{1,2,3},{4,5,6},{7,8,9}};
    mmatrix<double> MatrixHcV = {10,11,12};
    mmatrix<double> MatrixDef;
    mmatrix<double> MatrixDim1(MatrixHc.size());
    mmatrix<double> MatrixDim2(MatrixHc.row_size(),MatrixHc.col_size());
    mmatrix<double> MatrixVec(MatrixHcV[0]);
    mmatrix<double> MatrixVecVec(MatrixHc.vector_matrix());
    mmatrix<double> MatrixCopy(MatrixHc);

    MatrixDef.push_back(MatrixHcV[0]);
    for(auto Vec : MatrixHc){
        MatrixDef.push_back(Vec);
    }
    
    for(std::size_t i = 0; i < MatrixHc.row_size(); i++){
        for(std::size_t j = 0; j < MatrixHc.col_size(); j++){
            assert(MatrixDim1[i][j] == 0.0);
            MatrixDim1[i][j] = MatrixHc[i][j];
            MatrixDim2[i][j] = MatrixHc[i][j];
        }
    }
    
    MatrixCopy *= MatrixVecVec;
    
    MatrixCopy *= MatrixDim2;
    
    MatrixCopy *= MatrixDim1;
    
    MatrixCopy *= MatrixHc;
    
    MatrixDef *= MatrixCopy;
    
    MatrixDef *= MatrixHcV.transposition();
    
    MatrixDef *= MatrixVec;
    
}
