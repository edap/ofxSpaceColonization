#include "ofMain.h"

class ofxSpaceColonizationBranch{

public:
    ofxSpaceColonizationBranch(glm::vec3 _direction);
    void reset();
    int getIndexParent() const;
    glm::vec3 getPosition() const;

    glm::vec3 getDirection() const;
    void setDirection(glm::vec3 _vec);

    glm::vec3 direction;
    glm::vec3 originalDirection;
    int count = 0;


    void setPosition(glm::vec3 pos);
    void move(glm::vec3 _pos, glm::vec3 _parentPos);
    void setParentByIndex(int parent_index) { this->indexParent = parent_index; };


private:
    glm::vec3 position;
    int indexParent = 0;
};

