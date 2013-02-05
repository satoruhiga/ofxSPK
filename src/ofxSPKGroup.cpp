#include "ofxSPKGroup.h"

#include "ofxSPK.h"

void ofxSPK::Group::setup(SPK::System *system)
{
	// cleanup
	exit();
	
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

void ofxSPK::Group::exit()
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

SPK::Emitter* ofxSPK::Group::createEmitter(ofxSPK::Emitter::Type type)
{
	ofxSPK::Emitter emitter(type);
	addEmitter(emitter);
	return emitter;
}

void ofxSPK::Group::addEmitter(SPK::Emitter *o)
{
	group->addEmitter(o);
}

void ofxSPK::Group::removeEmitter(SPK::Emitter *o)
{
	group->removeEmitter(o);
	SPK_Destroy(o);
}

SPK::Modifier* ofxSPK::Group::createModifier(ofxSPK::Modifier::Type type)
{
	ofxSPK::Modifier modifier(type);
	addModifier(modifier);
	return modifier;
}

void ofxSPK::Group::addModifier(SPK::Modifier *o)
{
	group->addModifier(o);
}

void ofxSPK::Group::removeModifier(SPK::Modifier *o)
{
	group->removeModifier(o);
	SPK_Destroy(o);
}

void ofxSPK::Group::emit(int num_emit, const ofVec3f& pos, const ofVec3f& vel)
{
	group->addParticles(num_emit, toSPK(pos), toSPK(vel));
}

void ofxSPK::Group::emit(int num_emit, const ofVec3f& pos, SPK::Emitter *emitter)
{
	group->addParticles(num_emit, toSPK(pos), emitter);
}

void ofxSPK::Group::emit(int num_emit, SPK::Emitter *emitter)
{
	group->addParticles(num_emit, emitter);
}

void ofxSPK::Group::lineEmit(float distance, const ofVec3f& start, const ofVec3f& end, const ofVec3f& vel)
{
	group->addParticles(toSPK(start), toSPK(end), toSPK(vel), distance);
}

void ofxSPK::Group::lineEmit(float distance, const ofVec3f& start, const ofVec3f& end, SPK::Emitter *emitter)
{
	group->addParticles(toSPK(start), toSPK(end), emitter, distance);
}
