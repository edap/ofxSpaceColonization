#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    //gui & listeners
    selectedMaxDist.addListener(this, &ofApp::selectedMaxDistChanghed);
    selectedMinDist.addListener(this, &ofApp::selectedMinDistChanghed);
    selectedLength.addListener(this, &ofApp::selectedLengthChanghed);
    radius.addListener(this, &ofApp::radiusChanghed);
    buildAgain.addListener(this, &ofApp::buildAgainPressed);
    radiusScale.addListener(this, &ofApp::radiusScaleChanghed);
    gui.setup();
    gui.setPosition(ofGetWidth()-200, 0);
    gui.add(selectedMaxDist.set("MaxDist", 150, 90, 300));
    gui.add(selectedMinDist.set("MinDist", 10, 3, 90));
    gui.add(selectedLength.set("selectedLength", 6, 2, 30));
    gui.add(radius.setup("radius", 11.0, 1.0, 32.0));
    gui.add(radiusScale.setup("radius scale", 0.98, 0.85, 1.0));
    gui.add(slowness.set("slowness", 4, 1, 10));
    gui.add(buildAgain.setup("build it again"));
    gui.add(showWireframe.setup("wireframe", false));
    // gui colors
    gui.add(diffuseColor.setup("diffuse color", ofColor(255, 0, 238), ofColor(0, 0), ofColor(255, 255)));
    gui.add(emissiveColor.setup("emissive color", ofColor(63, 182, 87), ofColor(0, 0), ofColor(255, 255)));
    gui.add(lightColor.setup("light color", ofColor(0, 0, 235), ofColor(0, 0), ofColor(255, 255)));
    gui.add(bgColor.setup("bg color", ofColor(53, 137, 222), ofColor(0, 0), ofColor(255, 255)));
    // gui envelope

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
        false,                           // done growing
        false,                           // cap
        radius,                          // radius;
        16,                              // resolution;
        1,                               // textureRepeat;
        radiusScale,                     // radiusScale;
        0.0                              // padding
    });
    tree.setup(opt);
    tree.build();
}

//--------------------------------------------------------------
void ofApp::update(){
    light.setAmbientColor(ofColor(lightColor));
    mat.setDiffuseColor(ofColor(diffuseColor));
    mat.setEmissiveColor(ofColor(emissiveColor));
    ofSetBackgroundColor(ofColor(bgColor));
    if( ofGetFrameNum() % slowness==0){
       tree.grow();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    camera.begin();
    light.draw();
    auto leaves = tree.getLeaves();
    // draw leaves
    for (auto l:leaves) {
        glm::vec3 pos = l.getPosition();
        //cout << pos.y << endl;
        ofDrawSphere(pos.x, pos.y, pos.z,20);
    }

    mat.begin();
    if (showWireframe) {
       tree.drawWireframe();
       //tree.drawNormals(abs(sin(ofGetElapsedTimef()*0.5)* 6));
    } else {
       tree.draw();
    }
    mat.end();

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
    tree.build();
}


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
