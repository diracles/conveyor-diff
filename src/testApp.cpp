#include "testApp.h"
#include <iostream>

//--------------------------------------------------------------
void testApp::setup(){
    ofSetFrameRate(30);
    counter=0;
    
    //    //allows console to receive info about camera
    //    camera.setVerbose(true);
    //
    //      //allocate memory for our ofImage, where we save the frame to
    //    objects.allocate(camera.getWidth(), camera.getHeight(), OF_IMAGE_COLOR);
    //    myFbo.allocate(camera.width, camera.height);
    
    
//    player.loadMovie("spool.mp4");
//    
//    
//    player.play();
    
    //initialize camera
    camera.initGrabber(320,240);
    
    //VID DELAY
    oldestFrameIndex = 0;
    //   oldestFrameIndex2 = 0;
    
    objectBuffer.resize(10);
    //   objectBuffer2.resize(50);
    //   objectBuffer3.resize(200);
    
    check.allocate(320, 240, OF_IMAGE_COLOR);
    
    //allocate an empty image so we have something to work with for the first frame
    frameDif.allocate(320, 240, OF_IMAGE_COLOR);
    
    //set pixel dinemtions
    //pixels values are stored as three numbers in order R-G-B so every third number represents the beginning of a new pixel, which is why we need to multiply by 3
    numPixels = camera.getWidth()*camera.getHeight()*3;
    
    //size up the previous image vector--a vector is a fancy array :)
    previousImage.resize(numPixels);
    
    playbuffer.push_back(frameDif);
    
    
    playIterator = playbuffer.begin();
    objectIterator = objectBuffer.begin();
}

