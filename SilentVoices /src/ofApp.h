#pragma once

#include "ofMain.h"
#include "ofxPortSF.h"

/*
 This example records and plays short sound sample.
 Press 1 for recording, and press 2 for playing.
 
 It's the example 05-LoopSampler from the book
 "Mastering openFrameworks: Creative Coding Demystified",
 Chapter 6 - Working with Sounds
 
 **********  WARNING  ***********************
 To avoid the hazard of damaging your ears,
 do not listen the project's output sound with headphones.
 This project uses low-level audio output, so due
 possible errors in software it can suddenly
 generate clicks and very loud sounds.
 ********************************************
 */


class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void mousePressed(int x, int y, int button);
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    //Function to convert stereo clip to mono
    void convertToMono();
    
    //Function for receiving audio
    void audioReceived( float *input, int bufferSize, int nChannels );
    
    //Function for generating audio
    void audioOut( float *output, int bufferSize, int nChannels );
    
    //Object for sound output and input setup
    ofSoundStream soundStream;
    vector<float> buffer;        //PCM buffer of sound sample
    
    //Used for loading sound
    PSF_PROPS soundFileProperties;//will be auto-populated when file loaded
    long framesRead, totalFramesRead;//framesread used to check if there are still more frames in file
    int ifd = -1;//identification for the sound file, used by the library
    float* frame = NULL;//location of currently read frame
    vector<float> soundFile;//actual stored sound file
    
    vector<float> monoSumSoundFile;
    int playCount;
};
