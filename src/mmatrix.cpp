#include "mmatrix.hpp"

mmatrix::mmatrix(){
    _Dimensions._Row = 0, _Dimensions._Col = 0;
}
mmatrix::mmatrix(size_t Row, size_t Col, double Val){
    resize(Row,Col,Val);
}
mmatrix::mmatrix(const mdimension & Dim, double Val){
    resize(Dim,Val);
}
mmatrix::mmatrix(const mdimension && Dim, double Val){
    resize(Dim,Val);
}
mmatrix::mmatrix(const mmatrix && Mat){
    _Matrix = Mat._Matrix;
    _Dimensions = Mat._Dimensions;
}
mmatrix::mmatrix(const mmatrix & Mat){
    _Matrix = Mat._Matrix;
    _Dimensions = Mat._Dimensions;
}


void mmatrix::push_back(const std::vector<double> && Mat, bool EnsureSize){
    push_back(Mat, EnsureSize);
}
void mmatrix::push_back(const std::vector<double> & Mat, bool EnsureSize){
    push_back_row(Mat,EnsureSize);
}
void mmatrix::push_back_row(const std::vector<double> && Mat, bool EnsureSize){
    push_back_row(Mat, EnsureSize);
}
void mmatrix::push_back_row(const std::vector<double> & Mat, bool EnsureSize){
    if(_Dimensions._Col != Mat.size() && _Dimensions._Col != 0){
        throw std::out_of_range("Matrix col-dimensions "+ _Dimensions.to_string()
            + " and [1x" + std::to_string(Mat.size()) + " are not conforming.");
    }
    if( _Dimensions._Col == 0){
        _Dimensions._Col = Mat.size();
    }
    _Matrix.push_back(Mat);
    _Dimensions._Row++;
}
void mmatrix::push_back_col(const std::vector<double> && Mat, bool EnsureSize){
    push_back_col(Mat, EnsureSize);
}
void mmatrix::push_back_col(const std::vector<double> & Mat, bool EnsureSize){
    if(_Dimensions._Row != Mat.size() && _Dimensions._Row != 0){
        throw std::out_of_range("Matrix row-dimensions "+ _Dimensions.to_string()
            + " and [1x" + std::to_string(Mat.size()) + " are not conforming.");
    }
    if(_Dimensions._Row == 0){
        _Dimensions._Row = Mat.size();
        _Matrix.resize(Mat.size());
    }
    std::transform(_Matrix.begin(),_Matrix.end(),Mat.begin(),_Matrix.begin(),[](std::vector<double> & Vec, double Val){
        Vec.push_back(Val);
        return Vec;
    });
    _Dimensions._Col++;
}

void mmatrix::resize(size_t NewSize, double Val){
    resize(mdimension(NewSize,NewSize),Val);
}
void mmatrix::resize(size_t NewRow, size_t NewCol, double Val){
    resize(mdimension(NewRow,NewCol),Val);
}
void mmatrix::resize(const mdimension && Dim, double Val){
    resize(Dim,Val);
}
void mmatrix::resize(const mdimension & Dim, double Val){
    _Matrix.resize(Dim._Row);
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[&Dim, Val](std::vector<double> & Vec){
        Vec.resize(Dim._Col,Val);
        return Vec;
    });
    _Dimensions = Dim;
}

void mmatrix::reserve(size_t NewSize){
    reserve(mdimension(NewSize,NewSize));
}
void mmatrix::reserve(size_t NewRow, size_t NewCol){
    reserve(mdimension(NewRow,NewCol));
}
void mmatrix::reserve(const mdimension && Dim){
    reserve(Dim);
}
void mmatrix::reserve(const mdimension & Dim){
    _Matrix.reserve(Dim._Row);
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[&Dim](std::vector<double> & Vec){
        Vec.resize(Dim._Col);
        return Vec;
    });
}

void mmatrix::clear() noexcept{
    _Matrix.clear();
    _Dimensions = mdimension(0);
}


std::vector<double>& mmatrix::operator[](size_t Idx){
    return _Matrix[Idx];
}

