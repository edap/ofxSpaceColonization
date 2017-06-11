#pragma once

#include "ofMain.h"
#include "ofxSpaceColonizationBranch.h"
#include "ofxSpaceColonizationLeaf.h"
#include "ofxSpaceColonizationHelper.h"

class ofxSpaceColonization {
public:
	ofxSpaceColonization();
    void build();
    void grow();
    void draw2d();

    void setMinDist(int min_dist);
    void setMaxDist(int max_dist);
    void setBranchLength(int branch_length);
    void setTrunkLength(int trunk_length);
    void setRootDirection(ofVec3f root_direction);
    void setRootPosition(ofVec3f root_position);
    void setLeavesPositions(vector<ofVec3f> leaves_positions);
    void set3d(bool use3d);

private:
    void addBranchToMesh(shared_ptr<ofxSpaceColonizationBranch> branch);
    vector<ofxSpaceColonizationLeaf> leaves;
    std::vector<shared_ptr<ofxSpaceColonizationBranch>> branches;
    int n_leaves = 100;
    int max_dist = 150;
    int min_dist = 10;
    int trunk_length = 300;
    ofVec3f root_position = ofVec3f(0.0f,0.0f,0.0f);
    ofVec3f root_direction = ofVec3f(0, 1, 0);
    vector<ofVec3f> leaves_positions;
    bool use3d = false;
    int branch_length = 5;
    bool done_growing = false;
};
