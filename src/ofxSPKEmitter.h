#pragma once

#include "ofMain.h"

#include "SPK.h"
#include "SPK_GL.h"

namespace ofxSPK
{

class Emitter : public ofNode
{
public:

	enum Type
	{
		UNKNOWN,
		STATIC,
		STRAIGHT,
		SPHERIC,
		RANDOM,
		NORMAL
	};

	Emitter() : emitter(NULL) {}
	Emitter(Type type);
	Emitter(SPK::Emitter *emitter) : emitter(emitter) { guessType(); }
	~Emitter() { dispose(); }

	void dispose();

	void update();

	void setZone(SPK::Zone *o, bool full = true);

	void setFlow(float flow) { emitter->setFlow(flow); }
	void setForce(float min, float max) { emitter->setForce(min, max); }

	// only Spheric [0. - 1.]
	void setAngles(float angle0, float angle1);

	operator SPK::Emitter* const () { return emitter; }
	SPK::Emitter* get() const { return emitter; }
	template <typename T> T* get() { return (T*)emitter; }

protected:

	SPK::Emitter *emitter;
	Type type;

	void customDraw()
	{
		// TODO: draw emitter
		ofDrawAxis(50);
	}

private:

	void guessType();
};

}