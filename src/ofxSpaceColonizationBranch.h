#pragma once
#include "ofMain.h"
#include "ofxBranch.h"

class ofxSpaceColonizationBranch : public ofxBranch{

public:
    ofxSpaceColonizationBranch(glm::vec4 startPos, glm::vec4 endPos, glm::quat orientation, glm::vec3 startDir)
    : ofxBranch(startPos, endPos, orientation, startDir){
        this->modifiedDirection = startDir;
        this->originalDirection = startDir;
    };
    
    int getIndexParent() const;
    int getCount() const;
    glm::vec3 getModifiedDirection() const;
    glm::vec3 getOldDirection() const;

    void reset();
    void addToDirection(glm::vec3 _newDir);
    void incrementCounterBy(int _val);
    void setParentByIndex(int parent_index);

private:
    int count = 0;
    glm::vec3 modifiedDirection;
    glm::vec3 originalDirection;
    int indexParent = 0;
};

