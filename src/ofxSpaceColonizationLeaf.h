#include "ofMain.h"

class ofxSpaceColonizationLeaf {

public:
    ofxSpaceColonizationLeaf(ofVec3f vec);
    void draw();
    ofVec3f getPosition();
    bool reached = false;

private:
    int ray = 20;
    ofVec3f pos;
};

