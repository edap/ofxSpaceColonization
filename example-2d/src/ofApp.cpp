#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    gui.setup();
    gui.setPosition(ofGetWidth()-200, 0);
    gui.add(selectedMaxDist.set("MaxDist", 150, 90, 300));
    gui.add(selectedMinDist.set("MinDist", 10, 3, 90));
    gui.add(selectedLength.set("selectedLength", 5, 2, 30));
    tree.build();
}

//--------------------------------------------------------------
void ofApp::update(){
    tree.grow();
}

//--------------------------------------------------------------
void ofApp::draw(){
    auto leaves = tree.getLeaves();
    // draw leaves
    for (auto l:leaves) {
        glm::vec3 pos = l.getPosition();
        ofDrawCircle(pos.x, pos.y, 20);
    }
    //draw branches
    auto nBranches = tree.getSizeBranches();
    for (int i = 0; i < nBranches; i++) {
        float lineWidth = ofMap(i, 0, nBranches, 20, 1);
        ofSetLineWidth(lineWidth);

        auto parentPos = tree.getParentBranchPosition(i);
        auto pos = tree.getBranchPosition(i);


        ofDrawLine(parentPos.x, parentPos.y,
                   parentPos.z, pos.x,
                   pos.y, pos.z);
    }

    maybeDrawGui();
}

void ofApp::maybeDrawGui(){
    if (drawGui) {
        //fps
        string msg = "\n\nfps: " + ofToString(ofGetFrameRate(), 2);
        ofDrawBitmapStringHighlight(msg, 10, 10);
        //gui
        gui.draw();
    }
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
