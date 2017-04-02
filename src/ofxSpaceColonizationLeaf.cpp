#include "ofxSpaceColonizationLeaf.h"

ofxSpaceColonizationLeaf::ofxSpaceColonizationLeaf(){
    pos = ofVec3f(ofRandom(0,ofGetWidth()),
                  ofRandom(0, ofGetHeight()-100),
                  0);
    //pos = ofVec3f(ofGetWidth()/2, 0,0);
}

void ofxSpaceColonizationLeaf::draw(){
    ofDrawCircle(pos.x, pos.y, raggio);
}

ofVec3f ofxSpaceColonizationLeaf::getPosition(){
    return pos;
}

