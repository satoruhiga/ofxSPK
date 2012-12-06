#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

#include "ofxSPKUtils.h"
#include "ofxSPKEmitter.h"
#include "ofxSPKModifier.h"

namespace ofxSPK
{

class Group
{
public:

	Group() : model(NULL), group(NULL) {}
	Group(SPK::Group *group) : group(group), model(group->getModel()) {}
	virtual ~Group() { dispose(); }

	size_t getNumActiveParticles() { return group->getParticles().getNbActive(); }
	size_t getNumReserved() { return group->getParticles().getNbReserved(); }
	void reserve(size_t size) { group->reallocate(size); }

	void dispose();

	SPK::Emitter* createEmitter(ofxSPK::Emitter::Type type);
	void addEmitter(SPK::Emitter *o);
	void removeEmitter(SPK::Emitter *o);

	SPK::Modifier* createModifier(ofxSPK::Modifier::Type type);
	void addModifier(SPK::Modifier *o);
	void removeModifier(SPK::Modifier *o);

	void setGravity(const ofVec3f& v);
	ofVec3f getGravity() const;

	void setFriction(float v) { group->setFriction(v); }
	float getFriction() { return group->getFriction(); }

	void setLifeTime(float _min, float _max = 0)
	{
		if (_max == 0) _max = _min;
		model->setLifeTime(_min, _max);
	}

	ofVec2f getLifeTime() { return ofVec2f(model->getLifeTimeMin(), model->getLifeTimeMax()); }

	inline void setSize(float v)
	{
		setSize(v, v);
	}
	
	inline void setSize(const RangeF& begin, const RangeF& end)
	{
		model->setParam(SPK::PARAM_SIZE, begin.min, begin.max, end.min, end.max);
	}

	inline void setColor(const ofFloatColor& v)
	{
		setColor(v, v);
	}

	inline void setColor(const RangeC& begin, const RangeC& end)
	{
		model->setParam(SPK::PARAM_RED, begin.min.r, begin.max.r, end.min.r, end.max.r);
		model->setParam(SPK::PARAM_GREEN, begin.min.g, begin.max.g, end.min.g, end.max.g);
		model->setParam(SPK::PARAM_BLUE, begin.min.b, begin.max.b, end.min.b, end.max.b);
		model->setParam(SPK::PARAM_ALPHA, begin.min.a, begin.max.a, end.min.a, end.max.a);
	}

	inline void setColorFade(const ofFloatColor &c0, const ofFloatColor &c1)
	{
		setColor(RangeC(c0, c0), RangeC(c1, c1));
	}

	inline void setColorRange(const ofFloatColor &c0, const ofFloatColor &c1)
	{
		setColor(RangeC(c0, c1), RangeC(c0, c1));
	}

	void setRenderer(SPK::Renderer *renderer) { group->setRenderer(renderer); }

	operator SPK::Group* () const { return group; }
	SPK::Group* get() const { return group; }

protected:

	SPK::Model *model;
	SPK::Group *group;
};

}