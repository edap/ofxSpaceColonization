#include "ofxSpaceColonizationHelper.h"


const vector<glm::vec3> ofxSpaceColonizationHelper::genRandomLeavesPositions(
        int _width, int _height, int n_particles, int _trunk_length
                ){
    vector<glm::vec3> tmp_particles;
    int ray = 400;
    for (int i = 0; i< n_particles; i++) {
        glm::vec3 pos = glm::vec3(ofRandom(-ray,+ray),
                              ofRandom(_trunk_length, 600),
                              ofRandom(-ray,+ray));
        tmp_particles.push_back(pos);
    }

    return tmp_particles;
}
