#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

#include "ofxSPKSystem.h"
#include "ofxSPKUtils.h"
#include "ofxSPKEmitter.h"
#include "ofxSPKModifier.h"

namespace ofxSPK
{
	class Group;
}

class ofxSPK::Group
{
public:

	Group() : group(NULL) {}
	Group(SPK::Group *group) : group(group) {}

	//
	
	void setModel(SPK::Model *model);
	SPK::Model* getModel() const { return group->getModel(); }

	//
	
	void setup(SPK::System *system);
	void dispose();
	
	//
	
	size_t getNumActiveParticles() { return group->getParticles().getNbActive(); }	
	size_t getNumReservedParticles() { return group->getParticles().getNbReserved(); }
	void reserve(size_t size) { group->reallocate(size); }

	SPK::Particle& getParticle(size_t index) { return group->getParticle(index); }

	//
	
	void setGravity(const ofVec3f& v);
	ofVec3f getGravity() const;
	
	inline void setFriction(float v);
	inline float getFriction();
	
	inline void setLifeTime(float _min, float _max = 0);
	inline ofVec2f getLifeTime();
	
	inline void setSize(float v);
	inline void setSize(const RangeF& begin, const RangeF& end);
	
	inline void setMass(float v);
	inline void setMass(float min, float max);
	
	inline void setColor(const ofFloatColor& v);
	inline void setColor(const RangeC& begin, const RangeC& end);
	
	inline void setColorFade(const ofFloatColor &c0, const ofFloatColor &c1);
	inline void setColorRange(const ofFloatColor &c0, const ofFloatColor &c1);
	
	//

	void emitStatic(int num_emit, const ofVec3f& pos);
	void emitRandom(int num_emit, const ofVec3f& pos, const RangeF& vel = RangeF(0, 30));
	void emitStraight(int num_emit, const ofVec3f& pos, const RangeF& vel = RangeF(0, 30), const ofVec3f& direction = ofVec3f(0, 1, 0));
	void emitSpheric(int num_emit, const ofVec3f& pos, const RangeF& vel, const ofVec3f& direction, const RangeF& angles = RangeF(0, 0.3));
	
	//
	
	void setRenderer(SPK::Renderer *renderer) { group->setRenderer(renderer); }

	//
	
	void debugDraw();
	
	operator SPK::Group*() const { return group; }
	SPK::Group* operator->() const { return group; }

protected:
	
	SPK::System *system;
	SPK::Group *group;
};


//

inline void ofxSPK::Group::setFriction(float v)
{
	group->setFriction(v);
}

inline float ofxSPK::Group::getFriction()
{
	return group->getFriction();
}

inline void ofxSPK::Group::setLifeTime(float _min, float _max)
{
	if (_max == 0) _max = _min;
	getModel()->setLifeTime(_min, _max);
}

inline ofVec2f ofxSPK::Group::getLifeTime()
{
	return ofVec2f(getModel()->getLifeTimeMin(),
				   getModel()->getLifeTimeMax());
}

inline void ofxSPK::Group::setSize(float v)
{
	setSize(v, v);
}

inline void ofxSPK::Group::setSize(const RangeF& begin, const RangeF& end)
{
	getModel()->setParam(SPK::PARAM_SIZE, begin.min, begin.max, end.min, end.max);
}

inline void ofxSPK::Group::setMass(float v)
{
	setMass(v, v);
}

inline void ofxSPK::Group::setMass(float min, float max)
{
	getModel()->setParam(SPK::PARAM_MASS, min, max);
}

inline void ofxSPK::Group::setColor(const ofFloatColor& v)
{
	setColor(v, v);
}

inline void ofxSPK::Group::setColor(const RangeC& begin, const RangeC& end)
{
	getModel()->setParam(SPK::PARAM_RED, begin.min.r, begin.max.r, end.min.r, end.max.r);
	getModel()->setParam(SPK::PARAM_GREEN, begin.min.g, begin.max.g, end.min.g, end.max.g);
	getModel()->setParam(SPK::PARAM_BLUE, begin.min.b, begin.max.b, end.min.b, end.max.b);
	getModel()->setParam(SPK::PARAM_ALPHA, begin.min.a, begin.max.a, end.min.a, end.max.a);
}

inline void ofxSPK::Group::setColorFade(const ofFloatColor &c0, const ofFloatColor &c1)
{
	setColor(RangeC(c0, c0), RangeC(c1, c1));
}

inline void ofxSPK::Group::setColorRange(const ofFloatColor &c0, const ofFloatColor &c1)
{
	setColor(RangeC(c0, c1), RangeC(c0, c1));
}
