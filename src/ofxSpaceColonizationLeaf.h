#include "ofMain.h"

class ofxSpaceColonizationLeaf {

public:
    ofxSpaceColonizationLeaf();
    void draw();
    ofVec3f getPosition();
    bool reached = false;

private:
    int raggio = 20;
    ofVec3f pos;
};

