#ifndef _MMATRIX_HPP_
#define _MMATRIX_HPP_

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <numeric>
#include <omp.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "mdimension.hpp"

template<typename T = double>
class mmatrix{
    private:
        std::vector< std::vector<T> > _Matrix;
        mdimension _Dimensions;

    public:
        mmatrix();
        mmatrix(size_t Row, size_t Col, T Val=T());
        mmatrix(const mdimension & Dim, T Val=T());
        mmatrix(const mdimension && Dim, T Val=T());
        mmatrix(const mmatrix<T> && Mat);
        mmatrix(const mmatrix<T> & Mat);
        mmatrix(const std::vector<T> && Mat);
        mmatrix(const std::vector<T> & Mat);


        void push_back(const std::vector<T> && ValList, bool EnsureSize = false);
        void push_back(const std::vector<T> & ValList, bool EnsureSize = false);
        void push_back_row(const std::vector<T> && ValList, bool EnsureSize = false);
        void push_back_row(const std::vector<T> & ValList, bool EnsureSize = false);
        void push_back_col(const std::vector<T> && ValList, bool EnsureSize = false);
        void push_back_col(const std::vector<T> & ValList, bool EnsureSize = false);

        void resize(size_t NewSize, T Val=T());
        void resize(size_t NewRow, size_t NewCol, T Val=T());
        void resize(const mdimension && Dim, T Val=T());
        void resize(const mdimension & Dim, T Val=T());

        void reserve(size_t NewSize);
        void reserve(size_t NewRow, size_t NewCol);
        void reserve(const mdimension && Dim);
        void reserve(const mdimension & Dim);

        void clear() noexcept;


        std::vector<T>& operator[](size_t Idx);

        mmatrix<T>& operator+=(mmatrix<T> && Mat);
        mmatrix<T>& operator-=(mmatrix<T> && Mat);
        mmatrix<T>& operator+=(mmatrix<T> & Mat);
        mmatrix<T>& operator-=(mmatrix<T> & Mat);
        mmatrix<T>& operator+=(std::vector<T> && Mat);
        mmatrix<T>& operator-=(std::vector<T> && Mat);
        mmatrix<T>& operator+=(std::vector<T> & Mat);
        mmatrix<T>& operator-=(std::vector<T> & Mat);
        mmatrix<T>& operator+=(const T Val);
        mmatrix<T>& operator-=(const T Val);

        mmatrix<T> operator+(mmatrix<T> && Mat);
        mmatrix<T> operator-(mmatrix<T> && Mat);
        mmatrix<T> operator+(mmatrix<T> & Mat);
        mmatrix<T> operator-(mmatrix<T> & Mat);
        mmatrix<T> operator+(std::vector<T> && Mat);
        mmatrix<T> operator-(std::vector<T> && Mat);
        mmatrix<T> operator+(std::vector<T> & Mat);
        mmatrix<T> operator-(std::vector<T> & Mat);
        mmatrix<T> operator+(const T Val);
        mmatrix<T> operator-(const T Val);

        mmatrix<T>& operator*=(mmatrix<T> && Mat);
        mmatrix<T>& operator*=(mmatrix<T> & Mat);
        mmatrix<T>& operator*=(std::vector<T> && Mat);
        mmatrix<T>& operator*=(std::vector<T> & Mat);
        mmatrix<T>& operator*=(const T Val);
        mmatrix<T>& operator/=(const T Val);

        mmatrix<T> operator*(mmatrix<T> && Mat);
        mmatrix<T> operator*(mmatrix<T> & Mat);
        mmatrix<T> operator*(std::vector<T> && Mat);
        mmatrix<T> operator*(std::vector<T> & Mat);
        mmatrix<T> operator*(const T Val);
        mmatrix<T> operator/(const T Val);

        mmatrix<T>& operator=(const mmatrix<T> && Mat);
        mmatrix<T>& operator=(const mmatrix<T> & Mat);


        mmatrix<T> transposition();
        void transpose();
        mmatrix<T> entry_mult(mmatrix<T> && Mat);
        mmatrix<T> entry_mult(mmatrix & Mat);
        mmatrix<T>& equal_entry_mult(mmatrix<T> && Mat);
        mmatrix<T>& equal_entry_mult(mmatrix<T> & Mat);

        std::string to_string(char Delimiter = ' ', char Separator = '\n', char Border = 0);

        mdimension dimension() const;
        mdimension size() const;
        size_t row_size() const;
        size_t col_size() const;

