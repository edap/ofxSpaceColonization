#include "ofxSpaceColonizationLeaf.h"

ofxSpaceColonizationLeaf::ofxSpaceColonizationLeaf(glm::vec3 _pos){
    pos = _pos;
}

glm::vec3 ofxSpaceColonizationLeaf::getPosition() const {
    return this->pos;
}

void ofxSpaceColonizationLeaf::setReached(bool _val){
    reached = _val;
}

