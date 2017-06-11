#include "ofxSpaceColonizationBranch.h"


ofxSpaceColonizationBranch::ofxSpaceColonizationBranch(const ofVec3f _direction){
    direction = _direction;
    originalDirection = _direction;
}

void ofxSpaceColonizationBranch::move(ofVec3f pos, ofVec3f parentPos){
    this->position = pos + parentPos;
}

ofVec3f ofxSpaceColonizationBranch::getPosition(){
    return this->position;
}

void ofxSpaceColonizationBranch::setPosition(ofVec3f pos){
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

