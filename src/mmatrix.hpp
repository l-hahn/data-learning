#ifndef _MMATRIX_HPP_
#define _MMATRIX_HPP_

#include <cstdlib>
#include <iterator>
#include <vector>

#include "mdimension.hpp"

class mmatrix{
    public:
        mmatrix();
        mmatrix(size_t Row, size_t Col, double Val = 0);
        mmatrix(mdimension & Dim, double Val = 0);
        mmatrix(mdimension && Dim, double Val = 0);


        void push_back(double Val);
        void push_back_row(double Val);
        void push_back_col(double Val);
        void push_back(std::vector<double> & ValList);
        void push_back(std::vector<double> && ValList);
        void push_back_row(std::vector<double> & ValList);
        void push_back_row(std::vector<double> && ValList);
        void push_back_col(std::vector<double> & ValList);
        void push_back_col(std::vector<double> && ValList);


        std::vector<double>& operator[](size_t Idx);

        mmatrix& operator+=(const mmatrix & Mat);
        mmatrix& operator-=(const mmatrix & Mat);
        mmatrix& operator+=(const mmatrix && Mat);
        mmatrix& operator-=(const mmatrix && Mat);
        mmatrix& operator+=(const double Val);
        mmatrix& operator-=(const double Val);

        mmatrix& operator+(const mmatrix & MatL, const mmatrix & MatR) const;
        mmatrix& operator-(const mmatrix & MatL, const mmatrix & MatR) const;
        mmatrix& operator+(const mmatrix && MatL, const mmatrix && MatR) const;
        mmatrix& operator-(const mmatrix && MatL, const mmatrix && MatR) const;
        mmatrix& operator+(const mmatrix && MatL, const double Val) const;
        mmatrix& operator-(const mmatrix && MatL, const double Val) const;
        mmatrix& operator+(const double Val, const mmatrix && MatL) const;
        mmatrix& operator-(const double Val, const mmatrix && MatL) const;

        mmatrix& operator*=(const mmatrix & Mat);
        mmatrix& operator*=(const mmatrix && Mat);
        mmatrix& operator*=(const double Val);
        mmatrix& operator/=(const double Val);

        mmatrix& operator*(const mmatrix & MatL, const mmatrix & MatR) const;
        mmatrix& operator*(const mmatrix && MatL, const mmatrix && MatR) const;
        mmatrix& operator*(const mmatrix && MatL, const double Val) const;
        mmatrix& operator/(const mmatrix && MatL, const double Val) const;
        mmatrix& operator*(const double Val, const mmatrix && MatL) const;
        mmatrix& operator/(const double Val, const mmatrix && MatL) const;


        mmatrix& transpose();
        mmatrix& entry_add();
        mmatrix& entry_mult();
        mmatrix& eigen_vectors() const;
        std::vector<double> eigen_values() const;

        mdimension dimension() const;
        mdimension size() const;
        size_t row_size() const;
        size_t col_size() const;



    private:
        std::vector< std::vector<double> > _Matrix
        mdimension _Dimensions;
};

#endif