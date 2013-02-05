#include "ofxSPKGroup.h"

#include "ofxSPK.h"

void ofxSPK::Group::setup(SPK::System *system)
{
	// cleanup
	dispose();
	
	this->group = new SPK::Group;
	this->system = system;

	{
		// setup model defaults
		int color_flags = SPK::FLAG_RED | SPK::FLAG_GREEN | SPK::FLAG_BLUE | SPK::FLAG_ALPHA;

		int enable_flags = color_flags | SPK::FLAG_SIZE | SPK::FLAG_CUSTOM_0;
		int mutable_flags = color_flags | SPK::FLAG_SIZE | SPK::FLAG_CUSTOM_0;
		int random_flags = color_flags | SPK::FLAG_SIZE;
		int interpolated_flags = SPK::FLAG_NONE;
		
		SPK::Model *model = SPK::Model::create(enable_flags, mutable_flags, random_flags, interpolated_flags);
		model->setParam(SPK::PARAM_CUSTOM_0, 1, 0);
		setModel(model);
	}
	
	{
		// setup group defaults
		setRenderer(getDefaultRenderer());
		reserve(3000);
		setGravity(ofVec3f(0.0f, -98.f, 0.0f));
		setFriction(0.8);
	}
	
	// register to system
	system->addGroup(group);
}

void ofxSPK::Group::dispose()
{
	if (group == NULL) return;
	
	system->removeGroup(group);
	
	SPK_Destroy(getModel());
	SPK_Destroy(group);
	
	group = NULL;
}

void ofxSPK::Group::setModel(SPK::Model *model)
{
	if (getModel()) SPK_Destroy(getModel());
	group->setModel(model);
}

void ofxSPK::Group::setGravity(const ofVec3f& v)
{
	group->setGravity(toSPK(v));
}

ofVec3f ofxSPK::Group::getGravity() const
{
	return toOF(group->getGravity());
}

void ofxSPK::Group::emitStatic(int num_emit, const ofVec3f& pos)
{
	static SPK::StaticEmitter em;
	group->addParticles(num_emit, toSPK(pos), &em);
}

void ofxSPK::Group::emitRandom(int num_emit, const ofVec3f& pos, const RangeF& vel)
{
	static SPK::RandomEmitter em;
	em.setForce(vel.min, vel.max);
	group->addParticles(num_emit, toSPK(pos), &em);
}

void ofxSPK::Group::emitStraight(int num_emit, const ofVec3f& pos, const RangeF& vel, const ofVec3f& direction)
{
	static SPK::StraightEmitter em;
	em.setForce(vel.min, vel.max);
	em.setDirection(toSPK(direction));
	group->addParticles(num_emit, toSPK(pos), &em);
}

void ofxSPK::Group::emitSpheric(int num_emit, const ofVec3f& pos, const RangeF& vel, const ofVec3f& direction, const RangeF& angles)
{
	static SPK::SphericEmitter em;
	em.setForce(vel.min, vel.max);
	em.setDirection(toSPK(direction));
	em.setAngles(angles.min * TWO_PI, angles.max * TWO_PI);
	group->addParticles(num_emit, toSPK(pos), &em);
}

