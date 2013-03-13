#include "ofxSPKModifier.h"

void ofxSPK::Modifier::setup(SPK::Modifier *modifier, SPK::Group *group)
{
	this->group = group;
	setModifier(modifier);
}

void ofxSPK::Modifier::dispose()
{
	if (modifier == NULL) return;
	
	setZone(NULL);
	
	group->removeModifier(modifier);
	SPK_Destroy(modifier);
	
	modifier = NULL;
}

void ofxSPK::Modifier::setModifier(SPK::Modifier *modifier)
{
	dispose();
	
	this->modifier = modifier;
	group->addModifier(modifier);
}

void ofxSPK::Modifier::setZone(SPK::Zone *o, bool full)
{
	SPK::Zone *zone = modifier->getZone();
	if (zone)
		SPK_Destroy(zone);
	
	modifier->setZone(o, full);
}
