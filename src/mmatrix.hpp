#ifndef _MMATRIX_HPP_
#define _MMATRIX_HPP_

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <stdexcept>
#include <vector>

#include "mdimension.hpp"

class mmatrix{
    public:
        mmatrix();
        mmatrix(size_t Row, size_t Col, double Val = 0);
        mmatrix(const mdimension & Dim, double Val = 0);
        mmatrix(const mdimension && Dim, double Val = 0);


        void push_back(const std::vector<double> && ValList, bool EnsureSize = false);
        void push_back(const std::vector<double> & ValList, bool EnsureSize = false);
        void push_back_row(const std::vector<double> && ValList, bool EnsureSize = false);
        void push_back_row(const std::vector<double> & ValList, bool EnsureSize = false);
        void push_back_col(const std::vector<double> && ValList, bool EnsureSize = false);
        void push_back_col(const std::vector<double> & ValList, bool EnsureSize = false);

        void resize(size_t NewSize, double Val = 0);
        void resize(size_t NewRow, NewCol, double Val = 0);
        void resize(const mdimension && Dim, double Val = 0);
        void resize(const mdimension & Dim, double Val = 0);

        void reserve(size_t NewSize);
        void reserve(size_t NewRow, NewCol);
        void reserve(const mdimension && Dim);
        void reserve(const mdimension & Dim);

        void clear() noexcept;


        std::vector<double>& operator[](size_t Idx);

        mmatrix& operator+=(const mmatrix && Mat);
        mmatrix& operator-=(const mmatrix && Mat);
        mmatrix& operator+=(const mmatrix & Mat);
        mmatrix& operator-=(const mmatrix & Mat);
        mmatrix& operator+=(const double Val);
        mmatrix& operator-=(const double Val);

        mmatrix& operator+(const mmatrix && Mat) const;
        mmatrix& operator-(const mmatrix && Mat) const;
        mmatrix& operator+(const mmatrix & Mat) const;
        mmatrix& operator-(const mmatrix & Mat) const;
        mmatrix& operator+(const double Val) const;
        mmatrix& operator-(const double Val) const;

        mmatrix& operator*=(const mmatrix && Mat);
        mmatrix& operator*=(const mmatrix & Mat);
        mmatrix& operator*=(const double Val);
        mmatrix& operator/=(const double Val);

        mmatrix& operator*(const mmatrix && Mat) const;
        mmatrix& operator*(const mmatrix & Mat) const;
        mmatrix& operator*(const double Val) const;
        mmatrix& operator/(const double Val) const;

        mmatrix& operator=(const mmatrix && Mat);
        mmatrix& operator=(const mmatrix & Mat);


        mmatrix& transpose() const;
        mmatrix& entry_mult(const mmatrix && Mat);
        mmatrix& entry_mult(const mmatrix & Mat);
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