//
//  nSpherePoint.cpp
//  ofSpheres
//
//  Created by Colin Brooks on 1/5/16.
//
//

#include "ofApp.h"
#include "nSpherePoint.h"

nSpherePoint::nSpherePoint(float radius, float theta, float phi, float lastTheta, float lastPhi, ofVec3f noise, float noiseFactor, float thetaPhiFactor) {
    
    this->radius = radius;
    this->theta = theta;
    this->phi = phi;
    this->lastTheta = lastTheta;
    this->lastPhi = lastPhi;
    this->noise = noise;
    this->noiseFactor = noiseFactor;
    this->thetaPhiFactor = thetaPhiFactor;
    
    position.x = cos(theta) * sin(phi) * radius + ofSignedNoise(noise.x) * (noiseFactor * noiseMultiplier);
    position.y = sin(theta) * sin(phi) * radius + ofSignedNoise(noise.y) * (noiseFactor * noiseMultiplier);
    position.z = cos(phi) * radius + ofSignedNoise(noise.z) * (noiseFactor * noiseMultiplier);
    
//    position.x = cos(theta) * sin(phi) * radius;
//    position.y = sin(theta) * sin(phi) * radius;
//    position.z = cos(phi) * radius;
    
    float distance = abs(lastTheta - theta) + abs(lastPhi - phi);

    weight = int(ofMap(distance, thetaPhiFactor / 2, thetaPhiFactor * 2, 3, 1));
    alpha = int(ofMap(distance, 0, thetaPhiFactor * 2, 255, 0));
}

void nSpherePoint::update() {
//    if (seven) {
//        position.x = position.x + ofMap(ofSignedNoise(noise.x), -1, 1, -1, 1);
//        position.y = position.y + ofMap(ofSignedNoise(noise.y), -1, 1, -1, 1);
//        position.z = position.z + ofMap(ofSignedNoise(noise.z), -1, 1, -1, 1);
//    }
    if (seven) {
        position.x = position.x + ofMap(ofRandom(10), 0, 10, -.5, .5);
        position.y = position.y + ofMap(ofRandom(10), 0, 10, -.5, .5);
        position.z = position.z + ofMap(ofRandom(10), 0, 10, -.5, .5);
    }
    
}

void nSpherePoint::draw() {
//    ofPushMatrix();
//    ofTranslate(position.x, position.y, position.y);
//    
////    if (two == true) {
////        strokeWeight(weight);
////        
////    } else {
////        strokeWeight(1);
////    }
//    
//    // Again if radius is greater than some arbitrary number make it dimmer
//    if (radius > 400) {
//        ofSetColor(255 - sqrt(alpha * 30), 255 - sqrt(alpha * 5), 255, alpha * .75);
//    } else {
//        ofSetColor(255 - sqrt(alpha * 30), 255 - sqrt(alpha * 5), 255, alpha);
//    }
//    
//    point(0, 0, 0);
//    
//    // Glow
//    if (three == true) {
//        
//        for (int i = 2; i < 6; i++) {
//            strokeWeight((weight * weight) * i / 5);
//            // i * 4; i * i
//            stroke(255 - sqrt(alph * 30), 255 - sqrt(alph * 5), 255, i * 4);
//            point(0,0,0);
//        }
//        
//        //strokeWeight(weight * 4);
//        //stroke(255, 255, 255, 10);
//        //point(0,0,0);
//        
//    }
//    
//    popMatrix();

}

