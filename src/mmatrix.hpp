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
    public:
        mmatrix();
        mmatrix(size_t Row, size_t Col, T Val=T());
        mmatrix(const mdimension & Dim, T Val=T());
        mmatrix(const mdimension && Dim, T Val=T());
        mmatrix(const mmatrix<T> && Mat);
        mmatrix(const mmatrix<T> & Mat);


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

        mmatrix<T>& operator+=(const mmatrix<T> && Mat);
        mmatrix<T>& operator-=(const mmatrix<T> && Mat);
        mmatrix<T>& operator+=(const mmatrix<T> & Mat);
        mmatrix<T>& operator-=(const mmatrix<T> & Mat);
        mmatrix<T>& operator+=(const T Val);
        mmatrix<T>& operator-=(const T Val);

        mmatrix<T> operator+(const mmatrix<T> && Mat) const;
        mmatrix<T> operator-(const mmatrix<T> && Mat) const;
        mmatrix<T> operator+(const mmatrix<T> & Mat) const;
        mmatrix<T> operator-(const mmatrix<T> & Mat) const;
        mmatrix<T> operator+(const T Val) const;
        mmatrix<T> operator-(const T Val) const;

        mmatrix<T>& operator*=(mmatrix<T> && Mat);
        mmatrix<T>& operator*=(mmatrix<T> & Mat);
        mmatrix<T>& operator*=(const T Val);
        mmatrix<T>& operator/=(const T Val);

        mmatrix<T> operator*(mmatrix<T> && Mat);
        mmatrix<T> operator*(mmatrix<T> & Mat);
        mmatrix<T> operator*(const T Val) const;
        mmatrix<T> operator/(const T Val) const;

        mmatrix<T>& operator=(const mmatrix<T> && Mat);
        mmatrix<T>& operator=(const mmatrix<T> & Mat);


        mmatrix<T> transposition();
        void transpose();
        mmatrix<T> entry_mult(const mmatrix<T> && Mat);
        mmatrix<T> entry_mult(const mmatrix & Mat);
        mmatrix<T>& equal_entry_mult(const mmatrix<T> && Mat);
        mmatrix<T>& equal_entry_mult(const mmatrix<T> & Mat);
        mmatrix<T> eigen_vectors() const;
        std::vector<T> eigen_values() const;

        std::string to_string(char Delimiter = ' ', char Separator = '\n', char Border = 0);

        mdimension dimension() const;
        mdimension size() const;
        size_t row_size() const;
        size_t col_size() const;

        typedef typename std::vector<T>::iterator iterator;
        iterator begin();
        iterator end();

    private:
        void create_col_wrapper();
        std::vector< std::vector<T> > _Matrix;
        std::vector< std::vector< std::reference_wrapper<T> > > _MatrixT;
        mdimension _Dimensions;
        mdimension _DimensionsT;
};

#include "mmatrix.hpp"

