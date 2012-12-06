#include "testApp.h"

#include "ofxSPK.h"

ofEasyCam cam;

ofxSPK::System sys;
ofxSPK::Group group;
ofxSPK::Emitter em;
ofxSPK::Modifier mod;
ofxSPK::Modifier mod2;

//--------------------------------------------------------------
void testApp::setup()
{
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);

	sys.setup();

	group = sys.createGroup();
	group.setColor(ofxSPK::RangeC(ofColor(255, 255, 0, 255), ofColor(255, 0, 0, 255)),
				   ofxSPK::RangeC(ofColor(255, 0, 255, 0), ofColor(255, 255, 0, 0)));
	group.setLifeTime(1);
	group.setFriction(0.1);
	group.setSize(ofxSPK::RangeF(1), ofxSPK::RangeF(400, 1000));

	group.setGravity(ofVec3f(0, 0, 0));

	group.reserve(10000);

	em = group.createEmitter(ofxSPK::Emitter::SPHERIC);

	em.setFlow(1000);
	em.setForce(100, 1350);

//	em.setZone(SPK::Sphere::create(ofxSPK::toSPK(ofVec3f(0, 0, 0)), 100), false);
	em.setAngles(0.0, 0.1);

	mod = group.createModifier(ofxSPK::Modifier::POINT_MASS);
	mod.get<SPK::PointMass>()->setMass(200000);

	mod2 = group.createModifier(ofxSPK::Modifier::POINT_MASS);
	mod2.setZone(SPK::Sphere::create(ofxSPK::toSPK(ofVec3f(0, 0, 0)), 200), false);
	mod2.get<SPK::PointMass>()->setMass(-300000);
}

//--------------------------------------------------------------
void testApp::update()
{
	sys.get()->setCameraPosition(ofxSPK::toSPK(cam.getPosition()));
	sys.update();

	em.setPosition(ofSignedNoise(1, 0, 0, ofGetElapsedTimef() * 0.5) * 1400,
				   ofSignedNoise(0, 1, 0, ofGetElapsedTimef() * 0.5) * 1400,
				   ofSignedNoise(0, 0, 1, ofGetElapsedTimef() * 0.5) * 1400);

	em.tilt(0.1);
	em.pan(15);
	em.roll(-3.5);

	em.update();

	mod.update();
	mod2.update();


//	mod.setPosition(ofSignedNoise(100, 0, 0, ofGetElapsedTimef() * 0.5) * 1000,
//				   ofSignedNoise(0, 100, 0, ofGetElapsedTimef() * 0.5) * 1000,
//				   ofSignedNoise(0, 0, 100, ofGetElapsedTimef() * 0.5) * 1000);
//
//	mod2.setPosition(ofSignedNoise(500, 0, 0, ofGetElapsedTimef() * 0.5) * 200,
//					ofSignedNoise(0, 500, 0, ofGetElapsedTimef() * 0.5) * 200,
//					ofSignedNoise(0, 0, 500, ofGetElapsedTimef() * 0.5) * 200);

	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw()
{
	
	
	cam.begin();

	ofEnableAlphaBlending();
	sys.draw();

	em.draw();

//	mod.draw();
//	mod2.draw();
//
//	mod2.transformGL();
//	ofNoFill();
//	ofSphere(100);
//	mod2.restoreTransformGL();

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