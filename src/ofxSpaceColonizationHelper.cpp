#include "ofxSpaceColonizationHelper.h"


const vector<glm::vec3> ofxSpaceColonizationHelper::genRandomLeavesPositions(
        int _width, int _height, int n_particles, bool use2d, int _trunk_length
                ){
    vector<glm::vec3> tmp_particles;
    int ray = 400;
    for (int i = 0; i< n_particles; i++) {
        if (!use2d) {
    
            glm::vec3 pos = glm::vec3(ofRandom(-ray,+ray),
                                  ofRandom(_trunk_length, 600),
                                  //0);
                                  ofRandom(-ray,+ray));
            tmp_particles.push_back(pos);
        } else {
            glm::vec3 pos = glm::vec3(ofRandom(0, _width),
                                  ofRandom((_height - _trunk_length), 0),
                                  0);
            tmp_particles.push_back(pos);
        }

    }
//    glm::vec3 pos = glm::vec3(-30,_trunk_length+120, 0);
//    glm::vec3 pos2 = glm::vec3(80,_trunk_length+120, 0);
//    tmp_particles.push_back(pos);
//    tmp_particles.push_back(pos2);

    return tmp_particles;
}
