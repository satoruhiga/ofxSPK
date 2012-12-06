#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

namespace ofxSPK
{

class Zone : public ofNode
{
public:

	Zone() : zone(NULL) {}
	Zone(SPK::Zone *zone) : zone(zone) {}

	void update();

	operator SPK::Zone* const () { return zone; }
	SPK::Zone* get() const { return zone; }
	template <typename T> T* get() { return (T*)zone; }

protected:

	SPK::Zone *zone;
};

}