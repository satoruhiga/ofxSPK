#pragma once

#include "ofMain.h"

#include "SPK.h"

namespace ofxSPK
{
	
inline SPK::Vector3D toSPK(const ofVec3f &v)
{
	return SPK::Vector3D(v.x, v.y, v.z);
}

inline ofVec3f toOF(const SPK::Vector3D &v)
{
	return ofVec3f(v.x, v.y, v.z);
}
	
void drawZone(SPK::Zone *zone, const ofMatrix4x4& mat);

template <typename T>
struct Range
{
	const T& min;
	const T& max;
	
	Range(const T& v) : min(v), max(v) {}
	Range(const T& min, const T& max) : min(min), max(max) {}
};
	
typedef Range<float> RangeF;
typedef Range<ofFloatColor> RangeC;

template <typename T>
class TransformableProxy : public ofNode
{
protected:
	
	void updateTransform()
	{
		SPK::Transformable *o = T::getTransformable((T*)this);
		
		if (!o) return;
		
		if (!parent)
		{
			const ofMatrix4x4& m = getLocalTransformMatrix();
			o->setTransform(m.getPtr());
		}
		else
		{
			ofMatrix4x4 m = getGlobalTransformMatrix();
			o->setTransform(m.getPtr());
		}
		
		o->updateTransform();
	}
	
	// TODO: reduce matrix update
	void onPositionChanged() { updateTransform(); }
	void onOrientationChanged() { updateTransform(); }
	void onScaleChanged() { updateTransform(); }
};
	
}