template<typename T>
mmatrix<T>::mmatrix(){
    _Dimensions = mdimension(0);
    _DimensionsT = mdimension(_Dimensions.Col,_Dimensions.Row);
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
    create_col_wrapper();

}
template<typename T>
mmatrix<T>::mmatrix(const mmatrix<T> & Mat){
    _Matrix = Mat._Matrix;
    _Dimensions = Mat._Dimensions;
    create_col_wrapper();
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
            + " and [1x" + std::to_string(Mat.size()) + " are not conforming.");
    }
    if( _Dimensions.Col == 0){
        _Dimensions.Col = Mat.size();
    }
    _Matrix.push_back(Mat);
    _Dimensions.Row++;

    if(_DimensionsT.Row == 0){
        _MatrixT.resize(Mat.size());
    }
    std::transform(_MatrixT.begin(),_MatrixT.end(),(_Matrix.end()-1)->begin(),_MatrixT.begin(),[](std::vector<std::reference_wrapper<T> > & Vec, T & Val){
        Vec.push_back(std::ref(Val));
        return Vec;
    });
    _DimensionsT.Col++;

}
template<typename T>
void mmatrix<T>::push_back_col(const std::vector<T> && Mat, bool EnsureSize){
    push_back_col(Mat, EnsureSize);
}
template<typename T>
void mmatrix<T>::push_back_col(const std::vector<T> & Mat, bool EnsureSize){
    if(_Dimensions.Row != Mat.size() && _Dimensions.Row != 0){
        throw std::out_of_range("Matrix row-dimensions "+ _Dimensions.to_string()
            + " and [1x" + std::to_string(Mat.size()) + " are not conforming.");
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

    if(_DimensionsT.Col == 0){
        _MatrixT.resize(1);
    }

    _DimensionsT.Row++;
    _MatrixT.resize(_DimensionsT.Row);
    std::transform(_Matrix.begin(),_Matrix.end(),std::back_inserter(*(_MatrixT.end()-1)),[](std::vector<T> & Vec){
        return std::ref(*(Vec.end()-1));
    });
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
    create_col_wrapper();
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
    _MatrixT.reserve(Dim.Col);
    std::transform(_MatrixT.begin(),_MatrixT.end(),_MatrixT.begin(),[&Dim](std::vector< std::reference_wrapper<T> > & Vec){
        Vec.reserve(Dim.Row);
        return Vec;
    });
}

template<typename T>
void mmatrix<T>::clear() noexcept{
    _MatrixT.clear();
    _Matrix.clear();
    _Dimensions = mdimension(0);
    _DimensionsT = mdimension(0);
}


template<typename T>
std::vector<T>& mmatrix<T>::operator[](size_t Idx){
    return _Matrix[Idx];
}

template<typename T>
mmatrix<T>& mmatrix<T>::operator+=(const mmatrix<T> && Mat){
    return operator+=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(const mmatrix<T> && Mat){
    return operator-=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator+=(const mmatrix<T> & Mat){
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),_Matrix.begin(),
    [](const std::vector<T> & VecA, const std::vector<T> & VecB){
        std::vector<T> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](T ValA, T ValB){
                return ValA + ValB;
            });
        return ResVec;
    });
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(const mmatrix<T> & Mat){
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),_Matrix.begin(),
    [](const std::vector<T> & VecA, const std::vector<T> & VecB){
        std::vector<T> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](T ValA, T ValB){
                return ValA - ValB;
            });
        return ResVec;
    });
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator+=(const T Add){
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[Add]
    (std::vector<T> & Vec){
        std::vector<T> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Add](T Val){
            return Val + Add;
        });
        return ResVec;
    });
    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator-=(const T Add){
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[Add]
    (std::vector<T> & Vec){
        std::vector<T> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Add](T Val){
            return Val - Add;
        });
        return ResVec;
    });
    return *this;
}

template<typename T>
mmatrix<T> mmatrix<T>::operator+(const mmatrix<T> && Mat) const{
    return operator+(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(const mmatrix<T> && Mat) const{
    return operator-(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator+(const mmatrix<T> & Mat) const{
    mmatrix<T> NewMat(_Dimensions, 0);
    std::vector< std::vector<T> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),ResMat.begin(),
    [](const std::vector<T> & VecA, const std::vector<T> & VecB){
        std::vector<T> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](T ValA, T ValB){
                return ValA + ValB;
            });
        return ResVec;
    });
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(const mmatrix<T> & Mat) const{
    mmatrix<T> NewMat(_Dimensions, 0);
    std::vector< std::vector<T> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),ResMat.begin(),
    [](const std::vector<T> & VecA, const std::vector<T> & VecB){
        std::vector<T> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](T ValA, T ValB){
                return ValA - ValB;
            });
        return ResVec;
    });
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator+(const T Add) const{
    mmatrix<T> NewMat(_Dimensions, 0);
    std::vector< std::vector<T> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),ResMat.begin(),
    [Add](const std::vector<T> & Vec){
        std::vector<T> ResVec(Vec.size());   
        std::transform(Vec.begin(),Vec.end(),ResVec.begin(),
            [Add](T Val){
                return Val + Add;
            });
        return ResVec;
    });
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator-(const T Add) const{
    mmatrix<T> NewMat(_Dimensions, 0);
    std::vector< std::vector<T> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),ResMat.begin(),
    [Add](const std::vector<T> & Vec){
        std::vector<T> ResVec(Vec.size());   
        std::transform(Vec.begin(),Vec.end(),ResVec.begin(),
            [Add](T Val){
                return Val - Add;
            });
        return ResVec;
    });
    return NewMat;
}

