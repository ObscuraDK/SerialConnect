#pragma once

#include "ofMain.h"
#include "ofxUI.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();
    
        void pwrCheck();
        void serialInit();
        void serialSend(int type);
        void guiInit();
    
		void keyPressed(int key);
    
        ofxUICanvas *gui;
        void guiEvent(ofxUIEventArgs &e);
        bool drawPadding;
        float red, green, blue;
		
        // Serial shit
        bool		bSendSerialMessage;			// a flag for sending serial
        char		bytesRead[3];				// data from serial, we will be trying to read 3
        char		bytesReadString[4];			// a string needs a null terminator, so we need 3 + 1 bytes
        int			nBytesRead;					// how much did we read?
        int			nTimesRead;					// how many times did we read?
        float		readTime;					// when did we last read?
    
        ofSerial	serial;
    
        unsigned char buf_pwr[6] = {'(', 'P', 'W', 'R', '?', ')'};
        unsigned char buf_pwr_on[7] = {'(', 'P', 'W', 'R', '1', '!', ')'};
        unsigned char buf_pwr_off[7] = {'(', 'P', 'W', 'R', '0', '!', ')'};
};
