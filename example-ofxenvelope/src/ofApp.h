#pragma once

#include "ofMain.h"
#include "ofxSpaceColonization.h"
#include "ofxGui.h"
#include "ofxEnvelope.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    void maybeDrawGui();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void selectedMinDistChanghed(int & aselectedMinDist);
    void selectedMaxDistChanghed(int & aselectedMaxDist);
    void selectedLengthChanghed(int & aselectedLength);
    void trunkLengthChanghed(int & atrunkLength);
    void radiusChanghed(float & radius);
    void radiusScaleChanghed(float & radiusScaleChanghed);
    void buildAgainPressed();
    void angleChanghed(float & angle);
    void deviationOnYChanghed(float & yDev);
    void deviationOnXChanghed(float & xDev);
    void nVerticesChanghed(int & nVertices);
    void heightChanghed(int & _height);
    void saveMeshPressed();

    void setUpPointsAndRebuild();

    ofxPanel gui;
    bool drawGui = true;
    ofParameter<int>    selectedMaxDist;
    ofParameter<int>    selectedMinDist;
    ofParameter<int>    selectedLength;
    ofParameter<int>    slowness;
    ofxFloatSlider      radius;
    ofxFloatSlider      radiusScale;
    ofParameter<int>    trunkLength;
    ofxButton           buildAgain;
    ofxToggle           showWireframe;
    ofxToggle           modelEnvelope;
    ofxButton saveMesh;


    ofxColorSlider diffuseColor;
    ofxColorSlider emissiveColor;
    ofxColorSlider lightColor;
    ofxColorSlider bgColor;

    //envelope params
    ofxFloatSlider angle;
    ofxFloatSlider yDev;
    ofxFloatSlider xDev;
    ofxIntSlider height;
    ofxIntSlider nVertices;

    ofxToggle applyWind;
    ofxFloatSlider windFreq;
    ofxFloatSlider windAmpl;

    ofEasyCam camera;
    ofxSpaceColonization tree;
    ofxEnvelope env;
    ofMaterial mat;
    ofLight light;
    
};
