#include "ofMain.h"

class ofxSpaceColonizationLeaf {

public:
    ofxSpaceColonizationLeaf(ofVec3f vec);
    void draw2d();
    ofVec3f getPosition();
    void setRay(int _ray);
    bool reached = false;

private:
    int ray = 20;
    ofVec3f pos;
    glm::vec3 posG;
};

