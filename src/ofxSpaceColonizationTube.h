
#pragma once

#include "ofMain.h"
#include "ofxSpaceColonizationBranch.h"

struct ofxSpaceColonizationTubeOptions{
    bool cap;
    float radiusBottom;
    float radiusTop;
    int resolution;
    int textureRepeat;
};

class ofxSpaceColonizationTube{
public:
    static void putIntoMesh(shared_ptr<ofxSpaceColonizationBranch> branch, ofMesh& mesh);
    static void putIntoMesh(shared_ptr<ofxSpaceColonizationBranch> branch, ofMesh& mesh, ofxSpaceColonizationTubeOptions options);

private:
    static void add(shared_ptr<ofxSpaceColonizationBranch> branch, ofMesh& mesh, ofxSpaceColonizationTubeOptions options);
};
