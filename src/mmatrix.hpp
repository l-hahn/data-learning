#ifndef _MMATRIX_HPP_
#define _MMATRIX_HPP_

/*===Libraries================================================================*/
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iterator>
#include <initializer_list>
#include <numeric>
#include <omp.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "mdimension.hpp"
#include "meigen.hpp" 

/*===Classes-Structurres======================================================*/
template<typename T = double>
class mmatrix{
    private:
        std::vector< std::vector<T> > _Matrix;
        mdimension _Dimensions;
        static std::size_t threadNumber;

    public:
        mmatrix();
        mmatrix(size_t Row, size_t Col, T Val=T());
        mmatrix(const mdimension && Dim, T Val=T());
        mmatrix(const mdimension & Dim, T Val=T());
        mmatrix(const mmatrix<T> && Mat);
        mmatrix(const mmatrix<T> & Mat);
        mmatrix(const std::vector<T> && Mat);
        mmatrix(const std::vector<T> & Mat);
        mmatrix(const std::initializer_list<T> && Mat);
        mmatrix(const std::initializer_list<T> & Mat);
        mmatrix(const std::vector< std::vector<T> > && Mat);
        mmatrix(const std::vector< std::vector<T> > & Mat);
        mmatrix(const std::initializer_list< std::initializer_list<T> > && Mat);
        mmatrix(const std::initializer_list< std::initializer_list<T> > & Mat);

        void push_back(const std::vector<T> && ValList);
        void push_back(const std::vector<T> & ValList);
        void push_back_row(const std::vector<T> && ValList);
        void push_back_row(const std::vector<T> & ValList);
        void push_back_col(const std::vector<T> && ValList);
        void push_back_col(const std::vector<T> & ValList);
        void push_back(const mmatrix<T> && Mat);
        void push_back(const mmatrix<T> & Mat);
        void push_back_row(const mmatrix<T> && Mat);
        void push_back_row(const mmatrix<T> & Mat);
        void push_back_col(const mmatrix<T> && Mat);
        void push_back_col(const mmatrix<T> & Mat);

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
        mmatrix<T> vec_entry_mult(std::vector<T> && Mat);
        mmatrix<T> vec_entry_mult(std::vector<T> & Mat);
        mmatrix<T>& equal_vec_entry_mult(std::vector<T> && Mat);
        mmatrix<T>& equal_vec_entry_mult(std::vector<T> & Mat);

        std::string to_string(char Delimiter = ' ', char Separator = '\n', char Border = 0);

        std::vector< std::vector<T> > vector_matrix() const;
        mdimension dimension() const;
        mdimension size() const;
        size_t row_size() const;
        size_t col_size() const;

        std::vector<T>& front();

        typedef typename std::vector< std::vector<T> >::iterator iterator;
        iterator begin();
        iterator end();


        static mmatrix<T> repmat(mmatrix<T> && Mat, std::size_t Row = 1, std::size_t Col = 1);
        static mmatrix<T> repmat(mmatrix<T> & Mat, std::size_t Row = 1, std::size_t Col = 1);
        static void transform(mmatrix<T> && Mat, std::function<T(T)> const& func);
        static void transform(mmatrix<T> & Mat, std::function<T(T)> const& func);
        static void transform(mmatrix<T> && Mat, std::function<T(mmatrix<T>)> const& func);
        static void transform(mmatrix<T> & Mat, std::function<T(mmatrix<T>)> const& func);

        static mmatrix<T> max(mmatrix<T> && Mat);
        static mmatrix<T> max(mmatrix<T> & Mat);
        static mmatrix<T> min(mmatrix<T> && Mat);
        static mmatrix<T> min(mmatrix<T> & Mat);

        static mmatrix<T> sum(mmatrix<T> && Mat);
        static mmatrix<T> sum(mmatrix<T> & Mat);

        static mmatrix<T> covariance(mmatrix<T> && Mat);
        static mmatrix<T> covariance(mmatrix<T> & Mat);
        static mmatrix<T> reduced_covariance(mmatrix<T> && Mat, std::vector< meigen<T> > && Eigens);
        static mmatrix<T> reduced_covariance(mmatrix<T> & Mat, std::vector< meigen<T> > & Eigens);
        static mmatrix<T> gramian(mmatrix<T> && Mat);
        static mmatrix<T> gramian(mmatrix<T> & Mat);
        static mmatrix<T> distance(mmatrix<T> && Mat1, mmatrix<T> && Mat2, std::size_t Norm = 2);
        static mmatrix<T> distance(mmatrix<T> & Mat1, mmatrix<T> & Mat2, std::size_t Norm = 2);
        static mmatrix<T> distance(mmatrix<T> && Mat1, mmatrix<T> && Mat2, std::function<T(mmatrix<T>)> const& Norm = euclid);
        static mmatrix<T> distance(mmatrix<T> & Mat1, mmatrix<T> & Mat2, std::function<T(mmatrix<T>)> const& Norm = euclid);
        static mmatrix<T> distance(mmatrix<T> && Mat1, mmatrix<T> && Mat2, std::function<mmatrix<T>(mmatrix<T>)> const& Norm = euclids);
        static mmatrix<T> distance(mmatrix<T> & Mat1, mmatrix<T> & Mat2, std::function<mmatrix<T>(mmatrix<T>)> const& Norm = euclids);
        static std::vector< meigen<T> > eigen(mmatrix<T> && Mat, std::size_t VecNo = 0, std::function<T(mmatrix<T>)> const& Norm = euclid);
        static std::vector< meigen<T> > eigen(mmatrix<T> & Mat, std::size_t VecNo = 0, std::function<T(mmatrix<T>)> const& Norm = euclid);

