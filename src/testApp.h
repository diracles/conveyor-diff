#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        ofVideoGrabber camera;
    
    ofVideoPlayer player;
    
        ofImage frameDif;
    
        int numPixels;
    
        //--Int array
        vector<int> previousImage;
    
//     ofFbo myFbo;
//    ofImage objects;
//    bool isScreenGrabbed = false;
    
    Boolean test;
    
    int counter;
    int numFrameDelay;
    int oldestFrameIndex;
    int oldestFrameIndex2;
    bool motion;
    vector<ofImage> objectBuffer;   //the vector where we will store our videos (vector of images)
      vector<ofImage> objectBuffer2;
      vector<ofImage> objectBuffer3;
      vector<ofImage> objectBuffer4;
    
    
    vector<ofImage>             playbuffer;
    vector<ofImage>::iterator   playIterator;
    vector<ofImage>::iterator   objectIterator;
    ofImage                     check;
};
