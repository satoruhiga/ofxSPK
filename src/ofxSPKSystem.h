#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

namespace ofxSPK
{

class System
{
public:

	System() : system(NULL) {}
	virtual ~System() { dispose(); }

	void setup()
	{
		if (system) return;
		system = SPK::System::create();
	}

	void update(float tick = ofGetLastFrameTime())
	{
		assert(system);
		system->update(tick);
	}

	void draw()
	{
		assert(system);
		system->render();
	}

	SPK::Group* createGroup();
	void removeGroup(SPK::Group *group);

	operator SPK::System* () const { return system; }
	SPK::System* get() const { return system; }

private:

	SPK::System *system;

	System(const System &copy) {}
	System& operator=(const System &copy) {}

	void dispose()
	{
		SPK_Destroy(system);
		system = NULL;
	}

};

}