        static T vector_norm(mmatrix<T> && Vector, std::size_t Norm = 2);
        static T vector_norm(mmatrix<T> & Vector, std::size_t Norm = 2);
        static T vector_norm(mmatrix<T> && Vector, std::function<T(mmatrix<T>)> const& Norm);
        static T vector_norm(mmatrix<T> & Vector, std::function<T(mmatrix<T>)> const& Norm);

        static const std::function<T(mmatrix<T>)> euclid;
        static const std::function<T(mmatrix<T>)> taxicap;

        static mmatrix<T> vector_norms(mmatrix<T> && Matrix, std::size_t Norm = 2);
        static mmatrix<T> vector_norms(mmatrix<T> & Matrix, std::size_t Norm = 2);
        static mmatrix<T> vector_norms(mmatrix<T> && Matrix, std::function<mmatrix<T>(mmatrix<T>)> const& Norm);
        static mmatrix<T> vector_norms(mmatrix<T> & Matrix, std::function<mmatrix<T>(mmatrix<T>)> const& Norm);

        static const std::function<mmatrix<T>(mmatrix<T>)> euclids;
        static const std::function<mmatrix<T>(mmatrix<T>)> taxicaps;

        //TODO: lp-norm, infty-norm, cosine distance, hamming distance, edit distance

        static void thread(std::size_t thrd = 2);
        static std::size_t thread();

    private:
        static mmatrix<T> l_p_norms(mmatrix<T> && Matrix, std::size_t Norm);
        static mmatrix<T> l_p_norms(mmatrix<T> & Matrix, std::size_t Norm);
        static mmatrix<T> eucl_norms(mmatrix<T>  Matrix);
        static mmatrix<T> taxicap_norms(mmatrix<T>  Matrix);
        static T l_p_norm(mmatrix<T> && Matrix, std::size_t Norm);
        static T l_p_norm(mmatrix<T> & Matrix, std::size_t Norm);
        static T eucl_norm(mmatrix<T>  Matrix);
        static T taxicap_Norm(mmatrix<T>  Matrix);
        static mdimension check_length_input(const std::vector< std::vector<T> > & Mat);
        static mdimension check_length_input(const std::initializer_list< std::initializer_list<T> > & Mat);

        static T l_p_norm(std::vector<T> & Matrix, std::size_t Norm);
};

/*===Variables================================================================*/

/*===Prototypes===============================================================*/

/*===Main=====================================================================*/
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
    push_back(Mat);
}
template<typename T>
mmatrix<T>::mmatrix(const std::vector<T> & Mat){
    push_back(Mat);
}
template<typename T>
mmatrix<T>::mmatrix(const std::initializer_list<T> && Mat){
    _Dimensions = mdimension(1,Mat.size());
    _Matrix = std::vector< std::vector<T> >(1);
    _Matrix.begin()->insert(_Matrix.begin()->end(),Mat.begin(),Mat.end());
}
template<typename T>
mmatrix<T>::mmatrix(const std::initializer_list<T> & Mat){
    _Dimensions = mdimension(1,Mat.size());
    _Matrix = std::vector< std::vector<T> >(1);
    _Matrix.begin()->insert(_Matrix.begin()->end(),Mat.begin(),Mat.end());
}
template<typename T>
mmatrix<T>::mmatrix(const std::vector< std::vector<T> > && Mat){
    _Dimensions = mmatrix<T>::check_length_input(Mat);
    _Matrix = Mat;
}
template<typename T>
mmatrix<T>::mmatrix(const std::vector< std::vector<T> > & Mat){
    _Dimensions = mmatrix<T>::check_length_input(Mat);
    _Matrix = Mat;
}

template<typename T>
mmatrix<T>::mmatrix(const std::initializer_list< std::initializer_list<T> > && Mat){
    _Dimensions = mmatrix<T>::check_length_input(Mat);
    _Matrix.insert(_Matrix.end(),Mat.begin(),Mat.end());
}
template<typename T>
mmatrix<T>::mmatrix(const std::initializer_list< std::initializer_list<T> > & Mat){
    _Dimensions = mmatrix<T>::check_length_input(Mat);
    _Matrix.insert(_Matrix.end(),Mat.begin(),Mat.end());
}

