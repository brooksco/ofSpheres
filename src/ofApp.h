#pragma once

#include "ofMain.h"
#include "nSphere.h"
#include "ofxBlur.h"
#include "ofxGUI.h"
#include "ofxXmlSettings.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        void drawHelper();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofEasyCam easyCam;
        ofCamera cam;
        vector<nSphere> nSpheres;
    
        // Blur
        ofxBlur blur;
    
        // GUI
        ofxPanel gui;
    
        // GUI groups
        ofxGuiGroup miscGroup;
    
        // GUI toggles
        ofxToggle metaMeshToggle;
        ofxToggle linesToggle;
        ofxToggle miniMeshToggle;
        ofxToggle vertexToggle;
        ofxToggle blurToggle;
        ofxToggle alternatePointsToggle;
        ofxToggle alternateMainPointsToggle;
        ofxToggle wiggleToggle;
        ofxToggle centerSphereToggle;
    
//        // GUI buttons;
//        ofxButton blurRefreshButton;
    
        // XML settings
        ofxXmlSettings settings;

};

// Global variables

extern bool boolMetaMesh;
extern bool boolLines;
extern bool boolMiniMesh;
extern bool boolVertex;
extern bool boolAlternatePoints;
extern bool boolAlternateMainPoints;
extern bool boolWiggle;
extern bool boolCenterSphere;

extern int shapeVertices;
extern int pointMultiplier;
extern int radiusMultiplier;
extern int noiseMultiplier;