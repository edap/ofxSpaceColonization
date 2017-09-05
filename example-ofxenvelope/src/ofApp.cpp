#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    //gui
    gui.setup();
    gui.setPosition(ofGetWidth()-200, 0);
    gui.add(selectedMaxDist.set("MaxDist", 150, 90, 300));
    gui.add(selectedMinDist.set("MinDist", 10, 3, 90));
    gui.add(trunkLength.set("trunkLenght", 150, 10, 300));
    gui.add(selectedLength.set("selectedLength", 6, 2, 30));
    gui.add(radius.setup("radius", 11.0, 1.0, 32.0));
    gui.add(radiusScale.setup("radius scale", 0.98, 0.85, 1.0));
    gui.add(slowness.set("slowness", 4, 1, 10));
    gui.add(buildAgain.setup("build it again"));
    gui.add(saveMesh.setup("save mesh",false));
    gui.add(showWireframe.setup("wireframe", false));
    // gui colors
    gui.add(diffuseColor.setup("diffuse color", ofColor(255, 105, 255), ofColor(0, 0), ofColor(255, 255)));
    gui.add(emissiveColor.setup("emissive color", ofColor(217, 44, 5), ofColor(0, 0), ofColor(255, 255)));
    gui.add(lightColor.setup("light color", ofColor(83, 255, 161), ofColor(0, 0), ofColor(255, 255)));
    gui.add(bgColor.setup("bg color", ofColor(92, 206, 208), ofColor(0, 0), ofColor(255, 255)));
    // gui envelope
    gui.add(modelEnvelope.setup("model envelope mode",false));
    gui.add(angle.setup("angle", 0.002, 0.001, 0.02));
    gui.add(cutTop.setup("cutTop %", 0.0, 0.0, 0.9));
    gui.add(xDev.setup("xDev %", 0.2, 0.0, 0.9));
    gui.add(yDev.setup("yDev %", 0.2, 0.0, 0.9));
    gui.add(nVertices.setup("nVertices", 400, 10, 4000));
    gui.add(height.setup("height", 400, 10, 1000));

    gui.add(applyWind.setup("apply wind",false));
    gui.add(windFreq.setup("windFreq", 0.1, 0.1, 10.0));
    gui.add(windAmpl.setup("windAmpl", 1.0, 0.1, 200.0));

    light.setPosition(-600, 800, 0);
    light.setAmbientColor(ofColor(lightColor));
    light.enable();
    mat.setDiffuseColor(ofColor(diffuseColor));
    mat.setEmissiveColor(ofColor(emissiveColor));

    auto opt = ofxSpaceColonizationOptions({
        selectedMaxDist,                 // max_dist
        selectedMinDist,                 // min_dist
        150,                             // trunk_length
        glm::vec4(0.0f,0.0f,0.0f, 1.0f), // rootPosition
        glm::vec3(0.0f, 1.0f, 0.0f),     // rootDirection
        selectedLength,                  // branchLength
        false,                           // done growing (is it still used? check)
        true,                            // cap
        radius,                          // radius;
        32,                              // resolution;
        1,                               // textureRepeat;
        radiusScale                      // radiusScale;
    });
    tree.setup(opt);

    auto optEnv = ofxEnvelopeOptions{
        400,   // curveHeight
        1.0f,   // curveCutoff
        0.002f, // curvature
        600,   // nVertices
        0.3f,   //deviationOnY (percent on the height)
        0.3f   //deviationOnX (percent on the ray)
    };
    env.setup(optEnv);
    tree.build();

    //listeners
    selectedMaxDist.addListener(this, &ofApp::selectedMaxDistChanghed);
    selectedMinDist.addListener(this, &ofApp::selectedMinDistChanghed);
    selectedLength.addListener(this, &ofApp::selectedLengthChanghed);
    trunkLength.addListener(this, &ofApp::trunkLengthChanghed);
    radius.addListener(this, &ofApp::radiusChanghed);
    buildAgain.addListener(this, &ofApp::buildAgainPressed);
    radiusScale.addListener(this, &ofApp::radiusScaleChanghed);
    angle.addListener(this, &ofApp::angleChanghed);
    cutTop.addListener(this, &ofApp::cutTopChanghed);
    xDev.addListener(this, &ofApp::deviationOnXChanghed);
    yDev.addListener(this, &ofApp::deviationOnYChanghed);
    nVertices.addListener(this, &ofApp::nVerticesChanghed);
    height.addListener(this, &ofApp::heightChanghed);
    saveMesh.addListener(this, &ofApp::saveMeshPressed);
}

