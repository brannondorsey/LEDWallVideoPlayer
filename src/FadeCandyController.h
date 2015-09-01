//
//  FadeCandyController.h
// 
//  Created by Brannon Dorsey
//
//

#pragma once
#include "ofMain.h"
#include "OPC.h"

class FadeCandyController{
public:
    
    ~FadeCandyController();
    void setup(std::string host1,
               std::string host2,
               std::string host3,
               std::string host4);
    
    void update(ofPixels& pixels);
    
    void turnOff();
    
    bool allClientsConnected() const;
    bool connect();
    
    OPCClient* clientOne;
    OPCClient* clientTwo;
    OPCClient* clientThree;
    OPCClient* clientFour;
    vector<uint8_t> packetOne;
    vector<uint8_t> packetTwo;
    vector<uint8_t> packetThree;
    vector<uint8_t> packetFour;
};
