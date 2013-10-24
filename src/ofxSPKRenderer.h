#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

namespace ofxSPK
{
	SPK::Renderer* getDefaultRenderer();
	
	class Renderer : public SPK::Renderer
	{
	public:
		
		std::string getClassName() const {return "ofxSPKRenderer"; }
		
		Renderer();
		
		void render(const SPK::Group& group);
		
		Renderer* clone(bool createBase) const
		{
			Renderer* cloneObject = new Renderer(*this);
			cloneObject->copyChildren(*this,createBase);
			return cloneObject;
		}
		
		void setBlending(SPK::BlendingMode blendMode) {}
		
		ofShader& getShader() { return shader; }

	protected:
		
		ofShader shader;
		
		float getCurrentFov();
		
		bool has_life_attr, has_point_size_attr;
	};
}
