#include "ofxSpaceColonizationLeaf.h"

ofxSpaceColonizationLeaf::ofxSpaceColonizationLeaf(ofVec3f _pos){
    pos = _pos;
}

void ofxSpaceColonizationLeaf::draw(){
    //ofDrawCircle(pos.x, pos.y, raggio);
    ofDrawSphere(pos.x, pos.y, pos.z, raggio);
}

ofVec3f ofxSpaceColonizationLeaf::getPosition(){
    return pos;
}

