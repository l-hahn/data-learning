import math,random
from numpy import matrix as mat

def point_to_string(Point):
    return " ".join(str(x) for x in Point)

def rotation(Point,Degree):
    if type(Point) != list:
        return Point
    if type(Degree) != list:
        Degree = [math.radians(Degree)]*len(Point);
    elif len(Point) != len(Degree) and len(Degree) != 3:
        return Point
    for i in range(len(Degree)):
        Degree[i] = math.radians(Degree[i])
    RotX = mat(([1,0,0],[0,math.cos(Degree[0]),-math.sin(Degree[0])],[0,math.sin(Degree[0]),math.cos(Degree[0])]))
    RotY = mat(([math.cos(Degree[0]),0,math.sin(Degree[0])],[0,1,0],[-math.sin(Degree[0]),0,math.cos(Degree[0])]))
    RotZ = mat(([math.cos(Degree[0]),-math.sin(Degree[0]),0],[math.sin(Degree[0]),math.cos(Degree[0]),0],[0,0,1]))
    return (Point*(RotZ*RotY*RotX)).tolist()[0]

#===MAIN=======================================================================#
nDataPart = 100;
nDim = 10
DataPoints = []
rotDeg = 45;

#--- d ------------------------------------------------------------------------#
xOff = 0;
yOff = 0;
for i in range(nDataPart):
    yOff += 1/nDataPart
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([xOff,yOff,0],rotDeg));
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point)
yOff = 0;
for i in range(nDataPart):
    yOff += 1/nDataPart/1.5;
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([-0.1*math.cos(yOff)+(1/13)+1e-3+xOff,0.3*math.sin(yOff)+math.sin(1/4),0],rotDeg))
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point);
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([-0.1*math.cos(yOff)+(1/13)+1e-3+xOff,-0.3*math.sin(yOff)+math.sin(1/4),0],rotDeg))
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point);
    
    

#--- a ------------------------------------------------------------------------#
xOff += 3e-2
yOff = 0;
for i in range(nDataPart):
    yOff += 1/nDataPart/2;
    Point = []
    #for p in range(2):
        #Point.append(random.random())
    Point.extend(rotation([xOff,yOff,0],rotDeg));
    #for p in range(nDim-2-3):
        #Point.append(random.random())
    DataPoints.append(Point)
yOff = 0;
for i in range(nDataPart):
    yOff += 1/nDataPart/1.5;
    Point = []
    #for p in range(2):
        #Point.append(random.random())
    Point.extend(rotation([-0.1*math.cos(yOff)+(1/13)+1e-3+xOff,0.3*math.sin(yOff)+math.sin(1/4),0],rotDeg))
    #for p in range(nDim-2-3):
        #Point.append(random.random())
    DataPoints.append(Point);
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([-0.1*math.cos(yOff)+(1/13)+1e-3+xOff,-0.3*math.sin(yOff)+math.sin(1/4),0],rotDeg))
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point);

#--- t ------------------------------------------------------------------------#
xOff += 3e-2
xOff -= 1.2e-2
yOff = 0.025;
tickOff = xOff- 3e-2/4
for i in range(nDataPart):
    yOff += 1/nDataPart/1.25;
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([xOff,yOff,0],rotDeg));
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point)
yOff = 0.55;
for i in range(nDataPart):
    tickOff += 3e-2/nDataPart/2;
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([tickOff,yOff,0],rotDeg));
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point)
yOff = 0.75;
xOff += 0.7e-2
for i in range(nDataPart):
    yOff += 1/nDataPart;
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([-7e-3*math.sin(yOff)+xOff,-7e-2*math.cos(yOff),0],rotDeg))
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point);
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([7e-3*math.sin(yOff)+xOff-8e-3,-7e-2*math.cos(yOff),0],rotDeg))
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point);
xOff -= 0.7e-2
xOff += 1.2e-2

#--- a ------------------------------------------------------------------------#
xOff += 3e-2
yOff = 0;
for i in range(nDataPart):
    yOff += 1/nDataPart/2;
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([xOff,yOff,0],rotDeg));
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point)
yOff = 0;
for i in range(nDataPart):
    yOff += 1/nDataPart/1.5;
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([-0.1*math.cos(yOff)+(1/13)+1e-3+xOff,0.3*math.sin(yOff)+math.sin(1/4),0],rotDeg))
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point);
    Point = []
    #for p in range(2):
    #    Point.append(random.random())
    Point.extend(rotation([-0.1*math.cos(yOff)+(1/13)+1e-3+xOff,-0.3*math.sin(yOff)+math.sin(1/4),0],rotDeg))
    #for p in range(nDim-2-3):
    #    Point.append(random.random())
    DataPoints.append(Point);

File = open("Hidden.dat","w")
for Point in DataPoints:
    File.write(point_to_string(Point)+"\n")
File.close()