//--------------------------------------------------------------
void testApp::update(){
    //update camera image
    camera.update();
    
    //    player.update();
    
    if (playIterator == playbuffer.end())
        playIterator = playbuffer.begin();
    
    if (objectIterator == objectBuffer.end()) {
        objectIterator = objectBuffer.begin();
    }
    
    
    //    if (isScreenGrabbed) {
    //        //draw saved frame into FBO
    //        myFbo.begin();
    //        //put stuff here
    //        ofPushStyle(); //so alpha only affects FBO
    //        ofEnableAlphaBlending(); //lets us use alpha channel in the FBO
    //        ofSetColor(255, 255, 255, 100); //sets color to full color, then 100 for alpha
    //        //we also want to mirror the screengrab
    //        objects.draw(camera.getWidth(), 0, -camera.getWidth(),camera.getHeight());
    //        //end styles (set color)
    //        ofPopStyle();
    //
    //        //end drawing into FBO
    //        myFbo.end();
    //
    //        //draw FBO
    //        myFbo.draw(0,0);
    //    }
    
    //make sure we have a new frame
    if(camera.isFrameNew()){
        //grab the pixel values out of the camera and the frameDiff image, frame diff is the destination of our new differenced image
        unsigned char * pix = camera.getPixels();
        unsigned char * img = frameDif.getPixels();
        
        //make an int to hold the sum of the total motion in the frame and loop through the pixels
        //pixels values are stored in order R-G-B so every third spot represents the beginning of a new pixel, which is why we +=3 through the array
        int movementSum = 0;
        for(int i=0;i<numPixels;i+=3){
            
            //get the current pixel colors
            float cR = pix[i]; //red
            float cG = pix[i+1]; //green
            float cB = pix[i+2]; //blue
            
            //get back the previous frame's colors
            float pR = previousImage[i]; //red
            float pG = previousImage[i+1]; //green
            float pB = previousImage[i+2]; //blue
            
            //subtract the previous pixel color from the current pixel color and set the absoloute difference (no negative numbers) to new variables.  If there is no difference these numbers equal 0
            float dR = abs(cR-pR); //red diff
            float dG = abs(cG-pG); //green diff
            float dB = abs(cB-pB); //blue diff
            
            //keep a running total of all the positive values from the frame by adding up all the colors
            movementSum += dR+dG+dB;
            
            //fill up the place holder pixel array with the new frame differenced pixels
            img[i] = dR; //new red
            img[i+1] = dG; //new green
            img[i+2] = dB; //new blue
            
            //replace the previous image's pixels with the current pixels to be used next frame
            previousImage[i] = pix[i];
            previousImage[i+1] = pix[i+1];
            previousImage[i+2] = pix[i+2];
            
            
        }
        
        
        //check.setFromPixels( , 320, 240, OF_IMAGE_COLOR);
        //check.reloadTexture();
        //        cout<<movementSum<<endl;
       // if (movementSum>1500000) {
            
            //oldestFrameIndex++;
            //            if(oldestFrameIndex >= objectBuffer.size()){
            //                oldestFrameIndex = 0;
            
            
            if(objectBuffer.size() == 10) {
                for(int i=0; i<10; i++){
                    ofImage holder;
                    holder.setFromPixels(objectBuffer[i]);
                    playbuffer.push_back(holder);
                    
                    //
                    //ofimage holder.setfrompixels(objectbuffer[i]) //push this back into play buffer
                }
                playIterator = playbuffer.begin();
                oldestFrameIndex = 0;
                objectBuffer.clear();
                objectBuffer.resize(10);
                objectIterator = objectBuffer.begin();
                cout<<"cleared"<<endl;
            }
            
            else {
                //  oldestFrameIndex++;
                ofImage newFrame;
                newFrame.setFromPixels(pix, camera.getWidth(), camera.getHeight(), OF_IMAGE_COLOR);
                newFrame.reloadTexture();
                objectBuffer.push_back(newFrame) ;
                
                cout<<"newimage"<<endl;
            }
            
            
            //
            //
            //                //                objectBuffer2[oldestFrameIndex2].setFromPixels(camera.getPixelsRef());
            //                //                oldestFrameIndex2++;
            //                //                if(oldestFrameIndex2 >= objectBuffer2.size()){
            //                //                    oldestFrameIndex2 = 0;
            //            }
           // test = true;
       // }
        
        
        frameDif.reloadTexture();
        
        
        //  if(playbuffer.size()>1){
        if(playbuffer.size() % ofGetFrameNum()==0) {
            counter=0;
            cout<<"fired"<<endl;
        }
        
        else {
            counter++;
        }
        
        // }
        
        
        
    }
    //if there is ANY movement on the screen, do something.  Raise this threshold to make it less sensitive
    
    
    //in this case, pull the differenced pixels into an image to display
    //frameDif.setFromPixels(img, 320, 240, OF_IMAGE_COLOR);
    
    //store image array of frames
    
    
    
}











//--------------------------------------------------------------
void testApp::draw(){
    
    //draw the frame differenced image if you want.
    // frameDif.draw(0, 0, 320, 240);
    
    check.draw(400, 400);
    
    frameDif.draw(600, 400);
    for(int i=0; i<10; i++){
        objectBuffer[i].draw(200,200);
    }
    //if(camera.isFrameNew()){
    
    //      playbuffer[counter].draw(0,0);
    
    if(playIterator != playbuffer.end())
        playIterator->draw(0, 0);
    
    if (objectIterator != objectBuffer.end()) {
        objectIterator->draw(400, 0);
    }
    //CELEBRATE
    camera.draw(0, 300);
    
    //player.draw(0,0);
    
    //    if (test) {
    //        ofSetColor(255, 0, 0);
    //        ofCircle(ofGetWidth()/2, ofGetHeight()/2, 100);
    //        test = false;
    //    }
    //
    //    if(objectBuffer[oldestFrameIndex].isAllocated()){
    //        objectBuffer[oldestFrameIndex].draw(camera.getWidth(), 0);
    //    }
    
    
    //    if(objectBuffer2[oldestFrameIndex2].isAllocated()){
    //        objectBuffer2[oldestFrameIndex2].draw(camera.getWidth(), 0);
    //    }
    
    playIterator++;
    objectIterator++;
    //   }
    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
    //    objects.setFromPixels(camera.getPixelsRef());
    //    isScreenGrabbed = true;
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}