mmatrix& mmatrix::operator+=(const mmatrix && Mat){
    return operator+=(Mat);
}
mmatrix& mmatrix::operator-=(const mmatrix && Mat){
    return operator-=(Mat);
}
mmatrix& mmatrix::operator+=(const mmatrix & Mat){
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),_Matrix.begin(),
    [](const std::vector<double> & VecA, const std::vector<double> & VecB){
        std::vector<double> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](double ValA, double ValB){
                return ValA + ValB;
            });
        return ResVec;
    });
    return *this;
}
mmatrix& mmatrix::operator-=(const mmatrix & Mat){
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),_Matrix.begin(),
    [](const std::vector<double> & VecA, const std::vector<double> & VecB){
        std::vector<double> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](double ValA, double ValB){
                return ValA - ValB;
            });
        return ResVec;
    });
    return *this;
}
mmatrix& mmatrix::operator+=(const double Add){
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[Add]
    (std::vector<double> & Vec){
        std::vector<double> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Add](double Val){
            return Val + Add;
        });
        return ResVec;
    });
    return *this;
}
mmatrix& mmatrix::operator-=(const double Add){
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[Add]
    (std::vector<double> & Vec){
        std::vector<double> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Add](double Val){
            return Val - Add;
        });
        return ResVec;
    });
    return *this;
}

mmatrix mmatrix::operator+(const mmatrix && Mat) const{
    return operator+(Mat);
}
mmatrix mmatrix::operator-(const mmatrix && Mat) const{
    return operator-(Mat);
}
mmatrix mmatrix::operator+(const mmatrix & Mat) const{
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),ResMat.begin(),
    [](const std::vector<double> & VecA, const std::vector<double> & VecB){
        std::vector<double> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](double ValA, double ValB){
                return ValA + ValB;
            });
        return ResVec;
    });
    return NewMat;
}
mmatrix mmatrix::operator-(const mmatrix & Mat) const{
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),ResMat.begin(),
    [](const std::vector<double> & VecA, const std::vector<double> & VecB){
        std::vector<double> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](double ValA, double ValB){
                return ValA - ValB;
            });
        return ResVec;
    });
    return NewMat;
}
mmatrix mmatrix::operator+(const double Add) const{
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),ResMat.begin(),
    [Add](const std::vector<double> & Vec){
        std::vector<double> ResVec(Vec.size());   
        std::transform(Vec.begin(),Vec.end(),ResVec.begin(),
            [Add](double Val){
                return Val + Add;
            });
        return ResVec;
    });
    return NewMat;
}
mmatrix mmatrix::operator-(const double Add) const{
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),ResMat.begin(),
    [Add](const std::vector<double> & Vec){
        std::vector<double> ResVec(Vec.size());   
        std::transform(Vec.begin(),Vec.end(),ResVec.begin(),
            [Add](double Val){
                return Val - Add;
            });
        return ResVec;
    });
    return NewMat;
}

mmatrix& mmatrix::operator*=(const mmatrix && Mat){
    return operator*=(Mat);
}
mmatrix& mmatrix::operator*=(const mmatrix & Mat){

}
mmatrix& mmatrix::operator*=(const double Mul){
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),
    [Mul](std::vector<double> & Vec){
        std::vector<double> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Mul](double Val){
            return Val * Mul;
        });
        return ResVec;
    });
    return *this;

}
mmatrix& mmatrix::operator/=(const double Mul){
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),
    [Mul](std::vector<double> & Vec){
        std::vector<double> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Mul](double Val){
            return Val / Mul;
        });
        return ResVec;
    });
    return *this;
}

mmatrix mmatrix::operator*( mmatrix && Mat){
    return operator*(Mat);
}
mmatrix mmatrix::operator*(mmatrix & Mat){
    mdimension NewDim = _Dimensions*Mat._Dimensions;
    mmatrix NewMat(NewDim);
    auto & MatL = _Matrix;
    auto MatR = Mat._Matrix;
    std::vector< std::vector<double> > & MultMat = NewMat._Matrix;

    std::vector<std::vector<double>::iterator> IterVec(MatR.size());
    std::transform(MatR.begin(), MatR.end(), IterVec.begin(), [](std::vector<double> & Vec){
        return Vec.begin();
    });

    std::transform(MatL.begin(), MatL.end(), MultMat.begin(), [&](std::vector<double> & Vec){
        std::vector<double> Row(NewDim._Col);
        auto CopyIter = IterVec;
        std::transform(Row.begin(),Row.end(),Row.begin(),[&CopyIter,Vec](double Init){
            double IP = std::inner_product(Vec.begin(),Vec.end(),CopyIter.begin(),Init,std::plus<double>(),[](double Val, std::vector<double>::iterator & Iter){
                return Val* (*Iter++);
            });
            return IP;
        });
        return Row;
    });
    return NewMat;
}
mmatrix mmatrix::operator*(const double Mul) const{
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),ResMat.begin(),
    [Mul](const std::vector<double> & Vec){
        std::vector<double> ResVec(Vec.size());   
        std::transform(Vec.begin(),Vec.end(),ResVec.begin(),
            [Mul](double Val){
                return Val * Mul;
            });
        return ResVec;
    });
    return NewMat;
}
mmatrix mmatrix::operator/(const double Mul) const{
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),ResMat.begin(),
    [Mul](const std::vector<double> & Vec){
        std::vector<double> ResVec(Vec.size());   
        std::transform(Vec.begin(),Vec.end(),ResVec.begin(),
            [Mul](double Val){
                return Val / Mul;
            });
        return ResVec;
    });
    return NewMat;
}

