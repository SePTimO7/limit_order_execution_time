//
//  stod.h
//  arrival_times_limitorder
//
//  Created by Jarvis on 15/3/2017.
//  Copyright © 2017 Jarvis. All rights reserved.
//


#ifndef stod_h
#define stod_h

#include <string>


namespace Zhuang {
    
    // reference to http://stackoverflow.com/questions/20257582/convert-vectorstdstring-to-vectordouble
    
    std::vector<double>
    convertStringVectortoDoubleVector(const std::vector<std::string>& stringVector){
        std::vector<double> doubleVector(stringVector.size());
        std::transform(stringVector.begin(),
                       stringVector.end(),
                       doubleVector.begin(),
                       [](const std::string& val){return stod(val);}
                       );
        return doubleVector;
    }
    
    
    std::vector<std::vector<double> >
    convertStringMatrixtoDoubleMatrix(std::vector<std::vector<std::string> >& stringMatrix){
        std::vector<std::vector<double> > doubleMatrix;
        
        for (auto row : stringMatrix) {
            doubleMatrix.push_back(convertStringVectortoDoubleVector(row));
        }
        return doubleMatrix;
    }
    
    
    
    
    
}


#endif /* stod_h */
