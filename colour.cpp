#include "colour.h"

Colour::Colour()
{
	Colour(1,1,1);//default to white
}

Colour::Colour(float r, float g, float b, float a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}
