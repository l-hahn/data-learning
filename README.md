# data-learning
Approach for implementing a library concerning data mining (PCA, MDS, etc.), machine learning (Perceptron, SVM, etc.) and clustering (k-means, etc.). Can be used in future projects, for instance in the field of genomic selection.

In lib-folder, all necessary code files can be found. Using $ ~ make , you can compile the test file from the src-folder.

Important is to include mmatrix.hpp, the "mathematical matrix" class and clustering, mining or learning.
All functions are defined within the scope data_learning::< category >::< class >, e.g. data_learning::clustering::kmeans

This personal project is being developed in freetime, so at some points there will be many changes, but at some other points in the future, there wont be changes within a few days.

As of 2021 I start continuing on this project; a plan besides finishing cpu implementation is to get it run on AMD GPUs with OpenCL.

If there are questions, please feel free to contact me:
  lhahn@data-learning.de
  
Best regards,
  Lars Hahn
