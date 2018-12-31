# 3-D Music Visualizer

## Description
Using OpenFrameworks, I created a 3d Music Visualizer. It uses the FFT Theorem to grab frequencies of a particular MP3 or WAV format, and is encapsulated in the form of 3d bars. While playing the song, spheres will show up on the screen. Each of these spheres is connected to one of the bands, and pulsates to the respective frequency. I wanted to create a 3-D visualizer because most of the visualizers I have found online are 2-D, and I thought it would be interesting for the user to be able to move around in an audio-visual environment, creating a more personal user-interactive experience.

## Library
* The addon libraries that are included with this project include:
    * ofxDatGui
    * ofxFEngine3DCore

## Usage

* Using XCode, use the debugger to run the program. The application should pop up. To use the visualizer, press the spacebar in order to select a song file of your choice.
* If you want to stop the song, press the stop button. If you want to restart the song, press the restart button.
* If you want to load in a new song, then press the spacebar again and repeat the process.
* For the sliders, you can input the desired value in the number bar in order to adjust the values.
* Wireframe Feature allows you to see the wireframe of the boxes and spheres. You can toggle the button to turn this feature on and off.
* Once you are done with the application, you can close the application to exit.
