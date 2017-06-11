#include "ofxSpaceColonizationHelper.h"


const vector<ofVec3f> ofxSpaceColonizationHelper::genRandomLeavesPositions(
        int _width, int _height, int n_particles, bool use3d, int _trunk_length
                ){
    vector<ofVec3f> tmp_particles;
    int ray = 400;
    for(int i = 0; i< n_particles; i++){
        if(use3d){
            ofVec3f pos = ofVec3f(ofRandom(-ray,+ray),
                                  ofRandom(_trunk_length, ray),
                                  ofRandom(-ray,+ray));
            tmp_particles.push_back(pos);
        }else{
            ofVec3f pos = ofVec3f(ofRandom(0, _width),
                                  ofRandom((_height - _trunk_length), 0),
                                  0);
            tmp_particles.push_back(pos);
        }

    }
    return tmp_particles;
}
