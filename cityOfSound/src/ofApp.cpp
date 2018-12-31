#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(10, 10, 10);
    environment.setup();
    ofSetFrameRate(120);
    ofSetVerticalSync(true);
    
    ofEnableDepthTest();
    // Set camera speed and position
    camera.setSpeed(10);
    camera.setPosition(500,0,500);
    
    // Set camera slow down rate after you release the button
    camera.setDecelerationMove(0.95);
    camera.setDecelerationRotate(0.9);
    
    // Set camera controls
    // w - forward, s - backward, a - left, d - right, u - up, j - down
    camera.setButtonsMovement('w', 's', 'a', 'd', 'u', 'j');
    
    // Setup Light Controls
    light.setPointLight();
    light.setPosition(2000,2000,2000);
    light.enable();
    
    
    for (int i = 0; i < 8192; i++) {
        fftBins[i] = 0;
    }
    
    ypos.push_back(500);
    ypos.push_back(650);
    ypos.push_back(800);
    ypos.push_back(950);
    ypos.push_back(1100);
    ypos.push_back(1250);
    ypos.push_back(1400);
    ypos.push_back(1550);
    
    // Initialize Vector of Bands and Spheres (and random position of Spheres)
    for (int i = 0; i < bands; i++) {
        bandBoxes.push_back(ofBoxPrimitive());
        graphicSphere.push_back(ofSpherePrimitive());

        graphicSphere.at(i).setPosition(ofRandom(-300, 1800), ofRandom(-100, 1800), ofRandom(-100, 800));
        
    }
    
    
    // Creating Buttons
    ofDisableDepthTest();
    play = new ofxDatGuiButton("RESTART");
    stop = new ofxDatGuiButton("STOP");
    wire = new ofxDatGuiButton("WIREFRAME");
    
    positionButtons();
    
    // Listen for events
    play->onButtonEvent(this, &ofApp::onButtonEvent);
    stop->onButtonEvent(this, &ofApp::onButtonEvent);
    wire->onButtonEvent(this, &ofApp::onButtonEvent);
    
    wire->setPosition(0, 150);
    
    // Volume Slider
    volume = new ofxDatGuiSlider("VOLUME", 0, 1.0);
    volume->setWidth(ofGetWidth()/4, .2); // make label area 20% of width //
    volume->setPosition(0, 60);
    volume->onSliderEvent(this, &ofApp::onSliderEvent);
    
    // Speed Slider
    speed = new ofxDatGuiSlider("SPEED", -3.0, 3, 1.0);
    speed->setWidth(ofGetWidth()/4, .2);
    speed->setPosition(0, 90);
    speed->onSliderEvent(this, &ofApp::onSliderEvent);
    
    // Amplitude Slider
    amplitude = new ofxDatGuiSlider("AMPLITUDE", 50, 300, 100);
    amplitude->setWidth(ofGetWidth()/4, .3);
    amplitude->setPosition(0, 120);
    amplitude->onSliderEvent(this, &ofApp::onSliderEvent);

    
    // Song Playlist
    data.push_back("Press Spacebar for New Song");
    data.push_back("Optimal Amplitude = 100 || Range: 30 - 300");
    data.push_back("Wireframe: press 1");
    menu = new ofxDatGuiDropdown("HOW TO USE", data);
    menu->setPosition(0, 180);
    
    
   wireframe  = false;
    


}

//--------------------------------------------------------------
void ofApp::update(){
    camera.update();
    ofSoundUpdate();
    
    
    
    // ofSoundGetSpectrum = gets fft sample and puts it in an array
    value = ofSoundGetSpectrum(bands);
    
    // Smooth Downward
    for (int i = 0; i < bands; i++) {
        fftBins[i] *= 0.96f;
        
        // taking the maximum, either the smooth or the incoming
        if (fftBins[i] < value[i]) {
            fftBins[i] = value[i];
        }
    }
    
    
    ofDisableDepthTest();
    volume->update();
    menu->update();
    play->update();
    stop->update();
    speed->update();
    amplitude->update();
    wire->update();
    

    

    
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    

    camera.begin();
    
    ofEnableDepthTest();
    ofDrawAxis(10);
    

    // Shading the cubes
    
    // Multiplies the overlapping colors --> darker effect
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    // Creates the contrast between blended colors (brigtens)
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    // Set the Color (HSB: Hue, Saturation, Brightness)
    // Changes color and repeats
    ofSetColor(ofColor::fromHsb(ofGetFrameNum()%225,225,225));
    
    
    setupBands(0, bands/8, ypos.at(7), 10);
    setupBands(bands/8, bands/4, ypos.at(6), 10);
    setupBands(bands/4, (bands*3)/8, ypos.at(5), 10);
    setupBands((bands*3)/8, bands/2, ypos.at(4), 10);
    setupBands(bands/2, (bands*5)/8, ypos.at(3), 10);
    setupBands((bands*5)/8, (bands*6)/8, ypos.at(2), 20);
    setupBands((bands*6)/8, (bands*7)/8, ypos.at(1), 60);
    setupBands((bands*7)/8, bands, ypos.at(0), 60);
    
    
    setupSpheres();

    camera.end();
    
    ofDisableDepthTest();
    ofDisableLighting();
    play->draw();
    stop->draw();
    volume->draw();
    speed->draw();
    menu->draw();
    amplitude->draw();
    wire->draw();

    
}



void ofApp::onSliderEvent(ofxDatGuiSliderEvent e)
{
    if (e.target == volume) {
        beat.setVolume(volume->getValue());
    }
    else if (e.target == speed) {
        beat.setSpeed(speed->getValue());
    }

}

void ofApp::onButtonEvent(ofxDatGuiButtonEvent e) {
    if (e.target == play) {
        beat.play();
    }
    else if (e.target == stop) {
        beat.stop();
        
    }
    else if (e.target == wire) {
        wireframe = !wireframe;
    }

}

void ofApp::positionButtons()
{
    play->setPosition(0, 0);
    stop->setPosition(0, 30);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == ' ') {
        ofFileDialogResult openFileResult = ofSystemLoadDialog("Select MP3 or WAV");
        if (openFileResult.bSuccess) {
            processOpenFileSelection(openFileResult);
            
            
            }
    }
    

}
void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){

    
    ofFile file (openFileResult.getPath());
    
    if (file.exists()){
        string fileExtension = ofToUpper(file.getExtension());
        if (fileExtension == "MP3" || fileExtension == "WAV") {
            ofSoundPlayer song;
            beat.load((openFileResult.getPath()));
            beat.play();
        }
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
//---------------------------------------------------
void ofApp::setupBands(int start, int end, int ypos, int multiple) {
    for (int i = start; i < end; i++) {
        // Individual Band Dimensions
        bandBoxes.at(i).set(WIDTH, HEIGHT,((fftBins[i] * amplitude->getValue())*log(i+1)*multiple));
        // Setting Band positions relative to each other
        bandBoxes.at(i).setPosition(XPOS+150*(i-start), ypos, ZPOS);
        
        bandBoxes.at(i).draw();
        
        if (wireframe) {
            bandBoxes.at(i).setResolution(4);
            bandBoxes.at(i).drawWireframe();
        }
    }
}
void ofApp::setupSpheres() {

    for (int i = 0; i < bands; i++) {
        graphicSphere.at(i).set(10*(fftBins[i]*exp(2)), 30);
        
        graphicSphere.at(i).draw();
        
        if (wireframe) {

            graphicSphere.at(i).drawWireframe();
        }

        
    }
}


