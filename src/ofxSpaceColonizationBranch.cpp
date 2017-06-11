#include "ofxSpaceColonizationBranch.h"


ofxSpaceColonizationBranch::ofxSpaceColonizationBranch(const glm::vec3 _direction){
    direction = _direction;
    originalDirection = _direction;
}

void ofxSpaceColonizationBranch::move(glm::vec3 pos, glm::vec3 parentPos){
    this->position = pos + parentPos;
}

glm::vec3 ofxSpaceColonizationBranch::getPosition(){
    return this->position;
}

void ofxSpaceColonizationBranch::setPosition(glm::vec3 pos){
    this->position = pos;
}

void ofxSpaceColonizationBranch::reset(){
    this->direction = this->originalDirection;
    this->count = 0;
}

void ofxSpaceColonizationBranch::draw(){
//    if(this->node.getParent() != nullptr){
//        auto pos = this->node.getGlobalPosition();
//        auto parentPos = this->node.getParent()->getGlobalPosition();
//        ofDrawLine(parentPos.x, parentPos.y, parentPos.z, pos.x, pos.y, pos.z);
//    }
}

