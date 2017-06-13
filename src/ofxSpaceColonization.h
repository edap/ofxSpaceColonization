#pragma once

#include "ofMain.h"
#include "ofxSpaceColonizationBranch.h"
#include "ofxSpaceColonizationLeaf.h"
#include "ofxSpaceColonizationHelper.h"
#include "ofxSpaceColonizationTu.h"

class ofxSpaceColonization {
public:
	ofxSpaceColonization();
    void build();
    void grow();
    void drawWireframe();
    void draw3d();
    //template <class ofxSpaceColonizationGeom>
    //void grow2(ofxSpaceColonizationGeom geom);

    vector<ofxSpaceColonizationLeaf> getLeaves() const;
    int getSizeBranches() const;
    glm::vec3 getBranchPosition(int _index) const;
    glm::vec3 getParentBranchPosition(int _index) const;

    void setMinDist(int min_dist);
    void setMaxDist(int max_dist);
    void setBranchLength(int branch_length);
    void setTrunkLength(int trunk_length);
    void setRootDirection(glm::vec3 root_direction);
    void setRootPosition(glm::vec3 root_position);
    void setLeavesPositions(vector<glm::vec3> leaves_positions);
    void set2d(bool use2d);

private:
    //template <class ofxSpaceColonizationGeom>
    //void addBranchToMesh(ofxSpaceColonizationGeom geom);
    void addBranchToMesh(glm::vec3 posStart, glm::vec3 posEnd, glm::vec3 dir);
    vector<ofxSpaceColonizationLeaf> leaves;
    vector<shared_ptr<ofxSpaceColonizationBranch>> branches;
    int max_dist = 150;
    int min_dist = 10;
    int trunk_length = 150;
    glm::vec3 root_position = glm::vec3(0.0f,0.0f,0.0f);
    glm::vec3 root_direction = glm::vec3(0.0f, 1.0f, 0.0f);
    vector<glm::vec3> leaves_positions;
    bool use2d = false;
    int branch_length = 5;
    bool done_growing = false;
    ofMesh         mesh;
};
