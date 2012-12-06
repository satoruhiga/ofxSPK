#include "ofxSPKEmitter.h"

ofxSPK::Emitter::Emitter(Type type)
{
	if (type == ofxSPK::Emitter::STATIC)
	{
		emitter = SPK::StaticEmitter::create();
	}
	else if (type == ofxSPK::Emitter::STRAIGHT)
	{
		emitter = SPK::StraightEmitter::create(SPK::Vector3D(0, 1, 0));
	}
	else if (type == ofxSPK::Emitter::SPHERIC)
	{
		emitter = SPK::SphericEmitter::create(SPK::Vector3D(0, 1, 0), 0, TWO_PI * 0.1);
	}
	else if (type == ofxSPK::Emitter::RANDOM)
	{
		emitter = SPK::RandomEmitter::create();
	}
	else if (type == ofxSPK::Emitter::NORMAL)
	{
		emitter = SPK::NormalEmitter::create();
	}
	
	setZone(SPK::Point::create(SPK::Vector3D(0, 0, 0)));
	
	setFlow(250);
	setForce(100, 180);
}

void ofxSPK::Emitter::dispose()
{
	if (emitter == NULL) return;
	
	SPK::Zone *zone = emitter->getZone();
	if (zone)
		SPK_Destroy(zone);
}

void ofxSPK::Emitter::update()
{
	if (!emitter) return;
	
	ofMatrix4x4 m = getGlobalTransformMatrix();
	emitter->setTransform(m.getPtr());
	emitter->updateTransform();
}

void ofxSPK::Emitter::guessType()
{
	string name = emitter->getClassName();
	
	if (name == "NormalEmitter")
	{
		type = NORMAL;
	}
	else if (name == "RandomEmitter")
	{
		type = RANDOM;
	}
	else if (name == "SphericEmitter")
	{
		type = SPHERIC;
	}
	else if (name == "StaticEmitter")
	{
		type = STATIC;
	}
	else if (name == "StraightEmitter")
	{
		type = STRAIGHT;
	}
}

void ofxSPK::Emitter::setZone(SPK::Zone *o, bool full)
{
	if (o == NULL) return;
	
	SPK::Zone *zone = emitter->getZone();
	if (zone)
		SPK_Destroy(zone);
	
	emitter->setZone(o, full);
}

void ofxSPK::Emitter::setAngles(float angle0, float angle1)
{
	if (type != SPHERIC) return;
	
	SPK::SphericEmitter *e = (SPK::SphericEmitter*)emitter;
	e->setAngles(angle0 * TWO_PI, angle1 * TWO_PI);
}
