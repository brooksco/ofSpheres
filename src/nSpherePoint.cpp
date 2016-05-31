//
//  nSpherePoint.cpp
//  ofSpheres
//
//  Created by Colin Brooks on 1/5/16.
//
//

#include "ofApp.h"
#include "nSpherePoint.h"

nSpherePoint::nSpherePoint(ofVec3f position, float radius, float theta, float phi, ofVec3f noise) {
    
    this->position = position;
    this->radius = radius;

    this->theta = theta;
    this->phi = phi;
    
    this->noise = noise;
    
}

void nSpherePoint::update() {

    position.x = radius * cos(theta) * sin(phi) + noise.x;
    position.y = radius * sin(theta) * sin(phi) + noise.y;
    position.z = radius * cos(phi) + noise.z;
    
    if (boolWiggle) {
        position.x = position.x + ofMap(ofRandom(10), 0, 10, -.5, .5);
        position.y = position.y + ofMap(ofRandom(10), 0, 10, -.5, .5);
        position.z = position.z + ofMap(ofRandom(10), 0, 10, -.5, .5);
    }

    
    theta += ofMap(radius, 0, maxRadius, .001, .0001);
    phi += ofMap(radius, 0, maxRadius, .001, .0001);
    
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

