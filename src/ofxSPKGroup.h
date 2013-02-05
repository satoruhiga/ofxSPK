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
	virtual ~Group() { exit(); }

	//
	
	void setModel(SPK::Model *model);
	SPK::Model* getModel() const { return group->getModel(); }

	//
	
	void setup(SPK::System *system);
	void exit();
	
	//
	
	size_t getNumActiveParticles() { return group->getParticles().getNbActive(); }	
	size_t getNumReservedParticles() { return group->getParticles().getNbReserved(); }
	void reserve(size_t size) { group->reallocate(size); }

	SPK::Particle& getParticle(size_t index) { return group->getParticle(index); }

	//
	
	void setGravity(const ofVec3f& v);
	ofVec3f getGravity() const;
	
	void setFriction(float v) { group->setFriction(v); }
	float getFriction() { return group->getFriction(); }
	
	void setLifeTime(float _min, float _max = 0)
	{
		if (_max == 0) _max = _min;
		getModel()->setLifeTime(_min, _max);
	}
	
	ofVec2f getLifeTime() { return ofVec2f(getModel()->getLifeTimeMin(), getModel()->getLifeTimeMax()); }
	
	inline void setSize(float v) { setSize(v, v); }
	inline void setSize(const RangeF& begin, const RangeF& end)
	{
		getModel()->setParam(SPK::PARAM_SIZE, begin.min, begin.max, end.min, end.max);
	}
	
	inline void setColor(const ofFloatColor& v) { setColor(v, v); }
	inline void setColor(const RangeC& begin, const RangeC& end)
	{
		getModel()->setParam(SPK::PARAM_RED, begin.min.r, begin.max.r, end.min.r, end.max.r);
		getModel()->setParam(SPK::PARAM_GREEN, begin.min.g, begin.max.g, end.min.g, end.max.g);
		getModel()->setParam(SPK::PARAM_BLUE, begin.min.b, begin.max.b, end.min.b, end.max.b);
		getModel()->setParam(SPK::PARAM_ALPHA, begin.min.a, begin.max.a, end.min.a, end.max.a);
	}
	
	inline void setColorFade(const ofFloatColor &c0, const ofFloatColor &c1)
	{
		setColor(RangeC(c0, c0), RangeC(c1, c1));
	}
	
	inline void setColorRange(const ofFloatColor &c0, const ofFloatColor &c1)
	{
		setColor(RangeC(c0, c1), RangeC(c0, c1));
	}
	
	//
	
	SPK::Emitter* createEmitter(ofxSPK::Emitter::Type type);
	void addEmitter(SPK::Emitter *o);
	void removeEmitter(SPK::Emitter *o);

	SPK::Modifier* createModifier(ofxSPK::Modifier::Type type);
	void addModifier(SPK::Modifier *o);
	void removeModifier(SPK::Modifier *o);
	
	//

	void emit(int num_emit, const ofVec3f& pos, const ofVec3f& vel = ofVec3f(0));
	void emit(int num_emit, const ofVec3f& pos, SPK::Emitter *emitter);
	void emit(int num_emit, SPK::Emitter *emitter);
	
	void lineEmit(float distance, const ofVec3f& start, const ofVec3f& end, const ofVec3f& vel);
	void lineEmit(float distance, const ofVec3f& start, const ofVec3f& end, SPK::Emitter *emitter);

	//
	
	void setRenderer(SPK::Renderer *renderer) { group->setRenderer(renderer); }

	//
	
	operator SPK::Group*() const { return group; }
	SPK::Group* operator->() const { return group; }

protected:
	
	SPK::System *system;
	SPK::Group *group;
};