mmatrix& mmatrix::operator=(const mmatrix && Mat){
    return operator=(Mat);
}
mmatrix& mmatrix::operator=(const mmatrix & Mat){
    _Dimensions = Mat._Dimensions;
    _Matrix = Mat._Matrix;
    return *this;
}


mmatrix mmatrix::transposition(){
    mdimension NewDim(_Dimensions._Col,_Dimensions._Row);
    mmatrix NewMat(NewDim,0);
    std::vector< std::vector<double> > & MatrixT = NewMat._Matrix;
    std::vector<std::vector<double>::iterator> IterVec(_Matrix.size());
    std::transform(_Matrix.begin(),_Matrix.end(),IterVec.begin(),[](std::vector<double> & Vec){
        return Vec.begin();
    });
    std::transform(MatrixT.begin(),MatrixT.end(),MatrixT.begin(),[&IterVec](std::vector<double> & Vec){
        std::transform(IterVec.begin(),IterVec.end(),Vec.begin(),[](std::vector<double>::iterator & It){
            return std::move(*It++);
        });
        return Vec;
    });
    // #pragma omp parallel
    // {
    //     #pragma omp for
    //     for(int j = 0; j < Col; j++){
    //         for(int i = 0; i < Row; i++){
    //             MatrixT[j][i] = std::move(_Matrix[i][j]);
    //         }
    //     }
    // }
    return NewMat;
}
void mmatrix::transpose(){
    mmatrix NewMat = transposition();
    std::swap(_Dimensions,NewMat._Dimensions);
    std::swap(_Matrix,NewMat._Matrix);
}
mmatrix mmatrix::entry_mult(const mmatrix && Mat){
    return entry_mult(Mat);
}
mmatrix mmatrix::entry_mult(const mmatrix & Mat){
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),ResMat.begin(),
    [](const std::vector<double> & VecA, const std::vector<double> & VecB){
        std::vector<double> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](double ValA, double ValB){
                return ValA * ValB;
            });
        return ResVec;
    });
    return NewMat;
}
mmatrix& mmatrix::equal_entry_mult(const mmatrix && Mat){
    return equal_entry_mult(Mat);
}
mmatrix& mmatrix::equal_entry_mult(const mmatrix & Mat){
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),_Matrix.begin(),
    [](const std::vector<double> & VecA, const std::vector<double> & VecB){
        std::vector<double> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](double ValA, double ValB){
                return ValA * ValB;
            });
        return ResVec;
    });
    return *this;
}
mmatrix mmatrix::eigen_vectors() const{
    return mmatrix();
}
std::vector<double> mmatrix::eigen_values() const{
    return std::vector<double>();
}

std::string mmatrix::to_string(char Delimiter, char Separator,  char Border){
    std::string MatStr;
    for(auto & Row : _Matrix){
        MatStr += Border;
        for(auto & Sgn : Row){
            MatStr += std::to_string(Sgn) + Delimiter;
        }
        MatStr[MatStr.size()-1] = Border;
        MatStr += Separator;
    }
    return MatStr;
}

mdimension mmatrix::dimension() const{
    return _Dimensions;
}
mdimension mmatrix::size() const{
    return _Dimensions;
}
size_t mmatrix::row_size() const{
    return _Dimensions._Row;
}
size_t mmatrix::col_size() const{
    return _Dimensions._Col;
}