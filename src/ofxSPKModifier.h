#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

namespace ofxSPK
{

class Modifier : public ofNode
{
public:

	enum Type
	{
		UNKNOWN,
		COLLISION,
		LINEAR_FORCE,
		OBSTACLE,
		ROTATOR,
		DESTROYER,
		MODIFIER_GROUP,
		POINT_MASS,
		VORTEX
	};

	Modifier() : modifier(NULL) {}
	Modifier(Type type);
	Modifier(SPK::Modifier *modifier) : modifier(modifier) {}

	void setZone(SPK::Zone *o, bool full = true);

	void update();

	operator SPK::Modifier* const () { return modifier; }
	SPK::Modifier* get() const { return modifier; }
	template <typename T> T* get() { return (T*)modifier; }

protected:

	SPK::Modifier *modifier;
	Type type;

};

}