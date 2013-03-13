#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

#include "ofxSPKUtils.h"

namespace ofxSPK
{
	class Zone;
}

	
class ofxSPK::Zone : public TransformableProxy<ofxSPK::Zone>
{
public:
	
	typedef SPK::AABox $AABox;
	typedef SPK::Cylinder $Cylinder;
	typedef SPK::Line $Line;
	typedef SPK::Plane $Plane;
	typedef SPK::Point $Point;
	typedef SPK::Ring $Ring;
	typedef SPK::Sphere $Sphere;
	typedef SPK::ZoneIntersection $ZoneIntersection;
	typedef SPK::ZoneUnion $ZoneUnion;

	Zone() : zone(NULL) {}
	Zone(SPK::Zone *zone) : zone(zone) {}

	operator SPK::Zone* const () { return zone; }
	SPK::Zone* get() const { return zone; }
	
	template <typename T> T* get() { return (T*)zone; }
	
	static void debugDraw(const string &transformable_class_name, const SPK::Zone *zone, const ofMatrix4x4& mat, const ofColor &color = ofColor(255));

	static SPK::Transformable* getTransformable(ofxSPK::Zone *self) { return self->zone; }

protected:

	SPK::Zone *zone;
};