        typedef typename std::vector<T>::iterator iterator;
        iterator begin();
        iterator end();

        static mmatrix<T> covariance(mmatrix<T> && Mat);
        static mmatrix<T> covariance(mmatrix<T> & Mat);
        static meigen<T> eigen(mmatrix<T> && Mat, unsigned VecNo = 0);
        static meigen<T> eigen(mmatrix<T> & Mat, unsigned VecNo = 0);

        static T vector_norm(mmatrix<T> && Vector, unsigned Norm = 2);
        static T vector_norm(mmatrix<T> & Vector, unsigned Norm = 2);
        static T vector_norm(mmatrix<T> && Vector, std::function<T(mmatrix<T>)> const& Norm);
        static T vector_norm(mmatrix<T> & Vector, std::function<T(mmatrix<T>)> const& Norm);

        static const std::function<T(mmatrix<T>)> euclid;
        static const std::function<T(mmatrix<T>)> taxicap;


    private:
        static T l_p_norm(mmatrix<T> & Matrix, unsigned Norm);
        static T eucl_norm(mmatrix<T> & Matrix);
        static T taxicap_Norm(mmatrix<T> & Matrix);
};

template<typename T>
mmatrix<T>::mmatrix(){
    _Dimensions = mdimension(0);
}
template<typename T>
mmatrix<T>::mmatrix(size_t Row, size_t Col, T Val){
    resize(Row,Col,Val);
}
template<typename T>
mmatrix<T>::mmatrix(const mdimension & Dim, T Val){
    resize(Dim,Val);
}
template<typename T>
mmatrix<T>::mmatrix(const mdimension && Dim, T Val){
    resize(Dim,Val);
}
template<typename T>
mmatrix<T>::mmatrix(const mmatrix<T> && Mat){
    _Matrix = Mat._Matrix;
    _Dimensions = Mat._Dimensions;

}
template<typename T>
mmatrix<T>::mmatrix(const mmatrix<T> & Mat){
    _Matrix = Mat._Matrix;
    _Dimensions = Mat._Dimensions;
}

template<typename T>
mmatrix<T>::mmatrix(const std::vector<T> && Mat){
    resize(1,Mat.size());
    push_back(Mat);
}

template<typename T>
mmatrix<T>::mmatrix(const std::vector<T> & Mat){
    resize(1,Mat.size());
    push_back(Mat);
}


template<typename T>
void mmatrix<T>::push_back(const std::vector<T> && Mat, bool EnsureSize){
    push_back(Mat, EnsureSize);
}
template<typename T>
void mmatrix<T>::push_back(const std::vector<T> & Mat, bool EnsureSize){
    push_back_row(Mat,EnsureSize);
}
template<typename T>
void mmatrix<T>::push_back_row(const std::vector<T> && Mat, bool EnsureSize){
    push_back_row(Mat, EnsureSize);
}
template<typename T>
void mmatrix<T>::push_back_row(const std::vector<T> & Mat, bool EnsureSize){
    if(_Dimensions.Col != Mat.size() && _Dimensions.Col != 0){
        throw std::out_of_range("Matrix col-dimensions "+ _Dimensions.to_string()
            + " and [1x" + std::to_string(Mat.size()) + "] are not conforming.");
    }
    if( _Dimensions.Col == 0){
        _Dimensions.Col = Mat.size();
    }
    _Matrix.push_back(Mat);
    _Dimensions.Row++;
}
template<typename T>
void mmatrix<T>::push_back_col(const std::vector<T> && Mat, bool EnsureSize){
    push_back_col(Mat, EnsureSize);
}
template<typename T>
void mmatrix<T>::push_back_col(const std::vector<T> & Mat, bool EnsureSize){
    if(_Dimensions.Row != Mat.size() && _Dimensions.Row != 0){
        throw std::out_of_range("Matrix row-dimensions "+ _Dimensions.to_string()
            + " and [1x" + std::to_string(Mat.size()) + "] are not conforming.");
    }
    if(_Dimensions.Row == 0){
        _Dimensions.Row = Mat.size();
        _Matrix.resize(Mat.size());
    }
    std::transform(_Matrix.begin(),_Matrix.end(),Mat.begin(),_Matrix.begin(),[](std::vector<T> & Vec, T Val){
        Vec.push_back(Val);
        return Vec;
    });
    _Dimensions.Col++;
}

