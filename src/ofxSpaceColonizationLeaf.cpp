#include "ofxSpaceColonizationLeaf.h"

ofxSpaceColonizationLeaf::ofxSpaceColonizationLeaf(ofVec3f _pos){
    pos = _pos;
}

void ofxSpaceColonizationLeaf::draw2d(){
    ofDrawCircle(pos.x, pos.y, ray);
}

ofVec3f ofxSpaceColonizationLeaf::getPosition(){
    return pos;
}

void ofxSpaceColonizationLeaf::setRay(int _ray){
    ray = _ray;
}