template<typename T>
mmatrix<T>& mmatrix<T>::operator*=(mmatrix<T> && Mat){
    return operator*=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator*=(mmatrix<T> & Mat){
    mdimension NewDim = _Dimensions*Mat._Dimensions;
    auto & MatL = _Matrix;
    auto & MatR = Mat._MatrixT;

    std::vector< std::vector<T> > MultMat(NewDim.Row, std::vector<T>(NewDim.Col));

    std::transform(MatL.begin(),MatL.end(),MultMat.begin(),[&](std::vector<T> & VecL){
        std::vector<T> Row(NewDim.Row);
        std::transform(Row.begin(),Row.end(),MatR.begin(),Row.begin(),[&](T Init, std::vector< std::reference_wrapper<T> > & VecR){
            return std::inner_product(VecL.begin(),VecL.end(),VecR.begin(),Init);
        });
        return Row;
    });
    std::swap(NewDim,_Dimensions);
    std::swap(MatL,MultMat);
    create_col_wrapper();

    return *this;
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator*=(const T Mul){
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),
    [Mul](std::vector<T> & Vec){
        std::vector<T> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Mul](T Val){
            return Val * Mul;
        });
        return ResVec;
    });
    return *this;

}
template<typename T>
mmatrix<T>& mmatrix<T>::operator/=(const T Mul){
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),
    [Mul](std::vector<T> & Vec){
        std::vector<T> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Mul](T Val){
            return Val / Mul;
        });
        return ResVec;
    });
    return *this;
}

template<typename T>
mmatrix<T> mmatrix<T>::operator*(mmatrix<T> && Mat){
    return operator*(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::operator*(mmatrix<T> & Mat){
    mdimension NewDim = _Dimensions*Mat._Dimensions;
    mmatrix<T> NewMat(NewDim);
    auto & MatL = _Matrix;
    auto MatR = Mat._MatrixT;
    std::vector< std::vector<T> > & MultMat = NewMat._Matrix;

    std::transform(MatL.begin(),MatL.end(),MultMat.begin(),[&](std::vector<T> & VecL){
        std::vector<T> Row(NewDim.Row);
        std::transform(Row.begin(),Row.end(),MatR.begin(),Row.begin(),[&](T Init, std::vector< std::reference_wrapper<T> > & VecR){
            return std::inner_product(VecL.begin(),VecL.end(),VecR.begin(),Init);
        });
        return Row;
    });
    NewMat.create_col_wrapper();
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator*(const T Mul) const{
    mmatrix<T> NewMat(_Dimensions, 0);
    std::vector< std::vector<T> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),ResMat.begin(),
    [Mul](const std::vector<T> & Vec){
        std::vector<T> ResVec(Vec.size());   
        std::transform(Vec.begin(),Vec.end(),ResVec.begin(),
            [Mul](T Val){
                return Val * Mul;
            });
        return ResVec;
    });
    return NewMat;
}
template<typename T>
mmatrix<T> mmatrix<T>::operator/(const T Mul) const{
    mmatrix<T> NewMat(_Dimensions, 0);
    std::vector< std::vector<T> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),ResMat.begin(),
    [Mul](const std::vector<T> & Vec){
        std::vector<T> ResVec(Vec.size());   
        std::transform(Vec.begin(),Vec.end(),ResVec.begin(),
            [Mul](T Val){
                return Val / Mul;
            });
        return ResVec;
    });
    return NewMat;
}

