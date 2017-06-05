//
//  jump.h
//  arrival_times_limitorder
//
//  Created by Jarvis on 15/3/2017.
//  Copyright © 2017 Jarvis. All rights reserved.
//

#ifndef jump_h
#define jump_h
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
class jump{
public:
    // number of events
    int num;
    // arrival time
    vector<double> time;
    // type can take two values, 1 or 2, 1 for the
    // first point process, and 2 for the second
    // point process
    vector<int> type;
    
    void clear_temp(){
        time.clear();
        type.clear();
    }
    
    void push_back_jump(const double t, const int ty){
        time.push_back(t);
        type.push_back(ty);
    }
    
    void print_part_for_test(size_t ob) const{
        for (size_t i = 0; i < ob; i++) {
            std::cout << std::setprecision(13) << time.at(i) <<" "<< type.at(i) <<std::endl;
        }
    }
    
    void printToFile(std::string outputfile) {
        // e.g. std::string outputfile = string("processedData.txt or csv etc.");
        std::ofstream processedData;
        processedData.open(outputfile);
        processedData.precision(15);

        for (size_t i = 0; i< time.size() ; i++){
            processedData << time.at(i) << "," << type.at(i) << std::endl;
        }
        
        processedData.close();
    }

};

#endif /* jump_h */
