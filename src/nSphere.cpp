//
//  nSphere.cpp
//  nSpheres
//
//  Created by Colin Brooks on 1/5/16.
//
//

#include "ofApp.h"
#include "nSphere.h"
#include "nSpherePoint.h"

nSphere::nSphere(ofVec3f position, float radius, float noiseFactor, int maxPoints) {
    
    this->position = position;
    this->radius = radius;
    this->noiseFactor = noiseFactor;
    this->maxPoints = maxPoints;
    
    thetaPhiFactor = .1;
    currentTheta = 0;
    currentPhi = 0;
    lastTheta = currentTheta;
    lastPhi = currentPhi;
    
    currentAltTheta = .77;
    currentAltPhi = .77;
    lastAltTheta = currentAltTheta;
    lastAltPhi = currentAltPhi;
    
    velocity.x = ofMap(ofRandom(10), 0, 10, -(1 / radius), (1 / radius));
    velocity.y = ofMap(ofRandom(10), 0, 10, -(1 / radius), (1 / radius));
    velocity.z = ofMap(ofRandom(10), 0, 10, -(1 / radius), (1 / radius));
    
    // Gotta be a better way to steepen the graph/speed at the center here
    if (radius < (30 * radiusMultiplier)) {
        velocity = velocity * 1.5;
    }
    
}

void nSphere::addPoint() {
    nSpherePoint p = nSpherePoint(radius, currentTheta, currentPhi, lastTheta, lastPhi, noise, noiseFactor, thetaPhiFactor);
    
    lastTheta = currentTheta;
    lastPhi = currentPhi;
    
    currentTheta += ofRandom(-thetaPhiFactor, thetaPhiFactor * 1.2);
    currentPhi += ofRandom(-thetaPhiFactor, thetaPhiFactor * 1.2);
    
    //    currentTheta += ofRandom(-thetaPhiFactor, thetaPhiFactor * (noiseFactor * .2));
    //    currentPhi += ofRandom(-thetaPhiFactor, thetaPhiFactor * (noiseFactor * .2));
    
    noise.x += ofRandom(-thetaPhiFactor, thetaPhiFactor);
    noise.y += ofRandom(-thetaPhiFactor, thetaPhiFactor);
    noise.z += ofRandom(-thetaPhiFactor, thetaPhiFactor);
    
    points.push_back(p);
    
    if (boolAlternateMainPoints == true) {
        altMainPoints.push_back(p);
    }
    
}

void nSphere::addAltPoint() {
    nSpherePoint p = nSpherePoint(radius, currentAltTheta, currentAltPhi, lastAltTheta, lastAltPhi, noise, noiseFactor, thetaPhiFactor);
    
    lastAltTheta = currentAltTheta;
    lastAltPhi = currentAltPhi;
    
    currentAltTheta += ofRandom(-thetaPhiFactor, thetaPhiFactor * 1.2);
    currentAltPhi += ofRandom(-thetaPhiFactor, thetaPhiFactor * 1.2);
    
    //    noise.x += ofRandom(-thetaPhiFactor, thetaPhiFactor);
    //    noise.y += ofRandom(-thetaPhiFactor, thetaPhiFactor);
    //    noise.z += ofRandom(-thetaPhiFactor, thetaPhiFactor);
    
    altPoints.push_back(p);
}

void nSphere::update() {
    // Add and remove points for next frame
    
    // Don't do this every frame and vary by radius
    int adjusted = floor(4 + (radius / (10 * radiusMultiplier)));
    if (ofGetFrameNum() % adjusted == 0) {
        
        // If we're doing shapes we need to add and remove in groups
        if (boolMiniMesh == true) {
            
            for (int i = 0; i < shapeVertices; i++) {
                addPoint();
            }
            
            if (points.size() >= maxPoints * pointMultiplier) {
                for (int i = 0; i < shapeVertices; i++) {
                    points.erase(points.begin());
                }
            }
            
        } else {
            addPoint();
            
            if (points.size() >= maxPoints * pointMultiplier) {
                points.erase(points.begin());
            }
        }
        
        if (boolAlternatePoints == true) {
            addAltPoint();
            
            if (altPoints.size() >= maxPoints * pointMultiplier * 2) {
                altPoints.erase(altPoints.begin());
            }
        }
        
        // Check for when alt points get removed
        if (boolAlternateMainPoints == true) {
            if (altMainPoints.size() >= maxPoints * pointMultiplier * 1.5) {
                // If we're doing shapes we need to remove in groups
                if (boolMiniMesh == true) {
                    
                    for (int i = 0; i < shapeVertices; i++) {
                        altMainPoints.erase(altMainPoints.begin());
                    }
                    
                } else {
                    altMainPoints.erase(altMainPoints.begin());
                }
                
            }
        }
        
    }
    
    // Update all the points individually
    if (points.size() > 0) {
        
        for (int i = 0; i < (points.size() - 1); i++) {
            nSpherePoint *p = &points[i];
            p->update();
        }
    }
    
    //    for (int i = 0; i < (altPoints.size() - 1); i++) {
    //        nSpherePoint *p = &altPoints[i];
    //        p->update();
    //    }
    
    if (altMainPoints.size() > 0) {
        
        for (int i = 0; i < (altMainPoints.size() - 1); i++) {
            nSpherePoint *p = &altMainPoints[i];
            p->update();
        }
    }
    
    
}

