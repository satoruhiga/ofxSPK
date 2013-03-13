#include "ofxSPKZone.h"

#include "ofxSPKUtils.h"

inline static void billboard()
{
    ofMatrix4x4 m;
    glGetFloatv(GL_MODELVIEW_MATRIX, m.getPtr());
    
    ofVec3f s = m.getScale();
    
    m(0, 0) = s.x;
    m(0, 1) = 0;
    m(0, 2) = 0;
    
    m(1, 0) = 0;
    m(1, 1) = s.y;
    m(1, 2) = 0;
    
    m(2, 0) = 0;
    m(2, 1) = 0;
    m(2, 2) = s.z;
    
    glLoadMatrixf(m.getPtr());
}

void ofxSPK::Zone::debugDraw(const string &transformable_class_name, const SPK::Zone *zone, const ofMatrix4x4& mat, const ofColor &color)
{
	string class_name;
	SPK::Vector3D p;
	
	if (zone)
	{
		class_name = zone->getClassName();
		p = zone->getPosition();
	}
	else
	{
		class_name = "(NULL)";
	}
	
	string text = transformable_class_name + " : " + class_name;
	ofVec3f text_pos;

	glPushMatrix();
	ofPushStyle();
	
	glMultMatrixf(mat.getPtr());
	
	ofNoFill();
	ofSetColor(color);
	
	ofColor text_color = ofColor::fromHsb((color.getHex() + 20) % 255, 255, 255);
	
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
		
		text_pos = toOF(b0).middle(toOF(b1));
	}
	else if (class_name == "Sphere")
	{
		glTranslatef(p.x, p.y, p.z);
		
		SPK::Sphere *o = (SPK::Sphere*)zone;
		
		billboard();
		ofCircle(0, 0, o->getRadius());
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
		
		ofMatrix4x4 m = mat.getRotate().inverse();
		
		ofVec3f v = mat.getRotate() * toOF(p);
		m.glTranslate(v);
		m.glScale(n.x, n.y, n.z);
		
		glMultMatrixf(m.getPtr());
		
		ofBox(1);
	}
	
	ofSetColor(text_color);
	ofDrawBitmapString(text, text_pos);
	
	ofPopStyle();
	glPopMatrix();
}
