#include "ofMain.h"

class ofxSpaceColonizationTu{

public:
    ofxSpaceColonizationTu(glm::vec3 start, glm::vec3 end, glm::vec3 startDir, glm::vec3 endDir, ofMesh& mesh);
    ofMesh getMesh();
    glm::quat rotationBetweenVectors(glm::vec3 start, glm::vec3 dest);

private:
    glm::vec3 pos;
    ofMesh mesh;
    int resolution = 6;
    int textureRepeat = 1;
};
