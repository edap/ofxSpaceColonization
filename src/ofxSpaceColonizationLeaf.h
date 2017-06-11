#include "ofMain.h"

class ofxSpaceColonizationLeaf {

public:
    ofxSpaceColonizationLeaf(glm::vec3 vec);
    void draw2d();
    glm::vec3 getPosition() const;
    void setRay(int _ray);
    void setReached(bool _val);
    bool isReached(){ return reached; };
private:
    bool reached = false;
    int ray = 20;
    glm::vec3 pos;
};

