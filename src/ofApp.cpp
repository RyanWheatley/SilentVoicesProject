#include "ofApp.h"

/**********  WARNING  ***********************
 To avoid the hazard of damaging your ears,
 do not listen the project's output sound with headphones.
 This project uses low-level audio output, so due
 possible errors in software it can suddenly
 generate clicks and very loud sounds.
 ********************************************/

//Constants
const int sampleRate = 44100;           //Sample rate of sound
const float duration = 3.25;            //Duration of the recorded sound in seconds
const int N = duration * sampleRate;    //Size of the PCM buffer

const float volume = 0.5;    //Output sound volume

//Variables
int recPos = 0;                //Current recording position in the buffer
int playPos = 0;            //Current playing position in the buffer

int recordingEnabled = 1;    //Is recording enabled
int playingEnabled = 0;        //Is playing enabled


//--------------------------------------------------------------
void ofApp::setup(){
    //Set buffer size and fill it by zeros
    buffer.resize( N, 0.0 );
    //Start the sound output in stereo (2 channels)
    //and sound input in mono (1 channel)
    soundStream.setup( this, 2, 1, sampleRate, 256, 4 );
    playCount=0;
}

//--------------------------------------------------------------
void ofApp::update(){
    //Nothing here
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( 255, 255, 255 );    //Set the background color
    
    int w = 1024;    //Width of the sound visualization picture
    
    //Graph of the sound buffer
    ofSetColor( 0, 0, 0 );
    for (int x=0; x<w; x++) {
        int i = float(x) * N / w;   //Convert x to buffer's position
        ofLine( x, 100, x, 100 - buffer[i] * 100 );
    }
    
}

//--------------------------------------------------------------
//Audio input
void ofApp::audioReceived(float *input, int bufferSize, int nChannels )
{
    //If recording is enabled by the user,
    //then store received data
    if ( recordingEnabled ) {
        for (int i=0; i<bufferSize; i++) {
            buffer[ recPos ] = input[i];
            recPos++;
            //When the end of buffer is reached, recPos sets
            //to 0, so we record sound in a loop
            recPos %= N;
        }
    }
}

//--------------------------------------------------------------
//Audio output
void ofApp::audioOut(float *output, int bufferSize, int nChannels)
{
    //If playing is enabled by the user, then do output sound
    if ( playingEnabled ) {
        for (int i=0; i<bufferSize; i++) {
            
            if(playCount ==1){
            output[ 2*i ] =0;
            output[ 2*i + 1]= buffer[ playPos ] * (1.0 - playCount/10.0); // reduce the volume each time we
            }
         
            
            else{
                output[ 2*i ] = buffer[ playPos ] * (1.0 - playCount/10.0); // reduce the volume each time we
                output[ 2*i + 1]= 0;
            }
            
            playPos++;
            //When the end of buffer is reached, playPos sets
            //to 0, so we hear looped sound
            playPos %= N;
            if (playPos == bufferSize - 1){ // just to keep count of how many times we go throgh the whole sound buffer
                playCount ++;
                playPos %2;
                
                if (playCount >9){ // to count up to nine and stop playing
                    playingEnabled = 0;
                    cout << " playing stopped" << endl; // debug to console
                }
                cout << "played " << playCount << endl; // debug to console
                
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case '1':
            buffer.clear(); //flush sound buffer
            recPos = 0; //start recoding from zero
            playingEnabled = 0; // stop playing
            recordingEnabled = 1; // start recording
            
            break;
            
        case '2':
            recordingEnabled = 0; // stop recording
            playingEnabled = 0; // stop playing
            break;
            
        case ' ':
            buffer.clear(); //flush sound buffer
            recPos = 0; //start recoding from zero
            playingEnabled = 0; // stop playing
            recordingEnabled = 1; // start recording
            break;
            
        default:
            break;
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case ' ':
            playPos = 0; //reset play position
            recordingEnabled = 0;
            playCount = 0;
            playingEnabled = 1; // start playing
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
