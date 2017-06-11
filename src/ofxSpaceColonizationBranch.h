#include "ofMain.h"

class ofxSpaceColonizationBranch{

public:
    ofxSpaceColonizationBranch(glm::vec3 _direction);
    void draw();
    void reset();

    glm::vec3 direction;
    glm::vec3 originalDirection;
    int count = 0;

    glm::vec3 getPosition();
    void setPosition(glm::vec3 pos);
    void move(glm::vec3 _pos, glm::vec3 _parentPos);
    int indexParent = 0;
    void setParentByIndex(int parent_index) { this->indexParent = parent_index; };
    glm::vec3 position;

};

