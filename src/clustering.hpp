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
      /*---KMeans-Clutering---------------------------------------------------*/
        template<typename T = double>
        class kmeans{
            private:
                mmatrix<T> _DataMatrix;
                mmatrix<T> _Prototypes;
                mmatrix<T> _Assignments;
                std::size_t _K;
                static double _Threshold;

            public:
                kmeans(std::size_t K);
                kmeans(mmatrix<T> && Mat, std::size_t K);
                kmeans(mmatrix<T> & Mat, std::size_t K);

                void initial_prototypes(mmatrix<T> & Mat);
                void data_matrix(mmatrix<T> && Mat);
                void data_matrix(mmatrix<T> & Mat);
                void threshold(T thresh);

                double cluster();
                std::vector<double> clustering(std::size_t Steps = 1e3);

                mmatrix<T> data_matrix();
                mmatrix<T> prototypes();
                mmatrix<T> assignments();
                T threshold();
                std::size_t k();

                std::vector<std::size_t> labels();
                std::vector< std::vector<std::size_t> > label_clusters();
                std::vector< mmatrix<T> > clusters();

                void reset();

            private:
                mmatrix<T> initial_proto();
                void initial_assign();
                void initialisation();
        };

        


      /*---Expectation-Maximisation-Clustering--------------------------------*/
        template<typename T = double>
        class emcluster{
            private:
                mmatrix<T> _DataMatrix;
                mmatrix<T> _Prototypes;
                mmatrix<T> _Assignments;
                mmatrix<T> _ClusterProb;
                std::size_t _K;
                double _Sigma;
                double _SigmaInit;
                static double _Threshold;

            public:
                emcluster(std::size_t K, double sigma = 1e-4);
                emcluster(mmatrix<T> && Mat, std::size_t K, double sigma = 1e-4);
                emcluster(mmatrix<T> & Mat, std::size_t K, double sigma = 1e-4);

                void initial_prototypes(mmatrix<T> & Mat);
                void data_matrix(mmatrix<T> && Mat);
                void data_matrix(mmatrix<T> & Mat);
                void probability_matrix(mmatrix<T> && Mat);
                void probability_matrix(mmatrix<T> & Mat);
                void threshold(T thresh);
                void sigma(double sigma);

                double cluster();
                std::vector<double> clustering(std::size_t Steps = 1e3);

                mmatrix<T> data_matrix();
                mmatrix<T> prototypes();
                mmatrix<T> assignments();
                mmatrix<T> probability_matrix();
                T threshold();
                double sigma();
                std::size_t k();

                std::vector<std::size_t> labels();
                std::vector< std::vector<std::size_t> > label_clusters();
                std::vector< mmatrix<T> > clusters();

                void reset();

            private:
                void init_kmeans();
                void initialisation();
        };

        template<typename T>
        double emcluster<T>::_Threshold = 1e-4;

        template<typename T>
        emcluster<T>::emcluster(std::size_t K, double sigma):_K(K),_Sigma(sigma),_SigmaInit(sigma){
            if(_K < 2){
                throw std::out_of_range("K, number of prototypes, has to be greater than 1.");
            }
            if(!clustering::_Seeded){
                std::srand(std::time(NULL));
                clustering::_Seeded = true;
            }
        }
        template<typename T>
        emcluster<T>::emcluster(mmatrix<T> && Mat, std::size_t K, double sigma):_K(K),_Sigma(sigma),_SigmaInit(sigma){
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
        emcluster<T>::emcluster(mmatrix<T> & Mat, std::size_t K, double sigma):_K(K),_Sigma(sigma),_SigmaInit(sigma){
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
        void emcluster<T>::initial_prototypes(mmatrix<T> & Mat){
            if(Mat.row_size() != _K){
                throw std::out_of_range("Initial prototypes row size("+
                std::to_string(Mat.row_size())+") differs from number K("+
                std::to_string(_K)+")");
            }
            if(Mat.col_size() != _DataMatrix.col_size() && _DataMatrix.col_size() != 0){
                throw std::out_of_range("initial prototypes col size("+
                std::to_string(Mat.col_size())+") differs from data col size ("+
                std::to_string(_DataMatrix.col_size())+").");
            }
            _Prototypes = Mat;
            initialisation();
        }
        template<typename T>
        void emcluster<T>::data_matrix(mmatrix<T> && Mat){
            data_matrix(Mat);
        }
        template<typename T>
        void emcluster<T>::data_matrix(mmatrix<T> & Mat){
            _DataMatrix = Mat;
            init_kmeans();
        }
        template<typename T>
        void emcluster<T>::probability_matrix(mmatrix<T> && Mat){
            probability_matrix(Mat);
        }
        template<typename T>
        void emcluster<T>::probability_matrix(mmatrix<T> & Mat){
            _ClusterProb = Mat;
            initialisation();
        }
        template<typename T>
        void emcluster<T>::threshold(T thresh){
            _Threshold = thresh;
        }
        template<typename T>
        void emcluster<T>::sigma(double sigma){
            _Sigma = sigma;
            _SigmaInit = sigma;
        }

        template<typename T>
        double emcluster<T>::cluster(){
            
            _ClusterProb = mmatrix<T>::sum(_Assignments.transposition())/(T)_DataMatrix.row_size();
            for(std::size_t i = 0; i < _K; i++){
                mmatrix<T> NewProto = _DataMatrix.vec_entry_mult(_Assignments.transposition()[i]);
                _Prototypes[i] = (mmatrix<T>::sum(NewProto.transposition())/mmatrix<T>::sum(_Assignments.transposition()[i])[0][0])[0];
            }
            double NewSigma = 0;
            for(std::size_t i = 0; i < _DataMatrix.row_size(); i++){
                NewSigma += (double)(mmatrix<T>::vector_norms(_Prototypes - _DataMatrix[i],mmatrix<T>::euclids)*_Assignments[i])[0][0];
            }
            _Sigma = NewSigma/(_DataMatrix.row_size()*_DataMatrix.col_size());
        }
        template<typename T>
        std::vector<double> emcluster<T>::clustering(std::size_t Steps){
            std::vector<double> ReconstError;

            ReconstError.push_back(cluster());

            for(std::size_t i = 1; i < Steps; i++){
                ReconstError.push_back(cluster());
                if(((ReconstError[i-1]-ReconstError[i])/ReconstError[i-1]) < _Threshold){
                    break;
                }                
            }

            return ReconstError;
        }

        template<typename T>
        mmatrix<T> emcluster<T>::data_matrix(){
            return _DataMatrix;
        }
        template<typename T>
        mmatrix<T> emcluster<T>::prototypes(){
            return _Prototypes;
        }
        template<typename T>
        mmatrix<T> emcluster<T>::assignments(){
            return _Assignments;
        }
        template<typename T>
        mmatrix<T> emcluster<T>::probability_matrix(){
            return _ClusterProb;
        }
        template<typename T>
        T emcluster<T>::threshold(){
            return _Threshold;
        }
        template<typename T>
        double emcluster<T>::sigma(){
            return _Sigma;
        }
        template<typename T>
        std::size_t emcluster<T>::k(){
            return _K;
        }

        template<typename T>
        std::vector<std::size_t> emcluster<T>::labels(){
            std::vector<std::size_t> Labels(_Assignments.row_size());
            for(std::size_t i = 0; i < _Assignments; i++){
                Labels[i] = std::max_element(_Assignments[i].begin(),
                    _Assignments[i].end())-_Assignments[i].begin();
            }
            return labels;
        }
        template<typename T>
        std::vector< std::vector<std::size_t> > emcluster<T>::label_clusters(){
            std::vector< std::vector<std::size_t> > Clusters(_K);
            for(std::size_t i = 0; i < _Assignments.row_size(); i++){
                Clusters[(std::max_element(_Assignments[i].begin(),
                    _Assignments[i].end())-_Assignments[i].begin())].push_back(i);
            }
            return Clusters;
        }
        template<typename T>
        std::vector< mmatrix<T> > emcluster<T>::clusters(){
            std::vector< mmatrix<T> > Clusters(_K);
            std::vector< std::vector<std::size_t> > cluster_label = label_clusters();
            for(std::size_t i = 0; i < _K; i++){
                Clusters[i].push_back(_Prototypes[i]);
                for(std::size_t j = 0; j < cluster_label[i].size(); j++){
                    Clusters[i].push_back(_DataMatrix[cluster_label[i][j]]);
                }
            }
            return Clusters;
        }

        template<typename T>
        void emcluster<T>::reset(){
            _Sigma = _SigmaInit;
            init_kmeans();
        }

        template<typename T>
        void emcluster<T>::init_kmeans(){
            kmeans<T> tmp_cluster(_DataMatrix,_K);
            tmp_cluster.clustering();
            _Prototypes = tmp_cluster.prototypes();
            _Assignments = tmp_cluster.assignments();
        }
        template<typename T>
        void emcluster<T>::initialisation(){
            if(_Prototypes.row_size() != _K){
                throw std::out_of_range("Initial prototypes row size("+
                    std::to_string(_Prototypes.row_size())+
                    ") differs from number K("+std::to_string(_K)+")");
            }
            if(_Prototypes.row_size() != _DataMatrix.col_size() && _DataMatrix.col_size() != 0){
                throw std::out_of_range("initial prototypes col size("+
                    std::to_string(_Prototypes.col_size())+
                    ") differs from data col size ("+
                    std::to_string(_DataMatrix.col_size())+").");
            }
            if(_ClusterProb.row_size() == _K){
                _ClusterProb.transpose();
            }
            if(_ClusterProb.col_size() != _K){
                throw std::out_of_range("Initial probabilities col size("+
                    std::to_string(_ClusterProb.col_size())+
                    ") differs from number K("+std::to_string(_K)+")");
            }
        }











      /*---Topograpic-Vector-Quantorisation-----------------------------------*/
        template<typename T = double>
        class tvq{

        };











      /*---KMeans-------------------------------------------------------------*/ 
        template<typename T>
        double kmeans<T>::_Threshold = 1e-4;

        template<typename T>
        kmeans<T>::kmeans(std::size_t K):_K(K){
            if(_K < 2){
                throw std::out_of_range("K, number of prototypes, has to be greater than 1.");
            }
            if(!clustering::_Seeded){
                std::srand(std::time(NULL));
                clustering::_Seeded = true;
            }
        }
        template<typename T>
        kmeans<T>::kmeans(mmatrix<T> && Mat, std::size_t K):_K(K){
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
        kmeans<T>::kmeans(mmatrix<T> & Mat, std::size_t K):_K(K){
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
                throw std::out_of_range("Initial prototypes row size("+
                    std::to_string(Mat.row_size())+") differs from number K("+
                    std::to_string(_K)+")");
            }
            if(Mat.col_size() != _DataMatrix.col_size() && _DataMatrix.col_size() != 0){
                throw std::out_of_range("initial prototypes col size("+
                std::to_string(Mat.col_size())+") differs from data col size ("+
                std::to_string(_DataMatrix.col_size())+").");
            }
            _Prototypes = Mat;
            initial_assign();
        }
        template<typename T>
        void kmeans<T>::data_matrix(mmatrix<T> && Mat){
            data_matrix(Mat);
        }
        template<typename T>
        void kmeans<T>::data_matrix(mmatrix<T> & Mat){
            _DataMatrix = Mat;
            initialisation();
        }
        template<typename T>
        void kmeans<T>::threshold(T thresh){
            _Threshold = thresh;
        }

        template<typename T>
        double kmeans<T>::cluster(){
            double ReconstError = 0;
            for(std::size_t i = 0; i < _DataMatrix.row_size(); i++){
                mmatrix<T> Assignment = mmatrix<T>::vector_norms(_Prototypes - _DataMatrix[i], mmatrix<T>::euclids);
                _Assignments[i][std::max_element(_Assignments[i].begin(),_Assignments[i].end())-_Assignments[i].begin()] = T(0);
                std::size_t Idx = std::max_element(Assignment[0].begin(),Assignment[0].end()) - Assignment[0].begin();
                _Assignments[i][Idx] = T(1);   
            }
            for(std::size_t i = 0; i < _K; i++){
                mmatrix<T> NewProto = _DataMatrix.vec_entry_mult(_Assignments.transposition()[i]);
                _Prototypes[i] = (mmatrix<T>::sum(NewProto.transposition())/mmatrix<T>::sum(_Assignments.transposition()[i])[0][0])[0];
            }
            for(std::size_t i = 0; i < _DataMatrix.row_size(); i++){
                ReconstError += (double)(mmatrix<T>::vector_norms(_Prototypes - _DataMatrix[i],mmatrix<T>::euclids)*_Assignments[i])[0][0];
            }
            return ReconstError*_DataMatrix.row_size();
        }
        template<typename T>
        std::vector<double> kmeans<T>::clustering(std::size_t Steps){
            std::vector<double> ReconstError;
            std::size_t Idx = 0, Try = 0;
            double Gradient = 1, Diff = 1;

            while(Try < Steps){
                ReconstError.push_back(cluster());
                Try++, Idx++;
                if(std::abs(mmatrix<T>::min(mmatrix<T>::max(_Assignments.transposition()))[0][0]) < 1e-10){
                    while(std::abs(mmatrix<T>::min(mmatrix<T>::max(_Assignments.transposition()))[0][0]) < 1e-10){
                        ReconstError.clear();
                        initialisation();
                        ReconstError.push_back(cluster());
                    }
                    Idx = 1;
                    Gradient = 1;
                }

                if(Idx > 1){
                    Gradient = std::fabs((ReconstError[Idx-2]-ReconstError[Idx-1])/(ReconstError[Idx-2]));
                }
                if(Idx > 2){
                    Diff = std::fabs(ReconstError[Idx-1]-ReconstError[Idx-3]);
                }
                if(Gradient < _Threshold || std::fabs(ReconstError[Idx-1]) == 0 || Diff == 0 ){
                    break;
                }   
            }

            return ReconstError;
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
        mmatrix<T> kmeans<T>::assignments(){
            return _Assignments;
        }
        template<typename T>
        T kmeans<T>::threshold(){
            return _Threshold;
        }
        template<typename T>
        std::size_t kmeans<T>::k(){
            return _K;
        }

        template<typename T>
        std::vector<std::size_t> kmeans<T>::labels(){
            std::vector<std::size_t> Labels(_Assignments.row_size());
            for(std::size_t i = 0; i < _Assignments; i++){
                Labels[i] = std::max_element(_Assignments[i].begin(),_Assignments[i].end())-_Assignments[i].begin();
            }
            return labels;
        }
        template<typename T>
        std::vector< std::vector<std::size_t> > kmeans<T>::label_clusters(){
            std::vector< std::vector<std::size_t> > Clusters(_K);
            for(std::size_t i = 0; i < _Assignments.row_size(); i++){
                Clusters[(std::max_element(_Assignments[i].begin(),_Assignments[i].end())-_Assignments[i].begin())].push_back(i);
            }
            return Clusters;
        }
        template<typename T>
        std::vector< mmatrix<T> > kmeans<T>::clusters(){
            std::vector< mmatrix<T> > Clusters(_K);
            std::vector< std::vector<std::size_t> > cluster_label = label_clusters();
            for(std::size_t i = 0; i < _K; i++){
                Clusters[i].push_back(_Prototypes[i]);
                for(std::size_t j = 0; j < cluster_label[i].size(); j++){
                    Clusters[i].push_back(_DataMatrix[cluster_label[i][j]]);
                }
            }
            return Clusters;
        }

        template<typename T>
        void kmeans<T>::reset(){
            _Prototypes = initial_proto();
            initial_assign();
        }

        template<typename T>
        mmatrix<T> kmeans<T>::initial_proto(){
            mmatrix<T> Protos;
            std::unordered_set<std::size_t> Indices;
            std::size_t i = 0, idx;

            while(i < _K){
                idx = std::fmod(std::rand(),_DataMatrix.row_size());
                auto Search = Indices.find(idx);
                if(Search == Indices.end()){
                    Protos.push_back(_DataMatrix[idx]);
                    Indices.insert(idx);
                    i++;
                }
            }

            return Protos;
        }
        template<typename T>
        void kmeans<T>::initial_assign(){
            mmatrix<T> Assignment;
            std::size_t Idx;
            for(std::size_t i = 0; i < _DataMatrix.row_size(); i++){
                Assignment = mmatrix<T>::vector_norms(_Prototypes - _DataMatrix[i], mmatrix<T>::euclids);
                Idx = std::max_element(Assignment[0].begin(),Assignment[0].end()) - Assignment[0].begin();
                _Assignments[i][Idx] = T(1);
            }
        }

        template<typename T>
        void kmeans<T>::initialisation(){
            do{
                _Assignments = mmatrix<T>(_DataMatrix.row_size(), _K);
                _Prototypes = initial_proto();
                initial_assign();
            }while(std::abs(mmatrix<T>::min(mmatrix<T>::max(_Assignments.transposition()))[0][0]) <1e-10);
        }
    };
};
#endif
