//
//  nSphere.h
//  nSpheres
//
//  Created by Colin Brooks on 1/5/16.
//
//

#ifndef nSphere_h
#define nSphere_h

#include "ofMain.h"
#include "nSpherePoint.h"

class nSphere {
    
    public:
    
        // Constructors
        nSphere(ofVec3f position, float radius, float noiseFactor, int maxPoints);
    
        // Methods
    
        void addPoint();
        void addAltPoint();
        void update();
        void draw();
    
        // Variables
        ofVec3f position;
        ofVec3f velocity;
        float radius;
        int maxPoints;
        vector<nSpherePoint> points;
        vector<nSpherePoint> altMainPoints;
    
        ofVec3f noise;
        float noiseFactor;
        float thetaPhiFactor;
    
        float currentTheta;
        float currentPhi;
    
        float lastTheta;
        float lastPhi;
    
        vector<nSpherePoint> altPoints;
        float currentAltTheta;
        float currentAltPhi;
        float lastAltTheta;
        float lastAltPhi;
    
        float alpha;
    int test;
};


#endif /* nSphere_h */
