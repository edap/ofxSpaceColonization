#include "ofxSpaceColonizationBranch.h"


ofxSpaceColonizationBranch::ofxSpaceColonizationBranch(const glm::vec3 _direction){
    this->direction = _direction;
    this->originalDirection = _direction;
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

int ofxSpaceColonizationBranch::getCount() const {
    return this->count;
};

void ofxSpaceColonizationBranch::addToDirection(glm::vec3 _newDir){
    this->direction = this->direction + _newDir;
};

void ofxSpaceColonizationBranch::incrementCounterBy(int _val){
    this->count = this->count + _val;
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


