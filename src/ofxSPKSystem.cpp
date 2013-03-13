#include "ofxSPKSystem.h"

#include "ofxSPKGroup.h"
#include "ofxSPKRenderer.h"

void ofxSPK::System::addGroup(SPK::Group *group)
{
	system->addGroup(group);
}

void ofxSPK::System::removeGroup(SPK::Group *group)
{
	system->removeGroup(group);
}

void ofxSPK::System::clear()
{
	system->empty();
}

void ofxSPK::System::debugDraw()
{
	for (int i = 0; i < system->getNbGroups(); i++)
	{
		ofxSPK::Group g(system->getGroup(i));
		g.debugDraw();
	}
}
