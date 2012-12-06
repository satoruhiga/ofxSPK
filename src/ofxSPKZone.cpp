#include "ofxSPKZone.h"

void ofxSPK::Zone::update()
{
	if (!zone) return;
	
	ofMatrix4x4 m = getGlobalTransformMatrix();
	zone->setTransform(m.getPtr());
	zone->updateTransform();
}
