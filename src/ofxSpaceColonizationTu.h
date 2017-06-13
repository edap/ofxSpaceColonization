#include "ofMain.h"

class ofxSpaceColonizationTu{

public:
    ofxSpaceColonizationTu(glm::vec3 start, glm::vec3 end, glm::vec3 dir, ofMesh& mesh);
    ofMesh getMesh();

private:
    glm::vec3 pos;
    ofMesh mesh;
    int resolution = 6;
    int textureRepeat = 1;
};
