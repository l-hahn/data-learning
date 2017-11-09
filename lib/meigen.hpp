#ifndef _MEIGEN_HPP_
#define _MEIGEN_HPP_

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

        static power_iteration(mmatrix<T> && SqrMatrix);
        static power_iteration(mmatrix<T> & SqrMatrix);
        static power_iteration(mmatrix<T> && SqrMatrix, mmatrix<T> && InitVector);
        static power_iteration(mmatrix<T> & SqrMatrix, mmatrix<T> && InitVector);
}

#endif