#ifndef _MEIGEN_HPP_
#define _MEIGEN_HPP_

#include <algorithm>
#include <cstlib>
#include <ctime>

template<typename T>
class mmatrix<T>;

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

        static mmatrix<T> power_iteration(mmatrix<T> && SqrMatrix);
        static mmatrix<T> power_iteration(mmatrix<T> & SqrMatrix);
        static mmatrix<T> power_iteration(mmatrix<T> && SqrMatrix, mmatrix<T> && InitVector);
        static mmatrix<T> power_iteration(mmatrix<T> & SqrMatrix, mmatrix<T> && InitVector);
}

template<typename T>
meigen::meigen(matrix<T> & Vector, T Value){
    meigen(Vector,Value);
}

template<typename T>
meigen::meigen(matrix<T> & Vector, T Value){
    EigenVector = Vector;
    EigenValue = Value;
}

template<typename T>
mmatrix<T> meigen::vector(){
    return EigenVector;
}

template<typename T>
T meigen::value(){
    return EigenValue;
}

template<typename T>
mmatrix<T> power_iteration(mmatrix<T> && SqrMatrix){
    return power_iteration(SqrMatrix);
}

template<typename T>
mmatrix<T> power_iteration(mmatrix<T> & SqrMatrix){
    std::vector<T> RandVec(SqrMatrix.col_size());
    std::srand(std::time(0));
    std::transform(RandVec.begin(), RandVec.end(), RandVec.begin(),rand());

    mmatrix<T> RandInitVector(RandVec);
    
    return power_iteration(SqrMatrix, RandInitVector);
}

template<typename T>
mmatrix<T> power_iteration(mmatrix<T> && SqrMatrix, mmatrix<T> && InitVector, std::function<T(mmatrix<T>)> const& Norm){
    power_iteration(SqrMatrix, InitVector);
}

template<typename T>
mmatrix<T> power_iteration(mmatrix<T> & SqrMatrix, mmatrix<T> & InitVector, std::function<T(mmatrix<T>)> const& Norm){
    
}

#endif