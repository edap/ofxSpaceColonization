#include "ofxSpaceColonizationBranch.h"


ofxSpaceColonizationBranch::ofxSpaceColonizationBranch(const ofVec3f _direction){
    direction = _direction;
    originalDirection = _direction;
}

void ofxSpaceColonizationBranch::moveV(ofVec3f pos, ofVec3f parentPos){
    this->position = pos + parentPos;
}

ofVec3f ofxSpaceColonizationBranch::getVPosition(){
    return this->position;
    //return this->position;
}

void ofxSpaceColonizationBranch::setVPosition(ofVec3f pos){
    this->position = pos;
    //return this->position;
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

