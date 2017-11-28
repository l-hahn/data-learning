function [EigenValues, EigenVectors] = PowerMethod(XdataMat,nEvs)
    [nDims,nVecs] = size(XdataMat);
    threshold = 1e-4;
    CovMat = (XdataMat*XdataMat')/(nVecs);
    EigenValues = zeros(1,nEvs);
    EigenVectors = zeros(nDims,nEvs);
    for Round = 1:nEvs;
        DirVec = rand(nDims,1);
        DirVec = DirVec/sqrt(DirVec'*DirVec);
        for i = 1:100;
            DirVecPrev = DirVec;
            WVec = CovMat*DirVec;
            DirVec = WVec/sqrt(WVec'*WVec);
            if acosd(DirVecPrev'*DirVec) < 1e-4;
                break;
            end;
        end;
        EigenVectors(:,Round) = DirVec;
        EigenValues(Round) = DirVec' * CovMat * DirVec;
        CovMat = CovMat - (EigenValues(Round)*EigenVectors(:,Round)*EigenVectors(:,Round)');
    end;
end