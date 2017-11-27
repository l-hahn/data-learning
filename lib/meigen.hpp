#ifndef _MEIGEN_HPP_
#define _MEIGEN_HPP_

#define _USE_MATH_DEFINES
#include <cmath>

#include <algorithm>
#include <cstdlib>
#include <ctime>

template<typename T>
class mmatrix;

template<typename T = double>
class meigen{
    private:
        mmatrix<T> EigenVector;
        T EigenValue;

    public:
        meigen(mmatrix<T> && Vector, T Value);
        meigen(mmatrix<T> & Vector, T Value);

        mmatrix<T> vector();
        T value();

        static meigen<T> power_iteration(mmatrix<T> && SqrMatrix, std::function<T(mmatrix<T>)> const& Norm = mmatrix<T>::euclid);
        static meigen<T> power_iteration(mmatrix<T> & SqrMatrix, std::function<T(mmatrix<T>)> const& Norm = mmatrix<T>::euclid);
        static meigen<T> power_iteration(mmatrix<T> && SqrMatrix, mmatrix<T> && InitVector, std::function<T(mmatrix<T>)> const& Norm = mmatrix<T>::euclid);
        static meigen<T> power_iteration(mmatrix<T> & SqrMatrix, mmatrix<T> & InitVector, std::function<T(mmatrix<T>)> const& Norm = mmatrix<T>::euclid);
};

template<typename T>
meigen<T>::meigen(mmatrix<T> && Vector, T Value){
   EigenVector = Vector;
   EigenValue = Value;
}

template<typename T>
meigen<T>::meigen(mmatrix<T> & Vector, T Value){
    EigenVector = Vector;
    EigenValue = Value;
}

template<typename T>
mmatrix<T> meigen<T>::vector(){
    return EigenVector;
}

template<typename T>
T meigen<T>::value(){
    return EigenValue;
}

template<typename T>
meigen<T> meigen<T>::power_iteration(mmatrix<T> && SqrMatrix, std::function<T(mmatrix<T>)> const& Norm){
    return power_iteration(SqrMatrix, Norm);
}

template<typename T>
meigen<T> meigen<T>::power_iteration(mmatrix<T> & SqrMatrix, std::function<T(mmatrix<T>)> const& Norm){
    std::vector<T> RandVec(SqrMatrix.col_size());

    std::srand(std::time(0));
    std::transform(RandVec.begin(), RandVec.end(), RandVec.begin(),rand());
    mmatrix<T> RandInitVector(RandVec);
    
    return power_iteration(SqrMatrix, RandInitVector, Norm);
}

template<typename T>
meigen<T> meigen<T>::power_iteration(mmatrix<T> && SqrMatrix, mmatrix<T> && InitVector, std::function<T(mmatrix<T>)> const& Norm){
    power_iteration(SqrMatrix, InitVector, Norm);
}

template<typename T>
meigen<T> meigen<T>::power_iteration(mmatrix<T> & SqrMatrix, mmatrix<T> & InitVector, std::function<T(mmatrix<T>)> const& Norm){
    //TODO: Throw Exception for wrong matrix size!
    mmatrix<T> PreVec = InitVector, EigVec(PreVec * SqrMatrix);
    EigVec /= Norm(EigVec);

    double deg = std::acos(PreVec*EigVec.transposition())*180.0 / M_PI;

    while(deg < 1e-4){
        EigVec = PreVec * SqrMatrix;
        EigVec /= Norm(EigVec);
        deg = std::acos(PreVec*EigVec.transposition())*180.0 / M_PI;
    }
    T EigVal = EigVec * SqrMatrix * EigVec;
    
    return meigen(EigVec, EigVal);
}

#endif