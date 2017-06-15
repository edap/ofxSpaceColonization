#include "ofxSpaceColonizationTu.h"

ofxSpaceColonizationTu::ofxSpaceColonizationTu(glm::vec3 startPos, glm::vec3 endPos, glm::vec3 startDir, glm::vec3 endDir, ofMesh& mesh){
    auto dir = startDir;
    bool cap = false;
    float length = glm::distance(startPos, endPos);
    const int radius = 8;
    const int scaledRadius = 8;//for now, do not scale the branches;

    // these variables are used to do not stretch the texture
    float circumferenceBottom = radius * 3.1415926f;
    float ratio = circumferenceBottom/length;
    float ratioCap = scaledRadius/length;
    float xWrapLimit = circumferenceBottom/(length/textureRepeat);
    float wrapLimitCap = ratioCap * textureRepeat;

    //ofMatrix4x4 beginMatrix = branch.begin.getGlobalTransformMatrix();
    //ofMatrix4x4 endMatrix = branch.end.getGlobalTransformMatrix();

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
        //calculate x and y component
        float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        //cout << z << endl;

        auto perp = glm::perp(startPos,dir);
        cout << perp << endl;
        glm::vec3 offset = glm::vec3(x, startPos.y, z);
        glm::vec3 circleBottom = startPos + offset;
        glm::vec3 direction = glm::normalize(circleBottom);

        float xTop = scaledRadius * cosf(theta);
        float zTop = scaledRadius * sinf(theta);
        glm::vec3 topOffset = glm::vec3(xTop, endPos.y, zTop);
        glm::vec3 circleTop = endPos + topOffset;
        glm::vec3 directionTop = dir;

        glm::vec2 tcoord;
        tcoord.x = ofMap(i, 0.f, resolution, 0.f, xWrapLimit);

        // bottom
        tcoord.y = 0;
        mesh.addVertex(circleBottom);
        mesh.addNormal(direction);
        mesh.addTexCoord(tcoord);

        //top
        tcoord.y = textureRepeat;
        mesh.addVertex(circleTop);
        mesh.addNormal(directionTop);
        mesh.addTexCoord(tcoord);
    }

    // Cylinder cap, NOT USED YET
    if (cap) {
        int topMiddlePoint = mesh.getNumVertices();
        mesh.addVertex(endPos);
        glm::vec3 topDir = dir;
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
            //add vertex


            float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
            float xTop = scaledRadius * cosf(theta);
            float zTop = scaledRadius * sinf(theta);
            glm::vec3 topOffset = glm::vec3(xTop, endPos.y, zTop);
            glm::vec3 circleTemp = endPos + topOffset;


            glm::vec2 capTcoord;
            capTcoord.x = ofMap(xTop, -scaledRadius, scaledRadius, 0.f, wrapLimitCap);
            capTcoord.y = ofMap(zTop, -scaledRadius, scaledRadius, 0.f, wrapLimitCap);
            mesh.addVertex(circleTemp);
            mesh.addNormal(topDir);
            mesh.addTexCoord(capTcoord);
        }
    }

}


