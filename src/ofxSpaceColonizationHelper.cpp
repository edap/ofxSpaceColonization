#include "ofxSpaceColonizationHelper.h"


const vector<glm::vec3> ofxSpaceColonizationHelper::genRandomLeavesPositions(
        int _width, int _height, int n_particles, bool use3d, int _trunk_length
                ){
    vector<glm::vec3> tmp_particles;
    int ray = 400;
    for(int i = 0; i< n_particles; i++){
        if(use3d){
            glm::vec3 pos = glm::vec3(ofRandom(-ray,+ray),
                                  ofRandom(_trunk_length, ray),
                                  ofRandom(-ray,+ray));
            tmp_particles.push_back(pos);
        }else{
            glm::vec3 pos = glm::vec3(ofRandom(0, _width),
                                  ofRandom((_height - _trunk_length), 0),
                                  0);
            tmp_particles.push_back(pos);
        }

    }
    return tmp_particles;
}
