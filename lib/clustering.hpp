#ifndef _CLUSTERING_HPP_
#define _CLUSTERING_HPP_

#include <ctime>
#include <stdexcept>
#include <string>
#include <unordered_set>

#include "mmatrix.hpp"

namespace data_learning{
  /*---clustering-------------------------------------------------------------*/
    namespace clustering{
        static bool _Seeded = false;
        
        template<typename T = double>
        class kmeans{
            private:
                mmatrix<T> _DataMatrix;
                mmatrix<T> _Prototypes;
                mmatrix<T> _Assignments;
                unsigned _K;
                static double _Threshold;

            public:
                kmeans(unsigned K);
                kmeans(mmatrix<T> && Mat, unsigned K);
                kmeans(mmatrix<T> & Mat, unsigned K);

                void initial_prototypes(mmatrix<T> & Mat);
                void data_matrix(mmatrix<T> && Mat);
                void data_matrix(mmatrix<T> & Mat);
                void threshold(T thresh);

                mmatrix<T> data_matrix();
                mmatrix<T> prototypes();
                mmatrix<T> assignemtns();
                T threshold();
                unsigned k();

                mmatrix<T> clusters();

            private:
                mmatrix<T> initial_proto(mmatrix<T> & Mat);
        };

        template<typename T>
        double kmeans<T>::_Threshold = T(1e-4);

        template<typename T>
        kmeans<T>::kmeans(unsigned K){
            _K = K;
            if(_K < 2){
                throw std::out_of_range("K, number of prototypes, has to be greater than 1.");
            }
            if(!clustering::_Seeded){
                std::srand(std::time(NULL));
                clustering::_Seeded = true;
            }
        }
        template<typename T>
        kmeans<T>::kmeans(mmatrix<T> && Mat, unsigned K){
            _K = K;
            if(_K < 2){
                throw std::out_of_range("K, number of prototypes, has to be greater than 1.");
            }
            if(!clustering::_Seeded){
                std::srand(std::time(NULL));
                clustering::_Seeded = true;
            }
            data_matrix(Mat);
        }
        template<typename T>
        kmeans<T>::kmeans(mmatrix<T> & Mat, unsigned K){
            _K = K;
            if(_K < 2){
                throw std::out_of_range("K, number of prototypes, has to be greater than 1.");
            }
            if(!clustering::_Seeded){
                std::srand(std::time(NULL));
                clustering::_Seeded = true;
            }
            data_matrix(Mat);
        }

        template<typename T>
        void kmeans<T>::initial_prototypes(mmatrix<T> & Mat){
            if(_Assignments.row_size() != 0){
                return;
            }
            if(Mat.row_size() != _K){
                throw std::out_of_range("Initial prototypes row size("+std::to_string(Mat.row_size())+") differs from number K("+std::to_string(_K)+")");
            }
            if(Mat.col_size() != _DataMatrix.col_size() && _DataMatrix.col_size() != 0){
                throw std::out_of_range("initial prototypes col size("+std::to_string(Mat.col_size())+") differs from data col size ("+std::to_string(_DataMatrix.col_size())+").");
            }
            _Prototypes = Mat;
        }
        template<typename T>
        void kmeans<T>::data_matrix(mmatrix<T> && Mat){
            data_matrix(Mat);
        }
        template<typename T>
        void kmeans<T>::data_matrix(mmatrix<T> & Mat){
            _Assignments.clear();
            _Prototypes = initial_proto();
            _DataMatrix = Mat;
        }
        template<typename T>
        void kmeans<T>::threshold(T thresh){

        }

        template<typename T>
        mmatrix<T> kmeans<T>::data_matrix(){
            return _DataMatrix;
        }
        template<typename T>
        mmatrix<T> kmeans<T>::prototypes(){
            return _Prototypes;
        }
        template<typename T>
        mmatrix<T> kmeans<T>::assignemtns(){
            return _Assignments;
        }
        template<typename T>
        T kmeans<T>::threshold(){
            return _Threshold;
        }
        template<typename T>
        unsigned kmeans<T>::k(){
            return _K;
        }

        template<typename T>
        mmatrix<T> kmeans<T>::clusters(){

        }

        template<typename T>
        mmatrix<T> kmeans<T>::initial_proto(mmatrix<T> & Mat){
            mmatrix<T> Protos;
            std::unordered_set<unsigned> Indices();
            unsigned i = 0;

            while(i < _K){
                unsigned idx = std::fmod(std::rand(),Mat.row_size());
                auto Search = Indices.find(idx);
                if(Search == Indices.end()){
                    Protos.push_back(Mat[idx]);
                    Indices.insert(idx);
                    i++;
                }
            }

            return Protos;
        }


      /*----------------------------------------------------------------------*/
        template<typename T = double>
        class emalgo{

        };


      /*----------------------------------------------------------------------*/
        template<typename T = double>
        class tvq{

        };
    };
};
#endif