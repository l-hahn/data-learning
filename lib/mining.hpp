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

            public:
                pca();
                pca(mmatrix<T> && Mat);
                pca(mmatrix<T> & Mat);


                void set_matrix(mmatrix<T> && Mat);
                void set_matrix(mmatrix<T> & Mat);


                mmatrix<T> cov_matrix();
                mmatrix<T> data_matrix();
                std::vector< meigen<T> > eigen(unsigned EigNumber = 0);

                mmatrix<T> eigen_spectrum(bool normalise = true, unsigned EigNumber = 0);
                mmatrix<T> loadings(unsigned LoadNumber = 0);
                mmatrix<T> loading(unsigned LoadIdx);
                mmatrix<T> principle_components(unsigned CompNumber = 0);
                mmatrix<T> principle_component(unsigned CompIdx);

            private:
                void calc_eigen(unsigned EigNumber);
        };

        template<typename T>
        pca<T>::pca(){
        }
        template<typename T>
        pca<T>::pca(mmatrix<T> && Mat){
            set_matrix(Mat);
        }
        template<typename T>
        pca<T>::pca(mmatrix<T> & Mat){
            set_matrix(Mat);
        }

        template<typename T>
        void pca<T>::set_matrix(mmatrix<T> && Mat){
            _Eigens.clear();
            _DataMatrix = Mat;
        }
        template<typename T>
        void pca<T>::set_matrix(mmatrix<T> & Mat){
            _Eigens.clear();
            _DataMatrix = Mat;
        }

        template<typename T>
        mmatrix<T> pca<T>::cov_matrix(){
            if(_CovMatrix.size().Row == 0 || _CovMatrix.size().Col == 0){
                _CovMatrix = mmatrix<T>::covariance(_DataMatrix);
            }
            return _CovMatrix;
        }
        template<typename T>
        mmatrix<T> pca<T>::data_matrix(){
            return _DataMatrix;
        }
        template<typename T>
        std::vector< meigen<T> > pca<T>::eigen(unsigned EigNumber){
            if(_Eigens.size() < EigNumber || EigNumber == 0){
                calc_eigen();
            }
            return _Eigens;
        }

        template<typename T>
        mmatrix<T> pca<T>::eigen_spectrum(bool normalise, unsigned EigNumber){
            if(_Eigens.size() < EigNumber || EigNumber == 0){
                calc_eigen(EigNumber);
            }
            mmatrix<T> EigSpec = mmatrix<T>(1,EigNumber);
            T Sum = T();
            for(unsigned i = 0; i < EigNumber; i++){
                EigSpec[0][i] = _Eigens[i].value();
                Sum += _Eigens[i].value();
            }
            if(normalise){
                std::transform(EigSpec[0].begin(), EigSpec[0].end(), EigSpec[0].begin(), [Sum](T & Val){
                    return Val/Sum;
                });
            }
            return EigSpec;
        }
        template<typename T>
        mmatrix<T> pca<T>::loadings(unsigned LoadNumber){
            if(_Eigens.size() < LoadNumber || LoadNumber == 0){
                calc_eigen(LoadNumber);
            }
            mmatrix<T> Loadings = mmatrix<T>();
            for(meigen<T> Eigen : _Eigens){
                Loadings.push_back(Eigen.vector());
            }
            return Loadings;
        }
        template<typename T>
        mmatrix<T> pca<T>::loading(unsigned LoadIdx){
            if(_Eigens.size() < LoadIdx){
                calc_eigen(LoadIdx);
            }
            return _Eigens[LoadIdx].vector();
        }
        template<typename T>
        mmatrix<T> pca<T>::principle_components(unsigned CompNumber){
            if(_Eigens.size() < CompNumber || CompNumber == 0){
                calc_eigen(CompNumber);
            }
            mmatrix<T> PrinComp = _DataMatrix*loadings().transposition();
            return PrinComp;
        }
        template<typename T>
        mmatrix<T> pca<T>::principle_component(unsigned CompIdx){
            if(_Eigens.size() < CompIdx){
                calc_eigen(CompIdx);
            }
            return _DataMatrix*_Eigens[CompIdx].vector().transposition();
        }

        template<typename T>
        void pca<T>::calc_eigen(unsigned EigNumber){
            if(_CovMatrix.size().Row == 0 || _CovMatrix.size().Col == 0){
                _CovMatrix = mmatrix<T>::covariance(_DataMatrix);
            }
            if(EigNumber == 0){
                EigNumber = _CovMatrix.row_size();
            }
            if(_Eigens.size() == 0){
                _Eigens = mmatrix<T>::eigen(_CovMatrix, EigNumber);
            }
            else if(_Eigens.size() < EigNumber){
                std::vector< meigen<T> > remainEigen = mmatrix<T>::eigen(mmatrix<T>::reduced_covariance(_CovMatrix, _Eigens),EigNumber-_Eigens.size()); 
                _Eigens.insert(_Eigens.end(),remainEigen.begin(),remainEigen.end());
            }
        }

      /*----------------------------------------------------------------------*/
        template<typename T = double>
        class mds{
            private:
                mmatrix<T> _DataMatrix;
                std::vector< meigen<T> > _Eigens;

            public:
                mds();
                mds(mmatrix<T> && Mat);
                mds(mmatrix<T> & Mat);

                void set_matrix(mmatrix<T> && Mat);
                void set_matrix(mmatrix<T> & Mat);
        };

        template<typename T>
        mds<T>::mds(){
        }
        template<typename T>
        mds<T>::mds(mmatrix<T> && Mat){
            set_matrix(Mat);
        }
        template<typename T>
        mds<T>::mds(mmatrix<T> & Mat){
            set_matrix(Mat);
        }

        template<typename T>
        void mds<T>::set_matrix(mmatrix<T> && Mat){
            _Eigens.clear();
            _DataMatrix = Mat;
        }
        template<typename T>
        void mds<T>::set_matrix(mmatrix<T> & Mat){
            _Eigens.clear();
            _DataMatrix = Mat;
        }


      /*----------------------------------------------------------------------*/
        template<typename T = double>
        class sammon{
            private:
                mmatrix<T> _DataMatrix;
                std::vector< meigen<T> > _Eigens;

            public:
                sammon();
                sammon(mmatrix<T> && Mat);
                sammon(mmatrix<T> & Mat);

                void set_matrix(mmatrix<T> && Mat);
                void set_matrix(mmatrix<T> & Mat);
        };

        template<typename T>
        sammon<T>::sammon(){
        }
        template<typename T>
        sammon<T>::sammon(mmatrix<T> && Mat){
            set_matrix(Mat);
        }
        template<typename T>
        sammon<T>::sammon(mmatrix<T> & Mat){
            set_matrix(Mat);
        }

        template<typename T>
        void sammon<T>::set_matrix(mmatrix<T> && Mat){
            _Eigens.clear();
            _DataMatrix = Mat;
        }
        template<typename T>
        void sammon<T>::set_matrix(mmatrix<T> & Mat){
            _Eigens.clear();
            _DataMatrix = Mat;
        }


      /*----------------------------------------------------------------------*/
        class kernelreg{

        };

    };
};
#endif