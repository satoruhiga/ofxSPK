#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

#include "ofxSPKUtils.h"

namespace ofxSPK
{
	class Emitter;
}

class ofxSPK::Emitter : public TransformableProxy<ofxSPK::Emitter>
{
public:

	Emitter() : emitter(NULL) {}
	Emitter(SPK::Emitter *emitter) : emitter(emitter) {}

	void setup(SPK::Emitter *emitter, SPK::Group *group);
	void dispose();

	void setEmitter(SPK::Emitter *emitter);
	SPK::Emitter* getEmitter() { return emitter; }

	void setZone(SPK::Zone *o, bool full = true);
	SPK::Zone* getZone() { return emitter->getZone(); }
	
	template <typename T>
	T* getZoneAs() { return (T*)emitter->getZone(); }

	void setActive(bool active) { emitter->setActive(active); }
	bool isActive() { return emitter->isActive(); }
	
	void setFlow(float flow) { emitter->setFlow(flow); }
	float getFlow() { return emitter->getFlow(); }
	
	void setTank(int num) { emitter->setTank(num); }
	int getTank() { return emitter->getTank(); }

	void setForce(float min, float max) { emitter->setForce(min, max); }
	void setForce(const RangeF& force) { emitter->setForce(force.min, force.max); }
	RangeF getForce() { return RangeF(emitter->getForceMin(), emitter->getForceMax()); }

	operator SPK::Emitter* const () { return emitter; }
	SPK::Emitter* operator->() const { return emitter; }
	
	template <typename T> T* get() { return (T*)emitter; }

	static SPK::Transformable* getTransformable(ofxSPK::Emitter *self) { return self->emitter; }
	
protected:

	SPK::Emitter *emitter;
	SPK::Group *group;

	void customDraw()
	{
		// TODO: draw emitter
		ofDrawAxis(5);
	}
};

