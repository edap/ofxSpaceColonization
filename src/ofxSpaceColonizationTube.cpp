//
//  ofxBranchCylinder.cpp
//  testSpline
//
//  Created by DavidePrati on 23/06/17.
//
//

#include "ofxSpaceColonizationTube.h"
static const ofxSpaceColonizationTubeOptions defaultOptions = {
    false,
    3.0,
    3.0,
    16,
    1
};

void ofxSpaceColonizationTube::putIntoMesh(shared_ptr<ofxSpaceColonizationBranch> branch, ofMesh& mesh){
    add(branch, mesh, defaultOptions);
}

void ofxSpaceColonizationTube::putIntoMesh(shared_ptr<ofxSpaceColonizationBranch> branch, ofMesh& mesh, ofxSpaceColonizationTubeOptions opt){
    add(branch, mesh, opt);
}

void ofxSpaceColonizationTube::add(shared_ptr<ofxSpaceColonizationBranch> branch, ofMesh& mesh, ofxSpaceColonizationTubeOptions opt){
    glm::vec4 startPos = branch->getStartPos();
    glm::vec4 endPos = branch->getEndPos();
    glm::quat startOrientation = branch->getStartOrientation();
    glm::quat endOrientation = branch->getEndOrientation();
    glm::vec3 direction = branch->getStartDirection();
    glm::vec3 endDirection = branch->getEndDirection();

    bool cap = opt.cap;
    int resolution = opt.resolution;
    int textureRepeat = opt.textureRepeat;
    float length = glm::distance(startPos, endPos);
    float radius = opt.radiusBottom;
    float scaledRadius;
    if(opt.radiusTop <= 0.03){
        scaledRadius = 0.03;
    }else{
        scaledRadius = opt.radiusTop;
    }

    //const int scaledRadius = opt.radiusTop;//for now, do not scale the branches;

    // these variables are used to do not stretch the texture
    float circumferenceBottom = radius * 3.1415926f;
    float ratio = circumferenceBottom/length;
    float ratioCap = scaledRadius/length;
    float xWrapLimit = circumferenceBottom/(length/textureRepeat);
    float wrapLimitCap = ratioCap * textureRepeat;

    glm::mat4x4 rotMatBottom = glm::toMat4(startOrientation);
    glm::mat4 tranMatBottom = glm::translate(glm::vec3(startPos));

    //top
    glm::mat4x4 rotMatTop = glm::toMat4(endOrientation);
    glm::mat4 tranMatTop = glm::translate(glm::vec3(endPos));

    // Cylinder body
    int first = mesh.getNumVertices();
    for (int i = 0; i <= resolution; i++) {
        // if it is the last face, close it where the first face
        // was started
        if (i == resolution) {
            mesh.addIndex(first+(i*2));
            mesh.addIndex(first);
            mesh.addIndex(first+1);

            mesh.addIndex(first+1);
            mesh.addIndex(first+(i*2)+1);
            mesh.addIndex(first+(i*2));
        } else {
            mesh.addIndex(first+(i*2));
            mesh.addIndex(first+(i*2)+2);
            mesh.addIndex(first+(i*2)+3);

            mesh.addIndex(first+(i*2)+3);
            mesh.addIndex(first+(i*2)+1);
            mesh.addIndex(first+(i*2));
        }
    }

    for (int i = 0; i <= resolution; i++) {
        //the circle, this is the element that will be moved
        float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        float x_scaled = scaledRadius * cosf(theta);
        float z_scaled = scaledRadius * sinf(theta);
        glm::vec4 circleCenter = glm::vec4(0.0f, 0.0f, 0.0f,1.0);
        glm::vec4 circle = glm::vec4(x, 0.0f, z, 1.0f);
        glm::vec4 circle_scaled = glm::vec4(x_scaled, 0.0f, z_scaled, 1.0f);
        glm::vec4 circleBottom = tranMatBottom * rotMatBottom * circle;
        glm::vec4 circleTop = tranMatTop * rotMatTop * circle_scaled;
        glm::vec4 normalTop = glm::normalize(
                                             (rotMatTop * circle_scaled ) -
                                             (rotMatTop * circleCenter)
                                             );
        glm::vec4 normalBottom = glm::normalize(
                                                (rotMatBottom * circle ) -
                                                (rotMatBottom * circleCenter)
                                                );

        glm::vec2 tcoord;
        tcoord.x = ofMap(i, 0.f, resolution, 0.f, xWrapLimit);

        // bottom
        tcoord.y = 0;
        mesh.addVertex(glm::vec3(circleBottom));
        mesh.addNormal(glm::vec3(normalBottom));
        mesh.addTexCoord(tcoord);

        //top
        tcoord.y = textureRepeat;
        mesh.addVertex(glm::vec3(circleTop));
        mesh.addNormal(glm::vec3(normalTop));
        mesh.addTexCoord(tcoord);
    }

    // Cylinder cap
    if (cap) {
        int topMiddlePoint = mesh.getNumVertices();
        glm::vec3 topDir = endDirection;

        mesh.addVertex(glm::vec3(endPos));
        mesh.addNormal(topDir);
        mesh.addTexCoord(glm::vec2(wrapLimitCap/2,wrapLimitCap/2));

        for (int i = 0; i <= resolution; i++) {
            if (i == resolution) {
                //closing triangle
                mesh.addIndex(topMiddlePoint);
                mesh.addIndex(topMiddlePoint+ i + 1);
                mesh.addIndex(topMiddlePoint+1);
            } else {
                //indices
                mesh.addIndex(topMiddlePoint);
                mesh.addIndex(topMiddlePoint+ i + 1);
                mesh.addIndex(topMiddlePoint+ i + 2);
            }

            float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
            float x = scaledRadius * cosf(theta);
            float z = scaledRadius * sinf(theta);
            glm::vec4 circle = glm::vec4(x, 0.0f, z, 1.0f);
            glm::vec4 circleTop = tranMatTop * rotMatTop * circle;
            glm::vec2 capTcoord;
            capTcoord.x = ofMap(x, -scaledRadius, scaledRadius, 0.f, wrapLimitCap);
            capTcoord.y = ofMap(z, -scaledRadius, scaledRadius, 0.f, wrapLimitCap);
            mesh.addVertex(glm::vec3(circleTop));
            mesh.addNormal(topDir);
            mesh.addTexCoord(capTcoord);
        }
    }
}



