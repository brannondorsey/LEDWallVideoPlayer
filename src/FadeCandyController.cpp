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
    delete clientThree;
    delete clientFour;
}

void FadeCandyController::setup(std::string host1,
                                std::string host2,
                                std::string host3,
                                std::string host4) {
    
    clientOne   = new OPCClient(host1, 7890);
    clientTwo   = new OPCClient(host2, 7890);
    clientThree = new OPCClient(host3, 7890);
    clientFour  = new OPCClient(host4, 7890);
}

bool FadeCandyController::connect() {
    
    if (!clientOne->isConnected())   clientOne->connect();
    if (!clientTwo->isConnected())   clientTwo->connect();
    if (!clientThree->isConnected()) clientThree->connect();
    if (!clientFour->isConnected())  clientFour->connect();
    return allClientsConnected();
}

void FadeCandyController::update(ofPixelsRef pixels){
    
    clientOne->setPixelCount(packetOne, 34564 / 3);
    clientTwo->setPixelCount(packetTwo, 34564 / 3);
    clientThree->setPixelCount(packetThree, 34564 / 3);
    clientFour->setPixelCount(packetFour, 34564 / 3); // 320 * 20
    
    int xStep = pixels.getWidth()/47; //23;
    int yStep = pixels.getHeight()/23;
    
    int indexOne = 4;
    int indexTwo = 4;
    int indexThree = 4;
    int indexFour = 4;
    
    for (int y = 0; y < pixels.getHeight(); y += yStep) {
        
        for (int x = 0; x < pixels.getWidth() * 0.5; x += xStep) {
            
            ofColor color = pixels.getColor(x, y);
            
            if (x >= pixels.getWidth() * 0.25) {
                
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
        
        for (int x = pixels.getWidth() * 0.5; x < pixels.getWidth(); x += xStep) {
            
            ofColor color = pixels.getColor(x, y);
            
            if (x >= pixels.getWidth() * 0.75) {
                
                for (int i = 0; i < 40; i++) {
                    packetThree[indexThree]     = ofClamp(color.r - 40, 0, 255);
                    packetThree[indexThree + 1] = ofClamp(color.g - 40, 0, 255);
                    packetThree[indexThree + 2] = ofClamp(color.b - 40, 0, 255);
                    indexThree += 3;
                }
                
            } else {
                
                for (int i = 0; i < 40; i++) {
                    packetFour[indexFour]     = ofClamp(color.r - 40, 0, 255);
                    packetFour[indexFour + 1] = ofClamp(color.g - 40, 0, 255);
                    packetFour[indexFour + 2] = ofClamp(color.b - 40, 0, 255);
                    indexFour += 3;
                }
            }
        }
    }
    
    
    clientOne->write(packetOne);
    clientTwo->write(packetTwo);
    clientThree->write(packetThree);
    clientFour->write(packetFour);
    
    packetOne.clear();
    packetTwo.clear();
    packetThree.clear();
    packetFour.clear();
    
}

bool FadeCandyController::allClientsConnected() const {
    return clientOne->isConnected() &&
           clientTwo->isConnected();
           clientThree->isConnected() &&
           clientFour->isConnected();
}
