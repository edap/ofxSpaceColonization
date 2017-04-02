#include "ofxSpaceColonizationLeaf.h"

ofxSpaceColonizationLeaf::ofxSpaceColonizationLeaf(){
    int ray = 400;
    pos = ofVec3f(ofRandom(-ray,+ray),
                  ofRandom(100, ray),
                  ofRandom(-ray,+ray));
    //pos = ofVec3f(ofGetWidth()/2, 0,0);
}

void ofxSpaceColonizationLeaf::draw(){
    //ofDrawCircle(pos.x, pos.y, raggio);
    ofDrawSphere(pos.x, pos.y, pos.z, raggio);
}

ofVec3f ofxSpaceColonizationLeaf::getPosition(){
    return pos;
}

