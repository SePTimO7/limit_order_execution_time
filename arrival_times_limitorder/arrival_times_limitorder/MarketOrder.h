//
//  MarketOrder.h
//  arrival_times_limitorder
//
//  Created by Jarvis on 25/3/2017.
//  Copyright © 2017 Jarvis. All rights reserved.
//

#ifndef MarketOrder_h
#define MarketOrder_h

namespace Zhuang {
    
    typedef const vector<vector<double> > constData;
    #define DeltaTime 1.0e-6

    class MarketOrder{
    private:
        vector<int> address;
        vector<int> type; // 1 for market buy and 2 for market sell
        vector<double> time;
        vector<int> bigOrderAddress;
        const size_t totalRecords;
        constData Message_, Orderbook_;
        
        int findSuccNumK(const int& i){
            if (!(Message_[i][1] == 4 || Message_[i][1] == 5)) return 0;
            if (i >= totalRecords-1) return 0;
            int k = 1;
            auto mes = Message_[i];
            double time = mes[0];
            int direction = mes[5];
            int id = mes[2];
            
            while (Message_[i+k][1] == 4 || Message_[i+k][1] == 5) { // continuous execution
                if(Message_[i+k][5]!=direction) return k; // the same direction
                if(Message_[i+k][0] - time >= DeltaTime) return k; // time constriant
                if(Message_[i+k][2] == id && id != 0) return k; // id constriant
                // if same id and both are not hidden executions, they must belong to two seperate market orders
                // if(Message_[i+k][2] == id && id == 0)
                // if both hidden executions and code arrives here, we consider  them as a whole market order till now, k should be added by 1
                k++;
            }
            return k;
        }
        
        
    public:
        MarketOrder(constData& Message,
                    constData& Orderbook): Message_(Message),
        Orderbook_(Orderbook),
        totalRecords(Message.size()) {};
        
        void findMarketOrder(){
            for (int i = 1, increment = 1; i < totalRecords; i = i + increment) {
                increment = 1;
                auto mes = Message_[i];
                double time = mes[0];
                int direction = mes[5];
                int k=findSuccNumK(i);
                if (k>1) {
                    // we consider these k market orders as a whole market order
                    increment = k;
                    address.push_back(i);
                    this->type.push_back(direction==1?2:1);
                    this->time.push_back(time);
                    continue;
                }
                if(k==1){
                    address.push_back(i);
                    this->type.push_back(direction==1?2:1);
                    this->time.push_back(time);
                    continue;
                }
                if(k==0) continue;
            }
        }
        
        size_t totalRecord() { return totalRecords;}
        vector<double> fetchTime() { return time;}
        vector<int> fetchAddress() { return address;}
        vector<int> fetchType() { return type;}
        
        void printType(){
            for ( auto& x : type){
                std::cout << x << std::endl;
            }
        }
        
    };

    
    
}



#endif /* MarketOrder_h */