template<typename T>
void mmatrix<T>::resize(size_t NewSize, T Val){
    resize(mdimension(NewSize,NewSize),Val);
}
template<typename T>
void mmatrix<T>::resize(size_t NewRow, size_t NewCol, T Val){
    resize(mdimension(NewRow,NewCol),Val);
}
template<typename T>
void mmatrix<T>::resize(const mdimension && Dim, T Val){
    resize(Dim,Val);
}
template<typename T>
void mmatrix<T>::resize(const mdimension & Dim, T Val){
    _Matrix.resize(Dim.Row);
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[&Dim, Val](std::vector<T> & Vec){
        Vec.resize(Dim.Col,Val);
        return Vec;
    });
    _Dimensions = Dim;
}

template<typename T>
void mmatrix<T>::reserve(size_t NewSize){
    reserve(mdimension(NewSize,NewSize));
}
template<typename T>
void mmatrix<T>::reserve(size_t NewRow, size_t NewCol){
    reserve(mdimension(NewRow,NewCol));
}
template<typename T>
void mmatrix<T>::reserve(const mdimension && Dim){
    reserve(Dim);
}
template<typename T>
void mmatrix<T>::reserve(const mdimension & Dim){
    _Matrix.reserve(Dim.Row);
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[&Dim](std::vector<T> & Vec){
        Vec.reserve(Dim.Col);
        return Vec;
    });
}

template<typename T>
void mmatrix<T>::clear() noexcept{
    _Matrix.clear();
    _Dimensions = mdimension(0);
}


template<typename T>
std::vector<T>& mmatrix<T>::operator[](size_t Idx){
    return _Matrix[Idx];
}

