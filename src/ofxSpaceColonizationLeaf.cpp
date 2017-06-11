#include "ofxSpaceColonizationLeaf.h"

ofxSpaceColonizationLeaf::ofxSpaceColonizationLeaf(glm::vec3 _pos){
    pos = _pos;
}

void ofxSpaceColonizationLeaf::draw2d(){
    ofDrawCircle(pos.x, pos.y, ray);
}

glm::vec3 ofxSpaceColonizationLeaf::getPosition() const {
    return this->pos;
}

void ofxSpaceColonizationLeaf::setRay(int _ray){
    ray = _ray;
}

void ofxSpaceColonizationLeaf::setReached(bool _val){
    reached = _val;
}

