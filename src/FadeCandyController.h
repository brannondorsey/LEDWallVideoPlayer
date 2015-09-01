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
    void setup(int videoWidth, int videoHeight);
    void update(ofPixels& pixels);
    
//    bool allClientsConnected() const;
//    bool connect();
    
    OPCClient* clientOne;
    OPCClient* clientTwo;
    OPCClient* clientThree;
    OPCClient* clientFour;
    vector<uint8_t> packetOne;
    vector<uint8_t> packetTwo;
    vector<uint8_t> packetThree;
    vector<uint8_t> packetFour;
};
