#pragma once

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
	
}
