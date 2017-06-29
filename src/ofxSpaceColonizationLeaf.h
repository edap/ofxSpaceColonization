#pragma once
#include "ofMain.h"

class ofxSpaceColonizationLeaf {

public:
    ofxSpaceColonizationLeaf(glm::vec3 vec);
    glm::vec3 getPosition() const;
    void setReached(bool _val);
    bool isReached(){ return reached; };
    void move(glm::vec3 pos);

private:
    bool reached = false;
    glm::vec3 pos;
};

