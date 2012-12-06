#include "ofxSPKSystem.h"

#include "ofxSPKGroup.h"
#include "ofxSPKRenderer.h"

SPK::Group* ofxSPK::System::createGroup()
{
	int color_flags = SPK::FLAG_RED | SPK::FLAG_GREEN | SPK::FLAG_BLUE | SPK::FLAG_ALPHA;
	
	int enable_flags = color_flags | SPK::FLAG_SIZE | SPK::FLAG_CUSTOM_0;
	int mutable_flags = color_flags | SPK::FLAG_SIZE | SPK::FLAG_CUSTOM_0;
	int random_flags = color_flags | SPK::FLAG_SIZE;
	int interpolated_flags = SPK::FLAG_NONE;
	
	SPK::Model *model = SPK::Model::create(enable_flags, mutable_flags, random_flags, interpolated_flags);
	
	model->setParam(SPK::PARAM_CUSTOM_0, 1, 0);
	
	ofxSPK::Group group = SPK::Group::create(model, 3000);
	group.setRenderer(getDefaultRenderer());
	group.setGravity(ofVec3f(0.0f, -98.f, 0.0f));
	group.setFriction(0.8);
	
	system->addGroup(group);
	
	return group;
}

void ofxSPK::System::removeGroup(SPK::Group *group)
{
	system->removeGroup(group);
	SPK_Destroy(group);
}