template<typename T>
void mmatrix<T>::push_back(const std::vector<T> && Mat){
    push_back(Mat);
}
template<typename T>
void mmatrix<T>::push_back(const std::vector<T> & Mat){
    push_back_row(Mat);
}
template<typename T>
void mmatrix<T>::push_back_row(const std::vector<T> && Mat){
    push_back_row(Mat);
}
template<typename T>
void mmatrix<T>::push_back_row(const std::vector<T> & Mat){
    if(_Dimensions.Col != Mat.size() && _Dimensions.Col != 0){
        throw std::out_of_range("push_back_row: Matrix col-dimensions "+ _Dimensions.to_string()
            + " and [1x" + std::to_string(Mat.size()) + "] are not conforming.");
    }
    if( _Dimensions.Col == 0){
        _Dimensions.Col = Mat.size();
    }
    _Matrix.push_back(Mat);
    _Dimensions.Row++;
}
template<typename T>
void mmatrix<T>::push_back_col(const std::vector<T> && Mat){
    push_back_col(Mat);
}
template<typename T>
void mmatrix<T>::push_back_col(const std::vector<T> & Mat){
    if(_Dimensions.Row != Mat.size() && _Dimensions.Row != 0){
        throw std::out_of_range("push_back_col: Matrix row-dimensions "+ _Dimensions.to_string()
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
void mmatrix<T>::push_back(const mmatrix<T> && Mat){
    push_back_row(Mat);
}

template<typename T>
void mmatrix<T>::push_back(const mmatrix<T> & Mat){
    push_back_row(Mat);
}

template<typename T>
void mmatrix<T>::push_back_row(const mmatrix<T> && Mat){
    push_back(Mat);
}
template<typename T>
void mmatrix<T>::push_back_row(const mmatrix<T> & Mat){
    if(_Dimensions.Col != Mat.col_size() && _Dimensions.Col != 0){
        throw std::out_of_range("push_back_row: Matrix col-dimensions "+ _Dimensions.to_string()
            + " and " + Mat._Dimensions.to_string() + " are not conforming.");
    }
    if( _Dimensions.Col == 0){
        _Dimensions.Col = Mat.col_size();
    }
    for(std::vector<T> Vec : Mat._Matrix){
        _Matrix.push_back(Vec);
        _Dimensions.Row++;
    }
}
template<typename T>
void mmatrix<T>::push_back_col(const mmatrix<T> && Mat){
    push_back_col(Mat);
}
template<typename T>
void mmatrix<T>::push_back_col(const mmatrix<T> & Mat){
    if(_Dimensions.Row != Mat.row_size() && _Dimensions.Row != 0){
        throw std::out_of_range("push_back_col: Matrix row-dimensions "+ _Dimensions.to_string()
            + " and " + Mat._Dimensions.to_string() + " are not conforming.");
    }
    if(_Dimensions.Row == 0){
        _Dimensions.Row = Mat.row_size();
        _Matrix.resize(Mat.row_size());
    }
    for(std::vector<T> MVec : Mat._Matrix){
        std::transform(_Matrix.begin(),_Matrix.end(),MVec.begin(),_Matrix.begin(),[](std::vector<T> & Vec, T Val){
            Vec.push_back(Val);
            return Vec;
        });
        _Dimensions.Col++;
    }
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
        throw std::out_of_range("operator+=: Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    std::vector<T> * RowsL = &front();
    std::vector<T> * RowsR = &Mat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            T * ValsR = &RowsR[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] += ValsR[j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(mmatrix<T> & Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("operator-=: Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    std::vector<T> * RowsL = &front();
    std::vector<T> * RowsR = &Mat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            T * ValsR = &RowsR[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] -= ValsR[j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
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
        throw std::out_of_range("operator+=: Matrix dimensions "+ _Dimensions.to_string()
            + " and [" + std::to_string(Mat.size()) + "x1] are not conforming.");
    }
    std::vector<T> * RowsL = &front();
    T * ValsR = &Mat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] += ValsR[j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(std::vector<T> & Mat){
    if((_Dimensions.Col - Mat.size()) != 0){
        throw std::out_of_range("operator-=: Matrix dimensions "+ _Dimensions.to_string()
            + " and [" + std::to_string(Mat.size()) + "x1] are not conforming.");
    }
    std::vector<T> * RowsL = &front();
    T * ValsR = &Mat.front();

    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] -= ValsR[j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator+=(const T Val){
    std::vector<T> * Rows = &front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * Vals = &Rows[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                Vals[j] += Val;
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(const T Val){
    std::vector<T> * Rows = &front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * Vals = &Rows[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                Vals[j] -= Val;
            }
        }
    #ifdef _OPENMP
    }
    #endif
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
        throw std::out_of_range("operator+: Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    mmatrix<T> NewMat(*this);
    std::vector<T> * RowsR = &Mat.front();
    std::vector<T> * RowsL = &NewMat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            T * ValsR = &RowsR[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] += ValsR[j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(mmatrix<T> & Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("operator-: Matrix dimensions "+ _Dimensions.to_string()
            + Mat._Dimensions.to_string() + " are not conforming.");
    }
    mmatrix<T> NewMat(*this);
    std::vector<T> * RowsR = &Mat.front();
    std::vector<T> * RowsL = &NewMat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            T * ValsR = &RowsR[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] -= ValsR[j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
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
    if((_Dimensions.Col - Mat.size()) != 0){
        throw std::out_of_range("operator+=: Matrix dimensions "+ _Dimensions.to_string()
            + " and [" + std::to_string(Mat.size()) + "x1] are not conforming.");
    }
    mmatrix<T> NewMat = mmatrix<T>(*this);
    std::vector<T> * RowsL = &NewMat.front();
    T * ValsR = &Mat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] += ValsR[j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(std::vector<T> & Mat){
    if((_Dimensions.Col - Mat.size()) != 0){
        throw std::out_of_range("operator+=: Matrix dimensions "+ _Dimensions.to_string()
            + " and [" + std::to_string(Mat.size()) + "x1] are not conforming.");
    }
    mmatrix<T> NewMat = mmatrix<T>(*this);
    std::vector<T> * RowsL = &NewMat.front();
    T * ValsR = &Mat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] -= ValsR[j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator+(const T Val){
    mmatrix<T> NewMat(*this);
    std::vector<T> * RowsL = &NewMat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] += Val;
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(const T Val){
    mmatrix<T> NewMat(*this);
    std::vector<T> * RowsL = &NewMat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] -= Val;
            }
        }
    #ifdef _OPENMP
    }
    #endif
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

    std::vector<T> * RowsL = &front();
    std::vector<T> * RowsR = &Mat.front();
    std::vector<T> * NewRows = &NewMat.front();
    std::vector<T*> Columns(Mat._Matrix.size());
    T **ValsR = &Columns.front();

    for(std::size_t i = 0; i < Mat._Matrix.size(); i++){
        ValsR[i] = &RowsR[i].front();
    }
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            T * Vals = &NewRows[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                Vals[j] = 0;
                for(std::size_t k = 0; k < Columns.size(); k++){
                    Vals[j] += ValsL[k] * ValsR[k][j];
                }
            }
        }
    #ifdef _OPENMP
    }
    #endif
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
    std::vector<T> * Rows = &front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * Vals = &Rows[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                Vals[j] *= Val;
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return *this;

}
template<typename T>
mmatrix<T>& mmatrix<T>::operator/=(const T Val){
    std::vector<T> * Rows = &front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * Vals = &Rows[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                Vals[j] /= Val;
            }
        }
    #ifdef _OPENMP
    }
    #endif
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

    std::vector<T> * RowsL = &front();
    std::vector<T> * RowsR = &Mat.front();
    std::vector<T> * NewRows = &NewMat.front();
    std::vector<T*> Columns(Mat._Matrix.size());
    T **ValsR = &Columns.front();

    for(std::size_t i = 0; i < Mat._Matrix.size(); i++){
        ValsR[i] = &RowsR[i].front();
    }
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < NewDim.Row; i++){
            T * ValsL = &RowsL[i].front();
            T * Vals = &NewRows[i].front();
            for(std::size_t j = 0; j < NewDim.Col; j++){
                for(std::size_t k = 0; k < Columns.size(); k++){
                    Vals[j] += ValsL[k] * ValsR[k][j];
                }
            }
        }
    #ifdef _OPENMP
    }
    #endif
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
    return operator*(NewMat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator*(const T Val){
    mmatrix<T> NewMat(*this);
    std::vector<T> * RowsL = &NewMat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] *= Val;
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator/(const T Val){
    mmatrix<T> NewMat(*this);
    std::vector<T> * RowsL = &NewMat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] /= Val;
            }
        }
    #ifdef _OPENMP
    }
    #endif
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

    std::vector<T> * RowsL = &NewMat.front();
    std::vector<T> * RowsR = &front();
    std::vector<T*> Columns(_Matrix.size());
    T **ValsR = &Columns.front();

    for(std::size_t i = 0; i < _Matrix.size(); i++){
        ValsR[i] = &RowsR[i].front();
    }
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < NewDim.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < NewDim.Col; j++){
                ValsL[j] = ValsR[j][i];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return NewMat;
}
template<typename T>
void mmatrix<T>::transpose(){
    std::vector< std::vector<T> > NewMat(_Dimensions.Col,std::vector<T>(_Dimensions.Row));

    std::vector<T> * RowsL = &NewMat.front();
    std::vector<T> * RowsR = &front();
    std::vector<T*> Columns(_Matrix.size());
    T **ValsR = &Columns.front();

    for(std::size_t i = 0; i < _Matrix.size(); i++){
        ValsR[i] = &RowsR[i].front();
    }
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Col; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Row; j++){
                ValsL[j] = ValsR[j][i];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    _Dimensions.swap();
    std::swap(_Matrix,NewMat);
}
template<typename T>
mmatrix<T> mmatrix<T>::entry_mult(mmatrix<T> && Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("entry_mult: Matrix dimensions "+ _Dimensions.to_string()
            +" and "+ Mat._Dimensions.to_string() + " are not conforming.");
    }
    return entry_mult(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::entry_mult(mmatrix<T> & Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("entry_mult: Matrix dimensions "+ _Dimensions.to_string()
            +" and "+ Mat._Dimensions.to_string() + " are not conforming.");
    }
    mmatrix<T> NewMat(*this);
    std::vector<T> * RowsR = &Mat.front();
    std::vector<T> * RowsL = &NewMat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            T * ValsR = &RowsR[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] *= ValsR[j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return NewMat;
}
template<typename T>
mmatrix<T>& mmatrix<T>::equal_entry_mult(mmatrix<T> && Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("equal_entry_mult: Matrix dimensions "+ _Dimensions.to_string()
            +" and "+ Mat._Dimensions.to_string() + " are not conforming.");
    }
    return equal_entry_mult(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::equal_entry_mult(mmatrix<T> & Mat){
    if((_Dimensions.Row - Mat._Dimensions.Row) != 0 || (_Dimensions.Row - Mat._Dimensions.Row) != 0){
        throw std::out_of_range("equal_entry_mult: Matrix dimensions "+ _Dimensions.to_string()
            +" and "+ Mat._Dimensions.to_string() + " are not conforming.");
    }
    std::vector<T> * RowsL = &front();
    std::vector<T> * RowsR = &Mat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            T * ValsR = &RowsR[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] *= ValsR[j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return *this;
}

template<typename T>
mmatrix<T> mmatrix<T>::vec_entry_mult(std::vector<T> && Mat){
    if(_Dimensions.Row != Mat.size()){
        throw std::out_of_range("vec_entry_mult: Matrix dimensions "+ _Dimensions.to_string()
            +" and " + Mat._Dimensions.to_string() + " are not conforming.");
    }
    return entry_mult(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::vec_entry_mult(std::vector<T> & Mat){
    if(_Dimensions.Row != Mat.size()){
        throw std::out_of_range("vec_entry_mult: Matrix dimensions "+ _Dimensions.to_string()
            + " and [" + std::to_string(Mat.size()) + "x1] are not conforming.");
    }
    mmatrix<T> NewMat(*this);
    std::vector<T> * RowsL = &NewMat.front();
    T * ValsR = &Mat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] *= ValsR[i];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return NewMat;
}
template<typename T>
mmatrix<T>& mmatrix<T>::equal_vec_entry_mult(std::vector<T> && Mat){
    if(_Dimensions.Row != Mat.size()){
        throw std::out_of_range("equal_entry_mult: Matrix dimensions "+ _Dimensions.to_string()
            +" and " + std::to_string(Mat.size()) + " are not conforming.");
    }
    return equal_entry_mult(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::equal_vec_entry_mult(std::vector<T> & Mat){
    if(_Dimensions.Row != Mat.size()){
        throw std::out_of_range("equal_entry_mult: Matrix dimensions "+ _Dimensions.to_string()
            +" and " + std::to_string(Mat.size()) + " are not conforming.");
    }
    std::vector<T> * RowsL = &front();
    T * ValsR = &Mat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < _Dimensions.Row; i++){
            T * ValsL = &RowsL[i].front();
            for(std::size_t j = 0; j < _Dimensions.Col; j++){
                ValsL[j] *= ValsR[i];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return *this;
}

template<typename T>
std::string mmatrix<T>::to_string(char Delimiter, char Separator,  char Border){
    std::string MatStr;
    for(auto & Row : _Matrix){
        if(Border != 0){
            MatStr += Border;
        }
        for(auto & Sgn : Row){
            MatStr += std::to_string(Sgn) + Delimiter;
        }
        if(Border  != 0){
            MatStr[MatStr.size()-1] = Border;
        }
        else{
            MatStr.pop_back();
        }
        MatStr += Separator;
    }
    MatStr.pop_back();
    return MatStr;
}

template<typename T>
std::vector< std::vector<T> > mmatrix<T>::vector_matrix() const{
    return _Matrix;
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
std::vector<T>& mmatrix<T>::front(){
    return _Matrix.front();
}

template<typename T>
typename std::vector< std::vector<T> >::iterator mmatrix<T>::begin(){
    return _Matrix.begin();
}
template<typename T>
typename std::vector< std::vector<T> >::iterator mmatrix<T>::end(){
    return _Matrix.end();
}

/*---static-------------------------------------------------------------------*/
template<typename T>
mmatrix<T> mmatrix<T>::repmat(mmatrix<T> && Mat, std::size_t Row, std::size_t Col){
    return repmat(Mat, Row, Col);
}
template<typename T>
mmatrix<T> mmatrix<T>::repmat(mmatrix<T> & Mat, std::size_t Row, std::size_t Col){
    mmatrix<T> RepMat(Mat);
    if(Row == 0 || Col == 0){
        throw std::out_of_range("repmat: column and row count has to be non-zero.");
    }
    RepMat._Dimensions = mdimension(Mat._Dimensions.Row*Row,Mat._Dimensions.Col*Col);

    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
    for(std::size_t i = 0; i < Mat.row_size(); i++){
        for(std::size_t j = 1; j < Col; j++){
            RepMat[i].insert(RepMat[i].end(),Mat[i].begin(),Mat[i].end());
        }
    }
    #ifdef _OPENMP
    }
    #endif

    RepMat._Matrix.resize(Mat.row_size()*Row);

    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = Mat.row_size(); i < RepMat.row_size(); i++){
            RepMat[i] = RepMat[i%Mat.row_size()];
        }
    #ifdef _OPENMP
    }
    #endif

    return RepMat;
}

template<typename T>
void mmatrix<T>::transform(mmatrix<T> && Mat, std::function<T(T)> const& func){
    transform(Mat, func);
}
template<typename T>
void mmatrix<T>::transform(mmatrix<T> & Mat, std::function<T(T)> const& func){
    for(std::size_t i = 0; i < Mat.row_size(); i++){
        for(std::size_t j = 0; j < Mat.col_size(); j++){
            func(Mat[i][j]);
        }
    }
}

template<typename T>
mmatrix<T> mmatrix<T>::max(mmatrix<T> && Mat){
    return max(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::max(mmatrix<T> & Mat){
    if(Mat.row_size() == 0 || Mat.row_size() == 0){
        throw std::out_of_range("max: column and row count has to be non-zero.");
    }
    mmatrix<T> Max(1,Mat.row_size());
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < Mat.row_size(); i++){
            Max[0][i] = *std::max_element(Mat[i].begin(),Mat[i].end());
        }
    #ifdef _OPENMP
    }
    #endif
    return Max;
}
template<typename T>
mmatrix<T> mmatrix<T>::min(mmatrix<T> && Mat){
    return min(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::min(mmatrix<T> & Mat){
    if(Mat.row_size() == 0 || Mat.row_size() == 0){
        throw std::out_of_range("min: column and row count has to be non-zero.");
    }
    mmatrix<T> Min(1,Mat.row_size());
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < Mat.row_size(); i++){
            Min[0][i] = *std::min_element(Mat[i].begin(),Mat[i].end());
        }
    #ifdef _OPENMP
    }
    #endif
    return Min;
}

template<typename T>
mmatrix<T> mmatrix<T>::sum(mmatrix<T> && Mat){
    return sum(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::sum(mmatrix<T> & Mat){
    if(Mat.row_size() == 0 || Mat.row_size() == 0){
        throw std::out_of_range("sum: column and row count has to be non-zero.");
    }
    mmatrix<T> Sum(1,Mat.row_size());
    T * Vec = &Sum[0].front();
    std::vector<T> * MatVec = &Mat.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < Mat.row_size(); i++){
            T * MVec = &MatVec[i].front();
            T Sum(0);
            for(std::size_t j = 0; j < Mat.col_size(); j++){
                Sum += MVec[j];
            }
            Vec[i] = Sum;
        }
    #ifdef _OPENMP
    }
    #endif
    return Sum;
}

template<typename T>
void mmatrix<T>::transform(mmatrix<T> && Mat, std::function<T(mmatrix<T>)> const& func){
    func(Mat);
}
template<typename T>
void mmatrix<T>::transform(mmatrix<T> & Mat, std::function<T(mmatrix<T>)> const& func){
    func(Mat);
}

template<typename T>
mmatrix<T> mmatrix<T>::covariance(mmatrix<T> && Mat){
    return covariance(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::covariance(mmatrix<T> & Mat){
    std::vector<T> MeanVec(Mat._Dimensions.Col,T());
    mmatrix<T> CovMat = Mat;

    std::vector<T> * Rows = &Mat.front();
    T * MeanCol = &MeanVec.front();

    for(std::size_t i = 0; i < Mat._Matrix.size(); i++){
        #ifdef _OPENMP
        #pragma omp parallel
        {
            T * Vals = &Rows[i].front();
            #pragma omp for
        #endif
            for(std::size_t j = 0; j < Mat._Dimensions.Col; j++){
                MeanCol[j] += Vals[j];
            }
        #ifdef _OPENMP    
        }
        #endif
    }
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < Mat._Dimensions.Col; i++){
            MeanCol[i] /= Mat._Dimensions.Row;
        }
    #ifdef _OPENMP
    }
    #endif

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
mmatrix<T>  mmatrix<T>::reduced_covariance(mmatrix<T> && Mat, std::vector< meigen<T> > && Eigens){
    return reduced_covariance(Mat, Eigens);
}
template<typename T>
mmatrix<T>  mmatrix<T>::reduced_covariance(mmatrix<T> & Mat, std::vector< meigen<T> > & Eigens){
    mmatrix<T> CovMat = Mat;
    for(meigen<T> Eigen : Eigens){
        Mat -= Eigen.vector().transposition()*Eigen.vector()*Eigen.value();
    }
    return CovMat;
}

template<typename T>
mmatrix<T> mmatrix<T>::gramian(mmatrix<T> && Mat){ 
    gramian(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::gramian(mmatrix<T> & Mat){
    if(Mat.row_size() != Mat.col_size()){
        throw std::out_of_range("gramian: Matrix has to be square matix, but it is "+Mat.size().to_string()+".");
    }
    mmatrix<T> GramianMat = Mat.entry_mult(Mat);
    std::vector<T> RowMean(GramianMat.row_size(),T()), ColMean(GramianMat.col_size(),T());
    
    T * RMean = &RowMean.front();
    T * CMean = &ColMean.front();

    std::vector<T> * GMat = &GramianMat.front();

    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < GramianMat.row_size(); i++){
            T * GVec = &GMat[i].front();
            for(std::size_t j = 0; j < GramianMat.col_size(); j++){
                RMean[i] += GVec[j];      
            }
        }
    #ifdef _OPENMP
    }
    #endif

    for(std::size_t i = 0; i < GramianMat.row_size(); i++){
        #ifdef _OPENMP
        #pragma omp parallel
        {
            T * GVec = &GMat[i].front();
            #pragma omp for
        #endif
            for(std::size_t j = 0; j < GramianMat.col_size(); j++){
                CMean[j] += GVec[j];       
            }
        #ifdef _OPENMP
        }
        #endif
    }

    T TotalMean = T();
    for(std::size_t i = 0; i < RowMean.size(); i++){
        TotalMean += RowMean[i];
    }


    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < RowMean.size(); i++){
            RMean[i] /= RowMean.size();
            CMean[i] /= RowMean.size();
        }
    #ifdef _OPENMP
    }
    #endif
    TotalMean /= GramianMat.row_size()*GramianMat.row_size();

    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < GramianMat.row_size(); i++){
            T * GVec = &GMat[i].front();
            for(std::size_t j = 0; j < GramianMat.col_size(); j++){
                GVec[j] = -0.5*(GVec[j] -RMean[i] - CMean[j] +TotalMean);
            }
        }
    #ifdef _OPENMP
    }
    #endif

    return GramianMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::distance(mmatrix<T> && Mat1, mmatrix<T> && Mat2, std::size_t Norm){
    return distance(Mat1, Mat2, Norm);
}
template<typename T>
mmatrix<T> mmatrix<T>::distance(mmatrix<T> & Mat1, mmatrix<T> & Mat2, std::size_t Norm){
    if(Mat1.col_size() != Mat2.col_size()){
        throw std::out_of_range("distance: Matrix1 col_size (" + std::to_string(Mat1.col_size()) + ") != Matrix2 col_size (" + std::to_string(Mat2.col_size()) + ")");
    }
    mmatrix<T> DistMat(Mat1.row_size(), Mat2.row_size());
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < Mat1.row_size(); i++){
            mmatrix<T> M(Mat1[i]);
            for(std::size_t j = i+1; j < Mat2.row_size(); j++){
                DistMat[i][j] = l_p_norm(M-Mat2[j],Norm);
                DistMat[j][i] = DistMat[i][j];
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return DistMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::distance(mmatrix<T> && Mat1, mmatrix<T> && Mat2, std::function<T(mmatrix<T>)> const& Norm){
    return distance(Mat1, Mat2, Norm);
}
template<typename T>
mmatrix<T> mmatrix<T>::distance(mmatrix<T> & Mat1, mmatrix<T> & Mat2, std::function<T(mmatrix<T>)> const& Norm){
    if(Mat1.col_size() != Mat2.col_size()){
        throw std::out_of_range("distance: Matrix1 col_size (" + std::to_string(Mat1.col_size()) + ") != Matrix2 col_size (" + std::to_string(Mat2.col_size()) + ")");
    }
    mmatrix<T> DistMat(Mat1.row_size(), Mat2.row_size());
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < Mat1.row_size(); i++){
            mmatrix<T> M(Mat1[i]);
            for(std::size_t j = 0; j < Mat2.row_size(); j++){
                DistMat[i][j] = Norm(M-Mat2[j]);
            }
        }
    #ifdef _OPENMP
    }
    #endif
    return DistMat;
}


template<typename T>
std::vector< meigen<T> > mmatrix<T>::eigen(mmatrix<T> && Mat, std::size_t VecNo, std::function<T(mmatrix<T>)> const& Norm){
    return eigen(Mat, VecNo, Norm);
}
template<typename T>
std::vector< meigen<T> > mmatrix<T>::eigen(mmatrix<T> & Mat, std::size_t VecNo, std::function<T(mmatrix<T>)> const& Norm){
    if(VecNo == 0){
        VecNo = Mat.row_size();
    }

    std::vector< meigen<T> > Eigens =  std::vector< meigen<T> >(VecNo);
    mmatrix<T> EigenMat = Mat;
    
    if(VecNo > EigenMat.row_size()){
        throw std::out_of_range("eigen: Matrix dimension is "+ Mat._Dimensions.to_string()
            + ", therefore number of "+ std::to_string(VecNo)+" eigen vectors is to high.");
    }

    for(std::size_t i = 0; i < VecNo; i++){
        Eigens[i] = meigen<T>::power_iteration(EigenMat, Norm);
        EigenMat -= Eigens[i].vector().transposition()*Eigens[i].vector()*Eigens[i].value();
    }
    return Eigens;
}


template<typename T>
T mmatrix<T>::vector_norm(mmatrix<T> && Vector, std::size_t LPNorm){
    return vector_norm(Vector, LPNorm);
}
template<typename T>
T mmatrix<T>::vector_norm(mmatrix<T> & Vector, std::size_t LPNorm){
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
T mmatrix<T>::l_p_norm(mmatrix<T> && Matrix, std::size_t Norm){
    return l_p_norm(Matrix,Norm);
}
template<typename T>
T mmatrix<T>::l_p_norm(mmatrix<T> & Matrix, std::size_t Norm){
    if(Matrix.row_size() != 1){
        throw std::out_of_range("l_p_norm: Matrix not in vector format; row dimension must be one.");
    }
    T UnSqr =  std::accumulate(Matrix.begin()->begin(),Matrix.begin()->end(), T(), [&Norm](T & SumPart, T & Element){
        return SumPart + std::pow(std::abs(Element),Norm);
    });
    return std::pow(UnSqr, 1.0/(double)Norm);
}
//TODO: solution to use reference of Matrix
template<typename T>
T mmatrix<T>::eucl_norm(mmatrix<T>  Matrix){
    return l_p_norm(Matrix, 2);
}
template<typename T>
T mmatrix<T>::taxicap_Norm(mmatrix<T>  Matrix){
    return l_p_norm(Matrix, 1);    
}
template<typename T>
const std::function<T(mmatrix<T>)> mmatrix<T>::euclid = &mmatrix<T>::eucl_norm;
template<typename T>
const std::function<T(mmatrix<T>)> mmatrix<T>::taxicap = &mmatrix<T>::taxicap_norm;


template<typename T>
mmatrix<T> mmatrix<T>::vector_norms(mmatrix<T> && Matrix, std::size_t Norm){
    return vector_norms(Matrix);
}
template<typename T>
mmatrix<T> mmatrix<T>::vector_norms(mmatrix<T> & Matrix, std::size_t Norm){
    return l_p_norms(Matrix,Norm);
}
template<typename T>
mmatrix<T> mmatrix<T>::vector_norms(mmatrix<T> && Matrix, std::function<mmatrix<T>(mmatrix<T>)> const& Norm){
    return vector_norms(Matrix, Norm);
}
template<typename T>
mmatrix<T> mmatrix<T>::vector_norms(mmatrix<T> & Matrix, std::function<mmatrix<T>(mmatrix<T>)> const& Norm){
    return Norm(Matrix);
}
template<typename T>
mmatrix<T> mmatrix<T>::l_p_norms(mmatrix<T> && Matrix, std::size_t Norm){
    return l_p_norms(Matrix, Norm);
}
template<typename T>
mmatrix<T> mmatrix<T>::l_p_norms(mmatrix<T> & Matrix, std::size_t Norm){
    mmatrix<T> Norms(1,Matrix.row_size());
    T * NormVec = &Norms.begin()->front();
    std::vector<T> * MVec = &Matrix.front();
    #ifdef _OPENMP
    #pragma omp parallel
    {
        #pragma omp for
    #endif
        for(std::size_t i = 0; i < Matrix.row_size(); i++){
            T UnSqr =  std::accumulate(MVec[i].begin(),MVec[i].end(), T(), [&Norm](T & SumPart, T & Element){
                return SumPart + std::pow(std::abs(Element),Norm);
            });
            NormVec[i] = std::pow(UnSqr, 1.0/(double)Norm);
        }
    #ifdef _OPENMP
    }
    #endif
    return Norms;
}
//TODO: solution to use reference of Matrix
template<typename T>
mmatrix<T> mmatrix<T>::eucl_norms(mmatrix<T>  Matrix){
    return l_p_norms(Matrix, 2);
}
template<typename T>
mmatrix<T> mmatrix<T>::taxicap_norms(mmatrix<T>  Matrix){
    return l_p_norms(Matrix, 1);    
}
template<typename T>
const std::function<mmatrix<T>(mmatrix<T>)> mmatrix<T>::euclids = &mmatrix<T>::eucl_norms;
template<typename T>
const std::function<mmatrix<T>(mmatrix<T>)> mmatrix<T>::taxicaps = &mmatrix<T>::taxicap_norms;


template<typename T>
mdimension mmatrix<T>::check_length_input(const std::vector< std::vector<T> > & Mat){
    mdimension MatDim;
    if(Mat.size() != 0){
        MatDim = mdimension(Mat.size(),Mat.begin()->size());
        for(auto iter = Mat.begin(); iter < Mat.end(); iter++){
            if(iter->size() != MatDim.Col){
                throw std::out_of_range("check_length_input: Column dimensions of submitted vector matrix are not conforming.");
            }
        }
    }
    else{
        throw std::out_of_range("check_length_input: Empty matrix submitted.");
    }
    return MatDim;
}

template<typename T>
mdimension mmatrix<T>::check_length_input(const std::initializer_list< std::initializer_list<T> > & Mat){
    mdimension MatDim;
    if(Mat.size() != 0){
        MatDim = mdimension(Mat.size(),Mat.begin()->size());
        for(auto iter = Mat.begin(); iter < Mat.end(); iter++){
            if(iter->size() != MatDim.Col){
                throw std::out_of_range("check_length_input: Column dimensions of submitted vector matrix are not conforming.");
            }
        }
    }
    else{
        throw std::out_of_range("check_length_input: Empty matrix submitted.");
    }
    return MatDim;
}

template<typename T>
std::size_t mmatrix<T>::threadNumber = 2;

template<typename T>
void mmatrix<T>::thread(std::size_t thrd){
    threadNumber = thrd;
    #ifdef _OPENMP
    omp_set_dynamic(0);
    omp_set_num_threads(threadNumber);
    #endif 
}

template<typename T>
std::size_t mmatrix<T>::thread(){
    return threadNumber;
}

#endif