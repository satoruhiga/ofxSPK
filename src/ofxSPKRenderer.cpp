#include "ofxSPKRenderer.h"

static SPK::Renderer *_renderer = NULL;

SPK::Renderer* ofxSPK::getDefaultRenderer()
{
	if (_renderer == NULL)
	{
		_renderer = new ofxSPK::Renderer;
	}
	
	return _renderer;
}


ofxSPK::Renderer::Renderer() : SPK::Renderer()
{
#define _S(src) #src
	
	const char *vs = _S(
		uniform float pixel_per_unit;
		
		attribute float point_size;
		attribute float life;
		
		void main()
		{
			gl_FrontColor = gl_Color;
			gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
			
			// calc point size
			gl_PointSize = (pixel_per_unit * point_size) / gl_Position.w;
		}
	);
	
#undef _S
	
	shader.setupShaderFromSource(GL_VERTEX_SHADER, vs);
	shader.linkProgram();
	
	has_life_attr = shader.getAttributeLocation("life") > 0;
	has_point_size_attr = shader.getAttributeLocation("point_size") > 0;
}

float ofxSPK::Renderer::getCurrentFov()
{
	GLfloat m[16];
	GLint viewport[4];
	
	glGetFloatv(GL_PROJECTION_MATRIX, m);
	glGetIntegerv(GL_VIEWPORT, viewport);
	
	float aspect = (float)viewport[2] / viewport[3];
	
	float a = (m[0] * aspect);
	float fov = (atan(a) - M_PI_2) * -2;
	
	return fov;
}

void ofxSPK::Renderer::render(const SPK::Group& group)
{
	float fov = getCurrentFov();
	float pixel_per_unit = fabs(ofGetViewportHeight() / (2.0f * std::tan(fov * 0.5f)));
	
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	ofPushStyle();
	
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	
	using namespace SPK;

	shader.begin();
	shader.setUniform1f("pixel_per_unit", pixel_per_unit);
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	glColorPointer(group.getModel()->isEnabled(PARAM_ALPHA) ? 4 : 3, GL_FLOAT, group.getParamStride(), group.getParamAddress(PARAM_RED));
	glVertexPointer(3, GL_FLOAT, group.getPositionStride(), group.getPositionAddress());
	
	int point_size_loc = 0;
	if (has_point_size_attr && group.getModel()->isEnabled(PARAM_SIZE))
	{
		point_size_loc = shader.getAttributeLocation("point_size");
		glVertexAttribPointer(point_size_loc, 1, GL_FLOAT, false, group.getParamStride(), group.getParamAddress(PARAM_SIZE));
		glBindAttribLocation(shader.getProgram(), point_size_loc, "point_size");
		glEnableVertexAttribArray(point_size_loc);
	}
	
	int life_loc = 0;
	if (has_life_attr && group.getModel()->isEnabled(PARAM_CUSTOM_0))
	{
		life_loc = shader.getAttributeLocation("life");
		glVertexAttribPointer(life_loc, 1, GL_FLOAT, false, group.getParamStride(), group.getParamAddress(PARAM_CUSTOM_0));
		glBindAttribLocation(shader.getProgram(), life_loc, "life");
		glEnableVertexAttribArray(life_loc);
	}
	
	glDrawArrays(GL_POINTS, 0, group.getNbParticles());
	
	if (point_size_loc)
	{
		glDisableVertexAttribArray(point_size_loc);
	}
	
	if (life_loc)
	{
		glDisableVertexAttribArray(life_loc);
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	shader.end();
	
	ofPopStyle();
	glPopAttrib();
}
