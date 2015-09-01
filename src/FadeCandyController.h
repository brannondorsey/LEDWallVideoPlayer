//
//  FadeCandyController.h
//  dolbySketch
//
//  Created by dantheman on 6/5/15.
//
//

#pragma once
#include "ofMain.h"
#include "OPC.h"
#include "ofxFastFboReader.h"

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
