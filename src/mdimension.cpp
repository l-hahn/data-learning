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

void swap(){
    size_t Tmp = std::move(_Row);
    _Row = std::move(_Col);
    _Col = std::move(Tmp);
}