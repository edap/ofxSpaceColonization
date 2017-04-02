#pragma once

#include "ofMain.h"
#include "ofxSpaceColonizationBranch.h"
#include "ofxSpaceColonizationLeaf.h"

class ofxSpaceColonization {
public:
	ofxSpaceColonization();
    void grow();
    void draw();
    void setMinDist(int min_dist);
    void setMaxDist(int max_dist);
    void setBranchLength(int branch_length);
private:
    void addBranchToMesh(shared_ptr<ofxSpaceColonizationBranch> branch);
    vector<ofxSpaceColonizationLeaf> leaves;
    std::vector<shared_ptr<ofxSpaceColonizationBranch>> branches;
    int n_leaves = 100;
    int max_dist = 150;
    int min_dist = 10;
    int branch_length = 5;
    bool done_growing = false;
    ofMesh mesh;
};
