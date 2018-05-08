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
void operators();
void static_operations();
void static_norms();
void thread();  


/*===Main=====================================================================*/
int main(){
    constructors();
    operators();
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
}

void operators(){
    mmatrix<double> MatrixHc = {{1,2,3},{4,5,6},{7,8,9}};
    mmatrix<double> MatrixHcV = {10,11,12};
    mmatrix<double> MatrixDef;
    mmatrix<double> MatrixDim(MatrixHc.size());
    mmatrix<double> MatrixVec(MatrixHcV[0]);
    mmatrix<double> MatrixCopy(MatrixHc);

    MatrixDef.push_back(MatrixHcV[0]);
    for(auto Vec : MatrixHc){
        MatrixDef.push_back(Vec);
    }
    
    for(std::size_t i = 0; i < MatrixHc.row_size(); i++){
        for(std::size_t j = 0; j < MatrixHc.col_size(); j++){
            assert(MatrixDim[i][j] == 0.0);
            MatrixDim[i][j] = MatrixHc[i][j];
        }
    }

    std::cout << "MatrixCopy: \n" << MatrixCopy.to_string() << std::endl << std::endl;   
    std::cout << "MatrixDim: \n" << MatrixDim.to_string() << std::endl << std::endl;   
    std::cout << "MatrixHc: \n" << MatrixHc.to_string() << std::endl << std::endl;   
    std::cout << "MatrixDef: \n" << MatrixDef.to_string() << std::endl << std::endl;
    std::cout << "MatrixHcV: \n" << MatrixHcV.to_string() << std::endl << std::endl;
    std::cout << "MatrixVec: \n" << MatrixVec.to_string() << std::endl << std::endl;



    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\t1) Matrix */ Matrix Multiplication\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    MatrixCopy = MatrixCopy * MatrixDim;
    std::cout << "MatrixCopy = MatrixCopy * MatrixDim: \n" << MatrixCopy.to_string() << std::endl << std::endl;   
    MatrixCopy = MatrixCopy * MatrixHc;
    std::cout << "MatrixCopy = MatrixCopy * MatrixHc: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy * MatrixVec.transposition();
    std::cout << "MatrixCopy = MatrixCopy * MatrixVec': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy * MatrixCopy.transposition()/1000000;
    std::cout << "MatrixCopy = MatrixCopy * MatrixCopy'/1000000: \n" << MatrixCopy.to_string() << std::endl << std::endl;




    MatrixCopy = mmatrix<double>(MatrixHc);
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\t2) Matrix */= Matrix Multiplication\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    MatrixCopy *= MatrixDim;
    std::cout << "MatrixCopy *= MatrixDim: \n" << MatrixCopy.to_string() << std::endl << std::endl;   
    MatrixCopy *= MatrixHc;
    std::cout << "MatrixCopy *= MatrixHc: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy *= MatrixVec.transposition();
    std::cout << "MatrixCopy *= MatrixVec': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy *= MatrixCopy.transposition()/1000000;
    std::cout << "MatrixCopy *= MatrixCopy'/1000000: \n" << MatrixCopy.to_string() << std::endl << std::endl;




    MatrixCopy = mmatrix<double>(MatrixHc);
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\t3) Matrix +- Matrix Addition\t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    MatrixCopy = MatrixCopy*MatrixCopy.transposition() + MatrixCopy*MatrixCopy.transposition();
    std::cout << "MatrixCopy = MatrixCopy*MatrixCopy' + MatrixCopy*MatrixCopy': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy+MatrixHc;
    std::cout << "MatrixCopy = MatrixCopy+MatrixHc: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy*MatrixVec.transposition()+MatrixVec.transposition();
    std::cout << "MatrixCopy = MatrixCopy*MatrixVec' + MatrixVec': \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy.transposition()-MatrixVec;
    std::cout << "MatrixCopy = MatrixCopy'-MatrixVec: \n" << MatrixCopy.to_string() << std::endl << std::endl;
    MatrixCopy = MatrixCopy.transposition()*MatrixVec - MatrixHc;
    std::cout << "MatrixCopy = MatrixCopy'*MatrixVec - MatrixHc: \n" << MatrixCopy.to_string() << std::endl << std::endl;

}