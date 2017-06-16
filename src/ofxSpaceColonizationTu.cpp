#include "ofxSpaceColonizationTu.h"

ofxSpaceColonizationTu::ofxSpaceColonizationTu(glm::vec3 startPos, glm::vec3 endPos, glm::vec3 startDir, glm::vec3 endDir, ofMesh& mesh){
    bool cap = false;
    float length = glm::distance(startPos, endPos);
    int resolution = 6;
    const int radius = 8;
    const int scaledRadius = 8;//for now, do not scale the branches;

    // these variables are used to do not stretch the texture
    float circumferenceBottom = radius * 3.1415926f;
    float ratio = circumferenceBottom/length;
    float ratioCap = scaledRadius/length;
    float xWrapLimit = circumferenceBottom/(length/textureRepeat);
    float wrapLimitCap = ratioCap * textureRepeat;

    auto idealUpAxis = glm::vec3(0.0f,1.0f,0.0f);

    //bottom
    glm::quat quatBottom = rotationBetweenVectors(idealUpAxis, startDir);
    glm::mat4x4 rotMatBottom = glm::toMat4(quatBottom);
    glm::mat4 tranMatBottom = glm::translate(glm::vec3(startPos));

    //top
    glm::quat quatTop = rotationBetweenVectors(idealUpAxis, endDir);
    glm::mat4x4 rotMatTop = glm::toMat4(quatTop);
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
        //calculate x and y component
        float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
        float x = radius * cosf(theta);
        float z = radius * sinf(theta);
        glm::vec4 circle = glm::vec4(x, 0.0f, z, 1.0f); // it is a vec4 because
        glm::vec4 circleBottom = tranMatBottom * rotMatBottom * circle;
        glm::vec4 circleTop = tranMatTop * rotMatTop * circle;


        glm::vec2 tcoord;
        tcoord.x = ofMap(i, 0.f, resolution, 0.f, xWrapLimit);
        glm::vec3 normal = glm::normalize(glm::vec3(circleBottom) - startPos);
        // bottom
        tcoord.y = 0;
        mesh.addVertex(glm::vec3(circleBottom));
        mesh.addNormal(normal);
        mesh.addTexCoord(tcoord);

        //top
        tcoord.y = textureRepeat;
        mesh.addVertex(glm::vec3(circleTop));
        mesh.addNormal(normal);
        mesh.addTexCoord(tcoord);
    }

//    // Cylinder cap, NOT USED YET
//    if (cap) {
//        int topMiddlePoint = mesh.getNumVertices();
//        mesh.addVertex(endPos);
//        //glm::vec3 topDir = dir;
//        mesh.addNormal(topDir);
//        mesh.addTexCoord(glm::vec2(wrapLimitCap/2,wrapLimitCap/2));
//
//        for (int i = 0; i <= resolution; i++) {
//            if (i == resolution) {
//                //closing triangle
//                mesh.addIndex(topMiddlePoint);
//                mesh.addIndex(topMiddlePoint+ i + 1);
//                mesh.addIndex(topMiddlePoint+1);
//            } else {
//                //indices
//                mesh.addIndex(topMiddlePoint);
//                mesh.addIndex(topMiddlePoint+ i + 1);
//                mesh.addIndex(topMiddlePoint+ i + 2);
//            }
//            //add vertex
//
//
//            float theta = 2.0f * 3.1415926f * float(i) / float(resolution);
//            float xTop = scaledRadius * cosf(theta);
//            float zTop = scaledRadius * sinf(theta);
//            glm::vec3 topOffset = glm::vec3(xTop, endPos.y, zTop);
//            glm::vec3 circleTemp = endPos + topOffset;
//
//
//            glm::vec2 capTcoord;
//            capTcoord.x = ofMap(xTop, -scaledRadius, scaledRadius, 0.f, wrapLimitCap);
//            capTcoord.y = ofMap(zTop, -scaledRadius, scaledRadius, 0.f, wrapLimitCap);
//            mesh.addVertex(circleTemp);
//            mesh.addNormal(topDir);
//            mesh.addTexCoord(capTcoord);
//        }
//    }

}

glm::quat ofxSpaceColonizationTu::rotationBetweenVectors(glm::vec3 start, glm::vec3 dest){
    start = normalize(start);
    dest = normalize(dest);

    float cosTheta = dot(start, dest);
    glm::vec3 rotationAxis;

    if (cosTheta < -1 + 0.001f){
        // special case when vectors in opposite directions:
        // there is no "ideal" rotation axis
        // So guess one; any will do as long as it's perpendicular to start
        rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
        if (glm::length2(rotationAxis) < 0.01 ) // bad luck, they were parallel, try again!
            rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

        rotationAxis = glm::normalize(rotationAxis);
        //return gtx::quaternion::angleAxis(180.0f, rotationAxis);
        glm::angleAxis(180.0f, rotationAxis);
    }

    rotationAxis = glm::cross(start, dest);
    float s = glm::sqrt( (1+cosTheta)*2 );
    float invs = 1 / s;

    return glm::quat(
                     s * 0.5f,
                     rotationAxis.x * invs,
                     rotationAxis.y * invs,
                     rotationAxis.z * invs
                     );
    
}
