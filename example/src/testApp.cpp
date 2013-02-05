#include "testApp.h"

#include "ofxSPK.h"

ofEasyCam cam;

ofxSPK::System sys;
ofxSPK::Group group;

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);

	sys.setup();

	group.setup(sys);
	group.setColor(ofxSPK::RangeC(ofColor(255, 255, 0, 255), ofColor(255, 0, 0, 255)),
				   ofxSPK::RangeC(ofColor(255, 0, 255, 0), ofColor(255, 255, 0, 0)));
	
	group.setLifeTime(10);
	group.setFriction(0.1);
	group.setSize(ofxSPK::RangeF(1), ofxSPK::RangeF(400, 100));

	group.setGravity(ofVec3f(0, 0, 0));

	group.reserve(10000);
}

//--------------------------------------------------------------
void testApp::update()
{
	sys->setCameraPosition(ofxSPK::toSPK(cam.getPosition()));
	sys.update();

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	cam.begin();

	ofEnableAlphaBlending();
	sys.draw();

	cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}