//--------------------------------------------------------------
void ofApp::update(){
    if (!modelEnvelope) {
        light.setAmbientColor(ofColor(lightColor));
        mat.setDiffuseColor(ofColor(diffuseColor));
        mat.setEmissiveColor(ofColor(emissiveColor));
        ofSetBackgroundColor(ofColor(bgColor));
        if( ofGetFrameNum() % slowness==0){
            if (applyWind) {
                float t = ofGetElapsedTimef();
                float n = ofSignedNoise(t * windFreq) * windAmpl;
                auto wind = glm::vec3(n,0.0,0.0);
                tree.grow(wind);
            } else {
                tree.grow();
            }

        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    camera.begin();
    if(!modelEnvelope){
        light.draw();
        auto leaves = tree.getLeaves();
        // draw leaves
        for (auto l:leaves) {
            glm::vec3 pos = l.getPosition();
            ofDrawSphere(pos.x, pos.y, pos.z,10);
        }

        mat.begin();
        if (showWireframe) {
           tree.drawWireframe();
           //tree.drawNormals(abs(sin(ofGetElapsedTimef()*0.5)* 6));
        } else {
           tree.draw();
        }
        mat.end();

    } else {
        this->env.draw();

    }
    ofDisableDepthTest();
    camera.end();
    maybeDrawGui();
}

void ofApp::maybeDrawGui(){
    if (drawGui) {
        ofPushStyle();
        //fps
        string msg = "\n\nfps: " + ofToString(ofGetFrameRate(), 2);
        ofDrawBitmapStringHighlight(msg, 10, 10);
        //gui
        gui.draw();
        ofPopStyle();
    }
}

void ofApp::selectedMaxDistChanghed(int & aselectedMaxDist){
    tree.options.maxDist = aselectedMaxDist;
}

void ofApp::selectedMinDistChanghed(int & aselectedMinDist){
    tree.options.minDist = aselectedMinDist;
}

void ofApp::trunkLengthChanghed(int & trunkLenght){
    tree.options.trunkLength = trunkLenght;
};

void ofApp::selectedLengthChanghed(int & aselectedLength){
    tree.options.branchLength = aselectedLength;
}

void ofApp::radiusChanghed(float & _radius){
    tree.options.radius = _radius;
}

void ofApp::radiusScaleChanghed(float & _radiusScale){
    tree.options.radiusScale = _radiusScale;
}

void ofApp::buildAgainPressed(){
    tree.clear();
    tree.setLeavesPositions(env.getPoints());
    tree.build();
}

void ofApp::angleChanghed(float & _angle){
    env.options.curvature = _angle;
    setUpPointsAndRebuild();
}

void ofApp::deviationOnYChanghed(float & _devY){
    env.options.deviationOnY = _devY;
    setUpPointsAndRebuild();
}

void ofApp::deviationOnXChanghed(float & _devX){
    env.options.deviationOnX = _devX;
    setUpPointsAndRebuild();
}

void ofApp::saveMeshPressed(){
    string randomFilename = ofGetTimestampString() + ".ply";
    tree.getMesh().save(randomFilename);
}

void ofApp::heightChanghed(int & _height){
    env.options.curveHeight = _height;
    setUpPointsAndRebuild();
};

void ofApp::nVerticesChanghed(int & _nVertices){
    env.options.nVertices = _nVertices;
    setUpPointsAndRebuild();
};

void ofApp::cutTopChanghed(float & _cutTop){
    env.options.curveCutoffTop = _cutTop;
    setUpPointsAndRebuild();
}

void ofApp::setUpPointsAndRebuild(){
    env.clear();
    env.setupPoints();

    auto pos = glm::vec3(0.0f, tree.options.trunkLength, 0.0f);
    env.moveTo(pos);

    tree.clear();
    tree.setLeavesPositions(env.getPoints());
    tree.build();
};

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g'){
        drawGui = !drawGui;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
