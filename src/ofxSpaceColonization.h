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
    void setMinDist(int min_dist);
    void setMaxDist(int max_dist);
    void setBranchLength(int branch_length);
    void setTrunkLength(int trunk_length);
    void setRootDirection(glm::vec3 root_direction);
    void setRootPosition(glm::vec3 root_position);
    void setLeavesPositions(vector<glm::vec3> leaves_positions);
    void set2d(bool use2d);

    void setup(ofxSpaceColonizationOptions opt);

private:
    ofxSpaceColonizationOptions options;
    void addBranchToMesh(shared_ptr<ofxSpaceColonizationBranch> branch);
    vector<ofxSpaceColonizationLeaf> leaves;
    vector<shared_ptr<ofxSpaceColonizationBranch>> branches;
    vector<glm::vec3> leaves_positions;
    ofMesh         mesh;
    //these needs to be moved to the options
    int max_dist = 150;
    int min_dist = 10;
    int trunk_length = 150;
    glm::vec4 root_position = glm::vec4(0.0f,0.0f,0.0f, 1.0f);
    glm::vec3 root_direction = glm::vec3(0.0f, 1.0f, 0.0f);
    bool use2d = false;
    int branch_length = 15;
    bool done_growing = false;

};
