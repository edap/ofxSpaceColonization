#pragma once
#include "ofMain.h"
#include "ofxBranchesPrimitive.h"

class ofxSpaceColonizationBranch : public ofxBranch{

public:
    ofxSpaceColonizationBranch(glm::vec4 startPos, glm::vec4 endPos, glm::quat orientation, glm::vec3 startDir, float _endRadius)
    : ofxBranch(startPos, endPos, orientation, startDir){
        this->nextBranchDirection = getEndDirection();
        this->endRadius = _endRadius;
    };
    
    int getCount() const;
    float getEndRadius() const;
    glm::vec3 getNextBranchDirectionDirection() const; //this has to be used just when calculating the new position

    void reset();
    void correctNextBranchDirection(glm::vec3 _newDir);
    void incrementCounterBy(int _val);

private:
    int count = 0;
    float endRadius = 0;
    glm::vec3 nextBranchDirection;
};

