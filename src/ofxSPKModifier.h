#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

#include "ofxSPKUtils.h"

namespace ofxSPK
{
	class Modifier;
}

class ofxSPK::Modifier : public TransformableProxy<ofxSPK::Modifier>
{
public:
	
	typedef SPK::Collision $Collision;
	typedef SPK::Destroyer $Destroyer;
	typedef SPK::LinearForce $LinearForce;
	typedef SPK::ModifierGroup $ModifierGroup;
	typedef SPK::Obstacle $Obstacle;
	typedef SPK::PointMass $PointMass;
	typedef SPK::Rotator $Rotator;
	typedef SPK::Vortex $Vortex;

	Modifier() : modifier(NULL) {}
	Modifier(SPK::Modifier *modifier) : modifier(modifier) {}

	void setup(SPK::Modifier *modifier, SPK::Group *group);
	void dispose();
	
	void setModifier(SPK::Modifier *modifier);
	SPK::Modifier* getModifier() { return modifier; }

	void setZone(SPK::Zone *o, bool full = true);
	SPK::Zone* getZone() { return modifier->getZone(); }
	
	template <typename T>
	T* getZoneAs() { return (T*)modifier->getZone(); }

	void setActive(bool active) { modifier->setActive(active); }
	bool isActive() const { return modifier->isActive(); }

	bool isFullZone() const { return modifier->isFullZone(); }
	
	bool setTrigger(SPK::ModifierTrigger trigger) { modifier->setTrigger(trigger); }
	SPK::ModifierTrigger getTrigger() const { return modifier->getTrigger(); }
	
	operator SPK::Modifier* const () { return modifier; }
	SPK::Modifier* operator->() const { return modifier; }
	
	template <typename T> T* get() { return (T*)modifier; }

	static SPK::Transformable* getTransformable(ofxSPK::Modifier *self) { return self->modifier; }

protected:

	SPK::Modifier *modifier;
	SPK::Group *group;

};
