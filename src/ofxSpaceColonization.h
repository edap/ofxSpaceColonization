#pragma once

#include "ofMain.h"
#include "ofxSpaceColonizationBranch.h"
#include "ofxSpaceColonizationLeaf.h"
#include "ofxSpaceColonizationHelper.h"
#include "ofxBranchCylinder.h"

struct ofxSpaceColonizationOptions{
    int maxDist;
    int minDist;
    int trunkLength;
    glm::vec4 rootPosition;
    glm::vec3 rootDirection;
    int branchLength;
    bool doneGrowing;
    bool cap;
    float radius;
    int resolution;
    int textureRepeat;
    float radiusScale;
    float padding;
};

class ofxSpaceColonization : public of3dPrimitive {
public:
	ofxSpaceColonization();
    ofxSpaceColonization(ofxSpaceColonizationOptions opt);

    void build();
    void grow();
    void grow(glm::vec3 wind);
    void clear();

    void setLeavesPositions(vector<glm::vec3> leaves_positions);
    void setup(ofxSpaceColonizationOptions opt);
    ofxSpaceColonizationOptions options;
    vector<ofxSpaceColonizationLeaf> getLeaves() const;

private:
    void makeSureThatThereAreLeaves();
    vector<glm::vec3> leaves_positions;
    vector<ofxSpaceColonizationLeaf> leaves;
    vector<shared_ptr<ofxSpaceColonizationBranch>> branches;

};
