#ifndef _MINING_HPP_
#define _MINING_HPP_

#include <cmath>
#include <vector>

#include "mmatrix.hpp"
#include "meigen.hpp"

namespace data_learning{
  /*---data-mining------------------------------------------------------------*/
    namespace mining{
        template<typename T = double>
        class pca{
            private:
                mmatrix<T> _DataMatrix;
                mmatrix<T> _CovMatrix;
                std::vector< meigen<T> > _Eigens;
                unsigned _EigenNumber;

            public:
                pca(unsigned EigNumber = 0);
                pca(mmatrix<T> && Mat, unsigned EigNumber = 0);
                pca(mmatrix<T> & Mat, unsigned EigNumber = 0);

                void set_matrix(mmatrix<T> && Mat);
                void set_matrix(mmatrix<T> & Mat);

                void eigen_number(unsigned EigNumber);
                unsigned eigen_number();

                std::vector<T> eigen_spectrum();
                mmatrix<T> principle_components(unsigned CompNumber = 0);
                mmatrix<T> principle_component(unsigned CompIdx);

        };

        template<typename T>
        pca<T>::pca(unsigned EigNumber){
            _EigenNumber = EigNumber;
        }
        template<typename T>
        pca<T>::pca(mmatrix<T> && Mat, unsigned EigNumber):_EigenNumber(EigNumber == 0 ? Mat.col_size() : EigNumber){
            set_matrix(Mat);
        }
        template<typename T>
        pca<T>::pca(mmatrix<T> & Mat, unsigned EigNumber):_EigenNumber(EigNumber == 0 ? Mat.col_size() : EigNumber){
            set_matrix(Mat);
        }

        template<typename T>
        void pca<T>::set_matrix(mmatrix<T> && Mat){
            _Eigens.clear();
            _DataMatrix = Mat;
            _CovMatrix = mmatrix<T>::covariance(Mat);
        }
        template<typename T>
        void pca<T>::set_matrix(mmatrix<T> & Mat){
            _Eigens.clear();
            _DataMatrix = Mat;
            _CovMatrix = mmatrix<T>::covariance(Mat);
        }

        template<typename T>
        void pca<T>::eigen_number(unsigned EigNumber){
            _EigenNumber = EigNumber;
        }
        template<typename T>
        unsigned pca<T>::eigen_number(){
            return _EigenNumber;
        }

      /*----------------------------------------------------------------------*/
        template<typename T = double>
        class mds{
            private:
                mmatrix<T> _DataMatrix;
                std::vector< meigen<T> > _Eigens;
                unsigned _EigenNumber;

            public:
                mds(unsigned EigNumber = 0);
                mds(mmatrix<T> && Mat, unsigned EigNumber = 0);
                mds(mmatrix<T> & Mat, unsigned EigNumber = 0);

                void set_matrix(mmatrix<T> && Mat);
                void set_matrix(mmatrix<T> & Mat);
        };


      /*----------------------------------------------------------------------*/
        template<typename T = double>
        class sammon{
            private:
                mmatrix<T> _DataMatrix;
                std::vector< meigen<T> > _Eigens;
                unsigned _EigenNumber;

            public:
                sammon(unsigned EigNumber = 0);
                sammon(mmatrix<T> && Mat, unsigned EigNumber = 0);
                sammon(mmatrix<T> & Mat, unsigned EigNumber = 0);

                void set_matrix(mmatrix<T> && Mat);
                void set_matrix(mmatrix<T> & Mat);
        };

        class kernelreg{

        };

    };
};
#endif