#include "ofApp.h"

bool boolMetaMesh = true;
bool boolLines = true;
bool boolMiniMesh = true;
bool boolVertex = false;
bool boolAlternatePoints = true;
bool boolAlternateMainPoints = true;
bool boolWiggle = true;
bool boolCenterSphere = false;

bool showGui = true;

int shapeVertices = 8;
int pointMultiplier = 200; //200
int radiusMultiplier = 16;
int maxRadius = radiusMultiplier * 120;
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
    ofSetWindowShape(1280, 800);
//    ofSetWindowShape(1920, 1080);
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
    
    // Setup blur
//    blur.setup(ofGetWindowWidth(), ofGetWindowHeight(), blurRadiusSlider, blurShapeSlider, blurPassesSlider, blurDownsampleSlider);
    blur.setup(ofGetWindowWidth(), ofGetWindowHeight(), 25, .2, 1, .1);
    
    
    // Setup GUI
    
    int guiWidth = 300;
    
    gui.setDefaultWidth(guiWidth);
    gui.setup();
    gui.setPosition(20, 20);
    
    // Misc group
    miscGroup.setup("Controls");
    miscGroup.add(metaMeshToggle.setup("meta mesh (fill)", boolMetaMesh));
    miscGroup.add(linesToggle.setup("lines", boolLines));
    miscGroup.add(miniMeshToggle.setup("mini meshes (fill)", boolMiniMesh));
    miscGroup.add(vertexToggle.setup("vertex spheres", boolVertex));
    miscGroup.add(alternatePointsToggle.setup("alternate points", boolAlternatePoints));
    miscGroup.add(alternateMainPointsToggle.setup("alternate main points (color)", boolAlternateMainPoints));
    miscGroup.add(wiggleToggle.setup("vibration", boolWiggle));
    miscGroup.add(centerSphereToggle.setup("center sphere", boolCenterSphere));
    
    miscGroup.add(depthTestToggle.setup("depth test", true));
    miscGroup.add(blurToggle.setup("blur", false));
    
    gui.add(&miscGroup);
    miscGroup.setWidthElements(guiWidth);
    
    // Load previous settings
    gui.loadFromFile("settings.xml");


}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Update settings from GUI
    boolMetaMesh = metaMeshToggle;
    boolLines = linesToggle;
    boolMiniMesh = miniMeshToggle;
    boolVertex = vertexToggle;
    boolAlternatePoints = alternatePointsToggle;
    boolAlternateMainPoints = alternateMainPointsToggle;
    boolWiggle = wiggleToggle;
    boolCenterSphere = centerSphereToggle;
    
    for (int i = 0; i < nSpheres.size(); i++) {
        nSpheres[i].update();
    }
    
}

//--------------------------------------------------------------
void ofApp::drawHelper(){
    
    easyCam.begin();
    
    if (depthTestToggle == true) {
        ofEnableDepthTest();
    }

    
    // Center sphere
    if (boolCenterSphere == true) {
        ofSetColor(0, 0, 0, 255);
        ofMesh sphere = ofMesh::sphere(20, 16, OF_PRIMITIVE_TRIANGLE_STRIP);
//        ofSetColor(255, 255, 255, 255);
        
        sphere.draw();
    }
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);

    
    for (int i = 0; i < nSpheres.size(); i++) {
        
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
        
        //        cam.begin();
        
        
        ofPushMatrix();
        
        ofTranslate(nSpheres[i].position.x, nSpheres[i].position.y, nSpheres[i].position.z);
        
        // Rotation
//        ofRotateX(ofGetFrameNum() * nSpheres[i].velocity.x * velocityMultiplier);
//        ofRotateY(ofGetFrameNum() * nSpheres[i].velocity.y * velocityMultiplier);
//        ofRotateZ(ofGetFrameNum() * nSpheres[i].velocity.z * velocityMultiplier);
        
        
        nSpheres[i].draw();
        
        
        ofPopMatrix();

        
        //        cam.end();
    }
    
    if (depthTestToggle == true) {
        ofDisableDepthTest();
    }
    
    easyCam.end();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
//    glPointSize(2);
    ofSetColor(255, 255, 255);

    
    
    // If blur is on, start the blur
    if (blurToggle == true) {
        blur.begin();
        ofBackground(0, 0, 0);
//        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    }

    drawHelper();
    
    if (blurToggle == true) {
        blur.end();
        blur.draw();
    }
    
    // If blur is on, draw it a second time
    if (blurToggle == true) {
        drawHelper();
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
    
    // Show the GUI if we want it
    if (showGui) {
        gui.draw();
    }
}

void ofApp::exit() {
    gui.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_RETURN) {
        showGui = !showGui;
    }
    
//    if (key == '1') {
//        one = !one;
//    }
    
//    if (key == '2') {
//        two = !two;
//    }
    
//    if (key == '3') {
//        three = !three;
//    }
    
//    if (key == '4') {
//        four = !four;
//    }
    
//    if (key == '5') {
//        five = !five;
//    }
    
//    if (key == '6') {
//        six = !six;
//    }
    
//    if (key == '7') {
//        seven = !seven;
//    }
    
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
