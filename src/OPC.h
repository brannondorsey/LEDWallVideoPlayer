//
//  OPC.h
//  fadeCandy
//
//  Created by dantheman on 8/15/15.
//
//

/*
 * Cinder Friendly Client for Open Pixel Control
 *
 * James Hurlbut @ Stimulant 2014
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"

class OPCClient {
public:

    OPCClient(const string &host, const int port);
    ~OPCClient();
    
    bool connect();
    void dispose();
    
    bool isConnected();
    void update();
    
    void setPixelCount(vector<uint8_t> & packetData, int numPixel);
    int getPixelCount();
    
    void write(vector<uint8_t> packetData);
    
    string host;
    int port;
    Poco::Net::SocketAddress address;
    Poco::Net::StreamSocket socket;
    bool bSocketConnected;

    vector<int> pixelLocations;

    uint8_t firmwareConfig;
    string colorCorrection;

    
};