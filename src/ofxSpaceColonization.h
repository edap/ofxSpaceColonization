#pragma once

#include "ofMain.h"
#include "ofxSpaceColonizationBranch.h"
#include "ofxSpaceColonizationLeaf.h"
#include "ofxSpaceColonizationHelper.h"
#include "ofxBranchCylinder.h"

struct ofxSpaceColonizationOptions{
    int max_dist;
    int min_dist;
    int trunk_length;
    glm::vec4 rootPosition;
    glm::vec3 rootDirection;
    bool use2d;
    int branchLength;
    bool doneGrowing;
    bool cap;
    float radius;
    int resolution;
    int textureRepeat;
    float radiusScale;
};

class ofxSpaceColonization {
public:
	ofxSpaceColonization();
    ofxSpaceColonization(ofxSpaceColonizationOptions opt);
    void build();
    void grow();
    void drawWireframe();
    void draw3d();

    vector<ofxSpaceColonizationLeaf> getLeaves() const;
    int getSizeBranches() const;
    glm::vec3 getBranchPosition(int _index) const;
    glm::vec3 getParentBranchPosition(int _index) const;

    //remove all the setters once that the transition to opt is done
    void setLeavesPositions(vector<glm::vec3> leaves_positions);
    void setup(ofxSpaceColonizationOptions opt);
    ofxSpaceColonizationOptions options;

private:
    void addBranchToMesh(shared_ptr<ofxSpaceColonizationBranch> branch);
    vector<ofxSpaceColonizationLeaf> leaves;
    vector<shared_ptr<ofxSpaceColonizationBranch>> branches;
    vector<glm::vec3> leaves_positions;
    ofMesh         mesh;

};
