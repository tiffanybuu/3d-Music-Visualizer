#pragma once

#include "ofMain.h"
#include "ofxFEngine3DCore.h"
#include "ofxDatGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
    
    bool wireframe;
    // Audio
    ofSoundPlayer beat;


    
    // bands of frequency
    int bands = 80;
    int sampleRate = 8192;
    
    
    float* value;
    float* fftBins = new float [8192];
    

    
    // Camera Movement
    ofxFEngineFreeCam camera;
    ofxFEngineEnvironment environment;
    

    // Reactive Rectangles Features
    
    // Coordinates/Positions
    float XPOS = 0;
    vector<float> ypos;
    const float ZPOS = 400;
    const float WIDTH = 40;
    const float HEIGHT = 40;
    // displaying frequency on bar definition
    double depthFactor = 100;
    
    vector<ofBoxPrimitive> bandBoxes;
  

    
    // Texture/Lights
    ofLight light;
    
    
    // Helper Function to Create Bands
    void setupBands(int start, int end, int ypos, int multiple);
    

    // Instructions Menu Bar
    ofxDatGuiDropdown* menu;
    void onDropdownEvent(ofxDatGuiDropdownEvent e);
    vector<string> data;
    

  
    
    
    
    // Play and Stop Buttons
    ofxDatGuiButton* play;
    ofxDatGuiButton* stop;
    ofxDatGuiButton* wire;
    void positionButtons();
    void onButtonEvent(ofxDatGuiButtonEvent e);
    ofTrueTypeFont	verdana14;
    
    
    // Sliders
    ofxDatGuiSlider* volume;
    ofxDatGuiSlider* speed;
    ofxDatGuiSlider* amplitude;
    void onSliderEvent(ofxDatGuiSliderEvent e);
    
    
    // Sphere graphic
    vector<ofSpherePrimitive> graphicSphere;
    void setupSpheres();
    
    
    
    
    
    void processOpenFileSelection(ofFileDialogResult openFileResult);

    
    
    
    
    
    
    
		
};
