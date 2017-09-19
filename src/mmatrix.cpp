#include "mmatrix.hpp"

mmatrix::mmatrix(){
    _Dimensions = mdimension(0);
}
mmatrix::mmatrix(size_t Row, size_t Col, double Val = 0){
    resize(Row,Col,Val);
}
mmatrix::mmatrix(const mdimension & Dim, double Val = 0){
    resize(Dim,Val);
}
mmatrix::mmatrix(const mdimension && Dim, double Val = 0){
    resize(Dim,Val);
}


void mmatrix::push_back(const mmatrix && Mat, bool EnsureSize){
    push_back(Mat, EnsureSize);
}
void mmatrix::push_back(const mmatrix & Mat, bool EnsureSize){
    push_back_row(Mat,EnsureSize);
}
void mmatrix::push_back_row(const mmatrix && Mat, bool EnsureSize){
    push_back_row(Mat, EnsureSize);
}
void mmatrix::push_back_row(const mmatrix & Mat, bool EnsureSize){
    if(_Dimensions._Col != ValList.size()){
        throw std::out_of_range("Matrix col-dimensions "+ _Dimensions.to_string()
            + " and " + Mat.dimension().to_string() + " are not conforming.");
    }
    _Matrix.push_back(ValList);
    _Dimensions._Row++;
}
void mmatrix::push_back_col(const mmatrix && Mat, bool EnsureSize){
    push_back_col(ValList, EnsureSize);
}
void mmatrix::push_back_col(const mmatrix & Mat, bool EnsureSize){
    if(_Dimensions._Row != ValList.size()){
        throw std::out_of_range("Matrix row-dimensions "+ _Dimensions.to_string()
            + " and " + Mat.dimension().to_string() + " are not conforming.");
    }
    auto InputIter = ValList.begin();
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[InputIter](std::vector<double> & Vec){
        Vec.push_back(*InputIter++);
        return Vec;
    });
    _Dimensions._Col++;
}

void mmatrix::resize(size_t NewSize, double Val = 0){
    resize(mdimension(NewSize,NewSize),Val);
}
void mmatrix::resize(size_t NewRow, NewCol, double Val = 0){
    resize(mdimension(NewRow,NewCol),Val);
}
void mmatrix::resize(const mdimension && Dim, double Val = 0){
    resize(Dim,Val);
}
void mmatrix::resize(const mdimension & Dim, double Val = 0){
    _Matrix.resize(Dim._Row, Val);
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[&Dim, Val](std::vector<double> & Vec){
        Vec.resize(Dim._Col,Val);
        return Vec;
    });
    _Dimensions = Dim;
}

void mmatrix::reserve(size_t NewSize){
    reserve(mdimension(NewSize,NewSize));
}
void mmatrix::reserve(size_t NewRow, NewCol){
    reserve(mdimension(NewSize,NewSize));
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
        std::vector<unsigned> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](unsigned ValA, unsigned ValB){
                return ValA + ValB;
            });
        return ResVec;
    });
    return *this;
}
mmatrix& mmatrix::operator-=(const mmatrix & Mat){
    std::transform(_Matrix.begin(),_Matrix.end(),Mat._Matrix.begin(),_Matrix.begin(),
    [](const std::vector<double> & VecA, const std::vector<double> & VecB){
        std::vector<unsigned> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](unsigned ValA, unsigned ValB){
                return ValA - ValB;
            });
        return ResVec;
    });
    return *this;
}
mmatrix& mmatrix::operator+=(const double Add){
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[Add]
    (std::vector<double> & Vec){
        std::vector<unsigned> ResVec(Vec.size());
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
        std::vector<unsigned> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Add](double Val){
            return Val - Add;
        });
        return ResVec;
    });
    return *this;
}

mmatrix& mmatrix::operator+(const mmatrix && Mat) const{
    return operator+(Mat);
}
mmatrix& mmatrix::operator-(const mmatrix && Mat) const{
    return operator-(Mat);
}
mmatrix& mmatrix::operator+(const mmatrix & Mat) const{
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(ResMat.begin(),ResMat.end(),Mat._Matrix.begin(),NewMat.begin(),
    [](const std::vector<double> & VecA, const std::vector<double> & VecB){
        std::vector<unsigned> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](unsigned ValA, unsigned ValB){
                return ValA + ValB;
            });
        return ResVec;
    });
    return NewMat;
}
mmatrix& mmatrix::operator-(const mmatrix & Mat) const{
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(ResMat.begin(),ResMat.end(),Mat._Matrix.begin(),NewMat.begin(),
    [](const std::vector<double> & VecA, const std::vector<double> & VecB){
        std::vector<unsigned> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),VecB.begin(),ResVec.begin(),
            [](unsigned ValA, unsigned ValB){
                return ValA - ValB;
            });
        return ResVec;
    });
    return NewMat;
}
mmatrix& mmatrix::operator+(const double Add) const{
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
mmatrix& mmatrix::operator-(const double Add) const{
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
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[Mul]
    (std::vector<double> & Vec){
        std::vector<double> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Mul](double Val){
            return Val * Mul;
        });
        return ResVec;
    });
    return *this;

}
mmatrix& mmatrix::operator/=(const double Mul){
    std::transform(_Matrix.begin(),_Matrix.end(),_Matrix.begin(),[Mul]
    (std::vector<double> & VecA){
        std::vector<double> ResVec(Vec.size());
        std::transform(Vec.begin(), Vec.end(),ResVec.begin(),[Mul](double Val){
            return Val / Mul;
        });
        return ResVec;
    });
    return *this;
}

mmatrix& mmatrix::operator*(const mmatrix && Mat) const{
    return operator*(Mat);
}
mmatrix& mmatrix::operator*(const mmatrix & Mat) const{

}
mmatrix& mmatrix::operator*(const double Val) const{
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),ResMat.begin(),
    [Val](const std::vector<double> & VecA){
        std::vector<double> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),ResVec.begin(),
            [Val](double ValA){
                return ValA * Val;
            });
        return ResVec;
    });
    return NewMat;
}
mmatrix& mmatrix::operator/(const double Val) const{
    mmatrix NewMat(_Dimensions, 0);
    std::vector< std::vector<double> > & ResMat = NewMat._Matrix;
    std::transform(_Matrix.begin(),_Matrix.end(),ResMat.begin(),
    [Val](const std::vector<double> & VecA){
        std::vector<double> ResVec(VecA.size());   
        std::transform(VecA.begin(),VecA.end(),ResVec.begin(),
            [Val](double ValA){
                return ValA / Val;
            });
        return ResVec;
    });
    return NewMat;
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