void nSphere::draw() {
    
    if (points.size() > 0) {
        
        ofMesh metaMesh;
        metaMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        metaMesh.enableIndices();
        
        for (int i = 0; i < (points.size() - 1); i++) {
            // Pointers, this hopefully works now
            nSpherePoint *p = &points[i];
            //            p->update();
            
            // Draw spheres at vertices, really inefficient
            if (boolVertex) {
                ofSpherePrimitive sphere = ofSpherePrimitive(2, 4);
                sphere.setPosition(p->position.x, p->position.y, p->position.z);
                ofSetColor(255, 125, 125, 50);
                sphere.draw();
            }
            
            // Meta mesh, previously points as points
            if (boolMetaMesh == true) {
                metaMesh.addVertex(ofVec3f(p->position.x, p->position.y, p->position.z));
                
                metaMesh.addIndex(i);
                
                // Make the shape more interesting by systematically adding new indices
                int count = floor(i / 4);
                if (count > 1) {
                    // Don't want to go back too far, so limit it
                    if (count > 2) {
                        count = 2;
                    }
                    // Add the indices for 7 earlier, up to 4 times or whatever is smaller
                    for (int j = 1; j < count; j++) {
                        metaMesh.addIndex(i - (4 * j));
                    }
                }
                
            }
            
            // Lines connecting two points
            if (boolLines == true) {
                nSpherePoint *q = &points[i + 1];
                
                float distance = ofDist(p->position.x, p->position.y, p->position.z, q->position.x, q->position.y, q->position.z);
                alpha = ofMap(distance, 0, radius / 8, 160, 60);
                
                if (distance > (radius / 12)) {
                    alpha = alpha * .75;
                }
                
                ofSetColor(255 - sqrt(alpha * 30), 255 - sqrt(alpha * 5), 255, alpha);
                
                ofDrawLine(p->position.x, p->position.y, p->position.z, q->position.x, q->position.y, q->position.z);
            }
            
            // Mesh between [shapeVertices] points (something like 8)
            if (boolMiniMesh == true) {
                
                if (i + (shapeVertices - 1) < points.size() && (i % shapeVertices == 0)) {
                    nSpherePoint *q = &points[i + 1];
                    
                    // This needs to be reworked to take into account both distance AND radius
                    // Distance between points
                    float distance = ofDist(p->position.x, p->position.y, p->position.z, q->position.x, q->position.y, q->position.z);
                    // Use that distance relative to radius to set initial alpha
                    alpha = ofMap(distance, 0, radius / 8, 160, 60); //120
                    
//                    if (radius < (radiusMultiplier * radiusMultiplier)) {
//                        alpha = 255;
//                    }
                    
                    
                    
                    // Create a multiplier based on the radius and an arbitrary max radius
                    // Lowering the max will make the outermost shapes darker
                    float multiplier = ofMap(radius, 0, maxRadius, 1, 0);
                    
                    // Change the alpha value with the multiplier
                    alpha = alpha * multiplier;
                    
                    // If distance is greater than an arbitrary portion of the radius, make the alpha even lower
                    if (distance > (radius / 12)) {
                        alpha = alpha * .75;
                    }

                    
                    ofFill();
                    ofSetColor(255, 255, 255, alpha);
                    
                    // hmm meshes
                    ofMesh miniMesh;
                    miniMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
                    
                    for (int j = 0; j < shapeVertices; j++) {
                        nSpherePoint *currentPoint = &points[i + j];
                        miniMesh.addVertex(ofVec3f(currentPoint->position.x, currentPoint->position.y, currentPoint->position.z));
                    }
                    miniMesh.draw();
                    
                    ofNoFill();
                }
            }
            
            p->draw();
        }
        
        ofFill();
        int metaAlpha = ofMap(radius, 0, maxRadius, 40, 5); //120

        ofSetColor(255, 255, 255, metaAlpha);
        metaMesh.draw();
        
        
        
        // Alternate points
        if (boolAlternatePoints) {
            
            glPointSize(2);
            
            if (altPoints.size() > 0) {
                
                ofMesh metaAltMesh;
                metaAltMesh.setMode(OF_PRIMITIVE_POINTS);
                metaAltMesh.enableIndices();
                
                for (int i = 0; i < (altPoints.size() - 1); i++) {
                    nSpherePoint *q = &altPoints[i];
                    // This is really interesting
                    //                    nSpherePoint *q = &points[i];
                    
                    metaAltMesh.addVertex(ofVec3f(q->position.x, q->position.y, q->position.z));
                    
                    metaAltMesh.addIndex(i);
                    
                    // Make the shape more interesting by systematically adding new indices
                    //            int count = floor(i / 4);
                    //            if (count > 1) {
                    //                // Don't want to go back too far, so limit it
                    //                if (count > 2) {
                    //                    count = 2;
                    //                }
                    //                // Add the indices for 7 earlier, up to 4 times or whatever is smaller
                    //                for (int j = 1; j < count; j++) {
                    //                    metaMesh.addIndex(i - (4 * j));
                    //                }
                    //            }
                }
                
                ofFill();
                ofSetColor(255, 255, 255, 127);
                metaAltMesh.draw();
                
            }
        }
        
        // Alternate lines
        if (boolAlternateMainPoints) {
            
            glPointSize(1);
            
            if (altMainPoints.size() > 0) {
                
                ofMesh metaAltMainMesh;
                metaAltMainMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
                metaAltMainMesh.enableIndices();
                
                for (int i = 0; i < (altMainPoints.size() - 1); i++) {
                    nSpherePoint *q = &altMainPoints[i];
                    
                    metaAltMainMesh.addVertex(ofVec3f(q->position.x, q->position.y, q->position.z));
                    
                    metaAltMainMesh.addIndex(i);
                }
                
                ofFill();
                // Red ish
//                ofSetColor(255, 0, 150, 50);
                // Teal ish
                ofSetColor(60, 100, 255, 80);
//                ofSetColor(255, 255, 255, 80);
                metaAltMainMesh.draw();
                
            }
        }
        
        
    }
    
}

