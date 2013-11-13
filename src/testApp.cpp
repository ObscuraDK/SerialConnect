#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
	ofEnableSmoothing();
    
    // Doing stuff
    serialInit();
    guiInit();
    
    serialSend(1);
}

void testApp::guiInit()
{
    drawPadding = false;
    gui = new ofxUICanvas();
	gui->addLabel("InFocus 3128HD", OFX_UI_FONT_LARGE);
    gui->addSpacer();
    
    vector<string> pwr_names; pwr_names.push_back("ON"); pwr_names.push_back("OFF");
	gui->addLabel("PWR manage", OFX_UI_FONT_MEDIUM);
	gui->addRadio("HR", pwr_names, OFX_UI_ORIENTATION_HORIZONTAL);
    
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
        case 1: cout << "PWR status?" << endl;
    }
    
    nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);
    
    // PWR status
    serial.writeBytes(&buf_pwr[0], 6);
    nTimesRead = 0;
    nBytesRead = 0;
    int nRead  = 0;  // a temp variable to keep count per read
    
    unsigned char bytesReturned[3];
    
    memset(bytesReadString, 0, 4);
    memset(bytesReturned, 0, 3);
    
    while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
        nTimesRead++;
        nBytesRead = nRead;
    };
    
    memcpy(bytesReadString, bytesReturned, 3);
    
    bSendSerialMessage = false;
    readTime = ofGetElapsedTimef();
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
