#include "ofApp.h"

bool one = true;
bool two = true;
bool three = true;
bool four = false;
bool five = true;
bool six = true;
bool seven = true;

int shapeVertices = 8;
int pointMultiplier = 200; //200
int radiusMultiplier = 16;
int noiseMultiplier = 20; //20

vector<nSphere> nSpheres;
int velocityMultiplier = 20;
int centerX = 0;
int centerY = 0;
int centerZ = 0;

bool saveScreen = false;
bool saveVideoScreens = false;
int videoScreens = 7800;
int videoScreensCounter = 0;

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
//    ofSetWindowShape(1280, 800);
    ofSetWindowShape(1920, 1080);
    ofEnableSmoothing();
    
    centerX = ofGetWindowWidth() / 2;
    centerY = ofGetWindowHeight() / 2;
    
    ofVec3f centerVec = ofVec3f(centerX, centerY, 0);
    
    centerVec = ofVec3f(0, 0, 0);
    
    // Position, size, noise, points
    nSphere nSphere1 = nSphere(centerVec, radiusMultiplier * 4, 4, 5); //5
    nSphere nSphere2 = nSphere(centerVec, radiusMultiplier * 16, 6, 7);
    
    nSphere nSphere3 = nSphere(centerVec, radiusMultiplier * 30, 8, 3);
    nSphere nSphere4 = nSphere(centerVec, radiusMultiplier * 42, 10, 6);
//
    nSphere nSphere5 = nSphere(centerVec, radiusMultiplier * 70, 30, 16);
    nSphere nSphere6 = nSphere(centerVec, radiusMultiplier * 120, 12, 16);
    
    nSpheres.push_back(nSphere1);
    nSpheres.push_back(nSphere2);
    nSpheres.push_back(nSphere3);
    nSpheres.push_back(nSphere4);
    nSpheres.push_back(nSphere5);
    nSpheres.push_back(nSphere6);
    
    long eyeX = (ofGetWindowWidth() / 3) * cos(ofGetFrameNum() * 0.0008);
    long eyeZ = (ofGetWindowWidth() / 2) * sin(ofGetFrameNum() * 0.0008);
    long eyeY = 0;
    centerZ = (ofGetWindowWidth() / 3) * sin(ofGetFrameNum() * 0.00008) + 100;
    float upX = 0;
    float upY = 1;
    float upZ = 0;
    
    ofVec3f camPos;
    ofVec3f lookAtPos;
    
    camPos = ofVec3f(centerX, centerY, centerZ);
    lookAtPos = ofVec3f(eyeX, eyeY, eyeZ);
    
    ofVec3f upVector;
    upVector.set(0, 1, 0);
    
    easyCam.setPosition(camPos);
    easyCam.lookAt(lookAtPos, upVector);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofSetColor(255, 255, 255);
    
    for (int i = 0; i < nSpheres.size(); i++) {
//        nSphere currentSphere = nSpheres[i];
        
        nSpheres[i].update();
        
    
        
        
//        long eyeX = (ofGetWindowWidth() / 3) * cos(ofGetFrameNum() * 0.0008);
//        long eyeZ = (ofGetWindowWidth() / 2) * sin(ofGetFrameNum() * 0.0008);
        
//        long eyeX = 0;
//        long eyeZ = 0;
//        long eyeY = 0;
//        centerX = ofGetWindowWidth() / 2 + 1500;
//        centerY = ofGetWindowHeight() / 2;
//        centerZ = (ofGetWindowWidth() / 3) * sin(ofGetFrameNum() * 0.00008);
//        float upX = 0;
//        float upY = 1;
//        float upZ = 0;
//        
//        ofVec3f camPos;
//        ofVec3f lookAtPos;
//        
//        camPos = ofVec3f(centerX, centerY, centerZ);
//        lookAtPos = ofVec3f(eyeX, eyeY, eyeZ);
//        
//        ofVec3f upVector;
//        upVector.set(0, 1, 0);
//        
//        cam.setPosition(camPos);
//        cam.lookAt(lookAtPos, upVector);
//        
//        
//        cam.begin();
        easyCam.begin();
        
        ofPushMatrix();
        
        // Reference box
//        ofBoxPrimitive box = ofBoxPrimitive(50, 50, 50);
//        box.setPosition(0, 0, 0);
//        ofSetColor(255, 125, 125);
//        box.draw();
        // end reference box
        
//        ofPushMatrix();
        
        ofTranslate(nSpheres[i].position.x, nSpheres[i].position.y, nSpheres[i].position.z);
        
        ofRotateX(ofGetFrameNum() * nSpheres[i].velocity.x * velocityMultiplier);
        ofRotateY(ofGetFrameNum() * nSpheres[i].velocity.y * velocityMultiplier);
        ofRotateZ(ofGetFrameNum() * nSpheres[i].velocity.z * velocityMultiplier);
        
//        ofPopMatrix();
        
        nSpheres[i].draw();
        ofPopMatrix();
        easyCam.end();
        
//        cam.end();
    }
    
    // Save frame
    if (saveScreen) {
        ofSaveScreen(ofToString(ofGetFrameNum())+".png");
        saveScreen = false;
    }
    
    // Save frames for video
    if (saveVideoScreens) {
        
        if (videoScreensCounter < videoScreens) {
            ofSaveScreen(ofToString(ofGetFrameNum())+".jpg");
            videoScreensCounter += 1;
            
        } else {
            videoScreensCounter = 0;
            saveVideoScreens = false;
            
        }
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == '1') {
        one = !one;
    }
    
    if (key == '2') {
        two = !two;
    }
    
    if (key == '3') {
        three = !three;
    }
    
    if (key == '4') {
        four = !four;
    }
    
    if (key == '5') {
        five = !five;
    }
    
    if (key == '6') {
        six = !six;
    }
    
    if (key == '7') {
        seven = !seven;
    }
    
    if (key == OF_KEY_UP) {
        noiseMultiplier += 5;
        cout << noiseMultiplier << endl;
    }
    
    if (key == OF_KEY_DOWN) {
        noiseMultiplier -= 5;
        if (noiseMultiplier < 0) {
            noiseMultiplier = 0;
        }
        cout << noiseMultiplier << endl;
    }
    
    if (key == 's') {
        saveScreen = true;
    }
    
    if (key == 'v') {
        saveVideoScreens = true;
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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
