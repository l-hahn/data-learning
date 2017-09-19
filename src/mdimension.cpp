#include "mdimension.hpp"

mdimension::mdimension():_Row(0),_Col(0){
}
mdimension::mdimension(size_t Size):_Row(Size),_Col(Size){
}
mdimension::mdimension(size_t Row, size_t Col):_Row(Row),_Col(Col){
}
mdimension::mdimension(const mdimension & Dim){
    _Row = Dim._Row;
    _Col = Dim._Col;
}
mdimension::mdimension(const mdimension && Dim){
    _Row = Dim._Row;
    _Col = Dim._Col;
}


std::string mdimension::to_string() const{
    std::string Str = "[" + std::to_string(_Row) + "x"+std::to_string(_Col) + "]";
    return Str;
}

bool mdimension::empty() const{
    return ((_Row + _Col) == 0);
}

void mdimension::swap(){
    size_t Tmp = std::move(_Row);
    _Row = std::move(_Col);
    _Col = std::move(Tmp);
}


bool mdimension::operator==(const mdimension && Dim) const{
    return operator==(Dim);
}
bool mdimension::operator!=(const mdimension && Dim) const{
    return operator!=(Dim);
}
bool mdimension::operator==(const mdimension & Dim) const{
    return (_Row - Dim._Row + _Col - Dim._Col) == 0;
}
bool mdimension::operator!=(const mdimension & Dim) const{
    return (_Row - Dim._Row + _Col - Dim._Col) != 0;   
}

mdimension mdimension::operator=(const mdimension && Dim){
    return operator=(Dim);
}
mdimension mdimension::operator=(const mdimension & Dim){
    _Row = Dim._Row;
    _Col = Dim._Col;
    return *this;
    return *this;
}

mdimension mdimension::operator*(const mdimension && Dim) const{
    return operator*(Dim);
}
mdimension mdimension::operator*=(const mdimension && Dim){
    return operator*=(Dim);
}
mdimension mdimension::operator*(const mdimension & Dim) const{
    mdimension NewDim(0);
    if((_Col - Dim._Row) == 0){
        NewDim._Row = _Row;
        NewDim._Col = Dim._Col;
    }
    else{
        throw std::out_of_range("Matrix dimensions "+to_string() + " * " + Dim.to_string() + " are not conforming!");
    }
    return NewDim;
}
mdimension mdimension::operator*=(const mdimension & Dim){
    if((_Col - Dim._Row) == 0){
        _Col = Dim._Col;
    }
    else{
        throw std::out_of_range("Matrix dimensions "+to_string() + " * " + Dim.to_string() + " are not conforming!");
    }
    return *this;
}