template<typename T>
mmatrix<T>& mmatrix<T>::operator=(const mmatrix<T> && Mat){
    return operator=(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::operator=(const mmatrix<T> & Mat){
    _Dimensions = Mat._Dimensions;
    _DimensionsT = Mat._DimensionsT;
    _Matrix = Mat._Matrix;
    create_col_wrapper();
    return *this;
}

template<typename T>
mmatrix<T> mmatrix<T>::transposition(){
    mdimension NewDim(_Dimensions.Col,_Dimensions.Row);
    mmatrix<T> NewMat(NewDim,0);
    std::vector< std::vector<T> > & MatrixT = NewMat._Matrix;

    std::transform(_MatrixT.begin(),_MatrixT.end(), MatrixT.begin(),[](std::vector< std::reference_wrapper<T> > & Vec){
        return std::vector<T>(std::move(Vec.begin()),std::move(Vec.end()));
    });
    NewMat.create_col_wrapper();
    return NewMat;
}
template<typename T>
void mmatrix<T>::transpose(){
    _Dimensions = _DimensionsT;
    std::vector< std::vector<T> > MatrixT(_Dimensions.Row, std::vector<T>(_Dimensions.Col));
    std::transform(_MatrixT.begin(),_MatrixT.end(), MatrixT.begin(),[](std::vector< std::reference_wrapper<T> > & Vec){
        return std::vector<T>(std::move(Vec.begin()),std::move(Vec.end()));
    });
    std::swap(_Matrix,MatrixT);
    create_col_wrapper();
}
template<typename T>
mmatrix<T> mmatrix<T>::entry_mult(const mmatrix<T> && Mat){
    return entry_mult(Mat);
}
template<typename T>
mmatrix<T> mmatrix<T>::entry_mult(const mmatrix<T> & Mat){
    mmatrix<T> NewMat(_Dimensions, 0);
    std::vector< std::vector<T> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),ResMat.begin(),
    [](const std::vector<T> & VecA, const std::vector<T> & VecB){
        std::vector<T> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](T ValA, T ValB){
                return ValA * ValB;
            });
        return ResVec;
    });
    return NewMat;
}
template<typename T>
mmatrix<T>& mmatrix<T>::equal_entry_mult(const mmatrix<T> && Mat){
    return equal_entry_mult(Mat);
}
template<typename T>
mmatrix<T>& mmatrix<T>::equal_entry_mult(const mmatrix<T> & Mat){
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),_Matrix.begin(),
    [](const std::vector<T> & VecA, const std::vector<T> & VecB){
        std::vector<T> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](T ValA, T ValB){
                return ValA * ValB;
            });
        return ResVec;
    });
    return *this;
}
template<typename T>
mmatrix<T> mmatrix<T>::eigen_vectors() const{
    return mmatrix();
}
template<typename T>
std::vector<T> mmatrix<T>::eigen_values() const{
    return std::vector<T>();
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
void mmatrix<T>::create_col_wrapper(){
    _MatrixT.clear();
    _DimensionsT = mdimension(_Dimensions.Col,_Dimensions.Row);
    std::vector<typename std::vector<T>::iterator > IterVec(_Dimensions.Row);
    std::transform(_Matrix.begin(),_Matrix.end(),IterVec.begin(),[](std::vector<T> & Vec){
        return Vec.begin();
    });

    _MatrixT.resize(_DimensionsT.Row);
    std::transform(_MatrixT.begin(), _MatrixT.end(), _MatrixT.begin(),[&IterVec](std::vector< std::reference_wrapper<T> > & Vec){
        Vec.reserve(IterVec.size());
        std::transform(IterVec.begin(),IterVec.end(),std::back_inserter(Vec),[](typename std::vector<T>::iterator & It){
            return std::ref(*It++);
        });
        return Vec;
    });
}
#endif