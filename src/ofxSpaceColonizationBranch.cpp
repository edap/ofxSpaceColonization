#include "ofxSpaceColonizationBranch.h"

glm::vec3 ofxSpaceColonizationBranch::getNextBranchDirectionDirection() const {
    return this->nextBranchDirection;
};

int ofxSpaceColonizationBranch::getCount() const {
    return this->count;
};

float ofxSpaceColonizationBranch::getEndRadius() const {
    return this->endRadius;
};


void ofxSpaceColonizationBranch::correctNextBranchDirection(glm::vec3 _newDir){
    this->nextBranchDirection = this->nextBranchDirection + _newDir;
};

void ofxSpaceColonizationBranch::incrementCounterBy(int _val){
    this->count = this->count + _val;
};

void ofxSpaceColonizationBranch::reset(){
    this->nextBranchDirection = getEndDirection();
    this->count = 0;
}


