#include "ofxSpaceColonizationBranch.h"

glm::vec3 ofxSpaceColonizationBranch::getNextBranchDirectionDirection() const {
    return this->nextBranchDirection;
};

int ofxSpaceColonizationBranch::getCount() const {
    return this->count;
};

void ofxSpaceColonizationBranch::correctNextBranchDirection(glm::vec3 _newDir){
    this->nextBranchDirection = this->nextBranchDirection + _newDir;
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
    this->nextBranchDirection = getEndDirection();
    this->count = 0;
}


