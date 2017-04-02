#pragma once

#include "ofMain.h"
#include "ofxSpaceColonizationBranch.h"
#include "ofxSpaceColonizationLeaf.h"

class ofxSpaceColonization {
public:
	ofxSpaceColonization();
    void grow();
    void draw();
private:
    void addBranchToMesh(shared_ptr<ofxSpaceColonizationBranch> branch);
    vector<ofxSpaceColonizationLeaf> leaves;
    std::vector<shared_ptr<ofxSpaceColonizationBranch>> branches;
    int n_leaves = 100;
    int max_dist = 150;
    int min_dist = 13;
    int branch_length = 5;
    ofMesh mesh;
};
