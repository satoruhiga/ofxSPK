#include "ofxSPKUtils.h"

void ofxSPK::drawZone(SPK::Zone *zone, const ofMatrix4x4& m)
{
	string class_name = zone->getClassName();
	const SPK::Vector3D& p = zone->getPosition();
	
	ofPushMatrix();
	ofPushStyle();
	
	ofNoFill();
	ofSetColor(255, 127);

	if (class_name == "Point")
	{
		glTranslatef(p.x, p.y, p.z);
		ofDrawAxis(5);
	}
	else if (class_name == "Line")
	{
		SPK::Line *o = (SPK::Line*)zone;
		const SPK::Vector3D& b0 = o->getBound(0);
		const SPK::Vector3D& b1 = o->getBound(1);
		
		ofLine(b0.x, b0.y, b0.z,
			   b1.x, b1.y, b1.z);
	}
	else if (class_name == "Sphere")
	{
		glTranslatef(p.x, p.y, p.z);
		
		SPK::Sphere *o = (SPK::Sphere*)zone;
		ofSphere(o->getRadius());
	}
	else if (class_name == "Ring")
	{
		glTranslatef(p.x, p.y, p.z);
		
		SPK::Ring *o = (SPK::Ring*)zone;
		const SPK::Vector3D &n = o->getNormal();
		
		ofMatrix4x4 m;
		m.makeRotationMatrix(ofVec3f(0, 0, 1), ofVec3f(n.x, n.y, n.z));
		glMultMatrixf(m.getPtr());
		
		ofCircle(0, 0, o->getMinRadius());
		ofCircle(0, 0, o->getMaxRadius());
	}
	else if (class_name == "Plane")
	{
		glTranslatef(p.x, p.y, p.z);
		
		SPK::Plane *o = (SPK::Plane*)zone;
		const SPK::Vector3D &n = o->getNormal();
		
		ofMatrix4x4 m;
		m.makeRotationMatrix(ofVec3f(0, 0, 1), ofVec3f(n.x, n.y, n.z));
		glMultMatrixf(m.getPtr());
		
		ofLine(-20000, 0, 20000, 0);
		ofLine(0, -20000, 0, 20000);
	}
	else if (class_name == "Cylinder")
	{
		glTranslatef(p.x, p.y, p.z);
		
		SPK::Cylinder *o = (SPK::Cylinder*)zone;
		const SPK::Vector3D &n = o->getDirection();
		
		ofMatrix4x4 m;
		m.makeRotationMatrix(ofVec3f(0, 0, 1), ofVec3f(n.x, n.y, n.z));
		glMultMatrixf(m.getPtr());
		
		float r = o->getRadius();
		float l = o->getLength();
		
		ofCircle(0, 0, -l * 0.5, r);
		ofCircle(0, 0, l * 0.5, r);
		
		ofLine(-r, 0, -l * 0.5, -r, 0, l * 0.5);
		ofLine(r, 0, -l * 0.5, r, 0, l * 0.5);
	}
	else if (class_name == "AABox")
	{
		SPK::AABox *o = (SPK::AABox*)zone;
		const SPK::Vector3D &n = o->getDimension();

		ofMatrix4x4 mm = m.getRotate().inverse();
		
		ofVec3f v = m.getRotate() * toOF(p);
		mm.glTranslate(v);
		mm.glScale(n.x, n.y, n.z);
		
		glMultMatrixf(mm.getPtr());
		
		ofBox(1);
	}
	
	ofPopStyle();
	ofPopMatrix();
}
