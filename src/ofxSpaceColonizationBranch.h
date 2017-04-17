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

    // try to avoid ofNode
    ofVec3f getVPosition();
    void setVPosition(ofVec3f pos);
    void moveV(ofVec3f _pos, ofVec3f _parentPos);
    int indexParent = 0;
    void setParentByIndex(int parent_index) { this->indexParent = parent_index; };
    ofVec3f position;

private:
    ofNode node;
};

