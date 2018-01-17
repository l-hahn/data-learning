import random

def random_data(nData, nDim, muVec, sigVec):
    if type(muVec) != list:
        muVec = [muVec]*nDim
    elif len(muVec) != nDim:
        pass        
    if type(sigVec) != list:
        sigVec = [sigVec]*nDim;
    elif len(muVec) != nDiM:
        pass

    DataPoints = []
    for n in range(nData):
        point = [0]*nDim
        for i in range(nDim):
            point[i] = random.gauss(muVec[i],sigVec[i])
        DataPoints.append(point)
    return DataPoints

def point_to_string(Point):
	return " ".join(str(x) for x in Point)


#---MAIN-----------------------------------------------------------------------#

nData = 5000
nDim = 2
sigma = 0.25
Data = []

Data.extend(random_data(nData,nDim,[0,0],sigma))
Data.extend(random_data(nData,nDim,[0,1],sigma))
Data.extend(random_data(nData,nDim,[1,0],sigma))
Data.extend(random_data(nData,nDim,[1,1],sigma))

File = open("Cluster.dat","w")
for Point in Data:
    File.write(point_to_string(Point)+"\n")
File.close()
