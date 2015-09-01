#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(24);
    ofBackground(ofColor::black);
    
    player.loadMovie("h264-color.mov");
    player.setLoopState(OF_LOOP_NORMAL);
	player.play();
    
    float aspect = player.getWidth() / player.getHeight();
    ofSetWindowShape(ofGetScreenWidth() / 2, (ofGetScreenWidth() / 2) / aspect);
    
    leds.setup(player.getWidth(), player.getHeight());
    
    debug = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    player.update();
    leds.update(player.getPixelsRef());
}

//--------------------------------------------------------------
void ofApp::draw(){
    
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
