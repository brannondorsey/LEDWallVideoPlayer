//
//  FadeCandyController.cpp
//
//  Created by Brannon Dorsey
//
//

#include "FadeCandyController.h"

FadeCandyController::~FadeCandyController() {
    
    delete clientOne;
    delete clientTwo;
//    delete clientThree;
//    delete clientFour;
}

void FadeCandyController::setup(std::string host1, std::string host2){
    
    clientOne   = new OPCClient(host1, 7890);
    clientTwo   = new OPCClient(host2, 7890);
//    clientThree = new OPCClient("192.168.2.103", 7890);
//    clientFour  = new OPCClient("192.168.2.102", 7890);
}

bool FadeCandyController::connect() {
    
    if (!clientOne->isConnected())   clientOne->connect();
    if (!clientTwo->isConnected())   clientTwo->connect();
//    if (!clientThree->isConnected()) clientThree->connect();
//    if (!clientFour->isConnected())  clientFour->connect();
    return allClientsConnected();
}

void FadeCandyController::update(ofPixelsRef pixels){
    
    clientOne->setPixelCount(packetOne, 34564 / 3); // 34564
    clientTwo->setPixelCount(packetTwo, 34564 / 3); // 34564
//    clientThree->setPixelCount(packetThree, 34564 / 3); // 34564
//    clientFour->setPixelCount(packetFour, 34564 / 3); // 34564 // 320 * 20
    
    int xStep = pixels.getWidth()/23;
    int yStep = pixels.getHeight()/23;
    
    int indexOne = 4;
    int indexTwo = 4;
    
    for (int y = 0; y < pixels.getHeight(); y += yStep) {
        
        for (int x = 0; x < pixels.getWidth(); x += xStep) {
            
            ofColor color = pixels.getColor(x, y);
            
            if (x >= pixels.getWidth()/2) {
                
                for (int i = 0; i < 40; i++) {
                    packetTwo[indexTwo]     = ofClamp(color.r - 40, 0, 255);
                    packetTwo[indexTwo + 1] = ofClamp(color.g - 40, 0, 255);
                    packetTwo[indexTwo + 2] = ofClamp(color.b - 40, 0, 255);
                    indexTwo += 3;
                }
                
            } else {
                
                for (int i = 0; i < 40; i++) {
                    packetOne[indexOne]     = ofClamp(color.r - 40, 0, 255);
                    packetOne[indexOne + 1] = ofClamp(color.g - 40, 0, 255);
                    packetOne[indexOne + 2] = ofClamp(color.b - 40, 0, 255);
                    indexOne += 3;
                }
            }
        }
    }
    
    clientOne->write(packetOne);
    clientTwo->write(packetTwo);
    
//    clientThree->write(packetOne);
//    clientThree->update();
//    
//    clientFour->write(packetTwo);
//    clientFour->update();
    
    packetOne.clear();
    packetTwo.clear();
//    packetThree.clear();
//    packetFour.clear();
    
}

bool FadeCandyController::allClientsConnected() const {
    return clientOne->isConnected() &&
           clientTwo->isConnected();
//           clientThree->isConnected() &&
//           clientFour->isConnected();
}
