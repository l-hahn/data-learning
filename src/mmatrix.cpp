#include "mmatrix.hpp"

mmatrix::mmatrix(){

}
mmatrix::mmatrix(size_t Row, size_t Col, double Val = 0){

}
mmatrix::mmatrix(const mdimension & Dim, double Val = 0){

}
mmatrix::mmatrix(const mdimension && Dim, double Val = 0){

}


void mmatrix::push_back(double Val){

}
void mmatrix::push_back_row(double Val){

}
void mmatrix::push_back_col(double Val){

}
void mmatrix::push_back(const std::vector<double> & ValList){

}
void mmatrix::push_back(const std::vector<double> && ValList){

}
void mmatrix::push_back_row(const std::vector<double> & ValList){

}
void mmatrix::push_back_row(const std::vector<double> && ValList){

}
void mmatrix::push_back_col(const std::vector<double> & ValList){

}
void mmatrix::push_back_col(const std::vector<double> && ValList){

}

void mmatrix::resize(size_t NewSize, double Val = 0){

}
void mmatrix::resize(size_t NewRow, NewCol, double Val = 0){

}
void mmatrix::resize(const mdimension && Dim, double Val = 0){

}
void mmatrix::resize(const mdimension & Dim, double Val = 0){

}

void mmatrix::reserve(size_t NewSize){

}
void mmatrix::reserve(size_t NewRow, NewCol){

}
void mmatrix::reserve(const mdimension && Dim){

}
void mmatrix::reserve(const mdimension & Dim){

}

void mmatrix::clear() noexcept{

}


std::vector<double>& mmatrix::operator[](size_t Idx){

}

mmatrix& mmatrix::operator+=(const mmatrix && Mat){

}
mmatrix& mmatrix::operator-=(const mmatrix && Mat){

}
mmatrix& mmatrix::operator+=(const mmatrix & Mat){

}
mmatrix& mmatrix::operator-=(const mmatrix & Mat){

}
mmatrix& mmatrix::operator+=(const double Val){

}
mmatrix& mmatrix::operator-=(const double Val){

}

mmatrix& mmatrix::operator+(const mmatrix && Mat) const{

}
mmatrix& mmatrix::operator-(const mmatrix && Mat) const{

}
mmatrix& mmatrix::operator+(const mmatrix & Mat) const{

}
mmatrix& mmatrix::operator-(const mmatrix & Mat) const{

}
mmatrix& mmatrix::operator+(const double Val) const{

}
mmatrix& mmatrix::operator-(const double Val) const{

}

mmatrix& mmatrix::operator*=(const mmatrix && Mat){

}
mmatrix& mmatrix::operator*=(const mmatrix & Mat){

}
mmatrix& mmatrix::operator*=(const double Val){

}
mmatrix& mmatrix::operator/=(const double Val){

}

mmatrix& mmatrix::operator*(const mmatrix && Mat) const{

}
mmatrix& mmatrix::operator*(const mmatrix & Mat) const{

}
mmatrix& mmatrix::operator*(const double Val) const{

}
mmatrix& mmatrix::operator/(const double Val) const{

}

mmatrix& mmatrix::operator=(const mmatrix && Mat){

}
mmatrix& mmatrix::operator=(const mmatrix & Mat){

}


mmatrix& mmatrix::transpose() const{

}
mmatrix& mmatrix::entry_mult(const mmatrix && Mat){

}
mmatrix& mmatrix::entry_mult(const mmatrix & Mat){

}
mmatrix& mmatrix::eigen_vectors() const{

}
std::vector<double> mmatrix::eigen_values() const{

}

mdimension mmatrix::dimension() const{

}
mdimension mmatrix::size() const{

}
size_t mmatrix::row_size() const{

}
size_t mmatrix::col_size() const{

}