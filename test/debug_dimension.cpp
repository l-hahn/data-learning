/*===Libraries================================================================*/
#include <iostream>
#include <vector>
#include <string>

#include "../src/mdimension.hpp"

/*===Classes-Structurres======================================================*/

/*===Variables================================================================*/

/*===Prototypes===============================================================*/
void constructors();
void operators();


/*===Main=====================================================================*/
int main(){
    constructors();
    operators();
}


/**
 * Check if constructors are working and modification is still possible.
 */
void constructors(){
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tA) Dimension Constructors \t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    mdimension DimEmpt;
    std::cout << "DimHc: " << DimEmpt.to_string() << std::endl << std::endl; 
    mdimension DimSq1(10);
    std::cout << "DimSq1(10): " << DimSq1.to_string() << std::endl << std::endl;
    mdimension DimSq2(2,5);
    std::cout << "DimSq2(10): " << DimSq2.to_string() << std::endl << std::endl; 
    mdimension DimDef;
    DimDef.Row = 4;
    DimDef.Col = 5;
    std::cout << "DimDef: " << DimDef.to_string() << std::endl;
    mdimension DimCopy(DimDef);
    std::cout << "DimDCopy(DimDef): " << DimCopy.to_string() << std::endl;
    DimCopy = DimSq1;
    std::cout << "DimCopy = DimSq1: " << DimCopy.to_string() << std::endl;
}

void operators(){
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tB) Dimension Operations \t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;
    mdimension DimEmpt;
    mdimension DimSq(2,5);
    mdimension DimDef(5,2);
    mdimension DimCopy(DimDef);

  
    std::cout << "DimEmpt: " << DimEmpt.to_string() << std::endl << std::endl;   
    std::cout << "DimDef: " << DimDef.to_string() << std::endl << std::endl;
    std::cout << "DimSq: " << DimSq.to_string() << std::endl << std::endl;
    std::cout << "DimCopy: " << DimCopy.to_string() << std::endl << std::endl;


    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tB1) Unary Operations\t\t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    DimDef.swap();
    std::cout << "DimCopy.swap() = " << DimCopy.to_string() << std::endl << std::endl;   
    std::cout << "DimCopy.empty = " << DimCopy.empty() << std::endl << std::endl;



    DimCopy = mdimension(DimDef);
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tB2) Boolean Operations\t\t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    std::cout << "DimDef == DimCopy: " << (DimDef == DimCopy) << std::endl << std::endl;   
    std::cout << "DimCopy != DimEmpt: " << (DimCopy != DimEmpt) << std::endl << std::endl;



    DimCopy = mdimension(DimDef);
    std::cout << std::endl << std::string(80,'#') << std::endl;
    std::cout << "#\t\tB3) Multiplication\t\t\t\t\t       #" << std::endl;
    std::cout << std::string(80,'#') << std::endl << "Reset\n" << std::endl;

    DimSq.swap();
    DimCopy = DimDef * DimSq;
    std::cout << "DimCopy = DimDef * DimSq.swap() \n" << DimCopy.to_string() << std::endl << std::endl;
    DimSq *= DimCopy;
    std::cout << "DimSq *= DimCopy: \n" << DimSq.to_string() << std::endl << std::endl;
}