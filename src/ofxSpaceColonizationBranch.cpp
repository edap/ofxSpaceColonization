#include "ofxSpaceColonizationBranch.h"


ofxSpaceColonizationBranch::ofxSpaceColonizationBranch(const glm::vec3 _direction){
    direction = _direction;
    originalDirection = _direction;
}

void ofxSpaceColonizationBranch::move(glm::vec3 pos, glm::vec3 parentPos){
    this->position = pos + parentPos;
}

glm::vec3 ofxSpaceColonizationBranch::getPosition() const {
    return this->position;
}

glm::vec3 ofxSpaceColonizationBranch::getDirection() const {
    return this->direction;
};

void ofxSpaceColonizationBranch::setDirection(glm::vec3 _vec){
    this->direction = _vec;
};

void ofxSpaceColonizationBranch::setPosition(glm::vec3 pos){
    this->position = pos;
}

int ofxSpaceColonizationBranch::getIndexParent() const{
    return this->indexParent;
}

void ofxSpaceColonizationBranch::reset(){
    this->direction = this->originalDirection;
    this->count = 0;
}


