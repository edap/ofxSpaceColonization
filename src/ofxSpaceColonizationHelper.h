#pragma once
#include "ofMain.h"

class ofxSpaceColonizationHelper{
    
public:
    static const vector<glm::vec3> genRandomLeavesPositions(int _width,
                                                          int _height,
                                                          int n_particles,
                                                          bool use2d,
                                                          int _trunk_length);
};
