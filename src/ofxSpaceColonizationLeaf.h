#include "ofMain.h"

class ofxSpaceColonizationLeaf {

public:
    ofxSpaceColonizationLeaf(glm::vec3 vec);
    void draw2d();
    glm::vec3 getPosition();
    void setRay(int _ray);
    bool reached = false;

private:
    int ray = 20;
    glm::vec3 pos;
};

