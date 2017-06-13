#include "ofxSpaceColonizationBranch.h"


ofxSpaceColonizationBranch::ofxSpaceColonizationBranch(const glm::vec3 _direction){
    this->direction = _direction;
    this->originalDirection = _direction;
}

void ofxSpaceColonizationBranch::move(glm::vec3 dest){
    this->position = dest;
}

glm::vec3 ofxSpaceColonizationBranch::getPosition() const {
    return this->position;
}

glm::vec3 ofxSpaceColonizationBranch::getDirection() const {
    return this->direction;
};

int ofxSpaceColonizationBranch::getCount() const {
    return this->count;
};

void ofxSpaceColonizationBranch::addToDirection(glm::vec3 _newDir){
    this->direction = this->direction + _newDir;
};

void ofxSpaceColonizationBranch::incrementCounterBy(int _val){
    this->count = this->count + _val;
};

int ofxSpaceColonizationBranch::getIndexParent() const{
    return this->indexParent;
}

void ofxSpaceColonizationBranch::setParentByIndex(int parent_index) {
    this->indexParent = parent_index;
};

void ofxSpaceColonizationBranch::reset(){
    this->direction = this->originalDirection;
    this->count = 0;
}


