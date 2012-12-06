#include "ofxSPKGroup.h"

#include "ofxSPK.h"

void ofxSPK::Group::setGravity(const ofVec3f& v)
{
	group->setGravity(toSPK(v));
}

ofVec3f ofxSPK::Group::getGravity() const
{
	return toOF(group->getGravity());
}

void ofxSPK::Group::dispose()
{
	if (group == NULL) return;
	
	SPK_Destroy(group);
	SPK_Destroy(model);
	
	group = NULL;
	model = NULL;
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