template<typename T>
mmatrix<T>& mmatrix<T>::operator+=(mmatrix<T> && Mat){
    return operator+=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(mmatrix<T> && Mat){
    return operator-=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator+=(mmatrix<T> & Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    std::vector<T> * RowsL = &_Matrix.front();
    std::vector<T> * RowsR = &Mat._Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * ValsR = &RowsR[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            ValsL[j] += ValsR[j];
        }
    }
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(mmatrix<T> & Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    std::vector<T> * RowsL = &_Matrix.front();
    std::vector<T> * RowsR = &Mat._Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * ValsR = &RowsR[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            ValsL[j] -= ValsR[j];
        }
    }
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator+=(std::vector<T> && Mat){
    return operator+=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(std::vector<T> && Mat){
    return operator-=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator+=(std::vector<T> & Mat){
    if((_Dimensions.Col - Mat.size()) != 0){
        throw std::out_of_range("Matrix dimensions "+ _Dimensions.to_string()
            + " and [" + std::to_string(Mat.size()) + "x1] are not conforming.");
    }
    mmatrix<T> NewMat(_Dimensions.Row,Mat.size());
    std::vector<T> * RowsL = &NewMat._Matrix.front();
    T * ValsR = &Mat.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        for(std::size_t j = 0; j < Mat.size(); j++){
            ValsL[j] = ValsR[j];
        }
    }
    return operator+=(NewMat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(std::vector<T> & Mat){
    if((_Dimensions.Col - Mat.size()) != 0){
        throw std::out_of_range("Matrix dimensions "+ _Dimensions.to_string()
            + " and [" + std::to_string(Mat.size()) + "x1] are not conforming.");
    }
    mmatrix<T> NewMat(_Dimensions.Row,Mat.size());
    std::vector<T> * RowsL = &NewMat._Matrix.front();
    T * ValsR = &Mat.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        for(std::size_t j = 0; j < Mat.size(); j++){
            ValsL[j] = ValsR[j];
        }
    }
    return operator-=(NewMat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator+=(const T Val){
    std::vector<T> * Rows = &_Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * Vals = &Rows[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            Vals[j] += Val;
        }
    }
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(const T Val){
    std::vector<T> * Rows = &_Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * Vals = &Rows[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            Vals[j] -= Val;
        }
    }
    return *this;
}

template<typename T>
mmatrix<T> mmatrix<T>::operator+(mmatrix<T> && Mat){
    return operator+(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(mmatrix<T> && Mat){
    return operator-(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator+(mmatrix<T> & Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    mmatrix<T> NewMat(_Dimensions);
    std::vector<T> * RowsL = &_Matrix.front();
    std::vector<T> * RowsR = &Mat._Matrix.front();
    std::vector<T> * Rows = &NewMat._Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * ValsR = &RowsR[i].front();
        T * Vals = &Rows[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            Vals[j] = ValsL[j] + ValsR[j];
        }
    }
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(mmatrix<T> & Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    mmatrix<T> NewMat(_Dimensions);
    std::vector<T> * RowsL = &_Matrix.front();
    std::vector<T> * RowsR = &Mat._Matrix.front();
    std::vector<T> * Rows = &NewMat._Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * ValsR = &RowsR[i].front();
        T * Vals = &Rows[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            Vals[j] = ValsL[j] - ValsR[j];
        }
    }
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator+(std::vector<T> && Mat){
    return operator+(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(std::vector<T> && Mat){
    return operator-(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator+(std::vector<T> & Mat){
    mmatrix<T> NewMat(_Dimensions.Row,Mat.size());
    std::vector<T> * RowsL = &NewMat._Matrix.front();
    T * ValsR = &Mat.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        for(std::size_t j = 0; j < Mat.size(); j++){
            ValsL[j] = ValsR[j];
        }
    }
    return operator+(NewMat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(std::vector<T> & Mat){
    mmatrix<T> NewMat(_Dimensions.Row,Mat.size());
    std::vector<T> * RowsL = &NewMat._Matrix.front();
    T * ValsR = &Mat.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        for(std::size_t j = 0; j < Mat.size(); j++){
            ValsL[j] = ValsR[j];
        }
    }
    return operator-(NewMat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator+(const T Val){
    mmatrix<T> NewMat(_Dimensions);
    std::vector<T> * RowsL = &NewMat._Matrix.front();
    std::vector<T> * RowsR = &_Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * ValsR = &RowsR[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            ValsL[j] = ValsR[j] + Val;
        }
    }
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(const T Val){
    mmatrix<T> NewMat(_Dimensions);
    std::vector<T> * RowsL = &NewMat._Matrix.front();
    std::vector<T> * RowsR = &_Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * ValsR = &RowsR[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            ValsL[j] = ValsR[j] - Val;
        }
    }
    return NewMat;
}

template<typename T>
mmatrix<T>& mmatrix<T>::operator*=(mmatrix<T> && Mat){
    return operator*=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator*=(mmatrix<T> & Mat){
    _Dimensions *= Mat._Dimensions;
    std::vector< std::vector<T> > NewMat(_Dimensions.Row,std::vector<T>(_Dimensions.Col));

    std::vector<T> * RowsL = &_Matrix.front();
    std::vector<T> * RowsR = &Mat._Matrix.front();
    std::vector<T> * NewRows = &NewMat.front();
    std::vector<T*> Columns(Mat._Matrix.size());
    T **ValsR = &Columns.front();

    for(unsigned int i = 0; i < Mat._Matrix.size(); i++){
        ValsR[i] = &RowsR[i].front();
    }
    for(unsigned int i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * Vals = &NewRows[i].front();
        for(unsigned int j = 0; j < _Dimensions.Col; j++){
            for(unsigned int k = 0; k < Columns.size(); k++){
                Vals[j] += ValsL[k] * ValsR[k][j];
            }
        }
    }
    std::swap(_Matrix,NewMat);
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator*=(std::vector<T> && Mat){
    return operator*=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator*=(std::vector<T> & Mat){
    mmatrix<T> NewMat;
    NewMat.push_back(Mat);
    NewMat.transpose();
    return operator*=(NewMat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator*=(const T Val){
    std::vector<T> * Rows = &_Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * Vals = &Rows[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            Vals[j] *= Val;
        }
    }
    return *this;

}
template<typename T>
mmatrix<T>& mmatrix<T>::operator/=(const T Val){
    std::vector<T> * Rows = &_Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * Vals = &Rows[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            Vals[j] /= Val;
        }
    }
    return *this;
}

template<typename T>
mmatrix<T> mmatrix<T>::operator*(mmatrix<T> && Mat){
    return operator*(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator*(mmatrix<T> & Mat){
    mdimension NewDim = _Dimensions * Mat._Dimensions;
    mmatrix<T> NewMat(NewDim);

    std::vector<T> * RowsL = &_Matrix.front();
    std::vector<T> * RowsR = &Mat._Matrix.front();
    std::vector<T> * NewRows = &NewMat._Matrix.front();
    std::vector<T*> Columns(Mat._Matrix.size());
    T **ValsR = &Columns.front();

    for(unsigned int i = 0; i < Mat._Matrix.size(); i++){
        ValsR[i] = &RowsR[i].front();
    }
    for(unsigned int i = 0; i < NewDim.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * Vals = &NewRows[i].front();
        for(unsigned int j = 0; j < NewDim.Col; j++){
            for(unsigned int k = 0; k < Columns.size(); k++){
                Vals[j] += ValsL[k] * ValsR[k][j];
            }
        }
    }
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator*(std::vector<T> && Mat){
    return operator*(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator*(std::vector<T> & Mat){
    mmatrix<T> NewMat;
    NewMat.push_back(Mat);
    NewMat.transpose();
    return operator*=(NewMat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator*(const T Val){
    mmatrix<T> NewMat(_Dimensions);
    std::vector<T> * RowsL = &NewMat._Matrix.front();
    std::vector<T> * RowsR = &_Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * ValsR = &RowsR[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            ValsL[j] = ValsR[j] * Val;
        }
    }
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator/(const T Val){
    mmatrix<T> NewMat(_Dimensions);
    std::vector<T> * RowsL = &NewMat._Matrix.front();
    std::vector<T> * RowsR = &_Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * ValsR = &RowsR[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            ValsL[j] = ValsR[j] / Val;
        }
    }
    return NewMat;
}

template<typename T>
mmatrix<T>& mmatrix<T>::operator=(const mmatrix<T> && Mat){
    return operator=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator=(const mmatrix<T> & Mat){
    _Dimensions = Mat._Dimensions;
    _Matrix = Mat._Matrix;
    return *this;
}

template<typename T>
mmatrix<T> mmatrix<T>::transposition(){
    mdimension NewDim(_Dimensions.Col,_Dimensions.Row);
    mmatrix<T> NewMat(NewDim);

    std::vector<T> * RowsL = &NewMat._Matrix.front();
    std::vector<T> * RowsR = &_Matrix.front();
    std::vector<T*> Columns(_Matrix.size());
    T **ValsR = &Columns.front();

    for(unsigned int i = 0; i < _Matrix.size(); i++){
        ValsR[i] = &RowsR[i].front();
    }
    for(unsigned int i = 0; i < NewDim.Row; i++){
        T * ValsL = &RowsL[i].front();
        for(unsigned int j = 0; j < NewDim.Col; j++){
            ValsL[j] = ValsR[j][i];
        }
    }
    return NewMat;
}
template<typename T>
void mmatrix<T>::transpose(){
    std::vector< std::vector<T> > NewMat(_Dimensions.Col,std::vector<T>(_Dimensions.Row));

    std::vector<T> * RowsL = &NewMat.front();
    std::vector<T> * RowsR = &_Matrix.front();
    std::vector<T*> Columns(_Matrix.size());
    T **ValsR = &Columns.front();

    for(unsigned int i = 0; i < _Matrix.size(); i++){
        ValsR[i] = &RowsR[i].front();
    }
    for(unsigned int i = 0; i < _Dimensions.Col; i++){
        T * ValsL = &RowsL[i].front();
        for(unsigned int j = 0; j < _Dimensions.Row; j++){
            ValsL[j] = ValsR[j][i];
        }
    }
    _Dimensions.swap();
    std::swap(_Matrix,NewMat);
}
template<typename T>
mmatrix<T> mmatrix<T>::entry_mult(mmatrix<T> && Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    return entry_mult(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::entry_mult(mmatrix<T> & Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    mmatrix<T> NewMat(_Dimensions);
    std::vector<T> * RowsL = &_Matrix.front();
    std::vector<T> * RowsR = &Mat._Matrix.front();
    std::vector<T> * Rows = &NewMat._Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * ValsR = &RowsR[i].front();
        T * Vals = &Rows[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            Vals[j] = ValsL[j] * ValsR[j];
        }
    }
    return NewMat;
}
template<typename T>
mmatrix<T>& mmatrix<T>::equal_entry_mult(mmatrix<T> && Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    return equal_entry_mult(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::equal_entry_mult(mmatrix<T> & Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    std::vector<T> * RowsL = &_Matrix.front();
    std::vector<T> * RowsR = &Mat._Matrix.front();
    for(std::size_t i = 0; i < _Dimensions.Row; i++){
        T * ValsL = &RowsL[i].front();
        T * ValsR = &RowsR[i].front();
        for(std::size_t j = 0; j < _Dimensions.Col; j++){
            ValsL[j] *= ValsR[j];
        }
    }
    return *this;
}

template<typename T>
std::string mmatrix<T>::to_string(char Delimiter, char Separator,  char Border){
    std::string MatStr;
    for(auto & Row : _Matrix){
        MatStr += Border;
        for(auto & Sgn : Row){
            MatStr += std::to_string(Sgn) + Delimiter;
        }
        MatStr[MatStr.size()-1] = Border;
        MatStr += Separator;
    }
    MatStr.pop_back();
    return MatStr;
}

template<typename T>
mdimension mmatrix<T>::dimension() const{
    return _Dimensions;
}
template<typename T>
mdimension mmatrix<T>::size() const{
    return _Dimensions;
}
template<typename T>
size_t mmatrix<T>::row_size() const{
    return _Dimensions.Row;
}
template<typename T>
size_t mmatrix<T>::col_size() const{
    return _Dimensions.Col;
}

template<typename T>
typename mmatrix<T>::iterator mmatrix<T>::begin(){
    return _Matrix.begin();
}
template<typename T>
typename mmatrix<T>::iterator mmatrix<T>::end(){
    return _Matrix.end();
}


template<typename T>
mmatrix<T> mmatrix<T>::covariance(mmatrix<T> && Mat){
    return covariance(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::covariance(mmatrix<T> & Mat){
    std::vector<T> MeanVec(Mat._Dimensions.Col,T());
    mmatrix<T> CovMat = Mat;

    std::vector<T> * Rows = &Mat._Matrix.front();
    T * MeanCol = &MeanVec.front();

    for(unsigned int i = 0; i < Mat._Matrix.size(); i++){
        T * Vals = &Rows[i].front();
        for(unsigned int j = 0; j < Mat._Dimensions.Col; j++){
            MeanCol[j] += Vals[j];
        }
    }
    for(unsigned int i = 0; i < Mat._Dimensions.Col; i++){
        MeanCol[i] /= Mat._Dimensions.Row;
    }

    CovMat -= MeanVec;
    if(Mat._Dimensions.Row > 1){
        CovMat = CovMat.transposition()*CovMat/(Mat._Dimensions.Row-1);
    }
    else{
        CovMat = CovMat.transposition()*CovMat/Mat._Dimensions.Row;
    }
    return CovMat;
}

template<typename T>
std::vector< meigen<T> > mmatrix<T>::eigen(mmatrix<T> && Mat, unsigned VecNo){
    return eigen(Mat, VecNo);
}
template<typename T>
std::vector< meigen<T> > mmatrix<T>::eigen(mmatrix<T> & Mat, unsigned VecNo){
    if(VecNo == 0){
        VecNo = Mat.size();
    }

    std::vector< meigen<T> > Eigens = Eigens(VecNo);
    mmatrix<T> EigenMat = Mat;
    
    for(unsigned i = 0; i < VecNo; i++){
        Eigens[i] = meigens<T>::power_iteration();
        EigenMat = EigenMat - Eigens[i].value()*Eigens[i].vector().transposition()*Eigens[i].vector();
    }

    return Eigens;
}


template<typename T>
T mmatrix<T>::vector_norm(mmatrix<T> && Vector, unsigned LPNorm){
    return vector_norm(Vector, LPNorm);
}
template<typename T>
T mmatrix<T>::vector_norm(mmatrix<T> & Vector, unsigned LPNorm){
    return l_p_norm(Vector, LPNorm);
}
template<typename T>
T mmatrix<T>::vector_norm(mmatrix<T> && Vector, std::function<T(mmatrix<T>)> const& Norm){
    return vector_norm(Vector, Norm);
}
template<typename T>
T mmatrix<T>::vector_norm(mmatrix<T> & Vector, std::function<T(mmatrix<T>)> const& Norm){
    return Norm(Vector);
}

template<typename T>
T l_p_norm(mmatrix<T> & Matrix, unsigned Norm){
    //TODO: Throw Exception for wrong matrix size!
    if(Matrix.row_size() == 1){
        T UnSqr =  std::accumulate(Matrix.begin()->begin(),Matrix.begin()->end(), 0, [&Norm](const T & SumPart, const T & Element){
            return SumPart + std::pow(Element,Norm);
        });
        return std::pow(UnSqr, 1.0/(double)Norm);
    }
    else{
        T UnSqr =  std::accumulate(Matrix[0].begin(),Matrix[0].end(), 0, [&Norm](const T & SumPart, const T & Element){
            return SumPart + std::pow(Element,Norm);
        });
        return std::pow(UnSqr, 1.0/(double)Norm);
    }
}
template<typename T>
T eucl_norm(mmatrix<T> & Matrix){
    return l_p_norm(Matrix, 2);
}
template<typename T>
T taxicap_Norm(mmatrix<T> & Matrix){
    return l_p_norm(Matrix, 1);    
}

mmatrix<T>::euclid = &mmatrix<T>::eucl_norm;
mmatrix<T>::taxicap = &mmatrix<T>::taxicap_norm;

#endif