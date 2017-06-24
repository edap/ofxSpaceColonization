#include "ofxSpaceColonizationBranch.h"

glm::vec3 ofxSpaceColonizationBranch::getModifiedDirection() const {
    return this->modifiedDirection;
};

glm::vec3 ofxSpaceColonizationBranch::getOldDirection() const {
    return this->originalDirection;
};

int ofxSpaceColonizationBranch::getCount() const {
    return this->count;
};

void ofxSpaceColonizationBranch::addToDirection(glm::vec3 _newDir){
    this->modifiedDirection = this->modifiedDirection + _newDir;
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
    this->modifiedDirection = this->originalDirection;
    this->count = 0;
}


