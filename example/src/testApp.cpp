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
	
	group.setLifeTime(5);
	group.setFriction(0.1);
	group.setSize(10);

	group.setGravity(ofVec3f(0, 0, 0));

	group.reserve(10000);
}

//--------------------------------------------------------------
void testApp::update()
{
	sys->setCameraPosition(ofxSPK::toSPK(cam.getPosition()));
	sys.update();
	
	ofVec3f p;
	p.x = ofSignedNoise(100, 0, 0, ofGetElapsedTimef()) * 300;
	p.y = ofSignedNoise(0, 100, 0, ofGetElapsedTimef()) * 300;
	p.z = ofSignedNoise(0, 0, 100, ofGetElapsedTimef()) * 300;

//	group.emitStatic(10, p);
	group.emitRandom(10, p, ofxSPK::RangeF(10, 40));
//	group.emitStraight(10, p);
//	group.emitSpheric(10, p, ofxSPK::RangeF(10, 40), p.crossed(ofVec3f(1, 0, 0)), ofxSPK::RangeF(0, 0.2));
	
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