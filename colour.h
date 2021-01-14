#ifndef COLOUR_H
#define COLOUR_H

#include <QOpenGLFunctions>

class Colour
{
private:
	float r, g, b, a;
public:
	Colour();
	Colour(float r,float g, float b,float  a = 1);

	inline void setColour(float r, float g, float b, float a = 1) { this->r=r; this->g=g; this->b=b; this->a = a; }

	inline void setAlpha(float a) { this->a = a; }

	inline void draw() const { glColor4f(r,g,b,a); }
};

#endif // COLOUR_H
