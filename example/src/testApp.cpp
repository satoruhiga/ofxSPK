#include "testApp.h"

#include "ofxSPK.h"

ofEasyCam cam;

ofxSPK::System sys;
ofxSPK::Group group;

ofxSPK::Emitter em;

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
	
	group.setLifeTime(0.5);
	group.setFriction(0.9);
	group.setSize(3);

	group.setGravity(ofVec3f(0, 0, 0));

	group.reserve(10000);
	
	em.setup(SPK::StaticEmitter::create(), group);
	em.setForce(300, 500);
	
//	em.setZone(SPK::Line::create(ofxSPK::toSPK(ofVec3f(100, 0, 0)),
//								 ofxSPK::toSPK(ofVec3f(200, 0, 0))));
	
//	em.setZone(SPK::Point::create());
//	em.setZone(SPK::Sphere::create(ofxSPK::toSPK(ofVec3f(100, 0, 0)), 50));

//	em.setZone(SPK::Ring::create(ofxSPK::toSPK(ofVec3f(100, 0, 0)), ofxSPK::toSPK(ofVec3f(0, 1, 0)), 40, 160), false);
	
//	em.setZone(SPK::Plane::create(ofxSPK::toSPK(ofVec3f(100, 0, 0)), ofxSPK::toSPK(ofVec3f(0, 1, 0))), true);

//	em.setZone(SPK::Cylinder::create(ofxSPK::toSPK(ofVec3f(100, 0, 0)), ofxSPK::toSPK(ofVec3f(0, 1, 0)), 100, 200));
	
	em.setZone(SPK::AABox::create(ofxSPK::toSPK(ofVec3f(100, 0, 0)), ofxSPK::toSPK(ofVec3f(100, 100, 100))), false);

}

//--------------------------------------------------------------
void testApp::update()
{
	sys->setCameraPosition(ofxSPK::toSPK(cam.getPosition()));
	sys.update();
	
	ofVec3f p;
	p.x = ofSignedNoise(100, 0, 0, ofGetElapsedTimef() * 0.1) * 300;
	p.y = ofSignedNoise(0, 100, 0, ofGetElapsedTimef() * 0.1) * 300;
	p.z = ofSignedNoise(0, 0, 100, ofGetElapsedTimef() * 0.1) * 300;

//	group.emitStatic(10, p);
//	group.emitRandom(10, p, ofxSPK::RangeF(10, 40));
//	group.emitStraight(10, p);
//	group.emitSpheric(10, p, ofxSPK::RangeF(10, 40), p.crossed(ofVec3f(1, 0, 0)), ofxSPK::RangeF(0, 0.2));
	
	em.setPosition(p);
	em.rotate(0.3, ofVec3f(0, 1, 0));
	em.rotate(0.1, ofVec3f(0, 0, 1));
	
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	cam.begin();
	
	em.draw();
	em.setFlow(1500);

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