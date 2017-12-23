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
        mmatrix<T> _EigenVector;
        T _EigenValue;
        static double _Threshold;
        static T _RMin;
        static T _RMax;
        static std::size_t _MaxPowerVal;
        static bool _Seeded;

    public:
        meigen();
        meigen(mmatrix<T> && Vector, T Value);
        meigen(mmatrix<T> & Vector, T Value);

        mmatrix<T> vector();
        T value();

        static meigen<T> power_iteration(mmatrix<T> && SqrMatrix, std::function<T(mmatrix<T>)> const& Norm = mmatrix<T>::euclid);
        static meigen<T> power_iteration(mmatrix<T> & SqrMatrix, std::function<T(mmatrix<T>)> const& Norm = mmatrix<T>::euclid);
        static meigen<T> power_iteration(mmatrix<T> && SqrMatrix, mmatrix<T> && InitVector, std::function<T(mmatrix<T>)> const& Norm = mmatrix<T>::euclid);
        static meigen<T> power_iteration(mmatrix<T> & SqrMatrix, mmatrix<T> & InitVector, std::function<T(mmatrix<T>)> const& Norm = mmatrix<T>::euclid);

        static double threshold();
        static void threshold(double thresh);
        static std::size_t power_counter();
        static void power_counter(std::size_t MaxCtr);
};

template<typename T>
double meigen<T>::_Threshold = 1e-4;
template<typename T>
T meigen<T>::_RMax = T(1000);
template<typename T>
T meigen<T>::_RMin = T(0);
template<typename T>
std::size_t meigen<T>::_MaxPowerVal = 1e5;
template<typename T>
bool meigen<T>::_Seeded = false;

template<typename T>
meigen<T>::meigen(){
    if(!_Seeded){
        std::srand(std::time(NULL));
        _Seeded = true;
    }
};

template<typename T>
meigen<T>::meigen(mmatrix<T> && Vector, T Value){
    _EigenVector = Vector;
    _EigenValue = Value;
    if(!_Seeded){
        std::srand(std::time(NULL));
        _Seeded = true;
    }
}

template<typename T>
meigen<T>::meigen(mmatrix<T> & Vector, T Value){
    _EigenVector = Vector;
    _EigenValue = Value;
    if(!_Seeded){
        std::srand(std::time(NULL));
        _Seeded = true;
    }
}

template<typename T>
mmatrix<T> meigen<T>::vector(){
    return _EigenVector;
}

template<typename T>
T meigen<T>::value(){
    return _EigenValue;
}

template<typename T>
meigen<T> meigen<T>::power_iteration(mmatrix<T> && SqrMatrix, std::function<T(mmatrix<T>)> const& Norm){
    return power_iteration(SqrMatrix, Norm);
}

template<typename T>
meigen<T> meigen<T>::power_iteration(mmatrix<T> & SqrMatrix, std::function<T(mmatrix<T>)> const& Norm){
    std::vector<T> RandVec(SqrMatrix.col_size());

    std::transform(RandVec.begin(), RandVec.end(), RandVec.begin(),[](T & Tmp){
        return std::fmod(std::rand(),(_RMax-_RMin + 1)) + _RMin;
    });
    mmatrix<T> RandInitVector(RandVec);
    
    return power_iteration(SqrMatrix, RandInitVector, Norm);
}

template<typename T>
meigen<T> meigen<T>::power_iteration(mmatrix<T> && SqrMatrix, mmatrix<T> && InitVector, std::function<T(mmatrix<T>)> const& Norm){
    power_iteration(SqrMatrix, InitVector, Norm);
}

template<typename T>
meigen<T> meigen<T>::power_iteration(mmatrix<T> & SqrMatrix, mmatrix<T> & InitVector, std::function<T(mmatrix<T>)> const& Norm){
    if(SqrMatrix.row_size() != SqrMatrix.col_size()){
        throw std::out_of_range("power_iteration: Matrix has to be square matix, but it is "+SqrMatrix.size().to_string()+".");
    }
    mmatrix<T> PreVec = InitVector/Norm(InitVector), EigVec(PreVec * SqrMatrix);
    EigVec /= Norm(EigVec);

    double deg = std::acos((PreVec*EigVec.transposition())[0][0])*180.0 / M_PI;
    std::size_t RoundCtr = 0;
    while(deg > _Threshold && RoundCtr < _MaxPowerVal){
        RoundCtr++;
        PreVec = EigVec;
        EigVec = PreVec * SqrMatrix;
        EigVec /= Norm(EigVec);
        deg = std::acos((PreVec*EigVec.transposition())[0][0])*180.0 / M_PI;
    }
    T EigVal = (EigVec * (SqrMatrix * EigVec.transposition()))[0][0];
    return meigen(EigVec, EigVal);
}

template<typename T>
double meigen<T>::threshold(){
    return _Threshold;
}
template<typename T>
void meigen<T>::threshold(double Thresh){
    _Threshold = Thresh;
}
template<typename T>
std::size_t meigen<T>::power_counter(){
    return _MaxPowerVal;
}
template<typename T>
void meigen<T>::power_counter(std::size_t MaxCtr){
    _MaxPowerVal = MaxCtr;
}

#endif