#ifndef _MDIMENSION_HPP_
#define _MDIMENSION_HPP_

/*===Libraries================================================================*/
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>

#include "mdimension.hpp"

/*===Classes-Structurres======================================================*/
class mdimension{
    public:
        // size(Mat) == _Row x _Col
        std::size_t Row;
        std::size_t Col;

    public:
        mdimension();
        mdimension(std::size_t Size);
        mdimension(std::size_t R, std::size_t C);
        mdimension(const mdimension & Dim);
        mdimension(const mdimension && Dim);

        std::string to_string() const;
        bool empty() const;
        void swap();

        bool operator==(const mdimension && Dim) const;
        bool operator!=(const mdimension && Dim) const;
        bool operator==(const mdimension & Dim) const;
        bool operator!=(const mdimension & Dim) const;

        mdimension& operator=(const mdimension && Dim);
        mdimension& operator=(const mdimension & Dim);

        mdimension operator*(const mdimension && DimL) const;
        mdimension& operator*=(const mdimension && DimL);
        mdimension operator*(const mdimension & DimL) const;
        mdimension& operator*=(const mdimension & DimL);
};


/*===Variables================================================================*/

/*===Prototypes===============================================================*/

/*===Main=====================================================================*/
mdimension::mdimension():Row(0),Col(0){
}
mdimension::mdimension(std::size_t Size):Row(Size),Col(Size){
}
mdimension::mdimension(std::size_t R, std::size_t C):Row(R),Col(C){
}
mdimension::mdimension(const mdimension & Dim){
    Row = Dim.Row;
    Col = Dim.Col;
}
mdimension::mdimension(const mdimension && Dim){
    Row = Dim.Row;
    Col = Dim.Col;
}


std::string mdimension::to_string() const{
    std::string Str = "[" + std::to_string(Row) + "x"+std::to_string(Col) + "]";
    return Str;
}

bool mdimension::empty() const{
    return ((Row + Col) == 0);
}

void mdimension::swap(){
    std::size_t Tmp = std::move(Row);
    Row = std::move(Col);
    Col = std::move(Tmp);
}


bool mdimension::operator==(const mdimension && Dim) const{
    return operator==(Dim);
}
bool mdimension::operator!=(const mdimension && Dim) const{
    return operator!=(Dim);
}
bool mdimension::operator==(const mdimension & Dim) const{
    return (Row - Dim.Row + Col - Dim.Col) == 0;
}
bool mdimension::operator!=(const mdimension & Dim) const{
    return (Row - Dim.Row + Col - Dim.Col) != 0;   
}

mdimension& mdimension::operator=(const mdimension && Dim){
    return operator=(Dim);
}
mdimension& mdimension::operator=(const mdimension & Dim){
    Row = Dim.Row;
    Col = Dim.Col;
    return *this;
}

mdimension mdimension::operator*(const mdimension && Dim) const{
    return operator*(Dim);
}
mdimension& mdimension::operator*=(const mdimension && Dim){
    return operator*=(Dim);
}
mdimension mdimension::operator*(const mdimension & Dim) const{
    mdimension NewDim(0);
    if((Col - Dim.Row) == 0){
        NewDim.Row = Row;
        NewDim.Col = Dim.Col;
    }
    else{
        throw std::out_of_range("Matrix dimensions "+to_string() + " * "
            + Dim.to_string() + " are not conforming, " + std::to_string(Col)
            + " != " +std::to_string(Dim.Row) + ".");
    }
    return NewDim;
}
mdimension& mdimension::operator*=(const mdimension & Dim){
    if((Col - Dim.Row) == 0){
        Col = Dim.Col;
    }
    else{
        throw std::out_of_range("Matrix dimensions "+to_string() + " * "
            + Dim.to_string() + " are not conforming, " + std::to_string(Col)
            + " != " +std::to_string(Dim.Row) + ".");
    }
    return *this;
}

#endif