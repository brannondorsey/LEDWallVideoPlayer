#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(24);
    ofBackground(ofColor::black);
    
    settings.loadFile("settings.xml");
    settings.pushTag("settings");
    
    std::string video = settings.getValue("video", "");
    
    if (video == "") {
        video = "weekdays/" + ofToString(ofClamp(ofGetWeekday(), 1, 5))
            + "_" + settings.getValue("side", "left") + ".mov";
    }
    
    player.loadMovie(video);
    player.setLoopState(OF_LOOP_NORMAL);
	player.play();
    
    float aspect = player.getWidth() / player.getHeight();
    ofSetWindowShape(ofGetScreenWidth() / 2, (ofGetScreenWidth() / 2) / aspect);
    
    std::string leftHost  = settings.getValue("lefthost", "192.168.2.100");
    std::string rightHost = settings.getValue("righthost", "192.168.2.101");
    
    leds.setup(leftHost, rightHost);
    leds.connect();
    
    debug = settings.getValue("debug", 0);
    
    if (debug) {
        ofSetLogLevel(OF_LOG_VERBOSE);
    }

}

//--------------------------------------------------------------
void ofApp::update(){
   
    player.update();
    if (leds.allClientsConnected()) {
        leds.update(player.getPixelsRef());
    } else {
        ofLogError("ofApp::update") << "Clients not connected. Exiting.";
        ofExit();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofLogNotice("draw") << "drawing...";
    if (debug) {
        ofSetColor(255, 255, 255);
        player.draw(0, 0, ofGetWidth(), ofGetHeight());
    }

    ofDrawBitmapStringHighlight(ofToString( (int) ofGetFrameRate()) + " FPS", 5, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == ' ') {
        debug = !debug;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
