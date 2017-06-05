//
//  main.cpp
//  arrival_times_limitorder
//
//  Created by Jarvis on 15/3/2017.
//  Copyright © 2017 Jarvis. All rights reserved.
//

#include <iostream>
#include "CSVReader.h"
#include "stod.h"
#include "jump.h"
#include "MarketOrder.h"
using namespace Zhuang;

int main(int argc, const char * argv[]) {

    CSVReader test1("/Users/zhuang/Dropbox/share_Zhuang/CSV2/message.csv");
    auto message_temp = test1.readCSV();
    auto message = convertStringMatrixtoDoubleMatrix(message_temp);
    CSVReader test2("/Users/zhuang/Dropbox/share_Zhuang/CSV2/orderbook.csv");
    auto orderbook_temp = test2.readCSV();
    auto orderbook = convertStringMatrixtoDoubleMatrix(orderbook_temp);

    MarketOrder mo(message, orderbook);
    mo.findMarketOrder();
    
    //mo.printMarketAddress();
    //mo.printMarketAddressWithGroup();
    //std::cout << mo.address.size()<< " "<<mo.type.size() <<std::endl;
    
    jump myjump;
    myjump.num = static_cast<int>(mo.fetchAddress().size());
    for(int i = 0; i<mo.fetchAddress().size(); i++){
        double time = mo.fetchTime().at(i);
        int type = mo.fetchType().at(i);
        myjump.push_back_jump(time, type);
    }
    mo.printType();
    myjump.printToFile("arrival_times.csv");
    
    return 0;
}
