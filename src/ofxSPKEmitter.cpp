#include "ofxSPKEmitter.h"

void ofxSPK::Emitter::setup(SPK::Emitter *emitter, SPK::Group *group)
{
	this->group = group;
	setEmitter(emitter);
	
	emitter->setFlow(0);
	emitter->setForce(0, 40);
}

void ofxSPK::Emitter::dispose()
{
	if (emitter == NULL) return;

	setZone(NULL);
	
	group->removeEmitter(emitter);
	SPK_Destroy(emitter);
	
	emitter = NULL;
}

void ofxSPK::Emitter::setEmitter(SPK::Emitter *emitter)
{
	dispose();
	this->emitter = emitter;
	group->addEmitter(emitter);
}

void ofxSPK::Emitter::setZone(SPK::Zone *o, bool full)
{
	SPK::Zone *zone = emitter->getZone();
	if (zone) SPK_Destroy(zone);
	
	emitter->setZone(o, full);
}
