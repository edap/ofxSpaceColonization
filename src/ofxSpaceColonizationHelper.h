#pragma once
#include "ofMain.h"

class ofxSpaceColonizationHelper{
public:
    static const vector<ofVec3f> genRandomLeavesPositions(int _width,
                                                          int _height,
                                                          int n_particles,
                                                          bool use3d,
                                                          int _trunk_length);
};
