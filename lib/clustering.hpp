#ifndef _CLUSTERING_HPP_
#define _CLUSTERING_HPP_

#include <algorithm>
#include <ctime>
#include <stdexcept>
#include <string>
#include <unordered_set>
#include <vector>

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

                double cluster();
                std::vector<double> clustering(unsigned Steps = 1e10);

                mmatrix<T> data_matrix();
                mmatrix<T> prototypes();
                mmatrix<T> assignemtns();
                T threshold();
                unsigned k();

                std::vector<unsigned> labels();
                std::vector< std::vector<unsigned> > clusters();

                void reset();

            private:
                mmatrix<T> initial_proto(mmatrix<T> & Mat);
        };

        template<typename T>
        double kmeans<T>::_Threshold = T(1e-4);

        template<typename T>
        kmeans<T>::kmeans(unsigned K):_K(K){
            if(_K < 2){
                throw std::out_of_range("K, number of prototypes, has to be greater than 1.");
            }
            if(!clustering::_Seeded){
                std::srand(std::time(NULL));
                clustering::_Seeded = true;
            }
        }
        template<typename T>
        kmeans<T>::kmeans(mmatrix<T> && Mat, unsigned K):_K(K){
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
        kmeans<T>::kmeans(mmatrix<T> & Mat, unsigned K):_K(K){
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
            _DataMatrix = Mat;
            _Assignments = mmatrix<T>(_DataMatrix.row_size(), _K);
            _Prototypes = initial_proto();
        }
        template<typename T>
        void kmeans<T>::threshold(T thresh){
            _Threshold = thresh;
        }

        template<typename T>
        double kmeans<T>::cluster(){
            for(unsigned i = 0; i < _DataMatrix.row_size(); i++){
                mmatrix<T> Assignment = mmatrix<T>::vector_norms(_Prototypes - _DataMatrix[i], 2).transposition();
                _Assignments[i][std::max_element(_Assignments[i].begin(),_Assignments[i].end())-_Assignments[i].begin()] = T();
                unsigned Idx = std::max_element(Assignment[0].begin(),Assignment[0].end()) - Assignment[0].begin();
                _Assignments[Idx] = T(1);

                
            }
        }
        template<typename T>
        std::vector<double> kmeans<T>::clustering(unsigned Steps){
            std::vector<double> ReconstError();
            double Gradient;
            unsigned Idx = 1;

            ReconstError.push_back(cluster());
            T ClsErr;
            
            do{
                ClsErr = mmatrix<T>::min(mmatrix<T>::max(_Assignments.transposition()).transposition())[0][0];
                if(ClsErr == 0){
                    Idx = 1;
                    ReconstError.clear();
                    reset();
                    ReconstError.push_back(cluster());
                }
                Gradient = std::abs(ReconstError[Idx]-ReconstError[Idx-1])/(ReconstError[Idx-1]);
            }while(Idx < Steps && Gradient > _Threshold);
            return ReconstError();
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
        std::vector<unsigned> kmeans<T>::labels(){
            std::vector<unsigned> Labels(_Assignments.row_size());
            for(unsigned i = 0; i < _Assignments; i++){
                Labels[i] = std::max_element(_Assignments[i].begin(),_Assignments[i].end())-_Assignments[i].begin();
            }
            return labels;
        }
        template<typename T>
        std::vector< std::vector<unsigned> > kmeans<T>::clusters(){
            std::vector< std::vector<unsigned> > Clusters(_K);
            for(unsigned i = 0; i < _Assignments.row_size(); i++){
                Clusters[(std::max_element(_Assignments[i].begin(),_Assignments[i].end())-_Assignments[i].begin())].push_back(i);
            }
            return Clusters;
        }

        template<typename T>
        void kmeans<T>::reset(){
            _Assignments = mmatrix<T>(_DataMatrix.row_size(), _K);
            _Prototypes = initial_proto();
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