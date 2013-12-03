#include "testApp.h"
#include <ctime>

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
	ofEnableSmoothing();
    
    // Doing stuff
    serialInit();
    guiInit();
    
    //serialSend(1);
}

void testApp::guiInit()
{
    drawPadding = false;
    gui = new ofxUICanvas();
    gui->getRect()->y = 22;
	gui->addLabel("InFocus 3128HD", OFX_UI_FONT_LARGE);
    gui->addSpacer();
    
    // PWR
    vector<string> pwr_names; pwr_names.push_back("ON"); pwr_names.push_back("OFF");
	gui->addLabel("PWR manage", OFX_UI_FONT_MEDIUM);
	gui->addRadio("HR", pwr_names, OFX_UI_ORIENTATION_HORIZONTAL);
    
    // Source
    gui->addSpacer();
    vector<string> pwr_source; pwr_source.push_back("HDMI1"); pwr_source.push_back("HDMI2");
	gui->addLabel("Source", OFX_UI_FONT_MEDIUM);
	gui->addRadio("HR", pwr_source, OFX_UI_ORIENTATION_HORIZONTAL);
    
    gui->addSpacer();
    vector<string> pwr_autoSource; pwr_autoSource.push_back("ON"); pwr_autoSource.push_back("OFF");
	gui->addLabel("AutoSource", OFX_UI_FONT_MEDIUM);
	gui->addRadio("HR", pwr_autoSource, OFX_UI_ORIENTATION_HORIZONTAL);
    
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    red = 0; blue = 0; green = 0;
	ofBackground(red, green, blue);
    
    gui->setColorBack(ofColor(255,100));
    gui->setWidgetColor(OFX_UI_WIDGET_COLOR_BACK, ofColor(255,100));
}

void testApp::serialInit()
{
    // INIT
	bSendSerialMessage = false;
	
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
    // Serial setup
	int baud = 9600;
	serial.setup("/dev/tty.usbserial", baud); // Default mac osx name
}
void testApp::serialSend(int type)
{
    switch (type)
    {
        case 1: cout << "PWR send ON!" << endl;
            serial.writeBytes(&buf_pwr_on[0], 7);
            break;
        case 2: cout << "PWR send OFF!" << endl;
            serial.writeBytes(&buf_pwr_off[0], 7);
            break;
    }
    
    nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);
    
}

//--------------------------------------------------------------
void testApp::update()
{
    
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground(red, green, blue, 255);
	
	ofPushStyle();
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofPopStyle();
}

void testApp::pwrCheck()
{
    
}
//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
    
    if(kind == OFX_UI_WIDGET_TOGGLE)
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        cout << name << "\t value: " << toggle->getValue() << endl;
        
        // if on
        if (name == "1")
        {
            serialSend(1);
        }
        // if off
        if (name == "2")
        {
            serialSend(2);
        }
    }
}
//--------------------------------------------------------------
void testApp::exit()
{
    delete gui;
}
//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
    switch (key)
    {
        case 'p':
        {
            drawPadding = !drawPadding;
            gui->setDrawWidgetPadding(drawPadding);
        }
            break;
            
        case 'g':
        {
            gui->toggleVisible();
        }
            break;
        default:
            break;
    }
}

//--- Timer
inline void mySleep(clock_t sec) // clock_t is a like typedef unsigned int clock_t. Use clock_t instead of integer in this context
{
    clock_t start_time = clock();
    clock_t end_time = sec * 1000 + start_time;
    while(clock() != end_time);
}
