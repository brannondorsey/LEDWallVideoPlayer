/*
 *
 * Copyright (c) 2014, James Hurlbut
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in
 * the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of James Hurlbut nor the names of its
 * contributors may be used to endorse or promote products
 * derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "ofMain.h"
#include "OPC.h"


OPCClient::OPCClient(const string &host, const int port):
host(host),
port(port),
address(Poco::Net::SocketAddress(host, port)),
bSocketConnected(false)
{
  
}
OPCClient::~OPCClient( )
{
      dispose();
}
void OPCClient::update(){

}
void OPCClient::dispose()
{
    if(bSocketConnected)
    {
        ofLog(OF_LOG_NOTICE, "ofxFadecandy: Disposing Socket Connection");
        try {
            socket.shutdown();
        } catch(Poco::Exception e) {
            ofLog(OF_LOG_ERROR, "ofxFadecandy: Poco net exception: ") << e.message();
        }
        socket.close();
        bSocketConnected = false;
    }
}

bool OPCClient::connect(){
    if(!bSocketConnected)
    {
        try
        {
            socket = Poco::Net::StreamSocket(address);
            socket.setNoDelay(true);
            socket.setKeepAlive(true);
            socket.setBlocking(true);
            bSocketConnected = true;
            ofLog(OF_LOG_NOTICE, "ofxFadecandy: Socket Connection Established");
        }
        catch(Poco::Exception e)
        {
            bSocketConnected = false;
            ofLog(OF_LOG_ERROR, "ofxFadecandy: Socket Connection NOT Established");
        }
    }
    return bSocketConnected;

}
void OPCClient::setPixelCount(vector<uint8_t> & packetData, int numPixels)
{
    int numBytes = 3 * numPixels;
    int packetLen = 4 + numBytes;
    if (packetData.size() != packetLen)
    {
        packetData.resize(packetLen, 0);
        packetData[0] = 0;
        packetData[1] = 0;
        packetData[2] = (uint8_t)(numBytes >> 8);
        packetData[3] = (uint8_t)(numBytes & 0xFF);
    }
}


void OPCClient::write(vector<uint8_t> packetData)
{
    if(packetData.size() > 0 && connect())
    {
        try
        {
            socket.sendBytes(&packetData[0], (int) packetData.size());
        }
        catch (Poco::Exception e)
        {
            ofLog(OF_LOG_ERROR, "ofxFadecandy: Error Sending Pixels");
            cout << e.message() << endl;
            dispose();
        }
    }
}

bool OPCClient::isConnected()
{
    return ( bSocketConnected);
}
