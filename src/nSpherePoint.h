//
//  nSpherePoint.h
//  ofSpheres
//
//  Created by Colin Brooks on 1/5/16.
//
//

#ifndef nSpherePoint_h
#define nSpherePoint_h

#include "ofMain.h"

class nSpherePoint {
    
public:
    // Constructors
//    nSpherePoint(float radius, float theta, float phi, float lastTheta, float lastPhi, ofVec3f noise, float noiseFactor, float thetaPhiFactor);
    nSpherePoint(ofVec3f position, float radius, float theta, float phi, ofVec3f noise);
    
    // Methods
    void update();
    void draw();
    
    // Variables
    float radius;
    float theta;
    float phi;
    
//    float lastTheta;
//    float lastPhi;
//    float noiseFactor;
//    float thetaPhiFactor;

    ofVec3f noise;
    ofVec3f position;
    
    int weight;
    int alpha;
    
};

#endif /* nSpherePoint_h */
