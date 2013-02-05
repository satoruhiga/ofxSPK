#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

namespace ofxSPK
{
	class System;
}

class ofxSPK::System
{
public:

	System() : system(NULL) {}
	System(SPK::System *system) : system(system) {}
	virtual ~System() { exit(); }

	void setup()
	{
		if (system) return;
		system = SPK::System::create();
	}

	void exit()
	{
		SPK_Destroy(system);
		system = NULL;
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

//	SPK::Group* createGroup();
	
	void addGroup(SPK::Group *group);
	void removeGroup(SPK::Group *group);
	
	void clear();

	operator SPK::System*() const { return system; }
	SPK::System* operator->() const { return system; }

private:

	SPK::System *system;

	System(const System &copy) {}
	System& operator=(const System &copy) {}

};
