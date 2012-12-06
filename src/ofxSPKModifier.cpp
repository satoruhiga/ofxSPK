#include "ofxSPKModifier.h"

ofxSPK::Modifier::Modifier(ofxSPK::Modifier::Type type) : type(type)
{
	if (type == ofxSPK::Modifier::COLLISION)
	{
		modifier = SPK::Collision::create();
	}
	else if (type == ofxSPK::Modifier::LINEAR_FORCE)
	{
		modifier = SPK::LinearForce::create();
	}
	else if (type == ofxSPK::Modifier::OBSTACLE)
	{
		modifier = SPK::Obstacle::create();
	}
	else if (type == ofxSPK::Modifier::ROTATOR)
	{
		modifier = SPK::Rotator::create();
	}
	else if (type == ofxSPK::Modifier::DESTROYER)
	{
		modifier = SPK::Destroyer::create();
	}
	else if (type == ofxSPK::Modifier::MODIFIER_GROUP)
	{
		modifier = SPK::ModifierGroup::create();
	}
	else if (type == ofxSPK::Modifier::POINT_MASS)
	{
		modifier = SPK::PointMass::create();
	}
	else if (type == ofxSPK::Modifier::VORTEX)
	{
		modifier = SPK::Vortex::create();
	}
	
	setZone(SPK::Point::create(SPK::Vector3D(0, 0, 0)));
}

void ofxSPK::Modifier::update()
{
	if (!modifier) return;
	
	ofMatrix4x4 m = getGlobalTransformMatrix();
	modifier->setTransform(m.getPtr());
	modifier->updateTransform();
}

void ofxSPK::Modifier::setZone(SPK::Zone *o, bool full)
{
	if (o == NULL) return;
	
	SPK::Zone *zone = modifier->getZone();
	if (zone)
		SPK_Destroy(zone);
	
	modifier->setZone(o, full);
}
