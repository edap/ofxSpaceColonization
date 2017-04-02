#include "ofMain.h"

class ofxSpaceColonizationBranch{

public:
    ofxSpaceColonizationBranch(ofVec3f _direction);
    void draw();
    void move(ofVec3f _pos);
    void setParent(shared_ptr<ofxSpaceColonizationBranch> branch);
    ofVec3f getPosition();
    void reset();

    ofVec3f direction;
    ofVec3f originalDirection;
    int count = 0;
private:
    ofNode node;
    //ofVec3f parentPos;
    //ofVec3f pos;
};

